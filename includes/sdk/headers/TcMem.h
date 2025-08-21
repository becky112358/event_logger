///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"

#if defined (TC_ENVIRONMENT_OS)
#define TCMEM_DLL_EXPORT TCOSSYS_API
#else
#define TCMEM_DLL_EXPORT DLL_EXPORT
#endif

TCMEM_DLL_EXPORT PVOID TCFRAMEWORKAPI TcMemAllocate(size_t nSize, LPCSTR lpszFileName = NULL, int nLine = 0);
TCMEM_DLL_EXPORT PVOID TCFRAMEWORKAPI TcMemReallocate(PVOID pMem, size_t nSize, LPCSTR lpszFileName = NULL, int nLine = 0);
TCMEM_DLL_EXPORT VOID TCFRAMEWORKAPI TcMemFree(PVOID pMem);
TCMEM_DLL_EXPORT INT_PTR TCFRAMEWORKAPI TcMemMaxAvailableRtMem(bool bAll);
