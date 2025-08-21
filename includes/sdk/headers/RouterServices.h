///////////////////////////////////////////////////////////////////////////////
// RouterServices.h

#ifndef __ROUTERSERVICES_H__
#define __ROUTERSERVICES_H__

#include "Ams.h"

///////////////////////////////////////////////////////////////////////////////

enum RouterCmdId
{
	ROUTERCMD_STATUSINFO		= AMS_ROUTERCMDS,			// generates a status info
	ROUTERCMD_CLEANUP			= AMS_ROUTERCMDS + 1,	// removes unused ports
	ROUTERCMD_FRAGMENT		= AMS_ROUTERCMDS + 2,	// fragment delivery
};

#pragma pack( push, 1 )
typedef struct TcRouterCtrlInfo
{
	ULONG			lockedMemSize;
	AmsAddr		address;
} TcRouterCtrlInfo, *PTcRouterCtrlInfo;

typedef struct RouterStatusInfo
{
	DWORD		maxMem;
	DWORD		maxMemAvail;
	DWORD		regPorts;
	DWORD		regDrivers;
	DWORD		regTrans;
	BOOL		debugWindow;
	DWORD		mailboxSize;
	DWORD		mailboxUsedEntrys;
} RouterStatusInfo, *PRouterStatusInfo;

typedef struct RouterPortStatusInfo
{
	DWORD			mailboxFullErrorCnt;
	DWORD			mailboxMaxCmdCnt;
	DWORD			mailboxCmdCnt;
	DWORD			reserved;
}RouterPortStatusInfo, *PRouterPortStatusInfo;


typedef struct TcRouterCtrlInfo64
{
	ULONGLONG	lockedMemSize;
	AmsAddr		address;
} TcRouterCtrlInfo64, *PTcRouterCtrlInfo64;

typedef struct RouterStatusInfo64
{
	ULONGLONG		maxMem;
	ULONGLONG		maxMemAvail;
	DWORD		regPorts;
	DWORD		regDrivers;
	DWORD		regTrans;
	BOOL		debugWindow;
	DWORD		mailboxSize;
	DWORD		mailboxUsedEntrys;
} RouterStatusInfo64, *PRouterStatusInfo64;

///////////////////////////////////////////////////////////////////////////////

typedef struct
{
	AmsHead	head;
} RouterStatusInfo_C, *PRouterStatusInfo_C;
#define	SIZEOF_RouterStatusInfo_C(p)	( sizeof(RouterStatusInfo_C) )
#define	CBDATA_RouterStatusInfo_C(p)	( SIZEOF_RouterStatusInfo_C(p)-sizeof(AmsHead) )

typedef struct
{
	AmsHead	head;
	RouterStatusInfo info;
} RouterStatusInfo_R, *PRouterStatusInfo_R;
#define	SIZEOF_RouterStatusInfo_R(p)	( sizeof(RouterStatusInfo_R) )
#define	CBDATA_RouterStatusInfo_R(p)	( SIZEOF_RouterStatusInfo_R(p)-sizeof(AmsHead) )

///////////////////////////////////////////////////////////////////////////////

typedef struct
{
	AmsHead	head;
} RouterCleanup_C, *PRouterCleanup_C;
#define	SIZEOF_RouterCleanup_C(p)	( sizeof(RouterCleanup_C) )
#define	CBDATA_RouterCleanup_C(p)	( SIZEOF_RouterCleanup_C(p)-sizeof(AmsHead) )

typedef struct
{
	AmsHead	head;
	DWORD		nPortsRemoved;
} RouterCleanup_R, *PRouterCleanup_R;
#define	SIZEOF_RouterCleanup_R(p)	( sizeof(RouterCleanup_R) )
#define	CBDATA_RouterCleanup_R(p)	( SIZEOF_RouterCleanup_R(p)-sizeof(AmsHead) )

#pragma pack( pop )

#endif	//	__ROUTERSERVICES_H__
