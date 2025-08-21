///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "platform/Common/TcSdkDef.h"
#include "TcOsDefMacros.h"

#if defined (TC_ENVIRONMENT_OS)
#include "stdint.h"
#include "stddef.h"
#include "limits.h"
#include <malloc.h>

#ifdef TCOS_PRIVATE
#include "stdlib.h"
#include "stdio.h"
#endif // TCOS_PRIVATE
#endif

#ifdef TCOS_PRIVATE
#include "TcOsDefIntrin.h"
#include "TcOsDefCtx.h"
#include "TcOsDefNetwork.h"
#include "TcOsDefPriv.h"
#include "TcOsDefPci.h"
#include "TcOsSList.h"
#endif // TCOS_PRIVATE

#include "TcOsDefGuid.h"
#include "TcOsDefTime.h"
#include "TcOsLinkedList.h"

#include "platform/Common/TcSdkError.h"
#ifdef TCOS_PRIVATE
#include "TcOsDefError.h"
#include "TcOsDefFile.h"
#endif // TCOS_PRIVATE

#include "TcOsDefCom.h"

TCOSSYS_API void TCFRAMEWORKAPI DbgPrint(const char* pFmtStr, ...);

// intrin.h
EXTERN_C void   __cdecl _disable(void);
EXTERN_C void   __cdecl _enable(void);

#if !defined(ARM) || _MSC_VER > 1900
#pragma intrinsic(_disable)
#pragma intrinsic(_enable)
#else
#define _enable	TcHal_EnableIRQs
#define _disable	TcHal_DisableIRQs
#endif


typedef struct _SYSTEM_INFO {
	union {
		DWORD dwOemId;          // Obsolete field...do not use
		struct {
			WORD wProcessorArchitecture;
			WORD wReserved;
		};
	};
	DWORD dwPageSize;
	LPVOID lpMinimumApplicationAddress;
	LPVOID lpMaximumApplicationAddress;
	DWORD dwActiveProcessorMask;
	DWORD dwNumberOfProcessors;
	DWORD dwProcessorType;
	DWORD dwAllocationGranularity;
	WORD wProcessorLevel;
	WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;
