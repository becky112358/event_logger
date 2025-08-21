///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"
#ifdef TCOS_APP
#include "TcString.h"
#endif

#define	RELATIVE_AMSNETID
#define	AMS_COMPRESSION

///////////////////////////////////////////////////////////////////////////////
//	FIXED PORTS

#define	AMSPORT_ROUTER					1
#define	AMSPORT_DEBUGGER				2
#define	AMSPORT_R0_TCOMSERVER		10		// dpc or passive level
#define	AMSPORT_R0_TCOMSERVERTASK	11		// rt context
#define	AMSPORT_R0_TCOMSERVER_PL	12		// passive level
#define	AMSPORT_R0_TCDEBUGGER		20		
#define	AMSPORT_R0_TCDEBUGGERTASK	21
#define	AMSPORT_R0_LICENSESERVER	30
#define	AMSPORT_R0_SYSTEM				50

#define	AMSPORT_LOGGER					100
#define	AMSPORT_EVENTLOG				110
#define	AMSPORT_DEVICEAPPLICATION	120	// application for coupler (EK), gateway (EL), etc.
#define	AMSPORT_EVENTLOG_UM             130
#define	AMSPORT_EVENTLOG_RT             131
#define	AMSPORT_EVENTLOG_PUBLISHER      132
#define	AMSPORT_R0_RTIME				200
#define	AMSPORT_R0_TRACE				(AMSPORT_R0_RTIME+90)
#define	AMSPORT_R0_IO					300
#define	AMSPORT_R0_SPS					400	// LEGACY
#define	AMSPORT_R0_MC					400	
#define	AMSPORT_R0_NC					500
#define	AMSPORT_R0_NCSAF				501
#define	AMSPORT_R0_NCSVB				511
#define	AMSPORT_R0_NCINSTANCE		520	// for preconfigured Nc2-Nc3-Instance
//#define	AMSPORT_R0_NCSTUBSAF		521	// for preconfigured PollCallStub with SAF-Context (NCINSTANCE+1)
//#define	AMSPORT_R0_NCSTUBSVB		522	// for preconfigured PollCallStub with SVB-Context (NCINSTANCE+2)
#define	AMSPORT_R0_ISG					550
#define	AMSPORT_R0_CNC					600
#define	AMSPORT_R0_LINE				700
#define	AMSPORT_R0_PLC					800
#define	AMSPORT_R0_RTS					850
#define	AMSPORT_R0_CAM					900
#define	AMSPORT_R0_CAMTOOL			950

#define	AMSPORT_R0_IOPORTBEGIN		1000
#define	AMSPORT_R0_IOPORTEND			1199

#define	AMSPORT_R0_USER				2000

#define	AMSPORT_R3_SYSSERV			10000
#define	AMSPORT_R3_CTRLPROG			10000
#define	AMSPORT_R3_SYSCTRL			10001
#define	AMSPORT_R3_SYSSAMPLER		10100
#define	AMSPORT_R3_TCPRAWCONN		10200
#define	AMSPORT_R3_TCPIPSERVER		10201
#define	AMSPORT_R3_SYSMANAGER		10300
#define	AMSPORT_R3_SMSSERVER			10400 
#define	AMSPORT_R3_MODBUSSERVER		10500
#define	AMSPORT_R3_AMSLOGGER			10502
#define	AMSPORT_R3_XMLDATASERVER	10600
#define	AMSPORT_R3_AUTOCONFIG		10700
#define	AMSPORT_R3_PLCCONTROL		10800	// CoDeSys
#define	AMSPORT_R3_FTPCLIENT			10900
#define	AMSPORT_R3_NCCTRL				11000
#define	AMSPORT_R3_NCINTERPRETER	11500
#define	AMSPORT_R3_GSTINTERPRETER	11600
#define	AMSPORT_R3_STRECKECTRL		12000
#define	AMSPORT_R3_CAMCTRL			13000
#define	AMSPORT_R3_SCOPE				14000
#define	AMSPORT_R3_SCOPE_END			14099
#define  AMSPORT_R3_CONDITIONMON    14100
#define	AMSPORT_R3_REPORTING			14200
#define	AMSPORT_R3_SINECH1			15000
#define	AMSPORT_R3_CONTROLNET		16000
#define	AMSPORT_R3_OPCSERVER			17000
#define	AMSPORT_R3_OPCCLIENT			17500
#define	AMSPORT_R3_MAILSERVER		18000		// 0x4650
#define	AMSPORT_R3_EL60XX				19000		// 0x4A38
#define	AMSPORT_R3_MANAGEMENT		19100
#define	AMSPORT_R3_MIELEHOME			19200
#define	AMSPORT_R3_CPLINK3			19300
#define	AMSPORT_R3_TOUCHLOCK			19310
#define	AMSPORT_R3_VNSERVICE			19500
#define	AMSPORT_R3_MULTIUSER			19600
#define	AMSPORT_R3_NI845X				19700
#define	AMSPORT_R3_UMRUNTIME			20000

#define	AMSPORT_R3_CUSTOMER_FIRST	25000		// 0x61A8
#define	AMSPORT_R3_CUSTOMER_LAST	25999		// 0x658F

#define	AMSPORT_FIRST					1
#define	AMSPORT_LAST					0xFFFE

#define	AMSPORT_UNFIXEDPORT			0
#define	AMSPORT_USEDEFAULT			0xFFFF

#define	AMSPORT_IOIMAGEBEGIN			0x6D00	
#define	AMSPORT_IOIMAGEEND			0x6DFF
#define	AMSPORT_IOBOXBEGIN_USB		0x6E00	// fixed ams ports for USB devices (plus dip-switch value)
#define	AMSPORT_IOBOXEND_USB			0x6EFF
#define	AMSPORT_IODEVBEGIN			0x7000
#define	AMSPORT_IODEVEND				0x70FF
#define	AMSPORT_IOBOXBEGIN			0x7100
#define	AMSPORT_IOBOXEND				0x7FFF

#define	AMSPORT_FREEBEGIN				0x8000
#define	AMSPORT_FREEEND				0xBFFF


#define	AMSPORT_NAMESIZE				31

///////////////////////////////////////////////////////////////////////////////
//	Port types
typedef enum
{
	PORTTYPE_INVALID				= -1,
	PORTTYPE_ROUTER				= 0x00, // compatibility issue
	PORTTYPE_R3PORT				= 0x01,
	PORTTYPE_R0CTRLPORT			= 0x02,
	PORTTYPE_R0TASKPORT			= 0x03,
	PORTTYPE_R0IOPORT				= 0x04,
	PORTTYPE_TPPORT				= 0x05,
	PORTTYPE_R3PORTITF			= 0x06,
	PORTTYPE_R0CTRLPORTITF		= 0x07,
	PORTTYPE_R0TASKPORTITF		= 0x08,
	PORTTYPE_R0IOPORTITF			= 0x09,
	PORTTYPE_R0PLPORT				= 0x0A,	// passive level port
	PORTTYPE_R0PLPORTITF			= 0x0B,	// passive level port
	PORTTYPE_TPPORTITF			= 0x10,
	PORTTYPE_MAXVAL				= 0xFF
}AMSPORT_TYPE;

///////////////////////////////////////////////////////////////////////////////
//	Port attributes
const	ULONG PORTATTRIB_UNDEF		= 0x00000000;
const	ULONG PORTATTRIB_ADS		= 0x00000001;
const	ULONG PORTATTRIB_SERVER		= 0x00000002;
const	ULONG PORTATTRIB_CLIENT		= 0x00000004;
const	ULONG PORTATTRIB_HASSYMBOLS	= 0x00000008;
const	ULONG PORTATTRIB_ISSYNC		= 0x00000010;
const	ULONG PORTATTRIB_ASYNC_RECV	= 0x00000020;
const	ULONG PORTATTRIB_IDLECALL	= 0x00000040;
const	ULONG PORTATTRIB_ADSSECURE	= 0x00000080;
const	ULONG PORTATTRIB_NOADSCHANGE= 0x00000100;
const	ULONG PORTATTRIB_WIN32PORT = 0x00000200;
const	ULONG PORTATTRIB_UMPORT = 0x00000400;
const	ULONG PORTATTRIB_R3FILEOBJ	= 0x80000000;

///////////////////////////////////////////////////////////////////////////////
//	Transport Types (TCP/IP, ...)
typedef enum
{
	NONE				=0,
	TCP_IP			=1,
	IIO_LIGHTBUS	=2,
	PROFIBUS_DP		=3,
	PCI_ISA_BUS		=4,
	ADS_UDP			=5,
	FATP_UDP			=6,
	COM_PORT			=7,
	USB				=8,
	CAN_OPEN			=9,
	DEVICE_NET		=10,
	SSB				=11,
	SOAP				=12,
	ETHERCAT			=13,
	MQTT				=14,
	MAX_TYPES
} AMS_TRANSPORTID;

///////////////////////////////////////////////////////////////////////////////
// global timeout value for remote connections
const ULONG g_coAmsRemoteTimeout=2000; // ms

///////////////////////////////////////////////////////////////////////////////
//	Command IDs

#define	AMSCMD_LOGMESSAGE				0x0001
#define	AMSCMD_ROUTERSHUTDOWN		0x0002
#define	AMSCMD_ROUTERACTIVATED		0x0003
#define	AMSCMD_SYSTEMREMOVED			0x0004
#define	AMSCMD_CLOSECONNECTION		0x0005
#define	AMSCMD_PROCESSORDER			0x00E0
#define	AMSCMD_SAVESYMVERSION		0x00FA
#define	AMSCMD_SIGNALSTART			0x00FB
#define	AMSCMD_SIGNALSTOP				0x00FC
#define	AMSCMD_HANDLERETAINDATA		0x00FD
#define	AMSCMD_DEVICECONFIGID		0x00FE
#define	AMSCMD_DOWNLOADSYMBOLS		0x00FF

#define	AMS_ERRLOGCMDS					0x100

#define	AMS_TASKCMDS					0x500
#define	AMS_CTRLCMDS					0x600

#define	AMS_ROUTERCMDS					0x900
#define	AMS_RTIMECMDS					0x1000
#define	AMS_TRACECMDS					(AMS_RTIMECMDS+0x900)
#define	AMS_IOCMDS						0x2000
#define	AMS_C1220CMDS					(AMS_IOCMDS+0x100)
#define	AMS_FCxxxxCMDS					(AMS_IOCMDS+0x200)
#define	AMS_SPSCMDS						0x3000
#define	AMS_NCCMDS						0x4000
#define	AMS_PLCCMDS						0x5000
#define	AMS_LINECMDS					0x6000
#define	AMS_CAMCMDS						0x7000

#define	AMS_CMDSPECIFIC				0x8000


///////////////////////////////////////////////////////////////////////////////
//	AmsHead
#define	MACHINEIDENTRYDONTCARE		0xFF
#define	AMS_NETIDLEN					23			// max. string length of an ams net id
															// without the terminating zero

#pragma pack( push, 1 )
typedef struct DLL_EXPORT AmsNetId_
{
	BYTE			b[6];

	int operator% (int hashSize) const;	// for calculating the hashvalue
	BOOL operator== ( const AmsNetId_& netId ) const;
	BOOL operator!= ( const AmsNetId_& netId ) const;
	BOOL operator> ( const AmsNetId_& netId ) const;
	BOOL operator< ( const AmsNetId_& netId ) const;
#if _MSC_VER < 1900
	void operator= ( const AmsNetId_& netId );
#endif
	void Clear();
	BOOL IsValid();
	BOOL IsRelative();
	void	SetRelative();
	BOOL	SetRelative(const AmsNetId_ &netId);
	void	ClearRelative(const AmsNetId_ &netId);
	AmsNetId_ GetAbsolute(const AmsNetId_ &netId);
#if defined(__ATLSTR_H__) || defined(_AFXDLL)
	void Id2String(CString& rcsNetId );
	CString Id2String();
	CString Id2String(const AmsNetId_& netId);
	void operator= ( const CString& csNetId );
#elif defined(TCOS_APP)
	CString Id2String();
#endif
	void operator= (LPCTSTR szNetId);
} AmsNetId, *PAmsNetId;

typedef	WORD	AmsPortNo, *PAmsPortNo;

const AmsNetId AMSNETID_NULL		= {0};
const AmsNetId AMSNETID_LOOPBACK	= {127, 0, 0, 1, 1, 1};
const AmsNetId AMSNETID_SUMUPCMD	= {0xff, 0xff, 0, 0, 0, 0};

typedef struct DLL_EXPORT AmsAddr_
{
	AmsNetId		netId;
	AmsPortNo	port;
	AmsAddr_( );
	AmsAddr_( AmsNetId	newNetId, AmsPortNo newPort );
	void	Clear();
#if defined(__ATLSTR_H__) || defined(_AFXDLL)
	AmsAddr_( const CString& csNetId, AmsPortNo newPort );
#endif	//	_AFXDLL
	BOOL operator== ( const AmsAddr_& addr ) const;
	BOOL operator!= ( const AmsAddr_& addr ) const;
	BOOL operator< ( const AmsAddr_& addr ) const;
	BOOL operator> ( const AmsAddr_& addr ) const;
#if _MSC_VER < 1900
	void operator= ( const AmsAddr_& addr );
#endif
} AmsAddr, *PAmsAddr;

// support for using AmsNetId and AmsAddr as a key in sdt::map
#ifdef _WIN64 
#define	STD_MAP_AMSNETID_SUPPORT() \
namespace std { \
template <> struct hash<AmsNetId>{ \
	std::size_t operator()(const AmsNetId& k) const	{ \
		std::size_t s=0; \
		memcpy(&s, &s, sizeof(AmsNetId); \
		return s; \
	} }; \
template <> struct equal_to<AmsNetId> { \
	bool operator ()(const AmsNetId & a,const AmsNetId & b) const 	{ \
		return memcmp(&a, &b, sizeof(AmsNetId)) == 0; \
	}}; }

#define	STD_MAP_AMSADDR_SUPPORT() \
namespace std { \
template <> struct hash<AmsAddr>{ \
	std::size_t operator()(const AmsAddr& k) const { \
		return *(std::size_t*)&k; \
	}}; \
template <> struct equal_to<AmsAddr> { \
	bool operator ()(const AmsAddr & a,const AmsAddr & b) const	{ \
		return memcmp(&a, &b, sizeof(AmsAddr)) == 0; \
	}};}
#else
#define	STD_MAP_AMSNETID_SUPPORT() \
namespace std { \
template <> struct hash<AmsNetId>{ \
	std::size_t operator()(const AmsNetId& k) const	{ \
		return ((UINT)(void*)((DWORD)k.b[2])); \
	} }; \
template <> struct equal_to<AmsNetId> { \
	bool operator ()(const AmsNetId & a,const AmsNetId & b) const 	{ \
		return memcmp(&a, &b, sizeof(AmsNetId)) == 0; \
	}}; }

#define	STD_MAP_AMSADDR_SUPPORT() \
namespace std { \
template <> struct hash<AmsAddr>{ \
	std::size_t operator()(const AmsAddr& k) const { \
		return ((PULONG)&k)[0] ^ ((PULONG)&k)[1]; \
	}}; \
template <> struct equal_to<AmsAddr> { \
	bool operator ()(const AmsAddr & a,const AmsAddr & b) const	{ \
		return memcmp(&a, &b, sizeof(AmsAddr)) == 0; \
	}};}
#endif

typedef struct
{ 
	AmsAddr		target;
	AmsAddr		sender;
	WORD			cmdId;			// command id
	WORD			stateFlags;		// state flags		
	DWORD			cbData;			// count bytes for actual command (excl. AmsHead)
	union 
	{
		LONG		errCode;			// error code
		LONG		hRcv;				// receive handle
	};
	union 
	{
		LONG	hUser;				//	user handle
		struct
		{
			USHORT	fragmentNo;		// increasing no
			USHORT	packetNo;		//	unique no of all fragments in a packet
		};
	};
} AmsHead, *PAmsHead;

///////////////////////////////////////////////////////////////////////////////
//	State flags

#define	AMSCMDSF_RESPONSE			0x0001				// command is executed
#define	AMSCMDSF_NORETURN			0x0002
#define	AMSCMDSF_ADSCMD			0x0004
#define	AMSCMDSF_SYSCMD			0x0008				// internal generated cmds
#define	AMSCMDSF_HIGHPRIO			0x0010				// R0 to R0 checked at task begin
#define	AMSCMDSF_TIMESTAMPADDED	0x0020				// cbData um 8 Byte vergrößert
#define	AMSCMDSF_UDP				0x0040				// UDP instead of TCP
#define	AMSCMDSF_INITCMD			0x0080				// command during init phase of TwinCAT
#define	AMSCMDSF_BROADCAST		0x8000

///////////////////////////////////////////////////////////////////////////////
//AmsCmd

typedef struct
{
	AmsHead	head;					// head for the string command
} AmsCmd, *PAmsCmd;

#define	SIZEOF_AmsCmd(p)		(sizeof(AmsHead) + ((PAmsCmd)p)->head.cbData)

///////////////////////////////////////////////////////////////////////////////
// AmsRegisterPort
struct DLL_EXPORT AmsRegisterPort
{
	AmsRegisterPort
	(
		AmsPortNo port,
		LPCSTR pszName,
		BOOL bFixed,
		WORD queueSize,
		AMSPORT_TYPE portType,
		DWORD dwPortAttrib
	);
	AmsRegisterPort();

	BOOL				m_bFixedPort;		//	if not bFixedPort the router will choose a port
	AmsPortNo		m_port;
	WORD				m_queueSize;
	AMSPORT_TYPE	m_portType;
	DWORD				m_dwPortAttrib;
	char				m_szPortName[AMSPORT_NAMESIZE+1];
};
typedef	struct AmsRegisterPort* PAmsRegisterPort;

struct DLL_EXPORT AmsRegisterPortOut
{
	AmsPortNo	m_port;
	WORD			m_err;
};
typedef	struct AmsRegisterPortOut* PAmsRegisterPortOut;

///////////////////////////////////////////////////////////////////////////////
// AmsRegisterR3PortIn
struct	DLL_EXPORT AmsRegisterR3PortIn : public AmsRegisterPort
{
	AmsRegisterR3PortIn
	(
		AmsPortNo port,
		LPCSTR pszName=NULL,
		BOOL bFixed=FALSE,
		BOOL bUnReg=FALSE,
		WORD queueSize=0x50,
		AMSPORT_TYPE portType=PORTTYPE_R3PORT,
		DWORD dwPortAttrib=PORTATTRIB_CLIENT 
	);
	AmsRegisterR3PortIn();
	BOOL m_bUnRegister;
};
typedef AmsRegisterR3PortIn *PAmsRegisterR3PortIn;

struct	AmsRegisterR3PortOut	: public AmsRegisterPortOut
{
};
typedef AmsRegisterR3PortOut *PAmsRegisterR3PortOut;

///////////////////////////////////////////////////////////////////////////////
// AmsRegisterTpPortIn
struct DLL_EXPORT AmsRegisterTpPortIn : public AmsRegisterPort
{ 
	AmsRegisterTpPortIn
	(
		AmsPortNo port,
		AmsNetId netId,
		LPCSTR pszName=NULL,
		BOOL bFixed=FALSE,
		BOOL bUnReg=FALSE,
		WORD queueSize=0x50,
		AMSPORT_TYPE portType=PORTTYPE_TPPORT,
		DWORD dwPortAttrib=PORTATTRIB_SERVER
	);
	AmsRegisterTpPortIn();

	BOOL m_bUnRegister;
	AmsNetId	m_netId;
};
typedef AmsRegisterTpPortIn* PAmsRegisterTpPortIn;

#pragma pack( pop )

///////////////////////////////////////////////////////////////////////////////
// CAmsPort
class	DLL_EXPORT CAmsPort
{
public:
	CAmsPort();
	CAmsPort
	(
		AmsPortNo port, 
		LPCSTR pszPortName = NULL,
		AMSPORT_TYPE type = PORTTYPE_INVALID,
		DWORD	dwAttrib = PORTATTRIB_UNDEF
	);

	// Ams API
	virtual BOOL			AmsSend( PAmsCmd pCmd );
	virtual void			AmsReceive( PAmsCmd pCmd ) = 0;
	virtual void			AmsDispatch( PAmsCmd pCmd );

	// Ams helper funtions
	virtual	PAmsCmd		AmsAlloc( LONG size = sizeof(AmsHead) ) = 0;
	virtual	void			AmsFree( PAmsCmd pCmd ) = 0;

	virtual	PAmsCmd		AmsAllocCopy( PAmsCmd pCmd, LONG size );
	virtual	PAmsCmd		AmsAllocCopy( PAmsCmd pCmd );
	virtual	PAmsCmd		AmsAllocCopyHead( PAmsCmd pCmd, LONG size );

	virtual	void			AmsCopy( PAmsCmd pDest, PAmsCmd pSrc );
	virtual	void			AmsCopy( PAmsCmd pDest, PAmsCmd pSrc, LONG size );
	virtual	void			AmsCopyHead( PAmsCmd pDest, PAmsCmd pSrc );
	virtual	void			AmsSetAddr( AmsAddr& addr );
	virtual	void			AmsResponse( PAmsCmd pCmd, LONG errCode = 0 );
	virtual	BOOL			AmsIsResponseCommand( PAmsCmd pCmd );

	virtual	AmsNetId		AmsGetNetId();
	virtual	AmsPortNo	AmsGetPort();
	virtual	AmsAddr		AmsGetAddr();
	virtual	BOOL			AmsPortConnected();
	virtual	DWORD			AmsGetLastError( );

	virtual	void	AmsMakeHead
	(
		AmsHead& head,
		WORD cmdId,
		LONG cbData,
		AmsNetId targetNetId,
		AmsPortNo targetPort,
		LONG hUser = 0,
		LONG errCode = 0,
		WORD stateFlags = 0
	);
	
	virtual	void	AmsMakeHead
	(
		AmsHead& head,
		WORD cmdId,
		LONG cbData,
		AmsAddr targetAddr,
		LONG hUser = 0,
		LONG errCode = 0,
		WORD stateFlags=0
	);
	
	virtual	void			AmsSwitchTarget( AmsHead& head );
	virtual	void			AmsSwitchTarget( PAmsCmd pCmd );
	virtual	void			AmsCopyHeadAndSwitchTarget( PAmsCmd pDest, PAmsCmd pSrc );
	virtual	PAmsCmd		AmsAllocCopyHeadAndSwitchTarget( PAmsCmd pSrc );
	
	virtual	void			AmsSetError( PAmsCmd pCmd, LONG errCode );
	virtual	DWORD			AmsGetPortType( );
protected:
	virtual	LPCSTR		SetPortName( LPCSTR pszPortName );
	virtual	LPCSTR		AppendPortName( LPCSTR pszPortName );

	AmsAddr			m_addr;
	BOOL				m_bConnected;
	DWORD				m_nLastError;
	AMSPORT_TYPE	m_type;
	DWORD				m_dwAttrib;
	char				m_szName[AMSPORT_NAMESIZE];
};


///////////////////////////////////////////////////////////////////////////////
//	AMSCMD_HANDLERETAINDATA
enum nHandleRetainData
{
	IGNORERETAINDATA			= 0,
	STORERETAINDATA			= 1,
	LOADSTORERETAINDATA		= 2,
	TRYLOADSTORERETAINDATA	= 3,
};

#pragma pack( push, 1 )
typedef struct
{
	AmsHead	head;							// head for the string command
	ULONG		handleRetain;
} HandleRetainDataCmd, *PHandleRetainDataCmd;

#pragma pack( pop )
