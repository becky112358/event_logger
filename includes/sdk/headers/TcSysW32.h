///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef TC_ENVIRONMENT_OS
#include "TcOsDefMacros.h"
#endif // TC_ENVIRONMENT_OS

/* Forward Declarations */ 
typedef interface ITcCtrl ITcCtrl;
typedef interface ITcAmsRouter ITcAmsRouter;

#include "TcBase.h"
#include "Ams.h"
#include "Ads.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declaration
typedef struct RouterR0Funcs* PRouterR0Funcs;
extern PRouterR0Funcs g_pRouterFuncs;

#if !defined(_WCEATL_H_)
#ifndef DECLSPEC_NOVTABLE
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_NOVTABLE __declspec(novtable)
#else
#define DECLSPEC_NOVTABLE
#endif
#endif

#ifndef DECLSPEC_UUID
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_UUID(x) __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif
#endif

#ifndef MIDL_INTERFACE
#define MIDL_INTERFACE(x)   struct DECLSPEC_UUID(x) DECLSPEC_NOVTABLE
#endif
#endif // UNDER_CE

#ifndef TC_ENVIRONMENT_OS
EXTERN_C const IID IID_ITcAds;
MIDL_INTERFACE("29EFABB6-E371-4785-8E80-A3639AEB138E")
ITcAds : public IUnknown
{
public:
	// ads basic requests
	STDMETHOD(AdsWriteReq)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbLength, PVOID pData)=0;
	STDMETHOD(AdsReadReq)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbLength)=0;
	STDMETHOD(AdsReadWriteReq)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, 
										PVOID pData)=0;
	STDMETHOD(AdsNotificationReq)(AmsAddr& rAddr, ULONG invokeId,
													  ULONG cbLength,
													  AdsNotificationStream notifications[])=0;

	// ads basic indications
	STDMETHOD(AdsWriteInd)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbLength, PVOID pData)=0;
	STDMETHOD(AdsReadInd)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbLength)=0;
	STDMETHOD(AdsReadWriteInd)(AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup,
										ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, 
										PVOID pData)=0;
	STDMETHOD(AdsDeviceNotificationInd)(AmsAddr& rAddr, ULONG invokeId,
														ULONG cbLength,
														AdsNotificationStream* pNotifications)=0;


	// ads basic forwards
	STDMETHOD(AdsWriteFrw)(AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr,
														ULONG invokeId, ULONG indexGroup,
															ULONG indexOffset, ULONG cbLength,
																PVOID pData)=0;
	STDMETHOD(AdsReadFrw)(AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr,
														ULONG invokeId, ULONG indexGroup,
															ULONG indexOffset, ULONG cbLength)=0;
	STDMETHOD(AdsReadWriteFrw)(AmsAddr& rSrcAddr, AmsAddr& rNewDestAddr,
															ULONG invokeId, ULONG indexGroup,
																ULONG indexOffset, ULONG cbReadLength,
																	ULONG cbWriteLength, PVOID pData)=0;
	STDMETHOD(AdsDeviceNotificationFrw)( AmsAddr& rSrcAddr,
																	 AmsAddr& rNewDestAddr,
																	 ULONG invokeId,
																	 ULONG cbLength,
																	 AdsNotificationStream* pNotifications)=0;

	// ads basic responses
	STDMETHOD(AdsWriteRes)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult)=0;
	STDMETHOD(AdsReadRes)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult,
									ULONG cbLength, PVOID pData)=0;
	STDMETHOD(AdsReadWriteRes)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult,
									ULONG cbLength, PVOID pData)=0;

	// ads basic confirmations
	STDMETHOD(AdsWriteCon)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult)=0;
	STDMETHOD(AdsReadCon)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult,
										ULONG cbLength, PVOID pData)=0;
	STDMETHOD(AdsReadWriteCon)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult,
										ULONG cbLength, PVOID pData)=0;
	STDMETHOD(AdsDeviceNotificationCon)(AmsAddr& rAddr, ULONG invokeId, ULONG nResult)=0;
};
#endif // !TC_ENVIRONMENT_OS

EXTERN_C const IID IID_ITcCtrl;
MIDL_INTERFACE("DD2974A6-A124-4507-8590-8B2B50248E63")
ITcCtrl : public IUnknown
{
public:
	STDMETHOD(Register)(/*[in]*/PRouterR0Funcs pRouterFuncs,
									/*[out]*/ PAmsPortNo pwPortNo)=0;
  
	STDMETHOD(Unregister)(void)=0;
  
	STDMETHOD(Init)(/*[in]*/ PAmsNetId pNetId)=0;

	STDMETHOD(Shutdown)( void)=0;
	
	STDMETHOD(ShutdownSysComponent)( void)=0;

	STDMETHOD(CheckTwinCATLevel)(TCATInstLevels nInstLevel)=0;
};

EXTERN_C const IID IID_ITcCtrlAdsState;
MIDL_INTERFACE("029B83C1-7A55-4490-A6BB-AE69BE370F8F")
ITcCtrlAdsState : public IUnknown
{
public:
	STDMETHOD(NotifyRequestedAdsState) (ADSSTATE);
};

EXTERN_C const IID IID_ITcRouterRtParams;
MIDL_INTERFACE("D5956D6D-16FF-4EF5-A61C-3453A22A3C7A")
ITcRouterRtParams : public IUnknown
{
public:
	STDMETHOD(SetRtParms)(void* p, size_t nSize);
};

EXTERN_C const IID IID_ITcUserCtrl;
MIDL_INTERFACE("619291B1-685B-4e65-AEC1-F03C04B2F677")
ITcUserCtrl : public ITcCtrl
{
public:	
	STDMETHOD(StartServer)(BSTR sModuleName) = 0;
};
  
EXTERN_C const IID IID_ITcUserCtrl2;
MIDL_INTERFACE("1E6CFBE0-E239-4c38-BE41-552720595991")
ITcUserCtrl2 : public ITcUserCtrl
{
public:	
	STDMETHOD(SetPath)(BSTR pPath);
	STDMETHOD(SetAdsInfo)(USHORT adsPort, ULONG indexGroup);
};

struct TcRouterCtrlInfo;
struct CheckLicenseInfoStruct;
struct ITComRouter;
EXTERN_C const IID IID_ITcCtrl2;
MIDL_INTERFACE("DD2973A6-A124-4507-8590-8B2B50248E63")
ITcCtrl2 : public IUnknown
{
public:
	STDMETHOD(CheckFrameworkVersion)(/*[in]*/AdsVersion sysSrvVersion, /*[out]*/ AdsVersion* pDrvVersion)=0;
};
  
EXTERN_C const IID IID_ITcAmsRouter;
MIDL_INTERFACE("9C82C0BB-2F6D-4620-B03C-AA2DF41EA4B2")
ITcAmsRouter : public ITcCtrl
{
public:
	STDMETHOD(InitRouter)(/*[in]*/ TcRouterCtrlInfo* pCtrlInfo,
								/*[out]*/ PRouterR0Funcs* ppRouterFuncs)=0;
	STDMETHOD(ActivateRouter)()=0;
	STDMETHOD(DeactivateRouter)()=0;
	STDMETHOD(RouteCmdW32)(/*[in]*/ PAmsCmd pCmd)=0;
	STDMETHOD(SignalSystemStart)()=0;
	STDMETHOD(SignalSystemStop)()=0;
	STDMETHOD(SignalSystemStopped)()=0;
	STDMETHOD(CheckSystemLicenses)(CheckLicenseInfoStruct* pInfo, ULONG nInfo)=0;
};

EXTERN_C const IID IID_ITcAmsRouterUserDb;
MIDL_INTERFACE("FB21B6C0-6E1E-485B-A58A-1C9F5AA398F8")
ITcAmsRouterUserDb : public IUnknown
{
public:
	STDMETHOD(SetUserDbHash)(PVOID pHash, ULONG nHash)=0;
};

EXTERN_C const IID IID_ITcAmsRouterLicense;
MIDL_INTERFACE("6BF35223-AD1E-49BE-B8E9-A7A6559B6110")
ITcAmsRouterLicense : public IUnknown
{
public:
	STDMETHOD(GetLicenseSystemId)(GUID* pSysId)=0;
};

EXTERN_C const IID IID_ITcAmsRouter2;
MIDL_INTERFACE("E96E812A-5841-4655-BC7A-13DC774E1618")
ITcAmsRouter2 : public IUnknown
{
public:
	STDMETHOD(ActivateRouter2)(DWORD flags)=0;
};

EXTERN_C const IID IID_ITcW32Router;
MIDL_INTERFACE("9B77F2A8-68DF-4484-B68F-963F05415066")
ITcW32Router : public IUnknown
{
public:
	STDMETHOD(ActivateForProcess)(/*[out]*/ PRouterR0Funcs* ppRouterFuncs,
											/*[out]*/ PVOID* ppMemBaseAddr)=0;
	STDMETHOD(ShutdownForProcess)()=0;
	STDMETHOD(GetRouterMemBase)(/*[out]*/ PVOID* ppMemBaseAddr)=0;
};

#if defined(WIN32_RUNTIME) || defined(POSIX)
typedef CComQIPtr<ITcCtrl> ITcCtrlPtr;
typedef CComQIPtr<ITcCtrl2> ITcCtrl2Ptr;
typedef CComQIPtr<ITcCtrlAdsState> ITcCtrlAdsStatePtr;
typedef CComQIPtr<ITcRouterRtParams> ITcRouterRtParamsPtr;
typedef CComQIPtr<ITcW32Router> ITcW32RouterPtr;
typedef CComQIPtr<ITcUserCtrl> ITcUserCtrlPtr;
typedef CComQIPtr<ITcUserCtrl2> ITcUserCtrl2Ptr;
#endif


