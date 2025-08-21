///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcIoInterfaces.h"
#include "TcRtServices.h"

#define	SYSTEM_MICROSECOND		10
#define	SYSTEM_MILLISECOND		10000
#define	SYSTEM_SECOND				10000000

#define TASKSTATE_UNDEFINED	0
#define TASKSTATE_CREATED		1
#define TASKSTATE_RUNNING		2
#define TASKSTATE_TERMINATING	3
#define TASKSTATE_ENDED			4
#define TASKSTATE_DELETED		5
#define TASKSTATE_SUSPENDED	6
#define TASKSTATE_WAITING		7

#define FACILITY_RTIME 0x1
#define STATUS_TCRTIME_WATCHDOG_TRIGGERED			((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0001)
#define STATUS_TCRTIME_DEADLOCK_DETECTED			((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0002)
#define STATUS_TCRTIME_GENERAL_PROTECTION_FAULT		((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0003)
#define STATUS_TCRTIME_DATA_BREAKPOINT				((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0004)
#define STATUS_TCRTIME_DEBUG_REGISTER_SECURITY_FLAG	((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0005)
#define STATUS_TCRTIME_INT3_BREAKPOINT              ((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0006)
#define STATUS_TCRTIME_TRAP_FLAG_BREAKPOINT         ((NTSTATUS)(0xE0000000L) | (FACILITY_RTIME)<<16 | 0x0007)

typedef DWORD		OSTICKS;					// type of time tick of the real-time OS
typedef BYTE		OSPRIO;
typedef PVOID		OSHDLTASK;				// task handle
typedef PVOID		OSHDLSEMA;				// semaphore handle
typedef PVOID		OSHDLMBOX;				// mailbox handle
typedef PVOID		OSHDLQUEUE;				// queue handle
typedef PVOID		OSMBOXITEM;				// type of a mailbox item
typedef PVOID		OSQITEM;					// type of a queue item
typedef PVOID		OSHDLCS;					// critical section handle
typedef PVOID		OSHDLBR;					// handle for barrier

#ifndef	OS_TIMEOUT
#define	OS_TIMEOUT 10
#endif

#define OSHDLTASK_CUR		((OSHDLTASK)0)
#define RTIME_PRIO_SELF		((OSHDLTASK) (ULONG_PTR)0xffffffff)
#define RTIME_NOWAIT			-1				// for peeking on sema's, mailboxes, queues
#define RTIME_ENDLESSWAIT	0				// wait endlessly on sema's, mailboxes, queues

#define RTIME_MAXTASKS		63

#ifdef _X64_
#define	SIZEOF_OSEVENT		64
#define	SIZEOF_OSTCBDATA	32
#define	SIZEOF_OSSPINLOCK 32
#else
#define	SIZEOF_OSEVENT		32
#define	SIZEOF_OSTCBDATA	16
#define	SIZEOF_OSSPINLOCK 24
#endif

#define SIZEOF_OSACS		256

#if !defined(UNDER_CE) && !defined(WIN32_RUNTIME)
#define	SIZEOF_OSHDLCS_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define	SIZEOF_OSHDLCS(n)		SIZEOF_OSHDLCS_MAX(SIZEOF_OSEVENT + (n)*SIZEOF_OSTCBDATA, SIZEOF_OSSPINLOCK)
#else

#ifndef POSIX
#define	SIZEOF_OSHDLCS(n)		(((n)+1)*sizeof(CRITICAL_SECTION))
#else
#include "OsUserTools.h"
#define	SIZEOF_OSHDLCS(n)		(((n)+1)*sizeof(OsUserCriticalSection))
#endif // _WIN32

#endif

typedef struct
{
	BOOL		bActive;
	DWORD		nPercent;
	DWORD		nBaseTime;			// 100 ns
	DWORD		nFastInterval;
} RTIME_TICKSETTINGS, *PRTIME_TICKSETTINGS;

typedef union
{
	struct
	{
		unsigned short bBSOD:  1;
		unsigned short bRtVio: 1;
		unsigned short bDisableOnlineChange: 1;
		unsigned short bDisableDownload: 1;
		unsigned short bDisableBreakpoints: 1;
		unsigned short bRes:  11;
	};
	unsigned short wFlags;
} RTIME_STATEFLAGS, *PRTIME_STATEFLAGS;

typedef enum
{
	EXTSYNCFNC_BEFORE_EOI,
	EXTSYNCFNC_AFTER_EOI,
} EXTSYNCFNCPOS;
typedef long (*PEXTSYNCFNC)( PVOID pUsr, EXTSYNCFNCPOS nPos );		
typedef void (*PTASKFNC)	( PVOID pUsr );	// pointer to task function body


typedef long			(*PRTime_AcquireGlobalLock)			(	);
typedef long			(*PRTime_ReleaseGlobalLock)			(	);

typedef long (*PEXCPHNDFNC)( PVOID pUsr, PEXCEPTION_POINTERS pExcpPtrs );		

#ifdef __cplusplus

struct __declspec(novtable) ITcTask : public ITcUnknown
{										
	virtual	HRESULT	TCOMAPI	GetCycleCounter(PULONGLONG pCnt)=0;
	virtual	HRESULT	TCOMAPI	GetCycleTime(PULONG pCycleTimeNS)=0;
	virtual	HRESULT	TCOMAPI	GetPriority(PULONG pPriority)=0;
	virtual	HRESULT	TCOMAPI	GetCurrentSysTime(PLONGLONG pSysTime)=0;
	virtual	HRESULT	TCOMAPI	GetCurrentDcTime(PLONGLONG pDcTime)=0;
	virtual	HRESULT	TCOMAPI	GetCurPentiumTime(PLONGLONG pCurTime)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcTask, IID_ITcTask);

struct	__declspec(novtable)	ITcRTimeTask : public ITcTask
{
	virtual	HRESULT	TCOMAPI	ExcpHandler(PEXCEPTION_POINTERS pExcpPtrs)=0;
	virtual	HRESULT	TCOMAPI	TaskEntryPoint()=0;
	virtual	HRESULT	TCOMAPI	EndlessLoopCheck(ULONG maxCycles)=0;
	virtual	HRESULT	TCOMAPI	GetTaskHandle(OSHDLTASK* pHTask)=0;
	virtual	HRESULT	TCOMAPI	GetCpuAccount(PULONG pAccount)=0;
	virtual	HRESULT	TCOMAPI	SetTaskCpuId(ULONG nCpuId)=0;
	virtual	HRESULT	TCOMAPI	GetTaskCpuId(PULONG pCpuId)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcRTimeTask, IID_ITcRTimeTask);

struct	__declspec(novtable)	ITcRTimeExcpHandler : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	ExcpHandler(PEXCEPTION_POINTERS pExcpPtrs)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcRTimeExcpHandler, IID_ITcRTimeExcpHandler);

struct	__declspec(novtable)	ITcRTimeRegisterExcpHandler : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI RegisterExcpHandler(ITcRTimeExcpHandler* ipExcpHandler)=0;
	virtual	HRESULT	TCOMAPI UnregisterExcpHandler(ITcRTimeExcpHandler* ipExcpHandler)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcRTimeRegisterExcpHandler, IID_ITcRTimeRegisterExcpHandler);

struct	__declspec(novtable)	ITcModuleState : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetPrevModuleState(ITcModuleState** pipModuleState)=0;
	virtual	HRESULT	TCOMAPI	SetPrevModuleState(ITcModuleState* ipModuleState)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcModuleState, IID_ITcModuleState);

struct __declspec(novtable) ITcDebugState : public ITcUnknown
{										
	virtual HRESULT	TCOMAPI GetDebugState() = 0;		// S_OK == RUN; S_PENDING == BREAK
};
_TCOM_SMARTPTR_TYPEDEF(ITcDebugState, IID_ITcDebugState);

struct __declspec(novtable) ITcDebugTask : public ITcUnknown
{										
	virtual HRESULT	TCOMAPI DebugHandler(ITcDebugState* ipDbgState) = 0;
	virtual HRESULT	TCOMAPI GetCurModule(ITcUnknown** pipModule, ULONG_PTR* pContext) = 0;
	virtual HRESULT	TCOMAPI GetCurInputDrv(ITcIoCyclic** pipDrv) = 0;
	virtual HRESULT	TCOMAPI GetCurOutputDrv(ITcIoCyclic** pipDrv) = 0;
	virtual HRESULT	TCOMAPI GetReloadSystemDcTime() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcDebugTask, IID_ITcDebugTask);

struct __declspec(novtable)	ITcTaskNotification : public ITcUnknown
{
	virtual HRESULT	TCOMAPI NotifyCycleTimeExceeded(ITcTask *ip, ULONG_PTR context) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcTaskNotification, IID_ITcTaskNotification);

#define	GETCURDCTIME_ACTUAL	0	// build from actual pentium time
#define	GETCURDCTIME_TICK		1	// build from current system time (actual base tick)
#define	GETCURDCTIME_TASK		2	// build from task tick

struct	__declspec(novtable)	ITcRTime : public ITcUnknown
{
	virtual HRESULT	TCOMAPI Delay(OSTICKS nTicks)=0;
	virtual HRESULT	TCOMAPI DelayUntil( OSTICKS awakeTick )=0;
	virtual HRESULT	TCOMAPI AdjustRealTime(BOOL bSlowDown)=0;

	// semaphore handling
	virtual HRESULT	TCOMAPI SemCreate( WORD nCntInit, OSHDLSEMA* phSema )=0;
	virtual HRESULT	TCOMAPI SemDelete( OSHDLSEMA hSema )=0;
	virtual HRESULT	TCOMAPI SemPost( OSHDLSEMA hSema )=0;
	virtual HRESULT	TCOMAPI SemPend( OSHDLSEMA hSema, OSTICKS nTimeout )=0;
	// queue handling
	virtual HRESULT	TCOMAPI QCreate( OSQITEM* pqBase, BYTE nSize, OSHDLQUEUE* phQueue )=0;
	virtual HRESULT	TCOMAPI QDelete( OSHDLQUEUE hQueue )=0;
	virtual HRESULT	TCOMAPI QPost( OSHDLQUEUE hQueue, OSQITEM pMsg )=0;
	virtual HRESULT	TCOMAPI QPend( OSHDLQUEUE hQueue, OSTICKS nTimeout, OSQITEM* phQueueItem, PBYTE pErr )=0;
	// critical section handling
	virtual HRESULT	TCOMAPI CsInitialize(OSHDLCS hdl)=0;
	virtual HRESULT	TCOMAPI CsDelete(OSHDLCS hdl)=0;
	virtual HRESULT	TCOMAPI CsEnter(OSHDLCS hdl)=0;
	virtual HRESULT	TCOMAPI CsLeave(OSHDLCS hdl)=0;
	virtual HRESULT	TCOMAPI CsInitializeConcurrent(OSHDLCS hdl, USHORT concurrent)=0;
	virtual HRESULT	TCOMAPI CsEnterConcurrent(OSHDLCS hdl)=0;

	virtual HRESULT	TCOMAPI IsTickerStarted( BOOL* pbStarted )=0;
	virtual HRESULT	TCOMAPI GetInWinFlag(BOOL* pbInWin)=0;
	virtual HRESULT	TCOMAPI GetCurSystemTime(PLONGLONG pCurTime)=0;
	virtual HRESULT	TCOMAPI GetCurPentiumTime(PLONGLONG pCurTime)=0;
	virtual HRESULT	TCOMAPI GetCurTaskTime(PLONGLONG pCurSysTime, PLONGLONG pCurDcTime)=0;
	virtual HRESULT	TCOMAPI GetTickBaseTime(ULONG nCpuId, DWORD* pdwBaseTime)=0;
	virtual HRESULT	TCOMAPI GetTickNow(ULONG nCpuId, OSTICKS* pOsTicks)=0;
	virtual HRESULT	TCOMAPI GetTickBaseTimeOfRootCpu(DWORD* pdwBaseTime)=0;
	virtual HRESULT	TCOMAPI GetTickNowOfRootCpu(OSTICKS* pOsTicks)=0;
	virtual HRESULT	TCOMAPI GetCurDcTime(ULONG nTimeMode, __int64* piCurDcTime)=0;
	virtual HRESULT	TCOMAPI QueryCurTaskInterface( ITCID iid, PPVOID pipTask )=0;

	virtual HRESULT	TCOMAPI GetTlsIndexOfType(ULONG tlsSlotType, PDWORD pTlsIndex)=0;
	virtual HRESULT	TCOMAPI OsTlsAlloc(ULONG tlsSlotType, PDWORD pTlsIndex)=0;
	virtual HRESULT	TCOMAPI OsTlsFree(DWORD tlsIndex)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcRTime, IID_ITcRTime);

class DLL_EXPORT CCriticalSectionInstance
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CCriticalSectionInstance(OTCID oid=0, ITComObjectServer* ipSrv=NULL);
	virtual	~CCriticalSectionInstance();
	virtual	void				SetOidCriticalSection(OTCID oid);
	virtual	bool				HasOidCriticalSection();
	virtual	bool				IsInitializedCriticalSection();
	virtual	HRESULT			CreateCriticalSection(ITComObjectServer* ipSrv);
	virtual	HRESULT			CreateCriticalSection(OTCID oid, ITComObjectServer* ipSrv);
	virtual	HRESULT			DeleteCriticalSection();
	virtual	HRESULT			EnterCriticalSection();
	virtual	HRESULT			LeaveCriticalSection();

private:
	BYTE										m_cs[SIZEOF_OSHDLCS(1)]; 
	ITcRTimePtr					m_spCsProvider;
};

class DLL_EXPORT CCriticalSectionInstanceConcurrent
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CCriticalSectionInstanceConcurrent(UINT concurrent, OTCID oid=0, ITComObjectServer* ipSrv=NULL);
	virtual	~CCriticalSectionInstanceConcurrent();
	virtual	void				SetOidCriticalSection(OTCID oid);
	virtual	bool				HasOidCriticalSection();
	virtual	bool				IsInitializedCriticalSection();
	virtual	HRESULT			CreateCriticalSection(ITComObjectServer* ipSrv);
	virtual	HRESULT			CreateCriticalSection(OTCID oid, ITComObjectServer* ipSrv);
	virtual	HRESULT			DeleteCriticalSection();
	virtual	HRESULT			EnterCriticalSection();
	virtual	HRESULT			LeaveCriticalSection();
	virtual	HRESULT			EnterCriticalSectionConcurrent();

private:
	UINT										m_concurrent;
	PBYTE										m_pCs; 
	ITcRTimePtr					m_spCsProvider;
};

// ----------------------------------------------------------------------------------------------------------------------------
class DLL_EXPORT CSemaphoreInstance
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CSemaphoreInstance(WORD nCntInit = 0, OTCID oid = 0, ITComObjectServer* ipSrv = NULL);
	~CSemaphoreInstance();

	void		SetOid(OTCID oid);
	bool		HasOid();
	bool		IsInitialized();

	HRESULT		SemCreate(ITComObjectServer* ipSrv);
	HRESULT		SemCreate(WORD nCntInit, OTCID oid, ITComObjectServer* ipSrv);
	HRESULT		SemDelete();
	HRESULT		SemPost();
	HRESULT		SemPend(OSTICKS nTimeout = 0);
private:
	ULONG		m_sem[8];
};

// ----------------------------------------------------------------------------------------------------------------------------
class CCtrl;
struct __declspec(novtable) ITaskCtrl : ITcUnknown
{
	TCOMMETHOD(GetCtrl(CCtrl** ppCtrl));
};

// ----------------------------------------------------------------------------------------------------------------------------
typedef ULONG_PTR TcJobHandle;

struct __declspec(novtable) ITcJobCalleeInfo
{
	virtual HRESULT TCOMAPI GetAbortRequest(HRESULT* phrAbort) = 0;
	virtual HRESULT TCOMAPI GetContext(ULONG* pInvokeId, ULONG* pnData = NULL, PVOID* ppData = NULL) = 0;
	virtual HRESULT TCOMAPI GetUserData(void* &data) = 0;
	virtual HRESULT TCOMAPI SetUserData(void* data) = 0;
};

struct __declspec(novtable) ITcJob : public ITcUnknown
{
	virtual HRESULT TCOMAPI ExecJob(ITcTask* ipTask, ITcJobCalleeInfo* ipInfo, ULONG invokeId, ULONG nData = 0, PVOID pData = NULL) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJob, IID_ITcJob);

// ----------------------------------------------------------------------------------------------------------------------------
struct __declspec(novtable) ITcJobCaller : public ITcUnknown
{
	virtual HRESULT TCOMAPI CreateJobHandle(TcJobHandle* pHdl, ITcJob* ipJob) = 0;
	virtual HRESULT TCOMAPI DeleteJobHandle(TcJobHandle hdl) = 0;
	virtual HRESULT TCOMAPI GetJob(TcJobHandle hdl, ITcJob** pipJob) = 0;
	virtual HRESULT TCOMAPI GetState(TcJobHandle hdl, HRESULT &hr) = 0;
	virtual HRESULT TCOMAPI GetCpuAccount(TcJobHandle hdl, ULONG &p) = 0;
	virtual HRESULT TCOMAPI GetTotalTime(TcJobHandle hdl, LONGLONG &p) = 0;
	virtual HRESULT TCOMAPI SetTimeout(TcJobHandle hdl, ULONG nTimeout) = 0;
	virtual HRESULT TCOMAPI GetTimeout(TcJobHandle hdl, ULONG &nTimeout) = 0;
	virtual HRESULT TCOMAPI SubmitJob(TcJobHandle hdl, ULONG invokeId, ULONG nData = 0, PVOID pData = NULL, ULONG nSortOrder = 100) = 0;
	virtual HRESULT TCOMAPI AbortJob(TcJobHandle hdl) = 0;
	virtual HRESULT TCOMAPI JoinJob(TcJobHandle hdl, OSTICKS nTimeout = 0) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJobCaller, IID_ITcJobCaller);

#endif // __cplusplus

