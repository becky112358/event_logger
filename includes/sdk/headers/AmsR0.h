///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include	"Ams.h"
#include	"FiFo.h"
#include	"TaskServices.h"
#include	"TcRouterInterfaces.h"


#define MAXPOINTERS				100

///////////////////////////////////////////////////////////////////////////////
// CAmsR0Port

typedef void	(*PAmsPortReceive)	( PVOID pThis, PAmsCmd pCmd );
typedef PVOID	(*PGetImagePtr)		( PVOID pThis, BOOL bInput, ULONG nSize );
typedef ULONG	(*PInitiateMapping)	( PVOID pThis, BOOL bInput );

struct AmsR0PortFuncs
{ 
	PVOID						pThis;
	PAmsPortReceive		pAmsPortReceive;
	PGetImagePtr			pGetImagePtr;
	PInitiateMapping		pInitiateMapping;
};
typedef AmsR0PortFuncs *PAmsR0PortFuncs;

struct ITComPort;
///////////////////////////////////////////////////////////////////////////////
//	AmsRegisterR0Port
struct DLL_EXPORT AmsRegisterR0PortIn : public AmsRegisterPort
{
#ifdef __cplusplus
	AmsRegisterR0PortIn
	(
		AmsPortNo port,
		LPCSTR pszName = NULL,
		AMSPORT_TYPE portType = PORTTYPE_R0CTRLPORT,
		AmsR0PortFuncs* pPortFuncs = NULL,
		DWORD dwPortAttrib = PORTATTRIB_SERVER,
		BOOL bFixed = TRUE,
		WORD queueSize = 0x50
	);

	AmsRegisterR0PortIn
	( 
		AmsPortNo port,
		LPCSTR pszName = NULL,
		AMSPORT_TYPE portType = PORTTYPE_R0CTRLPORT,
		ITComPort* ipPort = NULL,
		DWORD dwPortAttrib = PORTATTRIB_SERVER,
		BOOL bFixed = TRUE,
		WORD queueSize = 0x50
	);
#endif // __cplusplus

	union
	{
		AmsR0PortFuncs*	m_pPortFuncs;	
		ITComPort*			m_ipPort;
	};
};
typedef	struct AmsRegisterR0PortIn* PAmsRegisterR0PortIn;

struct DLL_EXPORT AmsRegisterR0PortOut	: public AmsRegisterPortOut
{
};
typedef	struct AmsRegisterR0PortOut* PAmsRegisterR0PortOut;

///////////////////////////////////////////////////////////////////////////////
class DLL_EXPORT CAmsR0Port : public CAmsPort
{
public:
	CAmsR0Port(AmsPortNo port, LPCSTR pszPortName = NULL, AMSPORT_TYPE type = PORTTYPE_INVALID, DWORD	dwAttrib = PORTATTRIB_UNDEF);
	CAmsR0Port();
	virtual	~CAmsR0Port();

	virtual	HRESULT	InitAmsPort(ITComObjectServer* ipSrv, AmsPortNo port=AMSPORT_USEDEFAULT, AMSPORT_TYPE type=PORTTYPE_INVALID, bool bNoConnect=false);
	virtual	HRESULT	InitAmsPort(ITComObjectServer* ipSrv, PCHAR szName, AmsPortNo port=AMSPORT_USEDEFAULT, AMSPORT_TYPE type=PORTTYPE_INVALID, bool bNoConnect=false);
	virtual	HRESULT	ShutdownAmsPort();

	// overrides for CAmsPorts virtual member functions
	virtual	BOOL	AmsSend( PAmsCmd pCmd );
	virtual	void	AmsReceive( PAmsCmd pCmd ) = 0;
	virtual	void	OnAmsReceive( PAmsCmd pCmd );

	virtual	PAmsCmd	AmsAlloc( long size = sizeof(AmsHead) );
	virtual	void	AmsFree( PAmsCmd pCmd );

	// wrappers of router-services
	virtual PVOID	RAllocMem( DWORD nSize );
	virtual PVOID	RAllocMemMustSucceed( DWORD nSize );
	virtual void	RFreeMem( PVOID pVoid );

//	virtual BOOL	IsRMem( PVOID pVoid );
	virtual DWORD	RMaxAllocMem();

protected:
	// extension for R0 ports
	virtual	void	AmsConnect(ITComRouter* ipRouter);
	virtual	void	AmsDisconnect();

	virtual	PAmsNetId	AmsGetOwnTpNetId() {return NULL;}
	virtual	void		AmsRegisterTpPorts() {};
	virtual	void		AmsUnregisterTpPorts() {};
	virtual	void		AmsRegisterTpPort(AmsNetId& netId, PCHAR pName=NULL);
	virtual	void		AmsUnregisterTpPort(AmsNetId netId);

	AmsR0PortFuncs		m_amsR0PortFuncs;
public:
	ITComRouterPtr		m_spRouter;
};
typedef	CAmsR0Port *PCAmsR0Port;

