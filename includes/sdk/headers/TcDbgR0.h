///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"

#define DEBUG_TRAP	{TRACE(_T("Break at function %s, line %u in file %s \n"), __FUNCTION__, __LINE__, __FILE__);  __debugbreak();}

#ifdef DEBUG
	#define	RTTRACE_ENABLED		0		// include code for debug tracing 
#else
	#define	RTTRACE_ENABLED		0		// always disable tracing in release version
#endif

EXTERN_C void _cdecl DbgFatalSound();
EXTERN_C void _cdecl DbgMsgSound();

#if defined(DEBUG) && defined(UNDER_CE) && defined(TCFRAMEWORK_EXPORTS)
#define TC_ASSERT_EXPORT _declspec(dllexport) 
#else
#define TC_ASSERT_EXPORT
#endif

EXTERN_C void TC_ASSERT_EXPORT _cdecl TcAssert(const char*, const char*, unsigned int);

///////////////////////////////////////////////////////////////////////////////
#if RTTRACE_ENABLED				// DEBUG and TRACE
///////////////////////////////////////////////////////////////////////////////
#include "Ams.h"
#include "TraceServices.h"

extern	PTraceVxdFuncs g_pTraceFuncs;		// Pointer to trace service functions

#define TRACE_ASSERT(x)								if ( !(x) && g_pTraceFuncs )		g_pTraceFuncs->pLogAssert( g_pTraceFuncs->pThis, (PBYTE)__FILE__, (WORD)__LINE__ );
#define TRACE_MSG( szMsg )							if ( g_pTraceFuncs )					g_pTraceFuncs->pLogMsg(		g_pTraceFuncs->pThis, szMsg );
#define TRACE_INT( osTime )						if ( g_pTraceFuncs )					g_pTraceFuncs->pLogInt(		g_pTraceFuncs->pThis, osTime );
#define TRACE_CTXSW( nPrioFrom, nPrioTo )		if ( g_pTraceFuncs )					g_pTraceFuncs->pLogCtxSw(	g_pTraceFuncs->pThis, nPrioFrom, nPrioTo  );

#define BUGERR(x)				if( !(x) )	{	TRACE_ASSERT(0); \
														DbgFatalSound(); \
														DbgPrint("\nBUGERR: %s : %d\n", __FILE__, __LINE__ ); \
														KeBugCheckEx(0x0000AFFE, (unsigned long)__LINE__, 0x0, 0x0, 0x0); \
													}
#define BUGERR_FNAME(x, pFileName)	if( !(x) ) {	char* pTmp=pFileName; \
														if ( pTmp == NULL	) \
															pTmp = "NONAME"; \
														DbgFatalSound(); \
														DbgPrint("\nBUGERR: %s : %d\n", __FILE__, __LINE__ ); \
														KeBugCheckEx(0x0000AFFE, (unsigned long)__LINE__, \
														*(ULONG*)pTmp,	  \
														*(ULONG*)&pTmp[4], \
														*(ULONG*)&pTmp[8]); \
													}
#define BUGWRN(x, szMsg)	if( !(x) )	{	TRACE_MSG((PBYTE)szMsg); \
														DbgMsgSound(); \
														DbgPrint("\nBUGWRN: %s Line: %d\n\"%s\"\n", __FILE__, __LINE__, szMsg ); \
													}
#define BUGMSG(x, szMsg)	if( !(x) )	{	TRACE_MSG((PBYTE)szMsg); \
														DbgPrint("\nBUGMSG: %s Line: %d\n\"%s\"\n", __FILE__, __LINE__, szMsg ); \
													}

///////////////////////////////////////////////////////////////////////////////
#elif defined(DEBUG)	&& defined(TC_ENVIRONMENT_RT)
///////////////////////////////////////////////////////////////////////////////
#ifndef ASSERT
	#define ASSERT(_Expression) (void)( (!!(_Expression)) || (TcAssert(#_Expression, __FILE__, __LINE__), 0) )
#endif
#define VERIFY(x)					((void)(x))
#define TRACE_ASSERT(x)
#define TRACE_MSG( szMsg )
#define TRACE_INT( osTime )
#define TRACE_CTXSW( nPrioFrom, nPrioTo )
#define BUGERR(x)				if( !(x) ) {	char* pTmp, *pFileName; \
														pTmp = pFileName = __FILE__; \
														while ( *pTmp ) \
														{ \
															if ( *pTmp == '\\' || *pTmp == '/' ) \
																pFileName = pTmp + 1; \
															pTmp++; \
														} \
														DbgPrint("\nBUGERR: %s : %d\n", __FILE__, __LINE__ ); \
														KeBugCheckEx(0x0000AFFE, (unsigned long)__LINE__, \
														*(ULONG*)pFileName,	  \
														*(ULONG*)&pFileName[4], \
														*(ULONG*)&pFileName[8]); \
													}
#define BUGVERIFY(x)			BUGERR(x)

#define BUGWRN(x, szMsg)	if( !(x) )	{	\
														DbgPrint("\nBUGWRN: %s Line: %d\n\"%s\"\n", __FILE__, __LINE__, szMsg ); \
													}
#define BUGBREAK(x, szMsg)	if( !(x) )	{	\
														DbgPrint("\nBUGBREAK: %s Line: %d\n\"%s\"\n", __FILE__, __LINE__, szMsg ); \
														__debugbreak(); \
													}
#define BUGMSG(x, szMsg)	if( !(x) )	{	\
														DbgPrint("\nBUGMSG: %s Line: %d\n\"%s\"\n", __FILE__, __LINE__, szMsg ); \
													}

///////////////////////////////////////////////////////////////////////////////
#elif defined(DEBUG)	&& (defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_CE_RT))
///////////////////////////////////////////////////////////////////////////////
#if !defined(_AFXDLL) && !defined(__DBGAPI_H__) 
#include <assert.h>
#ifndef ASSERT
	#define ASSERT(x)					assert(x)
#endif
#define VERIFY(x)					assert(x)
#define TRACE_ASSERT(x)			assert(x)
#define TRACE_MSG( szMsg )
#define TRACE_INT( osTime )
#define TRACE_CTXSW( nPrioFrom, nPrioTo )
#endif
#define BUGERR(x)					ASSERT(x)
#define BUGERR_FNAME(x, y)		ASSERT(x)
#define BUGWRN(x, szMsg)      if( !(x) )	{	\
															DbgPrint(_T("%hs(%d) : BUGWRN \"%hs\"\n"), __FILE__, __LINE__, szMsg ); \
														}
#if !defined(TC_ENVIRONMENT_CE_RT)
#define BUGBREAK(x, szMsg)    if( !(x) )	{	\
															DbgPrint(_T("%hs(%d) : BUGBREAK \"%hs\"\n"), __FILE__, __LINE__, szMsg ); \
															__debugbreak(); \
														}
#else
//__debugbreak() would crash the whole system in the RTOS context
#define BUGBREAK(x, szMsg)    if( !(x) )	{	\
															DbgPrint(_T("%hs(%d) : BUGBREAK \"%hs\"\n"), __FILE__, __LINE__, szMsg ); \
														}
#endif

#define BUGMSG(x, szMsg)      if( !(x) )	{	\
															DbgPrint(_T("%hs(%d) : BUGMSG \"%hs\"\n"), __FILE__, __LINE__, szMsg ); \
														}
#define BUGVERIFY(x)				ASSERT(x)
///////////////////////////////////////////////////////////////////////////////

#elif defined(TC_ENVIRONMENT_OS) && defined(DEBUG)
#ifndef ASSERT
	#define ASSERT(x)
#endif

#define VERIFY(x) ASSERT(x)
#define TRACE_ASSERT(x)
#define TRACE_MSG( szMsg ) TRACE(szMsg)
#define TRACE_INT( osTime )
#define TRACE_CTXSW( nPrioFrom, nPrioTo )
#define BUGERR(x)                            ASSERT(x)
#define BUGERR_FNAME(x, y)                   ASSERT(x)
#define BUGWRN(x, szMsg)                     if (!(x)) TRACE(_T("%hs(%d): Warning, %s\n"), __FILE__, __LINE__, szMsg)
#define BUGBREAK(x, szMsg)                   if (!(x)) TRACE(_T("Error, %s"), szMsg)
#define BUGMSG(x, szMsg)                     if (!(x)) TRACE(_T("%hs(%d): Warning, %s\n"), __FILE__, __LINE__, szMsg)
#define BUGVERIFY(x)                         ASSERT(x)
#else							// neither DEBUG nor TRACE
///////////////////////////////////////////////////////////////////////////////
#if !defined(_AFXDLL) && !defined(__DBGAPI_H__) 
#ifndef ASSERT
	#define ASSERT(x)
#endif
#define VERIFY(x)					((void)(x))
#define TRACE_ASSERT(x)
#define TRACE_MSG( szMsg )
#define TRACE_INT( osTime )
#define TRACE_CTXSW( nPrioFrom, nPrioTo )
#endif
#define BUGERR(x)
#define BUGERR_FNAME(x, y)
#define BUGWRN(x, szMsg)
#define BUGBREAK(x, szMsg)
#define BUGMSG(x, szMsg)
#define BUGVERIFY(x)

#endif//if DBGTRACE_ENABLED
