///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH & Co. KG
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TcDef.h"

#if defined(_X86_) || defined(_X64_)

#ifndef POSIX
#define TCSEH
#ifdef _X64_
#define SEH_FOR_X64
#endif // _X64_
#endif // !POSIX

#endif

#if defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT) || defined(TC_ENVIRONMENT_UM) 

///////////////////////////////////////////////////////////////////////////////
// Macro Definitions
///////////////////////////////////////////////////////////////////////////////
#define TcTry __try
#define TcExcept __except
#define TcFinally __finally
#define TcRaiseException RaiseException
#define TcShowExceptionRegistrationList(pPrefix)

#elif defined(TC_ENVIRONMENT_RT)	|| defined(TC_ENVIRONMENT_OS) || defined(POSIX) || defined(TCFRAMEWORK_TESTS)


#if defined TCSEH
///////////////////////////////////////////////////////////////////////////////
// Macro Definitions
///////////////////////////////////////////////////////////////////////////////
#define TcTry __try
#define TcExcept __except
#define TcFinally __finally


///////////////////////////////////////////////////////////////////////////////
// Function Declarations
///////////////////////////////////////////////////////////////////////////////

#if defined(_X86_)
VOID __stdcall
TcRaiseException
(
	DWORD dwExceptionCode,
	DWORD dwExceptionFlags,
	DWORD nNumberOfArguments,
	CONST ULONG_PTR *lpArguments
);
#else
VOID 
TcRaiseException
(
	DWORD dwExceptionCode,
	DWORD dwExceptionFlags,
	DWORD nNumberOfArguments,
	CONST ULONG_PTR *lpArguments
);
#endif

EXCEPTION_DISPOSITION 
TcDispatchException
(
	EXCEPTION_RECORD* pExceptionRecord,
	CONTEXT* pContext
);

#if defined(DEBUG) && defined(_X86_)
VOID 
DLL_EXPORT TCFRAMEWORKAPI TcShowExceptionRegistrationList
(
	PCCH pPrefix
);
#else
#define TcShowExceptionRegistrationList(pPrefix) 
#endif

#else
// TwinCAT SEH disabled
#define TcShowExceptionRegistrationList(pPrefix) 
#define TcTry 
#define TcExcept(X) if (FALSE)
#define TcFinally 
#define TcRaiseException
#define TcDispatchException(x,y)
#endif
#endif


///////////////////////////////////////////////////////////////////////////////
// Template functions to enable/disable calls to TcRaiseException at
// compile time.
///////////////////////////////////////////////////////////////////////////////
template<bool _Activator> inline void TcRaiseExceptionIfActivated(DWORD dwErrorCode) {TcRaiseException(dwErrorCode, EXCEPTION_NONCONTINUABLE, 0, NULL);}
// disabled: warning C4100: 'dwErrorCode' : unreferenced formal parameter
#pragma warning(suppress:4100)
template<> inline void TcRaiseExceptionIfActivated<false>(DWORD dwErrorCode) {}

template<bool _Activator> inline void TcConditionalRaiseExceptionIfActivated(bool bCondition, DWORD dwErrorCode)
{
	if(bCondition)
		TcRaiseExceptionIfActivated<true>(dwErrorCode);
}
// disabled: warning C4100: 'dwErrorCode' : unreferenced formal parameter
// disabled: warning C4100: 'bCondition' : unreferenced formal parameter
#pragma warning(suppress:4100)
template<> inline void TcConditionalRaiseExceptionIfActivated<false>(bool bCondition, DWORD dwErrorCode) {}

#ifdef _DEBUG
	#define TC_SEH_ERROR(nErrorCode) TcRaiseExceptionIfActivated<true>((DWORD)nErrorCode);
	#define TC_SEH_DEBUG_ERROR(nErrorCode) TC_SEH_ERROR(nErrorCode)
	#define TC_SEH_CONDITIONAL_ERROR(bCondition, nErrorCode) TcConditionalRaiseExceptionIfActivated<true>(bCondition, (DWORD)nErrorCode);
	#define TC_SEH_CONDITIONAL_DEBUG_ERROR(bCondition, nErrorCode) TC_SEH_CONDITIONAL_ERROR(bCondition, nErrorCode)
	#define TC_SEH_ERROR_DYNAMIC(nErrorCode) TC_SEH_ERROR(nErrorCode)
#else
	#define TC_SEH_ERROR(nErrorCode) TcRaiseExceptionIfActivated<((nErrorCode & TC_COMMON_SEH_DEBUG_ERROR_ID) == 0)>((DWORD)nErrorCode);
	#define TC_SEH_DEBUG_ERROR(nErrorCode) ;
	#define TC_SEH_CONDITIONAL_ERROR(bCondition, nErrorCode) TcConditionalRaiseExceptionIfActivated<((nErrorCode & TC_COMMON_SEH_DEBUG_ERROR_ID) == 0)>(bCondition, (DWORD)nErrorCode);
	#define TC_SEH_CONDITIONAL_DEBUG_ERROR(bCondition, nErrorCode) ;
	#define TC_SEH_ERROR_DYNAMIC(nErrorCode) {if((nErrorCode & TC_COMMON_SEH_DEBUG_ERROR_ID) == 0) TcRaiseExceptionIfActivated<true>(nErrorCode);}
#endif

#define TC_SEH_BUGVERIFY(bCondition, nFacilityCode) TC_SEH_CONDITIONAL_DEBUG_ERROR(!(bCondition), TCMAKE_STATUS_CODE(nFacilityCode, TC_COMMON_SEH_ASSERTION_FAILED_ID | TC_COMMON_SEH_DEBUG_ERROR_ID))
#define TC_SEH_ASSERT(bCondition, nFacilityCode) TC_SEH_BUGVERIFY(bCondition, nFacilityCode)
