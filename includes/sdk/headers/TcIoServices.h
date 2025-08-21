///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"

#define	FCXXXX_INFODATA_SUPPORT
#ifdef _DEBUG
//#define	BUFFERED_MAPPING_SUPPORT
#endif

#define TC3_TASKS

const		ULONG		DrvID_TcIo							= 0x03000000;

// class ids
TCOM_DECL_CLASS(CID_TCIO_CTRL, DrvID_TcIo | 0x0000)
TCOM_DECL_CLASS(CID_TcIoTask, DrvID_TcIo | 0x0011)
TCOM_DECL_CLASS(CID_TcIoIdleTask, DrvID_TcIo | 0x0012)
TCOM_DECL_CLASS(CID_TcIoAdiImage, DrvID_TcIo | 0x0021)
TCOM_DECL_CLASS(CID_TcAdi, DrvID_TcIo | 0x0022)
TCOM_DECL_CLASS(CID_TcPlcAdi, DrvID_TcIo | 0x0023)
TCOM_DECL_CLASS(CID_TcAdiLegacyDev, DrvID_TcIo | 0x0024)
TCOM_DECL_CLASS(CID_TcAdsImagePort, DrvID_TcIo | 0x0025)
TCOM_DECL_CLASS(CID_TcIoSlaveImage, DrvID_TcIo | 0x0026)
TCOM_DECL_CLASS(CID_TcIoMasterImage, DrvID_TcIo | 0x0027)
TCOM_DECL_CLASS(CID_TcIoMasterSyncImage, DrvID_TcIo | 0x0028)
#ifdef	BUFFERED_MAPPING_SUPPORT
TCOM_DECL_CLASS(CID_TcAdiBuffered, DrvID_TcIo | 0x0029)
#endif
TCOM_DECL_CLASS(CID_TcChildDataAreaOwner, DrvID_TcIo | 0x002A)
TCOM_DECL_CLASS(CID_TcIoAddSync, DrvID_TcIo | 0x0041)
TCOM_DECL_CLASS(CID_TcIoAddASync, DrvID_TcIo | 0x0042)
TCOM_DECL_CLASS(CID_TcIoECatMAppBaseAdiHelper, DrvID_TcIo | 0x0060)

// interface ids
TCOM_DECL_INTERFACE("03000000-0000-0000-e000-000000000064", ITComIo)
TCOM_DECL_INTERFACE("03000010-0000-0000-e000-000000000064", ITcCyclic)
TCOM_DECL_INTERFACE("03000011-0000-0000-e000-000000000064", ITcIoCyclic)
TCOM_DECL_INTERFACE("03000012-0000-0000-e000-000000000064", ITcADI)
TCOM_DECL_INTERFACE("03000013-0000-0000-e000-000000000064", ITcADILegacy)
TCOM_DECL_INTERFACE("03000015-0000-0000-e000-000000000064", ITcADIGlobalOffsets)
TCOM_DECL_INTERFACE("03000016-0000-0000-e000-000000000064", ITcADIState)
TCOM_DECL_INTERFACE("03000017-0000-0000-e000-000000000064", ITcPreInputCyclic)
TCOM_DECL_INTERFACE("03000018-0000-0000-e000-000000000064", ITcWatchSource)
TCOM_DECL_INTERFACE("03000019-0000-0000-e000-000000000064", ITcIoLegacyDevice)
TCOM_DECL_INTERFACE("0300001C-0000-0000-e000-000000000064", ITcIoLegacyEthernetDevice)
TCOM_DECL_INTERFACE("0300001D-0000-0000-e000-000000000064", ITcIoDevice)
TCOM_DECL_INTERFACE("0300001E-0000-0000-e000-000000000064", ITcCyclicCaller)
TCOM_DECL_INTERFACE("0300001F-0000-0000-e000-000000000064", ITcIoCyclicCaller)
TCOM_DECL_INTERFACE("03000020-0000-0000-e000-000000000064", ITcPciDevice)
TCOM_DECL_INTERFACE("03000021-0000-0000-e000-000000000064", ITcIoCyclicDivModCaller)
TCOM_DECL_INTERFACE("03000022-0000-0000-e000-000000000064", ITcADIAccess)
TCOM_DECL_INTERFACE("03000023-0000-0000-e000-000000000064", ITComOcMapping)
TCOM_DECL_INTERFACE("03000024-0000-0000-e000-000000000064", ITcIoCyclicNeedUpdate)
TCOM_DECL_INTERFACE("03000025-0000-0000-e000-000000000064", ITcPostCyclic)
TCOM_DECL_INTERFACE("03000026-0000-0000-e000-000000000064", ITcPostCyclicCaller)
TCOM_DECL_INTERFACE("03000027-0000-0000-e000-000000000064", ITcADISymbolic)
TCOM_DECL_INTERFACE("03000028-0000-0000-e000-000000000064", ITComRetainMapping)
TCOM_DECL_INTERFACE("03000029-0000-0000-e000-000000000064", ITcFastCyclic)
TCOM_DECL_INTERFACE("0300002a-0000-0000-e000-000000000064", ITcFastCyclicCaller)
TCOM_DECL_INTERFACE("0300002b-0000-0000-e000-000000000064", ITComOcMapping2)
TCOM_DECL_INTERFACE("0300002c-0000-0000-e000-000000000064", ITcADISymbolLocation)
TCOM_DECL_INTERFACE("0300002d-0000-0000-e000-000000000064", ITComMappingStatus)
TCOM_DECL_INTERFACE("0300002e-0000-0000-e000-000000000064", ITcSymbolCyclicAccess)
TCOM_DECL_INTERFACE("0300002f-0000-0000-e000-000000000064", ITcAddRemoveAdditionalSymbols)
TCOM_DECL_INTERFACE("03000030-0000-0000-e000-000000000064", ITcDcTimeData)
TCOM_DECL_INTERFACE("03000031-0000-0000-e000-000000000064", ITcIoTimeCtrl)
TCOM_DECL_INTERFACE("03000032-0000-0000-e000-000000000064", ITcPreInputCyclicCaller)
TCOM_DECL_INTERFACE("03000033-0000-0000-e000-000000000064", ITcIoTimeMaster)
TCOM_DECL_INTERFACE("03000034-0000-0000-e000-000000000064", ITcIoTimeSlave)
TCOM_DECL_INTERFACE("03000035-0000-0000-e000-000000000064", ITcADISymbolLocation2)
TCOM_DECL_INTERFACE("03000036-0000-0000-e000-000000000064", ITcIoCyclicNeedUpdate2)
TCOM_DECL_INTERFACE("03000037-0000-0000-e000-000000000064", ITcIoImageOwner)

// object ids
const		OTCID		OID_TCIO_CTRL						= DrvID_TcIo | 0x0000;
const		OTCID		OID_TcIoIdleTask					= DrvID_TcIo | 0x0011;
const		OTCID		OID_TcIoIdleTaskConfigMode		= DrvID_TcIo | 0x0012;
const		OTCID		OID_TCIO_IOTASK_BEGIN			= DrvID_TcIo | 0x0100;
const		OTCID		OID_TCIO_IOTASK_END				= DrvID_TcIo | 0x01FF;

// category ids
const		CATTCID	CATID_TcIo_Device					= DrvID_TcIo | 0x0001;
const		CATTCID	CATID_TcIo_Box						= DrvID_TcIo | 0x0002;
const		CATTCID	CATID_TcIo_Module					= DrvID_TcIo | 0x0003;
const		CATTCID	CATID_TcIo_Image					= DrvID_TcIo | 0x0008;
const		CATTCID	CATID_TcIo_Mapping				= DrvID_TcIo | 0x0009;

const		CATTCID	CATID_TcIo_EtherCAT				= DrvID_TcIo | 0x0100;
const		CATTCID	CATID_TcIo_Profibus				= DrvID_TcIo | 0x0110;
const		CATTCID	CATID_TcIo_Profinet				= DrvID_TcIo | 0x0111;
const		CATTCID	CATID_TcIo_CANopen				= DrvID_TcIo | 0x0120;
const		CATTCID	CATID_TcIo_Devicenet				= DrvID_TcIo | 0x0121;

#define	ADI_I					0x00000000
#define	ADI_O					0x00000001
#define	ADI_RETAIN			0x00000007
#ifdef ETH_REDUNDANCY_HDL
#define	ADI_REDUNDANCY		0x00000008
#endif
#define	ADI_DPRAM			0xF0000000

#define	ADI_DEV_I			ADI_I
#define	ADI_DEV_O			ADI_O

#define	ADI_STATE_OK			0x0000
#define	ADI_STATE_I_PENDING	0x0001
#define	ADI_STATE_I_ERROR		0x8000

#define	ADI_STATE_O_PENDING	0x00010000
#define	ADI_STATE_O_NOTREADY	0x00020000
#define	ADI_STATE_O_ERROR		0x80000000

typedef struct TTcIoAdiInitData
{
	OTCID		oid;
	UINT		adi_x;
	UINT		offs;
	UINT		size;
} TcIoAdiInitData, *PTcIoAdiInitData;

typedef struct TTcIoDataAreaSize
{
	UINT		area;
	UINT		size;
} TcIoDataAreaSize, *PTcIoDataAreaSize;

typedef struct TTcIoDataAreaCfg
{
	UINT		pid;
	UINT		bitSize;
	UINT		bitOffs;
	UINT		reserved;
} TcIoDataAreaCfg, *PTcIoDataAreaCfg;

typedef struct TTcSubModuleConfig			// PID_SubModuleConfig
{
	GUID		subModule;				// moduleGuid
	OTCID		oid;
	UINT		reserved[11];
	CHAR		name[64];				// \0 terminated
	UINT		dataAreaOffs[16];		// up to 16 data areas
	UINT		dataAreaSize[16];
} TcSubModuleConfig, *PTcSubModuleConfig;

typedef struct TTcIoChildAreaLocation
{
	OTCID		oid;
	UINT		area;
	UINT		offs;
	UINT		size;
} TcIoChildAreaLocation, *PTcIoChildAreaLocation;

typedef struct TTcIoContextInfo
{
	UINT		contextId;
	UINT		cycleTime;	// in ns
	UINT		priority;
	OTCID		oidTask;
	UINT		reserved[12];
} TcIoContextInfo, *PTcIoContextInfo;

typedef struct TTcIoAdsOpenDevice
{
	ULONG		expectedBoxes;
	ULONG		openFlags;
} TcIoAdsOpenDevice, *PTcIoAdsOpenDevice;

typedef struct T_PlcAdi_InitData
{
	OTCID		oidApp;
	UINT		uiAreaId;
	UINT		uiByteOffset;
	UINT		uiSize;
}PlcAdi_InitData, *PPlcAdi_InitData;

typedef struct T_AdiLegacyDev_InitData
{
	OTCID		oidTask;
	OTCID		oidMapping;
	WORD		wImgOffsIn;
	WORD		wImgOffsOut;
	USHORT	nImgId;
	USHORT	nMapId;
}AdiLegacyDev_InitData, *PAdiLegacyDev_InitData;

typedef struct T_AddMap_InitData
{
	OTCID							oidAdiA;
	UINT							uiReserved;
	UINT							nAdisB;
// T_AddMap_ADI_InitData	adiInitData[nAdisB];
}AddMap_InitData, *PAddMap_InitData;
#define PAddMap_InitDataNEXTHDR(p) ((PAddMap_ADI_InitData)((PAddMap_InitData)p + 1))

typedef struct T_AddMap_Map_InitData
{
	UINT		uiAreaId;
	UINT		uiOffsAdiA;
	UINT		uiOffsAdiB;
	UINT		uiSize;
}AddMap_Map_InitData, *PAddMap_Map_InitData;

typedef struct T_AddMap_ADI_InitData
{
	OTCID							oidAdiB;
	UINT							nMapsBToA;
	UINT							nMapsAToB;
// T_AddMap_Map_InitData	mapToPlcInitData[nMapsBToA];
// T_AddMap_Map_InitData	mapFromPlcInitData[nMapsAToB];
}AddMap_ADI_InitData, *PAddMap_ADI_InitData;
#define PAddMap_ADI_InitDataDATA(p) ((PAddMap_Map_InitData)((PAddMap_ADI_InitData)p + 1))
#define PAddMap_ADI_InitDataNEXTHDR(p) ((PAddMap_ADI_InitData)((PBYTE)p + sizeof(AddMap_ADI_InitData )+ ((PAddMap_ADI_InitData)p)->nMapsBToA * sizeof(AddMap_Map_InitData) + ((PAddMap_ADI_InitData)p)->nMapsAToB * sizeof(AddMap_Map_InitData) ))

#pragma pack(push, 1)
typedef struct TIoAdsBoxInfoEntry
{
	USHORT	entryLength;
	USHORT	boxNo;
	USHORT	boxType;
	USHORT	fieldbusAddr;
	AmsAddr	amsAddr;
	USHORT	nameLength;
	USHORT	commentLength;
	// CHAR	name[];		// length of box name (excl. \0)
	// CHAR	comment[];	// length of box comment (excl. \0)
} IoAdsBoxInfoEntry, *PIoAdsBoxInfoEntry;
#define	IoAdsBoxInfoName(pBox)		(PCHAR)ENDOF((PIoAdsBoxInfoEntry)pBox)
#define	IoAdsBoxInfoComment(pBox)	((PCHAR)(ENDOF((PIoAdsBoxInfoEntry)pBox))+((PIoAdsBoxInfoEntry)pBox)->nameLength+1)
#define	IoAdsBoxInfoNextBox(pBox)	((PIoAdsBoxInfoEntry)((PBYTE)(ENDOF((PIoAdsBoxInfoEntry)pBox))+((PIoAdsBoxInfoEntry)pBox)->nameLength+1+((PIoAdsBoxInfoEntry)pBox)->commentLength+1))

#define	IoAdsDevInfoEntryVersion	1
typedef struct	TIoAdsDevInfoEntry
{
	ULONG		entryLength;
	USHORT	version;
	USHORT	devType;
	USHORT	devId;
	USHORT	boxCount;
	AmsAddr	amsAddr;
	USHORT	nameLength;
	USHORT	commentLength;
	// CHAR	name[];		// length of device name (excl. \0)
	// CHAR	comment[];	// length of device comment (excl. \0)
} IoAdsDevInfoEntry, *PIoAdsDevInfoEntry;
#define	IoAdsDevInfoName(pDev)		(PCHAR)ENDOF((PIoAdsDevInfoEntry)pDev)
#define	IoAdsDevInfoComment(pDev)	((PCHAR)(ENDOF((PIoAdsDevInfoEntry)pDev))+((PIoAdsDevInfoEntry)pDev)->nameLength+1)
#define	IoAdsDevInfoFirstBox(pDev)	((PIoAdsBoxInfoEntry)((PBYTE)(ENDOF((PIoAdsDevInfoEntry)pDev))+((PIoAdsDevInfoEntry)pDev)->nameLength+1+((PIoAdsDevInfoEntry)pDev)->commentLength+1))

typedef struct TIoEtherStatistic
{
	ULONG		timeStamp;
	BOOL		realtimeMode;
	ULONG		sendFrames;
	ULONG		recvFrames;
	ULONG		sendTimeRTime;
	ULONG		recvTimeRTime;
	ULONG		sendTimeNdis;
	ULONG		recvTimeNdis;
} IoEtherStatistic, *PIoEtherStatistic;

typedef struct TIoAdiAccess
{
	ULONG	adi_x;
	ULONG	size;
	ULONG	offs;
} IoAdiAccess, *PIoAdiAccess;

typedef struct TIoCreateAdi
{
	UINT			nIn;			// in Byte
	UINT			nOut;			// in Byte
	USHORT		addrType;
	USHORT		reserved1[3];
	OTCID			oidFrameAlloc;
	UINT			nInOffs;		// in Byte
	UINT			nOutOffs;	// in Byte
	UINT			reserved2;
} IoCreateAdi, *PIoCreateAdi;

#define	TCIODEVICENAME_MAXLENGTH	31
typedef struct TTcIoCreateAmsIoTpPort
{
	AmsNetId	netId;
	CHAR		name[TCIODEVICENAME_MAXLENGTH+1];
} TcIoCreateAmsIoTpPort, *PTcIoCreateAmsIoTpPort;

typedef struct TTcIoCreateAmsIoPort
{
	USHORT	port;
	USHORT	nBoxNo;
	USHORT	timeout;
	USHORT	nNetIds;
} TcIoCreateAmsIoPort, *PTcIoCreateAmsIoPort;

typedef struct _TcIoECatMAppBaseOidCfg
{
	OTCID		oidEcMaster;
	OTCID		oidECatAutoCfg;
	OTCID		oidTask;
	OTCID		oidIdleTask;
} TcIoECatMAppBaseOidCfg, *PTcIoECatMAppBaseOidCfg;

typedef struct _TcIoIpSettings
{
	ULONG					ipAddr;
	ULONG					subMask;
	ULONG					gateway;
	BYTE					dhcpEnable;
	BYTE					manualSettings;
	BYTE					dhcpAutoIpTimeOut; // 0 = disable | in sec | 255 = direct auto ip
	BYTE					reserved;
} TcIoIpSettings, *PTcIoIpSettings;

typedef struct _TcIoTimeMeasurment
{
	ULONG		cnt;
	ULONG		average;		// in ns
	ULONG		min;			// in ns
	ULONG		max;			// in ns
} TcIoTimeMeasurment, *PTcIoTimeMeasurment;


#pragma pack(pop)

const ULONG	IOFFS_TcIoOpenDevice						= DrvID_TcIo | 0x0001;
const ULONG	IOFFS_TcIoCsProvider						= DrvID_TcIo | 0x0002;
const ULONG	IOFFS_TcIoResetDevice					= DrvID_TcIo | 0x0003;
const ULONG	IOFFS_TcIoLegacyDeviceId				= DrvID_TcIo | 0x0004;
const ULONG	IOFFS_TcIoDevInfo							= DrvID_TcIo | TCOMINITDATAELM_IOFFS_OPTIONAL | 0x0005; //legacy support IOADS_IOF_DEVINFO
const ULONG	IOFFS_TcIoDevType							= DrvID_TcIo | 0x0006; //legacy support IOADS_IOF_READDEVTYPE
const ULONG	IOFFS_TcIoAccType							= DrvID_TcIo | 0x0007;
const ULONG	IOFFS_TcIoTaskSettings					= DrvID_TcIo | 0x0011;
const ULONG	IOFFS_TcIoImageCreate					= DrvID_TcIo | 0x0021;
const ULONG	IOFFS_TcIoImageParent					= DrvID_TcIo | 0x0022;
const ULONG	IOFFS_TcIoImageAdsPort					= DrvID_TcIo | 0x0023;
const	ULONG	IOFFS_TcIoCyclicCallList				= DrvID_TcIo | 0x0024;
const ULONG	IOFFS_TcIoImageCycleTimeNS				= DrvID_TcIo | 0x0025;
const ULONG	IOFFS_TcIoCreateAdi						= DrvID_TcIo | 0x0026;
const ULONG	IOFFS_TcIoIoCaller						= DrvID_TcIo | 0x0027;
const ULONG	IOFFS_TcIoOwnAmsNetId					= DrvID_TcIo | 0x0028;
const ULONG	IOFFS_TcIoChildAreaLocation			= DrvID_TcIo | 0x0029;	// type: TcIoChildAreaLocation[]
const ULONG	IOFFS_TcIoDataAreaSize					= DrvID_TcIo | 0x002a;	// type: TcIoDataAreaSize[]
const ULONG	IOFFS_TcIoContextInfo					= DrvID_TcIo | 0x002b;	// type: TcIoContextInfo[]
const ULONG	IOFFS_TcIoCreateAmsIoPort				= DrvID_TcIo | 0x002c;	// type: TcIoCreateAmsIoPort
const ULONG	IOFFS_TcIoIdleCaller						= DrvID_TcIo | 0x002d;
const ULONG	IOFFS_TcIoAdsAddr							= DrvID_TcIo | 0x002e;
const ULONG	IOFFS_TcIoAdsPort							= DrvID_TcIo | 0x002f;
const ULONG	IOFFS_TcIoImageInputAccess				= DrvID_TcIo | 0x0030;
const ULONG	IOFFS_TcIoImageOutputAccess			= DrvID_TcIo | 0x0031;
const	ULONG	IOFFS_TcIoInfoData						= DrvID_TcIo | 0x0032;
const	ULONG	IOFFS_TcIoInfoImgOid						= DrvID_TcIo | 0x0033;
const	PTCID IOFFS_EnabledDataAreas					= DrvID_TcIo | 0x0034;
const	PTCID IOFFS_TcIoDataAreaOwner					= DrvID_TcIo | TCOMINITDATAELM_IOFFS_OPTIONAL | 0x0035;
const ULONG	IOFFS_TcIoImageInputSize				= DrvID_TcIo | 0x0036;
const ULONG	IOFFS_TcIoImageOutputSize				= DrvID_TcIo | 0x0037;
const ULONG	IOFFS_TcIoPromiscuousMode				= DrvID_TcIo | 0x0038;
const ULONG	IOFFS_TcIoAdiReadAccess					= DrvID_TcIo | 0x0040;
const ULONG	IOFFS_TcIoAdiBitReadAccess				= DrvID_TcIo | 0x0041;
const ULONG	IOFFS_TcIoAdiWriteAccess				= DrvID_TcIo | 0x0050;
const ULONG	IOFFS_TcIoAdiBitWriteAccess			= DrvID_TcIo | 0x0051;
const ULONG	IOFFS_TcIoAdiBitForceAccess			= DrvID_TcIo | 0x0061;
const ULONG	IOFFS_TcIoAdiBitReleaseForce			= DrvID_TcIo | 0x0063;
const ULONG	IOFFS_TcIoAdiReadForceInfo				= DrvID_TcIo | 0x0064;
const ULONG	IOFFS_TcIoAdiReadForceInfoCount		= DrvID_TcIo | 0x0065;
const PTCID	IOFFS_TcIoAdiSetInputCopyInfo			= DrvID_TcIo | 0x0066;
const PTCID	IOFFS_TcIoAdiSetOutputCopyInfo		= DrvID_TcIo | 0x0067;
const PTCID	IOFFS_TcIoAdiSymbolOwner				= DrvID_TcIo | 0x0068;


// CID_TcIoAddSync
const ULONG	IOFFS_TcIoAddSync_OID_A					= DrvID_TcIo | 0x0041;
const ULONG	IOFFS_TcIoAddSync_OID_B					= DrvID_TcIo | 0x0042;

// CID_TcIoECatMAppBaseAdiHelper
const ULONG	IOFFS_TcIoECatMAppBaseAdiHelper		= DrvID_TcIo | 0x0060;
const ULONG	IOFFS_TcIoECatMAppBaseOidCfg			= DrvID_TcIo | 0x0061;
const ULONG	IOFFS_TcIoECatMAppBaseExtImage		= DrvID_TcIo | 0x0062;
const	ULONG	IOFFS_TcIoECatMAppBaseGpioOid			= DrvID_TcIo | 0x0063;
const	ULONG	IOFFS_TcIoECatMAppBaseSysTimeOid		= DrvID_TcIo | 0x0064;
const	ULONG	IOFFS_TcIoECatMAppBaseIntCtrlOid		= DrvID_TcIo | 0x0065;
const	ULONG	IOFFS_TcIoECatMAppBaseDevOid			= DrvID_TcIo | 0x0066;
const	ULONG	IOFFS_TcIoECatMAppBaseDeviceId		= DrvID_TcIo | 0x0067;
const	ULONG	IOFFS_TcIoECatMAppEthBaseDevOid		= DrvID_TcIo | 0x0068;

// generic PIDs
const PTCID	PID_Io_IoCallees							= DrvID_TcIo | 0x2001;
const PTCID	PID_Io_Callees								= DrvID_TcIo | 0x2002;
const PTCID	PID_Io_PostCallees						= DrvID_TcIo | 0x2003;
const PTCID	PID_Io_Callers								= DrvID_TcIo | 0x2004;
const PTCID	PID_Io_PostCallers						= DrvID_TcIo | 0x2005;
const PTCID	PID_Io_IoCallers							= DrvID_TcIo | 0x2006;
const PTCID	PID_Io_SortOrders							= DrvID_TcIo | 0x2007;
const PTCID	PID_Io_IoSortOrders						= DrvID_TcIo | 0x2008;


const PTCID	PID_Io_IoCaller							= DrvID_TcIo | 0x2010;
const PTCID	PID_Io_IoCaller2							= DrvID_TcIo | 0x2011;
const PTCID	PID_Io_IoCaller3							= DrvID_TcIo | 0x2012;
const PTCID	PID_Io_IoCaller4							= DrvID_TcIo | 0x2013;
const PTCID	PID_Io_IoCaller5							= DrvID_TcIo | 0x2014;
const PTCID	PID_Io_IoCaller6							= DrvID_TcIo | 0x2015;
const PTCID	PID_Io_IoCaller7							= DrvID_TcIo | 0x2016;
const PTCID	PID_Io_IoCaller8							= DrvID_TcIo | 0x2017;
const PTCID	PID_Io_IoCaller9							= DrvID_TcIo | 0x2018;
const PTCID	PID_Io_IoCaller10							= DrvID_TcIo | 0x2019;
const PTCID	PID_Io_IoCaller11							= DrvID_TcIo | 0x201A;
const PTCID	PID_Io_IoCaller12							= DrvID_TcIo | 0x201B;
const PTCID	PID_Io_IoCaller13							= DrvID_TcIo | 0x201C;
const PTCID	PID_Io_IoCaller14							= DrvID_TcIo | 0x201D;
const PTCID	PID_Io_IoCaller15							= DrvID_TcIo | 0x201E;
const PTCID	PID_Io_IoCaller16							= DrvID_TcIo | 0x201F;

const PTCID	PID_Io_Caller								= DrvID_TcIo | 0x2020;
const PTCID	PID_Io_Caller2								= DrvID_TcIo | 0x2021;
const PTCID	PID_Io_Caller3								= DrvID_TcIo | 0x2022;
const PTCID	PID_Io_Caller4								= DrvID_TcIo | 0x2023;
const PTCID	PID_Io_Caller5								= DrvID_TcIo | 0x2024;
const PTCID	PID_Io_Caller6								= DrvID_TcIo | 0x2025;
const PTCID	PID_Io_Caller7								= DrvID_TcIo | 0x2026;
const PTCID	PID_Io_Caller8								= DrvID_TcIo | 0x2027;
const PTCID	PID_Io_Caller9								= DrvID_TcIo | 0x2028;
const PTCID	PID_Io_Caller10							= DrvID_TcIo | 0x2029;
const PTCID	PID_Io_Caller11							= DrvID_TcIo | 0x202A;
const PTCID	PID_Io_Caller12							= DrvID_TcIo | 0x202B;
const PTCID	PID_Io_Caller13							= DrvID_TcIo | 0x202C;
const PTCID	PID_Io_Caller14							= DrvID_TcIo | 0x202D;
const PTCID	PID_Io_Caller15							= DrvID_TcIo | 0x202E;
const PTCID	PID_Io_Caller16							= DrvID_TcIo | 0x202F;

const PTCID	PID_Io_ADI									= DrvID_TcIo | 0x2030;
const PTCID	PID_Io_ADI2									= DrvID_TcIo | 0x2031;
const PTCID	PID_Io_ADI3									= DrvID_TcIo | 0x2032;
const PTCID	PID_Io_ADI4									= DrvID_TcIo | 0x2033;
const PTCID	PID_Io_ADI5									= DrvID_TcIo | 0x2034;
const PTCID	PID_Io_ADI6									= DrvID_TcIo | 0x2035;
const PTCID	PID_Io_ADI7									= DrvID_TcIo | 0x2036;
const PTCID	PID_Io_ADI8									= DrvID_TcIo | 0x2037;
const PTCID	PID_Io_ADI9									= DrvID_TcIo | 0x2038;
const PTCID	PID_Io_ADI10								= DrvID_TcIo | 0x2039;
const PTCID	PID_Io_ADI11								= DrvID_TcIo | 0x203A;
const PTCID	PID_Io_ADI12								= DrvID_TcIo | 0x203B;
const PTCID	PID_Io_ADI13								= DrvID_TcIo | 0x203C;
const PTCID	PID_Io_ADI14								= DrvID_TcIo | 0x203D;
const PTCID	PID_Io_ADI15								= DrvID_TcIo | 0x203E;
const PTCID	PID_Io_ADI16								= DrvID_TcIo | 0x203F;

const PTCID	PID_Io_Adapter								= DrvID_TcIo | 0x2040;
const PTCID	PID_Io_Adapter2							= DrvID_TcIo | 0x2041;
const PTCID	PID_Io_Adapter3							= DrvID_TcIo | 0x2042;
const PTCID	PID_Io_Adapter4							= DrvID_TcIo | 0x2043;
const PTCID	PID_Io_Adapter5							= DrvID_TcIo | 0x2044;
const PTCID	PID_Io_Adapter6							= DrvID_TcIo | 0x2045;
const PTCID	PID_Io_Adapter7							= DrvID_TcIo | 0x2046;
const PTCID	PID_Io_Adapter8							= DrvID_TcIo | 0x2047;
const PTCID	PID_Io_Adapter9							= DrvID_TcIo | 0x2048;
const PTCID	PID_Io_Adapter10							= DrvID_TcIo | 0x2049;
const PTCID	PID_Io_Adapter11							= DrvID_TcIo | 0x204A;
const PTCID	PID_Io_Adapter12							= DrvID_TcIo | 0x204B;
const PTCID	PID_Io_Adapter13							= DrvID_TcIo | 0x204C;
const PTCID	PID_Io_Adapter14							= DrvID_TcIo | 0x204D;
const PTCID	PID_Io_Adapter15							= DrvID_TcIo | 0x204E;
const PTCID	PID_Io_Adapter16							= DrvID_TcIo | 0x204F;

const PTCID	PID_Io_IpSettings							= DrvID_TcIo | 0x2050;
const PTCID	PID_Io_IpSettings2						= DrvID_TcIo | 0x2051;
const PTCID	PID_Io_IpSettings3						= DrvID_TcIo | 0x2052;
const PTCID	PID_Io_IpSettings4						= DrvID_TcIo | 0x2053;

const PTCID	PID_Ctx_TaskOid							= DrvID_TcIo | 0x2060;	// context task OID (automatically filled by SysMan)
const PTCID	PID_Ctx_TaskOid2							= DrvID_TcIo | 0x2061;
const PTCID	PID_Ctx_TaskOid3							= DrvID_TcIo | 0x2062;
const PTCID	PID_Ctx_TaskOid4							= DrvID_TcIo | 0x2063;
const PTCID	PID_Ctx_TaskOid5							= DrvID_TcIo | 0x2064;
const PTCID	PID_Ctx_TaskOid6							= DrvID_TcIo | 0x2065;
const PTCID	PID_Ctx_TaskOid7							= DrvID_TcIo | 0x2066;
const PTCID	PID_Ctx_TaskOid8							= DrvID_TcIo | 0x2067;
const PTCID	PID_Ctx_TaskOid9							= DrvID_TcIo | 0x2068;
const PTCID	PID_Ctx_TaskOid10							= DrvID_TcIo | 0x2069;
const PTCID	PID_Ctx_TaskOid11							= DrvID_TcIo | 0x206A;
const PTCID	PID_Ctx_TaskOid12							= DrvID_TcIo | 0x206B;
const PTCID	PID_Ctx_TaskOid13							= DrvID_TcIo | 0x206C;
const PTCID	PID_Ctx_TaskOid14							= DrvID_TcIo | 0x206D;
const PTCID	PID_Ctx_TaskOid15							= DrvID_TcIo | 0x206E;
const PTCID	PID_Ctx_TaskOid16							= DrvID_TcIo | 0x206F;

const PTCID	PID_Ctx_TaskPrio							= DrvID_TcIo | 0x2070;
const PTCID	PID_Ctx_TaskPrio2							= DrvID_TcIo | 0x2071;
const PTCID	PID_Ctx_TaskPrio3							= DrvID_TcIo | 0x2072;
const PTCID	PID_Ctx_TaskPrio4							= DrvID_TcIo | 0x2073;
const PTCID	PID_Ctx_TaskPrio5							= DrvID_TcIo | 0x2074;
const PTCID	PID_Ctx_TaskPrio6							= DrvID_TcIo | 0x2075;
const PTCID	PID_Ctx_TaskPrio7							= DrvID_TcIo | 0x2076;
const PTCID	PID_Ctx_TaskPrio8							= DrvID_TcIo | 0x2077;
const PTCID	PID_Ctx_TaskPrio9							= DrvID_TcIo | 0x2078;
const PTCID	PID_Ctx_TaskPrio10						= DrvID_TcIo | 0x2079;
const PTCID	PID_Ctx_TaskPrio11						= DrvID_TcIo | 0x207A;
const PTCID	PID_Ctx_TaskPrio12						= DrvID_TcIo | 0x207B;
const PTCID	PID_Ctx_TaskPrio13						= DrvID_TcIo | 0x207C;
const PTCID	PID_Ctx_TaskPrio14						= DrvID_TcIo | 0x207D;
const PTCID	PID_Ctx_TaskPrio15						= DrvID_TcIo | 0x207E;
const PTCID	PID_Ctx_TaskPrio16						= DrvID_TcIo | 0x207F;

const PTCID	PID_Ctx_TaskCycleNs						= DrvID_TcIo | 0x2080;	// in 1ns (automatically filled by SysMan)
const PTCID	PID_Ctx_TaskCycleNs2						= DrvID_TcIo | 0x2081;
const PTCID	PID_Ctx_TaskCycleNs3						= DrvID_TcIo | 0x2082;
const PTCID	PID_Ctx_TaskCycleNs4						= DrvID_TcIo | 0x2083;
const PTCID	PID_Ctx_TaskCycleNs5						= DrvID_TcIo | 0x2084;
const PTCID	PID_Ctx_TaskCycleNs6						= DrvID_TcIo | 0x2085;
const PTCID	PID_Ctx_TaskCycleNs7						= DrvID_TcIo | 0x2086;
const PTCID	PID_Ctx_TaskCycleNs8						= DrvID_TcIo | 0x2087;
const PTCID	PID_Ctx_TaskCycleNs9						= DrvID_TcIo | 0x2088;
const PTCID	PID_Ctx_TaskCycleNs10					= DrvID_TcIo | 0x2089;
const PTCID	PID_Ctx_TaskCycleNs11					= DrvID_TcIo | 0x208A;
const PTCID	PID_Ctx_TaskCycleNs12					= DrvID_TcIo | 0x208B;
const PTCID	PID_Ctx_TaskCycleNs13					= DrvID_TcIo | 0x208C;
const PTCID	PID_Ctx_TaskCycleNs14					= DrvID_TcIo | 0x208D;
const PTCID	PID_Ctx_TaskCycleNs15					= DrvID_TcIo | 0x208E;
const PTCID	PID_Ctx_TaskCycleNs16					= DrvID_TcIo | 0x208F;

const PTCID	PID_Ctx_AdsPort							= DrvID_TcIo | 0x2090;
const PTCID	PID_Ctx_AdsPort2							= DrvID_TcIo | 0x2091;
const PTCID	PID_Ctx_AdsPort3							= DrvID_TcIo | 0x2092;
const PTCID	PID_Ctx_AdsPort4							= DrvID_TcIo | 0x2093;
const PTCID	PID_Ctx_AdsPort5							= DrvID_TcIo | 0x2094;
const PTCID	PID_Ctx_AdsPort6							= DrvID_TcIo | 0x2095;
const PTCID	PID_Ctx_AdsPort7							= DrvID_TcIo | 0x2096;
const PTCID	PID_Ctx_AdsPort8							= DrvID_TcIo | 0x2097;
const PTCID	PID_Ctx_AdsPort9							= DrvID_TcIo | 0x2098;
const PTCID	PID_Ctx_AdsPort10							= DrvID_TcIo | 0x2099;
const PTCID	PID_Ctx_AdsPort11							= DrvID_TcIo | 0x209A;
const PTCID	PID_Ctx_AdsPort12							= DrvID_TcIo | 0x209B;
const PTCID	PID_Ctx_AdsPort13							= DrvID_TcIo | 0x209C;
const PTCID	PID_Ctx_AdsPort14							= DrvID_TcIo | 0x209D;
const PTCID	PID_Ctx_AdsPort15							= DrvID_TcIo | 0x209E;
const PTCID	PID_Ctx_AdsPort16							= DrvID_TcIo | 0x209F;

const PTCID	PID_Ctx_TaskCycleTime					= DrvID_TcIo | 0x20A0;	// in 100ns
const PTCID	PID_Ctx_TaskCycleTime2					= DrvID_TcIo | 0x20A1;
const PTCID	PID_Ctx_TaskCycleTime3					= DrvID_TcIo | 0x20A2;
const PTCID	PID_Ctx_TaskCycleTime4					= DrvID_TcIo | 0x20A3;
const PTCID	PID_Ctx_TaskCycleTime5					= DrvID_TcIo | 0x20A4;
const PTCID	PID_Ctx_TaskCycleTime6					= DrvID_TcIo | 0x20A5;
const PTCID	PID_Ctx_TaskCycleTime7					= DrvID_TcIo | 0x20A6;
const PTCID	PID_Ctx_TaskCycleTime8					= DrvID_TcIo | 0x20A7;
const PTCID	PID_Ctx_TaskCycleTime9					= DrvID_TcIo | 0x20A8;
const PTCID	PID_Ctx_TaskCycleTime10					= DrvID_TcIo | 0x20A9;
const PTCID	PID_Ctx_TaskCycleTime11					= DrvID_TcIo | 0x20AA;
const PTCID	PID_Ctx_TaskCycleTime12					= DrvID_TcIo | 0x20AB;
const PTCID	PID_Ctx_TaskCycleTime13					= DrvID_TcIo | 0x20AC;
const PTCID	PID_Ctx_TaskCycleTime14					= DrvID_TcIo | 0x20AD;
const PTCID	PID_Ctx_TaskCycleTime15					= DrvID_TcIo | 0x20AE;
const PTCID	PID_Ctx_TaskCycleTime16					= DrvID_TcIo | 0x20AF;

const PTCID	PID_Ctx_TaskSortOrder					= DrvID_TcIo | 0x20B0;	
const PTCID	PID_Ctx_TaskSortOrder2					= DrvID_TcIo | 0x20B1;
const PTCID	PID_Ctx_TaskSortOrder3					= DrvID_TcIo | 0x20B2;
const PTCID	PID_Ctx_TaskSortOrder4					= DrvID_TcIo | 0x20B3;
const PTCID	PID_Ctx_TaskSortOrder5					= DrvID_TcIo | 0x20B4;
const PTCID	PID_Ctx_TaskSortOrder6					= DrvID_TcIo | 0x20B5;
const PTCID	PID_Ctx_TaskSortOrder7					= DrvID_TcIo | 0x20B6;
const PTCID	PID_Ctx_TaskSortOrder8					= DrvID_TcIo | 0x20B7;
const PTCID	PID_Ctx_TaskSortOrder9					= DrvID_TcIo | 0x20B8;
const PTCID	PID_Ctx_TaskSortOrder10					= DrvID_TcIo | 0x20B9;
const PTCID	PID_Ctx_TaskSortOrder11					= DrvID_TcIo | 0x20BA;
const PTCID	PID_Ctx_TaskSortOrder12					= DrvID_TcIo | 0x20BB;
const PTCID	PID_Ctx_TaskSortOrder13					= DrvID_TcIo | 0x20BC;
const PTCID	PID_Ctx_TaskSortOrder14					= DrvID_TcIo | 0x20BD;
const PTCID	PID_Ctx_TaskSortOrder15					= DrvID_TcIo | 0x20BE;
const PTCID	PID_Ctx_TaskSortOrder16					= DrvID_TcIo | 0x20BF;

const PTCID	PID_Io_DataArea0AutoPdoMapping		= DrvID_TcIo | 0x20C0;	
const PTCID	PID_Io_DataArea1AutoPdoMapping		= DrvID_TcIo | 0x20C1;	

const PTCID	PID_Io_DataArea0AutoPdoSize			= DrvID_TcIo | 0x20D0;	
const PTCID	PID_Io_DataArea1AutoPdoSize			= DrvID_TcIo | 0x20D1;

const PTCID	PID_Io_AmsSymbolDownload1				= DrvID_TcIo | 0x20E0;
const PTCID	PID_Io_AmsSymbolDownload2				= DrvID_TcIo | 0x20E1;
const PTCID	PID_Io_AmsSymbolDownload3				= DrvID_TcIo | 0x20E2;

const PTCID	PID_MapEnableTimeMeasurment			= DrvID_TcIo | 0x2101;
const PTCID	PID_MapReadTimeMeasurment				= DrvID_TcIo | 0x2102;
// PID_TcTraceLevel
const PTCID	PID_MapRetainMaxBlockSize				= DrvID_TcIo | 0x2104;
const PTCID	PID_MapAutoInitOutputs					= DrvID_TcIo | 0x2105;
const PTCID	PID_MapEnableOnlineChange				= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2106;

const PTCID	PID_TcTraceLevel							= DrvID_TcIo | 0x2103;

const	PTCID PID_Io_DefaultMapping					= DrvID_TcIo | 0x2110;		
const PTCID PID_Io_AsyncTaskPrio						= DrvID_TcIo | 0x2111;		
const	PTCID PID_Io_AsyncTaskId						= DrvID_TcIo | 0x2112;
const	PTCID PID_SubModuleConfig						= DrvID_TcIo | 0x2113;
const	PTCID PID_ModuleGuid								= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2114;
const	PTCID PID_ModuleMD5Hash							= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2115;
const	PTCID PID_ModuleMD5Hash2						= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2116;
const	PTCID PID_ModuleMD5HashCfg						= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2117;
const	PTCID PID_ModuleMD5HashCfgOC					= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x2118;
const	PTCID PID_LibraryId								= DrvID_TcIo | 0x2119;	// <vendor>|<lib>|version
const	PTCID PID_ModuleClsId							= DrvID_TcIo | 0x211A;	// ClsId of sub module created by CTcTmcHandler
const	PTCID PID_JobTaskOid								= TCOMINITDATAELM_IOFFS_OPTIONAL | DrvID_TcIo | 0x211B;	// OID of job task to use

const PTCID	PID_Ctx_TaskOids							= DrvID_TcIo | 0x2201;	// more than 16 contexts: context task OIDs (automatically filled by SysMan)
const PTCID	PID_Ctx_TaskPrios							= DrvID_TcIo | 0x2202;	// more than 16 contexts: context task OIDs (automatically filled by SysMan)
const PTCID	PID_Ctx_TaskCycleNss						= DrvID_TcIo | 0x2203;	// more than 16 contexts: in 1ns
const PTCID	PID_Ctx_TaskSortOrders					= DrvID_TcIo | 0x2204;	// more than 16 contexts: context task OIDs (automatically filled by SysMan)
const PTCID	PID_Ctx_AdsPorts							= DrvID_TcIo | 0x2205;

const PTCID	PID_DataAreaCfg0							= DrvID_TcIo | 0x7000;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg1							= DrvID_TcIo | 0x7001;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg2							= DrvID_TcIo | 0x7002;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg3							= DrvID_TcIo | 0x7003;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg4							= DrvID_TcIo | 0x7004;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg5							= DrvID_TcIo | 0x7005;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg6							= DrvID_TcIo | 0x7006;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg7							= DrvID_TcIo | 0x7007;	// TcIoDataAreaCfg[]
const PTCID	PID_DataAreaCfg4095						= DrvID_TcIo | 0x7fff;
