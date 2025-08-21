///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBase.h"
#include "TcError.h"
#include "AmsR0.h"
#include "Ads.h"
#include "AdsLog.h"
#include	"HashTable.h"
#include "TcInterfaces.h"
#include "TcRtInterfaces.h"

#define	ADS_JSON_SUPPORT

#define ADS_METHODCAST
//#define ADS_OPT_NOTIFICATION

#ifndef OBJ_DRIVER_FRAMELIB
////////////////////////////////////////////////////////////////////////////////
//typedef BOOL	(*PAdsGetWatchValueFunc)	( PVOID pData );
#define	ADSWATCH_MAXSERACHKEYBUFFER	500
#define	ADSWATCH_MAXDYNSYMBOLPOOLS		8
#define	ADSWATCH_NEWDYNSYMBOLPOOL_INVOKEID	0x00fe0000

typedef struct
{
	AmsHead	head;
	ULONG		result;
	ULONG		cbLength;
	BYTE		data[1];
} TAmsAdsReadRwRes, *PAmsAdsReadRwRes;
#define SIZEOF_TAmsAdsReadRwRes	(offsetof(TAmsAdsReadRwRes, data))
#define AdsOptReadResAndFree(a, i, p)			AdsOptReadOrRwResAndFree(FALSE, a, i, p)
#define AdsOptReadWriteResAndFree(a, i, p)	AdsOptReadOrRwResAndFree(TRUE, a, i, p)

////////////////////////////////////////////////////////////////////////////////
struct AdsSymbolArrayEntry;
struct AdsDatatypeArrayEntry;
struct AdsPersistentDataEntry;
struct AdsPersistentInfoEntry;
struct AdsTcComIFacePtrInfoEntry;
struct TcAdsSymbolData;

////////////////////////////////////////////////////////////////////////////////
class CAdsWatchClients;
class CAdsLog;
class CAdsWatchEntry;
class CR0Archive;
class CAdsLockHelper;
#ifdef	ADS_JSON_SUPPORT
struct SAdsJsonValuesHandler;
struct SJsonValuesReader;
struct SJsonValuesWriter;
struct ITcJsonSaxWriter;
#endif

class DLL_EXPORT CAdsWatchServerR0 : public CAds
{
public:
	CAdsWatchServerR0();
	virtual ~CAdsWatchServerR0();

	ULONG GetUniqueHandle();

	long AdsUpdateWatches(__int64 nTime=0, UINT nContext=0);

	virtual	void	AdsDeviceNotificationCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );

	virtual	void	AdsDelDeviceNotificationInd( AmsAddr& rAddr, ULONG invokeId, ULONG hNotification );

	virtual	long	AdsAddWatch(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
		ULONG indexOffset, AdsNotificationAttrib noteAttrib,
		ULONG& hNotification, ULONG hDynEntry = 0);

	virtual	long	AdsRemoveWatch( AmsAddr& rAddr, ULONG invokeId, ULONG hNotification );

	virtual	long	AdsGetWatchValue( ULONG indexGroup, ULONG indexOffset, ULONG& cbLength, PVOID pWatch );
	virtual	long	AdsSetWatchValue( ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pWatch );

	virtual	void	AdsGetTime( __int64& nTime ) = 0;
	virtual	ULONG GetTimeBase();
	virtual	void	SetTimeBase( ULONG nTimeBase );
	virtual	ULONG AdsGetWatchCycleTime();
	
	friend	class CAdsWatchEntry;
	virtual	long	InitWatchServer( ULONG nTimeBase, UINT nContexts=1 );
	virtual	long	IncreaseWatchServerLists(UINT nContexts);
	virtual	long	ShutdownWatchServer();

	virtual	int	AdsReadWriteRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int	AdsReadRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int	AdsWriteRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
	virtual	int	AdsReadWriteSumUpRes( ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );

	virtual	void	AdsWriteInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData );
	virtual	void	AdsReadInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength );
	virtual	void	AdsReadWriteInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData );
	virtual	void	AdsAddDeviceNotificationInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, AdsNotificationAttrib noteAttrib );
	virtual	void	AdsReadCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	void	AdsWriteCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );

	virtual PVOID	AdsInterpretGroupOffsetLength( ULONG indexGroup, ULONG indexOffset, ULONG& cbLength );
	virtual	LONG	AdsGetContextAndCycleTime(ULONG indexGroup, ULONG indexOffset, ULONG cbLength, ULONG& context, ULONG& cycleTime) { return ADSERR_DEVICE_SRVNOTSUPP; }
	virtual	LONG	AdsGetCycleTimeOfContext(ULONG context, ULONG& cycleTime) { return ADSERR_DEVICE_SRVNOTSUPP; }

	virtual	HRESULT	AdsAddFlexibleSymbols(PAdsSymbolUpAndDownloadHeader2 pSymData);
	virtual	HRESULT	AdsRemoveFlexibleSymbols(PAdsSymbolUpAndDownloadHeader2 pSymData);
	virtual	HRESULT	AdsReplaceFlexibleSymbols(PAdsSymbolUpAndDownloadHeader2 pOldData, PAdsSymbolUpAndDownloadHeader2 pNewData);
protected:
	virtual	PAmsAdsReadRwRes	AdsAllocOptReadOrRwRes(ULONG cbLength, ULONG result=ADSERR_NOERR);
	virtual	int	AdsOptReadOrRwResAndFree(BOOL bRW, AmsAddr& rAddr, ULONG invokeId, PAmsAdsReadRwRes pRes); // pRes must be allocated via AdsAllocOptReadOrRwRes
	virtual	TcAdsSymbolData*	AllocSymbolData(AdsSymbolUpAndDownloadHeader2* pHead, PVOID pSym=NULL, PVOID pDt=NULL, ULONG nAddData=0, PVOID pAddData=NULL);
	virtual	TcAdsSymbolData*	AllocSymbolData(AdsSymbolUpAndDownloadHeader3* pHead, PVOID pSym=NULL, PVOID pDt=NULL);
#ifdef AMS_COMPRESSION
	virtual	bool	UncompressData(const PVOID pIn, ULONG nIn, PVOID pOut, ULONG nOut) { return false; }
#endif
	virtual	void	FindPersistentArrayInstances(PCHAR name, PAdsDatatypeEntry pType, PAdsDatatypeArrayInfo pAInfo, USHORT dim, TcAdsSymbolData* pSD, ULONG& nPersistent, ULONG& nPersistSize);
	virtual	void	FindPersistentDataInstances(PAdsDatatypeEntry pType, TcAdsSymbolData* pSD, ULONG& nPersistent, ULONG& nPersistSize);
	virtual	void	FillPersistentArrayInstances(UINT level, PCHAR name, PAdsDatatypeEntry pType, PAdsDatatypeArrayInfo pAInfo, USHORT dim, TcAdsSymbolData* pSD, ULONG iGrp, ULONG iOffs, AdsPersistentDataEntry*& pData, AdsPersistentInfoEntry*& pInfo);
	virtual	void	FillPersistentDataInstances(UINT level, PAdsDatatypeEntry pType, TcAdsSymbolData* pSD, ULONG iGrp, ULONG iOffs, AdsPersistentDataEntry*& pData, AdsPersistentInfoEntry*& pInfo);
	virtual	void	FindTcComIFacePtrArrayInstances(PAdsDatatypeEntry pType, PAdsDatatypeArrayInfo pAInfo, USHORT dim, TcAdsSymbolData* pSD, ULONG& nTcComIFacePtr);
	virtual	void	FindTcComIFacePtrInstances(PAdsDatatypeEntry pType, TcAdsSymbolData* pSD, ULONG& nTcComIFacePtr);
	virtual	void	FillTcComIFacePtrArrayInstances(PAdsDatatypeEntry pType, PAdsDatatypeArrayInfo pAInfo, USHORT dim, TcAdsSymbolData* pSD, ULONG iGrp, ULONG iOffs, AdsTcComIFacePtrInfoEntry*& pInfo);
	virtual	void	FillTcComIFacePtrInstances(PAdsDatatypeEntry pType, TcAdsSymbolData* pSD, ULONG iGrp, ULONG iOffs, AdsTcComIFacePtrInfoEntry*& pInfo);
	virtual	void	FreeSymbolData(TcAdsSymbolData*& pData);
	virtual	long	AdsPrepareSymbolDownload(TcAdsSymbolData* pNewData);
	virtual	long	AdsSymbolDownload(TcAdsSymbolData*& pData);
	virtual	void	AdsSymbolUpload(AmsAddr& rAddr, ULONG invokeId, ULONG indexOffset, ULONG cbLength);
	virtual	void	AdsDatatypeUpload(AmsAddr& rAddr, ULONG invokeId, ULONG indexOffset, ULONG cbLength);
	virtual	void	AdsClearSymbols();
	virtual	ULONG	AdsGenerateSymbolName(PAdsDatatypeEntry pType, ULONG iOffs, ULONG size, PAdsDatatypeEntry pEntry, PCHAR pName=NULL, ULONG nName=0, TcAdsSymbolData* pSymData=NULL, BOOL bExact=FALSE);
	virtual	ULONG	AdsGenerateSymbolName(ULONG iGrp, ULONG iOffs, ULONG size, PCHAR pName=NULL, ULONG nName=0, TcAdsSymbolData* pSymData=NULL);
	virtual	ULONG	AdsGenerateSymbolName(AdsDynSymbolArrayEntry* pEntry, PCHAR pName=NULL, ULONG nName=0, TcAdsSymbolData* pSymData=NULL);
	virtual	long	AdsResolveOnlinePointer(AdsDynSymbolArrayEntry*& pEntry, PBYTE& pOnline, ULONG& cbLength, ULONG& size);
public:
	virtual	PAdsDatatypeEntry	AdsGetTypeByName(PCHAR sType, TcAdsSymbolData* pSymData=NULL);
protected:
	virtual	AdsDynSymbolArrayEntry*	AdsGetDynSymbolArrayEntry(ULONG handle, TcAdsSymbolData* pSymData=NULL);
	virtual	AdsDynSymbolArrayEntry* AdsGetFreeDynSymbolArrayEntry(TcAdsSymbolData* pSymData, AdsDynSymbolArrayEntry* pUsed=NULL);
	virtual	ULONG	AdsSearchSymbol(PVOID pSym, UINT nSym, ULONG& result, TcAdsSymbolData* pSymData=NULL, AdsDynSymbolArrayEntry* pUsed=NULL, BOOL bIgnoreExisting=FALSE ADSREFACTORINFO_H);
	virtual	AdsDynSymbolArrayEntry*	AdsParseSymbol(AdsSymbolArrayEntry* pSEntry, PCHAR sSym, PCHAR sType, DWORD flags, PCHAR sRest, ULONG iGrp, ULONG iOffs, ULONG& result, TcAdsSymbolData* pSymData, 
		AdsDynSymbolArrayEntry* pUsed=NULL ADSREFACTORINFO_H);

	virtual	BOOL	AdsCalcArrayOffs(USHORT arrayDim, ULONG& size, PAdsDatatypeArrayInfo arrayInfos, PULONG arrayIdx, ULONG& offs, bool bAnySize=false);
	virtual	BOOL	AdsCalcArrayDim(ULONG offs, USHORT arrayDim, ULONG size, PAdsDatatypeArrayInfo arrayInfos, PULONG arrayIdx);
	virtual	ULONG	AdsReleaseHandle(ULONG handle, TcAdsSymbolData* pSymData=NULL);
	virtual	void	AdsIncUsedDynSymbol(TcAdsSymbolData* pSymData=NULL);
	virtual	VOID	AdsIncreaseDynSymPool();
	virtual	PAdsSymbolEntry	AdsGetSymbolByName(PCCH sName, TcAdsSymbolData* pSymData=NULL, BOOL bSearchMainSymbol=FALSE);
	virtual	CAdsLog*	GetAdsLog()
		{ return NULL; }
	virtual	HRESULT	GetTComObjectServer(ITComObjectServer** pipSrv)
		{ return E_NOTIMPL; }
	virtual	void	SafeSymbolVersionToRegistry() {};	
	virtual	ULONG	AdsGetSymbolTypeGuidByHandle(ULONG handle, GUID* pGuid, ULONG* pSize=NULL, ULONG* pOffs=NULL, ULONG* pGrp=NULL, TcAdsSymbolData* pSymData=NULL, bool bDontDerefLastReference=false);
	virtual	PVOID	AdsGetMethodCallBaseAddress() { return NULL; }
	virtual	HRESULT	PerformSymbolOnlineChange(PAdsSymbolUpAndDownloadHeader2 pAdd, PAdsSymbolUpAndDownloadHeader2 pDel);
#ifdef	ADS_EXTERNALTIME_PROVIDER
	virtual	void	AdsGetExternalTimeOffset(ITcExternalTime::TimeType type, __int64& offset) { offset = 0; }
#endif
public:
	virtual	PAdsDatatypeEntry	AdsGetTypeBySymbolAddress(ULONG iGrp, ULONG iOffs, ULONG size, BOOL bExternalCall, TcAdsSymbolData* pSymData=NULL);
	virtual	PAdsDatatypeEntry AdsGetTypeBySymbolAddress(PAdsDatatypeEntry pType, ULONG iOffs, ULONG size, BOOL bExternalCall, TcAdsSymbolData* pSymData=NULL);
	virtual	BOOL	SymbolsAvailable();
	virtual	ULONG	AdsGetSymbolCnt(TcAdsSymbolData* pData=NULL);
	virtual	ULONG	AdsGetDatatypeCnt(TcAdsSymbolData* pData=NULL);
	virtual	ULONG	AdsGetSymbolSize(TcAdsSymbolData* pData=NULL);
	virtual	ULONG	AdsGetDatatypeSize(TcAdsSymbolData* pData=NULL);
	virtual	PBYTE	AdsGetSymbolPtr(TcAdsSymbolData* pData=NULL);
	virtual	PBYTE	AdsGetDatatypePtr(TcAdsSymbolData* pData=NULL);

	void AdsClearOnlinePtrs();
	friend class CAdsWatchClient;

	struct SumUpData
	{
		SumUpData() : pData(NULL), pAddr(NULL) {}
		SumUpData(PVOID Data) : pData(Data), pAddr(NULL) {}
		SumUpData(PVOID Data, AmsAddr* Addr) : pData(Data), pAddr(Addr) {}
		PVOID pData;
		AmsAddr* pAddr;
	};

protected:
	virtual int AmsSend__(PAmsCmd pCmd) = 0;
	virtual AmsAddr GetAmsAddr__() = 0;

	virtual	void	AdsLock()
		{}
	virtual	void	AdsUnlock()
		{}
	friend class CAdsLockHelper;

	virtual	void*	AdsAllocSymbols( ULONG size )
		{ return AdsAlloc(size); }
	virtual	void	AdsFreeSymbols( void* pVoid )
		{ AdsFree(pVoid); }

	ULONG							m_nNextSymbolIdx;
	BYTE							m_nSymbolVersion;
	ULONG							m_nInvalidDynSymbol;
	BOOL							m_bPendingIncrease;
	BOOL							m_bDisableUpdateWatches;
	ULONG							m_nOnlineChangeCnt;
	TcAdsSymbolData*			m_pSymData;

	LIST_ENTRY						m_listInvalidDynSymbol;

	CHashTable<ULONG, SumUpData, 10>	m_mapSumUpData;
	ULONG							m_nSumUpKey;

#ifdef	ADS_EXTERNALTIME_PROVIDER
	CHashTableDyn<AmsAddr, ULONG>	m_vExternalTimeType;
	ITcExternalTimePtr				m_spExternalTime;
	ITcExternalTime::TimeType		m_eExternalTimeType;
#endif

	// Persistent Data
	enum SavePersistentDataMode
	{
		SPDM_NORMAL,
		SPDM_2PASS,
		SPDM_VAR_BOOST,
	};
	typedef void	(_stdcall *PSpd_Boost_Func)(PVOID pThis);
	virtual	long	AdsSavePersistentData(SavePersistentDataMode mode, PVOID pThis, PSpd_Boost_Func pBoost, PSpd_Boost_Func pUnboost);
	virtual	long	AdsRestorePersistentData();
	virtual	void	AdsWritePersistentData(ITComArchiveOp* ipArchive, TcAdsSymbolData* pSymData=NULL);
	virtual	void	AdsWritePersistentDatatypes(ITComArchiveOp* ipArchive, TcAdsSymbolData* pSymData = NULL);
	virtual	bool	AdsAllocRestorePersistentDatatypes(ITComArchiveOp* ipArchive, TcAdsSymbolData** ppSymData);
	virtual	bool	AdsAllocRestorePersistentDatatypes(CR0Archive* pArchive, TcAdsSymbolData** ppSymData);
	virtual	long	AdsReadAndRestorePersistentData(ITComArchiveOp* ipArchive, BYTE& persitentStatus, TcAdsSymbolData* pSymData = NULL);
	virtual	long	AdsReadAndRestorePersistentData(CR0Archive* pArchive, BYTE& persitentStatus, TcAdsSymbolData* pSymData = NULL);
	friend	HRESULT	AdsRestorePersistentSubEntry(CAdsWatchServerR0* pSrv, PAdsDatatypeEntry pType, PBYTE pOnline, PBYTE pData, ULONG nData);
	friend	HRESULT	AdsRestorePersistentEntry(CAdsWatchServerR0* pSrv, AdsPersistentDataEntry* p, PAdsSymbolEntry& pEntry, USHORT& level, PCHAR pTmp, TcAdsSymbolData* pSymData = NULL);
	friend	ULONG		AdsEnumPersistentSubEntryToRestore(CAdsWatchServerR0* pSrv, PAdsDatatypeEntry pType);
	friend	ULONG		AdsTryRestorePersistentArrayEntries(CAdsWatchServerR0* pSrv, PCHAR pName, PAdsDatatypeEntry pBDT, size_t size, USHORT dim, PAdsDatatypeArrayInfo pAInfo, PBYTE pSrc, TcAdsSymbolData* pSymData);
	friend	ULONG		AdsTryRestorePersistentSubEntries(CAdsWatchServerR0* pSrv, PCHAR pName, const GUID& guid, PBYTE pSrc, TcAdsSymbolData* pSymData);
	virtual	void	ReleaseSymbolTcomInterfacePtr(bool bClearPtr=true);
#ifdef ADS_METHODCAST
	virtual	HRESULT	AdsQueueAsyncMethodDeviceNotification(AmsAddr amsClientAddr, ULONG hNotification, ULONG cbLength, __int64 nActTime, ULONG hDynEntry) { return E_NOTIMPL; }
	virtual	HRESULT	AdsSendAsyncMethodDeviceNotification(AmsAddr amsClientAddr, ULONG hNotification, ULONG cbLength, __int64 nActTime, ULONG hDynEntry);
	virtual	HRESULT	AdsSupportAsyncMethodDeviceNotification() { return S_FALSE; }
#endif

#ifdef	ADS_JSON_SUPPORT
	friend struct SAdsJsonValuesHandler;
	virtual	long	AdsReadWriteJsonInd(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData);
	virtual	long	AdsReadWriteJson(PCCH sJsonReq, ULONG& nJsonRes, PCHAR sJsonRes=NULL);
	virtual	LONGLONG AdsGetCurSystemTime() {return 0;}
	virtual	long	AdsGetDatatypeNameByAddress(ULONG iGrp, ULONG iOffs, ULONG size, ULONG& nName, PCHAR sName, TcAdsSymbolData* pSymData = NULL);
	friend struct SJsonValuesReader;
	virtual	long	AdsSetSymbolFromJson(PCCH sJson, PCCH sDatatype, ULONG nData, PVOID pData);
	virtual	long	AdsGetJsonFromSymbol(PCCH sDatatype, ULONG nData, PVOID pData, ULONG& nJson, PCHAR sJson=NULL);
	virtual	long	AdsAddJsonValueFromSymbol(ITcJsonSaxWriter* ipJson, PCCH sDatatype, ULONG nData, PVOID pData);
	virtual	long	AdsGetJsonFromSymbolProperties(PCCH sDatatype, PCCH sProperties, ULONG& nJson, PCHAR sJson=NULL);	// sProperties separated by '|'
	virtual	long	AdsAddJsonPropertiesFromSymbol(ITcJsonSaxWriter* ipJson, PCCH sDatatype, PCCH sProperties);
	virtual	long	AdsGetAdsSymbolInfo(PCCH sSymbol, ULONG& nInfo, PAdsSymbolEntry pInfo=NULL);
	virtual	long	AdsGetAdsDatatypeInfo(PCCH sDatatype, ULONG& nInfo, PAdsDatatypeEntry pInfo=NULL);
	virtual	long	AdsGetAdsBaseDatatypes(PCCH sDatatype, bool includeGlobal, ULONG& nTypes, ULONG& nChars, PCHAR pChars=NULL);
	virtual	long	AdsGetSymbolDatatype(PCCH sSymbol, ULONG& nDatatype, PCHAR sDatatype=NULL);
#endif
	virtual	long	AdsGetAdsSymbolInfoByHandle(ULONG handle, AdsSymbolInfoByName& info);

	DECLARE_CRITSEC

private:
	ULONG						m_nNewHandle;
	CAdsWatchClients**	m_pparrWatchClients;
	UINT						m_narrWatchClients;
	ULONG						m_nTimeBase;
	ULONG						m_nMinWatchSize;
	int						m_nSuppressLogMsgs;
	friend class CSuppressLogMsgHelper;
};
#endif // OBJ_DRIVER_FRAMELIB

class DLL_EXPORT CAdsAddAttribute
{
public:
	CAdsAddAttribute(PCHAR name="", PCHAR value="");
	ULONG CalcSize();
	ULONG GenerateDesc(PAdsAttributeEntry pData);
	PCHAR		m_name;
	PCHAR		m_value;
};

class DLL_EXPORT CAdsAddEnumInfo
{
public:
	CAdsAddEnumInfo(PCHAR name, ULONG value);
	ULONG CalcSize(ULONG size);
	ULONG GenerateDesc(PAdsEnumInfoEntry pData, ULONG size);
	PCHAR		m_name;
	ULONG		m_value;
};

class DLL_EXPORT CAdsAddDatatype
{
public:
	CAdsAddDatatype(PCHAR name, PCHAR type, ULONG size, GUID	guid=GUID_NULL, ULONG ads=ADST_BIGTYPE, DWORD flags=0, PCHAR comment="", USHORT cntAttr=0, 
		CAdsAddAttribute* pAttr=NULL, USHORT cntEnum=0, CAdsAddEnumInfo* pEnum=NULL);
	virtual ~CAdsAddDatatype() {};
	virtual void SetAttributes(USHORT cntAttr, CAdsAddAttribute* pAttr);
	virtual void SetEnumInfos(USHORT cntEnum, CAdsAddEnumInfo* pEnum);
	virtual ULONG CalcSize();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false)	{}
	virtual ULONG GenerateDesc(PVOID pData);
	virtual	void AppendDescAfterHeader(PAdsDatatypeEntry p);
	virtual	bool IsBaseType() { return false; }
	PCHAR		m_name;
	PCHAR		m_type;
	PCHAR		m_comment;
	GUID		m_guid;
	ULONG		m_size;
	ULONG		m_ads;
	DWORD		m_flags;
	ULONG		m_offs;
	USHORT				m_cntAttr;
	CAdsAddAttribute*	m_pAttr;
	USHORT				m_cntEnum;
	CAdsAddEnumInfo*	m_pEnum;
};

class DLL_EXPORT CAdsAddAliasDatatype : public CAdsAddDatatype
{
public:
	CAdsAddAliasDatatype(PCHAR name, CAdsAddDatatype& base, DWORD flags=0, PCHAR comment="", USHORT cntAttr=0, CAdsAddAttribute* pAttr=NULL, USHORT cntEnum=0, CAdsAddEnumInfo* pEnum=NULL);
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	CAdsAddDatatype&		m_base;
};

class DLL_EXPORT CAdsAddDataitem : public CAdsAddDatatype
{
public:
	CAdsAddDataitem(PCHAR name, CAdsAddDatatype& type, ULONG offs, DWORD flags=0, PCHAR comment="", USHORT cntAttr=0, CAdsAddAttribute* pAttr=NULL, USHORT cntEnum=0, CAdsAddEnumInfo* pEnum=NULL);
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	CAdsAddDatatype&		m_type;
};

class DLL_EXPORT CAdsAddBaseDatatype : public CAdsAddDatatype
{
public:
	CAdsAddBaseDatatype(PCHAR name, ULONG size, ULONG ads, BYTE typeByte=0, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	virtual	bool IsBaseType() { return true; }
};

class DLL_EXPORT CAdsAddStructDatatype : public CAdsAddDatatype
{
public:
	CAdsAddStructDatatype(PCHAR name, GUID guid, USHORT item, CAdsAddDataitem* items, ULONG size=0, DWORD flags=0, PCHAR comment="", USHORT cntAttr=0, CAdsAddAttribute* pAttr=NULL);
	virtual ULONG CalcSize();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	virtual	void AppendDescAfterHeader(PAdsDatatypeEntry p);
	USHORT				m_item;
	CAdsAddDataitem*	m_items;
};

class DLL_EXPORT CAdsAddArrayDatatype : public CAdsAddDatatype
{
public:
	CAdsAddArrayDatatype(PCHAR name, CAdsAddDatatype& base, ULONG elements, ULONG lBound=0, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	CAdsAddArrayDatatype(CAdsAddDatatype& base, ULONG elements, ULONG lBound=0, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	virtual ~CAdsAddArrayDatatype();
	virtual ULONG CalcSize();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	virtual	void AppendDescAfterHeader(PAdsDatatypeEntry p);
	CAdsAddDatatype&		m_base;
	AdsDatatypeArrayInfo m_arr;
protected:
	virtual	void TryCalcGuid();
	PCHAR m_arrName;
};

class DLL_EXPORT CAdsAddArray2Datatype : public CAdsAddDatatype
{
public:
	CAdsAddArray2Datatype(PCHAR name, CAdsAddDatatype& base, ULONG elements0, ULONG lBound0, ULONG elements1, ULONG lBound1, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	CAdsAddArray2Datatype(CAdsAddDatatype& base, ULONG elements0, ULONG lBound0, ULONG elements1, ULONG lBound1, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	virtual ~CAdsAddArray2Datatype();
	virtual ULONG CalcSize();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	virtual	void AppendDescAfterHeader(PAdsDatatypeEntry p);
	CAdsAddDatatype&		m_base;
	AdsDatatypeArrayInfo m_arr[2];
protected:
	PCHAR m_arrName;
};

class DLL_EXPORT CAdsAddPointerDatatype : public CAdsAddDatatype
{
public:
	CAdsAddPointerDatatype(PCHAR name, CAdsAddDatatype& base, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	CAdsAddPointerDatatype(CAdsAddDatatype& base, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	virtual ~CAdsAddPointerDatatype();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	CAdsAddDatatype&		m_base;
protected:
	PCHAR m_ptrName;
};

class DLL_EXPORT CAdsAddReferenceDatatype : public CAdsAddDatatype
{
public:
	CAdsAddReferenceDatatype(PCHAR name, CAdsAddDatatype& base, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	CAdsAddReferenceDatatype(CAdsAddDatatype& base, GUID guid=GUID_NULL, DWORD flags=0, PCHAR comment="");
	virtual ~CAdsAddReferenceDatatype();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	CAdsAddDatatype&		m_base;
protected:
	PCHAR m_ptrName;
};

class DLL_EXPORT CAdsAddSymbol
{
public:
	CAdsAddSymbol(PCHAR prefix=NULL, PCHAR name=NULL, CAdsAddDatatype* type=NULL, ULONG igrp=0, ULONG ioffs=0, WORD flags=0, PCHAR comment=NULL, USHORT cntAttr=0, CAdsAddAttribute* pAttr=NULL);
	virtual void Set(PCHAR prefix, PCHAR name, CAdsAddDatatype* type, ULONG igrp=0, ULONG ioffs=0, WORD flags=0, PCHAR comment=NULL);
	virtual void SetAttributes(USHORT cntAttr, CAdsAddAttribute* pAttr);
	virtual ULONG CalcSize();
	virtual void EnumTypes(CHashTableDyn<GUID, CAdsAddDatatype*>& map, bool bExcludeBaseTypes=false);
	virtual ULONG GenerateDesc(PVOID pData);
	PCHAR		m_prefix;
	PCHAR		m_name;
	CAdsAddDatatype*	m_type;
	PCHAR		m_comment;
	WORD		m_flags;
	ULONG		m_igrp;
	ULONG		m_ioffs;
	USHORT				m_cntAttr;
	CAdsAddAttribute*	m_pAttr;
};
DLL_EXPORT HRESULT AllocAdsAddSymbolDesc(ULONG nSym, CAdsAddSymbol** ppSym, PAdsSymbolUpAndDownloadHeader2* ppHead);
DLL_EXPORT void FreeAdsAddSymbolDesc(PAdsSymbolUpAndDownloadHeader2& p);


class CAdsBaseDataTypes
{
public:
	CAdsBaseDataTypes() :
		AdsAddDatatype_BIT("BIT", 1, ADST_BIT, 16, GUID_NULL, ADSDATATYPEFLAG_BITVALUES),
		AdsAddDatatype_SINT("SINT", 1, ADST_INT8, 3),
		AdsAddDatatype_USINT("USINT", 1, ADST_UINT8, 2),
		AdsAddDatatype_BYTE("BYTE", 1, ADST_UINT8, 1),
		AdsAddDatatype_INT("INT", 2, ADST_INT16, 6),
		AdsAddDatatype_UINT("UINT", 2, ADST_UINT16, 5),
		AdsAddDatatype_WORD("WORD", 2, ADST_UINT16, 4),
		AdsAddDatatype_DINT("DINT", 4, ADST_INT32, 9),
		AdsAddDatatype_UDINT("UDINT", 4, ADST_UINT32, 8),
		AdsAddDatatype_DWORD("DWORD", 4, ADST_UINT32, 7),
		AdsAddDatatype_LINT("LINT", 8, ADST_INT64, 12),
		AdsAddDatatype_ULINT("ULINT", 8, ADST_UINT64, 11),
		AdsAddDatatype_LWORD("LWORD", 8, ADST_UINT64, 10),
		AdsAddDatatype_REAL("REAL", 4, ADST_REAL32, 13),
		AdsAddDatatype_LREAL("LREAL", 8, ADST_REAL64, 14),
		AdsAddDatatype_BOOL("BOOL", 1, ADST_UINT8, 48)
	{
	}

	CAdsAddBaseDatatype AdsAddDatatype_BIT;
	CAdsAddBaseDatatype AdsAddDatatype_SINT;
	CAdsAddBaseDatatype AdsAddDatatype_USINT;
	CAdsAddBaseDatatype AdsAddDatatype_BYTE;
	CAdsAddBaseDatatype AdsAddDatatype_INT;
	CAdsAddBaseDatatype AdsAddDatatype_UINT;
	CAdsAddBaseDatatype AdsAddDatatype_WORD;
	CAdsAddBaseDatatype AdsAddDatatype_DINT;
	CAdsAddBaseDatatype AdsAddDatatype_UDINT;
	CAdsAddBaseDatatype AdsAddDatatype_DWORD;
	CAdsAddBaseDatatype AdsAddDatatype_LINT;
	CAdsAddBaseDatatype AdsAddDatatype_ULINT;
	CAdsAddBaseDatatype AdsAddDatatype_LWORD;
	CAdsAddBaseDatatype AdsAddDatatype_REAL;
	CAdsAddBaseDatatype AdsAddDatatype_LREAL;
	CAdsAddBaseDatatype AdsAddDatatype_BOOL;
};

////////////////////////////////////////////////////////////////////////////////

struct DLL_EXPORT CCtrlBase
{
	virtual PVOID	RAllocMem( DWORD nSize )=0;
	virtual PVOID	RAllocMemMustSucceed( DWORD nSize )=0;
	virtual void	RFreeMem( PVOID pVoid )=0;
	virtual BOOL	IsRMem( PVOID pVoid )=0;
	virtual DWORD	RMaxAllocMem()=0;
	virtual	BOOL	InWindows()=0;
	virtual __int64 RtGetCurSystemTime()=0;
};

///////////////////////////////////////////////////////////////////////////////
// CR0Archive
#define		R0ARCHIVEINVOKEID_BOOTOPEN				0xF7000000
#define		R0ARCHIVEINVOKEID_BOOTSAVE_WRITING	0xF8000000
#define		R0ARCHIVEINVOKEID_BOOTLOAD_READING	0xF9000000
#define		R0ARCHIVEINVOKEID_BOOTCLOSE			0xFA000000

class DLL_EXPORT CR0Archive : public CAdsArchive
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CR0Archive( ITComArchiveServer* ipServer, Mode nMode, ULONG nBufSize = 0x4000 );
	CR0Archive( ITComArchiveServer* ipServer, ULONG handle, Mode nMode, ULONG nBufSize = 0x4000 );
	virtual	~CR0Archive();

	virtual void	Flush();
	virtual void	ReadBuffer();
	virtual void	OnBufferEmpty();
	virtual void	OnBufferFull();
	virtual bool	IncreaseBufferSize(ULONG nBufSize);
	virtual bool	EnsureBytesInBuffer(ULONG nBytes);
	virtual PVOID	ReadInBuffer(ULONG nData);
	virtual bool	ReadWithoutIncrement(PVOID pData, ULONG nData);
	virtual void	ClearBuffer();

protected:
	ITComArchiveServerPtr	m_spServer;
	ULONG							m_handle;
};

#define ADSCFG_TIMEOUT		60000 //ms

enum CADSCTRL_INVOKEID
{
	LOADSAVECFGSTATE_READY		= 0x0000,
	SAVECFGSTATE_OPENING			= 0x1001,
	SAVECFGSTATE_WRITING			= 0x1002,
	SAVECFGSTATE_CLOSING			= 0x1003,
	LOADCFGSTATE_OPENING			= 0x1004,
	LOADCFGSTATE_READING			= 0x1005,
	LOADCFGSTATE_CLOSING			= 0x1006,
	SAVECFGSTATE_SEEKING			= 0x1007,
	LOADCFGSTATE_TELLING			= 0x1008,
	ADSLOGMESSAGE_REQ				= 0x2001,
};

#define	MAXCONFIGBLOCKSIZE	65535

///////////////////////////////////////////////////////////////////////////////
class	DLL_EXPORT CAdsR0Port : public CAdsWatchServerR0, public CAmsR0Port, public CAdsLog
{
public:

	CAdsR0Port();
	CAdsR0Port(AmsPortNo nPort, LPCSTR pszPortName=NULL, DWORD	dwAttrib=PORTATTRIB_ADS );
	virtual ~CAdsR0Port();

	virtual	void		AmsReceive( PAmsCmd pCmd );
	virtual	void		AdsGetTime( __int64& nTime );
	virtual	__int64	AdsGetTime();
	virtual	LONG		AdsLogMessage( CAdsLogMessage& rLogMess );
	virtual	char*		AdsLogDeviceName();
	virtual	void		AdsReadWriteInd( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
							ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength,  PVOID pData );
	virtual	int		AdsReadRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int		AdsReadWriteRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG cbLength, PVOID pData );
	virtual	int		AdsAddDeviceNotificationRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, ULONG handle );
	virtual	int		AdsDelDeviceNotificationRes( AmsAddr& rAddr, ULONG invokeId, ULONG nResult );
protected:
	virtual	int		AmsSend__(PAmsCmd pCmd) { return CAmsR0Port::AmsSend(pCmd) == TRUE ? ADSERR_NOERR : CAmsR0Port::AmsGetLastError(); }
	virtual	AmsAddr	GetAmsAddr__() { return CAmsR0Port::AmsGetAddr(); }
	virtual	void		OnAmsReceive( PAmsCmd pCmd );
	// generic ads functions
	virtual	int		AdsRequest( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData );
	virtual	int		AdsForward( AmsAddr& rSrcAddr, AmsAddr& rDestAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData );
	virtual	int		AdsResponse( AmsAddr& rAddr, ULONG invokeId, USHORT serviceId, ULONG cbLength, PVOID pData );

	virtual	void*		AdsAlloc( ULONG size );
	virtual	void		AdsFree( void* pVoid );
	virtual	PAmsAdsReadRwRes	AdsAllocOptReadOrRwRes(ULONG cbLength, ULONG result=ADSERR_NOERR);
	virtual	int		AdsOptReadOrRwResAndFree(BOOL bRW, AmsAddr& rAddr, ULONG invokeId, PAmsAdsReadRwRes pRes); // pRes must be allocated via AdsAllocOptReadOrRwRes
	virtual	int		AdsAddDeviceNotificationSumUpRes(ULONG invokeId, ULONG nResult, ULONG handle);
	virtual	CAdsLog*	GetAdsLog();
};

///////////////////////////////////////////////////////////////////////////////
class	DLL_EXPORT CAdsR0FifoPort : public CAdsR0Port
{
public:

	CAdsR0FifoPort();

	CAdsR0FifoPort(AmsPortNo nPort, LPCSTR pszPortName=NULL, DWORD	dwAttrib=PORTATTRIB_ADS );

	virtual ~CAdsR0FifoPort();

	virtual	HRESULT	InitAmsPort(ITComObjectServer* ipSrv, AmsPortNo port=AMSPORT_USEDEFAULT, AMSPORT_TYPE type=PORTTYPE_INVALID, bool bNoConnect=false);
	virtual	HRESULT	ShutdownAmsPort();

	virtual	void	AmsReceive( PAmsCmd pCmd );
	virtual	void	CheckOrders();
	
protected:
	
	ITcRTimePtr										m_spRTime;
	CFiFoList<PAmsCmd, MAXPOINTERS>*			m_pFifoBox;

};
