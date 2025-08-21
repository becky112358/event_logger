///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Ads.h"
#include "AdsR0.h"
#include "TcInterfaces.h"
#include "HashTable.h"
#include "TcRtInterfaces.h"
#include "TcDbgUnit.h"
#ifdef _ARM_
#include "ArmHelper.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Forward declaration
typedef struct RouterR0Funcs* PRouterR0Funcs;



template<class T>
HRESULT Create(ITCID iid, PPVOID pipItf) {
	HRESULT hr =  ADS_E_NOMEMORY;
	T* pObj = new T();
	if (pObj)
	{
		if ( FAILED( hr = pObj->TcQueryInterface(iid, pipItf) ) )
		{
			delete pObj;
		}
	}
	return hr;
}

enum TcClassMapEntries
{
	TCCME_CLSID,
	TCCME_CLASS,
	TCCME_NAME,
	TCCME_RT_ALLOC,
};

#define	DECLARE_CLASS_MAP() \
virtual	HRESULT TcHandleClassMap( TcClassMapEntries mode, int idx, PCTCID pClsId, PITCID pIid, PPVOID pipItf, PCHAR* ppName );

#define	BEGIN_CLASS_MAP(theFactory) \
HRESULT theFactory::TcHandleClassMap( TcClassMapEntries mode, int idx, PCTCID pClsId, PITCID pIid, PPVOID pipItf, PCHAR* ppName ) \
{	volatile bool bForceDebugging = false; HRESULT hr=S_OK; int i=0; \
	if ( pClsId == NULL || (mode == TCCME_CLASS && pIid == NULL) || (mode == TCCME_NAME && ppName == NULL) ) return E_POINTER; 

#define	CLASS_ENTRY(cid, name, cls) \
	if ( mode == TCCME_CLSID ) { \
		if ( idx == i ) \
			{ *pClsId = cid; return hr; } \
		++i; } \
	if ( mode == TCCME_CLASS && *pClsId == cid ) \
		{ hr = Create<cls>(*pIid, pipItf); return hr; } \
	if ( mode == TCCME_NAME && *pClsId == cid ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCCME_RT_ALLOC && *pClsId == cid ) \
		{ return ADS_E_INVALIDCONTEXT; }

#define	CLASS_ENTRY_RT(cid, name, cls) \
	if ( mode == TCCME_CLSID ) { \
		if ( idx == i ) \
			{ *pClsId = cid; return hr; } \
		++i; } \
	if ( mode == TCCME_CLASS && *pClsId == cid ) \
		{ hr = Create<cls>(*pIid, pipItf); return hr; } \
	if ( mode == TCCME_NAME && *pClsId == cid ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCCME_RT_ALLOC && *pClsId == cid ) \
		{ return S_OK; } 

#define	CLASS_ENTRY_LIB(vid, cid, name, cls) \
	if ( mode == TCCME_CLSID ) { \
		if ( idx == i ) \
			{ _XorGuids(pClsId, cid, vid); return hr; } \
		++i; } \
	if ( mode == TCCME_CLASS && _CmpXorGuids(pClsId, cid, vid) ) \
		{ hr = Create<cls>(*pIid, pipItf); return hr; } \
	if ( mode == TCCME_NAME && _CmpXorGuids(pClsId, cid, vid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCCME_RT_ALLOC && _CmpXorGuids(pClsId, cid, vid) ) \
		{ return ADS_E_INVALIDCONTEXT; }

#define	CLASS_ENTRY_LIB_RT(vid, cid, name, cls) \
	if ( mode == TCCME_CLSID ) { \
		if ( idx == i ) \
			{ _XorGuids(pClsId, cid, vid); return hr; } \
		++i; } \
	if ( mode == TCCME_CLASS && _CmpXorGuids(pClsId, cid, vid) ) \
		{ hr = Create<cls>(*pIid, pipItf); return hr; } \
	if ( mode == TCCME_NAME && _CmpXorGuids(pClsId, cid, vid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCCME_RT_ALLOC && _CmpXorGuids(pClsId, cid, vid) ) \
		{ return S_OK; }

#define DECLARE_REPOSITORY_DRIVER() \
	virtual const char* GetRepositoryDriverIdName(); 

#define DEFINE_REPOSITORY_DRIVER(ClassFactory, LibraryIdNameStr) \
	const char* ClassFactory::GetRepositoryDriverIdName() { return LibraryIdNameStr; }

#ifndef POSIX

#ifdef _X64_
#define FORCELOCALTHUNK4DEBUGGING()\
	{localThunk(); emptyExecutableMemory();}
#else
#ifdef _ARM_
#define FORCELOCALTHUNK4DEBUGGING()\
	localThunkArm();
#else
#define FORCELOCALTHUNK4DEBUGGING() (void)(0);
#endif
#endif

#else

#define FORCELOCALTHUNK4DEBUGGING() (void)(0);

#endif // !POSIX

#define	END_CLASS_MAP() \
	if ( mode == TCCME_CLSID ) \
		hr = S_FALSE; \
	else \
		hr = ADS_E_INVALIDCLSID; \
	if(bForceDebugging)\
		FORCELOCALTHUNK4DEBUGGING()\
	return hr; \
}

enum TcFuncMapEntries
{
	TCFME_FTCID,
	TCFME_FUNC,
	TCFME_METHOD,
	TCFME_NAME,
	TCFME_SIGNATURE,
	TCFME_VERSION,
};

#define	TCFNCMETHOD_MAIN		"MAIN"
#define	TCFNCMETHOD_FBINIT	"FB_INIT"

__inline BOOL TcFncCompareId(PFTCID pFncId, PCHAR pMethod, PFTCID pCompId)
{
	if ( pMethod && strcmp(pMethod, TCFNCMETHOD_MAIN) != 0 )
	{
		FTCID fncId = *pFncId;
		size_t len = strlen(pMethod);
		for ( size_t i=0; i < len; i++ )
			((PBYTE)&fncId)[i%16] ^= pMethod[i];
		return fncId == *pCompId;
	}
	else
		return *pFncId == *pCompId;
}

__inline BOOL TcFncCompareIdLib(PFTCID pFncId, PCHAR pMethod, PFTCID pCompId, PFTCID pVerId)
{
	if ( pMethod && strcmp(pMethod, TCFNCMETHOD_MAIN) != 0 )
	{
		FTCID fncId = *pFncId;
		size_t len = strlen(pMethod);
		for ( size_t i=0; i < len; i++ )
			((PBYTE)&fncId)[i%16] ^= pMethod[i];
		return _CmpXorGuids(&fncId, *pCompId, *pVerId);
	}
	else
		return _CmpXorGuids(pFncId, *pCompId, *pVerId);
}

#define	DECLARE_FUNC_MAP() \
virtual	HRESULT TcHandleFuncMap( TcFuncMapEntries mode, int idx, PFTCID pFncId, PPVOID pipFnc, PCHAR* ppMethod, PCHAR* ppName, PULONG pSignature, PULONG pVersion );

#define	BEGIN_FUNC_MAP(theFactory) \
HRESULT theFactory::TcHandleFuncMap( TcFuncMapEntries mode, int idx, PFTCID pFncId, PPVOID pipFnc, PCHAR* ppMethod, PCHAR* ppName, PULONG pSignature, PULONG pVersion ) \
{	HRESULT hr=S_OK; int i=0; \
	if ( pFncId == NULL || (mode == TCFME_NAME && ppName == NULL) || (mode == TCFME_METHOD && ppMethod == NULL) || \
		(mode == TCFME_SIGNATURE && pSignature == NULL) || (mode == TCFME_VERSION && pVersion == NULL) ) return E_POINTER; 

#define	FUNC_ENTRY(fid, name, fnc) \
	if ( mode == TCFME_FTCID ) { \
		if( idx == i ) \
			{ *pFncId = fid; if (ppMethod) *ppMethod = NULL; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && *pFncId == fid ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && *pFncId == fid ) \
		{ return ADS_E_NOTINIT; } \
	if ( mode == TCFME_NAME && *pFncId == fid ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && *pFncId == fid ) \
		{ *pSignature = 0; return hr; } \
	if ( mode == TCFME_VERSION && *pFncId == fid ) \
		{ *pVersion = 0; return hr; } 

#define	FUNC_ENTRY_LIB(vid, fid, name, fnc) \
	if ( mode == TCFME_FTCID )	{ \
		if (idx == i ) \
			{ _XorGuids(pFncId, fid, vid); if (ppMethod) *ppMethod = NULL; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && _CmpXorGuids(pFncId, fid, vid) ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && _CmpXorGuids(pFncId, fid, vid) ) \
		{ return ADS_E_NOTINIT; } \
	if ( mode == TCFME_NAME && _CmpXorGuids(pFncId, fid, vid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && _CmpXorGuids(pFncId, fid, vid) ) \
		{ *pSignature = 0; return hr; } \
	if ( mode == TCFME_VERSION && _CmpXorGuids(pFncId, fid, vid) ) \
		{ *pVersion = 0; return hr; } 

#define	FUNC_ENTRY_SV(fid, name, fnc, sig, ver) \
	if ( mode == TCFME_FTCID ) { \
		if ( idx == i ) \
			{ *pFncId = fid; if (ppMethod) *ppMethod = NULL; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && *pFncId == fid ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && *pFncId == fid ) \
		{ return ADS_E_NOTINIT; } \
	if ( mode == TCFME_NAME && *pFncId == fid ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && *pFncId == fid ) \
		{ *pSignature = sig; return hr; } \
	if ( mode == TCFME_VERSION && *pFncId == fid ) \
		{ *pVersion = ver; return hr; } 

#define	FUNC_METHOD_ENTRY(fid, method, name, fnc) \
	if ( mode == TCFME_FTCID ) { \
		if ( idx == i ) \
			{ *pFncId = fid; if (ppMethod) *ppMethod = method; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *ppMethod = method; return hr; } \
	if ( mode == TCFME_NAME && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pSignature = 0; return hr; } \
	if ( mode == TCFME_VERSION && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pVersion = 0; return hr; } 

#define	FUNC_METHOD_ENTRY_LIB(vid, fid, method, name, fnc) \
	if ( mode == TCFME_FTCID ) { \
		if ( idx == i ) \
			{ _XorGuids(pFncId, fid, vid); if (ppMethod) *ppMethod = method; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && TcFncCompareIdLib(pFncId, method, (PFTCID)&fid, (PFTCID)&vid) ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && TcFncCompareIdLib(pFncId, method, (PFTCID)&fid, (PFTCID)&vid) ) \
		{ *ppMethod = method; return hr; } \
	if ( mode == TCFME_NAME && TcFncCompareIdLib(pFncId, method, (PFTCID)&fid, (PFTCID)&vid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && TcFncCompareIdLib(pFncId, method, (PFTCID)&fid, (PFTCID)&vid) ) \
		{ *pSignature = 0; return hr; } \
	if ( mode == TCFME_VERSION && TcFncCompareIdLib(pFncId, method, (PFTCID)&fid, (PFTCID)&vid) ) \
		{ *pVersion = 0; return hr; } 

#define	FUNC_METHOD_ENTRY_SV(fid, method, name, fnc, sig, ver) \
	if ( mode == TCFME_FTCID ) { \
		if ( idx == i ) \
			{ *pFncId = fid; if (ppMethod) *ppMethod = method; return hr; } \
		++i; } \
	if ( mode == TCFME_FUNC && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pipFnc = fnc; return hr; } \
	if ( mode == TCFME_METHOD && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *ppMethod = method; return hr; } \
	if ( mode == TCFME_NAME && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *ppName = name; return hr; } \
	if ( mode == TCFME_SIGNATURE && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pSignature = sig; return hr; } \
	if ( mode == TCFME_VERSION && TcFncCompareId(pFncId, method, (PFTCID)&fid) ) \
		{ *pVersion = ver; return hr; } 

#define	END_FUNC_MAP() \
	if ( mode == TCFME_FTCID ) \
		hr = S_FALSE; \
	else \
		hr = ADS_E_INVALIDCLSID; \
	return hr; \
}

class DLL_EXPORT CObjClassFactory 
	: public CCtrlBase
	, public ITcBaseClassFactory
	, public ITcRtClassFactory
	, public ITComFuncProvider
	, public ITComObjectParent
{
public:
	CObjClassFactory();
	virtual ~CObjClassFactory();

	virtual	void	GetFrameworkVersion(AdsVersion sysSrvVersion, PAdsVersion pOwnVersion);

	virtual	void	ObjManagerConnect(RouterR0Funcs* pRouterFuncs);
	virtual	void	ObjManagerDisconnect();
	virtual	void	InitCtrl( PAmsNetId pNetId, PDWORD pErr );
	virtual	long	OnShutdown();
	virtual void SetRequestedAdsState(ADSSTATE adsState);
	virtual void AfterInitCtrl();
	virtual void BeforeShutdown();

	// ITcUnknown
	DECLARE_IUNKNOWN_NODELETE()

	DECLARE_CLASS_MAP()
	DECLARE_FUNC_MAP()
	// ITcBaseClassFactory
	virtual HRESULT TCOMAPI TcCreateInstance(RCTCID clsId, RITCID iid, PPVOID pipItf);
	virtual HRESULT TCOMAPI TcEnumClassIds(int& idx, RCTCID clsId);
	virtual HRESULT TCOMAPI TcGetClassName(RCTCID clsId, PCHAR* ppClassName);

	// ITcRtClassFactory
	virtual HRESULT TCOMAPI TcRtCreateInstance(RCTCID clsId, RITCID iid, PPVOID pipItf);

	// ITComFuncProvider
	virtual	HRESULT TCOMAPI	TcGetFuncPointer(RFTCID fncId, PPVOID pipFnc, PULONG pSignature=NULL, PULONG pVersion=NULL);
	virtual	HRESULT TCOMAPI	TcReleaseFuncPointer(RFTCID fncId);
	virtual	HRESULT TCOMAPI	TcGetFuncName( RFTCID fncId, PCHAR* ppClassName);

	// ITComObjectParent
	virtual	HRESULT TCOMAPI	AddChildObject(ITcUnknown* ipUnk);
	virtual	HRESULT TCOMAPI	RemoveChildObject(ITcUnknown* ipUnk);

	// wrappers of router-services
	virtual PVOID      RAllocMem( DWORD nSize );
	virtual PVOID      RAllocMemMustSucceed( DWORD nSize );
	virtual void       RFreeMem( PVOID pVoid );
	virtual BOOL       IsRMem( PVOID pVoid );
	virtual DWORD      RMaxAllocMem();
	virtual BOOL       InWindows();
	virtual __int64    RtGetCurSystemTime();

public:
	ITComObjectServerPtr m_spSrv;
	ITComRouterPtr			m_spRouter;
	ITcRTimePtr				m_spRTime;
	static ULONG_PTR addressDebughandler;

protected:
	ADSSTATE					m_reqAdsState;
	AUTO_ULONG				m_refCntParentLock;

	VOID TcDbgUnitSetImageName(PCSTR szImageName);
	VOID TcDbgUnitSetVersion(ULONG nMajor, ULONG nMinor, ULONG nBuild, ULONG nRevision);
	VOID TcDbgUnitSetFlags(TcDbgUnitFlags flags);

	virtual	BOOL	TcEnumFuncIds(int& idx, RFTCID fncId, PCHAR* ppMethod);
	virtual const char* GetRepositoryDriverIdName(); 

#if defined(TC_ENVIRONMENT_OS) || defined(TC_ENVIRONMENT_RT)
	virtual void LateInitialize();
	virtual void ReportOverflowAtexitArr();
#endif

private:
	CTcDbgUnit           m_TcDbgUnit; 
	ULONG				 m_bRtPtrRefFlag;
};

DLL_EXPORT void TCFRAMEWORKAPI localThunk();
DLL_EXPORT void TCFRAMEWORKAPI emptyExecutableMemory();
struct ITcClassFactoryProvider;
class DLL_EXPORT CObjClassFactoryMS : public CObjClassFactory
{
public:
	CObjClassFactoryMS();
	virtual ~CObjClassFactoryMS();

	DECLARE_IUNKNOWN_DERIVED_NODELETE()
private:
	ITcClassFactoryProvider* m_ipCFP;
};


