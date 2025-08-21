///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"

// {4C256767-E6E6-4AF5-BD68-9F7ABAD0C200}
static const GUID TC_LICENSEID_BASE = 
{ 0x4c256767, 0xe6e6, 0x4af5, { 0xbd, 0x68, 0x9f, 0x7a, 0xba, 0xd0, 0xc2, 0x0 } };
// {3FF18E97-7754-401B-93FB-70544DE28A13}
static const GUID TC_LICENSEID_IO = 
{ 0x3FF18E97, 0x7754, 0x401B, { 0x93, 0xFB, 0x70, 0x54, 0x4D, 0xE2, 0x8A, 0x13 } };
// {66689887-CCBD-452C-AC9A-039D997C6E66}
static const GUID TC_LICENSEID_PLC30 = 
{ 0x66689887, 0xccbd, 0x452c, { 0xac, 0x9a, 0x3, 0x9d, 0x99, 0x7c, 0x6e, 0x66 } };
// {304D006A-8299-4560-AB79-438534B50288}
static const GUID TC_LICENSEID_CPP = 
{ 0x304d006a, 0x8299, 0x4560, { 0xab, 0x79, 0x43, 0x85, 0x34, 0xb5, 0x2, 0x88 } };
// {AD7F40C3-F160-4413-83E3-6B7656A795A2}
static const GUID TC_LICENSEID_MATLAB = 
{ 0xad7f40c3, 0xf160, 0x4413, { 0x83, 0xe3, 0x6b, 0x76, 0x56, 0xa7, 0x95, 0xa2 } };

const		ULONG		DrvID_TcRouter					= 0x01000000;

// class IDs
TCOM_DECL_CLASS(CID_TCROUTER_CTRL, DrvID_TcRouter)
TCOM_DECL_CLASS(CID_TCROUTER_LOADER, DrvID_TcRouter + 0x0001)
TCOM_DECL_CLASS(CID_TCROUTER_TASK, DrvID_TcRouter + 0x0010)
TCOM_DECL_CLASS(CID_TCEVENTLOGGER, DrvID_TcRouter + 0x0070)

// object IDs
const		OTCID		OID_TCROUTER_CTRL				= DrvID_TcRouter;
const		OTCID		OID_TCROUTER_DRVLDR			= DrvID_TcRouter + 0x0001;
const		OTCID		OID_TCROUTER_TASK				= DrvID_TcRouter + 0x0010;
const		OTCID		OID_TCROUTER_DEBUGGERPORT	= DrvID_TcRouter + 0x0020;
const		OTCID		OID_TCROUTER_DEBUGGERBP		= DrvID_TcRouter + 0x0021;
const		OTCID		OID_TCROUTER_DEBUGGERBPPOOL= DrvID_TcRouter + 0x0022;
const		OTCID		OID_TCEVENTLOGGER				= DrvID_TcRouter + 0x0070;

// object names

#define NAME_TCROUTER_TASK				"TComServerTask"
#define NAME_TCROUTER_DEBUGGERPORT	"TcDebuggerPort"

// interface IDs
TCOM_DECL_INTERFACE("01000000-0000-0000-e000-000000000064", ITComRouter)
TCOM_DECL_INTERFACE("01000001-0000-0000-e000-000000000064", ITComPort)
TCOM_DECL_INTERFACE("01000002-0000-0000-e000-000000000064", ITComRouterMemory)
TCOM_DECL_INTERFACE("01000003-0000-0000-e000-000000000064", ITcSearchPciBus)
TCOM_DECL_INTERFACE("01000004-0000-0000-e000-000000000064", ITComRouterMemory2)
TCOM_DECL_INTERFACE("01000100-0000-0000-e000-000000000064", IQueueOwner)
TCOM_DECL_INTERFACE("01000200-0000-0000-e000-000000000064", ITComEventServer)
TCOM_DECL_INTERFACE("01000201-0000-0000-e000-000000000064", ITComEventConsumer)

TCOM_DECL_INTERFACE("BCCA22A6-3593-4A6B-98E9-ABCA96076949", ITcCodeAreaProvider)

// category ids
const		CATTCID	CATID_TComServer_EarlyShutdown			= DrvID_TcRouter | 0x0001;
const		CATTCID	CATID_TComServer_LateShutdown				= DrvID_TcRouter | 0x0002;
const		CATTCID	CATID_TComServer_NotifyBeforeShutdown	= DrvID_TcRouter | 0x0003;
const		CATTCID	CATID_TComServer_CodeAreaProvider		= DrvID_TcRouter | 0x0004;
const		CATTCID	CATID_TComServer_AdsSymbolServer			= DrvID_TcRouter | 0x0005;

// parameter IDs
const		PTCID		PID_AmsPortInitData							= DrvID_TcRouter | 0x0001;
const		PTCID		PID_NotificationBeforeShutdown			= DrvID_TcRouter | 0x0002;
const		PTCID		PID_ShutdownActive							= DrvID_TcRouter | 0x1000;

// event IDs
const		ULONG		EVTID_TComServer_ObjAdded		= DrvID_TcRouter | 0x8001;
const		ULONG		EVTID_TComServer_ObjRemoved	= DrvID_TcRouter | 0x8002;

const		ULONG		EVTID_TComServer_EvtSrvShutdown			= DrvID_TcRouter | 0x8010;
const		ULONG		EVTID_TComServer_EvtSrvSignalStopping	= DrvID_TcRouter | 0x8011;

#define	TCOMSRV_EVTFLAG_RECURSIVE	0x80000000
#define	TCOMSRV_EVTFLAG_EVTID		0x0FFFFFFF