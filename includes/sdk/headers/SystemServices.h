///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Ams.h"

///////////////////////////////////////////////////////////////////////////////
#define	SYSTEMSERVICE_NOSEEK				-1
#define	SYSTEMSERVICE_DELETEONCLOSE	-2

#define	SYSTEMSERVICE_ERROR			0xFFFFFFFF
#define	SYSTEMSERVICE_NOERROR		0
#define	SYSTEMSERVICE_1ST_POTENTIAL_HANDLE 	0x1000
#define	SYSTEMSERVICE_1STHANDLE 	0xF600
#define	SYSTEMSERVICE_SEEKTOEND		0xFFFFFFFE

#define	SYSTEMSERVICE_REGISTRY_INVALIDKEY	1
#define	SYSTEMSERVICE_REGISTRY_INVALIDVAL	2
#define  SYSTEMSERVICE_REGISTRY_INVALIDSIZE	3

#define	SYSTEMSERVICE_OLDBOOTDATAFLAG	0x80000000

//#define	TC_BETA_EXPIRE_FILETIME			0x01ccc8182a383a00	// 31.12.2011 23:59
//#define	TC_BETA_EXPIRE_FILETIME			0x01ccf73e1b013a00	// 29.2.2012 23:59
//#define	TC_BETA_EXPIRE_FILETIME			0x01cd272d3633fa00	// 30.4.2012 23:59
//#define	TC_BETA_EXPIRE_FILETIME			0x01cdcf56aa9a7a00	// 30.11.2012 23:59
//#define	TC_BETA_EXPIRE_FILETIME			0x01ce000ef036fa00	// 31.1.2013 23:59
//#define	TC_BETA_EXPIRE_FILETIME				0x01ce45feaefaba00	// 30.4.2013 23:59
//#define	TC_BETA_EXPIRE_FILETIME				0x01ce5e5ad1c8fa00	// 31.5.2013 23:59
//#define	TC_BETA_EXPIRE_FILETIME				0x01ce75edca2d7a00	// 30.6.2013 23:59
#define	TC_BETA_EXPIRE_FILETIME			0

#pragma pack( push, 1 )

///////////////////////////////////////////////////////////////////////////////
enum nSystemServiceIndexGroups
{
	SYSTEMSERVICE_OPENCREATE				= 100,
	SYSTEMSERVICE_OPENREAD					= 101,
	SYSTEMSERVICE_OPENWRITE					= 102,
	SYSTEMSERVICE_CREATEFILE				= 110,
	SYSTEMSERVICE_CLOSEHANDLE				= 111,
	SYSTEMSERVICE_FFLUSH						= 112,
	SYSTEMSERVICE_DEVICENAMESBYCLASS		= 113,
	SYSTEMSERVICE_FTRUNCATE					= 114,
	SYSTEMSERVICE_FGENERATECRC				= 115,
	SYSTEMSERVICE_FOPEN						= 120,
	SYSTEMSERVICE_FCLOSE						= 121,
	SYSTEMSERVICE_FREAD						= 122,
	SYSTEMSERVICE_FWRITE						= 123,
	SYSTEMSERVICE_FSEEK						= 124,
	SYSTEMSERVICE_FTELL						= 125,
	SYSTEMSERVICE_FGETS						= 126,
	SYSTEMSERVICE_FPUTS						= 127,
	SYSTEMSERVICE_FSCANF						= 128,
	SYSTEMSERVICE_FPRINTF					= 129,
	SYSTEMSERVICE_FEOF						= 130,
	SYSTEMSERVICE_FDELETE					= 131,
	SYSTEMSERVICE_FRENAME					= 132,
	SYSTEMSERVICE_FFILEFIND					= 133,
	SYSTEMSERVICE_FGETSTATUS				= 134,
	SYSTEMSERVICE_FGETSIZE_BY_HANDLE		= 135,
	SYSTEMSERVICE_FCOPY						= 136,
	SYSTEMSERVICE_FGETMD5HASH				= 137,
	SYSTEMSERVICE_MKDIR						= 138,
	SYSTEMSERVICE_RMDIR						= 139,

	SYSTEMSERVICE_UDP_SOCKET				= 140,
	SYSTEMSERVICE_UDP_DISCOVERY			= 141,
	SYSTEMSERVICE_CP_DISCOVERY				= 142,
#ifdef AMS_COMPRESSION
	SYSTEMSERVICE_FZREAD						= 145,
	SYSTEMSERVICE_FZWRITE					= 146,
#endif

	SYSTEMSERVICE_XML_CREATEWRITER		= 150,
	SYSTEMSERVICE_XML_STARTELEMENT		= 151,
	SYSTEMSERVICE_XML_ENDELEMENT			= 152,	
	SYSTEMSERVICE_XML_ADDATTRIBUTE		= 153,
	SYSTEMSERVICE_XML_FILLCHARELEMENT	= 154,
	SYSTEMSERVICE_XML_MULTIWRITE			= 155,
	SYSTEMSERVICE_XML_CLOSEWRITER			= 156,

	SYSTEMSERVICE_PRODUCT_VERSION			= 160,

	SYSTEMSERVICE_ADD_INITCMD				= 170,
	SYSTEMSERVICE_DEL_INITCMD				= 171,
	SYSTEMSERVICE_DEL_ALLADDEDINITCMDS	= 172,

	SYSTEMSERVICE_HASHED_BOOTDATA			= 180,

	SYSTEMSERVICE_REG_HKEYLOCALMACHINE	= 200,
	SYSTEMSERVICE_REG_HKEYCURRENTUSER	= 201,
	SYSTEMSERVICE_REG_HKEYCLASSESROOT	= 202,
	SYSTEMSERVICE_REG_FLUSHLOCALMACHINE	= 203,
	SYSTEMSERVICE_REG_FLUSHCURRENTUSER	= 204,
	SYSTEMSERVICE_REG_FLUSHCLASSESROOT	= 205,
	
	SYSTEMSERVICE_SYS_CONTROL				= 220,
	SYSTEMSERVICE_SYS_LOAD_SERVER			= 230,
	SYSTEMSERVICE_SYSSERV_STATE			= 240,
	
	SYSTEMSERVICE_SENDEMAIL					= 300,

	SYSTEMSERVICE_TIMESERVICES				= 400,
	SYSTEMSERVICE_STARTPROCESS				= 500,
	SYSTEMSERVICE_CHANGENETID				= 600,
	SYSTEMSERVICE_QUERYNETID				= 601,
	SYSTEMSERVICE_TARGETINFO				= 700,
	SYSTEMSERVICE_IPHELPERAPI				= 701,
	SYSTEMSERVICE_IPHOSTNAME				= 702,
	SYSTEMSERVICE_IPADDRINFO				= 703,

	SYSTEMSERVICE_ADDREMOTE					= 801,
	SYSTEMSERVICE_DELREMOTE					= 802,
	SYSTEMSERVICE_ENUMREMOTE				= 803,
	SYSTEMSERVICE_TEST_CONNECTION			= 804,
	SYSTEMSERVICE_CHANGEREMOTEFILE		= 805,

	SYSTEMSERVICE_REMOVE_AUTOINSTALL_DRIVER	= 821,

	SYSTEMSERVICE_SCREENRES					= 900,
	SYSTEMSERVICE_SCREENRESMODES			= 901,

	SYSTEMSERVICE_CSMI						= 1000,
	SYSTEMSERVICE_BIOSAPI					= 1100,
	
	SYSTEMSERVICE_SETNUMPROC				= 1200,
	SYSTEMSERVICE_NETCFG						= 1300,

	SYSTEMSERVICE_ENV_VARS					= 1400, // Environment Variables

	SYSTEMSERVICE_LICENSE					= 1500,
	SYSTEMSERVICE_DEFAULTPWD_ENCRYPTED	= 1510, // use LsaStorePrivateData to store AutoAdminLogon password (pwd in ADS data is encrypted when ioffs == 1)

	SYSTEMSERVICE_CREATE_GUID				= 1600,
	SYSTEMSERVICE_VIRTUALMP					= 1700,
};

///////////////////////////////////////////////////////////////////////////////
enum nSystemConrolOffsets
{
	SYS_CONTROL_STARTUPSTATE				= 1,
	SYS_CONTROL_REGISTEREDUSER				= 2,
	SYS_CONTROL_REGISTEREDCOMPANY			= 3,
	SYS_CONTROL_REGISTEREDSERIAL			= 4,
	SYS_CONTROL_TIMELIMIT_STRING			= 5,
	SYS_CONTROL_LEVEL							= 6,
	SYS_CONTROL_IS_TCADMIN					= 7,
	SYS_CONTROL_OSVERSIONINFO				= 8,
	SYS_CONTROL_IS_TCADMIN_AES				= 9,
	SYS_CONTROL_HKLM_NATIVE_HIVE			= 10,	// for iGrp SYSTEMSERVICE_REG_xxx to access 64 registry on 64 systems, if not set KEY_WOW64_32KEY added
	SYS_CONTROL_KEY_WOW64_32KEY			= 11
};

///////////////////////////////////////////////////////////////////////////////
enum nTimeServiceOffsets
{
	TIMESERVICE_DATEANDTIME					= 1,
	TIMESERVICE_SYSTEMTIMES					= 2,
	TIMESERVICE_RTCTIMEDIFF					= 3,
	TIMESERVICE_ADJUSTTIMETORTC			= 4,
	TIMESERVICE_DATEANDTIME_100NS			= 5,
	TIMESERVICE_TIMEZONEINFO				= 6,
	TIMESERVICE_DATEANDTIME_GMT			= 7
};

///////////////////////////////////////////////////////////////////////////////
enum nUdpAccessPwdOffsets
{
	UDP_ACCESS_PWD_READONLY					= 1,
	UDP_ACCESS_PWD_WRITEACCESS				= 2,
	UDP_ACCESS_PWD_ALLACCESS				= 3,
};

///////////////////////////////////////////////////////////////////////////////
enum nSystemServiceOpenFile
{
	SYSTEMSERVICE_OPENGENERIC		= 1,
	SYSTEMSERVICE_OPENBOOTPRJ		= 2,
	SYSTEMSERVICE_OPENBOOTDATA		= 3,
	SYSTEMSERVICE_OPENBOOTPATH		= 4,
	SYSTEMSERVICE_OPENTARGETPATH	= 5,
	SYSTEMSERVICE_OPENCONFIGPATH	= 6,
	SYSTEMSERVICE_OPENTC3PATH		= 7,
	SYSTEMSERVICE_OPENTC3REPOSITORY	= 8,
	SYSTEMSERVICE_OPENUSERPATH1	= 11,
	SYSTEMSERVICE_OPENUSERPATH2	= 12,
	SYSTEMSERVICE_OPENUSERPATH3	= 13,
	SYSTEMSERVICE_OPENUSERPATH4	= 14,
	SYSTEMSERVICE_OPENUSERPATH5	= 15,
	SYSTEMSERVICE_OPENUSERPATH6	= 16,
	SYSTEMSERVICE_OPENUSERPATH7	= 17,
	SYSTEMSERVICE_OPENUSERPATH8	= 18,
	SYSTEMSERVICE_OPENUSERPATH9	= 19
};

///////////////////////////////////////////////////////////////////////////////
enum nTargetInfoOffsets
{
	COMPATGLITCH_LOADTPSSTATE		= 0,	// used for backward compatibility to TC 2.8
	TARGETINFO_QUERYXMLINFO			= 1,
	TARGETINFO_TARGETTYPE			= 2,
	TARGETINFO_FILEVERSION			= 3,
	TARGETINFO_PLATFORM				= 4,	// string like "TwinCAT RT (x86)"
	TARGETINFO_PROJECTGUID			= 5,	// cbRead >= 32 returns projectGuid + projectVersionGuid
	TARGETINFO_PROJECTVERSIONGUID	= 6,	// 
	TARGETINFO_PROJECTNAME			= 7,	// 
	TARGETINFO_QUERYXMLINFOVERB	= 8,
	TARGETINFO_SELFSIGNEDCERTFP	= 9,
	TARGETINFO_IS_UM_RUNTIME		= 10
};

enum nEnvVarsOffsets
{
	ENVVARS_GET_ALL = 0,						// Get All Variables (Read)
	ENVVARS_GET_TWINCAT = 1,				// Get TwinCAT Extension of Variables (Read)
	ENVVARS_GET_SHELL = 2,					// Get Process / Shell Variables (Read)

	ENVVARS_EXPAND_STRING = 3,				// Expand Environment String (ReadWrite)
};

enum nLicenseServiceOffsets
{
	LICENSESERVICE_CACHELICENSES = 1
};

///////////////////////////////////////////////////////////////////////////////
enum nTargetType
{
	TARGETTYPE_UNKNOWN				= 0,
	TARGETTYPE_PC						= 1,
	TARGETTYPE_CX						= 2,
	TARGETTYPE_BX						= 3,	
	TARGETTYPE_BCXX50					= 4,
};

///////////////////////////////////////////////////////////////////////////////
enum nIpHelperApiOffsets
{
	IPHELPERAPI_ADAPTERSINFO					= 1,
	IPHELPERAPI_BESTINTERFACE					= 2,
	IPHELPERAPI_NETIDBYHOSTNAME				= 3,
	IPHELPERAPI_IPADDRBYHOSTNAME				= 4,
	IPHELPERAPI_SENDARP							= 5,
	IPHELPERAPI_IPADDRTABLE						= 6,
	IPHELPERAPI_IPADDRBYADAPTERNAME			= 7,
	IPHELPERAPI_IPADDRBYADAPTERNAMEWCHAR	= 8,
	IPHELPERAPI_GETIPFORWARDTABLE				= 9,
	IPHELPERAPI_SETIPFORWARDENTRY				= 10,
	IPHELPERAPI_DELETEIPFORWARDENTRY			= 11,
	IPHELPERAPI_ADDIPADDRESS					= 12,
	IPHELPERAPI_SETIPADDRESS					= 13
};

///////////////////////////////////////////////////////////////////////////////
enum nHashedBootDataOffsets
{
	HASHED_BOOTDATA_READ = 1,
	HASHED_BOOTDATA_WRITE = 2,
	HASHED_BOOTDATA_SIZE = 3,
};

///////////////////////////////////////////////////////////////////////////////
enum nVirtualMpOffsets
{
	VIRTUALMP_CREATE = 0,
	VIRTUALMP_SET_INSTANCE_ID = 1,
};

enum nNetCfgOffsets
{
	SYSTEMSERVICE_NETCFG_FIND_ADAPTER_BY_DEVICE_NAME	= 1,
	SYSTEMSERVICE_NETCFG_FIND_ADAPTER_BY_FRIENDLY_NAME = 2,
};

///////////////////////////////////////////////////////////////////////////////
// Common Storage Management Interface
enum nCsmiOffsets
{
	ADS_GET_RAID_CONFIG		= 1,
	CSMI_ENUM_CNTLRS			= 11,
	CSMI_OPEN_CNTLR			= 12,
	CSMI_DRIVER_INFO			= 13,
	CSMI_GET_CNTLR_CONFIG	= 14,
	CSMI_GET_CNTLR_STATUS	= 15,
	CSMI_GET_RAID_INFO		= 16,
	CSMI_GET_RAID_CONFIG		= 17,
	CSMI_GET_PHY_INFO			= 18,
	CSMI_GET_SATA_SIGNATURE	= 19
};

typedef struct _AdsCsmiDriveStatus
{
	USHORT	uDriveStatus;
	USHORT	uDriveUsage;
	CHAR		uDriveSASAddr[8];
	CHAR		uDriveSerial[40];
}AdsCsmiDriveStatus, *PAdsCsmiDriveStatus;

typedef struct _AdsCsmiGetRaidConfigReq
{
	ULONG		nControllerId;
	ULONG		nRaidSetIndex;
}AdsCsmiGetRaidConfigReq, *PAdsCsmiGetRaidConfigReq;

typedef struct _AdsCsmiGetRaidStatusRes
{
	ULONG		uRaidSetIndex;
	USHORT	uRaidType;
	USHORT	uRaidStatus;
	USHORT	uDriveCount;
	BYTE		uInformation;
	BYTE		uReserved;
	AdsCsmiDriveStatus	drive[1];
}AdsCsmiGetRaidConfigRes, *PAdsCsmiGetRaidConfigRes;

typedef struct _AdsCsmiEnumControllersRes
{
	ULONG		uCntlCount;
	ULONG		uCntlIds[1];
}AdsCsmiEnumControllersRes, *PAdsCsmiEnumControllersRes;

enum SYSTEMSERVICE_PLATFORM
{
	SYSTEMSERVICE_PLATFORM_X86		= 0,
	SYSTEMSERVICE_PLATFORM_X64		= 1,
	SYSTEMSERVICE_PLATFORM_ARM		= 2,	// v7
	SYSTEMSERVICE_PLATFORM_ARMT2	= 3,	// Thumb2
};

enum SYSTEMSERVICE_OSTYPE
{
	SYSTEMSERVICE_OSTYPE_XP			= 0,
	SYSTEMSERVICE_OSTYPE_CE			= 1,
	SYSTEMSERVICE_OSTYPE_UM			= 2,
	SYSTEMSERVICE_OSTYPE_TC			= 3,
};

typedef struct _AdsSysServState
{
	USHORT	adsState;
	USHORT	deviceState;
	USHORT	restartIndex;
	BYTE		version;
	BYTE		revision;
	USHORT	build;
	BYTE		platform;
	BYTE		osType;
	union
	{
		struct
		{
			USHORT configModeOnly : 1;
			USHORT routerModeOnly : 1;
		};
		USHORT flags;
	};
	USHORT	reserved;
} AdsSysServState, *PAdsSysServState;
#define ACTIVATEROUTERFLAG_CONFIGMODEONLY	0x01
#define ACTIVATEROUTERFLAG_ROUTERMODEONLY	0x02

typedef struct _AdsAddInitCommand
{
	ULONG		initNo;
	AmsAddr	addr;
	ULONG		indexGroup;
	ULONG		indexOffset;
	ULONG		timeout;
	USHORT	keyLength;	// excl. terminating '\0'
	USHORT	msgLength;	// excl. terminating '\0'
	USHORT	dataLength;
	USHORT	reserved[5];
	// CHAR	key[];
	// CHAR	msg[];
	// BYTE	data[];
} AdsAddInitCommand, *PAdsAddInitCommand;

#define	SIZEOF_AdsAddInitCommand(p)	(sizeof(AdsAddInitCommand)+((PAdsAddInitCommand)p)->keyLength+1+((PAdsAddInitCommand)p)->msgLength+1+((PAdsAddInitCommand)p)->dataLength)
#define	PADSADDINITCMD_KEY(p)			((PCHAR)(((PAdsAddInitCommand)p)+1))
#define	PADSADDINITCMD_MSG(p)			(((PCHAR)(((PAdsAddInitCommand)p)+1))+((PAdsAddInitCommand)p)->keyLength+1)
#define	PADSADDINITCMD_DATA(p)			(((PBYTE)(((PAdsAddInitCommand)p)+1))+((PAdsAddInitCommand)p)->keyLength+1+((PAdsAddInitCommand)p)->msgLength+1)

///////////////////////////////////////////////////////////////////////////////
#define	SYSTEMSERVICE_REG_ENUMVALUE_MASK	0xC0000000

#define	SYSTEMSERVICE_REG_ENUMVALUE_V		0x80000000
#define	SYSTEMSERVICE_REG_ENUMVALUE_VT	0x40000000
#define	SYSTEMSERVICE_REG_ENUMVALUE_VTD	0xC0000000

///////////////////////////////////////////////////////////////////////////////
typedef struct TFOPEN_INDEXOFFS
{
	union
	{
		struct
		{
			ULONG		modeRead					: 1;
			ULONG		modeWrite				: 1;
			ULONG		modeAppend				: 1;
			ULONG		modePlus					: 1;
			ULONG		modeBinary				: 1;
			ULONG		modeText					: 1;
			ULONG		ensureDirectory		: 1;
			ULONG		enableDirectory		: 1;
			ULONG		overwrite				: 1;
			ULONG		overwriteAndRename	: 1;
			ULONG		modeExtractTmpZip		: 1;
			ULONG		forceCloseIfOpen		: 1;
			ULONG		reserved					: 4;
			ULONG		openPath					: 16;
		};
		ULONG		all;
	};
} FOPEN_INDEXOFFS;

typedef struct TFSEEK_STRUCT
{
	LONG	seekPos;
	LONG	seekOrigin;
} FSEEK_STRUCT;

#define	SYSTEMSERVICE_FIRSTUSERPATH	SYSTEMSERVICE_OPENUSERPATH1
#define	SYSTEMSERVICE_LASTUSERPATH		SYSTEMSERVICE_OPENUSERPATH9

#define	TWINCATBOOTPRJEXT_A			"bootprj"
#define	TWINCATBOOTPRJEXTOLD_A		"bootprj-old"
#define	TWINCATBOOTDATAEXT_A			"bootdata"
#define	TWINCATBOOTDATAEXTOLD_A		"bootdata-old"
#define	TWINCATBOOTRUNMODEFILE_A	"CurrentConfig.xml"
#define	TWINCATBOOTEVENTMSGFILE_A	"CurrentEventMessages.xml"
#define	TWINCATBOOTCFGMODEFILE_A	"DefaultConfig.xml"

#define	TWINCATBOOTPRJEXT_W			L"bootprj"
#define	TWINCATBOOTPRJEXTOLD_W		L"bootprj-old"
#define	TWINCATBOOTDATAEXT_W			L"bootdata"
#define	TWINCATBOOTDATAEXTOLD_W		L"bootdata-old"
#define	TWINCATBOOTRUNMODEFILE_W	L"CurrentConfig.xml"
#define	TWINCATBOOTEVENTMSGFILE_W	L"CurrentEventMessages.xml"
#define	TWINCATBOOTCFGMODEFILE_W	L"DefaultConfig.xml"

#ifndef _UNICODE
#define	TWINCATBOOTPRJEXT				TWINCATBOOTPRJEXT_A			
#define	TWINCATBOOTPRJEXTOLD			TWINCATBOOTPRJEXTOLD_A		
#define	TWINCATBOOTDATAEXT			TWINCATBOOTDATAEXT_A			
#define	TWINCATBOOTDATAEXTOLD		TWINCATBOOTDATAEXTOLD_A		
#define	TWINCATBOOTRUNMODEFILE		TWINCATBOOTRUNMODEFILE_A	
#define	TWINCATBOOTEVENTMSGFILE		TWINCATBOOTEVENTMSGFILE_A
#define	TWINCATBOOTCFGMODEFILE		TWINCATBOOTCFGMODEFILE_A	
#else
#define	TWINCATBOOTPRJEXT				TWINCATBOOTPRJEXT_W			
#define	TWINCATBOOTPRJEXTOLD			TWINCATBOOTPRJEXTOLD_W		
#define	TWINCATBOOTDATAEXT			TWINCATBOOTDATAEXT_W			
#define	TWINCATBOOTDATAEXTOLD		TWINCATBOOTDATAEXTOLD_W		
#define	TWINCATBOOTRUNMODEFILE		TWINCATBOOTRUNMODEFILE_W	
#define	TWINCATBOOTEVENTMSGFILE		TWINCATBOOTEVENTMSGFILE_W
#define	TWINCATBOOTCFGMODEFILE		TWINCATBOOTCFGMODEFILE_W	
#endif

///////////////////////////////////////////////////////////////////////////////
#define	SERVICE_CONTROL_USER				128

#define	TCATSYS_USERSHELLACTIVATED		SERVICE_CONTROL_USER+1
#define	TCATSYS_USERLOGGEDOFF			SERVICE_CONTROL_USER+2
#define	TCATSYS_SYSTEMRESTART			SERVICE_CONTROL_USER+3
#define	TCATSYS_SYSTEMSTART				SERVICE_CONTROL_USER+4
#define	TCATSYS_SYSTEMSTOP				SERVICE_CONTROL_USER+5
#define	TCATSYS_IORESET					SERVICE_CONTROL_USER+6
#define	TCATSYS_SYSTEMSTARTED			SERVICE_CONTROL_USER+7
#define	TCATSYS_POWERFAIL					SERVICE_CONTROL_USER+8
#define	TCATSYS_SYSTEMCONFIG				SERVICE_CONTROL_USER+9
#define	TCATSYS_SYSTEMRECONFIG			SERVICE_CONTROL_USER+10
#define	TCATSYS_SYSUIATTACH				SERVICE_CONTROL_USER+11
#define	TCATSYS_SYSUIDETACH				SERVICE_CONTROL_USER+12
#define	TCATSYS_OS_SHUTDOWN				SERVICE_CONTROL_USER+13
#define	TCATSYS_OS_REBOOT					SERVICE_CONTROL_USER+14

///////////////////////////////////////////////////////////////////////////////
#ifndef CREATE_NEW
	#define CREATE_NEW          1
	#define CREATE_ALWAYS       2
	#define OPEN_EXISTING       3
	#define OPEN_ALWAYS         4
	#define TRUNCATE_EXISTING   5
#endif
///////////////////////////////////////////////////////////////////////////////
typedef struct TAdsWin32CreateFile
{
	DWORD	dwDesiredAccess;			// access (read-write) mode 
	DWORD	dwShareMode;				// share mode 
	DWORD	dwCreationDistribution; // how to create 
	DWORD	dwFlagsAndAttributes;	// file attributes 
	DWORD hTemplateFile;			// handle to file with attributes to copy (not supported, must be zero)
	ULONG	cbNameSize;					//	sizeof filename
	CHAR	sFileName[ANYSIZE_ARRAY];// filename
} AdsWin32CreateFile, *PAdsWin32CreateFile;

typedef struct TAdsWin32LaunchProcess			// LOWORD(indexOffset) == timeout (0== no wait) 
{															// indexOffset bit 16 == SW_HIDE
	ULONG cbProcessPath;
	ULONG cbDirectoryName;
	ULONG cbCommandLine;
	CHAR	szData[ANYSIZE_ARRAY];
} AdsWin32LaunchProcess, *PAdsWin32LaunchProcess;

#define	SIZEOF_AdsWin32LaunchProcess(p)	(offsetof(AdsWin32LaunchProcess, szData)+((PAdsWin32LaunchProcess)p)->cbProcessPath+((PAdsWin32LaunchProcess)p)->cbDirectoryName+((PAdsWin32LaunchProcess)p)->cbCommandLine+3)

#define	ADSWIN32LAUNCHPROCESS_TIMEOUT_MASK		0x0000ffff
#define	ADSWIN32LAUNCHPROCESS_SW_HIDE				0x00010000

///////////////////////////////////////////////////////////////////////////////
//
#define	ADSSYSADDREMOTEFLAG_TEMPORARY		0x00000001
#define	ADSSYSADDREMOTEFLAG_DYNAMIC		0x00000002	// hostname instead of IP address
#define	ADSSYSADDREMOTEFLAG_NOOVERRIDE	0x00000004	
#define	ADSSYSADDREMOTEFLAG_TLS				0x00000008
#define	ADSSYSADDREMOTEFLAG_OWNFILE		0x00000010
#define	ADSSYSADDREMOTEFLAG_IPADDR			0x00000020	// use ip address instead of hostname
#define	ADSSYSADDREMOTEFLAG_FROM_UDP_DISCO	0x00000040	// AddRemoteComputer() called from UDP Discovery - do not call VerifyConnected (no ADS secure)
#define	ADSSYSADDREMOTEFLAG_UNIDIRECTIONAL	0x00000080	// only allow Ads Responses, Notification Requests and ReadState Requests
#define	ADSSYSADDREMOTEFLAG_REMOTENETID	0x00000100	// for AmsNAT

#define	ADSSYSADDREMOTEFLAG_INTERNAL		(ADSSYSADDREMOTEFLAG_TLS|ADSSYSADDREMOTEFLAG_OWNFILE|ADSSYSADDREMOTEFLAG_REMOTENETID)

typedef struct TAdsSysAddNetId
{
	AmsNetId	netId;
	USHORT	reserved[5];
	DWORD		dwFlags;
	ULONG		cbName;						// incl. \0
//	char		szName[];
} AdsSysAddNetId, *PAdsSysAddNetId;

#define	ADSSYSADDREMOTETLSFLAG_CASESENSITIVE	0x00000001
#define	ADSSYSADDREMOTETLSFLAG_USERPWD			0x00000002	// if set szIdentity == username
#define	ADSSYSADDREMOTETLSFLAG_SERVERINFO		0x00000004	// save only serverinfo (e.g. fingerprint but not IP address of peer)
#define	ADSSYSADDREMOTETLSFLAG_TYPE_MASK			0x00000030	// 
#define	ADSSYSADDREMOTETLSFLAG_SSC					0x00000010	//	self signed certificate
#define	ADSSYSADDREMOTETLSFLAG_PSK					0x00000020	// preshared key
#define	ADSSYSADDREMOTETLSFLAG_SCA					0x00000030	// shared CA
#define	ADSSYSADDREMOTETLSFLAG_IGNORECN			0x00000040	// ignore common name
#define	ADSSYSADDREMOTETLSFLAG_TYPE(f)			((f)&ADSSYSADDREMOTETLSFLAG_TYPE_MASK)
#define	ADSSYSADDREMOTETLSFLAG_ISTYPE(f, t)		(ADSSYSADDREMOTETLSFLAG_TYPE(f)==(t))
typedef struct TAdsSysAddRemoteTls
{
	DWORD					dwFlags;
	USHORT				cbStart;
	USHORT				cbIdentity;		// incl. \0
	USHORT				cbPwd;			// incl. \0
	USHORT				reserved;		
	USHORT				cbKey;
	USHORT				cbHost;			// incl. \0
//	char					szIdentity[];
//	char					szPwd[];
//	BYTE					key[];
//	char					szHost[];
} AdsSysAddRemoteTls, *PAdsSysAddRemoteTls;
#define	SIZOF_AdsSysAddNetIdHead(p)		(sizeof(AdsSysAddRemoteTls))
#define	SIZOF_AdsSysAddNetIdData(p)		(p->cbStart + p->cbIdentity + p->cbPwd + p->cbKey)
#define	SIZOF_AdsSysAddNetId(p)				(SIZOF_AdsSysAddNetIdHead(p) + SIZOF_AdsSysAddNetIdData(p))


typedef struct TAdsSysAddRemote
{
	AmsNetId				netId;
	USHORT				nTransType;
	DWORD					dwFlags;
	ULONG					nTimeout;
	ULONG					nMaxFragment;
	ULONG					reserved[3];
	ULONG					cbAddress;		// incl. \0
	ULONG					cbName;			// incl. \0
	ULONG					cbAddNetIds;
//	char					address[];
//	char					szName[];
//	AdsSysAddNetId		addNetIds[];
//	AdsSysAddRemoteTls tls;				// if ADSSYSADDREMOTEFLAG_TLS set
//	AmsNetId				remoteNetId;	// if ADSSYSADDREMOTEFLAG_REMOTENETID set -> for AmsNAT
} AdsSysAddRemote, *PAdsSysAddRemote;

typedef struct TAdsIpAddrInfo
{
	DWORD					bEnableDhcp;
	DWORD					bEnableAutoDNS;
	ULONG					cbAdapterName;
	ULONG					cbAddress;		// incl. \0
	ULONG					cbSubNet;		// incl. \0
	ULONG					cbDefGateway;
	ULONG					cbPriDns;
	ULONG					cbSecDns;
//	char					szAdapter[];
//	char					szAddr[];
//	char					szSubNet[];
//	char					szDefGetway[];
//	char					szPriDns[];
//	char					szSecDns[];
} AdsIpAddrInfo, *PAdsIpAddrInfo;

typedef struct TAdsScreenRes
{
	DWORD					dwColorDepth; // 0 => don't care
	ULONG					cbScreenRes;
//	char					szScreenRes[];
} AdsScreenRes, *PAdsScreenRes;

typedef struct TAdsScreenResModes
{
	ULONG	cbResolutions; 
	ULONG	cbPacketSize;
} AdsScreenResModes, *PAdsScreenResModes;

#if !defined(IS_R0) && !defined(TC_ENVIRONMENT_OS)
typedef struct TAdsFileFindData
{
	ULONG handle;
	WIN32_FIND_DATAA data;
} AdsFileFindData, *PAdsFileFindData;
#endif

typedef struct TAdsFileStatus
{
	union
	{
		ULONGLONG	ulFileSize;
		struct
		{
			ULONG	ulFileSizeLow;
			ULONG	ulFileSizeHigh;
		};
	};
	ULONGLONG	ulCreateTime;
	ULONGLONG	ulModifiedTime;
	ULONGLONG	ulReadTime;
	DWORD			dwAttribute;
} AdsFileStatus, *PAdsFileStatus;

////////////////////////////////////////////////////////////////////////////////
// EMail Service
typedef struct TAdsSendEMailEntry
{
	ULONG			entryLength;	// length of complete email entry
	USHORT		addrLength;		// length of addr name (excl. \0)
	// ADS_INT8		addr[];			// name of symbol with terminating \0
	// ADS_UINT16	subjectLength;	// length of subject (excl. \0)
	// ADS_INT8		subject[];		// subject with terminating \0
	// ADS_UINT16	textLength;		// length of text (excl. \0)
	// ADS_INT8		text[];			// text with terminating \0
	// ADS_UINT16	attachLength;	// attach file path (excl. \0)
	// ADS_INT8		attach[];		// attach file path with terminating \0
} AdsSendEMailEntry, *PAdsSendEMailEntry;

#define	PADSEMAILADDR(pEntry)			((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))
#define	PADSEMAILSUBJECT(pEntry)		(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1+sizeof(USHORT)) )
#define	PADSEMAILSUBJECTLEN(pEntry)	*(PUSHORT)(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1) )
#define	PADSEMAILTEXT(pEntry)			(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILSUBJECT(pEntry)-sizeof(USHORT))+1+sizeof(USHORT) ))
#define	PADSEMAILTEXTLEN(pEntry)		*(PUSHORT)(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILSUBJECT(pEntry)-sizeof(USHORT))+1))
#define	PADSEMAILATTACH(pEntry)			(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILSUBJECT(pEntry)-sizeof(USHORT))+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILTEXT(pEntry)-sizeof(USHORT))+1+sizeof(USHORT) ))
#define	PADSEMAILATTACHLEN(pEntry)		*(PUSHORT)(((PCHAR)(((PAdsSendEMailEntry)pEntry)+1))+\
														(((PAdsSendEMailEntry)pEntry)->addrLength+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILSUBJECT(pEntry)-sizeof(USHORT))+1+sizeof(USHORT)+\
														*(ADS_UINT16*)(PADSEMAILTEXT(pEntry)-sizeof(USHORT))+1 ))


////////////////////////////////////////////////////////////////////////////////
// XMLWriter Service
typedef struct TAdsXMLEntry
{
	ULONG			entryLength;	// length of complete entry
	ULONG			dataType;		// adsDataType of value
	USHORT		nameLength;		// length of name (excl. \0)
	USHORT		valueLength;	// length of the value
	// ADS_INT8		name[];		// name of entry with terminating \0	
	// ADS_UINT8	value[];		// value of entry
}	AdsXMLEntry, *PAdsXMLEntry;

#define	PADSXMLNAME(pEntry)			((PCHAR)(((PAdsXMLEntry)pEntry)+1))
#define	PADSXMLVALUE(pEntry)			((PBYTE)(((PAdsXMLEntry)pEntry)+1)+\
													((PAdsXMLEntry)pEntry)->nameLength+1 )

#pragma pack( pop )

typedef struct TAdsTimeZoneInfo
{
	LONG Bias;
	CHAR StandardName[ 32 ];
	SYSTEMTIME StandardDate;
	LONG StandardBias;
	CHAR DaylightName[ 32 ];
	SYSTEMTIME DaylightDate;
	LONG DaylightBias;
	DWORD	dwOperationRange;
} AdsTimeZoneInfo, *PAdsTimeZoneInfo; 


typedef struct TAdsAddIpAddressIn
{
	ULONG		ipAddr;
	ULONG		ipMask;
	DWORD		dwIndex;
} AdsAddIpAddressIn, *PAdsAddIpAddressIn; 

typedef struct TAdsAddIpAddressOut
{
	ULONG nteContext;
	ULONG nteIndex;
} AdsAddIpAddressOut, *PAdsAddIpAddressOut;

typedef struct TAdsIpData
{
	BYTE	bDHCPEnabled;
	BYTE	reserved[3];
	union 
	{
		struct 
		{
			BYTE  ipAdd[4];
			BYTE	subAdd[4];
			BYTE	gateAdd[4];
		} seg;
		BYTE	bytes[12];
	} data;
} AdsIpData, *PAdsIpData;

typedef struct TAdsSetIpAddress
{
	AdsIpData	ipDataNew;
	AdsIpData	ipDataOld;
	BYTE			adapterMac[6];
} AdsSetIpAddress, *PAdsSetIpAddress; 

//SYSTEMSERVICE_NETCFG
typedef struct _NetCfgAdapterInfo
{
	ULONG						cbLength;
	ULONG						nDisplayNameLength;				// (excl. \0)
	ULONG						nIdLength;							// (excl. \0)	
	ULONG						nFriendlyNameLength;				// (excl. \0)	
	ULONG						nStatus;
	LONG						nResult;
	BOOL						bTcEtherEnabled;	
	BOOL						bTcRteImEnabled;		
	BOOL						bTcEtherBindingPath;
	BOOL						bTcRteImBindingPath;
	BOOL						bTcMiniport;
	BOOL						bCompatible;
	GUID						guidInstance;
	//WCHAR[]					pwszDisplayName;	with terminating \0
	//WCHAR[]					pwszId;				with terminating \0
	//WCHAR[]					pwszFriednlyName  with terminating \0
}NetCfgAdapterInfo, *PNetCfgAdapterInfo;
#define	NETCFG_ADAPTERINFO_DISPNAME(pEntry)				((PWCHAR)(((PNetCfgAdapterInfo)pEntry)+1))
#define	NETCFG_ADAPTERINFO_ID(pEntry)						( (PWCHAR)((PBYTE)(((PNetCfgAdapterInfo)pEntry)+1)+\
																		(((PNetCfgAdapterInfo)pEntry)->nDisplayNameLength+1)*sizeof(WCHAR)) )
#define	NETCFG_ADAPTERINFO_FRIENDLYNAME(pEntry)			( (PWCHAR)((PBYTE)(((PNetCfgAdapterInfo)pEntry)+1)+\
																		(((PNetCfgAdapterInfo)pEntry)->nDisplayNameLength+1)*sizeof(WCHAR)+\
																		(((PNetCfgAdapterInfo)pEntry)->nIdLength+1)*sizeof(WCHAR)) )

typedef struct _EnvVarsInfo
{
	ULONG cbLength;
	//x	WCHAR[] pwszEnvironment; // with terminating \0
}EnvVarsInfo, *PEnvVarsInfo;
#define ENVVARS_INFO_ENVIRONMENT_STRING(pEntry) ((PWCHAR)(((PEnvVarsInfo)pEntry)+1))

////////////////////////////////////////////////////////////////////////////////
// License Service
typedef struct
{
	AmsAddr	addr;
	ULONG		timeout;
	ULONG		coeChannel;
	BOOL		bForceRefresh;
} LicenseCacheInfo, *PLicenseCacheInfo;

