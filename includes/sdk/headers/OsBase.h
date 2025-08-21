///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBase.h"

#ifdef TC_ENVIRONMENT_OS
#define TCFRAMEWORK_EXPORT	TCOSSYS_API
#else
#define TCFRAMEWORK_EXPORT DLL_EXPORT
#endif

///////////////////////////////////////////////////////////////////////////////
#ifdef WINNT
///////////////////////////////////////////////////////////////////////////////
// Tracing
///////////////////////////////////////////////////////////////////////////////
#ifdef	DEBUG
	#ifdef	DISABLE_DEBUGOUTPUT
		#define 	OsDebugPrintf
		#define	TRACE
		#define	TRACE_BUFFER
	#else
		#define 	OsDebugPrintf		DbgPrint
		#define	TRACE					DbgPrint
		#define	TRACE_BUFFER		OsDebugPrintBuffer
	#endif
#else
	#define 	OsDebugPrintf
	#define	TRACE
	#define	TRACE_BUFFER
#endif

//-----------------------------------------------------------------------------
void OsDebugPrintBuffer(void* pData, int nData);

///////////////////////////////////////////////////////////////////////////////
// OsSpinLock
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	KSPIN_LOCK		spinLock;
	KIRQL				irql;
	ULONG				ulNestedCnt;
	PKTHREAD			pOwnerThread;
	ULONG				ulPendCnt;
} OsSpinLock, *POsSpinLock;

///////////////////////////////////////////////////////////////////////////////
// OsThread
///////////////////////////////////////////////////////////////////////////////
typedef	void	(*POSTHREADFUNC) ( PVOID pUsr );
PVOID TCFRAMEWORKAPI OsGetCurrentThread();
HANDLE TCFRAMEWORKAPI OsGetCurrentThreadId();
NTSTATUS TCFRAMEWORKAPI OsEndCurrentSystemThread(NTSTATUS status);
BOOL TCFRAMEWORKAPI OsSetPriorityThread(PVOID pThread, KPRIORITY nPriority);
PVOID TCFRAMEWORKAPI OsCreateSystemThread( POSTHREADFUNC pFunc, PVOID pUser );
NTSTATUS	TCFRAMEWORKAPI OsSetThreadAffinityMask(ULONG_PTR affinityMask);
void TCFRAMEWORKAPI OsCloseSystemThread( PVOID pThread );
NTSTATUS TCFRAMEWORKAPI OsWaitForThreadExit(PVOID ThreadHandle, int nTimeout);

///////////////////////////////////////////////////////////////////////////////
// OsWait
///////////////////////////////////////////////////////////////////////////////
#define	WFSO_INFINITIVE	0
#define	WFSO_SIGNALED		0
#define	WFSO_TIMEOUT		1
#define	WFSO_ERROR			2

int OsWaitForSingleObject( PVOID pObject, int nTimeout );

///////////////////////////////////////////////////////////////////////////////
// OsMutex
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	PKMUTEX	pMutex;
} OsMutex, *POsMutex;

///////////////////////////////////////////////////////////////////////////////
// CCycleTimer
///////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CCycleTimer
{
	LARGE_INTEGER	m_nMSec;
	__int64			m_nTicks;
	LONG				m_nOnTimerCnt;
private:
	PKTIMER			m_pTimerObject;
	PKDPC				m_pDpcObject;
	BOOL				m_bRunning;
	LONG				m_msec;

	static VOID handler( IN PKDPC Dpc, IN PVOID pThis,
								IN PVOID SystemArgument1, IN PVOID SystemArgument2 );

public:
	DECLARE_OPERATOR_NEW_DELETE()

	CCycleTimer( ULONG msec, BOOL autoStart );
	virtual ~CCycleTimer();
	virtual	void	OnTimer();
	void SetTimer();
	void StopTimer();
	void StartTimer();
};

///////////////////////////////////////////////////////////////////////////////
// CSingleTimer
///////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CSingleTimer
{
	LARGE_INTEGER	m_nMSec;
	PKTIMER			m_pTimerObject;
	PKDPC				m_pDpcObject;
protected:
	__int64			m_nTicks;

public:
	DECLARE_OPERATOR_NEW_DELETE()

	CSingleTimer( ULONG msec );
	virtual ~CSingleTimer();
	static VOID handler( IN PKDPC Dpc, IN PVOID pThis,
								IN PVOID SystemArgument1, IN PVOID SystemArgument2 );

	virtual	void	OnTimer();
	void Set();
};

///////////////////////////////////////////////////////////////////////////////
// COsEvent
///////////////////////////////////////////////////////////////////////////////
#define	COSEVENT_SIGNALED		0
#define	COSEVENT_TIMEOUT		1
#define	COSEVENT_ERROR			2
#define	OSEVENTNAME_PREFIX	"\\Device\\"


class DLL_EXPORT COsEvent
{
	HANDLE	m_hEvent;
	PKEVENT	m_pkEvent;
public:	
	COsEvent( PSTR pCharStr );
	COsEvent( PWCHAR uszString );
	~COsEvent();
	BOOL	Valid();
	int Wait( int nTimeout );	// in ms
	int Wait();	// infinitive
	void Signal();
	void Clear();
};

#endif // WINNT

#if defined(TC_ENVIRONMENT_OS)

#include <TcRtInterfaces.h>

#ifdef	DEBUG
void OsDebugPrintBuffer(void* pData, int nData);
#ifdef	DISABLE_DEBUGOUTPUT
#define 	OsDebugPrintf
#define	TRACE
#define	TRACE_BUFFER
#else
#define 	OsDebugPrintf		DbgPrint
#define	TRACE					DbgPrint
#define	TRACE_BUFFER		/*OsDebugPrintBuffer*/ // currently not defined
#endif
#else
#define 	OsDebugPrintf
//#define	TRACE DbgPrint
#define	TRACE
#define	TRACE_BUFFER
#endif

///////////////////////////////////////////////////////////////////////////////
// OsSpinLock
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	char buf[SIZEOF_OSSPINLOCK];
} OsSpinLock, *POsSpinLock;

///////////////////////////////////////////////////////////////////////////////
// OsMutex
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	char	buf[SIZEOF_OSSPINLOCK];
} OsMutex, *POsMutex;

///////////////////////////////////////////////////////////////////////////////
// OsExclusiveResource
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	void*	resource;
} OsRWLock, *POsRWLock;

///////////////////////////////////////////////////////////////////////////////
// OsThread
///////////////////////////////////////////////////////////////////////////////
typedef	void(*POSTHREADFUNC) (PVOID pUsr);
TCOSSYS_API PVOID __stdcall OsGetCurrentThread();
TCOSSYS_API HANDLE __stdcall OsGetCurrentThreadId();
TCOSSYS_API NTSTATUS __stdcall OsEndCurrentSystemThread(NTSTATUS status);
TCOSSYS_API BOOL __stdcall OsSetPriorityThread(PVOID pThread, KPRIORITY nPriority);
TCOSSYS_API KPRIORITY OsGetThreadPriority(PVOID pThread);
TCOSSYS_API PVOID __stdcall OsCreateSystemThread(POSTHREADFUNC pFunc, PVOID pUser);
TCOSSYS_API NTSTATUS	__stdcall OsSetThreadAffinityMask(ULONG_PTR affinityMask);
TCOSSYS_API void __stdcall OsCloseSystemThread(PVOID pThread);
TCOSSYS_API void __stdcall OsCleanUpSystemThreads(void);
TCOSSYS_API NTSTATUS __stdcall OsWaitForThreadExit(PVOID ThreadHandle, int nTimeout);
TCOSSYS_API void TCFRAMEWORKAPI OsDelayExecutionThread(ULONG nDelay);
TCOSSYS_API void TCFRAMEWORKAPI OsDelayExecutionThreadInUs(ULONG nDelay);


///////////////////////////////////////////////////////////////////////////////
// COsEvent
///////////////////////////////////////////////////////////////////////////////
#define	COSEVENT_SIGNALED		0
#define	COSEVENT_TIMEOUT		1
#define	COSEVENT_ERROR			2
#define	COSEVENT_IDLE			3
#define	OSEVENTNAME_PREFIX	"TCOSEvt_"
class TCOSSYS_API COsEvent
{
	HANDLE	m_hEvent;
	char*		m_pszName;
	ULONG		m_state;

public:
	COsEvent(PSTR pCharStr);
	COsEvent(PWCHAR uszString);
	COsEvent(ULONG flags);
	~COsEvent();
	BOOL	Valid();
	int Wait(int nTimeout);	// in ms
	int Wait();	// infinitive
	void Signal();
	void Clear();
};

///////////////////////////////////////////////////////////////////////////////
// CCycleTimer
///////////////////////////////////////////////////////////////////////////////
struct TcOsTimerObject;
class TCOSSYS_API CCycleTimer
{
private:
	__int64			m_nTicks;
	volatile BOOL	m_bRunning;

	LONG				m_msec;
	TcOsTimerObject* m_pTimerObj;

public:
	DECLARE_OPERATOR_NEW_DELETE()

	CCycleTimer(ULONG msec, BOOL autoStart);
	virtual ~CCycleTimer();
	virtual	void	OnTimer();
	void SetTimer();
	void StopTimer();
	void StartTimer();

	friend void TcOsTimerListExec();
};

///////////////////////////////////////////////////////////////////////////////
// OsWait
///////////////////////////////////////////////////////////////////////////////
#define	WFSO_INFINITIVE	INFINITE
#define	WFSO_SIGNALED		0
#define	WFSO_TIMEOUT		1
#define	WFSO_ERROR			2

int OsWaitForSingleObject(PVOID pObject, int nTimeout);
int OsWaitForMultipleObjects(int nCount, const PVOID *pObject, BOOL bWaitAll, int nTimeout);

///////////////////////////////////////////////////////////////////////////////
// OsGetLastError
///////////////////////////////////////////////////////////////////////////////
DWORD TCFRAMEWORKAPI OsGetLastError(VOID);


///////////////////////////////////////////////////////////////////////////////
// OsGetSystemInfo
///////////////////////////////////////////////////////////////////////////////
VOID TCFRAMEWORKAPI OsGetSystemInfo(LPSYSTEM_INFO lpSystemInfo);


#endif // defined(TC_ENVIRONMENT_OS)

#if defined(TC_ENVIRONMENT_CE_RT)
//the definition has a different return parameter than in TC_ENVIRONMENT_OS
typedef	DWORD(*POSTHREADFUNC) (PVOID pUsr);

#endif

///////////////////////////////////////////////////////////////////////////////
//
#ifdef WIN32_RUNTIME

//#ifdef UNDER_CE
//	#include "ceddk.h"
//#endif

#if defined (UNDER_CE)
#include "altcecrt.h"
#else
#include <crtdbg.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Tracing
///////////////////////////////////////////////////////////////////////////////
#ifdef	DEBUG
	#ifdef	DISABLE_DEBUGOUTPUT
		#define 	OsDebugPrintf
		#define	TRACE
		#define	TRACE_BUFFER
	#else
		#define 	OsDebugPrintf		DbgPrint
		#if !_AFXDLL
			#define	TRACE				DbgPrint
		#endif
		#define	TRACE_BUFFER		OsDebugPrintBuffer
	#endif
#else
	#define 	OsDebugPrintf
	#if !_AFXDLL
	//Fast way of finding the source of a message: #define TRACE(text, ...) DbgPrint(_T("%s:%u ") text, _T(__FILE__), __LINE__, __VA_ARGS__)
	#define TRACE
	#endif
	#define	TRACE_BUFFER
#endif

#ifndef TC_ENVIRONMENT_CE_RT
#define snprintf	_snprintf
#endif

DLL_EXPORT void TCFRAMEWORKAPI DbgPrint(LPCTSTR pFmtStr, ...);
DLL_EXPORT void TCFRAMEWORKAPI OsDebugPrintBuffer(void* pData, int nData);

#include "platform/Common/TcSdkLinkedListMacros.h"


///////////////////////////////////////////////////////////////////////////////
// OsGetLastError
///////////////////////////////////////////////////////////////////////////////
DLL_EXPORT DWORD TCFRAMEWORKAPI OsGetLastError(VOID);


///////////////////////////////////////////////////////////////////////////////
// OsGetSystemInfo
///////////////////////////////////////////////////////////////////////////////
DLL_EXPORT VOID TCFRAMEWORKAPI OsGetSystemInfo(LPSYSTEM_INFO lpSystemInfo);


///////////////////////////////////////////////////////////////////////////////
// OsWait
///////////////////////////////////////////////////////////////////////////////
#define	WFSO_INFINITIVE	INFINITE
#define	WFSO_SIGNALED		WAIT_OBJECT_0
#define	WFSO_TIMEOUT		WAIT_TIMEOUT
#define	WFSO_ERROR			WAIT_FAILED

DLL_EXPORT int TCFRAMEWORKAPI OsWaitForSingleObject( PVOID pObject, int nTimeout );

///////////////////////////////////////////////////////////////////////////////
// COsEvent
///////////////////////////////////////////////////////////////////////////////
#define	COSEVENT_SIGNALED	WAIT_OBJECT_0
#define	COSEVENT_TIMEOUT	WAIT_TIMEOUT
#define	COSEVENT_ERROR		WAIT_FAILED
#define	OSEVENTNAME_PREFIX	"W32Evt_"
class DLL_EXPORT COsEvent
{
	HANDLE	m_hEvent;
public:	
	COsEvent( PSTR pCharStr );
	COsEvent( PWCHAR uszString );
	~COsEvent();
	BOOL	Valid();
	int Wait( int nTimeout );	// in ms
	int Wait();	// infinitive
	void Signal();
	void Clear();
};

///////////////////////////////////////////////////////////////////////////////
// OsThread
///////////////////////////////////////////////////////////////////////////////
#if	 UNDER_CE >= 300
	#define LOW_PRIORITY                254
	#define LOW_REALTIME_PRIORITY		128
	#define OSTIMER_PRIORITY			63
#else
	#define LOW_REALTIME_PRIORITY		THREAD_PRIORITY_ABOVE_NORMAL
	#define OSTIMER_PRIORITY			THREAD_PRIORITY_TIME_CRITICAL
#endif

#define OsGetCurrentThread()			GetCurrentThread()
#define OsEndCurrentSystemThread(x)	
#define OsGetCurrentThreadId()		(HANDLE)(DWORD_PTR)GetCurrentThreadId()
DLL_EXPORT HANDLE TCFRAMEWORKAPI	OsCreateSystemThread( PVOID pFunc, PVOID pUser );
DLL_EXPORT void TCFRAMEWORKAPI		OsCloseSystemThread( HANDLE pThread );
DLL_EXPORT NTSTATUS TCFRAMEWORKAPI	OsWaitForThreadExit(PVOID ThreadHandle, int nTimeout);
DLL_EXPORT NTSTATUS TCFRAMEWORKAPI	OsSetThreadAffinityMask(ULONG affinityMask);
#define OsTerminateSystemThread(x)	::ExitThread(x)	
#if	 UNDER_CE >= 300
	#define OsSetPriorityThread(a, b)	::CeSetThreadPriority(((PVOID)a), (b))
#else
	#define OsSetPriorityThread(a, b)	::SetThreadPriority(((PVOID)a), (b))
#endif


#ifndef	STATUS_SUCCESS
	#define STATUS_SUCCESS				0
#endif

class DLL_EXPORT CTimer
{
	__int64			m_nTicks;

private:
	LONG		m_nMSec;
	BOOL		m_bActive;
	BOOL		m_bTerminate;

	HANDLE	m_hThread;
	HANDLE	m_hThreadActiveEvent;
	HANDLE	m_hEvent;
	DWORD		m_dwThreadId; 
	DWORD		m_dwTimerId;
	WORD		m_wTimerRes;
	DWORD		m_dwMMAttrib;

public:
	DECLARE_OPERATOR_NEW_DELETE()

	CTimer( ULONG msec, BOOL autoStart, DWORD dwMMAttrib);
	CTimer( ULONG msec, DWORD dwMMAttrib );
	virtual ~CTimer();
	static ULONG TCFRAMEWORKAPI ThreadWrapper(void* pThis);
	virtual	void	OnTimer();
	virtual void StopTimer();
	virtual void StartTimer();
	virtual void Set();

private:
	virtual void SetTimer();
};

///////////////////////////////////////////////////////////////////////////////
// CSingleTimer
///////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CSingleTimer : public CTimer
{
public:
	CSingleTimer(ULONG msec);
};

///////////////////////////////////////////////////////////////////////////////
// CCycleTimer
///////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CCycleTimer : public CTimer
{
public:
	CCycleTimer(ULONG msec, BOOL autoStart);
	virtual void Set();
};


///////////////////////////////////////////////////////////////////////////////
// OsContiguousMemory
///////////////////////////////////////////////////////////////////////////////
#if (_WIN32_WCE >= 0x600)
DLL_EXPORT PVOID TCFRAMEWORKAPI OsAllocateContiguousMemoryUM(ULONG cbSize, PULONG pPhysAddr);
DLL_EXPORT VOID TCFRAMEWORKAPI OsFreeContiguousMemoryUM(PVOID pVirtAddr);
#endif

///////////////////////////////////////////////////////////////////////////////
// OsSpinLock
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	CRITICAL_SECTION	critSec;
} OsSpinLock, *POsSpinLock;

///////////////////////////////////////////////////////////////////////////////
// OsMutex
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	HANDLE	mutex;
} OsMutex, *POsMutex;

#endif // WIN32_RUNTIME


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// WINNT and WIN32_RUNTIME common declarations and defnitions
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Check Execution level
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT BOOL TCFRAMEWORKAPI OsIsPassiveLevel();
TCFRAMEWORK_EXPORT BOOL TCFRAMEWORKAPI OsIsDispatchLevel();
TCFRAMEWORK_EXPORT BOOL TCFRAMEWORKAPI OsIsLessOrEqualDispatchLevel();


///////////////////////////////////////////////////////////////////////////////
// OsMapPhys
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT PVOID TCFRAMEWORKAPI OsMapPhysAddr( PVOID pPhysMem, ULONG memSize );
TCFRAMEWORK_EXPORT VOID  TCFRAMEWORKAPI OsUnMapPhysAddr( PVOID pLinMem, ULONG memSize );
TCFRAMEWORK_EXPORT PVOID TCFRAMEWORKAPI OsMapPhysAddr(PVOID pPhysMem, ULONG memSize);
TCFRAMEWORK_EXPORT VOID  TCFRAMEWORKAPI OsUnMapPhysAddr( PVOID pLinMem, ULONG memSize );

DLL_EXPORT PVOID TCFRAMEWORKAPI OsMapPhysAddr(PHYSICAL_ADDRESS phys, size_t nMemSize);
DLL_EXPORT PVOID TCFRAMEWORKAPI OsMapPhysAddrCached( PVOID pPhysMem, ULONG memSize );
DLL_EXPORT PVOID TCFRAMEWORKAPI OsMapPhysAddrCached(PHYSICAL_ADDRESS phys, size_t nMemSize);
DLL_EXPORT VOID  TCFRAMEWORKAPI OsUnMapMemAddr( PVOID pSpace2UnMap );

///////////////////////////////////////////////////////////////////////////////
#if defined(TC_ENVIRONMENT_RT) || defined(TC_ENVIRONMENT_OS)
DLL_EXPORT PHYSICAL_MEMORY_RANGE* TCFRAMEWORKAPI OsGetPhysicalMemoryRanges();
#endif

#if defined(TC_ENVIRONMENT_OS)
VOID TCFRAMEWORKAPI OsReadPhysAddr(PVOID pBuff, PVOID pPhysMem, ULONG ReadSize);
VOID TCFRAMEWORKAPI OsWritePhysAddr(PVOID pBuff, PVOID pPhysMem, ULONG ReadSize);
#endif

///////////////////////////////////////////////////////////////////////////////
// OsContiguousMemory
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT PVOID TCFRAMEWORKAPI OsAllocateContiguousMemory(ULONG cbSize);
TCFRAMEWORK_EXPORT VOID TCFRAMEWORKAPI OsFreeContiguousMemory(PVOID BaseAddress);
TCFRAMEWORK_EXPORT PHYSICAL_ADDRESS TCFRAMEWORKAPI OsGetPhysicalAddress(PVOID BaseAddress);

#ifndef TC_ENVIRONMENT_OS
#define OsAllocateContiguousMemoryEx			OsAllocateContiguousMemory
#define OsFreeContiguousMemoryEx(p,s)			OsFreeContiguousMemory(p)
#else
TCFRAMEWORK_EXPORT PVOID TCFRAMEWORKAPI OsAllocateContiguousMemoryEx(ULONG cbSize);
TCFRAMEWORK_EXPORT VOID TCFRAMEWORKAPI	OsFreeContiguousMemoryEx(PVOID BaseAddress, ULONG cbSize);
#endif




///////////////////////////////////////////////////////////////////////////////
// OsSpinLock
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsInitializeSpinLock(POsSpinLock pSp);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsDeleteSpinLock(POsSpinLock pSp);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsAcquireSpinLock(POsSpinLock pSp);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsAcquireSpinLockAtDpcLevel(POsSpinLock pSp);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsReleaseSpinLock(POsSpinLock pSp);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsReleaseSpinLockFromDpcLevel(POsSpinLock pSp);

#if defined(TC_ENVIRONMENT_OS_UM_SUPPORT)
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsInitializeSpinLockEx(POsSpinLock pSp, bool bRecursive);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsDeleteSpinLockEx(POsSpinLock pSp, bool bCheckNonRtContext = false);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsAcquireSpinLockEx(POsSpinLock pSp, bool bCheckNonRtContext = false);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsReleaseSpinLockEx(POsSpinLock pSp, bool bCheckNonRtContext = false);
#endif


///////////////////////////////////////////////////////////////////////////////
// OsMutex
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsInitializeMutex(POsMutex pMtx);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsDeleteMutex(POsMutex pMtx);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsAcquireMutex(POsMutex pMtx);
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsReleaseMutex(POsMutex pMtx);


///////////////////////////////////////////////////////////////////////////////
// OsTime
///////////////////////////////////////////////////////////////////////////////
typedef	LARGE_INTEGER SYSTEM_TIME;

TCFRAMEWORK_EXPORT LARGE_INTEGER TCFRAMEWORKAPI OsQueryPerformanceCounter(LARGE_INTEGER* pFreq);
TCFRAMEWORK_EXPORT ULONGLONG TCFRAMEWORKAPI OsQueryTickCount100Ns();
TCFRAMEWORK_EXPORT void TCFRAMEWORKAPI OsQuerySystemTime(SYSTEM_TIME& time);
TCFRAMEWORK_EXPORT ULONG TCFRAMEWORKAPI OsQueryTickCountMs();
TCFRAMEWORK_EXPORT BOOL TCFRAMEWORKAPI OsTimeElapsed(SYSTEM_TIME base, SYSTEM_TIME current, ULONG interval);

#ifndef TC_ENVIRONMENT_OS
DLL_EXPORT void TCFRAMEWORKAPI OsDelayExecutionThread(ULONG nDelay);
DLL_EXPORT void TCFRAMEWORKAPI OsDelayExecutionThreadInUs(ULONG nDelay);
#endif // !TC_ENVIRONMENT_OS
DLL_EXPORT void TCFRAMEWORKAPI OsStallExecutionProcessor( ULONG nDelay );

///////////////////////////////////////////////////////////////////////////////
// OsCreateGuid
///////////////////////////////////////////////////////////////////////////////
TCFRAMEWORK_EXPORT BOOL TCFRAMEWORKAPI OsCreateGuid(GUID* g);

///////////////////////////////////////////////////////////////////////////////
// CTimeout
///////////////////////////////////////////////////////////////////////////////
class	CTimeout
{
public:
	CTimeout() : m_timeElapse(0)		{};
	CTimeout(ULONG timeoutMsec)		{ Start(timeoutMsec); }
	void	Start(ULONG timeoutMsec)	{ m_timeElapse = OsQueryTickCountMs() + timeoutMsec; if (m_timeElapse == 0) m_timeElapse = 1; }
	bool	IsElapsed()						{ return m_timeElapse != 0 && (OsQueryTickCountMs() - m_timeElapse) < 0x80000000; }
#if 0	
	bool	IsElapsed(ULONG timeMs)		{ return m_timeElapse != 0 && (timeMs - m_timeElapse) < 0x80000000; }
	ULONG	GetTimeLeft(ULONG timeMs)	{ return  timeMs - m_timeElapse; };
	static ULONG GetTime()				{ return OsQueryTickCountMs(); }
#endif

private:
	ULONG	m_timeElapse;
};

#define TCMEMREALLOCATE

struct DLL_EXPORT __declspec(novtable)	ITcMemoryManager
{
	virtual	PVOID		Alloc(INT_PTR len, LPCSTR lpszFileName=NULL, int nLine=0)=0;
	virtual	PVOID		AllocAds(INT_PTR len)=0;
	virtual	void		Free(PVOID ptr)=0;
	virtual	bool		IsPointerRtMem(const PVOID ptr) const =0;
	virtual	INT_PTR	MaxAvailableRtMem(bool bAll)=0;
};

#ifdef TCMEMREALLOCATE
struct DLL_EXPORT __declspec(novtable)	ITcMemoryManager2 : public ITcMemoryManager
{
	virtual	PVOID		Realloc(PVOID ptr, INT_PTR len, LPCSTR lpszFileName=NULL, int nLine=0)=0;
	virtual	PVOID		ReallocAds(PVOID ptr, INT_PTR len)=0;
};
#endif

#include "TcMem.h"

DLL_EXPORT bool	TCFRAMEWORKAPI base64_isvalid(PCCH s, bool bUrl = false);
DLL_EXPORT size_t TCFRAMEWORKAPI base64_bufferlen(size_t n, bool noPadding = false);
DLL_EXPORT size_t TCFRAMEWORKAPI base64_bufferlen(PCCH s, bool noPadding = false);
DLL_EXPORT size_t TCFRAMEWORKAPI base64_encode(BYTE const* pData, size_t nData, PCHAR pBuf, size_t nBuf = 0, bool noPadding = false, bool bUrl = false);
DLL_EXPORT size_t TCFRAMEWORKAPI base64_decode(PCCH sData, PBYTE pBuf = NULL, size_t nBuf = 0, bool bUrl = false);

DLL_EXPORT bool	TCFRAMEWORKAPI hexbin_isvalid(PCCH s);
DLL_EXPORT size_t TCFRAMEWORKAPI hexbin_length(PCCH s);
DLL_EXPORT size_t TCFRAMEWORKAPI hexbin_encode(BYTE const* pData, size_t nData, PCHAR pBuf, size_t nBuf = 0);
DLL_EXPORT size_t TCFRAMEWORKAPI hexbin_decode(PCCH sData, PBYTE pBuf = NULL, size_t nBuf = 0);

#if defined(TC_ENVIRONMENT_RT)
void* TCFRAMEWORKAPI OsFwMemAllocate(size_t nBytes);
#ifdef TCMEMREALLOCATE
void* TCFRAMEWORKAPI OsFwMemReallocate(void* ptr, size_t nBytes);
size_t TCFRAMEWORKAPI OsFwMemAllocatedSize(void* ptr);
#endif
void	TCFRAMEWORKAPI OsFwMemFree(void* ptr);
#endif

///////////////////////////////////////////////////////////////////////////////

_inline PVOID	OsMemAllocate( size_t nSize, LPCSTR lpszFileName=NULL, int nLine=0)
{
	CHECK_NON_RT_CONTEXT();

	if ( nSize == 0 && lpszFileName != NULL )
	{
	#if defined(TC_ENVIRONMENT_RT)
		DbgMsgSound();
	#endif
		OsDebugPrintf(_T("%s (%d): WARNING: allocate null size memory!\n"), lpszFileName, nLine);
	}
	else
	{
		BUGWRN(nSize,_T("OsMemAllocate() Attempt to allocate null size memory!\n"));
	}
#if defined(TC_ENVIRONMENT_RT)
	PVOID pMem = OsFwMemAllocate(nSize);
#elif defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT)	|| defined(TC_ENVIRONMENT_OS)
	PVOID pMem = malloc( nSize );
#else
	PVOID pMem = _malloc_dbg( nSize, _NORMAL_BLOCK, lpszFileName, nLine);
#endif // defined(TC_ENVIRONMENT_RT)
#if DEBUGLEVEL == 2
	OsDebugPrintf(_T("OsMemAllocate() allocated memory block at 0x%x with size %d.\n"), pMem, nSize);
#endif
	return pMem;
}

#ifdef TCMEMREALLOCATE
_inline PVOID	OsMemReallocate(PVOID ptr, size_t nSize, LPCSTR lpszFileName=NULL, int nLine=0)
{
	CHECK_NON_RT_CONTEXT();

	if ( nSize == 0 && lpszFileName != NULL )
	{
	#if defined(TC_ENVIRONMENT_RT)
		DbgMsgSound();
	#endif
		OsDebugPrintf(_T("%s (%d): WARNING: allocate null size memory!\n"), lpszFileName, nLine);
	}
	else
	{
		BUGWRN(nSize,_T("OsMemReallocate() Attempt to allocate null size memory!\n"));
	}
#if defined(TC_ENVIRONMENT_RT)
	PVOID pMem = OsFwMemReallocate(ptr, nSize);
#elif defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT)	|| defined(TC_ENVIRONMENT_OS)
	PVOID pMem = realloc(ptr, nSize );
#else
	PVOID pMem = _realloc_dbg(ptr, nSize, _NORMAL_BLOCK, lpszFileName, nLine);
#endif // defined(TC_ENVIRONMENT_RT)
#if DEBUGLEVEL == 2
	OsDebugPrintf(_T("OsMemReallocate() allocated memory block at 0x%x with size %d.\n"), pMem, nSize);
#endif
	return pMem;
}
#endif

//-----------------------------------------------------------------------------
_inline VOID OsMemFree( PVOID pMem )
{
#if defined(TC_ENVIRONMENT_RT)
	CHECK_NON_RT_CONTEXT();
#endif

	BUGWRN(pMem, "OsMemFree() Attempt to free null pointer!\n");
	if (pMem )
	{
#if defined(TC_ENVIRONMENT_RT)
	#if DEBUGLEVEL == 2
		OsDebugPrintf(_T("OsMemFree() Memory block 0x%x, size == %d\n"), pMem, *((ULONG*)pMem-1));
	#endif

		OsFwMemFree(pMem);
	
#elif defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT)	|| defined(TC_ENVIRONMENT_OS)
#if DEBUGLEVEL == 2
		OsDebugPrintf(_T("OsMemFree() Memory block 0x%x\n"), pMem);
#endif
		free( pMem );
#else
#if DEBUGLEVEL == 2
		OsDebugPrintf(_T("OsMemFree() Memory block 0x%x\n"), pMem);
#endif
		_free_dbg(pMem, _NORMAL_BLOCK);
#endif // defined(TC_ENVIRONMENT_RT)
	}
}

#define IMPLEMENT_OPERATOR_NEW_DELETE(theClass) \
	PVOID _cdecl theClass::operator new( size_t n )                                      { return TcMemAllocate(n); } \
	PVOID _cdecl theClass::operator new( size_t n, LPCSTR lpszFileName, int nLine )      { return TcMemAllocate(n, lpszFileName, nLine); } \
	PVOID _cdecl theClass::operator new [] ( size_t n )                                  { return TcMemAllocate(n); } \
	PVOID _cdecl theClass::operator new [] ( size_t n, LPCSTR lpszFileName, int nLine )  { return TcMemAllocate(n, lpszFileName, nLine); } \
	VOID _cdecl theClass::operator delete( PVOID p )                                     { TcMemFree(p); } \
	VOID _cdecl theClass::operator delete( PVOID p, LPCSTR lpszFileName, int nLine )     { TcMemFree(p); } \
	VOID _cdecl theClass::operator delete [] ( PVOID p )                                 { TcMemFree(p); } \
	VOID _cdecl theClass::operator delete [] ( PVOID p, LPCSTR lpszFileName, int nLine ) { TcMemFree(p); } 

#ifndef TC_DISABLE_OPERATOR_NEW_DELETE

#ifndef __PLACEMENT_NEW_INLINE
#define __PLACEMENT_NEW_INLINE
inline void* __cdecl operator new(size_t, void* _P) { return (_P); }
inline void __cdecl operator delete(void* p, void* _P) { /* do nothing */ }
#endif

///////////////////////////////////////////////////////////////////////////////
// Each call to operator new will increment this counter and each call to delete 
// will decrement it. Eventually on unloading the  driver can check for memory 
// leaks using the nNewCounter. 
//#define NEWDELETECOUNTER
#ifdef NEWDELETECOUNTER
extern int nNewCounter;
#endif

#ifdef _DEBUG

#pragma warning( disable: 4291 )
inline PVOID _cdecl operator new(size_t n, LPCSTR lpszFileName, int nLine)
{
#ifdef NEWDELETECOUNTER
	PVOID	pv;
	pv	= TcMemAllocate( n, lpszFileName, nLine );
	if ( pv )
		nNewCounter++;
	return pv;
#else
	return TcMemAllocate( n, lpszFileName, nLine );
#endif
}

#ifndef _AFXDLL
	#define DEBUG_NEW new(THIS_FILE, __LINE__)
#endif
#endif

#pragma warning( disable: 4595 )
inline PVOID _cdecl operator new( size_t n )
{
#ifdef NEWDELETECOUNTER
	PVOID	pv;
	pv	= TcMemAllocate( n, NULL, 0 );
	if ( pv )
		nNewCounter++;
	return pv;
#else
	return  TcMemAllocate( n, NULL, 0 );
#endif
}

inline VOID _cdecl operator delete( PVOID p )
{
	if ( p )
	{
#ifdef NEWDELETECOUNTER
		nNewCounter--;
#endif
		TcMemFree( p );
	}
}

#if _MSC_VER >= 1900 // compiler VS2015 or later
inline VOID _cdecl operator delete( PVOID p, size_t n )
{
	if ( p )
	{
#ifdef NEWDELETECOUNTER
		nNewCounter--;
#endif
		TcMemFree( p );
	}
}
inline VOID _cdecl operator delete[](PVOID p, size_t n)
{
	if (p)
	{
#ifdef NEWDELETECOUNTER
		nNewCounter--;
#endif
		TcMemFree(p);
	}
}

#endif // _MSC_VER >= 1900

inline PVOID _cdecl operator new [] ( size_t n )
{
#ifdef NEWDELETECOUNTER
	PVOID	pv;
	pv	= TcMemAllocate( n, NULL, 0 );
	if ( pv )
		nNewCounter++;
	return pv;
#else
	return TcMemAllocate( n, NULL, 0 );
#endif
}

inline VOID _cdecl operator delete [] ( PVOID p )
{
	if ( p )
	{
#ifdef NEWDELETECOUNTER
		nNewCounter--;
#endif
		TcMemFree( p );
	}
}

#pragma warning( default: 4595 )

#endif // TC_DISABLE_OPERATOR_NEW_DELETE

