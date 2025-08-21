///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcSysW32.h"

template <class T, class CtrlBase>
class __declspec(novtable) ITcOCFCtrlImpl :
	public ITcCtrl,
	public ITcCtrl2,
	public CtrlBase
{
public:
	ITcOCFCtrlImpl() : CtrlBase()
	{}
	virtual ~ITcOCFCtrlImpl()
	{}

	STDMETHOD(Register)(PRouterR0Funcs pRouterFuncs, PAmsPortNo pwPortNo)
	{
		ObjManagerConnect( pRouterFuncs );
		return S_OK;
	}
	STDMETHOD(Unregister)()
	{
		ObjManagerDisconnect();
		return S_OK;
	}
	STDMETHOD(Init)(AmsNetId_* pNetId)
	{
		DWORD dwErr = 0;
		HRESULT hr = S_OK;

		InitCtrl( pNetId, &dwErr );
		if( dwErr != 0 )
			hr = S_FALSE;

		return hr;
	}

	STDMETHOD(Shutdown)()
	{
		OnShutdown();

		return ERR_NOERROR; 
	}

	STDMETHOD(ShutdownSysComponent)()
	{
		return ERR_NOERROR; 
	}

	STDMETHOD(CheckTwinCATLevel)(TCATInstLevels nInstLevel)
	{
		return S_OK;
	}

	// ITcCtrl2
	STDMETHOD(Register)(/*[in]*/ITComRouter* ipRouter, /*[out]*/ PAmsPortNo pwPortNo)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(CheckFrameworkVersion)(AdsVersion sysSrvVersion, AdsVersion* pDrvVersion)
	{
		GetFrameworkVersion(sysSrvVersion, pDrvVersion);
		return S_OK;
	}
};


#include "ObjClassFactory.h"
// for the future this class is used by TwinCAT drivers if created with the TwinCAT Wizard
class __declspec(novtable) ITcCtrlImpl :
	 public ITcCtrl
	,public ITcCtrl2
{
public:
	ITcCtrlImpl() : m_pObjClassFactory(NULL)
	{}
	virtual ~ITcCtrlImpl()
	{}

	STDMETHOD(Register)(PRouterR0Funcs pRouterFuncs, USHORT* pwPortNo)
	{
		m_pObjClassFactory->ObjManagerConnect( pRouterFuncs );
		return S_OK;
	}
	STDMETHOD(Unregister)()
	{
		m_pObjClassFactory->ObjManagerDisconnect();
		return S_OK;
	}
	STDMETHOD(Init)(AmsNetId_* pNetId)
	{
		DWORD dwErr = 0;
		HRESULT hr = S_OK;

		m_pObjClassFactory->InitCtrl( pNetId, &dwErr );
		if( dwErr != 0 )
			hr = S_FALSE;

		return hr;
	}

	STDMETHOD(Shutdown)()
	{
		m_pObjClassFactory->OnShutdown();

		return ERR_NOERROR; 
	}

	STDMETHOD(ShutdownSysComponent)()
	{
		return ERR_NOERROR; 
	}

	STDMETHOD(CheckTwinCATLevel)(TCATInstLevels nInstLevel)
	{
		return S_OK;
	}

	// ITcCtrl2
	STDMETHOD(Register)(/*[in]*/ITComRouter* ipRouter, /*[out]*/ PAmsPortNo pwPortNo)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(CheckFrameworkVersion)(AdsVersion sysSrvVersion, AdsVersion* pDrvVersion)
	{
		m_pObjClassFactory->GetFrameworkVersion(sysSrvVersion, pDrvVersion);
		return S_OK;
	}

protected:

	CObjClassFactory*  m_pObjClassFactory;
};
