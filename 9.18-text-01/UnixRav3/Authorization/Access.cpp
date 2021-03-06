#include "Stdafx.h"

/*
struct STUSERACCESS				// 权限和等级对照结构
{
	RS_DWORD dwAccess;			// 权限值
	RS_DWORD dwItemLevel;		// 所要求的项目等级
};

// 用户 ID 表
const RS_DWORD g_adwUserTable[USER_NUMBER][RS_USERID_LEN] = 
{
	{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{0xFFFFFFFF, 0, 0, 1},		//安装程序
	{0xFFFFFFFF, 0, 0, 2},		//主程序
	{0, 0, 0, 0}
};

// 用户权限与项目等级的对照表
const STUSERACCESS g_astUserAccess[USER_NUMBER][ACCESS_NUMBER] =
{
	{
		{CONFIG_ACCESS_READ,	1},
		{CONFIG_ACCESS_WRITE,	1},
		{CONFIG_ACCESS_CREATE,	1},
		{CONFIG_ACCESS_DELETE,	1},
		{CONFIG_ACCESS_IMPORT,	1},
		{CONFIG_ACCESS_EXPORT,	1},
		{CONFIG_ACCESS_LOCK,	1},
		{CONFIG_ACCESS_UNLOCK,	1},
		{CONFIG_ACCESS_CREATETMP,	1},
		{CONFIG_ACCESS_QUERY,	1},
		{CONFIG_ACCESS_SHARE,	1}
	},
	{
		{CONFIG_ACCESS_READ,	1},
		{CONFIG_ACCESS_WRITE,	1},
		{CONFIG_ACCESS_CREATE,	1},
		{CONFIG_ACCESS_DELETE,	5},
		{CONFIG_ACCESS_IMPORT,	1},
		{CONFIG_ACCESS_EXPORT,	1},
		{CONFIG_ACCESS_LOCK,	1},
		{CONFIG_ACCESS_UNLOCK,	1},
		{CONFIG_ACCESS_CREATETMP,	1},
		{CONFIG_ACCESS_QUERY,	1},
		{CONFIG_ACCESS_SHARE,	1}
	},
	{
		{CONFIG_ACCESS_READ,	4},
		{CONFIG_ACCESS_WRITE,	4},
		{CONFIG_ACCESS_CREATE,	4},
		{CONFIG_ACCESS_DELETE,	2},
		{CONFIG_ACCESS_IMPORT,	1},
		{CONFIG_ACCESS_EXPORT,	1},
		{CONFIG_ACCESS_LOCK,	1},
		{CONFIG_ACCESS_UNLOCK,	1},
		{CONFIG_ACCESS_CREATETMP,	1},
		{CONFIG_ACCESS_QUERY,	1},
		{CONFIG_ACCESS_SHARE,	1}
	},
	{
		{CONFIG_ACCESS_READ,	2},
		{CONFIG_ACCESS_WRITE,	2},
		{CONFIG_ACCESS_CREATE,	2},
		{CONFIG_ACCESS_DELETE,	2},
		{CONFIG_ACCESS_IMPORT,	1},
		{CONFIG_ACCESS_EXPORT,	1},
		{CONFIG_ACCESS_LOCK,	1},
		{CONFIG_ACCESS_UNLOCK,	1},
		{CONFIG_ACCESS_CREATETMP,	1},
		{CONFIG_ACCESS_QUERY,	1},
		{CONFIG_ACCESS_SHARE,	1}
	}
};

// 取出一定等级的项目所对应的权限
RS_RESULT GetUserAccess(const RS_DWORD* pdwUser, RS_DWORD dwItemLevel, RS_DWORD& dwAccess)
{
	if(pdwUser == NULL)
		return ERR_FAILED;

	for(int i=0; i<USER_NUMBER; i++)
	{
		if(memcmp(g_adwUserTable[i], pdwUser, sizeof(RS_DWORD) * RS_USERID_LEN) == 0)
			break;
	}

	if(i == USER_NUMBER)	// 表示没有找到此用户
		return ERR_CFG_USER_NOTFOUND;

	dwAccess = 0;
	for(int j=0; j<ACCESS_NUMBER; j++)
	{
		if(g_astUserAccess[i][j].dwItemLevel <= dwItemLevel)
			dwAccess |= g_astUserAccess[i][j].dwAccess;
	}

	return ERR_SUCCESS;
}
*/