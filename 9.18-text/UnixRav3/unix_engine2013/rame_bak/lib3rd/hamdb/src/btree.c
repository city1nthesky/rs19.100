/*
 * Copyright (C) 2005-2010 Christoph Rupp (chris@crupp.de).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 *
 * See files COPYING.* for License information.
 */

/**
 * @brief implementation of btree.h
 *
 */

#include "config.h"

#include <string.h>

#include "btree.h"
#include "db.h"
#include "env.h"
#include "error.h"
#include "extkeys.h"
#include "keys.h"
#include "mem.h"
#include "page.h"
#include "txn.h"


/**
 * perform a binary search for the *smallest* element, which is >= the
 * key
 */
ham_status_t 
btree_get_slot(ham_db_t *db, ham_page_t *page, 
        ham_key_t *key, ham_s32_t *slot, int *pcmp)
{
    int cmp = -1;
    btree_node_t *node = ham_page_get_btree_node(page);
    ham_s32_t r = btree_node_get_count(node)-1;
    ham_s32_t l = 1;
    ham_s32_t i;
    ham_s32_t last = MAX_KEYS_PER_NODE + 1;

    ham_assert(btree_node_get_count(node)>0, 
            ("node is empty"));

    /*
     * only one element in this node?
     */
    if (r==0) {
        cmp=key_compare_pub_to_int(db, page, key, 0);
        if (cmp < -1)
            return (ham_status_t)cmp;
        *slot=cmp<0 ? -1 : 0;
        goto bail;
    }

    for (;;) {
        /* [i_a] compare is not needed     (while (r>=0)) */

        /* get the median item; if it's identical with the "last" item,
         * we've found the slot */
        i=(l+r)/2;

        if (i==last) {
            *slot=i;
            cmp=1;
            ham_assert(i >= 0, (0));
            ham_assert(i < MAX_KEYS_PER_NODE + 1, (0));
            break;
        }
        
        /* compare it against the key */
        cmp=key_compare_pub_to_int(db, page, key, (ham_u16_t)i);
        if (cmp < -1)
            return (ham_status_t)cmp;

        /* found it? */
        if (cmp==0) {
            *slot=i;
            break;
        }

        /* if the key is bigger than the item: search "to the left" */
        if (cmp<0) {
            if (r==0) {
                ham_assert(i == 0, (0));
                *slot=-1;
                break;
            }
            r=i-1;
        }
        else {
            last=i;
            l=i+1;
        }
    }
    
bail:
    if (pcmp /* && *slot!=-1 */) {
        /*
           [i_a] reduced the total number of key comparisons; this one is not 
                 needed any more, as it was only really required to 
                 compensate for the (i==last) conditional jump above.
                 So we can simply use 'cmp' as-is.
        */
        *pcmp=cmp;
    }

    return (0);
}

ham_size_t
btree_calc_maxkeys(ham_size_t pagesize, ham_u16_t keysize)
{
    ham_size_t p, k, max;

    /* 
     * a btree page is always P bytes long, where P is the pagesize of 
     * the database. 
     */
    p=pagesize;

    /* every btree page has a header where we can't store entries */
    p-=OFFSETOF(btree_node_t, _entries);

    /* every page has a header where we can't store entries */
    p -= page_get_persistent_header_size();

    /*
     * compute the size of a key, k. 
     */
    k = keysize + db_get_int_key_header_size();

    /* 
     * make sure that MAX is an even number, otherwise we can't calculate
     * MIN (which is MAX/2)
     */
    max=p/k;
    return (max&1 ? max-1 : max);
}

/**                                                                 
 * estimate the number of keys per page, given the keysize          
 *                                                                  
 * @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t
my_fun_calc_keycount_per_page(ham_btree_t *be, ham_size_t *maxkeys, 
                ham_u16_t keysize)
{
    ham_db_t *db=be_get_db(be);

    if (keysize == 0) {
        *maxkeys=btree_get_maxkeys(be);
    }
    else {
        /* 
         * prevent overflow - maxkeys only has 16 bit! 
         */
        *maxkeys=btree_calc_maxkeys(env_get_pagesize(db_get_env(db)), keysize);
        if (*maxkeys>MAX_KEYS_PER_NODE) {
            ham_trace(("keysize/pagesize ratio too high"));
            return HAM_INV_KEYSIZE;
        }
        else if (*maxkeys==0) {
            ham_trace(("keysize too large for the current pagesize"));
            return HAM_INV_KEYSIZE;
        }
    }

    return (0);
}

/**                                                                 
 * create and initialize a new backend                              
 *                                                                  
 * @remark this function is called after the @a ham_db_t structure  
 * and the file were created                                        
 *                                                                  
 * the @a flags are stored in the database; only transfer           
 * the persistent flags!                                            
 *
 * @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t 
my_fun_create(ham_btree_t *be, ham_u16_t keysize, ham_u32_t flags)
{
    ham_status_t st;
    ham_page_t *root;
    ham_size_t maxkeys;
    ham_db_t *db=be_get_db(be);
    db_indexdata_t *indexdata=env_get_indexdata_ptr(db_get_env(db), 
                                db_get_indexdata_offset(db));
    if (be_is_active(be))
    {
        ham_trace(("backend has alread been initialized before!"));
        /* HAM_INTERNAL_ERROR -- not really, when keeping custom 
         * backends in mind */
        return HAM_ALREADY_INITIALIZED; 
    }

    /* 
     * prevent overflow - maxkeys only has 16 bit! 
     */
    maxkeys=btree_calc_maxkeys(env_get_pagesize(db_get_env(db)), keysize);
    if (maxkeys>MAX_KEYS_PER_NODE) {
        ham_trace(("keysize/pagesize ratio too high"));
        return HAM_INV_KEYSIZE;
    }
    else if (maxkeys==0) {
        ham_trace(("keysize too large for the current pagesize"));
        return HAM_INV_KEYSIZE;
    }

    /*
     * allocate a new root page
     */
    st=db_alloc_page(&root, db, PAGE_TYPE_B_ROOT, PAGE_IGNORE_FREELIST);
    ham_assert(st ? root == NULL : 1, (0));
    ham_assert(!st ? root != NULL : 1, (0));
    if (!root)
        return st ? st : HAM_INTERNAL_ERROR;

    memset(page_get_raw_payload(root), 0, 
            sizeof(btree_node_t)+sizeof(ham_perm_page_union_t));

    /*
     * calculate the maximum number of keys for this page, 
     * and make sure that this number is even
     */
    btree_set_maxkeys(be, (ham_u16_t)maxkeys);
    be_set_dirty(be, HAM_TRUE);
    be_set_keysize(be, keysize);
    be_set_flags(be, flags);

    btree_set_rootpage(be, page_get_self(root));

    index_clear_reserved(indexdata);
    index_set_max_keys(indexdata, (ham_u16_t)maxkeys);
    index_set_keysize(indexdata, keysize);
    index_set_self(indexdata, page_get_self(root));
    index_set_flags(indexdata, flags);
    index_set_recno(indexdata, 0);
    index_clear_reserved(indexdata);

    env_set_dirty(db_get_env(db));

    be_set_active(be, HAM_TRUE);

    return (0);
}

/**                                                                 
 * open and initialize a backend                                    
 *                                                                  
 * @remark this function is called after the ham_db_structure       
 * was allocated and the file was opened                            

 @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t 
my_fun_open(ham_btree_t *be, ham_u32_t flags)
{
    ham_offset_t rootadd;
    ham_offset_t recno;
    ham_u16_t maxkeys;
    ham_u16_t keysize;
    ham_db_t *db=be_get_db(be);
    db_indexdata_t *indexdata=env_get_indexdata_ptr(db_get_env(db), 
                                    db_get_indexdata_offset(db));

    /*
     * load root address and maxkeys (first two bytes are the
     * database name)
     */
    maxkeys = index_get_max_keys(indexdata);
    keysize = index_get_keysize(indexdata);
    rootadd = index_get_self(indexdata);
    flags = index_get_flags(indexdata);
    recno = index_get_recno(indexdata);

    btree_set_rootpage(be, rootadd);
    btree_set_maxkeys(be, maxkeys);
    be_set_keysize(be, keysize);
    be_set_flags(be, flags);
    be_set_recno(be, recno);

    be_set_active(be, HAM_TRUE);

    return (0);
}

/**                                                                 
 * flush the backend                                                
 *                                                                  
 * @remark this function is called during ham_flush                 

 @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t
my_fun_flush(ham_btree_t *be)
{
    ham_db_t *db=be_get_db(be);
    db_indexdata_t *indexdata=env_get_indexdata_ptr(db_get_env(db), 
                        db_get_indexdata_offset(db));

    /*
     * nothing to do if the backend was not touched
     */
    if (!be_is_dirty(be))
        return (0);

    index_set_max_keys(indexdata, btree_get_maxkeys(be));
    index_set_keysize(indexdata, be_get_keysize(be));
    index_set_self(indexdata, btree_get_rootpage(be));
    index_set_flags(indexdata, be_get_flags(be));
    index_set_recno(indexdata, be_get_recno(be));
    index_clear_reserved(indexdata);

    env_set_dirty(db_get_env(db));
    be_set_dirty(be, HAM_FALSE);

    return (0);
}

/**                                                                 
 * close the backend                                                
 *                                                                  
 * @remark this function is called before the file is closed        

 @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t
my_fun_close(ham_btree_t *be)
{
    ham_status_t st; 
    ham_env_t *env=db_get_env(be_get_db(be));

    /*
     * just flush the backend info if it's dirty
     */
    st = my_fun_flush(be);

    /* even when an error occurred, the backend has now been de-activated */
    be_set_active(be, HAM_FALSE);

    /* free allocated storage */
    if (btree_get_keydata1(be)) {
        allocator_free(env_get_allocator(env), btree_get_keydata1(be));
        btree_set_keydata1(be, 0);
    }
    if (btree_get_keydata2(be)) {
        allocator_free(env_get_allocator(env), btree_get_keydata2(be));
        btree_set_keydata2(be, 0);
    }

    return st;
}

/**                                                                 
 * free all allocated resources                                     
 *                                                                  
 * @remark this function is called after _fun_close()               

 @note This is a B+-tree 'backend' method.
 */                                                                 
static ham_status_t
my_fun_delete(ham_btree_t *be)
{
    /*
     * nothing to do
     */
    return HAM_SUCCESS;
}

/**                                                                    
 Create a new cursor instance.                                        

 @note This is a B+-tree 'backend' method.
*/                                                                    
static ham_status_t 
my_fun_cursor_create(ham_btree_t *be, ham_db_t *db, ham_txn_t *txn, ham_u32_t flags, ham_cursor_t **cu)
{
    return bt_cursor_create(db, txn, flags, (ham_bt_cursor_t **)cu);
}
                                                                    

/**                                                                    
 * uncouple all cursors from a page                                    
 *                                                                    
 * @remark this is called whenever the page is deleted or            
 * becoming invalid                                                    

 @note This is a B+-tree 'backend' method.
 */                                                                    
static ham_status_t
my_fun_uncouple_all_cursors(ham_btree_t *be, ham_page_t *page, ham_size_t start)
{
    return (bt_uncouple_all_cursors(page, start));
}

/**                                                                    
Close (and free) all cursors related to this database table.        

 @note This is a B+-tree 'backend' method.
*/                                                                    
static ham_status_t 
my_fun_close_cursors(ham_btree_t *be, ham_u32_t flags)
{
    ham_db_t *db=be_get_db(be);

    ham_assert(db, (0));

    return (btree_close_cursors(db, flags));
}


/**                                                                    
 * Remove all extended keys for the given @a page from the            
 * extended key cache.                                                
 */                                                                    
static ham_status_t
my_fun_free_page_extkeys(ham_btree_t *be, ham_page_t *page, ham_u32_t flags)
{
    ham_db_t *db=be_get_db(be);
    
    ham_assert(page_get_owner(page) == db, (0));
    
    ham_assert(0 == (flags & ~DB_MOVE_TO_FREELIST), (0));

    /*
     * if this page has a header, and it's either a B-Tree root page or 
     * a B-Tree index page: remove all extended keys from the cache, 
     * and/or free their blobs
     */
    if (page_get_pers(page) 
            && (!(page_get_npers_flags(page)&PAGE_NPERS_NO_HEADER))
            && (page_get_type(page)==PAGE_TYPE_B_ROOT 
                || page_get_type(page)==PAGE_TYPE_B_INDEX)) 
    {
        ham_size_t i;
        ham_offset_t blobid;
        int_key_t *bte;
        btree_node_t *node=ham_page_get_btree_node(page);
        extkey_cache_t *c;

        ham_assert(db, ("Must be set as page owner when this is a Btree page"));
        ham_assert(db=page_get_owner(page), (""));
        c=db_get_extkey_cache(db);

        for (i=0; i<btree_node_get_count(node); i++) 
        {
            bte=btree_node_get_key(db, node, i);
            if (key_get_flags(bte)&KEY_IS_EXTENDED) 
            {
                blobid=key_get_extended_rid(db, bte);
                if (env_get_rt_flags(db_get_env(db))&HAM_IN_MEMORY_DB) 
                {
                    /* delete the blobid to prevent that it's freed twice */
                    *(ham_offset_t *)(key_get_key(bte)+
                        (db_get_keysize(db)-sizeof(ham_offset_t)))=0;
                }
                //(void)key_erase_record(db, bte, 0, BLOB_FREE_ALL_DUPES);
                if (c)
                    (void)extkey_cache_remove(c, blobid);
            }
        }
    }

    return (HAM_SUCCESS);
}

ham_status_t
btree_create(ham_backend_t **backend_ref, ham_db_t *db, ham_u32_t flags)
{
    ham_btree_t *btree;

    *backend_ref = 0;

    btree = (ham_btree_t *)allocator_calloc(env_get_allocator(db_get_env(db)), sizeof(*btree));
    if (!btree)
    {
        return HAM_OUT_OF_MEMORY;
    }

    /* initialize the backend */
    btree->_db=db;
    btree->_fun_create=my_fun_create;
    btree->_fun_open=my_fun_open;
    btree->_fun_close=my_fun_close;
    btree->_fun_flush=my_fun_flush;
    btree->_fun_delete=my_fun_delete;
    btree->_fun_find=btree_find;
    btree->_fun_insert=btree_insert;
    btree->_fun_erase=btree_erase;
    btree->_fun_enumerate=btree_enumerate;
    btree->_fun_check_integrity=btree_check_integrity;
    btree->_fun_calc_keycount_per_page=my_fun_calc_keycount_per_page;
    btree->_fun_cursor_create = my_fun_cursor_create;
    btree->_fun_close_cursors = my_fun_close_cursors;
    btree->_fun_uncouple_all_cursors=my_fun_uncouple_all_cursors;
    btree->_fun_free_page_extkeys=my_fun_free_page_extkeys;

    *backend_ref = (ham_backend_t *)btree;
    return HAM_SUCCESS;
}

ham_status_t
btree_traverse_tree(ham_page_t **page_ref, ham_s32_t *idxptr, 
                    ham_db_t *db, ham_page_t *page, ham_key_t *key)
{
    ham_status_t st;
    ham_s32_t slot;
    int_key_t *bte;
    btree_node_t *node=ham_page_get_btree_node(page);

    /*
     * make sure that we're not in a leaf page, and that the 
     * page is not empty
     */
    ham_assert(btree_node_get_count(node)>0, (0));
    ham_assert(btree_node_get_ptr_left(node)!=0, (0));

    st=btree_get_slot(db, page, key, &slot, 0);
    if (st)
    {
        *page_ref = 0;
        return st;
    }

    if (idxptr)
        *idxptr=slot;

    if (slot==-1)
    {
        st = db_fetch_page(page_ref, db, btree_node_get_ptr_left(node), 0);
        ham_assert(st ? !*page_ref : 1, (0));
        return st;
    }
    else 
    {
        bte=btree_node_get_key(db, node, slot);
        ham_assert(key_get_flags(bte)==0 || 
                key_get_flags(bte)==KEY_IS_EXTENDED,
                ("invalid key flags 0x%x", key_get_flags(bte)));
        st = db_fetch_page(page_ref, db, key_get_ptr(bte), 0);
        ham_assert(st ? !*page_ref : 1, (0));
        return st;
    }
}

ham_s32_t 
btree_node_search_by_key(ham_db_t *db, ham_page_t *page, ham_key_t *key, 
                    ham_u32_t flags)
{
    int cmp; /* [i_a] */
    ham_s32_t slot;
    ham_status_t st;
    btree_node_t *node=ham_page_get_btree_node(page);

    /* ensure the approx flag is NOT set by anyone yet */
    ham_key_set_intflags(key, ham_key_get_intflags(key) & ~KEY_IS_APPROXIMATE);

    if (btree_node_get_count(node)==0)
        return (-1);

    st=btree_get_slot(db, page, key, &slot, &cmp);
    if (st) {
        ham_assert(st < -1, (0));
        return st;
    }

    /*
       'approximate matching'

        When we get here and cmp != 0 and we're looking for LT/GT/LEQ/GEQ 
        key matches, this is where we need to do our prep work.

        Yes, due to the flag tweak in a caller when we have (the usual) 
        multi-page DB table B+tree, both LT and GT flags are 'ON' here, 
        but let's not get carried way and assume that is always
        like that. To elaborate a bit here: it may seem like doing something 
        simple the hard way, but in here, we do NOT know if there are 
        adjacent pages, so 'edge cases' like the scenarios 1, 2, and 5 below 
        should NOT return an error KEY_NOT_FOUND but instead produce a 
        valid slot AND, most important, the accompanying 'sign' (LT/GT) flags 
        for that slot, so that the outer call can analyze our response and 
        shift the key index into the left or right adjacent page, when such 
        is available. We CANNOT see that here, so we always should work with 
        both LT+GT enabled here.
        And to make matters a wee bit more complex still: the one exception 
        to the above is when we have a single-page table: then we get 
        the actual GT/LT flags in here, as we're SURE there won't be any 
        left or right neighbour pages for us to shift into when the need 
        arrises.

        Anyway, the purpose of the next section is to see if we have a 
        matching 'approximate' key AND feed the 'sign' (i.e. LT(-1) or 
        GT(+1)) back to the caller, who knows _exactly_ what the
        user asked for and can thus take the proper action there.

        Here, we are only concerned about determining which key index we 
        should produce, IFF we should produce a matching key.

        Assume the following page layout, with two keys (values 2 and 4):

      * index:
      *    [0]   [1]  
      * +-+---+-+---+-+
      * | | 2 | | 4 | |
      * +-+---+-+---+-+

        Various scenarios apply. For the key search (key ~ 1) i.e. (key=1, 
        flags=NEAR), we get this:

        cmp = -1;
        slot = -1;

        hence we point here:

      *  |
      *  V
      * +-+---+-+---+-+
      * | | 2 | | 4 | |
      * +-+---+-+---+-+

        which is not a valid spot. Should we return a key? YES, since no key 
        is less than '1', but there exists a key '2' which fits as NEAR allows 
        for both LT and GT. Hence, this should be modified to become

        slot=0
        sign=GT

      *     | ( slot++ )
      *     V
      * +-+---+-+---+-+
      * | | 2 | | 4 | |
      * +-+---+-+---+-+


        Second scenario: key <= 1, i.e. (key=1, flags=LEQ)
        which gives us the same as above:

       cmp = -1;
       slot = -1;

        hence we point here:

      *  |
      *  V
      * +-+---+-+---+-+
      * | | 2 | | 4 | |
      * +-+---+-+---+-+

        Should we return a valid slot by adjusting? Your common sense says 
        NO, but the correct answer is YES, since (a) we do not know if the 
        user asked this, as _we_ see it in here as 'key ~ 1' anyway and 
        we must allow the caller to adjust the slot by moving it into the 
        left neighbour page -- an action we cannot do as we do not know, 
        in here, whether there's more pages adjacent to this one we're 
        currently looking at.

        EXCEPT... the common sense answer 'NO' is CORRECT when we have a 
        single-page db table in our hands; see the remark at the top of this 
        comment section; in that case, we can safely say 'NO' after all.

        Third scenario: key ~ 3
        which gives us either:

       cmp = -1;
       slot = 1;

         or

       cmp = 1;
       slot = 0;

         As we check for NEAR instead of just LT or GT, both are okay like 
         that, no adjustment needed.
         All we need to do is make sure sure we pass along the proper LT/GT 
         'sign' flags for outer level result processing.

      
        Fourth scenario: key < 3

        again, we get either:

       cmp = -1;
       slot = 1;

         or

       cmp = 1;
       slot = 0;

        but this time around, since we are looking for LT, we'll need to 
        adjust the second result, when that happens by slot++ and sending 
        the appropriate 'sign' flags.
    
      Fifth scenario: key ~ 5

        which given us:

       cmp = -1;
       slot = 1;

         hence we point here:

      *           |
      *           V
      * +-+---+-+---+-+
      * | | 2 | | 4 | |
      * +-+---+-+---+-+

        Should we return this valid slot? Yup, as long as we mention that 
        it's an LT(less than) key; the caller can see that we returned the 
        slot as the upper bound of this page and adjust accordingly when
        the actual query was 'key > 5' instead of 'key ~ 5' which is how we 
        get to see it.
    */
    /*
      Note that we have a 'preference' for LT answers in here; IFF the user'd 
        asked NEAR questions, most of the time that would give him LT answers, 
        i.e. the answers to NEAR ~ LT questions -- mark the word 'most' in 
        there: this is not happening when we're ending up at a page's lower 
        bound.
     */
    if (cmp)
    {
        /*
         When slot == -1, you're in a special situation: you do NOT know what 
         the comparison with slot[-1] delivers, because there _is_ _no_ slot 
         -1, but you _do_ know what slot[0] delivered: 'cmp' is the
         value for that one then.
         */
        if (slot < 0) 
            slot = 0;

        ham_assert(slot <= btree_node_get_count(node) - 1, (0));

        if (flags & HAM_FIND_LT_MATCH)
        {
            if (cmp < 0)
            {
                /* key @ slot is LARGER than the key we search for ... */
                if (slot > 0)
                {
                    slot--;
                    ham_key_set_intflags(key, ham_key_get_intflags(key) | KEY_IS_LT);
                    cmp = 0;
                }
                else if (flags & HAM_FIND_GT_MATCH)
                {
                    ham_assert(slot == 0, (0));
                    ham_key_set_intflags(key, ham_key_get_intflags(key) | KEY_IS_GT);
                    cmp = 0;
                }
            }
            else
            {
                /* key @ slot is SMALLER than the key we search for */
                ham_assert(cmp > 0, (0));
                ham_key_set_intflags(key, ham_key_get_intflags(key) | KEY_IS_LT);
                cmp = 0;
            }
        } 
        else if (flags&HAM_FIND_GT_MATCH)   
        {
            /*
             When we get here, we're sure HAM_FIND_LT_MATCH is NOT set...
             */
            ham_assert(!(flags&HAM_FIND_LT_MATCH), (0));

            if (cmp < 0)
            {
                /* key @ slot is LARGER than the key we search for ... */
                ham_key_set_intflags(key, ham_key_get_intflags(key) | KEY_IS_GT);
                cmp = 0;
            }
            else
            {
                /* key @ slot is SMALLER than the key we search for */
                ham_assert(cmp > 0, (0));
                if (slot < btree_node_get_count(node) - 1)
                {
                    slot++;
                    ham_key_set_intflags(key, ham_key_get_intflags(key) | KEY_IS_GT);
                    cmp = 0;
                }
            }
        }
    }

    if (cmp)
        return (-1);

    ham_assert(slot >= -1, (0));
    return (slot);
}

/**
 Always make sure the db cursor set is released, no matter what happens.
*/
ham_status_t 
btree_close_cursors(ham_db_t *db, ham_u32_t flags)
{
    ham_status_t st = HAM_SUCCESS;
    ham_status_t st2 = HAM_SUCCESS;

    /*
    * auto-cleanup cursors?
    */
    if (db_get_cursors(db)) {
        ham_bt_cursor_t *c=(ham_bt_cursor_t *)db_get_cursors(db);
        while (c) {
            ham_bt_cursor_t *next=(ham_bt_cursor_t *)cursor_get_next(c);
            if (flags&HAM_AUTO_CLEANUP)
            {
                st=ham_cursor_close((ham_cursor_t *)c);
            }
            else
            {
                //st=bt_cursor_close(c);
                st=c->_fun_close(c);
            }
            if (st)
            {
                if (st2 == 0) st2 = st;
                /* continue to try to close the other cursors, though */
            }
            c=next;
        }
        db_set_cursors(db, 0);
    }
    
    return st2;
}

