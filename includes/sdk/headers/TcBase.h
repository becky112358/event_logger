///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"

#if !defined(TC_ENVIRONMENT_APP)
#include "TcDbgR0.h"
#include "RtlR0.h" // InterlockedIncrementR0, InterlockedOrR0, InterlockedAndR0, InterlockedDecrementR0, InterlockedExchangeR0, InterlockedExchangePtrR0
#include "TcMath.h"
#else
inline LONG InterlockedIncrementR0(ULONG* value) { return InterlockedIncrement((LONG*)value); }
inline LONG InterlockedDecrementR0(ULONG* value) { return InterlockedDecrement((LONG*)value); }
inline LONG InterlockedExchangeR0(ULONG* value, ULONG newValue) { return InterlockedExchange((LONG*)value, (LONG)newValue); }
inline PVOID InterlockedExchangePtrR0(LONG_PTR* value, LONG_PTR newValue) { return InterlockedExchangePointer((void**)value, (void*)newValue); }
#endif 

///////////////////////////////////////////////////////////////////////////////
// enable features required by the TwinCAT STL 
#define TCSTL_MUTEX_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// enable multi processor synchronization
#if defined(TC_ENVIRONMENT_RT) || defined(TCRTOS) || defined(TC_ENVIRONMENT_OS)

#if !defined(_ARM_) || !defined(TC_ENVIRONMENT_OS)

//We do not want MPS SUPPORT for CortexM and Zynq. Both are TC_ENVIRONMENT_OS and _ARM_

#define MPS_SUPPORT
#endif

#endif

#if defined(TC_ENVIRONMENT_OS) && !defined(ARM)
	#define TC_ENVIRONMENT_OS_UM_SUPPORT
#endif

///////////////////////////////////////////////////////////////////////////////
// XXXX_CRITSEC macros
#if defined(TC_ENVIRONMENT_RT) || (defined(TC_ENVIRONMENT_OS) && !defined(TC_ENVIRONMENT_OS_UM_SUPPORT))
	#if defined(ARM)
		#include "ArmHelper.h"
	#endif
	#define EXPORT_API
	#if defined(MPS_SUPPORT)
		typedef LONG			(*PRTime_AcquireGlobalLock)			(	);
		typedef LONG			(*PRTime_ReleaseGlobalLock)			(	);
		EXTERN_C	PRTime_AcquireGlobalLock g_pAcquireGlobalLock;
		EXTERN_C	PRTime_ReleaseGlobalLock g_pReleaseGlobalLock;
		#define DECLARE_CRITSEC
		#define INIT_CRITSEC
		#define DELETE_CRITSEC

		#define DISABLE_IRQS(){ if ( g_pAcquireGlobalLock )				\
										{													\
											{_disable();}								\
											g_pAcquireGlobalLock();					\
										}													\
										else												\
										{													\
											{_disable();}								\
										}													\
									 }


		#define ENABLE_IRQS() {	if ( g_pReleaseGlobalLock )				\
										{													\
											if ( g_pReleaseGlobalLock() == 0 )	\
											{												\
												{_enable();}							\
											}												\
										}													\
										else												\
										{													\
											{_enable();}								\
										}													\
									 }
		#define ENTER_CRITSEC	DISABLE_IRQS();
		#define LEAVE_CRITSEC	ENABLE_IRQS();
	#else // defined(MPS_SUPPORT)
		#if defined(_ARM_)
			#define DECLARE_CRITSEC
			#define INIT_CRITSEC
			#define DELETE_CRITSEC
			#define DISABLE_IRQS()	{_disable();}
			#define ENABLE_IRQS()	{_enable();}
			#define ENTER_CRITSEC	DISABLE_IRQS();
			#define LEAVE_CRITSEC	ENABLE_IRQS();
		#else
			#define DECLARE_CRITSEC
			#define INIT_CRITSEC
			#define DELETE_CRITSEC
			#define DISABLE_IRQS()	{__asm cli}
			#define ENABLE_IRQS()	{__asm sti}
			#define ENTER_CRITSEC	DISABLE_IRQS();
			#define LEAVE_CRITSEC	ENABLE_IRQS();
		#endif
	#endif //defined(MPS_SUPPORT)
#elif defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT)
	#if defined(_X86_) && (UNDER_CE < 0x700)
		#define DECLARE_CRITSEC
		#define INIT_CRITSEC
		#define DELETE_CRITSEC
		#define DISABLE_IRQS()	{__asm cli}
		#define ENABLE_IRQS()	{__asm sti}
		#define ENTER_CRITSEC	DISABLE_IRQS();
		#define LEAVE_CRITSEC	ENABLE_IRQS();
	#elif defined(_X86_) && !defined(TCRTOS)
		#define EXPORT_API
		#if defined(TCFRAMEWORK_STATIC_CE_LIB)
				extern "C" BOOL g_bSingleCore;
		#else
			#if defined(TCFRAMEWORK_EXPORTS)
				extern "C" __declspec(dllexport) BOOL g_bSingleCore;
			#else
				extern "C" __declspec(dllimport) BOOL g_bSingleCore;
			#endif
		#endif

		#define DECLARE_CRITSEC	CRITICAL_SECTION	critSec;
		#define INIT_CRITSEC		if (!g_bSingleCore) ::InitializeCriticalSection(&critSec);
		#define DELETE_CRITSEC	if (!g_bSingleCore) ::DeleteCriticalSection(&critSec);
		#define DISABLE_IRQS()	{	if ( g_bSingleCore )													\
											{																			\
												{__asm cli};														\
											}																			\
											else																		\
											{																			\
												::EnterCriticalSection((CRITICAL_SECTION*)&critSec);	\
											}																			\
										}
		#define ENABLE_IRQS()	{	if ( g_bSingleCore )													\
											{																			\
												{__asm sti};														\
											}																			\
											else																		\
											{																			\
												::LeaveCriticalSection((CRITICAL_SECTION*)&critSec);	\
											}																			\
										}
		#define ENTER_CRITSEC	DISABLE_IRQS();
		#define LEAVE_CRITSEC	ENABLE_IRQS();

	#elif defined(_X86_) && defined(TCRTOS)

		#if defined(TCFRAMEWORK_STATIC_CE_LIB)
				extern "C" BOOL g_bKernelMode;
		#else
			#if defined(TCFRAMEWORK_EXPORTS)
				extern "C" __declspec(dllexport) BOOL g_bKernelMode;
			#else
				extern "C" __declspec(dllimport) BOOL g_bKernelMode;
			#endif
		#endif


		#if defined(TCFRAMEWORK_EXPORTS)
			#define EXPORT_API __declspec(dllexport)
		#else
			#define EXPORT_API __declspec(dllimport)
		#endif
		typedef LONG			(*PRTime_AcquireGlobalLock)			(	);
		typedef LONG			(*PRTime_ReleaseGlobalLock)			(	);
		EXTERN_C	EXPORT_API PRTime_AcquireGlobalLock g_pAcquireGlobalLock;
		EXTERN_C	EXPORT_API PRTime_ReleaseGlobalLock g_pReleaseGlobalLock;
		#define DECLARE_CRITSEC		
		#define INIT_CRITSEC
		#define DELETE_CRITSEC
		#define DISABLE_IRQS()	{__asm cli}
		#define ENABLE_IRQS()	{__asm sti}
		#define ENTER_CRITSEC		DISABLE_IRQS();
		#define LEAVE_CRITSEC		ENABLE_IRQS();

	#elif defined(TC_ENVIRONMENT_CE) && defined(ARM)
		#include "ArmHelper.h"
		#define EXPORT_API
		#if defined(TCFRAMEWORK_STATIC_CE_LIB)
				extern "C" BOOL g_bKernelMode;
		#else
			#if defined(TCFRAMEWORK_EXPORTS)
				extern "C" __declspec(dllexport) BOOL g_bKernelMode;
			#else
				extern "C" __declspec(dllimport) BOOL g_bKernelMode;
			#endif
		#endif

		#define DECLARE_CRITSEC		CRITICAL_SECTION	critSec;
		#define INIT_CRITSEC			if (!g_bKernelMode) ::InitializeCriticalSection(&critSec);
		#define DELETE_CRITSEC		if (!g_bKernelMode) ::DeleteCriticalSection(&critSec);
		#define DISABLE_IRQS()		if ( g_bKernelMode ) DisableInts(); else ::EnterCriticalSection((CRITICAL_SECTION*)&critSec);
		#define ENABLE_IRQS()		if ( g_bKernelMode ) EnableInts(); else ::LeaveCriticalSection((CRITICAL_SECTION*)&critSec);
		#define ENTER_CRITSEC		DISABLE_IRQS();
		#define LEAVE_CRITSEC		ENABLE_IRQS();
	#elif defined(TC_ENVIRONMENT_CE_RT) && defined(ARM)
		#include "ArmHelper.h"

		#if defined(TCFRAMEWORK_EXPORTS)
			#define EXPORT_API __declspec(dllexport)
		#else
			#define EXPORT_API __declspec(dllimport)
		#endif

		#if defined(TCFRAMEWORK_STATIC_CE_LIB)
			extern "C" BOOL g_bKernelMode;
		#else
			extern "C" EXPORT_API BOOL g_bKernelMode;
		#endif

		typedef LONG			(*PRTime_AcquireGlobalLock)			(	);
		typedef LONG			(*PRTime_ReleaseGlobalLock)			(	);
		EXTERN_C	EXPORT_API PRTime_AcquireGlobalLock g_pAcquireGlobalLock;
		EXTERN_C	EXPORT_API PRTime_ReleaseGlobalLock g_pReleaseGlobalLock;
		#define DECLARE_CRITSEC		bool bIntsWereDisabled;
		#define INIT_CRITSEC bIntsWereDisabled = false;
		#define DELETE_CRITSEC
		#if 1
			//multicore variant
			#define DISABLE_IRQS(){ if ( g_pAcquireGlobalLock )		\
									{													\
										{bIntsWereDisabled = DisableInts();}							\
										g_pAcquireGlobalLock();					\
									}													\
									else												\
									{													\
										{bIntsWereDisabled = DisableInts();}							\
									}													\
								}
			#define ENABLE_IRQS() {	if ( g_pReleaseGlobalLock )		\
									{													\
										if ( g_pReleaseGlobalLock() == 0 )	\
										{												\
											{if (!bIntsWereDisabled) EnableInts();}						\
										}												\
									}													\
									else												\
									{													\
										{if (!bIntsWereDisabled) EnableInts();}							\
									}													\
								}
		#else
			//old single core variant
			#define DISABLE_IRQS()		DisableInts();
			#define ENABLE_IRQS()		EnableInts();
		#endif
		#define ENTER_CRITSEC		DISABLE_IRQS();
		#define LEAVE_CRITSEC		ENABLE_IRQS();


	#else
		#error "For TC_ENVIRONMENT_CE either _X86_ or ARM is must be defined"
	#endif
#elif defined(TC_ENVIRONMENT_UM)
	#define EXPORT_API
	#define DECLARE_CRITSEC		CRITICAL_SECTION	critSec;
	#define INIT_CRITSEC			::InitializeCriticalSection(&critSec);
	#define DELETE_CRITSEC		::DeleteCriticalSection(&critSec);
	#define DISABLE_IRQS()		::EnterCriticalSection((CRITICAL_SECTION*)&critSec);
	#define ENABLE_IRQS()		::LeaveCriticalSection((CRITICAL_SECTION*)&critSec);
	#define ENTER_CRITSEC		::EnterCriticalSection((CRITICAL_SECTION*)&critSec);
	#define LEAVE_CRITSEC		::LeaveCriticalSection((CRITICAL_SECTION*)&critSec);
#elif defined(TCOS_APP)
	#define DECLARE_CRITSEC		OsUserCriticalSection critSec;
	#define INIT_CRITSEC			OsUserInitializeCriticalSection(&critSec);
	#define DELETE_CRITSEC		OsUserDeleteCriticalSection(&critSec);
	#define DISABLE_IRQS()		OsUserEnterCriticalSection(&critSec);
	#define ENABLE_IRQS()		OsUserLeaveCriticalSection(&critSec);
	#define ENTER_CRITSEC		OsUserEnterCriticalSection(&critSec);
	#define LEAVE_CRITSEC		OsUserLeaveCriticalSection(&critSec);
#elif defined(TC_ENVIRONMENT_OS_UM_SUPPORT)

#define EXPORT_API
extern "C" BOOL g_bTcOsKernelMode;
extern "C" uint32_t __readcs();

inline BOOL IsKernelMode()
{
	return (__readcs() & 0x3) != 3;
}

typedef LONG(*PRTime_AcquireGlobalLock)			();
typedef LONG(*PRTime_ReleaseGlobalLock)			();
EXTERN_C	PRTime_AcquireGlobalLock g_pAcquireGlobalLock;
EXTERN_C	PRTime_ReleaseGlobalLock g_pReleaseGlobalLock;

#define DECLARE_CRITSEC			OsSpinLock critSec;
#define INIT_CRITSEC				if ( !g_bTcOsKernelMode ) OsInitializeSpinLock(&critSec);
#define DELETE_CRITSEC			if ( !g_bTcOsKernelMode ) OsDeleteSpinLock(&critSec);

#define DISABLE_IRQS(){ if ( g_pAcquireGlobalLock )				\
										{													\
											if ( g_bTcOsKernelMode ) {_disable();}	\
											g_pAcquireGlobalLock();					\
										}													\
										else if ( g_bTcOsKernelMode )					\
										{													\
											_disable();									\
										}													\
										else												\
										{													\
											OsAcquireSpinLock(const_cast<POsSpinLock>(&critSec));	\
										}													\
									 }


#define ENABLE_IRQS() {	if ( g_pReleaseGlobalLock )				\
										{													\
											if ( g_pReleaseGlobalLock() == 0 &&	\
												g_bTcOsKernelMode )						\
											{												\
												_enable();								\
											}												\
										}													\
										else if ( g_bTcOsKernelMode )					\
										{													\
											_enable();									\
										}													\
										else												\
										{													\
											OsReleaseSpinLock(const_cast<POsSpinLock>(&critSec));	\
										}													\
									 }
#define ENTER_CRITSEC	DISABLE_IRQS()
#define LEAVE_CRITSEC	ENABLE_IRQS()

#else
	#define DECLARE_CRITSEC
	#define INIT_CRITSEC
	#define DELETE_CRITSEC
	#define DISABLE_IRQS()
	#define ENABLE_IRQS()
	#define ENTER_CRITSEC
	#define LEAVE_CRITSEC
#endif 


///////////////////////////////////////////////////////////////////////////////
// TcIsRtTask
///////////////////////////////////////////////////////////////////////////////
#ifdef TC_ENVIRONMENT_OS
#ifdef __cplusplus
TCOSSYS_API bool TCFRAMEWORKAPI TcIsRtTask();
#endif
#else
#ifdef __cplusplus
DLL_EXPORT bool TCFRAMEWORKAPI TcIsRtTask();
#endif
#endif // TC_ENVIRONMENT_OS


///////////////////////////////////////////////////////////////////////////////
// CHECK_RT_CONTEXT, CHECK_NON_RT_CONTEXT
///////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#if defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT) || defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_RT)  || defined(TC_ENVIRONMENT_OS)
const LPCSTR cszInvalidContextRT    = "####################  Invalid context, expected RT  ####################";
const LPCSTR cszInvalidContextNonRT = "####################  Invalid context, expected Non-RT  ####################";
#define	CHECK_RT_CONTEXT()                          BUGBREAK(TcIsRtTask(), cszInvalidContextRT)
#define	CHECK_NON_RT_CONTEXT()                      BUGBREAK(!TcIsRtTask(), cszInvalidContextNonRT)
#elif defined(TC_ENVIRONMENT_APP)
	#define	CHECK_RT_CONTEXT()
	#define	CHECK_NON_RT_CONTEXT()
#endif
#else //  _DEBUG
	#define	CHECK_RT_CONTEXT()
	#define	CHECK_NON_RT_CONTEXT()
#endif //  _DEBUG

///////////////////////////////////////////////////////////////////////////////
typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;
typedef LARGE_INTEGER LINEAR_ADDRESS, *PLINEAR_ADDRESS;

///////////////////////////////////////////////////////////////////////////////
typedef enum TCATInstLevels
{
	TCATINSTLEVEL_NOLEVEL	=0,
	TCATINSTLEVEL_IO			=1,
	TCATINSTLEVEL_PLC			=2,
	TCATINSTLEVEL_NCPTP		=3,
	TCATINSTLEVEL_NCI			=4,
	TCATINSTLEVEL_CNC			=5,
	TCATINSTLEVEL_CNCPTP		=6,
	TCATINSTLEVEL_KERNELDEBUG = 99,
	TCATINSTLEVEL_MAX
} TCATINSTLEVEL;


///////////////////////////////////////////////////////////////////////////////
#if defined(TC_ENVIRONMENT_RT) || defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT)  || defined(TC_ENVIRONMENT_OS)
#define DECLARE_OPERATOR_NEW_DELETE() \
	static PVOID _cdecl operator new( size_t n ); \
	static PVOID _cdecl operator new( size_t n, LPCSTR lpszFileName, int nLine ); \
	static PVOID _cdecl operator new [] ( size_t n ); \
	static PVOID _cdecl operator new [] ( size_t n, LPCSTR lpszFileName, int nLine ); \
	static VOID _cdecl operator delete( PVOID p ); \
	static VOID _cdecl operator delete( PVOID p, LPCSTR lpszFileName, int nLine ); \
	static VOID _cdecl operator delete [] ( PVOID p ); \
	static VOID _cdecl operator delete [] ( PVOID p, LPCSTR lpszFileName, int nLine ); 
#else
#define DECLARE_OPERATOR_NEW_DELETE()
#endif

#define POINTER_DIFF32(a, b)	((ULONG)((ULONG_PTR)(a)-(ULONG_PTR)(b)))
