///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include "TcBase.h"
#include "TcInterfaces.h"
#include "TcIoInterfaces.h"
#include "TcRouterServices.h"
#include "TcRtInterfaces.h"

struct ITcRTime;
struct	__declspec(novtable)	ITComRouter : public ITcUnknown
{
	virtual	BOOL			RegisterR0Funcs( WORD drvId, PVOID pFuncs ) = 0;
	virtual	BOOL			UnRegisterR0Funcs( WORD drvId ) = 0;
	virtual	BOOL			RegisterR0Port( struct AmsRegisterR0PortIn* pIn ) = 0;
	virtual	BOOL			UnRegisterR0Port( AmsPortNo port ) = 0;
	virtual	long			RouteCmd( PAmsCmd pCmd ) = 0;
	virtual	PVOID			RAllocMem( DWORD nSize ) = 0;
	virtual	void			RFreeMem( PVOID pVoid ) = 0;
	virtual	DWORD			RMaxAllocMem( ) = 0;
	virtual	PVOID			GetR0Funcs( WORD drvId ) = 0;
	virtual	BOOL			RegisterR0TpPort( struct AmsRegisterTpPortIn* pTp ) = 0;
	virtual	BOOL			UnRegisterR0TpPort( AmsNetId& netId ) = 0;
	virtual	AmsPortNo	GeneratePort( ) = 0;
	virtual	PVOID			RAllocMemMustSucceed(DWORD nSize) = 0;
	virtual	void			GetLocalNetId(AmsNetId& localNetId) = 0;
	virtual	void			RegisterRTimeInterface(ITcRTime* ipRTime) = 0;
	virtual	BOOL			IsRouterMem( PVOID pVoid ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComRouter, IID_ITComRouter);

struct	__declspec(novtable)	ITComPort : public ITcUnknown
{
	virtual void		AmsPortReceive( PAmsCmd pCmd ) = 0;	// called by router
	virtual void		ProcessOrder(PAmsCmd pCmd) = 0; // called by aux task (caller deletes pCmd)
	virtual PVOID		GetImagePtr( PVOID pThis, BOOL bInput, ULONG nSize ) = 0;
	virtual ULONG		InitiateMapping( PVOID pThis, BOOL bInput ) = 0;
	virtual HRESULT	GetPort(AmsPortNo& wPort) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComPort, IID_ITComPort);

struct __declspec(novtable) IQueueOwner : public ITcUnknown
{
	virtual OSHDLQUEUE GetQHandle() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(IQueueOwner, IID_IQueueOwner);

struct	__declspec(novtable) ITComEventConsumer : public ITcUnknown
{
	TCOMMETHOD(EventCallback(UINT uiEventId, ITcUnknown* ipCaller, PVOID pvEventArgs, DWORD dwContext));
};
_TCOM_SMARTPTR_TYPEDEF(ITComEventConsumer, IID_ITComEventConsumer);

struct	__declspec(novtable) ITComEventServer : public ITcUnknown
{
	TCOMMETHOD(RegisterEventConsumer(UINT uiEventId, ITComEventConsumer* ipConsumer, DWORD dwContext));
	TCOMMETHOD(RemoveEventConsumer(UINT uiEventId, ITComEventConsumer* ipConsumer));

	TCOMMETHOD(PostEvent(UINT uiEventId, ITcUnknown* ipCaller, PVOID pvEventArgs));
};
_TCOM_SMARTPTR_TYPEDEF(ITComEventServer, IID_ITComEventServer);

struct ITcMemoryManager;
struct	__declspec(novtable)	ITComRouterMemory : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetTcMemoryManager(ITcMemoryManager** pipMemMan)=0; 	
};
_TCOM_SMARTPTR_TYPEDEF(ITComRouterMemory, IID_ITComRouterMemory);

struct ITcMemoryManager2;
struct	__declspec(novtable)	ITComRouterMemory2 : public ITComRouterMemory
{
	virtual	HRESULT	TCOMAPI	GetTcMemoryManager2(ITcMemoryManager2** pipMemMan)=0; 	
};
_TCOM_SMARTPTR_TYPEDEF(ITComRouterMemory2, IID_ITComRouterMemory2);


