///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"

const		ULONG		DrvID_TcRt								= 0x02000000;

TCOM_DECL_CLASS(CID_TCRTIME_CTRL, DrvID_TcRt | 0x0000)

TCOM_DECL_INTERFACE("02000002-0000-0000-e000-000000000064", ITcTask)
TCOM_DECL_INTERFACE("02000003-0000-0000-e000-000000000064", ITcRTimeTask)
TCOM_DECL_INTERFACE("02000004-0000-0000-e000-000000000064", ITcDebugTask)
TCOM_DECL_INTERFACE("02000005-0000-0000-e000-000000000064", ITcCriticalSectionProvider)
TCOM_DECL_INTERFACE("0200000A-0000-0000-e000-000000000064", ITcCriticalSectionProvider2)
TCOM_DECL_INTERFACE("0200000B-0000-0000-e000-000000000064", ITcRTimeExcpHandler)
TCOM_DECL_INTERFACE("0200000C-0000-0000-e000-000000000064", ITcRTimeDbg)
TCOM_DECL_INTERFACE("0200000E-0000-0000-e000-000000000064", ITcDebugState)
TCOM_DECL_INTERFACE("0200000F-0000-0000-e000-000000000064", ITcRTimeRegisterExcpHandler)
TCOM_DECL_INTERFACE("02000010-0000-0000-e000-000000000064", ITcRTime)
TCOM_DECL_INTERFACE("02000011-0000-0000-e000-000000000064", ITcModuleState)
TCOM_DECL_INTERFACE("02000100-0000-0000-e000-000000000064", ITaskCtrl)
TCOM_DECL_INTERFACE("9CDE7C78-32A0-4375-827E-924B31021FCD", ITcTaskNotification)
TCOM_DECL_INTERFACE("90E779BB-5754-4180-BAFF-14C8892E5DDE", ITcJobCaller);
TCOM_DECL_INTERFACE("B6ED365E-9146-439A-94A0-E5D91DF00469", ITcJob);

const		OTCID		OID_TCRTIME_CTRL						= DrvID_TcRt | 0x0000;
const		OTCID		OID_TCRTIME_TASK_BEGIN				= DrvID_TcRt | 0x0100;
const		OTCID		OID_TCRTIME_TASK_END					= DrvID_TcRt | 0x01FF;


#ifndef TASKTYPE_UNDEFINED
#define	TASKTYPE_UNDEFINED				0
#define	TASKTYPE_CYCLETASK				1
#define	TASKTYPE_SEMATASK					2
#define	TASKTYPE_QUEUETASK				3
#define	TASKTYPE_AMSSEMATASK				4
#define	TASKTYPE_CYCLETASKWITHEXTIRQ	5
#endif

#define	TASKFLAG_UNDEFINED				0x00000000
#define	TASKFLAG_START_SUSPENDED		0x00000001
#define	TASKFLAG_WITHEXTIRQ				0x00000002

const		ULONG		TCRTTLSTYPE_TaskDef								= DrvID_TcRt | 0x0001;
const		ULONG		TCRTTLSTYPE_ITcRTimeTask						= DrvID_TcRt | 0x0002;
const		ULONG		TCRTTLSTYPE_ITcAdsInvoker						= DrvID_TcRt | 0x0003;
const		ULONG		TCRTTLSTYPE_ITcModuleState						= DrvID_TcRt | 0x0004;
const		ULONG		TCRTTLSTYPE_ITcWatchdogStack					= DrvID_TcRt | 0x0005;
const		ULONG		TCRTTLSTYPE_ITcJobCalleeInfo					= DrvID_TcRt | 0x0006;
const		ULONG		TCRTTLSTYPE_ITcOpenMPHandler					= DrvID_TcRt | 0x0007;
const		ULONG		TCRTTLSTYPE_ITcBufferedDebugPrint			= DrvID_TcRt | 0x0008;
const		ULONG		TCRTTLSTYPE_ITcOpenMPMaster					= DrvID_TcRt | 0x0009;

typedef struct TTcRtTaskAccount
{
	ULONG		nCycle;
	ULONG		nAccountNetto;
	ULONG		nAccountBrutto;
	ULONG		nReserved;
} TcRtTaskAccount, *PTcRtTaskAccount;

typedef struct
{
	ULONG		nBaseTick;
	ULONG		nAccountNetto;
	ULONG		nAccountNtMax;
	ULONG		nAccountJob;
	ULONG		nAccountJobMax;
	ULONG		nReserved[2];
	ULONG		nExecutedJobs;
	ULONG		nPendingJobs;
} TcRtJobTaskAccount;

const		PTCID		PID_RT_CycleTimeNS					= DrvID_TcRt | 0x1001;	// ns based
const		PTCID		PID_RT_Priority						= DrvID_TcRt | 0x1002;
const		PTCID		PID_RT_TaskType						= DrvID_TcRt | 0x1003;	// see: TASKTYPE_xxxxx
const		PTCID		PID_RT_TaskFlags						= DrvID_TcRt | 0x1004;	// see: TASKFLAG_xxxxx
const		PTCID		PID_RT_ExceedCounter					= DrvID_TcRt | 0x1005;
const		PTCID		PID_RT_TaskAccount					= DrvID_TcRt | 0x1006;
const		PTCID		PID_RT_TaskAffinity					= DrvID_TcRt | 0x1007;
const		PTCID		PID_RT_TaskPort						= DrvID_TcRt | 0x1008;
const		PTCID		PID_RT_CycleTime2NS					= DrvID_TcRt | 0x1009;	// ns based
const		PTCID		PID_RT_TaskWatchdog					= DrvID_TcRt | 0x100A;	// in cycles
const		PTCID		PID_RT_TaskCpuId						= DrvID_TcRt | 0x100B;
const		PTCID		PID_RT_TaskTickModulo				= DrvID_TcRt | 0x100C;
const		PTCID		PID_RT_TaskAffinity64				= DrvID_TcRt | 0x100D;
const		PTCID		PID_RT_ExceedWarning					= DrvID_TcRt | TCOMINITDATAELM_IOFFS_OPTIONAL | 0x100E;
const		PTCID		PID_RT_FpException					= DrvID_TcRt | TCOMINITDATAELM_IOFFS_OPTIONAL | 0x100F;
const		PTCID		PID_RT_InputUpdatePreTicks			= DrvID_TcRt | 0x1010;	
const		PTCID		PID_RT_AmsSymbolDownload1			= DrvID_TcRt | 0x1011;	
const		PTCID		PID_RT_AmsSymbolDownload2			= DrvID_TcRt | 0x1012;	
const    PTCID    PID_RT_EnablePerfData				= DrvID_TcRt | 0x1013;
const    PTCID    PID_RT_WatchdogStackCapacity		= DrvID_TcRt | TCOMINITDATAELM_IOFFS_OPTIONAL | 0x1014;
const		PTCID		PID_RT_JobTaskAccount				= DrvID_TcRt | 0x1015;
const		PTCID		PID_RT_AmsSymbolDownload3			= DrvID_TcRt | 0x1016;	
const		PTCID		PID_RT_TaskStackUsage				= DrvID_TcRt | 0x1017;
const		PTCID		PID_RT_TComObjectMarks				 = DrvID_TcRt | 0x1100;

#define	TCRTIME_OID_TASK(prio)	(OID_TCRTIME_TASK_BEGIN + prio)

#define	FACILITY_TC_RTOS               0x1841
inline	HRESULT	MAKE_RTOS_HRESULT( ULONG code )
	{	return (code==0) ? S_OK : MAKE_HRESULT(0, FACILITY_TC_RTOS, (code&(~0x80000000)))|((~code)&0x80000000); }
