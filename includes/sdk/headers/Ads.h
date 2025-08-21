///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// includes
#include "TcBase.h"
#include "TcError.h"
#include	"Ams.h"
#include	"AdsTypes.h"
#include	"AdsErrorCodes.h"

#if defined(_WIN64)
    typedef unsigned __int64 ADS_SIZE_T;
#else
	typedef unsigned __int32 ADS_SIZE_T;
#endif

#if defined(IS_R0) || defined(WIN32_RUNTIME)
#define	ADS_DRIVER_CONTEXT
#define	TCADSAPI TCFRAMEWORKAPI
#else 
#define	TCADSAPI 
#endif
#ifdef _DEBUG
//#define  ADS_IGNORE_SYMBOLVERSION
#endif
#define	ADS_EXTERNALTIME_PROVIDER
#define	ADS_REFACTOR_INFO

//#define	SAFETYMAPPING_VIA_PLC
#define	LEGACY_PROPERTY_GETSET_SUPPORT	// used until 3.1.4022

#ifdef ADS_REFACTOR_INFO
#define ADSREFACTORINFO_H	, INT refactorCnt=-1
#define ADSREFACTORINFO_C	, INT refactorCnt
#define ADSREFACTORINFO_U	, refactorCnt
#else
#define ADSREFACTORINFO_H	
#define ADSREFACTORINFO_C	
#define ADSREFACTORINFO_U	
#endif
////////////////////////////////////////////////////////////////////////////////

#define ADS_MAXSYNCPORTS	500	// used in AdsDll.dll and TcAdsDll.dll

////////////////////////////////////////////////////////////////////////////////
// ADS Service Ids
#define ADSSRVID_INVALID					0x00
#define ADSSRVID_READDEVICEINFO			0x01
#define ADSSRVID_READ         			0x02
#define ADSSRVID_WRITE        			0x03
#define ADSSRVID_READSTATE    			0x04
#define ADSSRVID_WRITECTRL    			0x05
#define ADSSRVID_ADDDEVICENOTE  			0x06
#define ADSSRVID_DELDEVICENOTE  			0x07
#define ADSSRVID_DEVICENOTE				0x08
#define ADSSRVID_READWRITE      			0x09

////////////////////////////////////////////////////////////////////////////////
// ADS reserved index groups
#define ADSIGRP_SYMTAB						0xF000
#define ADSIGRP_SYMNAME						0xF001
#define ADSIGRP_SYMVAL						0xF002

#define ADSIGRP_SYM_HNDBYNAME				0xF003		// readLength == 4: handle
																	// readLength > 4: handle(4) + var size(4) + type decoration(4) + 
																		// type name length(2) + type name(n) + '\0'(1)
#define ADSIGRP_SYM_VALBYNAME				0xF004
#define ADSIGRP_SYM_VALBYHND				0xF005
#define ADSIGRP_SYM_RELEASEHND			0xF006
#define ADSIGRP_SYM_INFOBYNAME			0xF007
#define ADSIGRP_SYM_VERSION				0xF008
#define ADSIGRP_SYM_INFOBYNAMEEX			0xF009

#define ADSIGRP_SYM_DOWNLOAD				0xF00A		// AdsSymbolUpAndDownloadHeader
#define ADSIGRP_SYM_UPLOAD					0xF00B
#define ADSIGRP_SYM_UPLOADINFO			0xF00C
#define ADSIGRP_SYM_DOWNLOAD2				0xF00D		// AdsSymbolUpAndDownloadHeader2
#define ADSIGRP_SYM_DT_UPLOAD				0xF00E
#define ADSIGRP_SYM_UPLOADINFO2			0xF00F

#define ADSIGRP_SYMNOTE						0xF010		// notification of named handle

#define ADSIGRP_SYM_DT_INFOBYNAMEEX		0xF011
#define ADSIGRP_SYM_ADDRBYHND				0xF012
#define ADSIGRP_SYM_POINTER_SUPPORT		0xF013
#define ADSIGRP_SYM_POINTER_ACCESS		0xF014		// dummy IGRP for dereferenced pointer: read or write access via this IGRP is not possible
#define ADSIGRP_SYM_REFERENCE_SUPPORT	0xF015
#define ADSIGRP_SYM_REFERENCE_ACCESS	0xF016		// dummy IGRP for dereferenced a reference: read or write access via this IGRP is not possible
#define ADSIGRP_SYM_VALBYHND_WITHMASK	0xF018
#define ADSIGRP_SYM_NOACCESS_TO_SUBSYM	0xF019
#define ADSIGRP_SYM_POINTER_BITACCESS		0xF01A	// dummy IGRP for dereferenced pointer to bit access: read or write access via this IGRP is not possible
#define ADSIGRP_SYM_REFERENCE_BITACCESS	0xF01B	// dummy IGRP for dereferenced a reference to bit access: read or write access via this IGRP is not possible
#define ADSIGRP_SYM_DOWNLOAD3				0xF01C		// AdsSymbolUpAndDownloadHeader3
#define ADSIGRP_SYM_FORWARD_ACCESS		0xF01D
#define ADSIGRP_SYM_FORWARD_BYHND		0xF01E


#define ADSIGRP_IOIMAGE_RWIB				0xF020		// read/write input byte(s)
#define ADSIGRP_IOIMAGE_RWIX				0xF021		// read/write input bit
#define ADSIGRP_IOIMAGE_RISIZE			0xF025		// read input size (in byte)
#define ADSIGRP_IOIMAGE_RWIX0				0xF028		// read/write input bit0, with byte offset
#define ADSIGRP_IOIMAGE_RWIX1				0xF029		// read/write input bit1, with byte offset
#define ADSIGRP_IOIMAGE_RWIX2				0xF02A		// read/write input bit2, with byte offset
#define ADSIGRP_IOIMAGE_RWIX3				0xF02B		// read/write input bit3, with byte offset
#define ADSIGRP_IOIMAGE_RWIX4				0xF02C		// read/write input bit4, with byte offset
#define ADSIGRP_IOIMAGE_RWIX5				0xF02D		// read/write input bit5, with byte offset
#define ADSIGRP_IOIMAGE_RWIX6				0xF02E		// read/write input bit6, with byte offset
#define ADSIGRP_IOIMAGE_RWIX7				0xF02F		// read/write input bit7, with byte offset

#define ADSIGRP_IOIMAGE_RWOB				0xF030		// read/write output byte(s)
#define ADSIGRP_IOIMAGE_RWOX				0xF031		// read/write output bit
#define ADSIGRP_IOIMAGE_ROSIZE			0xF035		// read output size (in byte)
#define ADSIGRP_IOIMAGE_RWOX0				0xF038		// read/write output bit0, with byte offset
#define ADSIGRP_IOIMAGE_RWOX1				0xF039		// read/write output bit1, with byte offset
#define ADSIGRP_IOIMAGE_RWOX2				0xF03A		// read/write output bit2, with byte offset
#define ADSIGRP_IOIMAGE_RWOX3				0xF03B		// read/write output bit3, with byte offset
#define ADSIGRP_IOIMAGE_RWOX4				0xF03C		// read/write output bit4, with byte offset
#define ADSIGRP_IOIMAGE_RWOX5				0xF03D		// read/write output bit5, with byte offset
#define ADSIGRP_IOIMAGE_RWOX6				0xF03E		// read/write output bit6, with byte offset
#define ADSIGRP_IOIMAGE_RWOX7				0xF03F		// read/write output bit7, with byte offset

#define ADSIGRP_IOIMAGE_CLEARI			0xF040		// write inputs to null
#define ADSIGRP_IOIMAGE_CLEARO			0xF050		// write outputs to null

#define ADSIGRP_IOIMAGE_RWIOB				0xF060		// read input and write output byte(s) // ADS_READWRITE

#define ADSIGRP_IOIMAGE_WATCHDOG			0xF064		// iOffs==1 client protection, pData (4Bytes) = Watchdog in ms

#define ADSIGRP_IOIMAGE_CREATE			0xF068		// write IoCreateImageStruct

#define ADSIGRP_JSON							0xF070		// read/write Json commands

#define ADSIGRP_JSON_DOM_ACCESS_GET		0xF071		// AdsR:  get the whole document -> one 0-terminated string
																	// AdsRW: W: one 0-terminated string: Length==0 whole document, Length > 0 path to an json object (0-terminated!) R: json content (0-terminated)
#define ADSIGRP_JSON_DOM_ACCESS_SET		0xF072		// AdsW: three 0-terminated strings: path+\0, member+\0, jsonText+\0
																	// strlen(path)==0 -> realtive to root
																	// strlen(member)==0 -> exchange existing path
#define ADSIGRP_JSON_DOM_ACCESS_DEL		0xF073		// AdsW: path+\0, member+\0
																	// strlen(path)==0 && strlen(member)==0 -> clear document
																	// strlen(path)==0 -> delete root member
																	// strlen(member)==0 -> removes path member
#define ADSIGRP_JSON_DOM_ACCESS_LEN		0xF074		// AdsR: string length of the whole document (incl. terminating \0) - 4 Bytes
																	// AdsRW: one 0-terminated string: Length==0 whole document, Length > 0 path to an json object (0-terminated!) R: Length of json object (incl. terminating 0) - 4 Bytes

#define ADSIGRP_SUMUP_READ					0xF080		// AdsRW  IOffs list size or 0 (=0 -> list size == WLength/3*sizeof(ULONG))
																	// W: {list of IGrp, IOffs, Length} 
																	// if IOffs != 0 then R: {list of results} and {list of data}
																	// if IOffs == 0 then R: only data (sum result)
#define ADSIGRP_SUMUP_WRITE				0xF081		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Length} followed by {list of data} 
																	// R: list of results
#define ADSIGRP_SUMUP_READWRITE			0xF082		// AdsRW  IOffs list size 
																	// W: {list of IGrp, IOffs, RLength, WLength} followed by {list of data} 
																	// R: {list of results, RLength} followed by {list of data (returned lengths)}
#define ADSIGRP_SUMUP_READEX				0xF083		// AdsRW  IOffs list size 
																	// W: {list of IGrp, IOffs, Length} 
																	// R: {list of results, Length} followed by {list of data (expepted lengths)}
#define ADSIGRP_SUMUP_READEX2				0xF084		// AdsRW  IOffs list size 
																	// W: {list of IGrp, IOffs, Length} 
																	// R: {list of results, Length} followed by {list of data (returned lengths)}
#define ADSIGRP_SUMUP_ADDDEVNOTE			0xF085		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Attrib} 
																	// R: {list of results, handles}
#define ADSIGRP_SUMUP_DELDEVNOTE			0xF086		// AdsRW  IOffs list size
																	// W: {list of handles} 
																	// R: {list of results}

#ifdef	ADS_EXTERNALTIME_PROVIDER
#define ADSIGRP_EXTERNALTIME				0xF088		// // ioffs&0xf == timebase (0 = SystemTime, 1 = External1, 2 = External2, 3 = External3
	#define ADSIOFFS_EXTERNALTIME_TYPE(io)	(ITcExternalTime::TimeType)((io)&0x000000ff)
	#define ADSIOFFS_EXTERNALTIME_FUNC(io)	((io)&0x0000ff00)
	#define ADSIOFFS_EXTERNALTIME_SET		0x00000000	// AdsW: nothing - set base time of calling AmsAddr
																		// AdsR: ITcExternalTime::TimeType - get base time of calling AmsAddr
	#define ADSIOFFS_EXTERNALTIME_OFFSET	0x00000100	// AdsW: timeoffset (__int64)
																		// AdsR: timeoffset (__int64)
	#define ADSIOFFS_EXTERNALTIME_ABSOLUTE	0x00000200	// AdsR: actuale time corrected by timeoffset (__int64)
	#define ADSIOFFS_EXTERNALTIME_PROVIDER	0x00000300	// AdsR: OTCID of provider
	#define ADSIOFFS_EXTERNALTIME_SETALL	0x00000400	// AdsW: nothing - set base time for all clients!
																		// AdsR: ITcExternalTime::TimeType - get base time for all clients!
#endif

#define ADS_SUMUP_IGRP(p, i)				(((PULONG)p)[(i)*3+0])
#define ADS_SUMUP_IOFFS(p, i)				(((PULONG)p)[(i)*3+1])
#define ADS_SUMUP_LENGTH(p, i)			(((PULONG)p)[(i)*3+2])

#define ADS_SUMUP_R_RESULT(p, i)			(((PULONG)p)[(i)*2+0])
#define ADS_SUMUP_R_LENGTH(p, i)			(((PULONG)p)[(i)*2+1])

#define ADS_SUMUP_W_RESULT(p, i)			(((PULONG)p)[i])

#define ADS_SUMUP_RW_IGRP(p, i)			(((PULONG)p)[(i)*4+0])
#define ADS_SUMUP_RW_IOFFS(p, i)			(((PULONG)p)[(i)*4+1])
#define ADS_SUMUP_RW_RLENGTH(p, i)		(((PULONG)p)[(i)*4+2])
#define ADS_SUMUP_RW_WLENGTH(p, i)		(((PULONG)p)[(i)*4+3])
#define ADS_SUMUP_RW_RESULT(p, i)		(((PULONG)p)[(i)*2+0])
#define ADS_SUMUP_RW_LENGTH(p, i)		(((PULONG)p)[(i)*2+1])

#define ADSIGRP_CHECK_NOTIFICATION		0xF090
#define ADSIGRP_DIAG_NOTIFICATION		0xF091		// info of current registered notifications - type AdsNotificationDiag

#define ADSIGRP_SYM_CONTEXTCYCLE			0xF0A0

#define ADSIGRP_DEVICE_CONTEXT_DATA		0xF0B0		// info about contexts (AdsR)
	#define ADSIOFFS_DEVCTXDATA_COUNT			0x0001		// returns count of contexts (USHORT) and synbol specific context 0=no or 1=yes (USHORT)
	#define ADSIOFFS_DEVCTXDATA_CYCLETIMES		0x0002		// returns list of cycletimes (n*ULONG in 100ns)

#define ADSIGRP_DEVICE_DATA				0xF100		// state, name, etc...
	#define ADSIOFFS_DEVDATA_ADSSTATE			0x0000	// ads state of device
	#define ADSIOFFS_DEVDATA_DEVSTATE			0x0002	// device state
	#define ADSIOFFS_DEVDATA_CONFIGID			0x0004	// 
	#define ADSIOFFS_DEVDATA_ADSVERSIONCHECK	0x0005	// 

#define ADSIGRP_TASK_DATA					0xF200		// cycleTime etc... (see TaskAds.h)
// ADSIGRP_TASK_DATA	reserved until		0xF2FF

#define ADSIGRP_CANOPEN_BEGIN				0xF300		// begin of reserved CANopen area
#define ADSIGRP_CANOPEN_SDO				0xF302		// index = HIWORD(iOffs), subIndex = LOBYTE(LOWORD(iOffs))
	#define	ADSIOFFS_ECAT_COE_COMPLETEACCESS		0x00000100
	#define	ADSIOFFS_ECAT_COE_EXTENDEDTIMEOUT	0x00000200	// increase mailbox timeout by factor 10
#define ADSIGRP_CANOPEN_SDO_LASTERROR	0xF303		// returns AdsLastErrorInfo
#define ADSIGRP_CANOPEN_SDO_SUMUP_READ	0xF304		// AdsRW IOffs = Count of subcommands, W: SubCommandsRead(IG,IO,Len)		R: Result i(4 byte),Len i(4 byte), data i(len i)
#define ADSIGRP_CANOPEN_SDO_SUMUP_WRITE	0xF305		// AdsRW IOffs = Count of subcommands, W: SubCommandsWrite(IG,IO,Len,data)	R: Result i(4 byte)
#define ADSIGRP_CANOPEN_TXPDO_ACCESS	0xF3F8		// read (remote transmission request) or write complete TX pdo via mailbox, IOffs = pdo no (0-511 or 0x1a00-0x1bff)
#define ADSIGRP_CANOPEN_RXPDO_ACCESS	0xF3F9		// read (remote transmission request) or write complete RX pdo via mailbox, IOffs = pdo no (0-511 or 0x1600-0x17ff)
#define ADSIGRP_CANOPEN_SDO_INFO_LIST	0xF3FC		// listType = HIWORD(iOffs)
#define ADSIGRP_CANOPEN_SDO_INFO_OBJ	0xF3FD		// index = HIWORD(iOffs)
#define ADSIGRP_CANOPEN_SDO_INFO_ENTRY	0xF3FE		// index = HIWORD(iOffs), subIndex = LOBYTE(LOWORD(iOffs))
#define ADSIGRP_CANOPEN_END				0xF3FF		// end of reserved CANopen area

#define ADSIGRP_ECAT_FOE_BEGIN			0xF400	// File Access over EtherCAT
#define ADSIGRP_ECAT_FOE_FOPENREAD		0xF401	// AdsRW IOffs = password, W: file name, R: file handle (4 byte) and opt. error text
#define ADSIGRP_ECAT_FOE_FOPENWRITE		0xF402	// AdsRW IOffs = password, W: file name, R: file handle (4 byte) and opt. error text
#define ADSIGRP_ECAT_FOE_FCLOSE			0xF403	// AdsRW IOffs = file handle
#define ADSIGRP_ECAT_FOE_FREAD			0xF404	// AdsRW IOffs = file handle, R: file data
#define ADSIGRP_ECAT_FOE_FWRITE			0xF405	// AdsRW IOffs = file handle, W: file data
#define ADSIGRP_ECAT_FOE_PROGRESSINFO	0xF406	// 
#define ADSIGRP_ECAT_FOE_LASTERROR		0xF407	// returns AdsLastErrorInfo	
#define ADSIGRP_ECAT_FOE_END				0xF41F	// File Access over EtherCAT

#define ADSIGRP_ECAT_SOE					0xF420		// SERCOS over EtherCAT: IDN = LOWORD(iOffs), ELEMENT = LOBYTE(HIWORD(iOffs))
	#define ADSIOFFS_ECAT_SOE_ELEMENT_MASK		0x00FF0000	// element mask of sercos idn
	#define ADSIOFFS_ECAT_SOE_DATASTATE			0x00010000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_NAME				0x00020000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_ATTRIBUTE			0x00040000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_UNIT				0x00080000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_MIN					0x00100000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_MAX					0x00200000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_VALUE				0x00400000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_DEFAULT			0x00800000	// element of sercos idn
	#define ADSIOFFS_ECAT_SOE_DRIVENO_MASK		0x07000000	// element mask of drive no
	#define ADSIOFFS_ECAT_SOE_COMMAND			0x08000000	// command execution requested
		#define ADSIOFFS_ECAT_SOE_P_IDN			0x00008000	// mask for sercos P idn (0x8000, bit 15)
		#define ADSIOFFS_ECAT_SOE_S_IDN			0x00000000	// mask for sercos S idn (0x0000, bit 15)
#define ADSIGRP_ECAT_SOE_LASTERROR		0xF421		// returns AdsLastErrorInfo


#define ADSIGRP_ECAT_VOE					0xF430		// Vendor over EtherCAT: 
	// ADS Write:	data to mailbox
	// ADS DevNotif

#define ADSIGRP_ECAT_SLAVE_SPECIFIC_BEGIN	0x80000000
#define ADSIGRP_ECAT_SLAVE_SPECIFIC_END	0x8FFFFFFF

////////////////////////////////////////////////////////////////////////////////
// ADS constants
const	unsigned int ADS_FIXEDNAMESIZE=16;
const unsigned int ADS_STATENAMESIZE=20;
const	unsigned int L_ADSINDXNAME=32+1;

// length of literal ads index description zstring
#define	ADS_NOTIFICATIONBLOCKSIZE	(sizeof(AdsNotificationBlock)-1)

typedef enum nAdsState
{
	ADSSTATE_INVALID	=0,
	ADSSTATE_IDLE		=1,
	ADSSTATE_RESET		=2,
	ADSSTATE_INIT		=3,
	ADSSTATE_START		=4,
	ADSSTATE_RUN		=5,
	ADSSTATE_STOP		=6,
	ADSSTATE_SAVECFG	=7,
	ADSSTATE_LOADCFG	=8,
	ADSSTATE_POWERFAILURE =9,
	ADSSTATE_POWERGOOD	 =10,
	ADSSTATE_ERROR			 =11,
	ADSSTATE_SHUTDOWN		 =12,
	ADSSTATE_SUSPEND		 =13,
	ADSSTATE_RESUME		 =14,
	ADSSTATE_CONFIG		 =15,	// system is in config mode
	ADSSTATE_RECONFIG		 =16,	// system should restart in config mode
	ADSSTATE_STOPPING		 =17,
	ADSSTATE_INCOMPATIBLE =18,
	ADSSTATE_EXCEPTION	 =19,
	ADSSTATE_MAXSTATES
} ADSSTATE;

typedef enum nAdsTransMode
{
	ADSTRANS_NOTRANS				= 0,
	ADSTRANS_CLIENTCYCLE			= 1,
	ADSTRANS_CLIENTONCHA			= 2,
	ADSTRANS_SERVERCYCLE			= 3,
	ADSTRANS_SERVERONCHA			= 4,
	ADSTRANS_SERVERCYCLE2		= 5,		// cycletime used as contextId - LEGACY
	ADSTRANS_SERVERONCHA2		= 6,		// cycletime used as contextId - LEGACY
	ADSTRANS_CLIENT1REQ			= 10,
	ADSTRANS_SERVERCYCLE_C0		= 16,		// same as ADSTRANS_SERVERCYCLE
	ADSTRANS_SERVERCYCLE_C1		= 17,	
	ADSTRANS_SERVERCYCLE_C2		= 18,	
	ADSTRANS_SERVERCYCLE_C3		= 19,	
	ADSTRANS_SERVERCYCLE_C4		= 20,	
	ADSTRANS_SERVERCYCLE_C5		= 21,	
	ADSTRANS_SERVERCYCLE_C6		= 22,	
	ADSTRANS_SERVERCYCLE_C7		= 23,	
	ADSTRANS_SERVERCYCLE_C8		= 24,	
	ADSTRANS_SERVERCYCLE_C9		= 25,	
	ADSTRANS_SERVERCYCLE_C10	= 26,	
	ADSTRANS_SERVERCYCLE_C11	= 27,	
	ADSTRANS_SERVERCYCLE_C12	= 28,	
	ADSTRANS_SERVERCYCLE_C13	= 29,	
	ADSTRANS_SERVERCYCLE_C14	= 30,	
	ADSTRANS_SERVERCYCLE_C15	= 31,	
	ADSTRANS_MAXMODES		
}ADSTRANSMODE;


////////////////////////////////////////////////////////////////////////////////
// ADS AMS command
#pragma	pack( push, 1)
typedef struct 
{
	AmsHead	head;
	USHORT	firstDataWord;
} AdsAmsCmd, *PAdsAmsCmd;

typedef	struct 
{
	BYTE		version;
	BYTE		revision;
	USHORT	build;
} AdsVersion, *PAdsVersion;

#define	AdsVersionCmp(a, b)	(a.version > b.version ? 1 : (a.version < b.version ? -1 : \
	(a.revision > b.revision ? 1 : (a.revision < b.revision ? -1 : \
	((a.build > b.build ? 1 : (a.build < b.build ? -1 : 0)))))))

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		hNotification;
	ULONG		cbSampleSize;
	BYTE		data[ANYSIZE_ARRAY];
} AdsNotificationSample, *PAdsNotificationSample;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	__int64	nTimeStamp;
	ULONG		nSamples;
	AdsNotificationSample tSample[ANYSIZE_ARRAY];
} AdsStampHeader, *PAdsStampHeader;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG							nStamps;
	AdsStampHeader				tStamp[ANYSIZE_ARRAY];
} AdsNotificationStream, *PAdsNotificationStream;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		hNotification;
	__int64	nTimeStamp;
	ULONG		cbSampleSize;
	BYTE		data[ANYSIZE_ARRAY];
} AdsNotificationHeader, *PAdsNotificationHeader;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		hNotification;
	__int64	nTimeStamp;
	ULONG		cbSampleSize;
	PVOID		pData;
} AdsNotificationPtrHeader, *PAdsNotificationPtrHeader;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	AmsAddr			addr;					// AmsAddr of client
	ADS_UINT32		watchList : 8;		// watchlist index -> context
	ADS_UINT32		notificationCnt : 24;	// count of notification of client
} AdsNotificationClientDiag, *PAdsNotificationClientDiag;

typedef struct
{
	ADS_UINT32		notificationCnt;	// sum of all registered notifications
	ADS_UINT32		clientCnt;			// count of clients
	// AdsNotificationClientDiag		client[clientCnt];			
} AdsNotificationDiag, *PAdsNotificationDiag;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG				cbLength;
	ADSTRANSMODE	nTransMode;
	ULONG				nMaxDelay;
	union 
	{
		ULONG				nCycleTime;
		ULONG				nContextId;		// if nTransMode == ADSTRANS_SERVERCYCLE2 or ADSTRANS_SERVERONCHA2
	};
	BYTE				nCmpMax[sizeof(double)];
	BYTE				nCmpMin[sizeof(double)];
} AdsNotificationAttrib, *PAdsNotificationAttrib;

#define SIZEOF_NOTIFICATIONSAMPLE(pSample) \
	( pSample->cbSampleSize + offsetof(AdsNotificationSample, data) )

#define	ADSNOTIFICATION_PDATA( pAdsNotificationHeader )	\
	(	(unsigned char*)	(((PAdsNotificationHeader)pAdsNotificationHeader->data )))


#define SIZEOF_NOTIFICATIONHEADER(pHeader) \
	( pHeader->cbSampleSize + offsetof(AdsNotificationHeader, data) )

typedef void (*PAdsNotificationFunc)(	AmsAddr*	pAddr,
													AdsNotificationHeader* pNotification,
													ULONG hUser						// user handle
													);

////////////////////////////////////////////////////////////////////////////////

#define	ADSSYMBOLFLAG_PERSISTENT		0x0001
#define	ADSSYMBOLFLAG_BITVALUE			0x0002
#define	ADSSYMBOLFLAG_REFERENCETO		0x0004
#define	ADSSYMBOLFLAG_TYPEGUID			0x0008
#define	ADSSYMBOLFLAG_TCCOMIFACEPTR	0x0010
#define	ADSSYMBOLFLAG_READONLY			0x0020
#define	ADSSYMBOLFLAG_ITFMETHODACCESS	0x0040
#define	ADSSYMBOLFLAG_METHODDEREF		0x0080
#define	ADSSYMBOLFLAG_CONTEXTMASK		0x0F00
#define	ADSSYMBOLFLAG_ATTRIBUTES		0x1000
#define	ADSSYMBOLFLAG_STATIC				0x2000
#define	ADSSYMBOLFLAG_INITONRESET		0x4000	// persistent data will not restored after reset (cold)
#define	ADSSYMBOLFLAG_EXTENDEDFLAGS	0x8000	// extended flags added

#define	ADSSYMBOLFLAG2_PLCPOINTERTYPE		0x00000001	// PLC pointer -> derelocate and relocate while equalizing redundancy projects
#define	ADSSYMBOLFLAG2_RDIGNORE				0x00000002	// ignore symbol while equalizing redundancy projects
#ifdef ADS_REFACTOR_INFO
#define	ADSSYMBOLFLAG2_REFACTORINFO		0x00000004	// one or more refactoring info AdsRefactorInfo added

typedef struct
{
	ADS_UINT32		refactorCnt			: 31;		// refactorCnt of oldname
	ADS_UINT32		nextRefactorInfo	: 1;		// more AdsRefactorInfo follows
	ADS_UINT16		nameLength;		// length of symbol name before refactoring (excl. \0)
	// ADS_INT8		name[];			// symbol name before refactoring with terminating \0
} AdsRefactorInfo, *PAdsRefactorInfo;
#define	PADSREFACTORNAME(p)				((PCHAR)(((PAdsRefactorInfo)p)+1))
#define	NEXTADSREFACTORINFO(p)			(PAdsRefactorInfo)(PADSREFACTORNAME(p)+p->nameLength+1)
#endif
typedef struct
{
	ADS_UINT32		lBound;		// 
	ADS_UINT32		elements;	// 
} AdsDatatypeArrayInfo, *PAdsDatatypeArrayInfo;

typedef struct
{
	ADS_UINT32		entryLength;	// length of complete symbol entry
	ADS_UINT32		iGroup;			// indexGroup of symbol: input, output etc.
	ADS_UINT32		iOffs;			// indexOffset of symbol
	ADS_UINT32		size;				// size of symbol ( in bytes, 0 = bit )
	ADS_UINT32		dataType;		// adsDataType of symbol
	ADS_UINT16		flags;			// see above
	ADS_UINT16		reserved;		// must be 0 (legacy arrayDim)
	ADS_UINT16		nameLength;		// length of symbol name (excl. \0)
	ADS_UINT16		typeLength;		// length of type name (excl. \0)
	ADS_UINT16		commentLength;	// length of comment (excl. \0)
	// ADS_INT8		name[];			// name of symbol with terminating \0
	// ADS_INT8		type[];			// type name of symbol with terminating \0
	// ADS_INT8		comment[];		// comment of symbol with terminating \0
	// GUID			typeGuid;		// if ADSSYMBOLFLAG_TYPEGUID is set
	// ADS_UINT16	attributes;		// count of attribute descriptions if ADSSYMBOLFLAG_ATTRIBUTES is set
	// AdsAttributeEntry attribute[]; // attribute description
	// ADS_UINT32	flags2;			// if ADSSYMBOLFLAG_EXTENDED_FLAGS is set
	// AdsRefactorInfo refInfo[];	// if ADSSYMBOLFLAG2_OLDNAMES is set one ore more AdsRefactorInfo
} AdsSymbolEntry, *PAdsSymbolEntry, **PPAdsSymbolEntry;


#define	PADSSYMBOLNAME(p)				((PCHAR)(((PAdsSymbolEntry)p)+1))
#define	PADSSYMBOLTYPE(p)				(((PCHAR)(((PAdsSymbolEntry)p)+1))+((PAdsSymbolEntry)p)->nameLength+1)
#define	PADSSYMBOLCOMMENT(p)			(((PCHAR)(((PAdsSymbolEntry)p)+1))+((PAdsSymbolEntry)p)->nameLength+1+((PAdsSymbolEntry)p)->typeLength+1)
#define	ADSSYMBOLHASTYPEGUID(p)		((((PAdsSymbolEntry)p)->flags&ADSSYMBOLFLAG_TYPEGUID) != 0)
#define	ADSSYMBOLITFMETHODACCESS(p)	((((PAdsSymbolEntry)p)->flags&(ADSSYMBOLFLAG_TYPEGUID|ADSSYMBOLFLAG_ITFMETHODACCESS)) == (ADSSYMBOLFLAG_TYPEGUID|ADSSYMBOLFLAG_ITFMETHODACCESS))
#define	ADSSYMBOLGETCONTEXT(f)		(((f)&ADSSYMBOLFLAG_CONTEXTMASK) >> 8)
#define	ADSSYMBOLSETCONTEXT(f, c)	(((f) |= (((c)<<8)&ADSSYMBOLFLAG_CONTEXTMASK)) )

const		GUID		ADS_GUID_NULL = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0 } };

inline GUID AdsSymbolTypeGuid(PAdsSymbolEntry p)
{
	if ( (p->flags&ADSSYMBOLFLAG_TYPEGUID) == 0 )
		return ADS_GUID_NULL;
	return *(UNALIGNED GUID*)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3);
}

inline UNALIGNED GUID* PAdsSymbolTypeGuid(PAdsSymbolEntry p)
{
	if ( (p->flags&ADSSYMBOLFLAG_TYPEGUID) == 0 )
		return NULL;
	return (UNALIGNED GUID*)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3);
}

inline void SetAdsSymbolTypeGuid(PAdsSymbolEntry p, GUID g)
{
	if ( (p->flags&ADSSYMBOLFLAG_TYPEGUID) == 0 )
		return;
	*(UNALIGNED GUID*)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3) = g;
}

typedef struct
{
	ADS_UINT8		nameLength;		// length of attribute name (excl. \0)
	ADS_UINT8		valueLength;	// length of attribute value (excl. \0)
	// ADS_INT8		name[];			// name of attribute with terminating \0
	// ADS_INT8		value[];			// value of attribute with terminating \0
} AdsAttributeEntry, *PAdsAttributeEntry, **PPAdsAttributeEntry;
#define	PADSATTRIBUTENAME(p)			((PCHAR)(((PAdsAttributeEntry)p)+1))
#define	PADSATTRIBUTEVALUE(p)		(((PCHAR)(((PAdsAttributeEntry)p)+1))+((PAdsAttributeEntry)p)->nameLength+1)
#define	NEXTADSATTRIBUTE(p)			(PAdsAttributeEntry)(((PBYTE)p)+sizeof(AdsAttributeEntry)+((PAdsAttributeEntry)p)->nameLength+((PAdsAttributeEntry)p)->valueLength+2);

#define	TC_DATAITEMOWNER_ATTRIBUTE		"TcDataItemOwner"
#define	TC_ARRAY_LENGTHIS_ATTRIBUTE	"TcArrayLengthIs"

inline ADS_UINT16 UNALIGNED* PAdsSymbolCntAttributes(PAdsSymbolEntry p)
{
	if ((p->flags&ADSSYMBOLFLAG_ATTRIBUTES) == 0)
		return NULL;
	PBYTE pByte = (((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3);
	if ((p->flags&ADSSYMBOLFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
		
	return (ADS_UINT16 UNALIGNED*)pByte;
}

inline ADS_UINT16 AdsSymbolCntAttributes(PAdsSymbolEntry p)
{
	ADS_UINT16 UNALIGNED* u = PAdsSymbolCntAttributes(p);
	return (u!=NULL) ? *u : 0;
}

inline PAdsAttributeEntry AdsSymbolAttributeItem(PAdsSymbolEntry p, ADS_UINT16 iAttribute)
{
	ADS_UINT16 UNALIGNED* u = PAdsSymbolCntAttributes(p);
	if (u == NULL || iAttribute >= *u)
		return NULL;
	PAdsAttributeEntry	pAttribute = (PAdsAttributeEntry)ENDOF(u);
	for (ADS_UINT16 i=0; i < iAttribute; i++)
		pAttribute = NEXTADSATTRIBUTE(pAttribute);
	return pAttribute;
}

inline ADS_UINT32 AdsSymbolExtendedFlags(PAdsSymbolEntry p)
{
	if ((p->flags&ADSSYMBOLFLAG_EXTENDEDFLAGS) == 0)
		return 0;
	PBYTE pByte = (((PBYTE)(p + 1)) + p->nameLength + p->typeLength + p->commentLength + 3);
	if ((p->flags&ADSSYMBOLFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
	if ((p->flags&ADSSYMBOLFLAG_ATTRIBUTES) != 0)
	{
		ADS_UINT16 n;
		memcpy(&n, pByte, sizeof(ADS_UINT16));
		pByte += sizeof(ADS_UINT16);
		for (ADS_UINT16 i = 0; i < n; i++)
			pByte = (PBYTE)NEXTADSATTRIBUTE(pByte);
	}
	ADS_UINT32 ret;
	memcpy(&ret, pByte, sizeof(ADS_UINT32));
	return ret;
}

inline ADS_UINT32 UNALIGNED* PAdsSymbolExtendedFlags(PAdsSymbolEntry p)
{
	if ((p->flags&ADSSYMBOLFLAG_EXTENDEDFLAGS) == 0)
		return NULL;
	PBYTE pByte = (((PBYTE)(p + 1)) + p->nameLength + p->typeLength + p->commentLength + 3);
	if ((p->flags&ADSSYMBOLFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
	if ((p->flags&ADSSYMBOLFLAG_ATTRIBUTES) != 0)
	{
		ADS_UINT16 n = *(ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		for (ADS_UINT16 i = 0; i < n; i++)
			pByte = (PBYTE)NEXTADSATTRIBUTE(pByte);
	}
	return (ADS_UINT32 UNALIGNED*)pByte;
}

#ifdef ADS_REFACTOR_INFO
inline PAdsRefactorInfo PAdsSymbolRefactorInfo(PAdsSymbolEntry p, INT refactorCnt)
{
	if (ADS_UINT32 UNALIGNED* f = PAdsSymbolExtendedFlags(p))
	{
		if (((*f)&ADSSYMBOLFLAG2_REFACTORINFO) != 0)
		{
			PAdsRefactorInfo q = (PAdsRefactorInfo)(f + 1);
			while (q)
			{
				if ((INT)q->refactorCnt > refactorCnt)
					return q;
				if (q->nextRefactorInfo)
					q = NEXTADSREFACTORINFO(q);
				else
					break;
			}
		}
	}
	return NULL;
}
#endif

struct AdsSymbolArrayEntry;
struct AdsDatatypeArrayEntry;
struct AdsDynSymbolArrayEntry;

////////////////////////////////////////////////////////////////////////////////
#define	ADSDATATYPEFLAG_DATATYPE		0x00000001
#define	ADSDATATYPEFLAG_DATAITEM		0x00000002
#define	ADSDATATYPEFLAG_REFERENCETO	0x00000004
#define	ADSDATATYPEFLAG_METHODDEREF	0x00000008
#define	ADSDATATYPEFLAG_OVERSAMPLE		0x00000010
#define	ADSDATATYPEFLAG_BITVALUES		0x00000020	// size and offs are in bits instead of bytes AND iGroup of main symbol incremented by 1!
#define	ADSDATATYPEFLAG_PROPITEM		0x00000040	// data type contains a reference to a FB property
#define	ADSDATATYPEFLAG_TYPEGUID		0x00000080	// 
#define	ADSDATATYPEFLAG_PERSISTENT		0x00000100	// means "ContainPersistent" for DATATYPES and "IsPersistent" for DATAITEMS
#define	ADSDATATYPEFLAG_COPYMASK		0x00000200	// 
#define	ADSDATATYPEFLAG_TCCOMIFACEPTR	0x00000400	// means "ContainTcComInterfacePtr" for DATATYPES and "IsTcComInterfacePtr" for DATAITEMS
#define	ADSDATATYPEFLAG_METHODINFOS	0x00000800	// 
#define	ADSDATATYPEFLAG_ATTRIBUTES		0x00001000	// 
#define	ADSDATATYPEFLAG_ENUMINFOS		0x00002000	//
#define	ADSDATATYPEFLAG_ALIGNED			0x00010000	// this flag is set if the datatype is aligned
#define	ADSDATATYPEFLAG_STATIC			0x00020000	// data item is static - do not use offs
#define	ADSDATATYPEFLAG_SPLEVELS		0x00040000	// means "ContainSpLevelss" for DATATYPES and "HasSpLevels" for DATAITEMS
#define	ADSDATATYPEFLAG_IGNOREPERSIST	0x00080000	// do not restore persistent data
#define	ADSDATATYPEFLAG_ANYSIZEARRAY	0x00100000	// 
#define	ADSDATATYPEFLAG_PERSIST_DT		0x00200000	// data type used for persistent variables -> should be saved with persistent data
#define	ADSDATATYPEFLAG_INITONRESET	0x00400000	// persistent data will not restored after reset (cold)
#define	ADSDATATYPEFLAG_PLCPOINTERTYPE	0x00800000	// means "ContainPlcPointerType" for DATATYPES and "IsPlcPointerType" for DATAITEMS
#ifdef ADS_REFACTOR_INFO
#define	ADSDATATYPEFLAG_REFACTORINFO		0x01000000	// one or more refactoring info AdsRefactorInfo added
#endif
#define	ADSDATATYPEFLAG_EXTENDEDFLAGS	0x80000000	// extended flags added

#define	ADSDATATYPE_VERSION_NEWEST		0x00000001

typedef struct
{
	ADS_UINT32		entryLength;	// length of complete datatype entry
	ADS_UINT32		version;			// version of datatype structure
#ifdef	LEGACY_PROPERTY_GETSET_SUPPORT
	union {
		struct {
			ADS_UINT16		subItemIdx;			// index of data item in data type
			ADS_UINT16		plcInterfaceId;	// interfaceId use for __System.GetInterfaceReference
		};
	ADS_UINT32		offsGetCode;	// code offset to getter method (ADSDATATYPEFLAG_SERACHDATA not set)
	};
	ADS_UINT32		offsSetCode;	// code offset to setter method
#else
	ADS_UINT16		subItemIdx;		// index of data item in data type
	ADS_UINT16		plcInterfaceId;	// interfaceId use for __System.GetInterfaceReference
	ADS_UINT32		reserved2;
#endif
	ADS_UINT32		size;				// size of datatype ( in bytes )
	ADS_UINT32		offs;				// offs of dataitem in parent datatype ( in bytes )
	ADS_UINT32		dataType;		// adsDataType of symbol (if alias)
	ADS_UINT32		flags;			// 
	ADS_UINT16		nameLength;		// length of datatype name (excl. \0)
	ADS_UINT16		typeLength;		// length of dataitem type name (excl. \0)
	ADS_UINT16		commentLength;	// length of comment (excl. \0)
	ADS_UINT16		arrayDim;		// 0 for DATAITEMS
	ADS_UINT16		subItems;		// 
	// ADS_INT8		name[];			// name of datatype with terminating \0
	// ADS_INT8		type[];			// type name of dataitem with terminating \0
	// ADS_INT8		comment[];		// comment of datatype with terminating \0
	// AdsDatatypeArrayInfo	array[];		// 
	// AdsDatatypeEntry		subItems[];	// 
	// GUID			typeGuid;		// typeGuid of this type if ADSDATATYPEFLAG_TYPEGUID is set
	// ADS_UINT8	copyMask[];		// "size" bytes containing 0xff or 0x00 - 0x00 means ignore byte (ADSIGRP_SYM_VALBYHND_WITHMASK)
	// ADS_UINT16	methods;			// count of method descriptions if ADSDATATYPEFLAG_METHODINFOS is set
	// AdsMethodEntry	method[];	// method descriptions
	// ADS_UINT16	attributes;		// count of attribute descriptions if ADSDATATYPEFLAG_ATTRIBUTES is set
	// AdsAttributeEntry attribute[]; // attribute description
	// ADS_UINT16	enumInfos;		// count of enum descriptions if ADSDATATYPEFLAG_ENUMINFOS is set
	// AdsEnumInfoEntry enums[];
	// AdsRefactorInfo refInfo[];	// if ADSDATATYPEFLAG_REFACTORINFO is set one ore more AdsRefactorInfo
	// ADS_UINT32	flags2;			// if ADSDATATYPEFLAG_EXTENDED_FLAGS is set
	// AdsSpLevelEntry access;		// if ADSDATATYPEFLAG_SPLEVELS is set read and write access rights
} AdsDatatypeEntry, *PAdsDatatypeEntry, **PPAdsDatatypeEntry;

#define	PADSDATATYPENAME(p)			((PCHAR)(((PAdsDatatypeEntry)p)+1))
#define	PADSDATATYPETYPE(p)			(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1)
#define	PADSDATATYPECOMMENT(p)		(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1+((PAdsDatatypeEntry)p)->typeLength+1)
#define	PADSDATATYPEARRAYINFO(p)	(PAdsDatatypeArrayInfo)(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1+((PAdsDatatypeEntry)p)->typeLength+1+((PAdsDatatypeEntry)p)->commentLength+1)
#define	ADSDATATYPEHASTYPEGUID(p)	((((PAdsDatatypeEntry)p)->flags&ADSDATATYPEFLAG_TYPEGUID) != 0)
#define	NEXTADSDATATYPE(p)			(PAdsDatatypeEntry)(((PBYTE)p)+p->entryLength)

inline PAdsDatatypeEntry AdsDatatypeStructItem(PAdsDatatypeEntry p, ADS_UINT16 iItem)
{
	if ( iItem >= p->subItems )
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for (ADS_UINT16 i = 0; i < iItem; i++)
		pItem = NEXTADSDATATYPE(pItem);
	return pItem;
}

inline GUID AdsDatatypeTypeGuid(PAdsDatatypeEntry p)
{
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) == 0 )
		return ADS_GUID_NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	return *(UNALIGNED GUID*)pItem;
}

inline UNALIGNED GUID* PAdsDatatypeTypeGuid(PAdsDatatypeEntry p)
{
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) == 0 )
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	return (UNALIGNED GUID*)pItem;
}

inline void SetAdsDatatypeTypeGuid(PAdsDatatypeEntry p, GUID g)
{
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) == 0 )
		return;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	*(UNALIGNED GUID*)pItem = g;
}

inline PBYTE AdsDatatypeCopyMask(PAdsDatatypeEntry p)
{
	if ( (p->flags&ADSDATATYPEFLAG_COPYMASK) == 0 )
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0 )
		pByte += sizeof(GUID);
	return pByte;
}

#define	ADSMETHODPARAFLAG_IN							0x00000001
#define	ADSMETHODPARAFLAG_OUT						0x00000002
#define	ADSMETHODPARAFLAG_INOUT						0x00000003
#define	ADSMETHODPARAFLAG_BYREFERENCE				0x00000004
#define	ADSMETHODPARAFLAG_RPC_OUTPTR				0x00000008
#define  ADSMETHODPARAFLAG_RPC_ARRAYDIM_MASK		0x00000030
#define  ADSMETHODPARAFLAG_RPC_ARRAYDIM_SHIFT	4
typedef struct
{
	ADS_UINT32		entryLength;	// length of complete datatype entry
	ADS_UINT32		size;				// size of datatype ( in bytes )
	ADS_UINT32		alignSize;		// size of biggest element for alignment
	ADS_UINT32		dataType;		// adsDataType of symbol (if alias)
	ADS_UINT32		flags;			// 
	ADS_UINT32		reserved;		// 
	GUID				typeGuid;		// 
	ADS_UINT16		lengthIsPara;	// index-1 of corresponding parameter with length info - 0 = no para, 1 = first para...
	ADS_UINT16		nameLength;		// length of datatype name (excl. \0)
	ADS_UINT16		typeLength;		// length of dataitem type name (excl. \0)
	ADS_UINT16		commentLength;	// length of comment (excl. \0)
	// ADS_INT8		name[];			// name of datatype with terminating \0
	// ADS_INT8		type[];			// type name of dataitem with terminating \0
	// ADS_INT8		comment[];		// comment of datatype with terminating \0
} AdsMethodParaEntry, *PAdsMethodParaEntry, **PPAdsMethodParaEntry;
#define	PADSMETHODPARANAME(p)			((PCHAR)(((PAdsMethodParaEntry)p)+1))
#define	PADSMETHODPARATYPE(p)			(((PCHAR)(((PAdsMethodParaEntry)p)+1))+((PAdsMethodParaEntry)p)->nameLength+1)
#define	PADSMETHODPARACOMMENT(p)		(((PCHAR)(((PAdsMethodParaEntry)p)+1))+((PAdsMethodParaEntry)p)->nameLength+1+((PAdsMethodParaEntry)p)->typeLength+1)
#define	NEXTADSMETHODPARA(p)				(PAdsMethodParaEntry)(((PBYTE)p)+p->entryLength)

#define	ADSMETHODFLAG_PLC_CALLINGCONVENTION		0x00000001
#define	ADSMETHODFLAG_CALL_UNLOCKED				0x00000002
typedef struct
{
	ADS_UINT32		entryLength;	// length of complete datatype entry
	ADS_UINT32		version;			// version of datatype structure
	ADS_UINT32		vTableIndex;	// vTable index of this method
	ADS_UINT32		returnSize;		// size of datatype ( in bytes )
	ADS_UINT32		returnAlignSize;		// size of biggest element for alignment
	ADS_UINT32		reserved;		// 
	GUID				returnTypeGuid;// 
	ADS_UINT32		returnDataType;// adsDataType of symbol (if alias)
	ADS_UINT32		flags;			// 
	ADS_UINT16		nameLength;		// length of datatype name (excl. \0)
	ADS_UINT16		returnTypeLength;		// length of dataitem type name (excl. \0)
	ADS_UINT16		commentLength;	// length of comment (excl. \0)
	ADS_UINT16		paras;			// 
	// ADS_INT8		name[];			// name of datatype with terminating \0
	// ADS_INT8		returnType[];	// type name of dataitem with terminating \0
	// ADS_INT8		comment[];		// comment of datatype with terminating \0
	// AdsMethodParaEntry	para[];	// 
} AdsMethodEntry, *PAdsMethodEntry, **PPAdsMethodEntry;
#define	PADSMETHODNAME(p)			((PCHAR)(((PAdsMethodEntry)p)+1))
#define	PADSMETHODTYPE(p)			(((PCHAR)(((PAdsMethodEntry)p)+1))+((PAdsMethodEntry)p)->nameLength+1)
#define	PADSMETHODCOMMENT(p)		(((PCHAR)(((PAdsMethodEntry)p)+1))+((PAdsMethodEntry)p)->nameLength+1+((PAdsMethodEntry)p)->returnTypeLength+1)
#define	NEXTADSMETHOD(p)			(PAdsMethodEntry)(((PBYTE)p)+p->entryLength)

inline ADS_UINT16 UNALIGNED* PAdsDatatypeTypeCntMethods(PAdsDatatypeEntry p)
{
	if ( (p->flags&ADSDATATYPEFLAG_METHODINFOS) == 0 )
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0 )
		pByte += sizeof(GUID);
	if ( (p->flags&ADSDATATYPEFLAG_COPYMASK) != 0 )
		pByte += p->size;
	return (ADS_UINT16 UNALIGNED*)pByte;
}

inline ADS_UINT16 AdsDatatypeTypeCntMethods(PAdsDatatypeEntry p)
{
	ADS_UINT16 UNALIGNED* u = PAdsDatatypeTypeCntMethods(p);
	return (u!=NULL) ? *u : 0;
}

inline PAdsMethodEntry AdsDatatypeMethodItem(PAdsDatatypeEntry p, ADS_UINT16 iMethod)
{
	if ( PAdsDatatypeTypeCntMethods(p) == NULL || iMethod >= *PAdsDatatypeTypeCntMethods(p) )
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( ADS_UINT16 i=0; i < p->subItems; i++ )
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ( (p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0 )
		pByte += sizeof(GUID);
	if ( (p->flags&ADSDATATYPEFLAG_COPYMASK) != 0 )
		pByte += p->size;
	pByte += sizeof(ADS_UINT16);
	PAdsMethodEntry	pMethod = (PAdsMethodEntry)pByte;
	for ( ADS_UINT16 i=0; i < iMethod; i++ )
		pMethod = NEXTADSMETHOD(pMethod);
	return pMethod;
}

inline PAdsMethodParaEntry AdsMethodParaItem(PAdsMethodEntry p, ADS_UINT16 iPara)
{
	if ( iPara >= p->paras )
		return NULL;
	PAdsMethodParaEntry	pPara = (PAdsMethodParaEntry)(((PBYTE)(p+1))+p->nameLength+p->returnTypeLength+p->commentLength+3);
	for ( ADS_UINT16 i=0; i < iPara; i++ )
		pPara = NEXTADSMETHODPARA(pPara);
	return pPara;
}

inline ADS_UINT16 UNALIGNED* PAdsDatatypeCntAttributes(PAdsDatatypeEntry p)
{
	if ((p->flags&ADSDATATYPEFLAG_ATTRIBUTES) == 0)
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for (ADS_UINT16 i=0; i < p->subItems; i++)
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ((p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
	if ((p->flags&ADSDATATYPEFLAG_COPYMASK) != 0)
		pByte += p->size;
	if ((p->flags&ADSDATATYPEFLAG_METHODINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsMethodEntry	pMethod = (PAdsMethodEntry)pByte;
		for (ADS_UINT16 i=0; i < *u; i++)
			pMethod = NEXTADSMETHOD(pMethod);
		pByte = (PBYTE)pMethod;
	}
	return (ADS_UINT16 UNALIGNED*)pByte;
}

inline ADS_UINT16 AdsDatatypeCntAttributes(PAdsDatatypeEntry p)
{
	ADS_UINT16 UNALIGNED* u = PAdsDatatypeCntAttributes(p);
	return (u!=NULL) ? *u : 0;
}

inline PAdsAttributeEntry AdsDatatypeAttributeItem(PAdsDatatypeEntry p, ADS_UINT16 iAttribute)
{
	ADS_UINT16 UNALIGNED* u = PAdsDatatypeCntAttributes(p);
	if (u == NULL || iAttribute >= *u)
		return NULL;
	PAdsAttributeEntry	pAttribute = (PAdsAttributeEntry)ENDOF(u);
	for (ADS_UINT16 i=0; i < iAttribute; i++)
		pAttribute = NEXTADSATTRIBUTE(pAttribute);
	return pAttribute;
}

typedef struct
{
	ADS_UINT8		nameLength;		// length of attribute name (excl. \0)
	// ADS_INT8		name[];			// name of attribute with terminating \0
	// ADS_INTx		value;			// value of attribute with terminating (valueSize == dataTypeSize)
} AdsEnumInfoEntry, *PAdsEnumInfoEntry, **PPAdsEnumInfoEntry;
#define	PADSENUMINFONAME(p)		((PCHAR)(((PAdsEnumInfoEntry)p)+1))
#define	PADSENUMINFOVALUE(p)		(PVOID)(((PCHAR)(((PAdsEnumInfoEntry)p)+1))+((PAdsEnumInfoEntry)p)->nameLength+1)
#define	NEXTADSENUMINFO(p, s)		(PAdsEnumInfoEntry)(((PBYTE)p) + sizeof(AdsEnumInfoEntry) + p->nameLength + 1 + s)

inline ADS_UINT16 UNALIGNED* PAdsDatatypeCntEnumInfos(PAdsDatatypeEntry p)
{
	if ((p->flags&ADSDATATYPEFLAG_ENUMINFOS) == 0)
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for (ADS_UINT16 i=0; i < p->subItems; i++)
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ((p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
	if ((p->flags&ADSDATATYPEFLAG_COPYMASK) != 0)
		pByte += p->size;
	if ((p->flags&ADSDATATYPEFLAG_METHODINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsMethodEntry	pMethod = (PAdsMethodEntry)pByte;
		for (ADS_UINT16 i=0; i < *u; i++)
			pMethod = NEXTADSMETHOD(pMethod);
		pByte = (PBYTE)pMethod;
	}
	if ((p->flags&ADSDATATYPEFLAG_ATTRIBUTES) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsAttributeEntry	pAttribute = (PAdsAttributeEntry)pByte;
		for (ADS_UINT16 i=0; i < *u; i++)
			pAttribute = NEXTADSATTRIBUTE(pAttribute);
		pByte = (PBYTE)pAttribute;
	}
	return (ADS_UINT16 UNALIGNED*)pByte;
}

inline ADS_UINT16 AdsDatatypeCntEnumInfos(PAdsDatatypeEntry p)
{
	ADS_UINT16 UNALIGNED* u = PAdsDatatypeCntEnumInfos(p);
	return (u!=NULL) ? *u : 0;
}

inline PAdsEnumInfoEntry AdsDatatypeEnumInfoItem(PAdsDatatypeEntry p, ADS_UINT16 iEnumInfo)
{
	ADS_UINT16 UNALIGNED* u = PAdsDatatypeCntEnumInfos(p);
	if (u == NULL || iEnumInfo >= *u)
		return NULL;
	PAdsEnumInfoEntry	pEnumInfo = (PAdsEnumInfoEntry)ENDOF(u);
	for (ADS_UINT16 i=0; i < iEnumInfo; i++)
		pEnumInfo = NEXTADSENUMINFO(pEnumInfo, p->size);
	return pEnumInfo;
}

#ifdef ADS_REFACTOR_INFO
inline PAdsRefactorInfo PAdsDatatypeRefactorInfo(PAdsDatatypeEntry p, INT refactorCnt)
{
	if ((p->flags&ADSDATATYPEFLAG_REFACTORINFO) == 0)
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p + 1)) + p->nameLength + p->typeLength + p->commentLength + 3 + p->arrayDim * sizeof(AdsDatatypeArrayInfo));
	for (ADS_UINT16 i = 0; i < p->subItems; i++)
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ((p->flags&ADSDATATYPEFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
#ifdef LEGACY_ADS_USE_COPYMASK
	if ((p->flags&ADSDATATYPEFLAG_COPYMASK) != 0)
		pByte += p->size;
#endif
	if ((p->flags&ADSDATATYPEFLAG_METHODINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsMethodEntry	pMethod = (PAdsMethodEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pMethod = NEXTADSMETHOD(pMethod);
		pByte = (PBYTE)pMethod;
	}
	if ((p->flags&ADSDATATYPEFLAG_ATTRIBUTES) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsAttributeEntry	pAttribute = (PAdsAttributeEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pAttribute = NEXTADSATTRIBUTE(pAttribute);
		pByte = (PBYTE)pAttribute;
	}
	if ((p->flags&ADSDATATYPEFLAG_ENUMINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsEnumInfoEntry	pEnumInfo = (PAdsEnumInfoEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pEnumInfo = NEXTADSENUMINFO(pEnumInfo, p->size);
		pByte = (PBYTE)pEnumInfo;
	}
	PAdsRefactorInfo q = (PAdsRefactorInfo)pByte;
	if (refactorCnt == 0)
		return q;	// search for begin of AdsRefactorInfo data
	while (q)
	{
		if ((INT)q->refactorCnt > refactorCnt)
			return q;
		if (q->nextRefactorInfo)
			q = NEXTADSREFACTORINFO(q);
		else
			break;
	}
	return NULL;
}
#endif

inline ADS_UINT32* PAdsDataTypeExtendedFlags(PAdsDatatypeEntry p)
{
	if ((p->flags & ADSDATATYPEFLAG_EXTENDEDFLAGS) == 0)
		return NULL;
	PAdsDatatypeEntry	pItem = (PAdsDatatypeEntry)(((PBYTE)(p + 1)) + p->nameLength + p->typeLength + p->commentLength + 3 + p->arrayDim * sizeof(AdsDatatypeArrayInfo));
	for (ADS_UINT16 i = 0; i < p->subItems; i++)
		pItem = NEXTADSDATATYPE(pItem);
	PBYTE pByte = (PBYTE)pItem;
	if ((p->flags & ADSDATATYPEFLAG_TYPEGUID) != 0)
		pByte += sizeof(GUID);
#ifdef LEGACY_ADS_USE_COPYMASK
	if ((p->flags & ADSDATATYPEFLAG_COPYMASK) != 0)
		pByte += p->size;
#endif
	if ((p->flags & ADSDATATYPEFLAG_METHODINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsMethodEntry	pMethod = (PAdsMethodEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pMethod = NEXTADSMETHOD(pMethod);
		pByte = (PBYTE)pMethod;
	}
	if ((p->flags & ADSDATATYPEFLAG_ATTRIBUTES) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsAttributeEntry	pAttribute = (PAdsAttributeEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pAttribute = NEXTADSATTRIBUTE(pAttribute);
		pByte = (PBYTE)pAttribute;
	}
	if ((p->flags & ADSDATATYPEFLAG_ENUMINFOS) != 0)
	{
		ADS_UINT16 UNALIGNED* u = (ADS_UINT16 UNALIGNED*)pByte;
		pByte += sizeof(ADS_UINT16);
		PAdsEnumInfoEntry	pEnumInfo = (PAdsEnumInfoEntry)pByte;
		for (ADS_UINT16 i = 0; i < *u; i++)
			pEnumInfo = NEXTADSENUMINFO(pEnumInfo, p->size);
		pByte = (PBYTE)pEnumInfo;
	}
	if ((p->flags & ADSDATATYPEFLAG_REFACTORINFO) != 0)
	{
		PAdsRefactorInfo q = (PAdsRefactorInfo)pByte;
		while (q->nextRefactorInfo)
			q++;
		pByte = (PBYTE)(q + 1);
	}
	return (ADS_UINT32*)pByte;
}

inline ADS_UINT32 AdsDataTypeExtendedFlags(PAdsDatatypeEntry p)
{
	ADS_UINT32 UNALIGNED* u = PAdsDataTypeExtendedFlags(p);
	return (u != NULL) ? *u : 0;
}


////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ADS_UINT32		iGroup;			// indexGroup of symbol: input, output etc.
	ADS_UINT32		iOffs;			// indexOffset of symbol
} AdsDynSymbolEntry, *PAdsDynSymbolEntry;
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		nSymbols;
	BOOL		bOnlineChange;
} AdsSymbolUpAndDownloadHeader, *PAdsSymbolUpAndDownloadHeader;

#define	PADSFIRSTSYMBOLENTRY(pHeader)	((PAdsSymbolEntry)(ENDOF((PAdsSymbolUpAndDownloadHeader)pHeader)))
#define	PADSNEXTSYMBOLENTRY(pEntry)	( (*(ADS_UINT32*)(((PBYTE)pEntry)+((PAdsSymbolEntry)pEntry)->entryLength)) ? \
							((PAdsSymbolEntry)(((PBYTE)pEntry)+((PAdsSymbolEntry)pEntry)->entryLength)): NULL)

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		nSymbols;
	ULONG		nSymbolSize;
	ULONG		nDatatypes;
	ULONG		nDatatypeSize;
	ULONG		nDynamicHandles;
	BOOL		bOnlineChange;
} AdsSymbolUpAndDownloadHeader2, *PAdsSymbolUpAndDownloadHeader2;

typedef struct
{
	ULONG		nCodePage;
	ULONG		b64BitTarget			: 1;
	ULONG		bBasetypesIncluded	: 1;
	ULONG		bPerformQSort			: 1;
	ULONG		bNoCopyMask				: 1;
	ULONG		reserved1				: 28;
	ULONG		reserved2[2];
	GUID		hash;
#ifdef AMS_COMPRESSION
	ULONG		nSymbolSizeUncompressed;
	ULONG		nDatatypeSizeUncompressed;
#ifdef ADS_REFACTOR_INFO
	LONG		nRefactorCnt;
	ULONG		reserved3[5];
#else
	ULONG		reserved3[6];
#endif
#else
#ifdef ADS_REFACTOR_INFO
	ULONG		reserved3[2];
	LONG		nRefactorCnt;
	ULONG		reserved4[5];
#else
	ULONG		reserved3[8];
#endif
#endif
	// GUID	spLevelGuid[];	nSpLevelGuids
} AdsAddSymbolInfo, *PAdsAddSymbolInfo;

#define	PADSFIRSTSYMBOLENTRY2(p)	((PAdsSymbolEntry)(ENDOF((PAdsSymbolUpAndDownloadHeader2)p)))
#define	PADSFIRSTDATATYPEENTRY2(p)	(((PAdsDatatypeEntry)((PBYTE)(ENDOF((PAdsSymbolUpAndDownloadHeader2)p))+(((PAdsSymbolUpAndDownloadHeader2)p)->nSymbolSize))))
#define	PADSADDSYMBOLINFOLENGTH2(p, c)	((c) - sizeof(AdsSymbolUpAndDownloadHeader2) - p->nSymbolSize - p->nDatatypeSize)
#define	PADSADDSYMBOLINFODATA2(p)	(((PAdsAddSymbolInfo)((PBYTE)(ENDOF(p))+((p)->nSymbolSize)+((p)->nDatatypeSize))))
#define	PADSNEXTDATATYPEENTRY2(pEntry)	( (*(ADS_UINT32*)(((PBYTE)pEntry)+((PAdsDatatypeEntry)pEntry)->entryLength)) ? \
							((PAdsDatatypeEntry)(((PBYTE)pEntry)+((PAdsDatatypeEntry)pEntry)->entryLength)): NULL)

////////////////////////////////////////////////////////////////////////////////
#define	AdsSymbolUpAndDownloadHeader3_Major	3
#define	AdsSymbolUpAndDownloadHeader3_WithCompression_Major	4
#define	AdsSymbolUpAndDownloadHeader3_Minor	0

struct AdsSymbolUpAndDownloadHeader3
{
	BYTE		majorVersion;				// must be known
	BYTE		minorVersion;				// changes may increase headSize with addional information
	USHORT	headSize;					// byte size of AdsSymbolUpAndDownloadHeader3
	ULONG		nSymbols;
	ULONG		nSymbolSize;
	ULONG		nDatatypes;
	ULONG		nDatatypeSize;
	ULONG		nDynamicHandles;
	ULONG		nCodePage;
	union
	{
		struct
		{
			ULONG		bOnlineChange			: 1;
			ULONG		b64BitTarget			: 1;
			ULONG		bBasetypesIncluded	: 1;
			ULONG		bPerformQSort			: 1;
			ULONG		bNoCopyMask				: 1;
		};
		ULONG		flags;
	};
#ifdef AMS_COMPRESSION
	ULONG		nSymbolSizeUncompressed;
	ULONG		nDatatypeSizeUncompressed;
#ifdef ADS_REFACTOR_INFO
	LONG		nRefactorCnt;
	ULONG		reserved;
#else
	ULONG		reserved[2];
#endif
#else
#ifdef ADS_REFACTOR_INFO
	LONG		nRefactorCnt;
	ULONG		reserved[3];
#else
	ULONG		reserved[4];
#endif
#endif
	GUID		hash;		
	// AdsSymbolEntry		symEntry[];		// starts after headSize
	// AdsDatatypeEntry	dtEntry[];		// starts after headSize+nSymbolSize
	// GUID	accessRightrs[];				// starts after headSize+nSymbolSize+nDatatypeSize
};
typedef AdsSymbolUpAndDownloadHeader3 *PAdsSymbolUpAndDownloadHeader3;
#define	PADSFIRSTSYMBOLENTRY3(p)		((PAdsSymbolEntry)(((PBYTE)(p))+(p)->headSize))
#define	PADSFIRSTDATATYPEENTRY3(p)		((PAdsDatatypeEntry)(((PBYTE)(p))+(p)->headSize+(p)->nSymbolSize))

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		nSymbols;
	ULONG		nSymSize;
} AdsSymbolUploadInfo, *PAdsSymbolUploadInfo;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		nSymbols;
	ULONG		nSymSize;
	ULONG		nDatatypes;
	ULONG		nDatatypeSize;
	ULONG		nMaxDynSymbols;
	ULONG		nUsedDynSymbols;
} AdsSymbolUploadInfo2, *PAdsSymbolUploadInfo2;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		nSymbols;
	ULONG		nSymSize;
	ULONG		nDatatypes;
	ULONG		nDatatypeSize;
	ULONG		nMaxDynSymbols;
	ULONG		nUsedDynSymbols;
	ULONG		nInvalidDynSymbols;
	ULONG		nCodePage;
	ULONG		b64BitTarget			: 1;
	ULONG		bBasetypesIncluded	: 1;
	ULONG		reserved1				: 30;
	ULONG		reseverd2[7];
} AdsSymbolUploadInfo3, *PAdsSymbolUploadInfo3;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG		indexGroup;
	ULONG		indexOffset;
	ULONG		cbLength;
} AdsSymbolInfoByName, *PAdsSymbolInfoByName;

////////////////////////////////////////////////////////////////////////////////
#pragma	pack( pop )

DLL_EXPORT LPCSTR  TCADSAPI AdsGetStateTextA(ADSSTATE nState);
DLL_EXPORT LPCWSTR TCADSAPI AdsGetStateTextW(ADSSTATE nState);
DLL_EXPORT LPCSTR  TCADSAPI AdsGetTransmodeTextA(ADSTRANSMODE nTransType);
DLL_EXPORT LPCWSTR TCADSAPI AdsGetTransmodeTextW(ADSTRANSMODE nTransType);
DLL_EXPORT LPCSTR  TCADSAPI AdsGetErrorText(LONG errCode);
DLL_EXPORT LPCSTR  TCADSAPI AdsGetHResultText(HRESULT hr);


#ifndef _UNICODE
#define	AdsGetStateText		AdsGetStateTextA
#define	AdsGetTransmodeText	AdsGetTransmodeTextA
#else
#define	AdsGetStateText		AdsGetStateTextW
#define	AdsGetTransmodeText	AdsGetTransmodeTextW
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// CAds
class DLL_EXPORT CAds
{
public:

	////////////////////////////////////////////////////////////////////////////////
	// Construction
	CAds();
	virtual ~CAds();

	////////////////////////////////////////////////////////////////////////////////
	// ads basic request
	virtual	int	AdsReadDeviceInfoReq( AmsAddr& rAddr, ULONG invokeId );
	virtual	int	AdsWriteControlReq( AmsAddr& rAddr, ULONG invokeId, USHORT adsState, USHORT deviceState, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadStateReq( AmsAddr& rAddr, ULONG invokeId );
	virtual	int	AdsWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength );
	virtual	int	AdsReadWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
									ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData );
	virtual	int	AdsAddDeviceNotificationReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset,
													  AdsNotificationAttrib noteAttrib);
	virtual	int	AdsDelDeviceNotificationReq( AmsAddr& rAddr, ULONG invokeId, ULONG hNotification );
	virtual	int	AdsDeviceNotificationReq( AmsAddr& rAddr, ULONG invokeId, ULONG cbLength, AdsNotificationStream notifications[] );

	// ads basic indications
	virtual	void	AdsReadDeviceInfoInd( AmsAddr& rAddr, ULONG invokeId );
	virtual	void	AdsWriteControlInd( AmsAddr& rAddr, ULONG invokeId, USHORT adsState, USHORT deviceState, ULONG cbLength, PVOID pDeviceData );
	virtual	void	AdsReadStateInd( AmsAddr& rAddr, ULONG invokeId );
	virtual	void	AdsWriteInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData );
	virtual	void	AdsReadInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength );
	virtual	void	AdsReadWriteInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
									ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData );
	virtual	void	AdsAddDeviceNotificationInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset,
													   AdsNotificationAttrib noteAttrib );
	virtual	void	AdsDelDeviceNotificationInd( AmsAddr& rAddr, ULONG invokeId, ULONG hNotification );
	virtual	void	AdsDeviceNotificationInd( AmsAddr& rAddr, ULONG invokeId, ULONG cbLength, AdsNotificationStream* pNotifications );

	// ads basic forwards
	virtual	int	AdsReadDeviceInfoFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId );
	virtual	int	AdsWriteControlFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, USHORT adsState,
																USHORT deviceState, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadStateFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId );
	virtual	int	AdsWriteFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, ULONG indexGroup,
														ULONG indexOffset, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, ULONG indexGroup,
														ULONG indexOffset, ULONG cbLength );
	virtual	int	AdsReadWriteFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, ULONG indexGroup,
															ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData );
	virtual	int	AdsAddDeviceNotificationFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, ULONG indexGroup,
																	 ULONG indexOffset, AdsNotificationAttrib noteAttrib );
	virtual	int	AdsDelDeviceNotificationFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr,  ULONG invokeId, ULONG hNotification );
	virtual	int	AdsDeviceNotificationFrw( AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr, ULONG invokeId, ULONG cbLength,
															 AdsNotificationStream* pNotifications );

	// ads basic responses
	virtual	int	AdsReadDeviceInfoRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, CHAR name[ADS_FIXEDNAMESIZE], AdsVersion version );
	virtual	int	AdsWriteControlRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	int	AdsReadStateRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, USHORT adsState, USHORT deviceState );
	virtual	int	AdsWriteRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	int	AdsReadRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadWriteRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int	AdsAddDeviceNotificationRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG handle );
	virtual	int	AdsDelDeviceNotificationRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );

	// ads basic confirmations
	virtual	void	AdsReadDeviceInfoCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, CHAR name[ADS_FIXEDNAMESIZE], AdsVersion version );
	virtual	void	AdsWriteControlCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	void	AdsReadStateCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, USHORT adsState, USHORT deviceState );
	virtual	void	AdsWriteCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	void	AdsReadCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	void	AdsReadWriteCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	void	AdsAddDeviceNotificationCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG handle );
	virtual	void	AdsDelDeviceNotificationCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	void	AdsDeviceNotificationCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );


protected:
	virtual	void*	AdsAlloc( ULONG size );
	virtual	void	AdsFree( void* pVoid );
	
	// generic ads functions
	virtual	int	AdsRequest( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData )=0;
	virtual	int	AdsForward( AmsAddr& rSrcAddr, AmsAddr& rDestAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData )=0;
	virtual	int	AdsResponse( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData )=0;
	virtual	void	AdsIndication( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, PVOID pData );
	virtual	void	AdsConfirmation( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, LONG transError, PVOID pData );


	ADSSTATE			m_nAdsState;
	ULONG				m_nDeviceState;
	AdsVersion		m_adsVersion;
	ULONG				nReserved; // don't touch, don't use
};

////////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CAdsArchive
{
public:
	enum Mode { store = 0x1, load = 0x2, bNoFlushOnDelete = 0x4, bNoByteSwap = 0x8 };

	CAdsArchive( Mode nMode );
	virtual	~CAdsArchive();

	virtual	CAdsArchive& operator<<(int val);
	virtual	CAdsArchive& operator>>(int& val);
	virtual	CAdsArchive& operator<<(UINT val);
	virtual	CAdsArchive& operator>>(UINT& val);
	virtual	CAdsArchive& operator<<(BYTE val);
	virtual	CAdsArchive& operator>>(BYTE& val);
	virtual	CAdsArchive& operator<<(CHAR val);
	virtual	CAdsArchive& operator>>(CHAR& val);
	virtual	CAdsArchive& operator<<(SHORT val);
	virtual	CAdsArchive& operator>>(SHORT& val);
	virtual	CAdsArchive& operator<<(USHORT val);
	virtual	CAdsArchive& operator>>(USHORT& val);
#ifndef POSIX
	virtual	CAdsArchive& operator<<(LONG val);
	virtual	CAdsArchive& operator>>(LONG& val);
	virtual	CAdsArchive& operator<<(ULONG val);
	virtual	CAdsArchive& operator>>(ULONG& val);	
#endif
	virtual	CAdsArchive& operator<<(float val);
	virtual	CAdsArchive& operator>>(float& val);
	virtual	CAdsArchive& operator<<(double val);
	virtual	CAdsArchive& operator>>(double& val);
	virtual	CAdsArchive& operator<<(bool val);
	virtual	CAdsArchive& operator>>(bool& val);
	virtual	CAdsArchive& operator<<(__int64 val);
	virtual	CAdsArchive& operator>>(__int64& val);
	virtual	CAdsArchive& operator<<(AdsDataTypeId val);
	virtual	CAdsArchive& operator>>(AdsDataTypeId& val);
	virtual	operator const void* ();

	virtual	void Read( PVOID pData, ULONG nData );
	virtual	void Write( PVOID pData, ULONG nData );

	virtual	void	Flush() = 0;
	virtual	void	ReadBuffer() =0 ;
	virtual	void	OnBufferEmpty() = 0;
	virtual	void	OnBufferFull() = 0;

	virtual	BOOL	IsStoring();
	virtual	BOOL	IsLoading();

	virtual	LONG	GetResult();
	virtual	BOOL	BufferEmpty();
	virtual	LONG_PTR	GetDataSize();

protected:
	Mode			m_nMode;
	ULONG			m_nBufSize;
	PBYTE			m_lpBufCur;
	PBYTE			m_lpBufMax;
	PBYTE			m_lpBufStart;
	LONG			m_nError;
};

////////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CAdsObject
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CAdsObject();
	CAdsObject( const CAdsObject& objectSrc );					// no implementation

	virtual ~CAdsObject();
	virtual void Serialize( CAdsArchive& ar );

protected:
	ULONG m_nType;
private:
	ULONG m_nVersion;
};

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG	result;
	ULONG	nRLength;
	PBYTE pData;
} TcAdsSumUpReadWriteRes, *PTcAdsSumUpReadWriteRes;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ULONG	result;
	ULONG	handle;
} TcAdsSumUpAddDevNoteRes, *PTcAdsSumUpAddDevNoteRes;


////////////////////////////////////////////////////////////////////////////////
// message templates for ams messages

///////////////////////////////////////////////////////////////////////////////
// request/indication templates
#pragma	pack( push, 1)
typedef struct
{
	ULONG invokeId;
}	TAdsReadDeviceInfoReq, *PTAdsReadDeviceInfoReq, TAdsReadDeviceInfoInd, *PTAdsReadDeviceInfoInd;

typedef struct
{
	USHORT	adsState;
	USHORT	deviceState;
	ULONG		cbLength;
	USHORT	firstDataWord;
}	TAdsWriteControlReq, *PTAdsWriteControlReq, TAdsWriteControlInd, *PTAdsWriteControlInd;
#define SIZEOF_TAdsWriteControlReqHead	(offsetof(TAdsWriteControlReq, firstDataWord))

typedef struct
{
	ULONG		invokeId;
} TAdsReadStateReq, *PTAdsReadStateReq, TAdsReadStateInd, *PTAdsReadStateInd;

typedef struct
{
	ULONG		indexGroup;
	ULONG		indexOffset;
	ULONG		cbLength;
} TAdsReadReq, *PTAdsReadReq, TAdsReadInd, *PTAdsReadInd;

typedef struct
{
	ULONG		indexGroup;
	ULONG		indexOffset;
	ULONG		cbLength;
	USHORT	firstDataWord;
} TAdsWriteReq, *PTAdsWriteReq, TAdsWriteInd, *PTAdsWriteInd;
#define SIZEOF_TAdsWriteReqHead	(offsetof(TAdsWriteReq, firstDataWord))

typedef struct
{
	ULONG		indexGroup;
	ULONG		indexOffset;
	ULONG		cbReadLength;
	ULONG		cbWriteLength;
	USHORT	firstDataWord;
} TAdsReadWriteReq, *PTAdsReadWriteReq, TAdsReadWriteInd, *PTAdsReadWriteInd;
#define SIZEOF_TAdsReadWriteReqHead	(offsetof(TAdsReadWriteReq, firstDataWord))

typedef struct
{
	ULONG						 indexGroup;
	ULONG						 indexOffset;
	AdsNotificationAttrib noteAttrib;
} TAdsAddDeviceNotificationReq, *PTAdsAddDeviceNotificationReq,
	TAdsAddDeviceNotificationInd, *PTAdsAddDeviceNotificationInd;

typedef struct
{
	ULONG	hNotification;
} TAdsDelDeviceNotificationReq, *PTAdsDelDeviceNotificationReq,
	TAdsDelDeviceNotificationInd, *PTAdsDelDeviceNotificationInd;

typedef struct
{
	ULONG							cbLength;
	AdsNotificationStream	noteBlocks;
} TAdsDeviceNotificationReq, *PTAdsDeviceNotificationReq,
	TAdsDeviceNotificationInd, *PTAdsDeviceNotificationInd;

///////////////////////////////////////////////////////////////////////////////
// response/confirmation templates

typedef struct
{
	ULONG		result;
} TAdsCon, *PTAdsCon, TAdsRes, *PTAdsRes;

typedef struct
{
	ULONG			result;
	AdsVersion	version;
	CHAR			sName[ADS_FIXEDNAMESIZE];
} TAdsReadDeviceInfoRes, *PTAdsReadDeviceInfoRes, TAdsReadDeviceInfoCon, *PTAdsReadDeviceInfoCon;

typedef struct
{
	ULONG		result;
} TAdsWriteControlRes, *PTAdsWriteControlRes, TAdsWriteControlCon, *PTAdsWriteControlCon;

typedef struct
{
	ULONG		result;
	USHORT	adsState;
	USHORT	deviceState;
} TAdsReadStateRes, *PTAdsReadStateRes, TAdsReadStateCon, *PTAdsReadStateCon;

typedef struct
{
	ULONG		result;
	ULONG		cbLength;
	USHORT	firstDataWord;
} TAdsReadRes, *PTAdsReadRes, TAdsReadCon, *PTAdsReadCon;
#define SIZEOF_TAdsReadResHead	(offsetof(TAdsReadRes, firstDataWord))

typedef struct
{
	ULONG		result;
	ULONG		cbLength;
	USHORT	firstDataWord;
} TAdsReadWriteRes, *PTAdsReadWriteRes, TAdsReadWriteCon, *PTAdsReadWriteCon;
#define SIZEOF_TAdsReadWriteResHead	(offsetof(TAdsReadWriteRes, firstDataWord))

typedef struct
{
	ULONG		result;
} TAdsWriteRes, *PTAdsWriteRes, TAdsWriteCon, *PTAdsWriteCon;

typedef struct
{
	ULONG		result;
	ULONG		handle;
} TAdsAddDeviceNotificationRes, *PTAdsAddDeviceNotificationRes,
	TAdsAddDeviceNotificationCon, *PTAdsAddDeviceNotificationCon;

typedef struct
{
	ULONG		result;
} TAdsDelDeviceNotificationRes, *PTAdsDelDeviceNotificationRes,
	TAdsDelDeviceNotificationCon, *PTAdsDelDeviceNotificationCon;

///////////////////////////////////////////////////////////////////////////////
// last error info
typedef struct TAdsLastErrorInfo
{
	AmsAddr	addr;			//address of ADS client
	ULONG		errorCode;	//additional error code
	//char	descr[]		//error Description 
} AdsLastErrorInfo, *PAdsLastErrorInfo;

#define	PADSLASTERRORINFO_DESCR(p)			((PCHAR)(((PAdsLastErrorInfo)p)+1))

#pragma	pack( pop )
