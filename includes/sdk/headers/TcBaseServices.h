///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "TcDef.h"

typedef	ULONG		OTCID, * POTCID;		// Object ID
typedef	CLSID		CTCID, * PCTCID;		// Class ID
typedef	REFCLSID	RCTCID;
typedef	IID		ITCID, * PITCID;		// Interface ID
typedef	REFIID	RITCID;
typedef	CLSID		FTCID, * PFTCID;		// Func ID
typedef	REFCLSID	RFTCID;

#ifndef DECLSPEC_NOVTABLE
#define DECLSPEC_NOVTABLE __declspec(novtable)
#endif

#if defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

#ifndef TCFRAMEWORK_EXTERN_IID_DEFINITION
#define	TCOM_DECL_INTERFACE(GID, ITF)	\
struct	__declspec(uuid(GID)) DECLSPEC_NOVTABLE ITF;	\
extern const		ITCID		IID_ ## ITF;
#else
#define	TCOM_DECL_INTERFACE(GID, ITF)	\
struct	__declspec(uuid(GID)) DECLSPEC_NOVTABLE ITF;	\
extern const		ITCID		IID_ ## ITF = __uuidof(ITF);
#endif

#else	// defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

#define	TCOM_DECL_INTERFACE(GID, ITF)	\
struct	__declspec(uuid(GID)) DECLSPEC_NOVTABLE ITF;	\
const		ITCID		IID_ ## ITF = __uuidof(ITF);
#endif // defined(TCFRAMEWORK_EXTERN_IID_DECLARATION)

///////////////////////////////////////////////////////////////////////////////
// Interface IDs
TCOM_DECL_INTERFACE("00000001-0000-0000-e000-000000000064", ITcUnknown)
