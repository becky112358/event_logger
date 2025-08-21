///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Ads.h"
#include "TcEventTypes.h"
#if !defined(UNDER_CE)
#define ADSLOG_XML_FORMATTER
#endif

////////////////////////////////////////////////////////////////////////////////
#define ADSLOG_BUFSIZE	256

#define ADSLOG_MSGTYPE_HINT			0x001
#define ADSLOG_MSGTYPE_WARN			0x002
#define ADSLOG_MSGTYPE_ERROR			0x004
#define ADSLOG_MSGTYPE_LOG				0x010
#define ADSLOG_MSGTYPE_MSGBOX			0x020
#define ADSLOG_MSGTYPE_RESOURCE		0x040
#define ADSLOG_MSGTYPE_STRING			0x080
#define ADSLOG_MSGTYPE_DEFMSGIDX		0x100
#define ADSLOG_MSGTYPE_FATALERROR	0x200
#define ADSLOG_MSGTYPE_TCOMEVENT		0x400	  	// uses gSrc and nEvtId instead of sDeviceName and nResourceId
#define ADSLOG_MSGTYPE_SRCNAMEPARA	0x800		// source name in parameter
#define ADSLOG_MSGTYPE_SRCOIDPARA	0x1000	// source id in parameter

#define ADSLOG_MSGTYPE_WARNLEVEL1	0x00010000
#define ADSLOG_MSGTYPE_WARNLEVEL2	0x00020000
#define ADSLOG_MSGTYPE_WARNLEVEL3	0x00030000

#define ADSLOG_MSGTYPE_LERROR		(ADSLOG_MSGTYPE_ERROR|ADSLOG_MSGTYPE_LOG)
#define ADSLOG_MSGTYPE_LRERROR	(ADSLOG_MSGTYPE_ERROR|ADSLOG_MSGTYPE_LOG|ADSLOG_MSGTYPE_RESOURCE)
#define ADSLOG_MSGTYPE_LBERROR	(ADSLOG_MSGTYPE_ERROR|ADSLOG_MSGTYPE_LOG|ADSLOG_MSGTYPE_MSGBOX)
#define ADSLOG_MSGTYPE_LBRERROR	(ADSLOG_MSGTYPE_ERROR|ADSLOG_MSGTYPE_LOG|ADSLOG_MSGTYPE_MSGBOX|ADSLOG_MSGTYPE_RESOURCE)

#define ADSLOG_MAXFMTSTRING		256
#define ADSLOG_MAXARGS				16

#define ADSLOG_ISHINT(x)		(x & ADSLOG_MSGTYPE_HINT)
#define ADSLOG_ISWARN(x)		(x & ADSLOG_MSGTYPE_WARN)
#define ADSLOG_ISERROR(x)		(x & ADSLOG_MSGTYPE_ERROR)
#define ADSLOG_ISLOG(x)			(x & ADSLOG_MSGTYPE_LOG)
#define ADSLOG_ISMSGBOX(x)		(x & ADSLOG_MSGTYPE_MSGBOX)
#define ADSLOG_ISSTRING(x)		(x & ADSLOG_MSGTYPE_STRING)
#define ADSLOG_ISRESOURCE(x)	(x & ADSLOG_MSGTYPE_RESOURCE)
#ifdef ADSLOG_XML_FORMATTER
#define ADSLOG_ISTCOMEVENT(x)	(x & ADSLOG_MSGTYPE_TCOMEVENT)
#define ADSLOG_HASSRCNAME(x)	(x & ADSLOG_MSGTYPE_SRCNAMEPARA)
#define ADSLOG_HASSRCOID(x)	(x & ADSLOG_MSGTYPE_SRCOIDPARA)
#define ADSLOG_HASSRCNAMEOID(x)	(((x) & (ADSLOG_MSGTYPE_SRCNAMEPARA|ADSLOG_MSGTYPE_SRCOIDPARA)) == (ADSLOG_MSGTYPE_SRCNAMEPARA|ADSLOG_MSGTYPE_SRCOIDPARA))
#endif

#define ADSLOG_WARNLEVEL(x)	((x & 0x00FF0000) >> 16)

#define TCEVENTLOGGER_IGRP_EVENTHANDLING 100
#define TCEVENTLOGGER_IOFFS_ADSLOG 810
#define TCEVENTLOGGER_IOFFS_NOTIFY_RT_LISTENER 820


enum nLogMessageType
{
	LOGMESSAGETYPE_NT = 0,
	LOGMESSAGETYPE_TCEVENT = 1,
	LOGMESSAGETYPE_BOTH = 2,
	LOGMESSAGETYPE_TCEVENTLOGGER = 3,
	LOGMESSAGETYPE_TCEVENTLOGGER_AND_NT = 4,
};

////////////////////////////////////////////////////////////////////////////////
#pragma pack( push, 1)
typedef struct
{
	ULONG		nStamps;
	__int64	nTimeStamp;
	ULONG		nSamples;
	ULONG		hNotification;
	ULONG		cbMsgSize;
	ULONG		dwMsgCtrl;
	union
	{
		struct
		{
			char		sDeviceName[ADS_FIXEDNAMESIZE];
			ULONG		nResourceId;
		};
#ifdef ADSLOG_XML_FORMATTER
		struct
		{
			GUID		gSrcId;
			ULONG		nEvtId;
		};
#endif
	};
	BYTE		msgData[ADSLOG_BUFSIZE];
} AdsLogHeader;

typedef struct
{
	__int64	nTimeStamp;
	DWORD		dwMsgCtrl;
	ULONG		nServerPort;
	char		sDeviceName[ADS_FIXEDNAMESIZE];
	ULONG		cbMsgSize;
	char		szMsg[ANYSIZE_ARRAY];
} AdsLogNotification, *PAdsLogNotification;

class DLL_EXPORT CAdsLogMessage
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CAdsLogMessage();
	CAdsLogMessage( DWORD msgCtrl, ULONG nResourceId );
#ifndef POSIX
	bool Add( LONG aLong );
#endif
	bool Add( int anInt );
	bool Add( __int64 anInt64 );
	bool Add( double aDouble );
	bool Add( char* aString );
	bool Add( void* pBlob, ULONG cbBlob );
	bool Add( char aChar );
	bool Add( void* aPointer ); // 64 Bit enabled !
	bool Add( unsigned char size, void* p);

	bool SetDeviceName( LPCSTR pDeviceName );
	void SetTimeStamp( __int64 nTime );
	size_t GetDataSize();
	operator AdsNotificationStream&();
	operator AdsNotificationStream*();

	char*	GetFormatString();
	AdsLogHeader* GetAdsLogHeader();
	PBYTE	GetDataPtr();
	PBYTE GetDataAddr();

private:
	union
	{
		AdsNotificationStream stream;
		AdsLogHeader			 head;
	} m_header;

	PBYTE	m_pBuf;
	PBYTE	m_pStartOfBuf;
	PBYTE m_pEndOfBuf;
//	ULONG m_cbLen;
	char	m_strFmt[2*ADSLOG_MAXARGS+1];
};
#pragma pack(pop)

////////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CAdsLog
{
public:
	CAdsLog();
	virtual ~CAdsLog();

#ifndef TCOS_APP
	LONG AdsReportLog( DWORD msgCtrlMask, PCHAR szFormat, ... );
#else
	LONG AdsReportLog(DWORD msgCtrlMask, PCCH szFormat, ...);
#endif
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, PCHAR szFormat, ... );
	LONG AdsReportLog( CAdsLogMessage& rLogMess, DWORD msgCtrlMask,
									ULONG nResourceId, PCHAR szFormat, ... );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg, LONG nArg1 );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg, LONG nArg1, LONG nArg2 );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg0, DOUBLE fArg1 );
	LONG AdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg0, DOUBLE fArg1, DOUBLE fArg2 );

protected:
	virtual LONG AdsLogMessage( CAdsLogMessage& rLogMess );
	virtual LPCSTR AdsGetDeviceName( );
	LONG ParseFormatString( PCHAR pszFormat, size_t cbFmtLen, char* pszArgs, ULONG& rnArgs );
	LONG AddArgsToLogMsg( const char* pszFmt, CAdsLogMessage& rLogMsg, va_list pArgs, ULONG nArgs );
private:
};

