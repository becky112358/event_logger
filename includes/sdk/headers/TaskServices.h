///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include	"Ams.h"

///////////////////////////////////////////////////////////////////////////////

#define	AMS_TASK_START						(0	+ AMS_TASKCMDS)
#define	AMS_TASK_STOP						(1	+ AMS_TASKCMDS)
#define	AMS_TASK_TRIGGERSEMA				(2	+ AMS_TASKCMDS)
#define	AMS_TASK_TRIGGERQUEUE			(3	+ AMS_TASKCMDS)
#define	AMS_TASK_EXCEEDWRN				(4	+ AMS_TASKCMDS)
#define  AMS_TASK_START64					(5 + AMS_TASKCMDS)

#define	TASKTYPE_UNDEFINED				0
#define	TASKTYPE_CYCLETASK				1
#define	TASKTYPE_SEMATASK					2
#define	TASKTYPE_QUEUETASK				3
#define	TASKTYPE_AMSSEMATASK				4
#define	TASKTYPE_CYCLETASKWITHEXTIRQ	5

#pragma pack( push, 1 )
typedef struct
{
	AmsHead		head;
	USHORT		taskType;
	USHORT		prior;
	union
	{
		ULONG	cycleTime;
		ULONG	queueSize;
	};
	ULONG			affinity;
} AmsStartTaskCmd, *PAmsStartTaskCmd;
#define	SIZEOF_AmsStartTaskCmd(p)		( sizeof(AmsStartTaskCmd) )
#define	CBDATA_AmsStartTaskCmd(p)		( SIZEOF_AmsStartTaskCmd(p)-sizeof(AmsHead) )

struct AmsStartTaskCmd64 : AmsStartTaskCmd
{
	ULONG			affinityHi;
};
#define	SIZEOF_AmsStartTaskCmd64(p)	( sizeof(AmsStartTaskCmd64) )
#define	CBDATA_AmsStartTaskCmd64(p)	( SIZEOF_AmsStartTaskCmd64(p)-sizeof(AmsHead) )

typedef struct
{
	AmsHead		head;
	ULONG			queueItem;
} AmsTriggerQueueCmd, *PAmsTriggerQueueCmd;
#define	SIZEOF_AmsTriggerQueueCmd(p)	( sizeof(AmsTriggerQueueCmd) )
#define	CBDATA_AmsTriggerQueueCmd(p)	( SIZEOF_AmsTriggerQueueCmd(p)-sizeof(AmsHead) )

typedef struct
{
	AmsHead		head;
	ULONG			exceedWarning;
} AmsTaskExceedWrnCmd, *PAmsTaskExceedWrnCmd;
#define	SIZEOF_AmsTaskExceedWrnCmd(p)	( sizeof(AmsTaskExceedWrnCmd) )
#define	CBDATA_AmsTaskExceedWrnCmd(p)	( SIZEOF_AmsTaskExceedWrnCmd(p)-sizeof(AmsHead) )

#pragma pack( pop )
