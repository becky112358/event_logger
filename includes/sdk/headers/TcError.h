///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "TcDef.h"

///////////////////////////////////////////////////////////////////////////////
// Facility codes used to construct HRESULT or STATUS codes
#define	FACILITY_TC_ADS					0x1811
#define	FACILITY_TC_CNC					0x1821
#define	FACILITY_TC_IO						0x1831
#define	FACILITY_TC_RTS					0x1841
#define	FACILITY_TC_CM						0x1851 // Condition Monitoring
#define	FACILITY_TC_DBG					0x1861
#define	FACILITY_TC_MULTIARRAY			0x1871 // MultiArray data type
#define	FACILITY_TC_NC						0x1881
#define	FACILITY_TC_STL					0x1891 // STL (used only for SEH)
#define	FACILITY_TC_JSON					0x1892 // Json
#define	FACILITY_TC_PLC					0x1893
#define	FACILITY_TC_VN						0x18A1 // Vision (used only for SEH)
#define	FACILITY_TC_ECAT					0x18B1
#define	FACILITY_TC_OPENMP				0x18C1 // OpenMP
#define	FACILITY_TC_MO						0x18E1 // Math COM Objects

///////////////////////////////////////////////////////////////////////////////
// Error strings
typedef struct
{
	DWORD				errNo;
	const char*		errStr;
} ErrorStrings;

#define	AMSERRCODEISWARNING		0x80000000

///////////////////////////////////////////////////////////////////////////////
//	Error Arrays

#define	ERR_ROUTERERRS				0x0500
#define	ERR_TASKERRS				0x0600
#define	ERR_ADSERRS					0x0700
#define	ERR_SYSSMPLERRS			0x0800
#define	ERR_RTIMEERRS				0x1000
#define	ERR_TRACEERRS				(ERR_RTIMEERRS+0x900)
#define	ERR_IOERRS					0x2000
#define	ERR_DPSLAVE					(ERR_IOERRS+0x900)
#define	ERR_CP5412A2				(ERR_IOERRS+0xA00)
#define	ERR_ASP						(ERR_IOERRS+0xB00)
#define	ERR_CANSLAVE				(ERR_IOERRS+0xC00)
#define	ERR_CIF30					(ERR_IOERRS+0xD00)
#define	ERR_IBSSLAVE				(ERR_IOERRS+0xE00)
#define	ERR_SPSERRS					0x3000
#define	ERR_NCERRS					0x4000	// NC error (first nc error code area, see also ERR_NCERRS2)
#define	ERR_APPLERRS				0x5000	// beckhoff application and supplement errors
#define	ERR_PLCERRS					0x6000
#define	ERR_STRKERRS				0x7000

#define	ERR_PRJSPECIFIC			0x7800	// don't shift this to a higher value 

#define	ERR_NCERRS2					0x8000	// NC3 error (second nc error code area, see also ERR_NCERRS)

#define	ERR_DRIVEERRS_C3D			0xD000	// hardware drive error, class 3 diagnostic (C3D)
#define	ERR_DRIVEERRS_C2D			0xE000	// hardware drive error, class 2 diagnostic (C2D)
#define	ERR_DRIVEERRS_C1D			0xF000	// hardware drive error, class 1 diagnostic (C1D)

///////////////////////////////////////////////////////////////////////////////
//	Global Error codes
#define	ERR_NOERROR						0
#define	ERR_INTERNAL					1
#define	ERR_NORTIME						2
#define	ERR_ALLOCLOCKEDMEM			3
#define	ERR_INSERTMAILBOX				4
#define	ERR_WRONGRECEIVEHMSG			5
#define	ERR_TARGETPORTNOTFOUND		6
#define	ERR_TARGETMACHINENOTFOUND	7
#define	ERR_UNKNOWNCMDID				8
#define	ERR_BADTASKID					9
#define	ERR_NOIO							10
#define	ERR_UNKNOWNAMSCMD				11
#define	ERR_WIN32ERROR					12
#define	ERR_PORTNOTCONNECTED			13
#define	ERR_INVALIDAMSLENGTH			14
#define	ERR_INVALIDAMSNETID			15
#define	ERR_LOWINSTLEVEL				16
#define	ERR_NODEBUGINTAVAILABLE		17
#define	ERR_PORTDISABLED				18
#define	ERR_PORTALREADYCONNECTED	19
#define	ERR_AMSSYNC_W32ERROR			20
#define	ERR_AMSSYNC_TIMEOUT			21
#define	ERR_AMSSYNC_AMSERROR			22
#define	ERR_AMSSYNC_NOINDEXINMAP	23
#define	ERR_INVALIDAMSPORT			24
#define	ERR_NOMEMORY					25
#define	ERR_TCPSEND						26
#define	ERR_HOSTUNREACHABLE			27
#define	ERR_INVALIDAMSFRAGMENT		28
#define	ERR_TLSSEND						29
#define	ERR_ACCESSDENIED				30
#define	ERR_TCP_CONN_REFUSED			31

///////////////////////////////////////////////////////////////////////////////
// ROUTER
#define	ROUTERERR_NOLOCKEDMEMORY	0 + ERR_ROUTERERRS
#define	ROUTERERR_RESIZEMEMORY		1 + ERR_ROUTERERRS
#define	ROUTERERR_MAILBOXFULL		2 + ERR_ROUTERERRS
#define	ROUTERERR_DEBUGBOXFULL		3 + ERR_ROUTERERRS
#define	ROUTERERR_UNKNOWNPORTTYPE	4 + ERR_ROUTERERRS
#define	ROUTERERR_NOTINITIALIZED	5 + ERR_ROUTERERRS
#define	ROUTERERR_PORTALREADYINUSE	6 + ERR_ROUTERERRS
#define	ROUTERERR_NOTREGISTERED		7 + ERR_ROUTERERRS
#define	ROUTERERR_NOMOREQUEUES		8 + ERR_ROUTERERRS
#define	ROUTERERR_INVALIDPORT		9 + ERR_ROUTERERRS
#define	ROUTERERR_NOTACTIVATED	  10 + ERR_ROUTERERRS
#define	ROUTERERR_FRAGMENTBOXFULL 11 + ERR_ROUTERERRS
#define	ROUTERERR_FRAGMENTTIMEOUT 12 + ERR_ROUTERERRS
#define	ROUTERERR_TOBEREMOVED	  13 + ERR_ROUTERERRS
#define	ROUTERERR_INVALIDPARM	  14 + ERR_ROUTERERRS

#define	TASKERR_UNKNOWNTASKTYPE		0 + ERR_TASKERRS
#define	TASKERR_TASKTERMINATED		1 + ERR_TASKERRS
#define	TASKERR_EVENTTIMEOUT			2 + ERR_TASKERRS

///////////////////////////////////////////////////////////////////////////////
// System Sampler
#define	SMPLERR_INTERNAL				0 + ERR_SYSSMPLERRS
#define	SMPLERR_INVALIDTYPE			1 + ERR_SYSSMPLERRS

///////////////////////////////////////////////////////////////////////////////
// RTIME
#define	RTERR_INTERNAL				0 + ERR_RTIMEERRS	// internal error
#define	RTERR_BADTIMERPERIODS		1 + ERR_RTIMEERRS	// invalid time ticker period values
#define	RTERR_INVALIDTASKPTR		2 + ERR_RTIMEERRS	// null task ptr
#define	RTERR_INVALIDSTACKPTR		3 + ERR_RTIMEERRS	// null stack ptr
#define	RTERR_PRIOEXISTS			4 + ERR_RTIMEERRS	// priority already in use
#define	RTERR_NOMORETCB				5 + ERR_RTIMEERRS	// no more TCB's available
#define	RTERR_NOMORESEMAS			6 + ERR_RTIMEERRS	// no more Semas
#define	RTERR_NOMOREQUEUES			7 + ERR_RTIMEERRS	// no more Queues
#define	RTERR_SHUTDOWNTIMEOUT		8 + ERR_RTIMEERRS	// 
#define	RTERR_CHECKHOSTOSNOPCR		9 + ERR_RTIMEERRS	// 
#define	RTERR_CHECKHOSTOSNOIDT		10 + ERR_RTIMEERRS	// 
#define	RTERR_CHECKHOSTOSNOPHYSMEM	11 + ERR_RTIMEERRS	// 
#define	RTERR_CHECKHOSTOSMAPERR		12 + ERR_RTIMEERRS	// 
#define	RTERR_EXTIRQALREADYDEF		13 + ERR_RTIMEERRS	//
#define	RTERR_EXTIRQNOTDEF 			14 + ERR_RTIMEERRS	//
#define	RTERR_EXTIRQINSTALLFAILED	15 + ERR_RTIMEERRS	//
#define	RTERR_IRQLNOTLESSOREQUAL	16 + ERR_RTIMEERRS	//
#define	RTERR_SYSCLOCKFAILURE		17 + ERR_RTIMEERRS	//
#define	RTERR_X64RTIMENOTSUPPORTED	18 + ERR_RTIMEERRS
#define	RTERR_SYSCLOCKMISSING		19 + ERR_RTIMEERRS	// 
#define	RTERR_VMXENTERFAILS			20 + ERR_RTIMEERRS
#define RTERR_MPSTARTUPFAILED		21 + ERR_RTIMEERRS
#define RTERR_CPUSTARTUPFAILED		22 + ERR_RTIMEERRS
#define	RTERR_VMXNOTSUPPORTED		23 + ERR_RTIMEERRS	//
#define	RTERR_VMXDISABLED			24 + ERR_RTIMEERRS
#define	RTERR_VMXCONTROLSMISSING	25 + ERR_RTIMEERRS
#define	RTERR_VMXENABLEFAILS		26 + ERR_RTIMEERRS
#define RTERR_INVALIDCPUCOUNT		27 + ERR_RTIMEERRS	//	
#define RTERR_INVALIDCPUALLOC		28 + ERR_RTIMEERRS
#define	RTERR_LEGACYSTACKREQUIRED	29 + ERR_RTIMEERRS
#define RTERR_COREISOLATIONDENIED	30 + ERR_RTIMEERRS
#define RTERR_CORENOTISOLATED		31 + ERR_RTIMEERRS
#define RTERR_CORENOTSHARED			32 + ERR_RTIMEERRS
#define	RTERR_CQOSNOTAVAIL			33 + ERR_RTIMEERRS
#define RTERR_CQOSSTARTFAIL			34 + ERR_RTIMEERRS
#define RTERR_NOINTELCPU			35 + ERR_RTIMEERRS
#define RTERR_INCOMPATIBLESW		36 + ERR_RTIMEERRS
#define RTERR_NOINTHMEM				37 + ERR_RTIMEERRS
#define RTERR_NOAMDCPU				38 + ERR_RTIMEERRS
#define	RTERR_AMDVNOTSUPPORTED		39 + ERR_RTIMEERRS	//
#define	RTERR_AMDVDISABLED			40 + ERR_RTIMEERRS
#define	RTERR_AMDVFEATUREMISSING	41 + ERR_RTIMEERRS
#define	RTERR_AMDVENABLEFAILS		42 + ERR_RTIMEERRS
#define RTERR_SHAREDCOREDENIED		43 + ERR_RTIMEERRS
#define RTERR_HWID_DETECT			44 + ERR_RTIMEERRS
#define RTERR_PG_LOOKUP_FAILS			45 + ERR_RTIMEERRS

///////////////////////////////////////////////////////////////////////////////
// TRACE
#define	TRACEERR_REGISTRY				0 + ERR_TRACEERRS	// error eading registry data
#define	TRACEERR_MEMMAP				1 + ERR_TRACEERRS // error mapping physical->linear addr
#define	TRACEERR_NOTAVAIL				2 + ERR_TRACEERRS	// tracing is disabled or bad init

///////////////////////////////////////////////////////////////////////////////
// IO
#define	IOERR_INTERNAL							(0	+ ERR_IOERRS)	// internal error
#define	IOERR_BADCARDNO						(1	+ ERR_IOERRS)	// invalid card no
#define	IOERR_INVALIDCARDADDR				(2	+ ERR_IOERRS)	// invalid interface card addr
#define	IOERR_CDLLISTFULL						(3	+ ERR_IOERRS)	// no free lines in cdl-list
#define	IOERR_BADCDLPARAM						(4	+ ERR_IOERRS)	// invalid cdl parameters
#define	IOERR_OPENIOFAILED					(5	+ ERR_IOERRS)	// i/o-open failed
#define	IOERR_RESETIOFAILED					(6	+ ERR_IOERRS)	// i/o-reset failed
#define	IOERR_UNKNOWNDEVICE					(7	+ ERR_IOERRS)	// unknown device type
#define	IOERR_UNKNOWNDEVICEID				(8	+ ERR_IOERRS)	// unknown device id
#define	IOERR_UNKNOWNIMAGEID					(9	+ ERR_IOERRS)	// unknown image id
#define	IOERR_GETIOSTATE						(10 + ERR_IOERRS)	// 
#define	IOERR_BADIMAGEID						(11 + ERR_IOERRS)	// 
#define	IOERR_NOMORECLIENTSPACE				(12 + ERR_IOERRS)	// 
#define	IOERR_CLIENTINFONOTFOUND			(13 + ERR_IOERRS)	// 
#define	IOERR_CDLNOTINUSE						(14 + ERR_IOERRS)	// 
#define	IOERR_TIMEOUTWITHDEVICE				(15 + ERR_IOERRS)	//
#define	IOERR_C1220FUNC_1						(16 + ERR_IOERRS)	//	lwl reset
#define	IOERR_C1220FUNC_9						(17 + ERR_IOERRS)	//	software reset
#define	IOERR_C1220FUNC_C						(18 + ERR_IOERRS)	//	comm management reinitialize
#define	IOERR_C1220FUNC_10					(19 + ERR_IOERRS)	//	load cdl configuration
#define	IOERR_C1220FUNC_1_MAXSEND			(20 + ERR_IOERRS)	//	lwl reset: 
#define	IOERR_C1220FUNC_1_ADDRSET			(21 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK				(22 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK0			(23 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK1			(24 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK2			(25 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK3			(26 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK4			(27 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK5			(28 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK6			(29 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK7			(30 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK8			(31 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK9			(32 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK10			(33 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK11			(34 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK12			(35 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK13			(36 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK14			(37 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK15			(38 + ERR_IOERRS)	//	
#define	IOERR_C1220FUNC_1_BREAK16			(39 + ERR_IOERRS)	//	
#define	IOERR_SPC3DEVINITDP					(40 + ERR_IOERRS)	//	SPC3 Profibus Init failed
#define	IOERR_SPC3UPDATEOUTPUT				(41 + ERR_IOERRS)	//	SPC3 Profibus failed
#define	IOERR_CIF30READDIAG					(42 + ERR_IOERRS)
#define	IOERR_CIF30COMMNOTSTARTED			(43 + ERR_IOERRS)
#define	IOERR_CIF30SLAVEPARASIZE			(44 + ERR_IOERRS)
#define	IOERR_CIF30NOPARAS					(45 + ERR_IOERRS)
#define	IOERR_CIF30SLAVEERROR				(46 + ERR_IOERRS)	// DP-Slave meldet Fehler
#define	IOERR_CIF30WATCHDOGEXPIRED			(47 + ERR_IOERRS)
#define	IOERR_UNKNOWNDEVICECMD				(48 + ERR_IOERRS)	// unknown device type
#define	IOERR_CIF40MESSAGEHANDLING			(49 + ERR_IOERRS)
#define	IOERR_CIF40PARAERROR					(50 + ERR_IOERRS)
#define	IOERR_CIF40WATCHDOGEXPIRED			(51 + ERR_IOERRS)
#define	IOERR_CIF40FLAGERROR					(52 + ERR_IOERRS)
#define	IOERR_CIF40COMMNOTSTARTED			(53 + ERR_IOERRS)
#define	IOERR_CIF40READDIAG					(54 + ERR_IOERRS)
#define	IOERR_CIF40SLAVEERROR				(55 + ERR_IOERRS)
#define	IOERR_CIF40GLOBALERROR				(56 + ERR_IOERRS)
#define	IOERR_CIF40CONFIGLIST				(57 + ERR_IOERRS)
#define	IOERR_CP5412A2SLAVEPARASIZE		(58 + ERR_IOERRS) // Länge der Slave-Parameter aus Registry ist falsch
#define	IOERR_CP5412A2NOPARAS				(59 + ERR_IOERRS) // CP5412A2 soll initialisiert werden, ohne daß Busparameter und Slaveparameter übergeben wurden
#define	IOERR_CP5412A2SLAVEERROR			(60 + ERR_IOERRS)	// DP-Slave meldet Fehler
#define	IOERR_CP5412A2FATAL					(61 + ERR_IOERRS)	// Syntax bei Antwort von CP5412A2 stimmt nicht
#define	IOERR_CP5412A2MAILBOXUSED			(62 + ERR_IOERRS)	// Kommando-Mailbox von CP5412A2 ist gerade besetzt
#define	IOERR_BEGINCONFIGWHILETICKER		(63 + ERR_IOERRS)
#define	IOERR_UNEXPECTEDBOXCOUNT			(64 + ERR_IOERRS)
#define	IOERR_C1200CHECKADDR					(65 + ERR_IOERRS)
#define	IOERR_C1200INTENSITYTEST			(66 + ERR_IOERRS)
#define	IOERR_NOIMAGE							(67 + ERR_IOERRS)
#define	IOERR_INVALIDIMAGEOFFSSIZE			(68 + ERR_IOERRS)
#define	IOERR_FORCESCOUNTEXCEEDEDMAXIMUM	(69 + ERR_IOERRS)
#define	IOERR_SERCOSLIFECOUNTERERR			(70 + ERR_IOERRS)
#define	IOERR_C1220NOTFOUND					(71 + ERR_IOERRS)
#define	IOERR_AMSDEVICENOAMSINTF			(72 + ERR_IOERRS) // Box hat kein AMS-Interface 
#define	IOERR_AMSDEVICEAMSCMDIDNOTSUPP	(73 + ERR_IOERRS) // AMS-Kommando wird von Box nicht unterstützt
#define	IOERR_AMSDEVICEAMSSERVICERUNNING	(74 + ERR_IOERRS) // letztes AMS-Kommando ist von Box noch nicht vollständig bearbeitet
#define	IOERR_PLCINTERFACE_BUSY				(75 + ERR_IOERRS)	// letzter SPS-Interface-Request ist noch nicht vollständig bearbeitet
#define	IOERR_PLCINTERFACE_FAULT			(76 + ERR_IOERRS) // Box meldet Fehler bei SPS-Interface-Response
#define	IOERR_PLCINTERFACE_TIMEOUT			(77 + ERR_IOERRS) // Timeout beim Bearbeiten des SPS-Interfaces (Toggle-Bit kommt nicht)
#define	IOERR_PLCINTERFACE_RESETTIMEOUT	(78 + ERR_IOERRS) // Timeout beim Reset des SPS-Interfaces (Reset-Quittung kommt nicht)
#define	IOERR_PLCINTERFACE_NODATAEXCH		(79 + ERR_IOERRS) // Box befindet sich sich nicht im Datenaustausch (daher keine SPS-Interface-Bearbeitung möglich)
#define	IOERR_PLCINTERFACE_RESET			(80 + ERR_IOERRS) // SPS-Interface wird gerade zurückgesetzt
#define	IOERR_CP5412A2INVALIDADDR			(81 + ERR_IOERRS)
#define	IOERR_CP5412A2INVALIDPORT			(82 + ERR_IOERRS)
#define	IOERR_AMSDEVICEBADBOXNO				(83 + ERR_IOERRS) // Box-Nummer ist zu groß beim Erzeugen einer AMS-Box
#define	IOERR_AMSDEVICEBADTYPE				(84 + ERR_IOERRS) // falscher Typ beim Erzeugen einer AMS-Box
#define	IOERR_AMSDEVICEILLEGALADDRESS		(85 + ERR_IOERRS) // falsche Adresse des SPS- oder Diagnose-Interfaces beim Erzeugen einer AMS-Box
#define	IOERR_CP5412A2INVALIDBOX			(86 + ERR_IOERRS) // Box-Nummer ist zu groß bei verschiedenen AMS-Diensten
#define	IOERR_AMSDEVICEFIFOOVERFLOW		(87 + ERR_IOERRS) // es kann kein AMS-String mehr gespeichert werden
#define	IOERR_AMSDEVICEAMSSEQUENCEERROR	(88 + ERR_IOERRS) // Fehler bei Zusammenstückeln der AMS-Teilstrings zu einem AMS-String
#define	IOERR_CP5412A2DPV1SYNTAXERROR		(89 + ERR_IOERRS) // Fehler in DPV1-Syntax
#define	IOERR_CP5412A2DEVICENOTRUNNING	(90 + ERR_IOERRS) // AMS-Kommando kann erst nach StartIO bearbeitet werden
#define	IOERR_AMSDEVICENOTRUNNING			(91 + ERR_IOERRS) // AMS-Kommando kann erst nach StartIO bearbeitet werden
#define	IOERR_AMSDEVICEBOXNOTDEFINED		(92 + ERR_IOERRS) // AMS-Box wurde nicht definiert
#define	IOERR_CP5412A2BADSERVICEPARA		(93 + ERR_IOERRS) // falsche Dienstparameter bei AMS-Service
#define	IOERR_CP5412A2FIFOOVERFLOW			(94 + ERR_IOERRS) // es kann kein AMS-Kommando mehr gespeichert werden
#define	IOERR_COMPORTOPENFAILED	 			(95 + ERR_IOERRS)
#define	IOERR_CIF30BADMESSAGERESPONSE		(96 + ERR_IOERRS)
#define	IOERR_CIF30DELETEDATABASE			(97 + ERR_IOERRS)
#define	IOERR_CIF30STARTSEQFAILED			(98 + ERR_IOERRS)
#define	IOERR_CIF30DOWNLOADFAILED			(99 + ERR_IOERRS)
#define	IOERR_CIF30ENDSEQFAILED				(100 + ERR_IOERRS)
#define	IOERR_CIF30BUSLOADFAILED			(101 + ERR_IOERRS)
#define	IOERR_PLCINTERFACE_RESETREQ		(102 + ERR_IOERRS)
#define	IOERR_CP5412A2INVALIDCYCLETICKS	(103 + ERR_IOERRS)
#define	IOERR_CP5412A2DPBUSFAULT			(104 + ERR_IOERRS)
#define	IOERR_INVALIDTERMCONFIG				(105 + ERR_IOERRS)
#define	IOERR_SERCANSBREAK					(106 + ERR_IOERRS) // LWL ist unterbrochen
#define	IOERR_SERCANSPHASE0					(107 + ERR_IOERRS) // umschalten in Phase 0 hat nicht geklappt
#define	IOERR_SERCANSPHASE1					(108 + ERR_IOERRS) // umschalten in Phase 1 hat nicht geklappt
#define	IOERR_SERCANSPHASE2					(109 + ERR_IOERRS) // umschalten in Phase 2 hat nicht geklappt
#define	IOERR_SERCANSPHASE3					(110 + ERR_IOERRS) // umschalten in Phase 3 hat nicht geklappt
#define	IOERR_SERCANSPHASE4					(111 + ERR_IOERRS) // umschalten in Phase 4 hat nicht geklappt
#define	IOERR_SERCANSNCSERVICECHNFAILED	(112 + ERR_IOERRS) // 
#define	IOERR_RESOURCECONFICT				(113 + ERR_IOERRS) // 
#define	IOERR_C1220INITSTRINGCOMM			(114 + ERR_IOERRS) // 
#define	IOERR_C1220REGSTRINGSLAVE			(115 + ERR_IOERRS) // 
#define	IOERR_C1220STRREGFAULT				(116 + ERR_IOERRS) // Registerkommunikation über Stringkommunikation hat nicht geklappt
#define	IOERR_IOSTATEBUSY						(117 + ERR_IOERRS) // internal error
#define	IOERR_IBSSCITWATCHDOGEXPIRED		(118 + ERR_IOERRS)
#define	IOERR_IBSSCITSYNCMAILBOXERROR		(119 + ERR_IOERRS)
#define	IOERR_IBSSCITCONFIRMDIAGERROR		(120 + ERR_IOERRS)
#define	IOERR_IBSSCITCREATECFGERROR		(121 + ERR_IOERRS)
#define	IOERR_IBSSCITCOMPLETEREADCFGERROR	(122 + ERR_IOERRS)
#define	IOERR_IBSSCITSTARTDATATRANSFERERROR	(123 + ERR_IOERRS)
#define	IOERR_IBSSCITSETFAULTINDICATION	(124 + ERR_IOERRS)
#define	IOERR_IBSSCITSETDEVICESTATEINDICATION	(125 + ERR_IOERRS)
#define	IOERR_IBSSCITSETBUSERRORINDICATION	(126 + ERR_IOERRS)
#define	IOERR_IBSSCITSTOPDATATRANSFERERROR	(127 + ERR_IOERRS)
#define	IOERR_IBSSCITSETVALUEINDICATION		(128 + ERR_IOERRS)
#define	IOERR_IBSSCITINITIATEREQ				(129 + ERR_IOERRS) // 
#define	IOERR_IBSSCITACTIVATECFGERROR			(130 + ERR_IOERRS) // 
#define	IOERR_IBSSCITCOMPACTLOADPDRLERROR	(131 + ERR_IOERRS) // 
#define	IOERR_IBSSCITCONTROLPARAMERROR		(132 + ERR_IOERRS) // 
#define	IOERR_IBSSCITDEACTIVATECFGERROR		(133 + ERR_IOERRS) // 
#define	IOERR_IBSSCITINVALIDPORT				(134 + ERR_IOERRS) // 
#define	IOERR_C1220FUNC_7_ADDRESSTEST			(135 + ERR_IOERRS) // 
#define	IOERR_FCXXXXMAILBOXUSED					(136 + ERR_IOERRS) 
#define	IOERR_FCXXXXDPRAMTOOSMALL				(137 + ERR_IOERRS)
#define	IOERR_COMUPS_PORTINUSE   				(138 + ERR_IOERRS)
#define	IOERR_COMUPS_NOUPSORNOPOWER			(139 + ERR_IOERRS)
#define	IOERR_COMUPS_LOWBATTERY					(140 + ERR_IOERRS)
#define	IOERR_UPS_ALREADY_EXISTS				(141 + ERR_IOERRS)
#define	IOERR_FCXXXXSTARTUPFAILED				(142 + ERR_IOERRS)
#define	IOERR_C1220GETSTRINGCOMMTXSTATEFAILED	(143 + ERR_IOERRS)
#define	IOERR_C1220SENDSTRINGTOSLAVEFAILED	(144 + ERR_IOERRS)
#define	IOERR_CP5613FIRMWARELOADFAILED		(145 + ERR_IOERRS)
#define	IOERR_CP5613DPOPENFAILED				(146 + ERR_IOERRS)
#define	IOERR_CP5613FATALERROR					(147 + ERR_IOERRS)
#define	IOERR_CP5613DPUSEROPENFAILED			(148 + ERR_IOERRS)
#define	IOERR_CP5613DPSETMODESTOPFAILED		(149 + ERR_IOERRS)
#define	IOERR_CP5613DPSETMODECLEARFAILED		(150 + ERR_IOERRS)
#define	IOERR_CP5613DPSETMODEOPERATEFAILED	(151 + ERR_IOERRS)
#define	IOERR_CP5613NODATAAVAILABLE			(152 + ERR_IOERRS)
#define	IOERR_CP5613DPSERVICEFAILED			(153 + ERR_IOERRS)
#define	IOERR_CP5613DPSETMODEOFFLINEFAILED	(154 + ERR_IOERRS)
#define	IOERR_CP5613DPUSERCLOSEFAILED			(155 + ERR_IOERRS)
#define	IOERR_CP5613DPCLOSEFAILED				(156 + ERR_IOERRS)
#define	IOERR_CP5613OTHERSERVICERETURNED		(157 + ERR_IOERRS)
#define	IOERR_CP5613DPOKASYNC					(158 + ERR_IOERRS)	// Request activated, confirmation not available
#define	IOERR_CP5613DPERROREVENT				(159 + ERR_IOERRS)	// slave sends in a response telegram  DPC1 error values
#define	IOERR_CP5613DPERROREVENTNET			(160 + ERR_IOERRS)	// error at an underlaying driver
#define	IOERR_CP5613DPERRORREQPAR				(161 + ERR_IOERRS)	// wrong request parameter
#define	IOERR_CP5613DPERRORCI					(162 + ERR_IOERRS)	// error at accessing the CP
#define	IOERR_CP5613DPERRORRES					(163 + ERR_IOERRS)	// not enough ressources
#define	IOERR_CP5613DPERRORUSRABORT			(164 + ERR_IOERRS)	// user has finished DP-communication
#define	IOERR_PKWSYNTAXERROR						(165 + ERR_IOERRS)	// Syntax-Error at PKW
#define	IOERR_CP5412A2CDLCFGFAULT				(166 + ERR_IOERRS)	// too much different IoAccessDividers
#define	IOERR_IBSSCITINITLOADCFGERROR			(168 + ERR_IOERRS)
#define	IOERR_IBSSCITLOADCFGERROR				(169 + ERR_IOERRS)
#define	IOERR_IBSSCITTERMLOADCFGERROR			(170 + ERR_IOERRS)
#define	IOERR_IBSSCITINITLOADPDRLERROR		(171 + ERR_IOERRS)
#define	IOERR_IBSSCITLOADPDRLERROR				(172 + ERR_IOERRS)
#define	IOERR_IBSSCITTERMLOADPDRLERROR		(173 + ERR_IOERRS)
#define	IOERR_IBSSCITDELETEOBJECTERROR		(174 + ERR_IOERRS)
#define	IOERR_IBSSCITCONTROLACTIVECFGGERROR	(175 + ERR_IOERRS)
#define	IOERR_IBSSCITINITLOADPDDLERROR		(176 + ERR_IOERRS)
#define	IOERR_IBSSCITLOADPDDLERROR				(177 + ERR_IOERRS)
#define	IOERR_IBSSCITTERMLOADPDDLERROR		(178 + ERR_IOERRS)
#define	IOERR_NOMOREMAPSINIMAGE					(179 + ERR_IOERRS)
#define	IOERR_IBSSCITSETSLAVEINFOERROR		(180 + ERR_IOERRS)	// 
#define	IOERR_CIF40NOTREADY						(190 + ERR_IOERRS)
#define	IOERR_C1220SETAMSNETIDFAILED			(191 + ERR_IOERRS)
#define	IOERR_AMSDEVICEIORESETACTIVE			(192 + ERR_IOERRS)
#define	IOERR_C1220INITPROGRAMMABLECDL		(193 + ERR_IOERRS) // 
#define	IOERR_FCXXXXINVALIDBOXNODOWNLOADED	(194 + ERR_IOERRS)	// invalid fieldbus address downloaded


#define	IOERR_CP5412A2_RESET					(4		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_LOADBUSPARA			(5		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_LOADSLAVE			(6		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_LOADPRMDATA			(7		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_LOADCFGDATA			(8		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_LOADSLAVECDL		(9		+	ERR_CP5412A2)
#define	IOERR_CP5412A2_ACTIVATESLAVE		(10	+	ERR_CP5412A2)
#define	IOERR_CP5412A2_ADDSLAVE				(11	+	ERR_CP5412A2)
#define	IOERR_CP5412A2_DELETESLAVE			(12	+	ERR_CP5412A2)
#define	IOERR_CP5412A2_STARTDATAEXCH		(13	+	ERR_CP5412A2)
#define	IOERR_CP5412A2_STOPDATAEXCH		(14	+	ERR_CP5412A2)
#define	IOERR_CP5412A2_DEBUGDPM				(15	+	ERR_CP5412A2)

///////////////////////////////////////////////////////////////////////////////
// FC Box - stamndadisiert

#define	FCERR_FMNOERROR								0 
#define	FCERR_FMDEACTIVATED							1 
#define	FCERR_FMNOANSWER								2 
#define	FCERR_FMMASTERLOCK							3 
#define	FCERR_FMINVALIDRESPONSE						4 
#define	FCERR_FMPRMFAULT								5 
#define	FCERR_FMFEATURENOTSUPPORTED				6 
#define	FCERR_FMCFGFAULT								7 
#define	FCERR_FMSTATIONNOTREADY						8 
#define	FCERR_FMSTATDIAG								9 
#define	FCERR_FMDIAGOVERFLOW							10
#define	FCERR_FMPHYSICALFAULT						11
#define	FCERR_FMDATATRANSFERLEFT					12
#define	FCERR_FMSYNIFAULT								13
#define	FCERR_FMTELEGRAMFAULT						14
#define	FCERR_FMNORESSOURCES							15
#define	FCERR_FMSERVICENOTACTIVATED				16
#define	FCERR_FMUNEXPECTEDTELEGRAM					17
#define	FCERR_FMSTATIONREADY							18
#define	FCERR_FMADSSTARTUP							19
#define	FCERR_FMINVALIDINDICATION					20
#define	FCERR_FMSTATIONINFAULT						21
#define	FCERR_FMINDICATIONMISSED					22
#define	FCERR_FMWAITFORINDICATIONS					23

#define	FCERR_FMFBUSSPECIFIC_1 						40
#define	FCERR_FMFBUSSPECIFIC_2 						41
#define	FCERR_FMFBUSSPECIFIC_3 						42
#define	FCERR_FMFBUSSPECIFIC_4 						43
#define	FCERR_FMFBUSSPECIFIC_5 						44
#define	FCERR_FMFBUSSPECIFIC_6 						45
#define	FCERR_FMFBUSSPECIFIC_7 						46
#define	FCERR_FMFBUSSPECIFIC_8 						47
#define	FCERR_FMFBUSSPECIFIC_9 						48

///////////////////////////////////////////////////////////////////////////////
// FC520x

#define	FCERR_FMFC520XHEARTBEATFAULT       		40
#define	FCERR_FMFC520XSHUTDOWNRECEIVED     		41
#define	FCERR_FMFC520XEKEYERROR_VENDOR     		42
#define	FCERR_FMFC520XEKEYERROR_DEVTYPE    		43
#define	FCERR_FMFC520XEKEYERROR_PRODCODE   		44
#define	FCERR_FMFC520XEKEYERROR_REVISION   		45
#define	FCERR_FMFC520XSTARTUPATTR          		46
#define	FCERR_FMFC520XIOLENGTH_PROD        		47
#define	FCERR_FMFC520XIOLENGTH_CONS        		48

#define	FCERR_FMFC520XDEVICEOPERATE_RUN    		0
#define	FCERR_FMFC520XDEVICEOPERATE_IDLE   		1
#define	FCERR_FMFC520XDEVICEDUPMAC         		2
#define	FCERR_FMFC520XDEVICESELFTEST       		3
#define	FCERR_FMFC520XDEVICESTANDBY        		4
#define	FCERR_FMFC520XDEVICEMAJORFAULT     		5
#define	FCERR_FMFC520XDEVICEMINORFAULT     		6
#define	FCERR_FMFC520XDEVICEBUSSENSEFAIL			7

#define	FCERR_FMFC520XCANBUSON             		0x01
#define	FCERR_FMFC520XCANBUSOFF            		0x02
#define	FCERR_FMFC520XCANWARNINGLIMIT      		0x04
#define	FCERR_FMFC520XCANOVERRUN           		0x08

///////////////////////////////////////////////////////////////////////////////
// DP-Slave-Errors

#define	DPSLAVEERROR_NOERROR							(FCERR_FMNOERROR					+	ERR_DPSLAVE)
#define	DPSLAVEERROR_STATIONDEACTIVATED			(FCERR_FMDEACTIVATED				+	ERR_DPSLAVE)
#define	DPSLAVEERROR_STATIONNONEXISTENT			(FCERR_FMNOANSWER					+	ERR_DPSLAVE)
#define	DPSLAVEERROR_MASTERLOCK						(FCERR_FMMASTERLOCK				+	ERR_DPSLAVE)
#define	DPSLAVEERROR_INVALIDSLAVERESPONSE		(FCERR_FMINVALIDRESPONSE		+	ERR_DPSLAVE)
#define	DPSLAVEERROR_PRMFAULT						(FCERR_FMPRMFAULT					+	ERR_DPSLAVE)
#define	DPSLAVEERROR_NOTSUPPORTED					(FCERR_FMFEATURENOTSUPPORTED	+	ERR_DPSLAVE)
#define	DPSLAVEERROR_CFGFAULT						(FCERR_FMCFGFAULT					+	ERR_DPSLAVE)
#define	DPSLAVEERROR_STATIONNOTREADY				(FCERR_FMSTATIONNOTREADY		+	ERR_DPSLAVE)
#define	DPSLAVEERROR_STATDIAG						(FCERR_FMSTATDIAG					+	ERR_DPSLAVE)
#define	DPSLAVEERROR_DIAGOVERFLOW					(FCERR_FMDIAGOVERFLOW			+	ERR_DPSLAVE)
#define	DPSLAVEERROR_PHYSICALFAULT					(FCERR_FMPHYSICALFAULT			+	ERR_DPSLAVE)
#define	DPSLAVEERROR_TELEGRAMFAULT					(FCERR_FMTELEGRAMFAULT			+	ERR_DPSLAVE)
#define	DPSLAVEERROR_NORESSOURCES					(FCERR_FMNORESSOURCES			+	ERR_DPSLAVE)
#define	DPSLAVEERROR_SERVICENOTACTIVATED			(FCERR_FMSERVICENOTACTIVATED	+	ERR_DPSLAVE)
#define	DPSLAVEERROR_UNEXPECTEDTELEGRAM			(FCERR_FMUNEXPECTEDTELEGRAM	+	ERR_DPSLAVE)
#define	DPSLAVEERROR_STATIONREADY					(FCERR_FMSTATIONREADY			+	ERR_DPSLAVE)
#define	DPSLAVEERROR_ADSSTARTUP						(FCERR_FMADSSTARTUP				+	ERR_DPSLAVE)

///////////////////////////////////////////////////////////////////////////////
// CAN-Node-Errors

#define	CANNODEERROR_NOERROR							(0	+	ERR_CANSLAVE)
#define	CANNODEERROR_STATIONNONEXISTENT			(1	+	ERR_CANSLAVE)
#define	CANNODEERROR_PRMFAULT						(4	+	ERR_CANSLAVE)
#define	CANNODEERROR_CFGFAULT						(6	+	ERR_CANSLAVE)
#define	CANNODEERROR_DEACTIVATED					(8	+	ERR_CANSLAVE)
#define	CANNODEERROR_PREOPERATIONAL				(12+	ERR_CANSLAVE)
#define	CANNODEERROR_NOT_OPERATIONAL				(13+	ERR_CANSLAVE)

///////////////////////////////////////////////////////////////////////////////
// IBS-Device-Errors

#define	IBSDEVICEERROR_NOERROR						(0	+	ERR_IBSSLAVE)
#define	IBSDEVICEERROR_STATIONDEACTIVATED		(1	+	ERR_IBSSLAVE)
#define	IBSDEVICEERROR_STATIONNONEXISTENT		(2	+	ERR_IBSSLAVE)
#define	IBSDEVICEERROR_CFGFAULT						(6	+	ERR_IBSSLAVE)
#define	IBSDEVICEERROR_DIAGOVERFLOW				(10+	ERR_IBSSLAVE)
#define	IBSDEVICEERROR_PHYSICALFAULT				(11+	ERR_IBSSLAVE)

///////////////////////////////////////////////////////////////////////////////
// PLC 
#define	PLCWRN_LOADINGBOOTPRJ		((0	+ ERR_PLCERRS) | AMSERRCODEISWARNING)
#define	PLCWRN_LOADINGRETAINDATA	((1	+ ERR_PLCERRS) | AMSERRCODEISWARNING)

///////////////////////////////////////////////////////////////////////////////
// NC
#define	ERR_NCR0MANERRS				(ERR_NCERRS+0x0000)			// nc R0 manager error offset				=> 0x4000
#define	ERR_NCCHNERRS					(ERR_NCERRS+0x0100)			// nc channel error offset					=> 0x4100
// see also 'NcDefs.h'														// nc errors ...								=> 0x4x00
#define	ERR_NCKINERRS					(ERR_NCERRS+0x0C00)			// nc kinematic trafo error offset		=> 0x4C00
#define	ERR_NC3ERRS						(ERR_NCERRS+0x0D00)			// nc 3 error offset	=> 0x4D00
#define	ERR_NCEXTSGERRS				(ERR_NCERRS+0x0E00)			// nc setpoint ext sg error offset	=> 0x4E00

///////////////////////////////////////////////////////////////////////////////
// NC3 error (0x8000 .. 0x8FFF)
#define	ERR_NC3BODEPLOTERRS			(ERR_NCERRS2+0x0100)			// nc3 bodeplot error offset				=> 0x8100

///////////////////////////////////////////////////////////////////////////////
// NC: R0-Manager Error Codes 
#define	NCERR_INTERNAL					(0x0000 + ERR_NCR0MANERRS)	// internal error
#define	NCERR_NOMEMORY					(0x0001 + ERR_NCR0MANERRS)	// out of memory
#define	NCERR_INVALIDBOOTDATA		(0x0002 + ERR_NCR0MANERRS)	// invalid/inconsistent boot data
#define	NCERR_CHECKDRIVEOUTPUT		(0x0003 + ERR_NCR0MANERRS)	// invalid range for parameter 'check drive output' in SAF-Task
#define	NCERR_EXTERNAL					(0x0004 + ERR_NCR0MANERRS)	// external error (e.g. from third-party module)
//
#define	NCERR_UNKNOWNCHANNELID		(0x0010 + ERR_NCR0MANERRS)	// unknown channel number
#define	NCERR_UNKNOWNGROUPID			(0x0011 + ERR_NCR0MANERRS)	// unknown group number
#define	NCERR_UNKNOWNAXISID			(0x0012 + ERR_NCR0MANERRS)	// unknown axis number
#define	NCERR_UNKNOWNENCODERID		(0x0013 + ERR_NCR0MANERRS)	// unknown encoder number
#define	NCERR_UNKNOWNCONTROLLERID	(0x0014 + ERR_NCR0MANERRS)	// unknown controller number
#define	NCERR_UNKNOWNDRIVEID			(0x0015 + ERR_NCR0MANERRS)	// unknown drive number
#define	NCERR_UNKNOWNTABULARID		(0x0016 + ERR_NCR0MANERRS)	// unknown tabular number
//
#define	NCERR_UNKNOWNPLCTONCADDR	(0x0020 + ERR_NCR0MANERRS)	// unknown PlcToNc address
#define	NCERR_UNKNOWNNCTOPLCADDR	(0x0021 + ERR_NCR0MANERRS)	// unknown NcToPlc address
#define	NCERR_UNKNOWNENCINADDR		(0x0022 + ERR_NCR0MANERRS)	// unknown encoder input address
#define	NCERR_UNKNOWNENCOUTADDR		(0x0023 + ERR_NCR0MANERRS)	// unknown encoder output address
#define	NCERR_UNKNOWNDRIVEINADDR	(0x0024 + ERR_NCR0MANERRS)	// unknown drive input address
#define	NCERR_UNKNOWNDRIVEOUTADDR	(0x0025 + ERR_NCR0MANERRS)	// unknown drive output address
//
#define	NCERR_UNKNOWNDSLAVETYPE		(0x0030 + ERR_NCR0MANERRS)	// unknown slave type
#define	NCERR_UNKNOWNAXISTYPE		(0x0031 + ERR_NCR0MANERRS)	// unknown axis type
#define	NCERR_UNKNOWNCHNTYPE			(0x0032 + ERR_NCR0MANERRS)	// unknown axis type
//
#define	NCERR_AXISINCOMPATIBLE		(0x0040 + ERR_NCR0MANERRS)	// object not of apropriate type
//
#define	NCERR_CHANNELINCOMPLETE		(0x0050 + ERR_NCR0MANERRS)	// channel is not in a useable state
#define	NCERR_GROUPINCOMPLETE		(0x0051 + ERR_NCR0MANERRS)	// channel is not in a useable state
#define	NCERR_AXISINCOMPLETE			(0x0052 + ERR_NCR0MANERRS)	// channel is not in a useable state
//
#define	NCERR_CHANNELEXISTS			(0x0060 + ERR_NCR0MANERRS)	// channel already exists
#define	NCERR_GROUPEXISTS				(0x0061 + ERR_NCR0MANERRS)	// group already exists
#define	NCERR_AXISEXISTS				(0x0062 + ERR_NCR0MANERRS)	// axis already exists
#define	NCERR_TABULAREXISTS			(0x0063 + ERR_NCR0MANERRS)	// table already exists
//
#define	NCERR_WRONGCHANNELINDEX		(0x0070 + ERR_NCR0MANERRS)	// channel
#define	NCERR_WRONGGROUPINDEX		(0x0071 + ERR_NCR0MANERRS)	// group

///////////////////////////////////////////////////////////////////////////////
// Channel Error Codes
#define	NCCHNERR_GROUPINDEX			(0x0001 + ERR_NCCHNERRS)
#define	NCCHNERR_ADDR_GROUP			(0x0002 + ERR_NCCHNERRS)
#define	NCCHNERR_NO_PLCINTERFACE	(0x0003 + ERR_NCCHNERRS)
#define	NCCHNERR_ILLEGALMFUNCNR		(0x0004 + ERR_NCCHNERRS)
#define	NCCHNERR_NOMEMORY				(0x0005 + ERR_NCCHNERRS)
#define	NCCHNERR_ISBUSY				(0x0006 + ERR_NCCHNERRS)
#define	NCCHNERR_NOTSUPPORTED		(0x0007 + ERR_NCCHNERRS)
#define	NCCHNERR_ILLEGALSETTING		(0x0008 + ERR_NCCHNERRS)
#define	NCCHNERR_START_NOTREADY		(0x0009 + ERR_NCCHNERRS)
#define	NCCHNERR_GOAHEADNOTREADY	(0x000A + ERR_NCCHNERRS)
//
#define	NCCHNERR_NOFILE				(0x0010 + ERR_NCCHNERRS)
#define	NCCHNERR_ITPSYNTAXLT			(0x0011 + ERR_NCCHNERRS)
#define	NCCHNERR_ITPSYNTAXRT			(0x0012 + ERR_NCCHNERRS)
#define	NCCHNERR_SUBNOTFOUND			(0x0013 + ERR_NCCHNERRS)
#define	NCCHNERR_LOADBUFFERFULL		(0x0014 + ERR_NCCHNERRS)
#define	NCCHNERR_INVALIDIDENTIFIER	(0x0015 + ERR_NCCHNERRS)
#define	NCCHNERR_UNKNOWNIDENTIFIER	(0x0016 + ERR_NCCHNERRS)
#define	NCCHNERR_SUBINCOMPLETE		(0x0017 + ERR_NCCHNERRS)
#define	NCCHNERR_MAXNCFILES			(0x0018 + ERR_NCCHNERRS)
#define	NCCHNERR_MAXPATH				(0x0019 + ERR_NCCHNERRS)
//
#define	NCCHNERR_ZERODIVIDE			(0x0020 + ERR_NCCHNERRS)
#define	NCCHNERR_BADCIRCLE			(0x0021 + ERR_NCCHNERRS)
#define	NCCHNERR_INVALIDOPERATION	(0x0022 + ERR_NCCHNERRS)
//
#define	NCCHNERR_CALLSTACKOVR		(0x0030 + ERR_NCCHNERRS)
#define	NCCHNERR_CALLSTACKUDR		(0x0031 + ERR_NCCHNERRS)
#define	NCCHNERR_CALCSTACKOVR		(0x0032 + ERR_NCCHNERRS)
#define	NCCHNERR_CALCSTACKUDR		(0x0033 + ERR_NCCHNERRS)
//
#define	NCCHNERR_REGINDEX				(0x0040 + ERR_NCCHNERRS)
#define	NCCHNERR_GFUNCINDEX			(0x0041 + ERR_NCCHNERRS)
#define	NCCHNERR_MFUNCINDEX			(0x0042 + ERR_NCCHNERRS)
#define	NCCHNERR_EXTENDEDADDR		(0x0043 + ERR_NCCHNERRS)
#define	NCCHNERR_INTERNALINDEXH		(0x0044 + ERR_NCCHNERRS)
#define	NCCHNERR_MDBACCESSINDEX		(0x0045 + ERR_NCCHNERRS)
//
#define	NCTRAFOERR_CANNOTCHANGE		(0x0050 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CANNOTCORRECT	(0x0051 + ERR_NCCHNERRS)
#define	NCTRAFOERR_PLANE				(0x0052 + ERR_NCCHNERRS)
#define	NCTRAFOERR_DPARAMINVALID	(0x0053 + ERR_NCCHNERRS)
#define	NCTRAFOERR_TOOLRADIUSINV	(0x0054 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CHANGETOOLRAD	(0x0055 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDOVERFLOW		(0x0056 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDON				(0x0057 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDCHECK			(0x0058 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDUNEXPECTED		(0x0059 + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDNEGRADIUS		(0x005A + ERR_NCCHNERRS)
#define	NCTRAFOERR_CDOCCURED			(0x005B + ERR_NCCHNERRS)
#define	NCTRAFOERR_COOKEDTBLFULL	(0x005C + ERR_NCCHNERRS)
#define	NCTRAFOERR_TFTBLFULL			(0x005D + ERR_NCCHNERRS)
#define	NCTRAFOERR_EXECTFTBLFULL	(0x005E + ERR_NCCHNERRS)
#define	NCTRAFOERR_EXECTFT			(0x005F + ERR_NCCHNERRS)

#define	NCBACKUPERR_WRITEDATA		(0x0060 + ERR_NCCHNERRS)
#define	NCBACKUPERR_TARGETENTRY		(0x0061 + ERR_NCCHNERRS)
#define	NCIPOLRULES_REQUEST			(0x0062 + ERR_NCCHNERRS)

#define	NCCHNERR_INVALIDPARAMETER	(0x0070 + ERR_NCCHNERRS)
#define	NCCHNERR_BADCONTOUR			(0x0071 + ERR_NCCHNERRS)

#define	NCCHNERR_INVALIDENTRYID		(0x0072 + ERR_NCCHNERRS)

#define	NCCHNERR_DEFAULTGCODEERR	(0x0073 + ERR_NCCHNERRS)
#define	NCCHNERR_DEFGCODEINVALIDFILE (0x0074 + ERR_NCCHNERRS)

///////////////////////////////////////////////////////////////////////////////
// Error Strings

#ifndef	VXD
#ifdef	_ADSAMSDLL

static const ErrorStrings errStrings[] = {
	{ ERR_INTERNAL,					"GLOBAL: internal error" },					
	{ ERR_NORTIME,						"GLOBAL: no real time" },
	{ ERR_ALLOCLOCKEDMEM,			"GLOBAL: error allocating locked memory" },
	{ ERR_INSERTMAILBOX,				"GLOBAL: mailbox full" },
	{ ERR_WRONGRECEIVEHMSG,			"GLOBAL: wrong receive handle" },
	{ ERR_TARGETPORTNOTFOUND,		"GLOBAL: target port not found" },
	{ ERR_TARGETMACHINENOTFOUND,	"GLOBAL: target machine not found" },
	{ ERR_UNKNOWNCMDID,				"GLOBAL: unknown command id" },
	{ ERR_BADTASKID,					"GLOBAL: bad task id" },
	{ ERR_LOWINSTLEVEL,				"GLOBAL: installation level conflict" },
	{ ERR_NODEBUGINTAVAILABLE,		"GLOBAL: no debug interrupt available" },
	{ ERR_AMSSYNC_W32ERROR,			"GLOBAL: AmsSync Win32 Error"},
	{ ERR_AMSSYNC_TIMEOUT,			"GLOBAL: AmsSync Timeout"},
	{ ERR_AMSSYNC_AMSERROR,			"GLOBAL: AmsSync internal Ams Error"},
	{ ERR_AMSSYNC_NOINDEXINMAP,	"GLOBAL: AmsSync map full"},

	{ ROUTERERR_NOLOCKEDMEMORY,	"ROUTER: no locked memory" },
	{ ROUTERERR_RESIZEMEMORY,		"ROUTER: error resizing locked memory" },
	{ ROUTERERR_MAILBOXFULL,		"ROUTER: mailbox full" },
	{ ROUTERERR_DEBUGBOXFULL,		"ROUTER: debug mailbox full" },
	{ ROUTERERR_UNKNOWNPORTTYPE,	"ROUTER: unknown port type" },
	{ ROUTERERR_NOTINITIALIZED,	"ROUTER: not initialized" },

	{ RTERR_INTERNAL,					"RTIME: internal error" },
	{ RTERR_BADTIMERPERIODS,		"RTIME: bad timer periods" },
	{ RTERR_INVALIDTASKPTR,			"RTIME: invalid task ptr" },
	{ RTERR_INVALIDSTACKPTR,		"RTIME: invalid stack ptr" },
	{ RTERR_PRIOEXISTS,				"RTIME: priority exists" },
	{ RTERR_NOMORETCB,				"RTIME: no more task control blocks" },
	{ RTERR_NOMORESEMAS,				"RTIME: no more sema control blocks" },
	{ RTERR_NOMOREQUEUES,			"RTIME: no more queue control blocks" },
	{ RTERR_SHUTDOWNTIMEOUT,		"RTIME: internal error (SHUTDOWNTIMEOUT)" },
	{ RTERR_CHECKHOSTOSNOPCR,		"RTIME: internal error (CHECKHOSTOSNOPCR)" }, 
	{ RTERR_CHECKHOSTOSNOIDT,		"RTIME: internal error (CHECKHOSTOSNOIDT)" },
	{ RTERR_CHECKHOSTOSNOPHYSMEM,	"RTIME: internal error (CHECKHOSTOSNOPHYSMEM)" }, 
	{ RTERR_CHECKHOSTOSMAPERR,		"RTIME: internal error (CHECKHOSTOSMAPERR)" }, 
	{ RTERR_EXTIRQALREADYDEF,		"RTIME: internal error (EXTIRQALREADYDEF)" },
	{ RTERR_EXTIRQNOTDEF, 			"RTIME: internal error (EXTIRQNOTDEF)" },
	{ RTERR_EXTIRQINSTALLFAILED,	"RTIME: internal error (EXTIRQINSTALLFAILED)" },
	{ RTERR_IRQLNOTLESSOREQUAL,	"RTIME: internal error (IRQLNOTLESSOREQUAL)" },
	{ RTERR_SYSCLOCKFAILURE,		"RTIME: timeout waiting for system clock interrupt!" },
	{ RTERR_X64RTIMENOTSUPPORTED,	"RTIME: real-time mode not supported on 64 bit systems!" },
	{ RTERR_SYSCLOCKMISSING,      "RTIME: system clock setup fails. \r\nHint: On Windows8 system and above execute win8settick.bat in TwinCAT\\3.1\\System as administrator and reboot." },
	{ RTERR_VMXENTERFAILS,			"RTIME: enter real-time mode fails!" },
	{ RTERR_CPUSTARTUPFAILED,     "RTIME: startup of isolated CPU fails!" },
	{ RTERR_VMXNOTSUPPORTED,		"RTIME: enter real-time mode fails: Intel VT-x extension not supported!" },
	{ RTERR_VMXDISABLED,				"RTIME: enter real-time mode fails: Intel VT-x extension not enabled (in Bios)!" },
	{ RTERR_VMXCONTROLSMISSING,	"RTIME: enter real-time mode fails: missing feature in Intel VT-x extension!" },
	{ RTERR_VMXENABLEFAILS,			"RTIME: enter real-time mode fails: enabling Intel VT-x fails!" },
	{ RTERR_INVALIDCPUCOUNT,		"RTIME: number of CPUs not supported on target" },
	{ RTERR_INVALIDCPUALLOC,		"RTIME: activated CPU(s) not present on target" },
	{ RTERR_LEGACYSTACKREQUIRED,  "RTIME: at least one driver requires legacy stack size" },
	{ RTERR_COREISOLATIONDENIED,  "RTIME: at least one driver denies usage of isolated cores" },
	{ RTERR_CORENOTISOLATED,		"RTIME: at least one windows core is activated as an isolated core" },
	{ RTERR_CORENOTSHARED,			"RTIME: at least one isolated core is expected to be a windows core" },
	{ RTERR_NOINTELCPU,				"RTIME: Intel CPU required" },
	{ RTERR_INCOMPATIBLESW,			"RTIME: incompatible software detected" },
	{ RTERR_NOAMDCPU,				"RTIME: AMD CPU required" },
	{ RTERR_AMDVNOTSUPPORTED,		"RTIME: enter real-time mode fails: AMD-V extension not supported!" },
	{ RTERR_AMDVDISABLED,			"RTIME: enter real-time mode fails: AMD-V extension not enabled (in Bios)!" },
	{ RTERR_AMDVFEATUREMISSING,		"RTIME: enter real-time mode fails: missing feature in AMD-V  extension!" },
	{ RTERR_AMDVENABLEFAILS,		"RTIME: enter real-time mode fails: enabling AMD-V fails!" },
	{ RTERR_SHAREDCOREDENIED,		"RTIME: start of shared core is denied!" },

#ifndef	WIN32_RUNTIME
	{ TRACEERR_REGISTRY,				"TRACE: error in registry data"	},
	{ TRACEERR_MEMMAP,				"TRACE: error mapping physical->linear addr" },
	{ TRACEERR_NOTAVAIL,				"TRACE: tracing is disabled or bad init" },

	{ IOERR_INTERNAL,					"IO: internal error" },
	{ IOERR_BADCARDNO,				"IO: bad card number" },
	{ IOERR_INVALIDCARDADDR,		"IO: invalid card address" },
	{ IOERR_CDLLISTFULL,				"IO: CDL list full" },
	{ IOERR_BADCDLPARAM,				"IO: bad CDL param" },
	{ IOERR_OPENIOFAILED,			"IO: open IO failed" },
	{ IOERR_RESETIOFAILED,			"IO: reset IO failed" },
	{ IOERR_UNKNOWNDEVICE,			"IO: unknown device type" },
	{ IOERR_UNKNOWNDEVICEID,		"IO: unknown device id" },
	{ IOERR_UNKNOWNIMAGEID,			"IO: unknown image id" },
	{ IOERR_GETIOSTATE,				"IO: error getting io-state" },
	{ IOERR_BADIMAGEID,				"IO: bad image id" },
	{ IOERR_NOMORECLIENTSPACE,		"IO: no more notification space available" },
	{ IOERR_CLIENTINFONOTFOUND,	"IO: stopping notification failed" },
	{ IOERR_CDLNOTINUSE,				"IO: CDL list not in use" },
	{ IOERR_TIMEOUTWITHDEVICE,		"IO: timeout while communicate with device" },
	{ IOERR_C1220FUNC_1,				"IO: C1220/FC200x lwl reset failed" },
	{ IOERR_C1220FUNC_9,				"IO: C1220/FC200x software reset failed" },
	{ IOERR_C1220FUNC_C,				"IO: C1220/FC200x comm management reinitialization failed" },
	{ IOERR_C1220FUNC_10,			"IO: C1220/FC200x load cdl configuration failed" },
	{ IOERR_C1220FUNC_1_MAXSEND,	"IO: C1220/FC200x lwl reset: max sends exceeded" },
	{ IOERR_C1220FUNC_1_ADDRSET,	"IO: C1220/FC200x lwl reset: address set" },
	{ IOERR_C1220FUNC_1_BREAK,		"IO: C1220/FC200x lwl reset: unknown break location" },
	{ IOERR_C1220FUNC_1_BREAK0,	"IO: C1220/FC200x lwl reset: break direct before receiver" },
	{ IOERR_C1220FUNC_1_BREAK1,	"IO: C1220/FC200x lwl reset: break between 1. and 2. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK2,	"IO: C1220/FC200x lwl reset: break between 2. and 3. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK3,	"IO: C1220/FC200x lwl reset: break between 3. and 4. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK4,	"IO: C1220/FC200x lwl reset: break between 4. and 5. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK5,	"IO: C1220/FC200x lwl reset: break between 5. and 6. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK6,	"IO: C1220/FC200x lwl reset: break between 6. and 7. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK7,	"IO: C1220/FC200x lwl reset: break between 7. and 8. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK8,	"IO: C1220/FC200x lwl reset: break between 8. and 9. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK9,	"IO: C1220/FC200x lwl reset: break between 9. and 10. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK10,	"IO: C1220/FC200x lwl reset: break between 10. and 11. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK11,	"IO: C1220/FC200x lwl reset: break between 11. and 12. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK12,	"IO: C1220/FC200x lwl reset: break between 12. and 13. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK13,	"IO: C1220/FC200x lwl reset: break between 13. and 14. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK14,	"IO: C1220/FC200x lwl reset: break between 14. and 15. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK15,	"IO: C1220/FC200x lwl reset: break between 15. and 16. box before receiver" },
	{ IOERR_C1220FUNC_1_BREAK16,	"IO: C1220/FC200x lwl reset: break between 16. and 17. box before receiver" },
	{ IOERR_SPC3DEVINITDP,			"IO: SPC3 Initialization of DP-Slave failed" },
	{ IOERR_SPC3UPDATEOUTPUT,		"IO: SPC3 UpdateOutputBuffer failed" },
	{ IOERR_CIF30READDIAG,			"IO: CIFx0 reading diagnosis" },
	{ IOERR_CIF30COMMNOTSTARTED,	"IO: CIFx0 communication not started" },
	{ IOERR_CIF30SLAVEPARASIZE,	"IO: CIFx0 invalid slave para size" },
	{ IOERR_CIF30NOPARAS,			"IO: CIFx0 no parameters" },
	{ IOERR_CIF30SLAVEERROR,		"IO: CIFx0 slave error" },
	{ IOERR_CIF30WATCHDOGEXPIRED,	"IO: CIFx0 watchdog expiered" },
	{ IOERR_UNKNOWNDEVICECMD,		"IO: unknown device specific cmd" },
	{ IOERR_CIF40MESSAGEHANDLING,	"IO: CIF40 message handling" },
	{ IOERR_CIF40PARAERROR,			"IO: CIF40 parameter error" },
	{ IOERR_CIF40WATCHDOGEXPIRED,	"IO: CIF40 watchdog expiered" },
	{ IOERR_CIF40FLAGERROR,			"IO: CIF40 flag error" },
	{ IOERR_CIF40COMMNOTSTARTED,	"IO: CIF40 communication not started" },
	{ IOERR_CIF40READDIAG,			"IO: CIF40 reading diagnosis" },
	{ IOERR_CIF40SLAVEERROR,		"IO: CIF40 slave error" },
	{ IOERR_CIF40GLOBALERROR,		"IO: CIF40 global error" },
	{ IOERR_CIF40CONFIGLIST,		"IO: CIF40 config list" },
	{ IOERR_BEGINCONFIGWHILETICKER,"IO: BeginConfiguration while ticker is running" },
	{ IOERR_UNEXPECTEDBOXCOUNT,	"IO: number of expected boxes differs from found boxes" },
	{ IOERR_NOIMAGE,					"IO: no image exists" },
	{ IOERR_INVALIDIMAGEOFFSSIZE,	"IO: invalid offset or size of image" },
	{ IOERR_FORCESCOUNTEXCEEDEDMAXIMUM, "IO: maximum of force infos exceeded" },
	{ IOERR_C1220NOTFOUND,			"IO: C1220/FC200x not found" },
	{ IOERR_CP5412A2INVALIDADDR,	"IO: CP5412A2 possible invalid DPRAM address" },
	{ IOERR_CP5412A2INVALIDPORT,	"IO: CP5412A2 possible invalid port address" },
	{ IOERR_COMPORTOPENFAILED,		"IO: ComPort Device failed to open COM interface" },
	{ IOERR_CP5412A2SLAVEPARASIZE,	"IO: CP5412A2 Länge der Slave-Parameter aus Registry ist falsch" },
	{ IOERR_CP5412A2NOPARAS,			"IO: CP5412A2 soll initialisiert werden, ohne daß Busparameter und Slaveparameter übergeben wurden" },
	{ IOERR_CP5412A2SLAVEERROR,		"IO: CP5412A2 DP-Slave meldet Fehler" },
	{ IOERR_CP5412A2FATAL,				"IO: CP5412A2 Syntax bei Antwort von CP5412A2 stimmt nicht" },
	{ IOERR_CP5412A2MAILBOXUSED,		"IO: CP5412A2 Kommando-Mailbox von CP5412A2 ist gerade besetzt" },
	{ IOERR_AMSDEVICENOAMSINTF,		"IO: AmsDevice Box hat kein AMS-Interface " },
	{ IOERR_AMSDEVICEAMSCMDIDNOTSUPP,	"IO: AmsDevice AMS-Kommando wird von Box nicht unterstützt" },
	{ IOERR_AMSDEVICEAMSSERVICERUNNING,	"IO: AmsDevice letztes AMS-Kommando ist von Box noch nicht vollständig bearbeitet" },
	{ IOERR_PLCINTERFACE_BUSY,			"IO: PlcInterface letzter SPS-Interface-Request ist noch nicht vollständig bearbeitet" },
	{ IOERR_PLCINTERFACE_FAULT,		"IO: PlcInterface Box meldet Fehler bei SPS-Interface-Response" },
	{ IOERR_PLCINTERFACE_TIMEOUT,		"IO: PlcInterface Timeout beim Bearbeiten des SPS-Interfaces (Toggle-Bit kommt nicht)" },
	{ IOERR_PLCINTERFACE_RESETTIMEOUT,	"IO: PlcInterface Timeout beim Reset des SPS-Interfaces (Reset-Quittung kommt nicht)" },
	{ IOERR_PLCINTERFACE_NODATAEXCH,	"IO: PlcInterface Box befindet sich sich nicht im Datenaustausch (daher keine SPS-Interface-Bearbeitung möglich)" },
	{ IOERR_PLCINTERFACE_RESET,		"IO: PlcInterface SPS-Interface wird gerade zurückgesetzt" },
	{ IOERR_AMSDEVICEBADBOXNO,			"IO: AmsDevice Box-Nummer ist zu groß beim Erzeugen einer AMS-Box" },
	{ IOERR_AMSDEVICEBADTYPE,			"IO: AmsDevice falscher Typ beim Erzeugen einer AMS-Box" },
	{ IOERR_AMSDEVICEILLEGALADDRESS,	"IO: AmsDevice falsche Adresse des SPS- oder Diagnose-Interfaces beim Erzeugen einer AMS-Box" },
	{ IOERR_CP5412A2INVALIDBOX,		"IO: CP5412A2 Box-Nummer ist zu groß bei verschiedenen AMS-Diensten" },
	{ IOERR_AMSDEVICEFIFOOVERFLOW,	"IO: AmsDevice es kann kein AMS-String mehr gespeichert werden" },
	{ IOERR_AMSDEVICEAMSSEQUENCEERROR,	"IO: AmsDevice Fehler bei Zusammenstückeln der AMS-Teilstrings zu einem AMS-String" },
	{ IOERR_CP5412A2DPV1SYNTAXERROR,	"IO: CP5412A2 Fehler in DPV1-Syntax" },
	{ IOERR_CP5412A2DEVICENOTRUNNING,	"IO: CP5412A2 AMS-Kommando kann erst nach StartIO bearbeitet werden" },
	{ IOERR_AMSDEVICENOTRUNNING,		"IO: AmsDevice AMS-Kommando kann erst nach StartIO bearbeitet werden" },
	{ IOERR_AMSDEVICEBOXNOTDEFINED,	"IO: AmsDevice AMS-Box wurde nicht definiert" },
	{ IOERR_CP5412A2BADSERVICEPARA,	"IO: CP5412A2 falsche Dienstparameter bei AMS-Service" },
	{ IOERR_CP5412A2FIFOOVERFLOW,		"IO: CP5412A2 es kann kein AMS-Kommando mehr gespeichert werden" },
	{ IOERR_CP5412A2INVALIDCYCLETICKS,	"IO: CP5412A2 Cycle-Ticks wurden falsch berechnet" },
	{ IOERR_CP5412A2DPBUSFAULT,		"IO: CP5412A2 der Scheduler hat einen Busfehler festgestellt" },
	{ IOERR_INVALIDTERMCONFIG,			"IO: Falsche Klemmenkonfiguration eines Buskopplers" },
	{ IOERR_SERCANSBREAK,				"IO: SERCANS Sercos-LWL ist unterbrochen" },
	{ IOERR_SERCANSPHASE0,				"IO: SERCANS umschalten in Phase 0 hat nicht geklappt" },
	{ IOERR_SERCANSPHASE1,				"IO: SERCANS umschalten in Phase 1 hat nicht geklappt" },
	{ IOERR_SERCANSPHASE2,				"IO: SERCANS umschalten in Phase 2 hat nicht geklappt" },
	{ IOERR_SERCANSPHASE3,				"IO: SERCANS umschalten in Phase 3 hat nicht geklappt" },
	{ IOERR_SERCANSPHASE4,				"IO: SERCANS umschalten in Phase 4 hat nicht geklappt" },
	{ IOERR_SERCANSNCSERVICECHNFAILED,	"IO: SERCANS NC-Service Kanal Fehler" },
	{ IOERR_RESOURCECONFICT,			"IO: Resource confict detected (Memory, Ports or IRQs)" },
	{ IOERR_C1220INITSTRINGCOMM,		"IO: Fehler beim Initialisieren der Stringkommunikation" },
	{ IOERR_C1220REGSTRINGSLAVE,		"IO: Fehler beim Eintragen eines Stringslaves" },
	{ IOERR_C1220STRREGFAULT,			"IO: Registerkommunikation über Stringkommunikation hat nicht geklappt"},
	{ IOERR_IBSSCITWATCHDOGEXPIRED,	"IO: IBS SC watchdog expiered" },
	{ IOERR_IBSSCITSYNCMAILBOXERROR,	"IO: IBS SC Fehler bei Dienst.con über Sync-Mailbox" },
	{ IOERR_IBSSCITCONFIRMDIAGERROR,	"IO: IBS SC Fehler bei Confirm_Diagnosis.con" },
	{ IOERR_IBSSCITCREATECFGERROR,	"IO: IBS SC Fehler bei Create_Cfg.con" },
	{ IOERR_IBSSCITCOMPLETEREADCFGERROR,	"IO: IBS SC Fehler bei Complete_Read_Cfg.con"},
	{ IOERR_IBSSCITSTARTDATATRANSFERERROR,	"IO: IBS SC Fehler bei Start_Data_Transfer.con"},
	{ IOERR_IBSSCITSETFAULTINDICATION,	"IO: IBS SC Fehler bei Set_Indication(Fault).con"},
	{ IOERR_IBSSCITSETDEVICESTATEINDICATION,	"IO: IBS SC Fehler bei Set_Indication(Device_State).con"},
	{ IOERR_IBSSCITSETBUSERRORINDICATION,	"IO: IBS SC Fehler bei Set_Indication(Bus_Error).con"},
	{ IOERR_IBSSCITSTOPDATATRANSFERERROR,	"IO: IBS SC Fehler bei Stop_Data_Transfer.con"},
	{ IOERR_IBSSCITINVALIDPORT,			"IO: IBS SC possible invalid port address" },
	{ IOERR_C1220FUNC_7_ADDRESSTEST,		"IO: C1220/FC200x address check failed" },
	{ IOERR_FCXXXXMAILBOXUSED,			"IO: FCxxxx Sendbox sollte leer sein" },
	{ IOERR_FCXXXXDPRAMTOOSMALL,		"IO: FCxxxx Dual-Port-RAM ist zu klein" },
	{ IOERR_COMUPS_PORTINUSE,			"IO: COM UPS Error, Port already in use" },
	{ IOERR_COMUPS_NOUPSORNOPOWER,	"IO: COM UPS Error, no UPS found or UPS has no power" },
	{ IOERR_COMUPS_LOWBATTERY,			"IO: COM UPS Warning, UPS signals low power state" },	
	{ IOERR_UPS_ALREADY_EXISTS,		"IO: UPS Error, only one ups possible" },
	{ IOERR_FCXXXXSTARTUPFAILED,		"IO: FCxxxx Start-Up failed" },
	{ IOERR_C1220GETSTRINGCOMMTXSTATEFAILED,	"IO: C1220/FC200x GetStringCommTxState failed" },
	{ IOERR_C1220SENDSTRINGTOSLAVEFAILED,	"IO: C1220/FC200x SendStringToSlave failed" },
	{ IOERR_CP5613FIRMWARELOADFAILED,		"IO: CP5613 firmware load failed" },
	{ IOERR_CP5613DPOPENFAILED,		"IO: CP5613 DP_Open failed" },
	{ IOERR_CP5613FATALERROR,			"IO: CP5613 fatal error" },
	{ IOERR_CP5613DPUSEROPENFAILED,	"IO: CP5613 DP_UserOpen failed" },
	{ IOERR_CP5613DPSETMODESTOPFAILED,	"IO: CP5613 DP_SetMode(STOP) failed" },
	{ IOERR_CP5613DPSETMODECLEARFAILED,	"IO: CP5613 DP_SetMode(CLEAR) failed" },
	{ IOERR_CP5613DPSETMODEOPERATEFAILED,	"IO: CP5613 DP_SetMode(OPERATE) failed" },
	{ IOERR_CP5613NODATAAVAILABLE,	"IO: CP5613 no data available" },
	{ IOERR_CP5613DPSERVICEFAILED,	"IO: CP5613 DP-service failed" },
	{ IOERR_CP5613DPSETMODEOFFLINEFAILED,	"IO: CP5613 DP_setMode(OFFLINE) failed" },
	{ IOERR_CP5613DPUSERCLOSEFAILED,	"IO: CP5613 DP_UserClose failed" },
	{ IOERR_CP5613DPCLOSEFAILED,		"IO: CP5613 DP_Close failed" },
	{ IOERR_CP5613OTHERSERVICERETURNED,	"IO: CP5613 other service was returned" },
	{ IOERR_CP5613DPOKASYNC,			"IO: CP5613 Request activated, confirmation not available" },
	{ IOERR_CP5613DPERROREVENT,		"IO: CP5613 slave sends in a response telegram  DPC1 error values" },
	{ IOERR_CP5613DPERROREVENTNET,	"IO: CP5613 error at an underlaying driver" },
	{ IOERR_CP5613DPERRORREQPAR,		"IO: CP5613 wrong request parameter" },
	{ IOERR_CP5613DPERRORCI,			"IO: CP5613 error at accessing the CP" },
	{ IOERR_CP5613DPERRORRES,			"IO: CP5613 not enough ressources" },
	{ IOERR_CP5613DPERRORUSRABORT,	"IO: CP5613 user has finished DP-communication" },
	{ IOERR_PKWSYNTAXERROR,				"IO: AmsDevice Syntax-Error at PKW" },
	{ IOERR_CP5412A2CDLCFGFAULT,		"IO: CP5412A2 too much different IoAccessDividers" },
	{ IOERR_IBSSCITCONTROLPARAMERROR,	"IO: IBS SC control param failed" },
	{ IOERR_IBSSCITINITLOADCFGERROR,	"IO: IBS SC initiate load config failed" },
	{ IOERR_IBSSCITLOADCFGERROR,		"IO: IBS SC load config failed" },
	{ IOERR_IBSSCITTERMLOADCFGERROR,	"IO: IBS SC terminate load config failed" },
	{ IOERR_IBSSCITINITLOADPDRLERROR,	"IO: IBS SC initiate load PDRL failed" },
	{ IOERR_IBSSCITLOADPDRLERROR,		"IO: IBS SC load PDRL failed" },
	{ IOERR_IBSSCITTERMLOADPDRLERROR,	"IO: IBS SC terminate load PDRL failed" },
	{ IOERR_IBSSCITDELETEOBJECTERROR,	"IO: IBS SC delete action object failed" },
	{ IOERR_IBSSCITACTIVATECFGERROR,	"IO: IBS SC activate config failed" },
	{ IOERR_IBSSCITCONTROLACTIVECFGGERROR,	"IO: IBS SC control active config failed" },
	{ IOERR_IBSSCITSETSLAVEINFOERROR,	"IO: IBS SC set of slave ident code and length code failed" },
	{ IOERR_NOMOREMAPSINIMAGE,			"IO: maximum of mapping in an image reached" },
	{ IOERR_CIF40NOTREADY,				"IO: READY-Bit of CIF40 is not set before Warm-Start" },
	{ IOERR_C1220SETAMSNETIDFAILED,	"IO: C1220: Setting of the AMS-Net-ID of a Box during IO-Reset failed" },
	{ IOERR_AMSDEVICEIORESETACTIVE,	"IO: Sending of AMS-Cmd not possible during IO-Reset" },
	{ IOERR_C1220INITPROGRAMMABLECDL,"IO: C1220: Register programable CDL failed" },
	{ IOERR_FCXXXXINVALIDBOXNODOWNLOADED,	"IO: FCxxxx: invalid fieldbus address downloaded" },


	{ IOERR_CP5412A2_RESET,			"IO: CP5412A2 reset failed" },
	{ IOERR_CP5412A2_LOADBUSPARA,	"IO: CP5412A2 load bus parameter failed" },
	{ IOERR_CP5412A2_LOADSLAVE,	"IO: CP5412A2 load slave failed" },
	{ IOERR_CP5412A2_LOADPRMDATA,	"IO: CP5412A2 load prm data failed" },
	{ IOERR_CP5412A2_LOADCFGDATA,	"IO: CP5412A2 load cfg data failed" },
	{ IOERR_CP5412A2_LOADSLAVECDL,"IO: CP5412A2 load slave cdl failed" },
	{ IOERR_CP5412A2_ACTIVATESLAVE,"IO: CP5412A2 activate slave failed" },
	{ IOERR_CP5412A2_ADDSLAVE,		"IO: CP5412A2 add slave failed" },
	{ IOERR_CP5412A2_DELETESLAVE,	"IO: CP5412A2 delete slave failed" },
	{ IOERR_CP5412A2_STARTDATAEXCH,	"IO: CP5412A2 start data exchange failed" },
	{ IOERR_CP5412A2_STOPDATAEXCH,"IO: CP5412A2 stop data exchange failed" },
	{ IOERR_CP5412A2_DEBUGDPM,		"IO: CP5412A2 debug dpram failed" },


	{ PLCWRN_LOADINGBOOTPRJ,		"PLC: error loading boot project" },
	{ PLCWRN_LOADINGRETAINDATA,	"PLC: error loading retain data" },

	{ NCERR_INTERNAL,					"NC: internal error" },
	{ NCERR_NOMEMORY,					"NC: out of memory" },
	//
	{ NCERR_UNKNOWNCHANNELID,		"NC: unknown channel id" },
	{ NCERR_UNKNOWNGROUPID,			"NC: unknown group id" },
	{ NCERR_UNKNOWNAXISID,			"NC: unknown axis id" },
	{ NCERR_UNKNOWNENCODERID,		"NC: unknown encoder id" },
	{ NCERR_UNKNOWNCONTROLLERID,	"NC: unknown controller id" },
	{ NCERR_UNKNOWNDRIVEID,			"NC: unknown drive id" },
	{ NCERR_UNKNOWNTABULARID,		"NC: unknown tabular id" },
	//
	{ NCERR_AXISINCOMPATIBLE,		"NC: axis is incompatible" },
	{ NCERR_AXISINCOMPLETE,			"NC: incomplete axis" },
	//
	{ NCERR_CHANNELEXISTS,			"NC: channel already exists" },
	{ NCERR_GROUPEXISTS,				"NC: group already exists" },
	{ NCERR_AXISEXISTS,				"NC: axis already exists" },
	{ NCERR_TABULAREXISTS,			"NC: look up table already exists" },
	//
	{ NCERR_WRONGCHANNELINDEX,		"NC: nr in channel illegal" },
	{ NCERR_WRONGGROUPINDEX,		"NC: nr in group illegal" },
	//
	{ NCERR_UNKNOWNPLCTONCADDR,	"NC: Axis <-> PLC image missing or illegal in offset" },
	{ NCERR_UNKNOWNNCTOPLCADDR,	"NC: Axis <-> PLC out offset" },
	{ NCERR_UNKNOWNENCINADDR,		"NC: Encoder <-> IO image missing or illegal in offset" },
	{ NCERR_UNKNOWNENCOUTADDR,		"NC: Encoder <-> IO out offset" },
	{ NCERR_UNKNOWNDRIVEINADDR,	"NC: Drive <-> IO image missing or illegal in offset" },
	{ NCERR_UNKNOWNDRIVEOUTADDR,	"NC: Drive <-> IO out offset" },
	//
	{ NCERR_UNKNOWNDSLAVETYPE,		"NC: Unknown slave type" },
	{ NCERR_UNKNOWNAXISTYPE,		"NC: Unknown axis type" },
	{ NCERR_UNKNOWNCHNTYPE,			"NC: Unknown channel type" },

	{ NCCHNERR_GROUPINDEX,			"NCChn: illegal nr in group" },
	{ NCCHNERR_ADDR_GROUP,			"NCChn: illegal group ptr (0)" },
	{ NCCHNERR_NO_PLCINTERFACE,	"NCChn: NC-Channel <-> PLC image missing or illegal offset" },
	{ NCCHNERR_ILLEGALMFUNCNR,		"NCChn: illegal M function" },
	{ NCCHNERR_NOMEMORY,				"NcChn: Out of buffer memory" },
	{ NCCHNERR_ISBUSY,				"NcChn: Already busy" },
	{ NCCHNERR_NOTSUPPORTED,		"NcChn: Function not supported (may be wrong type)" },
	//
	{ NCCHNERR_NOFILE,				"NcChn: File not found" },
	{ NCCHNERR_ITPSYNTAXLT,			"NcChn: Itp LoadTime Syntax Error" },
	{ NCCHNERR_ITPSYNTAXRT,			"NCChn: Itp RunTime Syntax Error" },
	{ NCCHNERR_SUBNOTFOUND,			"NcChn: Calling undefined subroutine" },
	{ NCCHNERR_LOADBUFFERFULL,		"NcChn: Load buffer overrun" },
	//
	{ NCCHNERR_ZERODIVIDE,			"NcChn: Divide by zero" },
	{ NCCHNERR_BADCIRCLE,			"NcChn: Bad circle definition" },
	{ NCCHNERR_INVALIDOPERATION,	"NcChn: Invalid operation (FPU)" },
	//
	{ NCCHNERR_CALLSTACKOVR,		"NcChn: Call stack overrun" },
	{ NCCHNERR_CALLSTACKUDR,		"NcChn: Call stack underrun" },
	{ NCCHNERR_CALCSTACKOVR,		"NcChn: Calculator stack overrun" },
	{ NCCHNERR_CALCSTACKUDR,		"NcChn: Calculator stack underrun" },
	//
	{ NCCHNERR_REGINDEX,				"NcChn: Illegal register index" },
	{ NCCHNERR_GFUNCINDEX,			"NcChn: Illegal G func index" },
	{ NCCHNERR_MFUNCINDEX,			"NcChn: Illegal M func index" },
	{ NCCHNERR_EXTENDEDADDR,		"NcChn: Illegal extended addr" },
	{ NCCHNERR_MDBACCESSINDEX,		"NcChn: Illegal index while accessing MDB" },
	{ NCCHNERR_INTERNALINDEXH,		"NcChn: Illegal internal H func index" },
	//
	{ NCTRAFOERR_CANNOTCHANGE,		"NcTrafo: Cannot change tool params here" },
	{ NCTRAFOERR_CANNOTCORRECT,	"NcTrafo: Cannot calculate tool correction" },
	{ NCTRAFOERR_PLANE,				"NcTrafo: Cannot change tool plane here" },
	{ NCTRAFOERR_DPARAMINVALID,	"NcTrafo: Invalid or missing D parameter" },
	{ NCTRAFOERR_TOOLRADIUSINV,	"NcTrafo: Invalid tool radius" },
	{ NCTRAFOERR_CHANGETOOLRAD,	"NcTrafo: Cannot change tool radius here" },

#endif	// WIN32_RUNTIME

	{ 0xFFFFFFFF,						"Last Entry"} };


#endif	// _ADSAMSDLL
#endif	// VXD

////////////////////////////////////////////////////////////////////////////////
// Status codes for structured exceptions

#define TCMAKE_STATUS_CODE(FacilityCode, ID) ((NTSTATUS)(0xE0000000L) | ((FacilityCode) & 0xefff) << 16 | (USHORT)(ID))
#define TCCHECK_FACILITY_CODE(FacilityCode, ID) ((((ID)>>16)&0x0fff)==((FacilityCode)&0x0fff))

////////////////////////////////////////////////////////////////////////////////
// Common error codes which occur in different facilities
#pragma warning(disable: 4480)
enum : USHORT
{
	// general error (1...255 reserved for facility-specific codes)
	TC_COMMON_SEH_ERROR_ID								=	0x0000,

	// memory errors
	TC_COMMON_SEH_MEMORY_ERROR_ID						=	0x0100,
	TC_COMMON_SEH_MEMORY_CORRUPTION_ID				=	0x0101,
	TC_COMMON_SEH_MEMORY_ALLOCATION_FAILED_ID		=	0x0102,

	// frequent errors
	TC_COMMON_SEH_INCOMPATIBLE_ID						=	0x0201,	
	TC_COMMON_SEH_OUT_OF_RANGE_ID						=	0x0202,
	TC_COMMON_SEH_INVALID_PARAMETER_ID				=	0x0203,
	TC_COMMON_SEH_LENGTH_ERROR_ID						=	0x0204,
	TC_COMMON_SEH_INVALID_REFERENCE_COUNT_ID		=	0x0205,
	TC_COMMON_SEH_INVALID_SIZE_ID						=	0x0206,
	TC_COMMON_SEH_NULL_POINTER_ID						=	0x0207,
	TC_COMMON_SEH_OVERFLOW_ID							=	0x0208,
	TC_COMMON_SEH_NOT_SUPPORTED_ID					=	0x0209,

	// multi-threading errors
	TC_COMMON_SEH_MULTITHREADING_ERROR_ID			=	0x0300,
	TC_COMMON_SEH_CRITICAL_SECTION_ERROR_ID		=	0x0301,

	// assertions
	TC_COMMON_SEH_ASSERTION_FAILED_ID				=	0x0400,

	// debug errors (values > 0x8000 reserved for debug errors)
	TC_COMMON_SEH_DEBUG_ERROR_ID						=	0x8000
};
#pragma warning(default: 4480)

#define STATUS_ADS_MEMORY_CORRUPTION	TCMAKE_STATUS_CODE(FACILITY_TC_ADS, TC_COMMON_SEH_MEMORY_CORRUPTION_ID)

///////////////////////////////////////////////////////////////////////////////
// Vision
#define STATUS_TCVN_ERROR(ID)		TCMAKE_STATUS_CODE(FACILITY_TC_VN, ID)
#define STATUS_TCVN_DEBUG_ERROR(ID)	(STATUS_TCVN_ERROR((ID)|TC_COMMON_SEH_DEBUG_ERROR_ID) )

#pragma warning(disable: 4480)
enum : USHORT
{
	// general vision error
	TCVN_ERROR_ID								=	TC_COMMON_SEH_ERROR_ID,

	// vision-specific codes
	TCVN_LIBRARY_ERROR_ID					=	0x0001,							// general library error

	// memory errors
	TCVN_MEMORY_CORRUPTION_ID				=	TC_COMMON_SEH_MEMORY_CORRUPTION_ID,
	TCVN_MEMORY_ALLOCATION_FAILED_ID		=	TC_COMMON_SEH_MEMORY_ALLOCATION_FAILED_ID,

	// frequent errors
	TCVN_INCOMPATIBLE_ID						=	TC_COMMON_SEH_INCOMPATIBLE_ID,
	TCVN_OUT_OF_RANGE_ID						=	TC_COMMON_SEH_OUT_OF_RANGE_ID,
	TCVN_INVALID_PARAMETER_ID				=	TC_COMMON_SEH_INVALID_PARAMETER_ID,
	TCVN_LENGTH_ERROR_ID						=	TC_COMMON_SEH_LENGTH_ERROR_ID,
	TCVN_INVALID_REFERENCE_COUNT_ID		=	TC_COMMON_SEH_INVALID_REFERENCE_COUNT_ID,
	TCVN_INVALID_SIZE_ID						=	TC_COMMON_SEH_INVALID_SIZE_ID,
	TCVN_NULL_POINTER_ID						=	TC_COMMON_SEH_NULL_POINTER_ID,
	TCVN_NOT_SUPPORTED_ID					=	TC_COMMON_SEH_NOT_SUPPORTED_ID,

	// multi-threading errors
	TCVN_CRITICAL_SECTION_ERROR_ID		=	TC_COMMON_SEH_CRITICAL_SECTION_ERROR_ID,

	// assertions
	TCVN_ASSERTION_FAILED_ID				=	TC_COMMON_SEH_ASSERTION_FAILED_ID
};
#pragma warning(default: 4480)

#define STATUS_TCVN_GENERAL_ERROR				STATUS_TCVN_ERROR(TCVN_ERROR_ID)
#define STATUS_TCVN_LIBRARY_ERROR				STATUS_TCVN_ERROR(TCVN_LIBRARY_ERROR_ID)
#define STATUS_TCVN_MEMORY_CORRUPTION			STATUS_TCVN_ERROR(TCVN_MEMORY_CORRUPTION_ID)
#define STATUS_TCVN_MEMORY_ALLOCATION_FAILED	STATUS_TCVN_ERROR(TCVN_MEMORY_ALLOCATION_FAILED_ID)
#define STATUS_TCVN_INCOMPATIBLE					STATUS_TCVN_ERROR(TCVN_INCOMPATIBLE_ID)
#define STATUS_TCVN_OUT_OF_RANGE					STATUS_TCVN_ERROR(TCVN_OUT_OF_RANGE_ID)
#define STATUS_TCVN_INVALID_PARAMETER			STATUS_TCVN_ERROR(TCVN_INVALID_PARAMETER_ID)
#define STATUS_TCVN_LENGTH_ERROR					STATUS_TCVN_ERROR(TCVN_LENGTH_ERROR_ID)
#define STATUS_TCVN_INVALID_REFERENCE_COUNT	STATUS_TCVN_DEBUG_ERROR(TCVN_INVALID_REFERENCE_COUNT_ID)
#define STATUS_TCVN_INVALID_SIZE					STATUS_TCVN_ERROR(TCVN_INVALID_SIZE_ID)
#define STATUS_TCVN_NULL_POINTER					STATUS_TCVN_ERROR(TCVN_NULL_POINTER_ID)
#define STATUS_TCVN_NOT_SUPPORTED				STATUS_TCVN_ERROR(TCVN_NOT_SUPPORTED_ID)
#define STATUS_TCVN_CRITICAL_SECTION_ERROR	STATUS_TCVN_ERROR(TCVN_CRITICAL_SECTION_ERROR_ID)
#define STATUS_TCVN_ASSERTION_FAILED			STATUS_TCVN_DEBUG_ERROR(TCVN_ASSERTION_FAILED_ID)

///////////////////////////////////////////////////////////////////////////////
// Stl
#define STATUS_TCSTL_ERROR(ID)			TCMAKE_STATUS_CODE(FACILITY_TC_STL, ID)
#define STATUS_TCSTL_DEBUG_ERROR(ID)	(STATUS_TCSTL_ERROR((ID)|TC_COMMON_SEH_DEBUG_ERROR_ID) )

#pragma warning(disable: 4480)
enum : USHORT
{
	// general STL error
	TCSTL_ERROR_ID									=	TC_COMMON_SEH_ERROR_ID,	

	// STL-specific codes
	TCSTL_ITERATOR_NOT_INCREMENTABLE_ID		=	0x0001,						// iterator errors
	TCSTL_ITERATOR_NOT_DECREMENTABLE_ID		=	0x0002,
	TCSTL_ITERATOR_NOT_DEREFERENCABLE_ID	=	0x0003,

	TCSTL_ABORT_ID									=	0x0004,
	TCSTL_BAD_WEAK_PTR_ID						=	0x0005,
	TCSTL_BAD_OPTIONAL_ACCESS_ID				=	0x0006,

	// std::system_error with different error codes
	TCSTL_SYSTEM_ERROR_ID						=	0x0080,
	TCSTL_SE_OPERATION_NOT_PERMITTED			=	0x0001 | TCSTL_SYSTEM_ERROR_ID,
	TCSTL_SE_RESOURCE_DEADLOCK_WOULD_OCCUR	=	0x0002 | TCSTL_SYSTEM_ERROR_ID,

	// memory errors
	TCSTL_MEMORY_CORRUPTION_ID					=	TC_COMMON_SEH_MEMORY_CORRUPTION_ID,
	TCSTL_MEMORY_ALLOCATION_FAILED_ID		=	TC_COMMON_SEH_MEMORY_ALLOCATION_FAILED_ID,

	// other errors
	TCSTL_INCOMPATIBLE_ID						=	TC_COMMON_SEH_INCOMPATIBLE_ID,	
	TCSTL_OUT_OF_RANGE_ID						=	TC_COMMON_SEH_OUT_OF_RANGE_ID,
	TCSTL_INVALID_PARAMETER_ID					=	TC_COMMON_SEH_INVALID_PARAMETER_ID,
	TCSTL_LENGTH_ERROR_ID						=	TC_COMMON_SEH_LENGTH_ERROR_ID,
	TCSTL_OVERFLOW_ID								=	TC_COMMON_SEH_OVERFLOW_ID,
	TCSTL_NOT_SUPPORTED_ID						=	TC_COMMON_SEH_NOT_SUPPORTED_ID,

	// multi-threading errors
	TCSTL_CRITICAL_SECTION_ERROR				= TC_COMMON_SEH_CRITICAL_SECTION_ERROR_ID,

	// assertions
	TCSTL_ASSERTION_FAILED_ID					=	TC_COMMON_SEH_ASSERTION_FAILED_ID
};
#pragma warning(default: 4480)

#define STATUS_TCSTL_ITERATOR_NOT_INCREMENTABLE		STATUS_TCSTL_DEBUG_ERROR(TCSTL_ITERATOR_NOT_INCREMENTABLE_ID)
#define STATUS_TCSTL_ITERATOR_NOT_DECREMENTABLE		STATUS_TCSTL_DEBUG_ERROR(TCSTL_ITERATOR_NOT_DECREMENTABLE_ID)
#define STATUS_TCSTL_ITERATOR_NOT_DEREFERENCABLE	STATUS_TCSTL_DEBUG_ERROR(TCSTL_ITERATOR_NOT_DEREFERENCABLE_ID)
#define STATUS_TCSTL_ABORT									STATUS_TCSTL_ERROR(TCSTL_ABORT_ID)
#define STATUS_TCSTL_BAD_WEAK_PTR						STATUS_TCSTL_ERROR(TCSTL_BAD_WEAK_PTR_ID)
#define STATUS_TCSTL_BAD_OPTIONAL_ACCESS				STATUS_TCSTL_ERROR(TCSTL_BAD_OPTIONAL_ACCESS_ID)

#define STATUS_TCSTL_SE_OPERATION_NOT_PERMITTED				STATUS_TCSTL_ERROR(TCSTL_SE_OPERATION_NOT_PERMITTED)
#define STATUS_TCSTL_SE_RESOURCE_DEADLOCK_WOULD_OCCUR		STATUS_TCSTL_ERROR(TCSTL_SE_RESOURCE_DEADLOCK_WOULD_OCCUR)

#define STATUS_TCSTL_MEMORY_CORRUPTION					STATUS_TCSTL_DEBUG_ERROR(TCSTL_MEMORY_CORRUPTION_ID)
#define STATUS_TCSTL_MEMORY_ALLOCATION_FAILED		STATUS_TCSTL_ERROR(TCSTL_MEMORY_ALLOCATION_FAILED_ID)
#define STATUS_TCSTL_INCOMPATIBLE						STATUS_TCSTL_DEBUG_ERROR(TCSTL_INCOMPATIBLE_ID)
#define STATUS_TCSTL_OUT_OF_RANGE						STATUS_TCSTL_ERROR(TCSTL_OUT_OF_RANGE_ID)
#define STATUS_TCSTL_INVALID_PARAMETER					STATUS_TCSTL_DEBUG_ERROR(TCSTL_INVALID_PARAMETER_ID)
#define STATUS_TCSTL_LENGTH_ERROR						STATUS_TCSTL_DEBUG_ERROR(TCSTL_LENGTH_ERROR_ID)
#define STATUS_TCSTL_OVERFLOW								STATUS_TCSTL_DEBUG_ERROR(TCSTL_OVERFLOW_ID)
#define STATUS_TCSTL_NOT_SUPPORTED						STATUS_TCSTL_ERROR(TCSTL_NOT_SUPPORTED_ID)
#define STATUS_TCSTL_CRITICAL_SECTION_ERROR			STATUS_TCSTL_ERROR(TCSTL_CRITICAL_SECTION_ERROR)
#define STATUS_TCSTL_ASSERTION_FAILED					STATUS_TCSTL_DEBUG_ERROR(TCSTL_ASSERTION_FAILED_ID)


///////////////////////////////////////////////////////////////////////////////
// Json
#define STATUS_TCJSON_ERROR(ID)			TCMAKE_STATUS_CODE(FACILITY_TC_JSON, ID)
#define STATUS_TCJSON_DEBUG_ERROR(ID)	(STATUS_TCJSON_ERROR((ID)|TC_COMMON_SEH_DEBUG_ERROR_ID) )

enum TcJsonErrorIds : USHORT
{
	// general JSON error
	TCJSON_ERROR_ID								=	TC_COMMON_SEH_ERROR_ID,

	// memory error 
	TCJSON_MEMORY_ALLOCATION_FAILED_ID		=	TC_COMMON_SEH_MEMORY_ALLOCATION_FAILED_ID,

	// assertion
	TCJSON_ASSERTION_FAILED_ID					=	TC_COMMON_SEH_ASSERTION_FAILED_ID
};

#define STATUS_TCJSON_MEMORY_ALLOCATION_FAILED	STATUS_TCJSON_ERROR(TCJSON_MEMORY_ALLOCATION_FAILED_ID)
#define STATUS_TCJSON_ASSERTION_FAILED				STATUS_TCJSON_DEBUG_ERROR(TCJSON_ASSERTION_FAILED_ID)


///////////////////////////////////////////////////////////////////////////////
// OpenMP
#define STATUS_TCOPENMP_ERROR(ID)		TCMAKE_STATUS_CODE(FACILITY_TC_OPENMP, ID)
#define STATUS_TCOPENMP_DEBUG_ERROR(ID)	(STATUS_TCOPENMP_ERROR((ID)|TC_COMMON_SEH_DEBUG_ERROR_ID) )

#pragma warning(disable: 4480)
enum : USHORT
{
	// general openmp error
	TCOPENMP_ERROR_ID = TC_COMMON_SEH_ERROR_ID,

	// openmp specific error
	TCOPENMP_TASK_NOT_REGISTERED_ERROR_ID = 0x0001,
	TCOPENMP_PARAJOB_MISSING_ERROR_ID = 0x002,
	TCOPENMP_PARAJOB_BARRIER_ERROR_ID = 0x003,
	TCOPENMP_VERSION_NOTSUPPORTED_ERROR_ID = 0x004,

};
#pragma warning(default: 4480)

#define STATUS_TCOPENMP_TASK_NOT_REGISTERED_ERROR	STATUS_TCOPENMP_ERROR(TCOPENMP_TASK_NOT_REGISTERED_ERROR_ID)
#define STATUS_TCOPENMP_PARAJOB_MISSING_ERROR		STATUS_TCOPENMP_ERROR(TCOPENMP_PARAJOB_MISSING_ERROR_ID)
#define STATUS_TCOPENMP_PARAJOB_BARRIER_ERROR		STATUS_TCOPENMP_ERROR(TCOPENMP_PARAJOB_BARRIER_ERROR_ID)
#define STATUS_TCOPENMP_VERSION_NOTSUPPORTED		STATUS_TCOPENMP_ERROR(TCOPENMP_VERSION_NOTSUPPORTED_ERROR_ID)

///////////////////////////////////////////////////////////////////////////////
// Plc
#define STATUS_TCPLC_ERROR(ID)			TCMAKE_STATUS_CODE(FACILITY_TC_PLC, ID)
#define STATUS_TCPLC_DEBUG_ERROR(ID)	(STATUS_TCPLC_ERROR((ID)|TC_COMMON_SEH_DEBUG_ERROR_ID) )

#pragma warning(disable: 4480)
enum : USHORT
{
	// general PLC error
	TCPLC_ERROR_ID				= TC_COMMON_SEH_ERROR_ID,

	// User has thrown an exception in their code
	TCPLC_USER_EXCEPTION		= 0x0001,

	// User has called an abort or PLC has decided to abort
	TCPLC_ABORT					= 0x0002,

	// Runtime is experiencing an error because of the user
	TCPLC_RUNTIME_EXCEPTION	=0x0003,
};
#pragma warning(default: 4480)

#define STATUS_TCPLC_USER_EXCEPTION			STATUS_TCPLC_ERROR(TCPLC_USER_EXCEPTION)
#define STATUS_TCPLC_ABORT						STATUS_TCPLC_ERROR(TCPLC_ABORT)
#define STATUS_TCPLC_RUNTIME_EXCEPTION		STATUS_TCPLC_ERROR(TCPLC_RUNTIME_EXCEPTION)
