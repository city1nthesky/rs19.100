/*
	R_STDLIB.C - platform-specific C library routines for RSAEURO

    Copyright (c) J.S.A.Kapp 1994 - 1996.

	RSAEURO - RSA Library compatible with RSAREF(tm) 2.0.

	All functions prototypes are the Same as for RSAREF(tm).
	To aid compatiblity the source and the files follow the
	same naming comventions that RSAREF(tm) uses.  This should aid
	direct importing to your applications.

	This library is legal everywhere outside the US.  And should
	NOT be imported to the US and used there.

	All Trademarks Acknowledged.

	Secure Standard Library Routines.

	Revision history
		0.90 First revision, routines no longer rely on
		ANSI Standard C provided routines as RSAREF(tm) does.

		0.91 Second revision, minor improvements to orginal
		code.

		0.92 Current revision, modified to allow use of assembler
		versions or the ANSI standard equivalent versions.
*/

#include "rsaeuro.h"

/* Library Copyright Message */

//CHAR *Copyright[] = { "Copyright (c) J.S.A.Kapp 94-96." };

#ifndef USE_ANSI
/* Secure memset routine */

#ifndef USEASM

void R_memset( POINTER output, int value, unsigned int len)
{
	if(len != 0) {
		do {
			*output++ = (unsigned char)value;
		}while(--len != 0);
	}
}

/* Secure memcpy routine */

void R_memcpy( POINTER output, POINTER input, unsigned int len )
{
	if (len != 0) {
		do {
			*output++ = *input++;
		}while (--len != 0);
	}
}

/* Secure memcmp routine */

int R_memcmp( POINTER Block1, POINTER Block2, unsigned int len )
{
	if(len != 0) {
		/* little trick in declaring vars */
		register const unsigned char *p1 = Block1, *p2 = Block2;

		do {
			if(*p1++ != *p2++)
				return(*--p1 - *--p2);
		}while(--len != 0);
	}
	return(0);
}

#endif /* USEASM */
#endif /* USE_ANSI */
