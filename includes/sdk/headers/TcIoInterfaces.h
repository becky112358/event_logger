///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcInterfaces.h"
#include "TcIoServices.h"

struct	__declspec(novtable)	ITComIo : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddIoImage(USHORT imgId, PVOID pImage) = 0;
	virtual	HRESULT	TCOMAPI	DelIoImage(USHORT imgId) = 0;
	virtual	HRESULT	TCOMAPI	GetIoImage(USHORT imgId, PPVOID ppImg) = 0;
	virtual	HRESULT	TCOMAPI	IoFrameAlloc(ULONG nData, PVOID* ppData)=0; 
	virtual	HRESULT	TCOMAPI	IoFrameFree(PVOID pData)=0; 
	virtual	HRESULT	TCOMAPI	AddIoDevice(USHORT devId, OTCID oid) = 0;
	virtual	HRESULT	TCOMAPI	DelIoDevice(USHORT devId) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComIo, IID_ITComIo);

struct __declspec(novtable) ITcTask;
struct __declspec(novtable) ITcCyclic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCyclic, IID_ITcCyclic);

struct __declspec(novtable) ITcIoCyclic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	InputUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, DWORD dwStateIn, ULONG_PTR context = 0)=0;
	virtual	HRESULT	TCOMAPI	OutputUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, PDWORD pdwStateOut = NULL, ULONG_PTR context = 0)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoCyclic, IID_ITcIoCyclic);

typedef	SIftEntrySorted<ITcPreInputCyclic, ULONG_PTR> STcPreInputCyclicEntry;
typedef	CItfListSorted<STcPreInputCyclicEntry, ITcPreInputCyclic, ULONG_PTR>	CItfListPreInputCyclic;
struct __declspec(novtable) ITcPreInputCyclic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	PreInputUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context = 0)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcPreInputCyclic, IID_ITcPreInputCyclic);

struct __declspec(novtable) ITcPostCyclic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	PostCyclicUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcPostCyclic, IID_ITcPostCyclic);

struct __declspec(novtable) ITcFastCyclic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	FastCyclicUpdate(ULONG mCyc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcFastCyclic, IID_ITcFastCyclic);

typedef	SIftEntrySorted<ITcCyclic, ULONG_PTR> STcCyclicEntry;
typedef	CItfListSorted<STcCyclicEntry, ITcCyclic, ULONG_PTR>	CItfListCyclic;
struct __declspec(novtable) ITcCyclicCaller : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddModule(STcCyclicEntry* pEntry, ITcCyclic* ipMod, ULONG_PTR context=0, ULONG sortOrder=0)=0;	// default sortOrder (of AddModule()) is 100
	virtual	HRESULT	TCOMAPI	RemoveModule(STcCyclicEntry* pEntry)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCyclicCaller, IID_ITcCyclicCaller);
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcCyclicCaller, IID_ITcCyclicCaller, STcCyclicEntry);

typedef	SIftEntrySorted<ITcIoCyclic, ULONG_PTR> STcIoCyclicEntry;
typedef	CItfListSorted<STcIoCyclicEntry, ITcIoCyclic, ULONG_PTR>	CItfListIoCyclic;
struct __declspec(novtable) ITcIoCyclicCaller : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddIoDriver(STcIoCyclicEntry* pEntry, ITcIoCyclic* ipDrv, ULONG_PTR context=0, ULONG sortOrder=0)=0;	// default sortOrder (of AddIoDriver()) is 100
	virtual	HRESULT	TCOMAPI	RemoveIoDriver(STcIoCyclicEntry* pEntry)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoCyclicCaller, IID_ITcIoCyclicCaller);
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcIoCyclicCaller, IID_ITcIoCyclicCaller, STcIoCyclicEntry);

typedef	SIftEntrySorted<ITcPostCyclic, ULONG_PTR> STcPostCyclicEntry;
typedef	CItfListSorted<STcPostCyclicEntry, ITcPostCyclic, ULONG_PTR>	CItfListPostCyclic;
struct __declspec(novtable) ITcPostCyclicCaller : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddPostModule(STcPostCyclicEntry* pEntry, ITcPostCyclic* ipMod, ULONG_PTR context=0, ULONG sortOrder=0)=0;	// default sortOrder (of AddPostModule()) is 100
	virtual	HRESULT	TCOMAPI	RemovePostModule(STcPostCyclicEntry* pEntry)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcPostCyclicCaller, IID_ITcPostCyclicCaller);
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcPostCyclicCaller, IID_ITcPostCyclicCaller, STcPostCyclicEntry);

typedef	SIftEntrySorted<ITcFastCyclic, ULONG_PTR> STcFastCyclicEntry;
typedef	CItfListSorted<STcFastCyclicEntry, ITcFastCyclic, ULONG_PTR>	CItfListFastCyclic;
struct __declspec(novtable) ITcFastCyclicCaller : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddFastModule(STcFastCyclicEntry* pEntry, ITcFastCyclic* ipMod, ULONG sortOrder=0)=0;	// default sortOrder (of AddFastModule()) is 100
	virtual	HRESULT	TCOMAPI	RemoveFastModule(STcFastCyclicEntry* pEntry)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcFastCyclicCaller, IID_ITcFastCyclicCaller);
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcFastCyclicCaller, IID_ITcFastCyclicCaller, STcFastCyclicEntry);

typedef	SIftEntrySorted<ITcPreInputCyclic, ULONG_PTR> STcPreInputCyclicEntry;
typedef	CItfListSorted<STcPreInputCyclicEntry, ITcPreInputCyclic, ULONG_PTR>	CItfListPreInputCyclic;
struct __declspec(novtable) ITcPreInputCyclicCaller : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddPreInputModule(STcPreInputCyclicEntry* pEntry, ITcPreInputCyclic* ipMod, ULONG_PTR context=0, ULONG sortOrder=0)=0;	// default sortOrder (of AddModule()) is 100
	virtual	HRESULT	TCOMAPI	RemovePreInputModule(STcPreInputCyclicEntry* pEntry)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcPreInputCyclicCaller, IID_ITcPreInputCyclicCaller);
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcPreInputCyclicCaller, IID_ITcPreInputCyclicCaller, STcPreInputCyclicEntry);

struct __declspec(novtable) ITcIoCyclicNeedUpdate : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	NeedUpdateCall()=0;	// S_OK = need call, S_FALSE = no call needed
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoCyclicNeedUpdate, IID_ITcIoCyclicNeedUpdate);

struct __declspec(novtable) ITcIoCyclicNeedUpdate2 : public ITcIoCyclicNeedUpdate
{
	virtual	HRESULT	TCOMAPI	SetNeedUpdateCall() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoCyclicNeedUpdate2, IID_ITcIoCyclicNeedUpdate2);

struct __declspec(novtable) ITcADI : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetImagePtr(UINT size, UINT offs, UINT adi_x, PVOID* ppData)=0;
	virtual	HRESULT	TCOMAPI	ReleaseImagePtr(PVOID pData)=0;
	virtual	HRESULT	TCOMAPI	GetImageSize(UINT adi_x, PUINT pSize)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADI, IID_ITcADI);

struct __declspec(novtable) ITcADIAccess : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	ReadImage(UINT size, UINT offs, UINT adi_x, PVOID pData)=0;
	virtual	HRESULT	TCOMAPI	WriteImage(UINT size, UINT offs, UINT adi_x, PVOID pData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADIAccess, IID_ITcADIAccess);

struct __declspec(novtable) ITcADILegacy : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	SetImagePtr(UINT nIn, PVOID pIn, UINT nOut, PVOID pOut)=0;
	virtual	HRESULT	TCOMAPI	SetImageInfo(UINT id, UINT imgType, UINT addrType)=0;
	virtual	HRESULT	TCOMAPI	GetImageInfo(PUINT pId, PUINT pImgType, PUINT pAddrType)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADILegacy, IID_ITcADILegacy);

struct __declspec(novtable) ITcADIGlobalOffsets : public ITcUnknown
{
	virtual	ULONG	TCOMAPI	GetInputOffset()=0;
	virtual	ULONG	TCOMAPI	GetOutputOffset()=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADIGlobalOffsets, IID_ITcADIGlobalOffsets);

struct __declspec(novtable) ITcADIState : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetImageState(PDWORD pdwState)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADIState, IID_ITcADIState);

struct __declspec(novtable) ITcADISymbolic : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetSymbolPtr(PCHAR areaSymbolName, PVOID* ppData)=0;
	virtual	HRESULT	TCOMAPI	GetSymbolPtr(UINT adi_x, PCHAR symbolName, PVOID* ppData)=0;
	virtual	HRESULT	TCOMAPI	ReleaseSymbolPtr(PVOID pData)=0;
	virtual	HRESULT	TCOMAPI	GetSymbolInfo(PCHAR areaSymbolName, GUID* pType, PUINT pSize=NULL, PUINT pOffs=NULL, PUINT pAreaNo=NULL)=0;
	virtual	HRESULT	TCOMAPI	GetSymbolInfo(UINT adi_x, PCHAR symbolName, GUID* pType, PUINT pSize=NULL, PUINT pOffs=NULL)=0;
	virtual	HRESULT	TCOMAPI	GetSymbolCount(UINT adi_x, PUINT pCnt)=0;
	virtual	HRESULT	TCOMAPI	GetSymbolName(UINT adi_x, UINT idx, PCHAR pSymName, UINT nSymName)=0;
	virtual	HRESULT	TCOMAPI	GetAreaCount(PUINT pCnt)=0;
	virtual	HRESULT	TCOMAPI	GetAreaInfo(UINT idx, PUINT pAreaNo, PCHAR pAreaName=NULL, UINT nAreaName=0)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADISymbolic, IID_ITcADISymbolic);

struct __declspec(novtable) ITcADISymbolLocation : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetSymbolLocation(UINT adi_x, PCHAR symbolName, PUINT pBitSize, PUINT pBitOffs, GUID* pType=NULL)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADISymbolLocation, IID_ITcADISymbolLocation);

struct __declspec(novtable) ITcADISymbolLocation2 : public ITcADISymbolLocation
{
	virtual	HRESULT	TCOMAPI	GetSymbolLocation64(UINT adi_x, PCHAR symbolName, PULONGLONG pBitSize, PULONGLONG pBitOffs, GUID* pType=NULL)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcADISymbolLocation2, IID_ITcADISymbolLocation2);

struct __declspec(novtable) ITcPciDevice : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	MapPciBusAddress(ULONG ulBusNo, ULONG ulSlotNo, ULONG ulBaseAddr, ULONG memSize,
							 USHORT vendorId, USHORT deviceId, USHORT subVendorId, USHORT subSystemId, PVOID* ppData)=0;
	virtual	HRESULT	TCOMAPI	UnMapPhysAddr( PVOID pLinMem, ULONG memSize )=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcPciDevice, IID_ITcPciDevice);

struct __declspec(novtable) ITcWatchSource : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	WatchValueAvailable(ULONG indexOffset, ULONG cbLength)=0;
	virtual	HRESULT	TCOMAPI	GetWatchValue(ULONG indexOffset, ULONG& cbLength, PVOID pWatch)=0;
	virtual	HRESULT	TCOMAPI	SetWatchValue(ULONG indexOffset, ULONG cbLength, PVOID pWatch)=0;
	virtual	HRESULT	TCOMAPI	InterpretGroupOffsetLength(ULONG indexOffset, ULONG& cbLength, PVOID* ppData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcWatchSource, IID_ITcWatchSource);

struct __declspec(novtable) ITcAddRemoveAdditionalSymbols : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	AddAdditionalSymbols(PAdsSymbolUpAndDownloadHeader2 pSymData)=0;
	virtual	HRESULT	TCOMAPI	RemoveAdditionalSymbols(PAdsSymbolUpAndDownloadHeader2 pSymData)=0;
	virtual	HRESULT	TCOMAPI	ReplaceAdditionalSymbols(PAdsSymbolUpAndDownloadHeader2 pOldData, PAdsSymbolUpAndDownloadHeader2 pNewData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAddRemoveAdditionalSymbols, IID_ITcAddRemoveAdditionalSymbols);

struct __declspec(novtable) ITcDcTimeData : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI GetDcTimeData(ULONG dcTime, DTCID type, PVOID pData, ITcUnknown* ipCaller=NULL, ULONG_PTR context=0)=0;	// dcTime contains lower 32 bit of global DC-Time
	virtual	HRESULT	TCOMAPI SetDcTimeData(ULONG dcTime, DTCID type, PVOID pData, ITcUnknown* ipCaller=NULL, ULONG_PTR context=0)=0;	// type identifies structure of pData
	virtual	HRESULT	TCOMAPI CalcDcTimeData(ULONG dcTime, DTCID type, PVOID pData, ITcUnknown* ipCaller=NULL, ULONG_PTR context=0)=0;	// type identifies structure of pData
};
_TCOM_SMARTPTR_TYPEDEF(ITcDcTimeData, IID_ITcDcTimeData);

struct __declspec(novtable) ITcIoLegacyDevice : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetLegacyDeviceId(USHORT& id)=0;
	virtual	HRESULT	TCOMAPI	GetLegacyDeviceInfo(PIoAdsDevInfoEntry* ppInfo)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoLegacyDevice, IID_ITcIoLegacyDevice);

struct __declspec(novtable) ITcIoLegacyEthernetDevice : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetStatistics(IoEtherStatistic& stat)=0;
	virtual	HRESULT	TCOMAPI	GetTxRxErrorCnt(ULONG& txCnt, ULONG& rxCnt, bool bSecondary)=0;
   virtual  HRESULT  TCOMAPI  ResetTxRxErrorCnt(bool bSecondary)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoLegacyEthernetDevice, IID_ITcIoLegacyEthernetDevice);

struct	__declspec(novtable)	ITcIoTimeCtrl : public ITcUnknown
{
	virtual ULONG	 TCOMAPI LockTime()=0;
	virtual ULONG	 TCOMAPI UnlockTime()=0;
	virtual HRESULT TCOMAPI GetTime(volatile PULONGLONG& pnsTime)=0; // if not supported returns E_NOTIMPL
	virtual HRESULT TCOMAPI GetTime(ULONGLONG& nsTime)=0;
	virtual HRESULT TCOMAPI	SetTime(ULONGLONG nsTime)=0;
	virtual HRESULT TCOMAPI SetTimeOffset(LONGLONG offset)=0;
	virtual HRESULT TCOMAPI GetTimeOffset(LONGLONG& offset)=0;	
	virtual HRESULT TCOMAPI EnableExternalTimeControl(bool bLockTime);
	virtual HRESULT TCOMAPI DisableExternalTimeControl();
	virtual HRESULT TCOMAPI SetExternalControlTimeOffset(LONGLONG controlOffset); 	
	virtual HRESULT TCOMAPI GetExternalControlTimeOffset(LONGLONG& controlOffset); 	
	virtual HRESULT TCOMAPI ControlTiming(ULONGLONG timeInternal, ULONGLONG timeExternal, bool bReinit)=0;	
	virtual HRESULT TCOMAPI UpdateTiming()=0;	
	virtual HRESULT TCOMAPI RegisterSyncMaster(ITcUnknown* ipSyncMaster, ULONG prio)=0; 
	virtual HRESULT TCOMAPI	UnregisterSyncMaster(ITcUnknown* ipSyncMaster)=0;	
	virtual HRESULT TCOMAPI IsSyncMasterEnabled(ITcUnknown* ipSyncMaster, bool& bEnabled)=0; 
	virtual HRESULT TCOMAPI	AdjustRealtime(ULONG actualTime, ULONG expectedTime, ITcUnknown* ipSyncMaster)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoTimeCtrl, IID_ITcIoTimeCtrl);


///////////////////////////////////////////////////////////////////////////////
typedef	SIftEntry<ITcIoTimeCtrl> STcIoTimeCtrlEntry;
typedef	CItfList<STcIoTimeCtrlEntry, ITcIoTimeCtrl>	CItfListIoTimeCtrl;

struct	__declspec(novtable)	ITcIoTimeMaster : public ITcUnknown
{
	virtual	HRESULT TCOMAPI AddSlaveClock(STcIoTimeCtrlEntry* pEntry, ITcIoTimeCtrl* ipSlaveClock) = 0;
	virtual	HRESULT TCOMAPI RemoveSlaveClock(STcIoTimeCtrlEntry* pEntry) = 0;
};
_TCOM_SMARTPTR_TYPEDEF_INFO(ITcIoTimeMaster, IID_ITcIoTimeMaster, STcIoTimeCtrlEntry);

struct __declspec(novtable) ITcIoTimeSlave : public ITcUnknown
{
	virtual	HRESULT TCOMAPI GetMasterClockOID(OTCID& oid) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoTimeSlave, IID_ITcIoTimeSlave);

struct __declspec(novtable) ITcIoDevice : public ITcUnknown
{
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoDevice, IID_ITcIoDevice);

struct __declspec(novtable) ITComOcMapping : public ITcUnknown
{
	virtual  HRESULT  TCOMAPI  DoOnlineChange(OTCID oidPlc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComOcMapping, IID_ITComOcMapping);

struct __declspec(novtable) ITComOcMapping2 : public ITComOcMapping
{
	virtual  HRESULT  TCOMAPI  PrepareOnlineChange(OTCID oidPlc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComOcMapping2, IID_ITComOcMapping2);

typedef enum
{
	MS_Unmapped = 0,
	MS_Mapped = 1,
	MS_Partial = 2
} EPlcMappingStatus, *PEPlcMappingStatus;

struct __declspec(novtable) ITComMappingStatus : public ITcUnknown
{
	virtual  HRESULT  TCOMAPI  PrepareMappingStatus(OTCID oidPlc, bool bOnlineChange)=0;
	virtual  HRESULT  TCOMAPI  GetMappingStatus(OTCID oidPlc, ULONG offs, ULONG size, PEPlcMappingStatus pMS, POTCID pObj=NULL, bool bitAddr=false)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComMappingStatus, IID_ITComMappingStatus);

struct __declspec(novtable) ITComRetainMapping : public ITcUnknown
{
	virtual  HRESULT  TCOMAPI  SaveRetainData()=0;
	virtual  HRESULT  TCOMAPI  RestoreRetainData()=0;
	virtual  HRESULT  TCOMAPI  ClearRetainData()=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComRetainMapping, IID_ITComRetainMapping);

struct __declspec(novtable) ITcSymbolCyclicAccess : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	SymbolCyclicAccessHandleByName(CHAR* pName, ULONG nName, PULONG pHandle)=0;
	virtual	HRESULT	TCOMAPI	SymbolCyclicAccessReleaseHandle(ULONG handle)=0;
	virtual	HRESULT	TCOMAPI	SymbolCyclicAccessCopyData(ULONG handle, BOOL bToSymbol, PVOID pData, ULONG nData)=0;
	virtual HRESULT TCOMAPI SymbolCyclicAccessCallerIdByName(CHAR* pName, ULONG nName, POTCID pOid)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcSymbolCyclicAccess, IID_ITcSymbolCyclicAccess);

struct __declspec(novtable) ITcIoImageOwner : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetIoObjectFromLocation(OTCID oidImage, UINT adi_x, ULONGLONG bitOffs, POTCID pOid) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcIoImageOwner, IID_ITcIoImageOwner);

///////////////////////////////////////////////////////////////////////////////
template<typename T>
HRESULT TcAdiGetImagePtr(T* pData, UINT size, UINT offs, PVOID* ppData)
{
	HRESULT hr = S_OK;
	if (ppData == NULL)
	{
		hr = E_POINTER;
	}
	else
	{
		if ( size+offs <= sizeof(*pData) )
		{
			*ppData = reinterpret_cast<PBYTE>(pData)+offs;
		}
		else
		{
			hr = ADS_E_INVALIDSIZE;
		}
	}
	return hr;
}

template<typename TIn, typename TOut> 
HRESULT TcAdiGetImagePtr(TIn* pIn, TOut* pOut, UINT size, UINT offs, UINT adi_x, PVOID* ppData)
{
	HRESULT hr = S_OK;
	if (adi_x == ADI_O)
	{
		// pointer to output 
		hr = TcAdiGetImagePtr(pOut, size, offs, ppData);
	}
	else if (adi_x == ADI_I)
	{
		// pointer to input
		hr = TcAdiGetImagePtr(pIn, size, offs, ppData);
	}
	else
	{
		hr = ADS_E_INVALIDPARM;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
template<typename T> 
HRESULT TcAdiGetImageSize(T* pData, PUINT pSize)
{
	HRESULT hr = S_OK;
	if ( pSize == NULL)
	{
		hr = E_POINTER;
	}
	else
	{
		*pSize = sizeof(*pData);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
template<typename TIn, typename TOut> 
HRESULT TcAdiGetImageSize(TIn* pIn, TOut* pOut, UINT adi_x, PUINT pSize)
{
	HRESULT hr = S_OK;
	if (adi_x == ADI_O)
	{
		// size of output data
		hr = TcAdiGetImageSize(pOut, pSize);
	}
	else if (adi_x == ADI_I)
	{
		// size of input data
		hr = TcAdiGetImageSize(pIn, pSize);
	}
	else
	{
		hr = ADS_E_INVALIDPARM;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
template<typename TYPE>
class _tc_com_data_ptr_t
{
public:
	// Default constructor.
	//
	_tc_com_data_ptr_t() 
		: m_pPtr(NULL), m_adix(0), m_offs(0)
	{
	}

	_tc_com_data_ptr_t(UINT oid, UINT adix, UINT offs=0) 
		: m_pPtr(NULL), m_adix(adix), m_offs(offs)
	{
		m_spADI.SetOID(oid);
	}

	_tc_com_data_ptr_t(PTcIoAdiInitData pAdi) 
		: m_pPtr(NULL), m_adix(pAdi->adi_x), m_offs(pAdi->offs)
	{
		m_spADI.SetOID(pAdi->oid);
	}

	~_tc_com_data_ptr_t()
	{
		Release(); 
	}

	// Allows this class to be used as the data pointer itself.
	TYPE* operator->() const 
	{ 
		return m_pPtr; 
	}

	TYPE& operator*() const
	{
		return *m_pPtr;
	}

	// Return a const data pointer. This value may be NULL.
	//
	operator const TYPE*() const
	{
		return m_pPtr;
	}

	// Return data pointer. This value may be NULL.
	//
	operator TYPE*() 
	{
		return m_pPtr;
	}

	// This operator is provided so that simple boolean expressions will
	// work.  For example: "if (p) ...".
	// Returns true if the pointer is not NULL.
	//
	operator bool() const 
	{ 
		return m_pPtr != NULL; 
	}

	// For comparison to NULL
	//
	bool operator==(int null) 
	{
		return m_pPtr == NULL;
	}

	bool operator==(long null)
	{
		return m_pPtr == NULL;
	}

	bool operator!=(int null) 
	{
		return m_pPtr != NULL;
	}

	bool operator!=(long null)
	{
		return m_pPtr != NULL;
	}

	// This operator is provided to permit the assignment of NULL to the class.
	// It will release the pointer
	_tc_com_data_ptr_t& operator=(int null) 
	{
		Release();
		return *this;
	}

	void	SetADI(const TcIoAdiInitData* pAdi)
	{
		Release(); 
		m_spADI.SetOID(pAdi->oid);
		m_adix=pAdi->adi_x;
		m_offs=pAdi->offs; 
	}

	OTCID GetOID()
	{
		return m_spADI.GetOID();
	}

	UINT GetSize()
	{
		return sizeof(TYPE);
	}

	bool HasOID()
	{
		return m_spADI.HasOID();
	}

	void Release()
	{
		if ( m_spADI != NULL && m_pPtr != NULL )
		{
			m_spADI->ReleaseImagePtr((PVOID)m_pPtr);
		}
		m_pPtr	= NULL; 
		m_spADI	= NULL;
	}

	HRESULT Init(ITComObjectServer* ipSrv)
	{
		HRESULT hr = S_OK;
		if (m_spADI != NULL)
		{
			hr = ADS_E_INVALIDSTATE;
		}
		else
		{
			if (SUCCEEDED(hr = ipSrv->TcQuerySmartObjectInterface(m_spADI)))
			{
				hr = m_spADI->GetImagePtr(GetSize(), m_offs, m_adix, (PPVOID)&m_pPtr);
			}
			if (FAILED(hr))
			{
				Release();
			}
		}
		return hr;
	}

private:
	UINT			m_adix;
	UINT			m_offs;
	TYPE*			m_pPtr;
	ITcADIPtr	m_spADI;
};

#define _TCOM_SMARTDATAPTR        _tc_com_data_ptr_t
#define _TCOM_SMARTDATAPTR_TYPEDEF(TYPE) \
	typedef _TCOM_SMARTDATAPTR<TYPE> \
         TYPE ## DataPtr

_TCOM_SMARTDATAPTR_TYPEDEF(ULONG);

///////////////////////////////////////////////////////////////////////////////
template<typename DataPointerArrayBase, typename DataPointerInitDataType = TcIoAdiInitData>
class TTcDataPointerArray 
	: public DataPointerArrayBase
{
protected:
	using DataPointerArrayBase::m_Storage;
public:
	HRESULT Init(ULONG nData, PCVOID pData)
	{
		HRESULT hr = S_OK;
		ULONG nValues = nData/sizeof(DataPointerInitDataType);
		if (nValues * sizeof(DataPointerInitDataType) != nData)
		{
			hr = ADS_E_INVALIDSIZE;
		}
		else
		{
			if (!m_Storage.IsInitialized())
			{
				hr = m_Storage.Init(nValues);
			}
			if (SUCCEEDED(hr) && (m_Storage.m_nValues==nValues))
			{
				const DataPointerInitDataType* pDataPointerInitData = reinterpret_cast<const DataPointerInitDataType*>(pData);
				for (ULONG idx=0; idx<nValues; ++idx)
				{
					m_Storage.m_pValues[idx].SetADI(&pDataPointerInitData[idx]);
				}
			}
		}
		return hr;
	}
};

template<typename DataPointerType>
class TTcDataPointerArrayDynamic
	: public TTcDataPointerArray < TTcValueArrayBase< TTcArrayStorageDynamic<DataPointerType> > >
{
};

template<typename DataPointerType, ULONG DataPointerCount>
class TTcDataPointerArrayStatic
	: public TTcDataPointerArray < TTcValueArrayBase< TTcArrayStorageStatic<DataPointerType, DataPointerCount> > >
{
};

///////////////////////////////////////////////////////////////////////////////

#define DECLARE_ITCADI() \
	virtual	HRESULT	TCOMAPI	GetImagePtr(UINT size, UINT offs, UINT adi_x, PVOID* ppData); \
	virtual	HRESULT	TCOMAPI	ReleaseImagePtr(PVOID pData); \
	virtual	HRESULT	TCOMAPI	GetImageSize(UINT adi_x, PUINT pSize); 

#define IMPLEMENT_ITCADI(theClass) \
HRESULT	theClass::GetImagePtr(UINT size, UINT offs, UINT adi_x, PVOID* ppData) \
{ \
	HRESULT hr = S_OK; \
	if (ppData == NULL) \
	{ \
		hr = E_POINTER; \
	} \
	else if (SUCCEEDED_DBG(hr = TcTryLockOpState())) \
	{ \
		ULONG nData = size; \
		hr = TcGetObjDataAreaPtr(adi_x, offs, nData, ppData);  \
		if (FAILED(hr)) \
		{ \
			TcReleaseOpState(); \
		} \
	} \
	return hr; \
} \
\
HRESULT	theClass::ReleaseImagePtr(PVOID pData) \
{ \
	return TcReleaseOpState(); \
} \
 \
HRESULT	theClass::GetImageSize(UINT adi_x, PUINT pSize) \
{ \
	HRESULT hr = S_OK; \
	if (pSize == NULL) \
	{ \
		hr = E_POINTER; \
	} \
	else \
	{ \
		ULONG nData = 0; \
		hr = TcGetObjDataAreaPtr(adi_x, 0, nData, NULL);  \
		if (SUCCEEDED(hr)) \
		{ \
			 *pSize = static_cast<UINT>(nData); \
		} \
	} \
	return hr; \
}


///////////////////////////////////////////////////////////////////////////////
// ITcWatchSource
#define DECLARE_ITCWATCHSOURCE() \
	virtual	HRESULT	TCOMAPI	WatchValueAvailable(ULONG indexOffset, ULONG cbLength); \
	virtual	HRESULT	TCOMAPI	GetWatchValue(ULONG indexOffset, ULONG& cbLength, PVOID pWatch); \
	virtual	HRESULT	TCOMAPI	SetWatchValue(ULONG indexOffset, ULONG cbLength, PVOID pWatch); \
	virtual	HRESULT	TCOMAPI	InterpretGroupOffsetLength(ULONG indexOffset, ULONG& cbLength, PVOID* ppData);


#define IMPLEMENT_ITCWATCHSOURCE(theClass) \
HRESULT theClass::WatchValueAvailable(ULONG indexOffset, ULONG cbLength) \
{ \
	PVOID pWatch = NULL; \
	return TcGetObjWatchPtr(indexOffset, cbLength, &pWatch); \
} \
 \
HRESULT theClass::GetWatchValue(ULONG indexOffset, ULONG& cbLength, PVOID pWatch) \
{ \
	return TcGetObjPara(indexOffset, cbLength, pWatch); \
} \
 \
HRESULT theClass::SetWatchValue(ULONG indexOffset, ULONG cbLength, PVOID pWatch) \
{ \
	return TcSetObjPara(indexOffset, cbLength, pWatch); \
} \
 \
HRESULT theClass::InterpretGroupOffsetLength(ULONG indexOffset, ULONG& cbLength, PVOID* ppData) \
{ \
	return TcGetObjWatchPtr(indexOffset, cbLength, ppData); \
}


