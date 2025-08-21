///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// includes
#include "TcDef.h"
#include "TcMath/fpu_statuscontrol.h"

#if !defined(TC_ENVIRONMENT_OS)
////////////////////////////////////////////////////////////////////////////////
//	common definitions, variables, types 
typedef struct
{
	ULONG		dwIoControlCode; 
	PVOID		pInBuf;
	ULONG		cbInBufSize;
	PVOID		pOutBuf;
	ULONG		cbOutBufSize;
	PULONG	pReserved;	// pDwRet don't use!!!!!!
	PIRP		pIrp;
	PVOID		pFileObject;
} IOCTL_PARAMETERS, *PIOCTL_PARAMETERS;

typedef struct
{
	PVOID		pInBuf;
	ULONG		dwBytesToWrite;
	union
	{
		ULONG		dwOffset;
		ULONG		dwPort;
	};
	PULONG_PTR	pdwBytesWritten;
	PIRP	pIrp;
	PVOID pFileObject;
} WRITEFILE_PARAMETERS, *PWRITEFILE_PARAMETERS;

typedef struct
{
	PVOID		pOutBuf;
	ULONG		dwBytesToRead;
	union
	{
		ULONG		dwOffset;
		ULONG		dwPort;
	};
	PULONG_PTR	pdwBytesRead;
	PIRP	pIrp;
	PVOID pFileObject;
} READFILE_PARAMETERS, *PREADFILE_PARAMETERS;
#endif // !defined(TC_ENVIRONMENT_OS)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// WinNt	driver framework
#ifdef WINNT

///////////////////////////////////////////////////////////////////////////////
// macros

#define OK_ALLOCATED(obj) \
   ((obj!=(void *)0) && NT_SUCCESS((obj)->m_status))


#define DECLARE_GENERIC_DEVICE(devName)\
	PCHAR TCFRAMEWORKAPI GetDeviceName( void )\
		{\
		return (devName##_NAME);\
		}\
	CGenDrv* TCFRAMEWORKAPI CreateGenDrv( void )\
		{\
		return (CGenDrv*) new DEVICE_CLASS;\
		}
 
VOID IoComplete( IN PIRP pIrp, IOSTATUS status=FALSE );											  
VOID IoPending( IN PIRP pIrp );
VOID IoCancel( IN PIRP pIrp );

typedef __declspec(align(16)) struct {
	char buffer[512];
} FXSAVE_STATE;

VOID DpcSaveExtContext(	FXSAVE_STATE* pBuffer, DWORD_PTR* pOldCR0 );
VOID DpcRestoreExtContext( FXSAVE_STATE* pBuffer, DWORD_PTR oldCR0 );

VOID DpcSaveFpuContext(	FPU_STATE* pFpuBuffer, DWORD_PTR* pOldCR0 );
VOID DpcRestoreFpuContext(	FPU_STATE* pFpuBuffer, DWORD_PTR oldCR0 );
VOID SpinLockSaveFpuContext( FPU_STATE* pFpuBuffer, DWORD_PTR* pOldCR0, PVOID pIrql );
VOID SpinLockRestoreFpuContext( FPU_STATE* pFpuBuffer, DWORD_PTR oldCR0, PVOID pIrql );
VOID AcquireSpinLock( PKIRQL pNewIrql );
VOID ReleaseSpinLock( KIRQL newIrql );

VOID SetResourceMap( IN PCM_PARTIAL_RESOURCE_DESCRIPTOR pResourceDescriptorIsa, 
						   IN ULONG nCountOfPartialsIsa, 
							IN PCM_PARTIAL_RESOURCE_DESCRIPTOR pResourceDescriptorPci, 
						   IN ULONG nCountOfPartialsPci, 
							OUT BOOL* pConfictDetected );
PVOID	GetDriverStartAddr();
BOOL GetDriverInfo(PSTR sModuleName, ULONG nModuleName, PULONG_PTR pImageBase, PULONG pImageSize);
BOOL GetDriverImagePath(PSTR sImagePath, ULONG nImagePath);

///////////////////////////////////////////////////////////////////////////////
// CGenDrv
// base class for generic device implementation
class CUString;
class CGenDrv
{
public:
	CGenDrv();
	virtual ~CGenDrv();

	static		char*					m_pszDeviceObjectName;
	static		char*					m_pszImagePath;
					PKSPIN_LOCK			m_pSpinLock;
					PDRIVER_OBJECT		m_pDriverObject;
					PDEVICE_OBJECT 	m_pDeviceObject;

	// thunks
	static	IOSTATUS	OnIoRequestThunk( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp );
	static	IOSTATUS	OnLoadThunk( IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath );
	static	void		OnUnLoadThunk( IN PDRIVER_OBJECT DriverObject );
	static	IOSTATUS OnCleanupThunk( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp );
	static	IOSTATUS OnShutDownThunk( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp );
	static	ULONG IrpHasToBeCancelled( IN PIRP pIrp2Cancel, IN PIRP pCleanUpIrp );

#ifdef WIN2000_TEST
	static	IOSTATUS OnAddDeviceThunk( IN PDRIVER_OBJECT DriverObject, IN OUT PDEVICE_OBJECT *PpDeviceObject );
#endif

protected:
	// overridables
	virtual	IOSTATUS	OnIoRequest( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp );
	virtual	IOSTATUS	OnIoControl(IOCTL_PARAMETERS& ioCtlParm ) = 0;
	virtual	IOSTATUS	OnWriteFile( WRITEFILE_PARAMETERS& wrFileParm );
	virtual	IOSTATUS	OnReadFile( READFILE_PARAMETERS& rdFileParm );
	virtual	IOSTATUS	OnOpen( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp );
	virtual	IOSTATUS	OnClose( IN PDEVICE_OBJECT pDeviceObject, IN PIRP pIrp, PVOID pFileObject );
	virtual	IOSTATUS	OnLoadNt( IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath );
	virtual	VOID		OnUnLoadNt( IN PDRIVER_OBJECT DriverObject );
	virtual	IOSTATUS	OnLoad( );
	virtual	VOID		OnUnLoad( );
	virtual	VOID		OnCleanup( IN PIRP pIrp );
	virtual	IOSTATUS	OnSystemShutdown( );
	// helper
private:

protected:
	BOOL	IsValidRouterFunc(PVOID pFunc);
	BOOL	m_bDriverRegistered;
};

///////////////////////////////////////////////////////////////////////////////
// device extension for nt device objects
class CNtDrvDeviceExt
{
public:
	CNtDrvDeviceExt();
	~CNtDrvDeviceExt();
};

#define Begin_VxD_Service_Table(deviceName)
#define End_VxD_Service_Table
#define VxD_Service(serviceName)
#endif // WINNT

#if defined(WIN32_RUNTIME)	|| defined(TC_ENVIRONMENT_OS)

typedef __declspec(align(16)) struct {
	char buffer[512];
} FXSAVE_STATE;

#if defined(TC_ENVIRONMENT_OS)
#define IoComplete(pIrp)	OsIoComplete(pIrp)
#define IoCancel(pIrp)		OsIoCancel(pIrp)
#else
#define IoComplete(pIrp)	((void)(pIrp))
#define IoCancel(pIrp)		((void)(pIrp))
#endif
#define IoPending(pIrp)		((void)(pIrp))

#define DpcSaveExtContext(	pBuffer,pOldCR0 )	 	 ((void)(pBuffer,pOldCR0))
#define DpcRestoreExtContext( pBuffer, oldCR0 )  ((void)(pBuffer,oldCR0))

#define DpcSaveFpuContext(pFpuBuffer,pOldCR0)	((void)(pFpuBuffer,pOldCR0))
#define DpcRestoreFpuContext(pFpuBuffer,oldCR0)	((void)(pFpuBuffer,oldCR0))
#define SpinLockSaveFpuContext(pFpuBuffer,pOldCR0,pIrql)		((void)(pFpuBuffer,pOldCR0,pIrql))
#define SpinLockRestoreFpuContext(pFpuBuffer,oldCR0,pIrql)	((void)(pFpuBuffer,oldCR0,pIrql))
#define AcquireSpinLock(x) ((void)(x))
#define ReleaseSpinLock(x)	((void)(x))

#endif
