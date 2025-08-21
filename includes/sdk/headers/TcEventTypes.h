///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

typedef enum TcEventFlags
{
#ifndef __cplusplus
	[helpstring("event request, create new event")]
#endif
	TCEVENTFLAG_REQ				=0x0001,					
#ifndef __cplusplus
	[helpstring("event request, has to be confirmed")]
#endif
	TCEVENTFLAG_REQMUSTCON		=0x0002,					
#ifndef __cplusplus
	[helpstring("event confirmation, confirm an event")]
#endif
	TCEVENTFLAG_CON				=0x0004,					
#ifndef __cplusplus
	[helpstring("event reset by source")]
#endif
	TCEVENTFLAG_RESET				=0x0008,					
#ifndef __cplusplus
	[helpstring("event class/priority is set by formatter")]
#endif
	TCEVENTFLAG_PRIOCLASS		=0x0010,					
#ifndef __cplusplus
	[helpstring("language dependant text format in message")]
#endif
	TCEVENTFLAG_FMTSELF			=0x0020,	// format in message
#ifndef __cplusplus
	[helpstring("write to log file")]
#endif
	TCEVENTFLAG_LOG				=0x0040,	// write to log file
#ifndef __cplusplus
	[helpstring("display message box")]
#endif
	TCEVENTFLAG_MSGBOX			=0x0080,	// display message box
#ifndef __cplusplus
	[helpstring("src id instead of source name")]
#endif
	TCEVENTFLAG_SRCID				=0x0100,	// src id instead of source name
#ifndef __cplusplus
	[helpstring("event resets itself")]
#endif
	TCEVENTFLAG_SELFRESET		=0x0200,	// event resets itself
#ifndef __cplusplus
	[helpstring("tcid id instead of source name")]
#endif
	TCEVENTFLAG_TCID				=0x0400,	// tc id instead of source name
#ifndef __cplusplus
	[helpstring("signals an existing event")]
#endif
	TCEVENTFLAG_SIGNAL			=0x0800,	// signals an existing event
#ifndef __cplusplus
	[helpstring("Automatic formatting. All available data is read from event configuration")]
#endif
	TCEVENTFLAG_AUTOFMTALL		=0x1000,	// automatic formatting
#ifndef __cplusplus
	[helpstring("Use eventlogger ADS protocol v2")]
#endif
	TCEVENTFLAG_EX					 =0x2000,	// automatic formatting
#ifndef __cplusplus
	[helpstring("generated via ADS call")]
#endif
	TCEVENTFLAG_ADS				=0x8000,	// event is generated via ads
#ifndef __cplusplus
	[helpstring("dont use formatter")]
#endif
	TCEVENTFLAG_STRING				=0x10000,	// Dont use Formatter; eventparameters contain message string.
#ifndef __cplusplus
		[helpstring("TcCOM source")]
#endif
	TCEVENTFLAG_TCCOM					=0x20000,	// TcCOM source: fixed formatter 'TcEventFormatter.TcXmlFormatter', 
} TcEventFlags;

const LONG TCEVENT_SRCNAMESIZE	=16;
const LONG TCEVENT_FMTPRGSIZE		=32;

typedef enum TcEventStreamType
{
#ifndef __cplusplus
	[helpstring("invalid event stream")]
#endif
	TCEVENTSTREAM_INVALID			=0,
#ifndef __cplusplus
	[helpstring("no source name, no prog id")]
#endif
	TCEVENTSTREAM_SIMPLE				=1,
#ifndef __cplusplus
	[helpstring("source name and prog id")]
#endif
	TCEVENTSTREAM_NORMAL				=2,
#ifndef __cplusplus
	[helpstring("no source name, but prog id")]
#endif
	TCEVENTSTREAM_NOSOURCE			=3,
#ifndef __cplusplus
	[helpstring("source name and class id")]
#endif
	TCEVENTSTREAM_CLASSID			=4,
#ifndef __cplusplus
	[helpstring("no source name but class id")]
#endif
	TCEVENTSTREAM_CLSNOSRC			=5,
#ifndef __cplusplus
	[helpstring("read count of event of class <TcEventClass>")]
#endif
	TCEVENTSTREAM_READCLASSCOUNT	=6,
#ifndef __cplusplus
	[helpstring("not defined, internal only")]
#endif
	TCEVENTSTREAM_MAXTYPE				
} TcEventStreamType, *PTcEventStreamType;

typedef enum TcEventLogIGrps
{
	TCEVENTLOGIGRP_LOGCTRL			=100,
	TCEVENTLOGIGRP_GETCONFIG		=200,
	TCEVENTLOGIGRP_ENUMEVENT	= 400,
	TCEVENTLOGIGRP_GETTEXT		= 500,
	TCEVENTLOGIGRP_SUMUPWRITE	= 0x8081
} TcEventLogIGrps;

typedef enum TcEventLogCtrlIOffs
{
	TCEVENTLOGIOFFS_CLEARACTIVE	=1,
	TCEVENTLOGIOFFS_CLEARLOGGED	=2,
	TCEVENTLOGIOFFS_CLEARALL		=3,
	TCEVENTLOGIOFFS_CLEAREVENT		=4,		
	TCEVENTLOGIOFFS_CLEAREVENTSRCID = 5,
	TCEVENTLOGIOFFS_CLEARDEVICE = 6
} TcEventLogCtrlIOffs;

typedef enum TcEventEnumEventIOffs
{	
	TCEVENTLOGIOFFS_ENUMACTIVE	= 0x0001,
	TCEVENTLOGIOFFS_ENUMLOGGED	= 0x0002,
	TCEVENTLOGIOFFS_CNT_ACTIVE	= 0x0101,
	TCEVENTLOGIOFFS_CNT_LOGGED	= 0x0102,
}	TcEventEnumEventIOffs;

typedef enum TcEventLogGetTextIOffs
{	
	TCEVENTLOGIOFFS_GETCOMPLETESTRING	= 0,
	TCEVENTLOGIOFFS_GETSOURCENAME			= 1
}	TcEventLogGetTextIOffs;


typedef enum TcEventClass
{
	TCEVENTCLASS_NONE				=0,
	TCEVENTCLASS_MAINTENANCE	=1,
	TCEVENTCLASS_MESSAGE			=2,
	TCEVENTCLASS_HINT				=3,
	TCEVENTCLASS_STATEINFO		=4,
	TCEVENTCLASS_INSTRUCTION	=5,
	TCEVENTCLASS_WARNING			=6,
	TCEVENTCLASS_ALARM			=7,
	TCEVENTCLASS_PARAMERROR		=8,
	TCEVENTCLASS_MAX
} TcEventClass, *PTcEventClass;

typedef enum TcEventConCodes
{
	TCEVENTCON_OK				=0,
	TCEVENTCON_ABORT			=1,
	TCEVENTCON_IGNORE			=2,
	TCEVENTCON_RETRY			=3
} TcEventConCodes, *PTcEventConCodes;

typedef enum TcEventError
{
#ifndef __cplusplus
	[helpstring("event object is not initialized")]
#endif
	TCEVENTERR_NOERROR		=0x00000000,
#ifndef __cplusplus
	[helpstring("event object is in signaled state")]
#endif
	TCEVENTERR_ISSIGNALED	=0x98210001,
#ifndef __cplusplus
	[helpstring("event object is reset state")]
#endif
	TCEVENTERR_ISCONFIRMED	=0x98210002,
#ifndef __cplusplus
	[helpstring("event object is confirmed but not reset")]
#endif
	TCEVENTERR_ISRESET		=0x98210003,
#ifndef __cplusplus
	[helpstring("event object is confirmed but not reset")]
#endif
	TCEVENTERR_RESETCON		=0x98210004,
#ifndef __cplusplus
	[helpstring("event object is confirmed but not reset")]
#endif
	TCEVENTERR_NOCONFIRM		=0x98210005,
#ifndef __cplusplus
	[helpstring("reset or confirm for unknown event")]
#endif
	TCEVENTERR_NOTFOUND		=0x98210006,
#ifndef __cplusplus
	[helpstring("event is loaded from persistent storage")]
#endif
	TCEVENTERR_ISPERSISTENT =0x98210007,
#ifndef __cplusplus
	[helpstring("event configuration could be retrieved from the storage")]
#endif
	TCEVNETERR_EVENTCONFIGNOTFOUND =0x98210008,
#ifndef __cplusplus
	[helpstring("could not access storage")]
#endif
	TCEVNETERR_STGACCESS		=0x98210009,
#ifndef __cplusplus
	[helpstring("limit error codes, internal only"),hidden]
#endif
	TCEVENTERR_MAXERROR
} TcEventError, *PTcEventError;

typedef enum TcEventStates
{
#ifndef __cplusplus
	[helpstring("event object is not initialized")]
#endif
	TCEVENTSTATE_INVALID		=0x00,
#ifndef __cplusplus
	[helpstring("event object is in signaled state")]
#endif
	TCEVENTSTATE_SIGNALED	=0x01,
#ifndef __cplusplus
	[helpstring("event object is reset state")]
#endif
	TCEVENTSTATE_RESET		=0x02,
#ifndef __cplusplus
	[helpstring("event object is confirmed but not reset")]
#endif
	TCEVENTSTATE_CONFIRMED	=0x10,
#ifndef __cplusplus
	[helpstring("event object is confirmed and reset")]
#endif
	TCEVENTSTATE_RESETCON	=0x12
} TcEventStates, *PTcEventStates;

typedef enum TcEventPriority
{
	TCEVENTPRIO_IMPLICIT			=0
} TcEventPriority, *PTcEventPriority;

typedef struct TcEventTime
{
	LONG	loPart;
	LONG	hiPart;
} TcEventTime, *PTcEventTime;

#if !defined(IS_R0) && !defined(TC_ENVIRONMENT_OS)
typedef struct TcEventHeader
{
	TcEventClass		nClass;
	TcEventPriority	nPriority;
	LONG					dwFlags;
	LONG					dwUserData;
	LONG					nId;
	LONG					nInvokeId;
	DATE					fDate;
	LONG					nMs;
	VARIANT				varSource;
	BSTR					szFmtProgId;
} TcEventHeader, *PTcEventHeader;
#endif // IS_R0

typedef enum TcEventHeaderIndex
{
	TCEVTHEADERIDX_CLASS		=0,
	TCEVTHEADERIDX_PRIORITY	=1,
	TCEVTHEADERIDX_FLAGS		=2,
	TCEVTHEADERIDX_USERDATA	=3,
	TCEVTHEADERIDX_ID			=4,
	TCEVTHEADERIDX_INVOKEID	=5,
	TCEVTHEADERIDX_DATE		=6,
	TCEVTHEADERIDX_DATEMS	=7,
	TCEVTHEADERIDX_SOURCE	=8,
	TCEVTHEADERIDX_FMTPROG	=9,
	TCEVTHEADERIDX_END
} TcEventHeaderIndex, *PTcEventHeaderIndex;


typedef enum TcEventStreamIndex
{
	TCEVTSTREAMIDX_INVOKEID =0,
	TCEVTSTREAMIDX_TIME_LO	=1,
	TCEVTSTREAMIDX_TIME_HI	=2,
	TCEVTSTREAMIDX_ID			=3,
	TCEVTSTREAMIDX_FLAGS		=4,
	TCEVTSTREAMIDX_USERDATA	=5,
	TCEVTSTREAMIDX_PRIO		=6,
	TCEVTSTREAMIDX_SRC		=7,
	TCEVTSTREAMIDX_FMTPROG	=8,
	TCEVTSTREAMIDX_DATA		=9,
	TCEVTSTREAMIDX_END
} TcEventStreamIndex, *PTcEventStreamIndex;

#pragma pack (push,1)

typedef struct TcEventData
{
	USHORT				cbFmt;	// length of parameter description string
	BYTE				data[1];		// event parameter, variable sized array
} TcEventData, *PTcEventData;






///////////////////////////////////////////////////////////////////////////////
// event structure transport by AdsWrite
// nIndexGroup		=> TcEventStreamType
// nIndexOffset	=> TcEventClass
// cbLength			=> sizeof event stream
typedef struct TcEventStream
{
	LONG					nInvokeId;								// id used by sender
	TcEventTime			nTime;									// time stamp in 100 ns units
	ULONG					nId;										// event id (message id)
	DWORD					dwFlags;									// event flags
	DWORD					dwUserData;								//	user data
	LONG					nPriority;								// event priority
	union
	{
		char				szSource[TCEVENT_SRCNAMESIZE];	// source name or any other identifier
		GUID				tcId;
		LONG				nSrcId;
		struct 
		{
			LONG		nSrcId;
			struct addr
			{
				struct netId
				{
					 unsigned char b[6];
				}netId;
				short port;
			}addr;
		}srcIdAddr;
	};
	char					szFmtProgId[TCEVENT_FMTPRGSIZE];	// progid of textformatter
	TcEventData			evtData;									// event data
}TcEventStream, *PTcEventStream;

///////////////////////////////////////////////////////////////////////////////
// event structure transport by AdsReadWrite
// to retrieve the configuartion of one alarm
// from the formater
// nIndexGroup		=> set to TCEVENTLOGIGRP_GETCONFIG
// 
// cbWrLen			=> sizeof event stream
typedef struct TcEventConfigStream
{
	ULONG					nId;										// event id (message id)
	DWORD					dwFlags;									// event flags
	DWORD					dwUserData;								//	user data
	LONG					nClass;									//	event class
	LONG					nPriority;								// event priority
	LONG					nStreamType;								//	stream type
	union
	{
		char				szSource[TCEVENT_SRCNAMESIZE];	// source name or any other identifier
		GUID				tcId;
		LONG				nSrcId;
	};
	char					szFmtProgId[TCEVENT_FMTPRGSIZE];	// progid of textformatter

}TcEventConfig, *PTcEventConfig;


///////////////////////////////////////////////////////////////////////////////
typedef struct TcEventClearParm
{
	DWORD					dwFlags;									// event flags
	ULONG					nId;										// event id (message id)
	union
	{
		char				szSource[TCEVENT_SRCNAMESIZE];	// source name or any other identifier
		GUID				tcId;
		LONG				nSrcId;
	};
} TcEventClearParm, *PTcEventClearParm;

#pragma pack (pop)
