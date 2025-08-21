///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"
#include "TcBaseServices.h"
#include "Ams.h"
#include "Ads.h"

#define	TCSERVICES_INUSE
#define	TCOMINITDATA_ALIGNED
#if !defined(TC_ENVIRONMENT_CE) && !defined(TC_ENVIRONMENT_CE_RT)
#define	TCOM_REPOSITORY
#define	TCTMCHANDLER_SUPPORT
#define	TCTMLHANDLER_SUPPORT
#endif
//#define	ETH_REDUNDANCY_HDL
#define	POINTER_MAPPING

#define	TCSDK_VERSION				0x0300
#define	TCSDK_VERSION_211			0x0211
#define	TCSDK_VERSION_211R2		0x0212
#define	TCSDK_VERSION_300			0x0300

typedef	ULONG		CATTCID, *PCATTCID;	// Category ID
typedef	ULONG		DTCID, *PDTCID;		// DataType ID
typedef	ULONG		PTCID, *PPTCID;		// Parameter ID
typedef	ULONG		PTCGP, *PPTCGP;		// Parameter Group
typedef	ULONG		DISPTCID;

#define	TCOMOBJ_NAME_LEN								128

#define	TCOMOBJ_MIN_OID								0x00100000
#define	TCOMOBJ_ADSPORTOWNER_OID					0x00100000


// HRESULTS
#define  S_PENDING										(0x00000203L)
#define  S_OLDBOOTDATA									(0x00000253L)
#define  S_DEMO_LICENSE									(0x00000254L)
#define  S_OEM_LICENSE									(0x00000255L)
#define	S_WATCHDOG_TIMEOUT							(0x00000256L)
#define	S_DIVISION_BY_ZERO							(0x00000257L)	// e.g. worked around integer division by zero


// create instances
#define TCOMSERVER_IGRP_CREATEINSTANCE				0x00000003
#define TCOMSERVER_IGRP_CREATEINSTANCE_MULTI		0x00000004
#define TCOMSERVER_IOFFS_CREATE_IF_NOT_EXIST			0x00000001
#define TCOMSERVER_IGRP_LOADDRIVER					0x00000005	// data: szKey ("<szVendor>|<szDriver>|<szVersion>"
#define TCOMSERVER_IGRP_UNLOADDRIVER				0x00000006	// data: szKey ("<szVendor>|<szDriver>|<szVersion>"

//connect instances
#define TCOMSERVER_IGRP_REGISTEROBJ					0x00000010

//query object map
#define TCOMSERVER_IGRP_LOOKUPOBJ					0x00000020

#define TCOMSERVER_IGRP_INIT							0x00000030
#define TCOMSERVER_IGRP_INIT_MULTI					0x00000031

#define TCOMSERVER_IGRP_DELOBJ						0x00000040
#define TCOMSERVER_IGRP_DELOBJ_ARCHIVE				0x00000041

#define TCOMSERVER_IGRP_SETALLOBJ_SAFEOP			0x00000050

#define TCOMSERVER_IGRP_INTERFACE_METHODS			0x00000060

#define TCOMSERVER_IGRP_GET_RESULT_SIZE_DATA		0x00000070	// w: TComAdsGetDataReq; r: TComAdsGetDataRes + data 

#define TCOMSERVER_IGRP_SETOBJSTATE					0x00000100
#define TCOMSERVER_IOFFS_SETOBJSTATE_ONLY_UP			0x00000001
#define TCOMSERVER_IOFFS_SETOBJSTATE_ONLY_DOWN		0x00000002
#define TCOMSERVER_IGRP_GETOBJSTATE					0x00000101
#define TCOMSERVER_IGRP_SETOBJSTATEFORWARD		0x00000102
#define TCOMSERVER_IGRP_SETOBJSTATES_OP			0x00000103
#define TCOMSERVER_IGRP_SETOBJSTATES_SAFEOP		0x00000104
#define TCOMSERVER_IGRP_SETOBJSTATES_OP_WIN		0x00000105

#define TCOMSERVER_IGRP_GETOBJLIST					0x00000110
#define TCOMSERVER_IGRP_GETOBJLIST_CLASSNAME		0x00000111
#define TCOMSERVER_IGRP_OBJIDS_FROM_CATEGORY		0x00000112	// indexOffs==0: ID-List, indexOffs==1: count of IDs

#define TCOMSERVER_IGRP_WINDOWSCALLBACK			0x00000120
#define TCOMSERVER_IGRP_REALTIMECALLBACK			0x00000121
#define TCOMSERVER_IGRP_WINDOWSCALLBACK2			0x00000122
#define TCOMSERVER_IGRP_REALTIMECALLBACK2			0x00000123

#define TCOMSERVER_IGRP_CFGMODE_OBJS				0x00000130
#define TCOMSERVER_IOFFS_CFGMODE_SET_OBJS				0x00000001
#define TCOMSERVER_IOFFS_CFGMODE_ADD_OBJS				0x00000002
#define TCOMSERVER_IOFFS_CFGMODE_DEL_OBJS				0x00000003
#define TCOMSERVER_IOFFS_CFGMODE_DEL_OBJS_SI			0x00000004
#define TCOMSERVER_IOFFS_CFGMODE_OBJS_SET_OS			0x00000005

#define TCOMSERVER_IGRP_DBGINFO_CLSID_LIST		0x00000200
#define TCOMSERVER_IGRP_DBGINFO_OID_LIST			0x00000201
#define TCOMSERVER_IGRP_DBGINFO_OBJECT				0x00000202
#define TCOMSERVER_IGRP_DBGINFO_CLASS				0x00000203

#define TCOMSERVER_IOFFS_DBGINFO_DEFAULT				0x00000000
#define TCOMSERVER_IOFFS_DBGINFO_LENGTH				0x00000001
#define TCOMSERVER_IOFFS_DBGINFO_VALUES				0x00000002

// TwinCAT XAE Debugger

#define TCOMSERVER_IGRP_CREATEDEBUGGERINSTANCE	0x00000200

#define TCOM_MAKE_CLASS_NAME(SrvName,ClassName) SrvName "!" ClassName
#ifdef WIN32_RUNTIME
#define TCDBG_UNIT_IMAGE_NAME(SrvName) SrvName "W32.dll"
#elif defined (_ARM_)
#define TCDBG_UNIT_IMAGE_NAME(SrvName) SrvName ".dll"
#elif defined (TC_ENVIRONMENT_OS)
#define TCDBG_UNIT_IMAGE_NAME(SrvName) SrvName ".tmx"
#else
#define TCDBG_UNIT_IMAGE_NAME(SrvName) SrvName ".sys"
#endif
#ifdef WIN32_RUNTIME
#define TCDBG_UNIT_IMAGE_NAME_TMX(SrvName) SrvName "W32.tmx"
#else
#define TCDBG_UNIT_IMAGE_NAME_TMX(SrvName) SrvName ".tmx"
#endif
#define TCDBG_UNIT_VERSION(SrvName) SrvName ## _FileVersionMajor, SrvName ## _FileVersionMinor, SrvName ## _FileVersionBuild, SrvName ## _FileVersionRevision

#ifndef ECAT_DCTIME_TO_SYSTIME_FACTOR
const	unsigned __int64	ECAT_DCSTARTIME_IN_SYSTEMTIME		= 0x01bf53eb256d4000;	// 100 ns between 1.1.1601 and 1.1.2000
const	unsigned __int64	ECAT_PTPSTARTIME_IN_SYSTEMTIME	= 0x019db1ded53e8000;	// 100 ns between 1.1.1601 and 1.1.1970
const	unsigned long		ECAT_DCSTARTIME_IN_PTPTIME			= 0x386D4380;				// s between 1.1.1970 and 1.1.2000
#define	ECAT_DCTIME_TO_SYSTIME_FACTOR							100
#define	ECAT_DCTIME_TO_PTPHIGHTIME_FACTOR					1000000000
#define	DCTIME_TO_SEC_FACTOR										1000000000
#define	DCTIME_TO_MSEC_FACTOR									1000000
#define	DCTIME_TO_USEC_FACTOR									1000
#define	DCTIME_TO_SEC_FACTOR_FP									1000000000.0
#define	DCTIME_TO_MSEC_FACTOR_FP								1000000.0
#define	DCTIME_TO_USEC_FACTOR_FP								1000.0
#define	ECAT_SYSTIME_TO_DCTIME_64(s)		(((s)-ECAT_DCSTARTIME_IN_SYSTEMTIME)*ECAT_DCTIME_TO_SYSTIME_FACTOR)
#define	ECAT_SYSTIME_TO_DCTIME_32(s)		((ULONG)ECAT_SYSTIME_TO_DCTIME_64(s))
#define	ECAT_DCTIME_TO_SYSTIME_64(d)		(((d)/ECAT_DCTIME_TO_SYSTIME_FACTOR)+ECAT_DCSTARTIME_IN_SYSTEMTIME)
#define	ECAT_DCTIME_TO_SYSTIME_32(d)		((ULONG)ECAT_DCTIME_TO_SYSTIME_64(d))
#define	ECAT_SYSBASE_TO_DCBASE(s)			((s)*ECAT_DCTIME_TO_SYSTIME_FACTOR)
#define	ECAT_DCBASE_TO_SYSBASE(d)			((d)/ECAT_DCTIME_TO_SYSTIME_FACTOR)
#define	ECAT_PTPTIME_TO_DCTIME_64(s,n)	((n) + (ECAT_DCTIME_TO_PTPHIGHTIME_FACTOR*((s)-ECAT_DCSTARTIME_IN_PTPTIME))
#define	ECAT_PTPTIME_TO_DCTIME_32(s,n)	((ULONG)ECAT_PTPTIME_TO_DCTIME_64(s,n))
#define	ECAT_DCTIME_TO_PTPHIGHTIME(d)		((ULONG)(ECAT_DCSTARTIME_IN_PTPTIME + ((d)/ECAT_DCTIME_TO_PTPHIGHTIME_FACTOR)))
#define	ECAT_DCTIME_TO_PTPLOWTIME(d)		((ULONG)((d)-((d)/ECAT_DCTIME_TO_PTPHIGHTIME_FACTOR)*ECAT_DCTIME_TO_PTPHIGHTIME_FACTOR))
#endif

inline ULONGLONG	ExtendDcTimeTo64Bit(ULONG dcTime, ULONGLONG global) 
{ 
	if ( (dcTime - (ULONG)(global)) >= 0x80000000 )	{  
		if ( dcTime >= 0x80000000 ) 
			((PULONG)&global)[1]--; 
		else	
			((PULONG)&global)[1]++;		
	}										
	*(PULONG)&global = dcTime;	 
	return global; 
}

#if defined(IS_R0) && !defined(IS_CE)
const		GUID		GUID_NULL = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };
#endif

#if defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

#ifndef TCFRAMEWORK_EXTERN_IID_DEFINITION
#define	TCOM_DECL_CLASS(CID, ID)	\
extern	const		CTCID		CID;
#define	TCOM_DECL_GUID(GID, ID)	\
extern const		GUID		GID = ID;
#else
#define	TCOM_DECL_CLASS(CID, ID)	\
extern	const		CTCID		CID = TCOM_MAKE_CLASSID(ID);
#define	TCOM_DECL_GUID(GID, ID)	\
extern const		GUID		GID = ID;
#endif

extern const		GUID		GUID_TComFncId;
extern const		GUID		GUID_TComItfId;
extern const		GUID		GUID_TComClassId;

#else	// defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

#define	TCOM_DECL_CLASS(CID, ID)	\
const		CTCID		CID = TCOM_MAKE_CLASSID(ID);

#define	TCOM_DECL_GUID(GID, ID)	\
const		GUID		GID = (GUID)(ID);

const		GUID		GUID_TComFncId = { 0, 0, 0,{ 0xd0, 0, 0, 0, 0, 0, 0, 0x64 } };
const		GUID		GUID_TComItfId = { 0, 0, 0,{ 0xe0, 0, 0, 0, 0, 0, 0, 0x64 } };
const		GUID		GUID_TComClassId = { 0, 0, 0,{ 0xf0, 0, 0, 0, 0, 0, 0, 0x64 } };

#endif // defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

inline	GUID		TCOM_MAKE_FNCID(ULONG sig, ULONG ver) 
{
	GUID g;
	g.Data1 = sig;
	memcpy(&g.Data2, &ver, sizeof(ver));
	memcpy(&g.Data4, &GUID_TComFncId, sizeof(g.Data4));
	return g;
}
inline	GUID		TCOM_MAKE_CLASSID(ULONG n) 
{
	GUID g;
	g.Data1 = n;
	memcpy(&g.Data2, &GUID_TComClassId.Data2, 12);
	return g;
}
#define	CTCID_NULL	GUID_NULL
#define	ITCID_NULL	GUID_NULL


#define		TCOMINITDATAELM_IOFFS_OPTIONAL			0x00008000

///////////////////////////////////////////////////////////////////////////////
// Interface IDs
TCOM_DECL_INTERFACE("00000002-0000-0000-e000-000000000064", ITcPersist)
TCOM_DECL_INTERFACE("00000003-0000-0000-e000-000000000064", ITcAlloc)
TCOM_DECL_INTERFACE("00000010-0000-0000-e000-000000000064", ITComAdmin)
TCOM_DECL_INTERFACE("00000011-0000-0000-e000-000000000064", ITComServer)
TCOM_DECL_INTERFACE("00000012-0000-0000-e000-000000000064", ITComObject)
TCOM_DECL_INTERFACE("00000013-0000-0000-e000-000000000064", ITComObjInd)
TCOM_DECL_INTERFACE("00000014-0000-0000-e000-000000000064", ITComObjRes)
TCOM_DECL_INTERFACE("00000015-0000-0000-e000-000000000064", ITComObjReq)
TCOM_DECL_INTERFACE("00000016-0000-0000-e000-000000000064", ITComObjCon)
TCOM_DECL_INTERFACE("00000017-0000-0000-e000-000000000064", ITComObjFrw)
TCOM_DECL_INTERFACE("00000018-0000-0000-e000-000000000064", ITcClassFactory)
TCOM_DECL_INTERFACE("00000021-0000-0000-e000-000000000064", ITcDispatch)
TCOM_DECL_INTERFACE("00000022-0000-0000-e000-000000000064", ITComObjectParent)
TCOM_DECL_INTERFACE("00000023-0000-0000-e000-000000000064", ITComObjectChild)
TCOM_DECL_INTERFACE("00000030-0000-0000-e000-000000000064", ITComObjectServer)
TCOM_DECL_INTERFACE("00000031-0000-0000-e000-000000000064", ITComCreateInstance)
TCOM_DECL_INTERFACE("00000033-0000-0000-e000-000000000064", ITComBaseServices)
TCOM_DECL_INTERFACE("00000034-0000-0000-e000-000000000064", ITComTimer)
TCOM_DECL_INTERFACE("00000035-0000-0000-e000-000000000064", ITComTimerConsumer)
TCOM_DECL_INTERFACE("00000036-0000-0000-e000-000000000064", ITcConfigModeFreerun)
TCOM_DECL_INTERFACE("00000037-0000-0000-e000-000000000064", ITComSystemInstance)
TCOM_DECL_INTERFACE("00000038-0000-0000-e000-000000000064", ITComObjectCategory)
TCOM_DECL_INTERFACE("00000039-0000-0000-e000-000000000064", ITComEnumTCID)
TCOM_DECL_INTERFACE("0000003a-0000-0000-e000-000000000064", ITComObjectEnum)
TCOM_DECL_INTERFACE("0000003b-0000-0000-e000-000000000064", ITComReportEvent)
TCOM_DECL_INTERFACE("0000003c-0000-0000-e000-000000000064", ITcDrvLdr)
TCOM_DECL_INTERFACE("0000003d-0000-0000-e000-000000000064", ITcLoader3)
TCOM_DECL_INTERFACE("0000003e-0000-0000-e000-000000000064", ITcLoader)
TCOM_DECL_INTERFACE("0000003f-0000-0000-e000-000000000064", ITcLoader2)
TCOM_DECL_INTERFACE("24D6E22E-77E0-457B-A6DE-774CB0B177E9", ITcOsFileLoader)
TCOM_DECL_INTERFACE("00000040-0000-0000-e000-000000000064", ITcObjParaAsyncRes)
TCOM_DECL_INTERFACE("00000041-0000-0000-e000-000000000064", ITcObjParaAsync)
TCOM_DECL_INTERFACE("00000042-0000-0000-e000-000000000064", ITcDynPoolObject)
TCOM_DECL_INTERFACE("00000043-0000-0000-e000-000000000064", ITcDynPoolManager)
TCOM_DECL_INTERFACE("00000044-0000-0000-e000-000000000064", ITComCallbackClient)
TCOM_DECL_INTERFACE("00000045-0000-0000-e000-000000000064", ITComCallbackServer)
TCOM_DECL_INTERFACE("00000046-0000-0000-e000-000000000064", ITcBaseClassFactory)
TCOM_DECL_INTERFACE("00000047-0000-0000-e000-000000000064", ITcLockable)
TCOM_DECL_INTERFACE("00000048-0000-0000-e000-000000000064", ITcDynMemManager) 
TCOM_DECL_INTERFACE("00000049-0000-0000-e000-000000000064", ITComArchiveServer)
#ifndef POSIX
TCOM_DECL_INTERFACE("0000004a-0000-0000-e000-000000000064", ITcAdsHelper)
#endif
TCOM_DECL_INTERFACE("0000004b-0000-0000-e000-000000000064", ITComObjArchiveServer)
TCOM_DECL_INTERFACE("0000004c-0000-0000-e000-000000000064", ITComArchive)
TCOM_DECL_INTERFACE("0000004d-0000-0000-e000-000000000064", ITComArchiveOp)
TCOM_DECL_INTERFACE("0000004e-0000-0000-e000-000000000064", ITcErrorLogger)
TCOM_DECL_INTERFACE("0000004f-0000-0000-e000-000000000064", ITcRtClassFactory)
TCOM_DECL_INTERFACE("00000050-0000-0000-e000-000000000064", ITComCallbackServer2)
TCOM_DECL_INTERFACE("00000051-0000-0000-e000-000000000064", ITComADSConFilter)
TCOM_DECL_INTERFACE("00000052-0000-0000-e000-000000000064", ITComAmsMem)
TCOM_DECL_INTERFACE("00000053-0000-0000-e000-000000000064", ITComAdsLog)
TCOM_DECL_INTERFACE("00000054-0000-0000-e000-000000000064", ITComAmsTaskPort)
TCOM_DECL_INTERFACE("00000055-0000-0000-e000-000000000064", ITComFuncProvider)
TCOM_DECL_INTERFACE("00000056-0000-0000-e000-000000000064", ITComFuncServer)
TCOM_DECL_INTERFACE("00000057-0000-0000-e000-000000000064", ITComAmsMemEx)
TCOM_DECL_INTERFACE("00000058-0000-0000-e000-000000000064", ITcObjPara)
TCOM_DECL_INTERFACE("00000059-0000-0000-e000-000000000064", ITcRtAdsPort)
TCOM_DECL_INTERFACE("0000005A-0000-0000-e000-000000000064", ITcRtAdsUser)
#ifdef TCOM_REPOSITORY
TCOM_DECL_INTERFACE("0000005B-0000-0000-e000-000000000064", ITcLoadRepositoryDriver)
TCOM_DECL_INTERFACE("FC7FAA09-B9D5-408B-BC6F-3ACCF467DF14", ITcLockRepositoryDriver)
#endif
TCOM_DECL_INTERFACE("0000005C-0000-0000-e000-000000000064", ITComArchiveStream)
TCOM_DECL_INTERFACE("FAD29836-5A73-4AB5-9E60-6ED7A986BDA6", ITComArchiveStream2)
TCOM_DECL_INTERFACE("0000005D-0000-0000-e000-000000000064", ITComContextCallbackServer)
TCOM_DECL_INTERFACE("0000005E-0000-0000-e000-000000000064", ITComEnsureOpState)
TCOM_DECL_INTERFACE("0000005F-0000-0000-e000-000000000064", ITcLoader4)

TCOM_DECL_INTERFACE("00000060-0000-0000-e000-000000000064", ITcDbgUnit)
TCOM_DECL_INTERFACE("00000060-0001-0000-e000-000000000064", ITcDbgUnitVersion)
TCOM_DECL_INTERFACE("4CDC89D5-3DB4-4035-8098-A31DD6120075", ITcDbgUnitFlags)
TCOM_DECL_INTERFACE("00000061-0000-0000-e000-000000000064", ITcDbgInformation)
TCOM_DECL_INTERFACE("00000061-0001-0000-e000-000000000064", ITcDbgInformation2)
TCOM_DECL_INTERFACE("00000062-0000-0000-e000-000000000064", ITComInterfaceDescServer)
TCOM_DECL_INTERFACE("00000063-0000-0000-e000-000000000064", ITComNoPlcWrapper)
TCOM_DECL_INTERFACE("00000064-0000-0000-e000-000000000064", ITComObjArchiveServer2)
TCOM_DECL_INTERFACE("00000065-0000-0000-e000-000000000064", ITcData)

#ifdef TCTMCHANDLER_SUPPORT
TCOM_DECL_INTERFACE("D28A8CD2-5477-4B75-AF0F-998841AF9E44", ITComOnlineChange)
#endif

TCOM_DECL_INTERFACE("3196D3F8-CBAF-478F-AF33-A989318D064B", ITcModuleLibraryHandler)

#ifdef	ADS_EXTERNALTIME_PROVIDER
TCOM_DECL_INTERFACE("00000066-0000-0000-e000-000000000064", ITcExternalTime)
TCOM_DECL_INTERFACE("00000067-0000-0000-e000-000000000064", ITcSetExternalTime)
#endif
TCOM_DECL_INTERFACE("00000068-0000-0000-e000-000000000064", ITComObjArchiveServer3)
TCOM_DECL_INTERFACE("00000069-0000-0000-e000-000000000064", ITcDbgInformationOC)
TCOM_DECL_INTERFACE("D3E324B1-1B20-4439-B9FD-DEEFD5F940F1", ITcVersionProvider)

TCOM_DECL_INTERFACE("08500105-0000-0000-e000-000000000064", ITcAdsInvoker)
TCOM_DECL_INTERFACE("BB005065-BAA3-485D-8671-60444AEC00AB", ITcAdsInvoker2)

// Event IDs 
const		UINT		EVTID_TcDbgUnitAdded				= 0x00000101; 
const		UINT		EVTID_TcDbgUnitEnumerate		= 0x00000102; 
const		UINT		EVTID_TcDbgUnitRemoved			= 0x00000103; 
const		UINT		EVTID_TcDbgTaskCreate			= 0x00000110; 
const		UINT		EVTID_TcDbgTaskDelete			= 0x00000111; 
const		UINT		EVTID_TcDbgTaskSuspend			= 0x00000112; 
const		UINT		EVTID_TcDbgTaskResume			= 0x00000113; 
const		UINT		EVTID_TcDbgTaskEnumerate		= 0x00000114; 


// Class IDs
const		OTCID		OTCID_CreateNewId				= 0xffffffff;
const		OTCID		OTCID_FirstFreeId				= 0x71010000;
const		OTCID		OTCID_LastFreeId				= 0x710fffff;

const		PTCID		PID_TComObjName				= 0x00000101;
const		PTCID		PID_TComObjClassId			= 0x00000102;
const		PTCID		PID_TComObjParentId			= 0x00000103;
const		PTCID		PID_TComObjState				= 0x00000104;
const		PTCID		PID_TComObjRefCount			= 0x00000105;
const		PTCID		PID_DownloadInitSymbols		= 0x00000107;
const		PTCID		PID_TComEventGuid				= TCOMINITDATAELM_IOFFS_OPTIONAL|0x00000108;
const		PTCID		PID_SymbolPortNo				= 0x00000109;
const		PTCID		PID_AdsVersion					= 0x0000010A;
const		PTCID		PID_FlexibleSymbolInfo		= 0x0000010B;	// PAdsSymbolUpAndDownloadHeader2 data
#ifdef	ADS_EXTERNALTIME_PROVIDER
const		PTCID		PID_ExternalTimeType			= 0x0000010C;	// ITcExternalTime::TimeType
#endif

const		PTCID		PID_TComObjSumupRead			= 0x00000151;
																	// W: {list of PID, Length} 
																	// R: {list of HRESULT, Length, Data[]} 
const		PTCID		PID_TComObjSumupWrite		= 0x00000152;
																	// W: {list of PID, Length, Data[]} 
																	// R: {list of HRESULT} 

///////////////////////////////////////////////////////////////////////////////

typedef struct {
	ULONG major;
	ULONG minor;
	ULONG build;
	ULONG revision;
} T_Version, *PT_Version, DbgUnitVersion, *PDbgUnitVersion;

///////////////////////////////////////////////////////////////////////////////

enum TcTraceLevel
{
	tlAlways,
	tlError,
	tlWarning,
	tlInfo,
	tlVerbose
};

// AMS cmds
#define	AMSCMD_ALLOCFREEMEM		(8 + 0x5000)
#define	AMSCMD_ALLOCFREEMEMEX	(8 + 0x5001)

///////////////////////////////////////////////////////////////////////////////
#pragma pack( push, 1 )	// all structures should be naturally aligned!

///////////////////////////////////////////////////////////////////////////////
static const	CHAR*	TCOM_STATE_TEXT[] = {"", "INIT", "PREOP", "", "SAFEOP", "", "", "", "OP"};

typedef enum ETCOM_STATE
{
	TCOM_STATE_INVALID		= 0,
	TCOM_STATE_INIT			= 1,
	TCOM_STATE_PREOP			= 2,
	TCOM_STATE_SAFEOP			= 4,
	TCOM_STATE_OP				= 8,
} TCOM_STATE, *PTCOM_STATE;

typedef enum ETCOMSTATE_TRANS
{
	TCOM_STATE_TRANS_I_P		= 1,
	TCOM_STATE_TRANS_P_S		= 2,
	TCOM_STATE_TRANS_S_O		= 4,
	TCOM_STATE_TRANS_O_S		= 8,
	TCOM_STATE_TRANS_S_P		= 16,
	TCOM_STATE_TRANS_P_I		= 32,
} TCOM_STATE_TRANS, *PTCOM_STATE_TRANS;

typedef struct T_TComInitDataElmHdr
{
	UINT		indexGroup;
	UINT		indexOffset;
	UINT		cbData;
}TComInitDataElmHdr, *PTComInitDataElmHdr;
#define PTComInitDataElmHdrDATA(p)					((PVOID)((PTComInitDataElmHdr)p + 1))
#define PTComInitDataElmHdrSETDATA(p, t, v)		(*((t*)((PTComInitDataElmHdr)p + 1)) = (v))
#ifndef TCOMINITDATA_ALIGNED
#define PTComInitDataElmHdrNEXTHDR(p)	((PTComInitDataElmHdr)(((PBYTE)((PTComInitDataElmHdr)p + 1)) + ((PTComInitDataElmHdr)p)->cbData ))
#define PTComInitDataElmSIZE(n)			(sizeof(TComInitDataElmHdr) + (n))
#define PTComInitDataElmHdrINIT(pI, pE, cb, ig, io) \
((PTComInitDataElmHdr)(((PBYTE)((PTComInitDataElmHdr)pE + 1)) + ((PTComInitDataElmHdr)pE)->cbData )); \
{pI->uiElmCnt++; \
pI->cbData += (PTComInitDataElmSIZE(cb)); \
pE->cbData = cb; \
pE->indexGroup = ig; \
pE->indexOffset = io;}
#else
#define TCOMINITDATA_ALIGN(n)				(4*(((n)+3)/4))
#define PTComInitDataElmHdrNEXTHDR(p)	((PTComInitDataElmHdr)(((PBYTE)((PTComInitDataElmHdr)p + 1)) + TCOMINITDATA_ALIGN(((PTComInitDataElmHdr)p)->cbData) ))
#define PTComInitDataElmSIZE(n)			(sizeof(TComInitDataElmHdr) + TCOMINITDATA_ALIGN(n))
#define PTComInitDataElmHdrINIT(pI, pE, cb, ig, io) \
((PTComInitDataElmHdr)(((PBYTE)((PTComInitDataElmHdr)pE + 1)) + TCOMINITDATA_ALIGN(((PTComInitDataElmHdr)pE)->cbData) )); \
{pI->uiElmCnt++; \
pI->cbData += (PTComInitDataElmSIZE(cb)); \
pE->cbData = cb; \
pE->indexGroup = ig; \
pE->indexOffset = io;}
#endif

typedef struct T_TComInitDataHdr
{
	UINT		cbData;
	USHORT	uiElmCnt;
	USHORT	reserved1;
	UINT		reserved2;
}TComInitDataHdr, *PTComInitDataHdr;
#define PTComInitDataHdrNEXTHDR(p)	((PTComInitDataElmHdr)((PTComInitDataHdr)p + 1))
#define PTComInitDataHdrSIZEOF(p)	(sizeof(TComInitDataHdr) + ((PTComInitDataHdr)p)->cbData)
#define PTComInitDataHdrINIT(pD, pI, cb, ig, io)	\
((PTComInitDataElmHdr)((PTComInitDataHdr)pI + 1)); \
{ pI->cbData	= pD->cbInitData - sizeof(TComInitDataHdr); pI->uiElmCnt = 1; \
((PTComInitDataElmHdr)((PTComInitDataHdr)pI + 1))->cbData = cb; \
((PTComInitDataElmHdr)((PTComInitDataHdr)pI + 1))->indexGroup = ig; \
((PTComInitDataElmHdr)((PTComInitDataHdr)pI + 1))->indexOffset = io;}

typedef struct T_TComAdsCreateInstance
{
	CTCID			clsid;
	OTCID			oid;
	OTCID			oidParent;
	TCOM_STATE	targetState;
	UINT			reserved[5];
	CHAR			name[128];
	UINT			cbInitData;
}TComAdsCreateInstance, *PTComAdsCreateInstance;
#define PTComAdsCreateInstanceDATA(p)		((PTComInitDataHdr)((PTComAdsCreateInstance)p + 1))
#define PTComAdsCreateInstanceNEXTHDR(p)	((PTComAdsCreateInstance)((PBYTE)p + sizeof(TComAdsCreateInstance) + ((PTComAdsCreateInstance)p)->cbInitData))
#define PTComAdsCreateInstanceINIT(P, SIZE, CLSID, OID, OIDPARENT, NAME, TARGETSTATE)		\
	((PTComInitDataHdr)((PTComAdsCreateInstance)P + 1)); \
	{ memset(P, 0, SIZE); \
	P->clsid = CLSID; \
	P->oid	= OID; \
	P->oidParent = OIDPARENT; \
	strncpy(P->name, NAME, sizeof(P->name)); \
	P->name[sizeof(P->name)-1] = 0; \
	P->targetState = TARGETSTATE; \
	P->cbInitData = SIZE - sizeof(TComAdsCreateInstance);}

typedef struct T_TComAdsSetState
{
	OTCID			oid;
	UINT			state;
	UINT			cbData;
}TComAdsSetState, *PTComAdsSetState;
#define PTComAdsSetStateNEXTHDR(p)	((PTComAdsSetState)((PTComAdsSetState) + 1 ))

#ifdef TCOMADSCREATEINSTANCELEGACY
typedef struct T_TComAdsObjectDataLEGACY
{
	OTCID			oid;
	CTCID			clsid;
	ULONG			refCnt;
	TCOM_STATE		state;
	ULONG			timeStamp;
	CHAR			name[32];
}TComAdsObjectDataLEGACY, *PTComAdsObjectDataLEGACY;
#endif
typedef struct T_TComAdsObjectData
{
	CTCID			clsid;
	OTCID			oid;
	OTCID			oidParent;
	ULONG			refCnt;
	TCOM_STATE	state;
	ULONG			timeStamp;
	OTCID			oidIoCaller;
	OTCID			oidCaller;
	OTCID			oidAdi;
	CHAR			name[128];
}TComAdsObjectData, *PTComAdsObjectData;


// TCOMSERVER_IGRP_GET_RESULT_SIZE_DATA
typedef struct T_TComAdsGetDataReq
{
	OTCID			oid;
	PTCID			pid;
}TComAdsGetDataReq, *PTComAdsGetDataReq;

typedef struct T_TComAdsGetDataRes
{
	ULONG			result;
	ULONG			cbLength;
}TComAdsGetDataRes, *PTComAdsGetDataRes;



// This structure provides space for 32 bit and for 64 bit 
// pointers. The field Ptr provides platform independent access
// to the pointer, i.e. it represents a 32 bit value if compiled for
// 32 bit platforms or a 64 bit pointer for 64 bit platforms.
// Explicit use of Ptr32 or Ptr64 should not be necessary.
typedef struct T_TComAdsObjectAddress
{
	union
	{
		ULONG_PTR Ptr;
		ULONG32 Ptr32; 
		ULONG64 Ptr64; 
	};
} TComAdsObjectAddress, *PTComAdsObjectAddress;

///////////////////////////////////////////////////////////////////////////////
// TCOMSERVER_IGRP_DBGINFO_OBJECT
// 
// Debug information for objects managed by TComObjectServer.
// 
// Request
typedef struct T_TComAdsDbgInfoObjectReq
{
	OTCID						oid; 
} TComAdsDbgInfoObjectReq, *PTComAdsDbgInfoObjectReq;

// Response
// Note for strings:
// Strings of variable length are appended at the end of the structure. The 
// Strings are guranteed to be terminated with at least one '\0' character. The
// number of bytes indicated for each string includes also all the terminating '\0'.
// It might be necessary to have more than one '\0' for proper aligment. 
// The data structures reserves space to indicate the number of bytes for 4
// additional strings in field reserved2. 
// 
// nLength - Number of bytes for the entire structure
// oid - object id
// clsid - class id
// ipInterface - Interface pointer of type indicated in szInterfaceName
// reserved1 - room for future extensions
// nObjectName - number of bytes of object name string including the terminating '\0'
// nInterfaceName - number of bytes of interface name string including the terminating '\0'
// reserved2 - room for future extensions
typedef struct T_TComAdsDbgInfoObjectRes
{
	ULONG						nLength;
	OTCID						oid;
	OTCID						oidParent;
	CTCID						clsid;
	TComAdsObjectAddress	ipInterface;
	ULONG						reserved1[4];
	ULONG						nObjectName;
	ULONG						nInterfaceName;
	ULONG						reserved2[4];
	//CHAR					szObjectName[];
	//CHAR					szInterfaceName[];
} TComAdsDbgInfoObjectRes, *PTComAdsDbgInfoObjectRes;

// compute field lengths for strings w.r.t. terminating '\0' and alignment
#define TCOM_DBGINFO_STRFIELD_SIZEOF(STR) TCOMINITDATA_ALIGN(strlen(STR)+1)

#define TComAdsDbgInfoObjectResLENGTH(OBJECTNAMESTR, INTERFACENAMESTR)	\
	(\
		sizeof(TComAdsDbgInfoObjectRes) + \
		TCOM_DBGINFO_STRFIELD_SIZEOF(OBJECTNAMESTR) + \
		TCOM_DBGINFO_STRFIELD_SIZEOF(INTERFACENAMESTR) \
	)

// initialize PTComAdsDbgInfoObjectRes 
#define PTComAdsDbgInfoObjectResINIT(P, SIZE, CLSID, OID, OIDPARENT, PTR, OBJECTNAMESTR, INTERFACENAMESTR)	\
	{ \
		memset(P, 0, SIZE); \
		(P)->nLength=(ULONG)SIZE; \
		(P)->oid	= OID; \
		(P)->oidParent = OIDPARENT; \
		(P)->clsid = CLSID; \
		(P)->ipInterface.Ptr = PTR; \
		(P)->nObjectName = (ULONG)TCOM_DBGINFO_STRFIELD_SIZEOF(OBJECTNAMESTR); \
		(P)->nInterfaceName = (ULONG)TCOM_DBGINFO_STRFIELD_SIZEOF(INTERFACENAMESTR); \
		strcpy((PCHAR)P+sizeof(*(P)), OBJECTNAMESTR); \
		strcpy((PCHAR)P+sizeof(*(P))+(P)->nObjectName, INTERFACENAMESTR); \
	}

///////////////////////////////////////////////////////////////////////////////
struct TComInitSymbolDataEntry
{
	ULONG		entryLength;
	ULONG		dataSize;
	USHORT	nameLength;
	USHORT	lastEntry	: 1;
	USHORT	typeGuid		: 1;
	USHORT	reserved		: 14;
	// CHAR		name[]
	// BYTE		data[]
	// GUID		typeGuid;
};
typedef TComInitSymbolDataEntry *PTComInitSymbolDataEntry;
#ifndef	ROUNDUPBYTE2DWORD
#define	ROUNDUPBYTE2DWORD(x)	(4*(((x)+3)/4))
#endif
#define	PTCOMINITSYMBOLDATAENTRYNAME(p)			((PCHAR)(((PTComInitSymbolDataEntry)p)+1))
#define	PTCOMINITSYMBOLDATAENTRYDATA(p)			(((PBYTE)(((PTComInitSymbolDataEntry)p)+1))+ROUNDUPBYTE2DWORD((p)->nameLength+1))
#define	PTCOMINITSYMBOLDATAENTRYTYPE(p)			((GUID*)(((PBYTE)(((PTComInitSymbolDataEntry)p)+1))+ROUNDUPBYTE2DWORD((p)->nameLength+1)+ROUNDUPBYTE2DWORD((p)->dataSize)))
#define	PTCOMINITSYMBOLDATAENTRYNEXT(p)			(((PTComInitSymbolDataEntry)(p->lastEntry ? NULL : (((PBYTE)p)+(p)->entryLength))))

///////////////////////////////////////////////////////////////////////////////
// TCOMSERVER_IGRP_DBGINFO_CLASS
//
// Debug information for class ids managed by TComObjectServer.
// 
// Request
typedef struct T_TComAdsDbgInfoClassReq
{
	CTCID						clsid; 
} TComAdsDbgInfoClassReq, *PTComAdsDbgInfoClassReq;

// Response
// See also 'Note for strings' in data structure TComAdsDbgInfoObjectRes
// 
// nLength - Number of bytes for the entire structure
// clsid - class id
// reserved - room for future extensions
// nClassName - number of bytes of class name string excluding the terminating '\0'
// 
typedef struct T_TComAdsDbgInfoClassRes
{
	ULONG						nLength;
	CTCID						clsid; 
	DbgUnitVersion				version;
	ULONG						nClassName;
	ULONG						reserved2[4];
	//CHAR					szClassName[];
} TComAdsDbgInfoClassRes, *PTComAdsDbgInfoClassRes;

#define TComAdsDbgInfoClassResLENGTH(CLASSNAMESTR)	\
		(sizeof(TComAdsDbgInfoClassRes) + TCOM_DBGINFO_STRFIELD_SIZEOF(CLASSNAMESTR))

// initialize PTComAdsDbgInfoObjectRes 
#define PTComAdsDbgInfoClassResINIT(P, SIZE, CLSID, CLASSNAMESTR)	\
	{ \
		memset(P, 0, SIZE); \
		(P)->nLength = (ULONG)SIZE; \
		(P)->clsid = CLSID; \
		(P)->nClassName = (ULONG)TCOM_DBGINFO_STRFIELD_SIZEOF(CLASSNAMESTR); \
		strcpy((PCHAR)P+sizeof(*(P)), CLASSNAMESTR); \
	}


///////////////////////////////////////////////////////////////////////////////
// TCOMSERVER_IGRP_DBGINFO_OID_LIST
//
// List of object ids for a given clsid
// 
// Request
typedef struct T_TComAdsDbgInfoOidListReq
{
	CTCID						clsid; 
} TComAdsDbgInfoOidListReq, *PTComAdsDbgInfoOidListReq;

typedef struct
{
	AmsHead		head;
	BOOL			bAlloc;
	OTCID			oidCaller;

	union
	{
		ULONG		nSize;
		PVOID		pVoid;
	};
} AmsAllocFreeMem, *PAmsAllocFreeMem;
#define	SIZEOF_AmsAllocFreeMem(p)	( sizeof(AmsAllocFreeMem) )
#define	CBDATA_AmsAllocFreeMem(p)	( SIZEOF_AmsAllocFreeMem(p) - sizeof(AmsHead) )

typedef struct T_AmsPort_InitData
{
	AMSPORT_TYPE	type;
	DWORD				dwAttrib;
	AmsPortNo		port;
	USHORT			nameLen;
	UINT				reserved;
//	CHAR				szPortName[nameLen]
}AmsPort_InitData, *PAmsPort_InitData;

#define PAmsPort_InitData_Name(p) ((PCHAR)((PAmsPort_InitData)p + 1))
#define PAmsPort_InitData_NextHdr(p) ((PVOID)((PBYTE)((PAmsPort_InitData)p + 1) + ((PAmsPort_InitData)p)->nameLen + (sizeof(AmsPort_InitData) + ((PAmsPort_InitData)p)->nameLen) % 4) )

typedef struct T_TComInterfaceMethods
{
	ITCID	iid; 
	ULONG	cnt;
} TComInterfaceMethods, *PTComInterfaceMethods;

#pragma pack( pop )

class CDbgObjEntry
{
public:
	PVOID			m_pObj;
	PCHAR			m_pName;

	CDbgObjEntry()
	{
		m_pObj	= NULL;
		m_pName	= NULL;
	}
};

///////////////////////////////////////////////////////////////////////////////
#ifndef TCFRAMEWORK_IID
extern	const		BYTE		ITCID_Prefix[];
extern	const		BYTE		CTCID_Prefix[];
extern	const		BYTE		OTCID_Prefix[];
#else
extern	const		BYTE		ITCID_Prefix[] = { 0x11,0xf6,0xd8,0xdb,0x0e,0x94,0xd2,0x11,0xb6,0x5c,0x00,0xe0 };
extern	const		BYTE		CTCID_Prefix[] = { 0x11,0xf6,0xd8,0xdb,0x0e,0x94,0xd2,0x11,0xb6,0x5c,0x00,0xe1 };
extern	const		BYTE		OTCID_Prefix[] = { 0x11,0xf6,0xd8,0xdb,0x0e,0x94,0xd2,0x11,0xb6,0x5c,0x00,0xe2 };
#endif
///////////////////////////////////////////////////////////////////////////////
inline	HRESULT	OTCID2GUID( OTCID oid, GUID& guid )
{
	memcpy( &guid, OTCID_Prefix, 12 );
	*(ULONG*)&guid.Data4[4]	= oid;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
inline	HRESULT	GUID2OTCID( OTCID& oid, GUID guid )
{
#ifdef DEBUG
	if ( memcmp( &guid, OTCID_Prefix, 12 ) != 0 )
		return E_FAIL;
#endif
	oid = *(ULONG*)&guid.Data4[4];
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// TcDataAreaPid 
const PTCID TcDataAreaPidFlag				= 0x80000000;
const PTCID TcDataAreaPidBitTypeFlag	= 0x40000000;
const PTCID TcDataAreaPidMask				= TcDataAreaPidFlag|TcDataAreaPidBitTypeFlag;
const PTCID TcDataAreaPidOffsetMask		= 0x00ffffff;
const PTCID TcDataAreaPidAreaNoMask		= 0x3F000000;
const UINT  TcDataAreaOffsetMax			= 0x01000000;
const UINT  TcDataAreaSpanDefault		= 1;

inline HRESULT TcDataAreaPidCreateWithOffset(UINT areaNo, UINT areaSpan, ULONG nOffset, BOOL fBitOffset, PTCID& pid)
{
	HRESULT hr = S_OK;
	if (areaNo > (TcDataAreaPidAreaNoMask >> 24))
	{
		hr = ADS_E_INVALIDPARM;
	}
	else if (nOffset >= TcDataAreaOffsetMax*areaSpan)
	{
		hr = ADS_E_INVALIDOFFSET;
	}
	else if (areaSpan>TcDataAreaSpanDefault)
	{
		if (fBitOffset == TRUE)
		{
			// no bit access allowed for data areas with span 
			hr = ADS_E_INVALIDACCESS;
		}
		else
		{
			pid =
				TcDataAreaPidFlag
				| (fBitOffset ? TcDataAreaPidBitTypeFlag : 0)
				| (TcDataAreaPidAreaNoMask & (areaNo << 24))
				+ nOffset;
		}
	}
	else
	{
		pid =
			TcDataAreaPidFlag
			| (fBitOffset ? TcDataAreaPidBitTypeFlag : 0)
			| (TcDataAreaPidAreaNoMask & (areaNo << 24))
			| (TcDataAreaPidOffsetMask & nOffset);
	}
	return hr;
}


inline HRESULT TcDataAreaPidCreateWithOffset(UINT areaNo, ULONG nOffset, BOOL fBitOffset, PTCID& pid)
{
	return TcDataAreaPidCreateWithOffset(areaNo, TcDataAreaSpanDefault, nOffset, fBitOffset, pid);
}

inline HRESULT TcDataAreaPidCreateWithByteOffset(UINT areaNo, UINT areaSpan, ULONG byteOffset, PTCID& pid)
{
	return TcDataAreaPidCreateWithOffset(areaNo, areaSpan, byteOffset, FALSE, pid);
}

inline HRESULT TcDataAreaPidCreateWithByteOffset(UINT areaNo, ULONG byteOffset, PTCID& pid)
{
	return TcDataAreaPidCreateWithOffset(areaNo, byteOffset, FALSE, pid); 
}

inline HRESULT TcDataAreaPidCreateWithBitOffset(UINT areaNo, ULONG bitOffset, PTCID& pid)
{
	return TcDataAreaPidCreateWithOffset(areaNo, bitOffset, TRUE, pid);
}

inline HRESULT TcDataAreaPidCreateWithBitOffset64(UINT areaNo, ULONGLONG bitOffset, PTCID& pid)
{
	if (bitOffset>TcDataAreaPidOffsetMask)
		return ADS_E_INVALIDOFFSET;
	return TcDataAreaPidCreateWithOffset(areaNo, (ULONG)bitOffset, TRUE, pid);
}

inline BOOL TcDataAreaPidCheck(PTCID pid)
{
	return ( (pid & TcDataAreaPidFlag) != 0);
}

inline UINT TcDataAreaPidGetAreaNo(PTCID pid)
{
	return ((pid & TcDataAreaPidAreaNoMask) >> 24); 
}

inline BOOL TcDataAreaPidIsBitType(PTCID pid)
{
	return (pid & TcDataAreaPidBitTypeFlag) != 0;
}

inline ULONG TcDataAreaPidGetBitOffset(PTCID pid)
{
	return (pid & TcDataAreaPidOffsetMask) * ( TcDataAreaPidIsBitType(pid) ? 1 : 8); 
}

inline ULONG TcDataAreaPidGetByteOffset(PTCID pid)
{
	return TcDataAreaPidGetBitOffset(pid)/8;
}

inline BOOL TcDataAreaPidCheck(PTCID pid, UINT areaNo)
{
	return ((pid & TcDataAreaPidFlag) != 0) && (TcDataAreaPidGetAreaNo(pid) == areaNo); 
}

inline BOOL TcDataAreaPidCheck(PTCID pid, UINT areaNo, ULONG offset, ULONG size)
{
	ULONG pidBitOffset = TcDataAreaPidGetBitOffset(pid);
	ULONG bitOffset = offset*8;
	ULONG bitSize = size*8;
	return 
		   ((pid & TcDataAreaPidFlag) != 0) 
		&& (TcDataAreaPidGetAreaNo(pid) == areaNo) 
		&& pidBitOffset>=bitOffset
		&& pidBitOffset<(bitOffset+bitSize);
}

enum JsonType
{
	JsonType_NULL,
	JsonType_SINT,
	JsonType_USINT,
	JsonType_UINT,
	JsonType_INT,
	JsonType_UDINT,
	JsonType_DINT,
	JsonType_ULINT,
	JsonType_LINT,
	JsonType_REAL,
	JsonType_LREAL,
	JsonType_BOOL,
	JsonType_BIT,
	JsonType_STRING,
};
struct JsonInfo
{
	JsonInfo(JsonType t=JsonType_NULL, UINT s=0, UINT o = 0, UINT x = 0) : type(t), bitSize(s), bitOffs(o), textOffs(x) {};
	JsonType type;
	UINT		bitSize;
	UINT		bitOffs;
	UINT		textOffs;
};


#if !defined(_TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_)
#define _TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_
BEGIN_SCOPED_TYPED_ENUM(TcEventSeverity, SHORT)
{
	Verbose = 0,
	Info,
	Warning,
	Error,
	Critical,
};
END_SCOPED_TYPED_ENUM(TcEventSeverity, SHORT)
#endif // !defined(_TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_)

#if !defined(_TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_)
#define _TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_
struct TcEventEntry
{
	GUID uuidEventClass;
	ULONG nEventId;
	TcEventSeverity eSeverity;
};
#endif // !defined(_TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_)


const CTCID CID_TcTmlHandler = { 0x7e50ea1d,0x4c0f,0x491e,{0x90,0x82,0x98,0x22,0xfb,0xea,0x02,0x3d} }; // should this be moved to a dedicated "TmlHandlerServices.h" ?

BEGIN_SCOPED_ENUM(ETmlHandlerIntention)
{
	Check = 0,
		Initialize,
		Terminate
};
END_SCOPED_ENUM(ETmlHandlerIntention)

typedef void(*TcTmlFunctionPointer)(void*);
typedef void(**TcTmlFunctionPointerArray)(void*);

struct TcTmlVersionedLibraryFunction
{
	GUID FID;
	PCCH sName;
	TcTmlFunctionPointer pFct;
};

struct TcTmlVersionedLibraryFB
{
	GUID FB_ID;
	PCCH functionNames;
	TcTmlFunctionPointerArray pFcts;
};

struct TcTmlVersionedLibraryInfo
{
	GUID VID;
	TcTmlVersionedLibraryFunction* functions;
	TcTmlVersionedLibraryFB* functionBlocks;
	PCCH sLibraryId;
	PCCH sVersion;
	PCCH sName;
	PCCH sVendor;
};
