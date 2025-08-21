///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"
#include "TcServices.h"
#include "Ads.h"
#include "AdsLog.h"
#include "TcBaseInterfaces.h"

#define THIS_CAST(itf)				static_cast<itf*>(this)
#define THIS_ITCOMOBJECT			static_cast<ITComObject*>(this)

typedef struct TComOnTimerValues
{
	ULONG nTimerTicks;
	ULONG nOnTimerMeasureFac;

} T_TComOnTimerValues, *PTComOnTimerValues;

typedef struct TComGlobalLockFuncs
{
	/*PRTime_AcquireGlobalLock pAcquireGlobalLock;
	PRTime_ReleaseGlobalLock pReleaseGlobalLock;*/
} T_TComGlobalLockFuncs, *PTComGlobalLockFuncs;

struct __declspec(novtable) ITComBaseServices : public ITcUnknown
{
	virtual HRESULT GetTComTimerValues(PTComOnTimerValues* ppOnTimerValues) = 0;
	virtual HRESULT GetTComGlobalLockFuncs(PTComGlobalLockFuncs* ppGlobalLockFuncs) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComBaseServices, IID_ITComBaseServices);

struct __declspec(novtable) ITComTimerConsumer : public ITcUnknown
{
	virtual HRESULT TcOnTimer() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComTimerConsumer, IID_ITComTimerConsumer);

struct __declspec(novtable) ITComTimer : public ITcUnknown
{
	virtual HRESULT TcRegisterConsumer(ITComTimerConsumer* ipConsumer, ULONG msec) = 0;
	virtual HRESULT TcRemoveConsumer(ITComTimerConsumer* ipConsumer) = 0;	
};
_TCOM_SMARTPTR_TYPEDEF(ITComTimer, IID_ITComTimer);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComArchiveServer : public ITcUnknown
{
	enum ARCHIVEOPENMODE {
		OPENBOOTPRJ_TOREAD,
		OPENBOOTDATA_TOREAD,
		OPENBOOTPRJ_TOWRITE,
		OPENBOOTDATA_TOWRITE,
		OPENBOOTUSER1_TOREAD,
		OPENBOOTUSER1_TOWRITE,
		OPENBOOTPRJ_TOREAD_RT = 0x10000000 | OPENBOOTPRJ_TOREAD,
		OPENBOOTDATA_TOREAD_RT = 0x10000000 | OPENBOOTDATA_TOREAD,
		OPENBOOTPRJ_TOWRITE_RT = 0x10000000 | OPENBOOTPRJ_TOWRITE,
		OPENBOOTDATA_TOWRITE_RT = 0x10000000 | OPENBOOTDATA_TOWRITE
	};
	virtual	HRESULT	OpenArchive(PCHAR sName, ARCHIVEOPENMODE openMode, ULONG& handle) = 0;
	virtual	HRESULT	CloseArchive(ULONG handle) = 0;
	virtual	HRESULT	WriteToArchive(ULONG handle, PBYTE pData, ULONG nData) = 0;
	virtual	HRESULT	ReadFromArchive(ULONG handle, PBYTE pData, ULONG& nData) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComArchiveServer, IID_ITComArchiveServer);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComArchive : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	Read( PVOID pData, ULONG nData ) = 0;
	virtual	HRESULT TCOMAPI	Write( PVOID pData, ULONG nData ) = 0;
	virtual	HRESULT TCOMAPI	FlushHr() = 0;
	virtual	HRESULT TCOMAPI	GetResult() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComArchive, IID_ITComArchive);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComArchiveOp : public ITComArchive
{
	virtual	ITComArchiveOp& operator<<(int val) = 0;
	virtual	ITComArchiveOp& operator>>(int& val) = 0;
	virtual	ITComArchiveOp& operator<<(UINT val) = 0;
	virtual	ITComArchiveOp& operator>>(UINT& val) = 0;
	virtual	ITComArchiveOp& operator<<(BYTE val) = 0;
	virtual	ITComArchiveOp& operator>>(BYTE& val) = 0;
	virtual	ITComArchiveOp& operator<<(CHAR val) = 0;
	virtual	ITComArchiveOp& operator>>(CHAR& val) = 0;
	virtual	ITComArchiveOp& operator<<(SHORT val) = 0;
	virtual	ITComArchiveOp& operator>>(SHORT& val) = 0;
	virtual	ITComArchiveOp& operator<<(USHORT val) = 0;
	virtual	ITComArchiveOp& operator>>(USHORT& val) = 0;
	virtual	ITComArchiveOp& operator<<(long val) = 0;
	virtual	ITComArchiveOp& operator>>(long& val) = 0;
	virtual	ITComArchiveOp& operator<<(unsigned long val) = 0;
	virtual	ITComArchiveOp& operator>>(unsigned long& val) = 0;
	virtual	ITComArchiveOp& operator<<(float val) = 0;
	virtual	ITComArchiveOp& operator>>(float& val) = 0;
	virtual	ITComArchiveOp& operator<<(double val) = 0;
	virtual	ITComArchiveOp& operator>>(double& val) = 0;
	virtual	ITComArchiveOp& operator<<(bool val) = 0;
	virtual	ITComArchiveOp& operator>>(bool& val) = 0;
	virtual	ITComArchiveOp& operator<<(__int64 val) = 0;
	virtual	ITComArchiveOp& operator>>(__int64& val) = 0;
	virtual	ITComArchiveOp& operator<<(AdsDataTypeId val) = 0;
	virtual	ITComArchiveOp& operator>>(AdsDataTypeId& val) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComArchiveOp, IID_ITComArchiveOp);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComArchiveStream : public ITcUnknown
{
	virtual	char Peek() = 0;
	virtual	char Take() = 0;
	virtual	size_t Tell() = 0;
	virtual	void Put(char c) = 0;
	virtual	void Flush() = 0;
	virtual	char* PutBegin() = 0;
	virtual	size_t PutEnd(char*) = 0;
	// For encoding detection only.
	virtual	const char* Peek4() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComArchiveStream, IID_ITComArchiveStream);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComArchiveStream2 : public ITComArchiveStream
{
	virtual PVOID	ReadInBuffer(ULONG nData) = 0;
	virtual bool	Peek(PVOID pData, ULONG nData) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComArchiveStream2, ITComArchiveStream2);

class CArchiveStream 
{
public:
	typedef char Ch;    //!< Character type (byte).
	CArchiveStream(ITComArchiveStream* ipAr) : spAr(ipAr) {}

	// reading
	Ch Peek() const { return spAr->Peek(); }
	Ch Take() { return spAr->Take(); }
	size_t Tell() const { return spAr->Tell(); }
	// writing
	void Put(Ch c) { spAr->Put(c); }
	void Flush() {	spAr->Flush(); }
	// Not implemented
	Ch* PutBegin() { return 0; }
	size_t PutEnd(Ch*) { return 0; }

private:
	ITComArchiveStreamPtr spAr;
};

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComObjArchiveServer : public ITcUnknown
{
	// CreateObjArchive return values for "bToRead == TRUE:
	// S_OK = actual data available
	// S_OLDBOOTDATA = only old data available
	// ADS_E_NOTFOUND = file not found
	// ADS_E_INCOMPATIBLE = file content incompatible
	// or other error codes
	virtual	HRESULT	TCOMAPI	CreateObjArchive(ITComObject* ipObj, BOOL bToRead, RITCID iid, PPVOID pipItf, ULONG nBufSize = 0x4000, PCHAR pFileName = NULL) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjArchiveServer, IID_ITComObjArchiveServer);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComObjArchiveServer2 : public ITComObjArchiveServer
{
	virtual	HRESULT	TCOMAPI	ExistsObjArchive(OTCID oid, PCHAR pFileName = NULL) = 0;	// S_OK = found, S_FALSE = not found
	virtual	HRESULT	TCOMAPI	DeleteObjArchive(OTCID oid, PCHAR pFileName = NULL) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjArchiveServer2, IID_ITComObjArchiveServer2);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComObjArchiveServer3 : public ITComObjArchiveServer2
{
	enum ARCHIVEOPENPATH {
		OPENPATH_BOOTDATA,
		OPENPATH_USER1,
	};

	virtual	HRESULT	TCOMAPI	CreateObjArchive(ITComObject* ipObj, BOOL bToRead, ARCHIVEOPENPATH openPath, RITCID iid, PPVOID pipItf, ULONG nBufSize = 0x4000, PCHAR pFileName = NULL) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjArchiveServer3, IID_ITComObjArchiveServer3);


struct __declspec(novtable) ITComInterfaceDescServer : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetVTableEntries(RITCID iid, PULONG pCnt) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComInterfaceDescServer, IID_ITComInterfaceDescServer);

///////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComNoPlcWrapper : public ITcUnknown
{	// no methods
};
_TCOM_SMARTPTR_TYPEDEF(ITComNoPlcWrapper, IID_ITComNoPlcWrapper);

///////////////////////////////////////////////////////////////////////////////
// ITcBaseClassFactory
// Base Class Factory -> Create object instances.
///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcBaseClassFactory : public ITcUnknown
{
	TCOMMETHOD(TcCreateInstance( RCTCID clsId, RITCID iid, PPVOID pipItf));
	TCOMMETHOD(TcEnumClassIds(int& idx, RCTCID clsId));
	TCOMMETHOD(TcGetClassName( RCTCID clsId, PCHAR* ppClassName));
};
_TCOM_SMARTPTR_TYPEDEF(ITcBaseClassFactory, IID_ITcBaseClassFactory);

///////////////////////////////////////////////////////////////////////////////
// ITcRtClassFactory
// Base Class Factory -> Create object instances.
///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcRtClassFactory : public ITcUnknown
{
	TCOMMETHOD(TcRtCreateInstance( RCTCID clsId, RITCID iid, PPVOID pipItf));
};
_TCOM_SMARTPTR_TYPEDEF(ITcRtClassFactory, IID_ITcRtClassFactory);


struct ITComObjectServer;
///////////////////////////////////////////////////////////////////////////////
// ITcClassFactory
// class factory receiving callbacks from object manager -> e.g. use TcInitiateClassFactory to initialize object pools
///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcClassFactory : public ITcBaseClassFactory
{
	TCOMMETHOD(TcInitiateClassFactory(ITComObjectServer* ipObjSrv));
	TCOMMETHOD(TcResetClassFactory(ITComObjectServer* ipObjSrv));
	TCOMMETHOD(TcShutdownClassFactory(ITComObjectServer* ipObjSrv));
};
_TCOM_SMARTPTR_TYPEDEF(ITcClassFactory, IID_ITcClassFactory);

#ifdef TCOM_REPOSITORY
///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcLoadRepositoryDriver : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	TcLoadRepositoryDriver(PCHAR szKey, bool bDoubleNullTerminated=false) = 0;
	virtual	HRESULT TCOMAPI	TcUnloadRepositoryDriver(PCHAR szKey, bool bDoubleNullTerminated=false) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcLoadRepositoryDriver, IID_ITcLoadRepositoryDriver);

///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcLockRepositoryDriver : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	TcLockRepositoryDriver(PCCH szKey) = 0;
	virtual	HRESULT TCOMAPI	TcUnlockRepositoryDriver(PCCH szKey) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcLockRepositoryDriver, IID_ITcLockRepositoryDriver);
#endif

///////////////////////////////////////////////////////////////////////////////
// ITcDbgUnit
// Implemented by class factories. Provides per module information used by TcDebuggerPort
// to find the symbol information. 
///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcDbgUnit : public ITcUnknown
{
	TCOMMETHOD(TcDbgUnitIsValid()); 
	TCOMMETHOD(TcDbgUnitGetImageName(PCSTR& szImageName)); 
	TCOMMETHOD(TcDbgUnitGetInfo(PCSTR& szImageName, ULONG_PTR& pImageBase, ULONG& nImageSize)); 
	TCOMMETHOD(TcDbgUnitGetImageFullName(PSTR pszImageFullName, SIZE_T nImageFullName));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgUnit, IID_ITcDbgUnit);

/////////////////////////////////////////////////////////////////////////////////
// ITcDbgUnitFlags
/////////////////////////////////////////////////////////////////////////////////
enum TcDbgUnitFlags
{
	TcDbgUnitFlagsNone   = 0x0,
	TcDbgUnitFlagsHidden = 0x1
};

struct	__declspec(novtable)	ITcDbgUnitFlags : public ITcUnknown
{
	TCOMMETHOD(TcDbgUnitCheckFlags(TcDbgUnitFlags flags, bool& bIsSet)); 
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgUnitFlags, IID_ITcDbgUnitFlags);

/////////////////////////////////////////////////////////////////////////////////
// ITcDbgUnitVersion
/////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITcDbgUnitVersion : public ITcUnknown
{
	TCOMMETHOD(TcDbgUnitGetImageVersion(DbgUnitVersion& ImageVersion));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgUnitVersion, IID_ITcDbgUnitVersion);

///////////////////////////////////////////////////////////////////////////////
// ITcDbgInformation - implemented by TComObjectServer in order to debug 
//    information to the TcDebuggerPort, i.e.
//       - list of loaded debug units, and
//       - list of tasks.
//    Note, that there is a one to one mapping between a debug unit and 
//    a symbol information file. A debug unit is the TcXae counterpart to 
//    a "module of a windows process".
//
// TcDbgTaskEnumerate
// - Trigger task enumeration events, which allows to synchronize onto 
//   the current list of tasks. 
// 
// TcDbgUnitEnumerate 
// - Trigger module enumeration events, which allows to synchronize onto 
//   the current module load state. 
//
// TcDbgUnitAdd 
// - Add debug unit information item
//
// TcDbgUnitRemove 
// - Remove debug unit information item
struct __declspec(novtable) ITcTask;
struct	__declspec(novtable)	ITcDbgInformation : public ITcUnknown
{
	TCOMMETHOD(TcDbgUnitAdd(ITcDbgUnit* ipTcDbgUnit)); 
	TCOMMETHOD(TcDbgUnitRemove(ITcDbgUnit* ipTcDbgUnit)); 
	TCOMMETHOD(TcDbgUnitEnumerate(ITcTask* ipCaller)); 
	TCOMMETHOD(TcDbgTaskEnumerate(ITcTask* ipCaller)); 
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgInformation, IID_ITcDbgInformation);

///////////////////////////////////////////////////////////////////////////////
// ITcDebugInformation2
struct __declspec(novtable) ITcDbgInformation2 : public ITcDbgInformation
{
	TCOMMETHOD(TcDbgUnitGetInfoByAddr (PSTR pModuleName, size_t nNameSize, ULONG_PTR &nModuleAddr, ULONG &nSize, DbgUnitVersion* pVersion));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgInformation2, IID_ITcDbgInformation2);


///////////////////////////////////////////////////////////////////////////////
// ITcDebugInformationOC
struct	__declspec(novtable)	ITcDbgInformationOC : public ITcUnknown
{
	TCOMMETHOD(TcDbgGetBaseAddressOC(ULONG_PTR& baseAddress));
	TCOMMETHOD(TcDbgReadDataOC(ULONG offs, UINT size, PVOID mem));
	TCOMMETHOD(TcDbgWriteDataOC(ULONG offs, UINT size, PVOID mem, UINT& cbWriteSize));
	TCOMMETHOD(TcDbgGetChildClsid(GUID& guid));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDbgInformationOC, IID_ITcDbgInformationOC);


///////////////////////////////////////////////////////////////////////////////
// ITcPersist
struct	__declspec(novtable)	ITcPersist : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI GetClassId ( CTCID& classId ) = 0;	
};
_TCOM_SMARTPTR_TYPEDEF(ITcPersist, IID_ITcPersist);

///////////////////////////////////////////////////////////////////////////////
// ITcAlloc
struct	__declspec(novtable)	ITcAlloc : public ITcUnknown
{
	virtual	HRESULT	Alloc( ULONG size, PPVOID ppData ) = 0;	
	virtual	HRESULT	Free( PVOID pData ) = 0;	
};
_TCOM_SMARTPTR_TYPEDEF(ITcAlloc, IID_ITcAlloc);

#ifndef POSIX
struct	__declspec(novtable)	ITcAdsHelper : public ITcAlloc
{
	virtual	HRESULT	AllocCopy( PAmsCmd pCmd, PAmsCmd* ppRes ) = 0;	
	virtual	HRESULT	AllocCopy( PAmsCmd pCmd, ULONG size, PAmsCmd* ppRes ) = 0;	
	virtual	HRESULT	MakeHead( AmsHead& head, WORD cmdId, long cbData, AmsAddr targetAddr, long hUser=0, long errCode=0, WORD stateFlags=0) = 0;	
	virtual	HRESULT	MakeHead( AmsHead& head, WORD cmdId, long cbData, AmsNetId targetNetId, AmsPortNo targetPort, long hUser=0, long errCode=0, WORD stateFlags=0) = 0;	
	virtual	HRESULT	SendResponse( PAmsCmd pCmd, long errCode ) = 0;	
};
_TCOM_SMARTPTR_TYPEDEF(ITcAdsHelper, IID_ITcAdsHelper);
#endif

///////////////////////////////////////////////////////////////////////////////
// ITComServer ( implemented by CAdsCtrl )
struct	ITComObjInd;
struct	ITComObjCon;
struct	__declspec(novtable)	ITComServer : public ITcUnknown
{
	virtual	HRESULT	AddToAdsConMap( ITComObjCon* ipCon, ULONG invokeId, LONG timeout, ULONG& invokeKey ) = 0;
	virtual	HRESULT	AddToAdsIndMap( ULONG indexGroup, ITComObjInd* ipObj ) = 0;
	virtual	HRESULT	QueryObjectInterface( OTCID oid, RITCID iid, PPVOID pipItf ) = 0;
	virtual	HRESULT	RemoveFromAdsConMap( ULONG invokeKey ) = 0;
	virtual	HRESULT	RemoveFromAdsIndMap( ULONG indexGroup ) = 0;
	virtual	HRESULT	ReportLog( DWORD msgCtrlMask, PCHAR szFormat, ... ) = 0;
	virtual	HRESULT	ReportLog( DWORD msgCtrlMask, ULONG nResourceId, 
		PCHAR szFormat, ... ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComServer, IID_ITComServer);

///////////////////////////////////////////////////////////////////////////////
// ITComObject ( implemented by TCom Objects )
struct	__declspec(novtable)	ITComObject : public ITcPersist
{
	TCOMMETHOD(TcGetObjectId( OTCID& objId ));
	TCOMMETHOD(TcGetObjectName( CHAR* objName, ULONG nameLen ));
	TCOMMETHOD(TcSetObjectId( OTCID objId ));	
	TCOMMETHOD(TcSetObjectName( CHAR* objName ));
	TCOMMETHOD(TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData));
	TCOMMETHOD(TcGetObjState(TCOM_STATE* pState));
	TCOMMETHOD(TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0));
	TCOMMETHOD(TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0));
	TCOMMETHOD(TcGetParentObjId( OTCID& objId ));
	TCOMMETHOD(TcSetParentObjId( OTCID objId ));	
};
_TCOM_SMARTPTR_TYPEDEF(ITComObject, IID_ITComObject);

///////////////////////////////////////////////////////////////////////////////
// ITComObjectParent - implemented by objects managing child objects
struct	__declspec(novtable)	ITComObjectParent : public ITcUnknown
{
	TCOMMETHOD(AddChildObject(ITcUnknown* ipUnk));
	TCOMMETHOD(RemoveChildObject(ITcUnknown* ipUnk));
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjectParent, IID_ITComObjectParent);

///////////////////////////////////////////////////////////////////////////////
// ITComObjectChild 
struct	__declspec(novtable)	ITComObjectChild : public ITcUnknown
{
	TCOMMETHOD(GetParent(ITcUnknown** pipUnk));
	TCOMMETHOD(SetParent(ITcUnknown* ipUnk));
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjectChild, IID_ITComObjectChild);

///////////////////////////////////////////////////////////////////////////////
// ITcConfigModeFreerun
struct __declspec(novtable) ITcConfigModeFreerun : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetFreerunState()=0;								// S_OK = free run, S_FALSE = no free run, E_FAIL if ConfigMode is inactive
	virtual	HRESULT	TCOMAPI	SetFreerunState(HRESULT hrFreerun)=0;		// returns old state	or E_FAIL if not in ConfigMode
};
_TCOM_SMARTPTR_TYPEDEF(ITcConfigModeFreerun, IID_ITcConfigModeFreerun);

///////////////////////////////////////////////////////////////////////////////
// ITComObjectCategory - implemented by objects implementing special categories
struct	__declspec(novtable)	ITComObjectCategory : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	EnumCategory(int& idx, CATTCID& catId)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjectCategory, IID_ITComObjectCategory);

///////////////////////////////////////////////////////////////////////////////
// ITComEnsureOpState
struct	__declspec(novtable)	ITComEnsureOpState : public ITcUnknown
{	// not thread safe! -> typically EnsureAndLockOpState() called in SetObjStateSO() and ReleaseOpState() in SetObjStateOS() (TComServerTask context)
	virtual	HRESULT TCOMAPI	EnsureAndLockOpState() = 0;	// if succeeded -> a corresponding call to ReleaseOpState required
	virtual	HRESULT TCOMAPI	ReleaseOpState() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComEnsureOpState, IID_ITComEnsureOpState);

///////////////////////////////////////////////////////////////////////////////
// ITComEnumTCID
struct	__declspec(novtable)	ITComEnumTCID : public ITcUnknown
{
	virtual HRESULT	TCOMAPI	Next( ULONG celt, ULONG *rgelt, ULONG *pceltFetched=NULL) = 0;
	virtual HRESULT	TCOMAPI	Skip( ULONG celt) = 0;
	virtual HRESULT	TCOMAPI	Reset( void) = 0;
	virtual HRESULT	TCOMAPI	Clone( ITComEnumTCID **ppEnum) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComEnumTCID, IID_ITComEnumTCID);

///////////////////////////////////////////////////////////////////////////////
// ITComFuncProvider
struct	__declspec(novtable)	ITComFuncProvider : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	TcGetFuncPointer(RFTCID fncId, PPVOID pipFnc, PULONG pSignature=NULL, PULONG pVersion=NULL)=0;
	virtual	HRESULT TCOMAPI	TcReleaseFuncPointer(RFTCID fncId)=0;
	virtual	HRESULT TCOMAPI	TcGetFuncName( RFTCID fncId, PCHAR* ppClassName)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComFuncProvider, IID_ITComFuncProvider);

///////////////////////////////////////////////////////////////////////////////
// ITComFuncServer
struct	__declspec(novtable)	ITComFuncServer : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	TcAddToFuncProviderMap( RFTCID fncId, ITComFuncProvider* ipFuncProvider )=0;
	virtual	HRESULT TCOMAPI	TcRemoveFromFuncProviderMap( RFTCID fncId )=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComFuncServer, IID_ITComFuncServer);

///////////////////////////////////////////////////////////////////////////////
// ITComObjectEnum - implemented by TComObjectServer in order to enumerate objects
//    of a specific category
struct	__declspec(novtable)	ITComObjectEnum : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	EnumObjByCategory(CATTCID catId, ITComEnumTCID** pipEnum)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjectEnum, IID_ITComObjectEnum);

///////////////////////////////////////////////////////////////////////////////
// ITComAdmin ( implemented by CAdsCtrl e.g. used by CTask )
struct	__declspec(novtable)	ITComAdmin : public ITcUnknown
{
	typedef struct
	{
		__int64			expirationTime;
		ULONG				invokeId;
		ITComObjCon* 	ipCon;
	} TCOM_ADSCON_ENTRY;
	virtual	HRESULT	AddToObjMap( OTCID oid, ITcUnknown* ipUnk ) = 0;
	virtual	HRESULT	LookupAdsConObjInterface( ULONG invokeKey, ITComObjCon*& ipCon, ULONG& invokeId ) = 0;
	virtual	HRESULT	LookupAdsIndObjInterface( ULONG indexGroup, ITComObjInd*& ipObj ) = 0;
	virtual	HRESULT	QueryObjectInterface( OTCID oid, RITCID iid, PPVOID pipItf ) = 0;
	virtual	HRESULT	RemoveFromObjMap( OTCID oid ) = 0;
	TCOMMETHOD(TcAddToClassFactoryMap( RCTCID clsId, ITcBaseClassFactory* ipClassFactory ));
	TCOMMETHOD(TcRemoveFromClassFactoryMap( RCTCID clsId ));
	TCOMMETHOD(TcCreateInstance( RCTCID clsId, RITCID iid, PPVOID pipItf, PVOID pvInit = NULL, UINT cbInitData = 0 ));
};
_TCOM_SMARTPTR_TYPEDEF(ITComAdmin, IID_ITComAdmin);

struct	__declspec(novtable)	ITComObjectServer : public ITcUnknown
{
	typedef struct
	{
		__int64			expirationTime;
		ULONG				invokeId;
		ITComObjCon* 	ipCon;
	} TCOM_ADSCON_ENTRY;
	TCOMMETHOD(TcAddToAdsConMap( ITComObjCon* ipCon, ULONG invokeId, LONG timeout, ULONG& invokeKey ));
	TCOMMETHOD(TcAddToAdsIndMap( ULONG indexGroup, ITComObjInd* ipObj ));
	TCOMMETHOD(TcAddToClassFactoryMap( RCTCID clsId, ITcBaseClassFactory* ipClassFactory ));
	TCOMMETHOD(TcAddToObjMap( OTCID oid, ITcUnknown* ipUnk));
	TCOMMETHOD(TcCreateInstance( RCTCID clsId, RITCID iid, PPVOID pipItf ));
	TCOMMETHOD(TcLookupAdsConObjInterface( ULONG invokeKey, ITComObjCon*& ipCon, ULONG& invokeId ));
	TCOMMETHOD(TcLookupAdsIndObjInterface( OTCID oid, ITComObjInd*& ipObj ));
	TCOMMETHOD(TcQueryObjectInterface( OTCID oid, RITCID iid, PPVOID pipItf ));
	TCOMMETHOD(TcRemoveFromAdsConMap( ULONG invokeKey ));
	TCOMMETHOD(TcRemoveFromAdsIndMap( ULONG indexGroup ));
	TCOMMETHOD(TcRemoveFromClassFactoryMap( RCTCID clsId ));
	TCOMMETHOD(TcRemoveFromObjMap( OTCID oid ));
	TCOMMETHOD(TcReportLog( DWORD msgCtrlMask, PCHAR szFormat, ... ));
	TCOMMETHOD(TcReportLog( DWORD msgCtrlMask, ULONG nResourceId, PCHAR szServerName, PCHAR szFormat, ... ));
	TCOMMETHOD(TcReportLogV( DWORD msgCtrlMask, PCHAR pszFormat, va_list pArgs));
	TCOMMETHOD(TcReportLogV( DWORD msgCtrlMask, ULONG nResourceId, PCHAR szServerName, PCHAR szFormat, va_list pArgs));
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjectServer, IID_ITComObjectServer);

struct	__declspec(novtable)	ITcDrvLdr : public ITcUnknown
{
	TCOMMETHOD(LoadDrv(PCHAR szDrvName, PULONG pidxDrv)); // potential interface method
	TCOMMETHOD(UnloadDrv(ULONG idxDrv));
	TCOMMETHOD(SendIoctl(ULONG idxDrv, PVOID pIoctlParams));
	TCOMMETHOD(GetFrameWorkVersion(ULONG idxDrv, AdsVersion sysSrvVersion, PAdsVersion pDrvVersion));
	TCOMMETHOD(RegisterDrv(ULONG idxDrv));
	TCOMMETHOD(InitDrv(ULONG idxDrv));
	TCOMMETHOD(ShutdownDrv(ULONG idxDrv));
	TCOMMETHOD(UnregisterDrv(ULONG idxDrv));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDrvLdr, IID_ITcDrvLdr);

struct	__declspec(novtable)	ITcLoader : public ITcUnknown
{
	TCOMMETHOD(Load(LPCSTR szFileName, HANDLE* phModule, BYTE* sha256Hash = NULL));
	TCOMMETHOD(Unload(HANDLE hModule));
	TCOMMETHOD(GetProcAddr(HANDLE hModule, LPCSTR szProcName, VOID** ppProc));
	TCOMMETHOD(GetModuleBase(HANDLE hModule, VOID** ppBase));
};
_TCOM_SMARTPTR_TYPEDEF(ITcLoader, IID_ITcLoader);

struct	__declspec(novtable)	ITcLoader2 : public ITcLoader
{
	TCOMMETHOD(GetModuleSize(HANDLE hModule, PULONG pcbModuleMemSize));
};
_TCOM_SMARTPTR_TYPEDEF(ITcLoader2, IID_ITcLoader2);

struct _TCMODULEINFO;
typedef _TCMODULEINFO TCMODULEINFO;

struct _MDCVInfoPDB70;
typedef _MDCVInfoPDB70 MDCVInfoPDB70;

struct	__declspec(novtable)	ITcLoader3 : public ITcLoader2
{
	TCOMMETHOD(GetModuleHandleExA(DWORD dwFlags, LPCSTR lpModuleName, HANDLE *phModule));
	TCOMMETHOD(GetModuleInformation(HANDLE hProcess, HANDLE hModule, TCMODULEINFO* lpmodinfo, size_t cb));
	TCOMMETHOD(GetModuleFileNameA(HANDLE hModule, LPSTR lpFilename, PULONG pcb));
	TCOMMETHOD(GetDebugInfo(HANDLE hModule, MDCVInfoPDB70* pCVInfo, size_t* pcb));
	TCOMMETHOD(GetDebugInfoByAddr(void* pImageBase, MDCVInfoPDB70* pCVInfo, size_t* pcb));
};
_TCOM_SMARTPTR_TYPEDEF(ITcLoader3, IID_ITcLoader3);

struct	__declspec(novtable)	ITcLoader4 : public ITcLoader3
{
	TCOMMETHOD(GetErrorText(INT nError, LPSTR lpFilename, size_t* pcb));
};
_TCOM_SMARTPTR_TYPEDEF(ITcLoader4, IID_ITcLoader4);

struct __declspec(novtable) ITcOsFileLoader : public ITcUnknown
{
	TCOMMETHOD(OsLoadFile(LPCSTR szFileName, void* pBuf, size_t nBuf, size_t* nRead));
	TCOMMETHOD(OSWriteFile(LPCSTR szFileName, void* pBuf, size_t nBuf, size_t* nWritten));
};
_TCOM_SMARTPTR_TYPEDEF(ITcOsFileLoader, IID_OsFileLoader);

struct	__declspec(novtable)	ITComReportEvent : public ITcUnknown
{
	TCOMMETHOD(TcReportEvent(DWORD dwFlags, ITComObject* ipSrc, ULONG nEvtId, PCHAR pszFormat, ...));
	TCOMMETHOD(TcReportEvent(DWORD dwFlags, ITComObject* ipSrc, ULONG nEvtId, ULONGLONG timeStamp, PCHAR pszFormat, ...));
	TCOMMETHOD(TcReportEvent(DWORD dwFlags, GUID gSrcId, PCHAR pszSrc, ULONG nObjId, ULONG nEvtId, PCHAR pszFormat, ...));
	TCOMMETHOD(TcReportEvent(DWORD dwFlags, GUID gSrcId, PCHAR pszSrc, ULONG nObjId, ULONG nEvtId, ULONGLONG timeStamp, PCHAR pszFormat, ...));
	TCOMMETHOD(TcReportEventV(DWORD dwFlags, ITComObject* ipSrc, ULONG nEvtId, PCHAR pszFormat, va_list pArgs, ULONGLONG timeStamp = 0));
	TCOMMETHOD(TcReportEventV(DWORD dwFlags, GUID gSrcId, PCHAR pszSrc, ULONG nObjId, ULONG nEvtId, PCHAR pszFormat, va_list pArgs, ULONGLONG timeStamp = 0));
};
_TCOM_SMARTPTR_TYPEDEF(ITComReportEvent, IID_ITComReportEvent);
#pragma deprecated(ITComReportEvent)

struct	__declspec(novtable)	ITComCreateInstance : public ITcUnknown
{
	TCOMMETHOD(TcCreateAndInitInstance( RCTCID clsId, RITCID iid, PPVOID pipItf, OTCID objId, OTCID parentId=0, CHAR* objName=NULL, 
		TCOM_STATE state=TCOM_STATE_INIT, PTComInitDataHdr pInitData=NULL ));
};
_TCOM_SMARTPTR_TYPEDEF(ITComCreateInstance, IID_ITComCreateInstance);


#define	TcQuerySmartObjectInterface(ip)	TcQueryObjectInterface(ip.GetOID(), ip.GetIID(), (PPVOID)&ip)

inline HRESULT TcEnsureOpState(ITComObjectPtr spObj)
{
	if ( spObj )
	{
		TCOM_STATE state;
		if ( SUCCEEDED(spObj->TcGetObjState(&state)) )
		{
			if ( state == TCOM_STATE_OP )
				return S_OK;
			if ( state == TCOM_STATE_SAFEOP )
				return spObj->TcSetObjState(TCOM_STATE_OP, NULL, NULL);
		}
	}
	return 0x98110712; // ADS_E_INVALIDSTATE;
}

inline HRESULT TcEnsureSafeOpState(ITComObjectPtr spObj)
{
	if (spObj)
	{
		TCOM_STATE state;
		if (SUCCEEDED(spObj->TcGetObjState(&state)))
		{
			if (state >= TCOM_STATE_SAFEOP)
				return S_OK;
			if (state == TCOM_STATE_PREOP)
				return spObj->TcSetObjState(TCOM_STATE_SAFEOP, NULL, NULL);
		}
	}
	return 0x98110712; // ADS_E_INVALIDSTATE;
}

///////////////////////////////////////////////////////////////////////////////
// ITcObjParaAsyncRes 
typedef struct _TCOM_OBJPARA_ASYNC_INFO
{
	AmsAddr					rAddr;
	ULONG						invokeId;
	ULONG						serviceId;
} TCOM_OBJPARA_ASYNC_INFO, *PTCOM_OBJPARA_ASYNC_INFO;

struct	__declspec(novtable)	ITcObjParaAsyncRes : public ITcUnknown
{
	TCOMMETHOD(TcObjParaRes(TCOM_OBJPARA_ASYNC_INFO& info, HRESULT hr, ULONG nData, PVOID pData));
	TCOMMETHOD(TcObjParaFrw(AmsAddr& rNewDestAddr, TCOM_OBJPARA_ASYNC_INFO& info, PTCID pid, ULONG nGetData, ULONG nSetData, PVOID pSetData, PTCGP pgp=0));
};
_TCOM_SMARTPTR_TYPEDEF(ITcObjParaAsyncRes, IID_ITcObjParaAsyncRes);

///////////////////////////////////////////////////////////////////////////////
// ITcObjParaAsync 
struct	__declspec(novtable)	ITcObjParaAsync : public ITcUnknown
{
	TCOMMETHOD(TcObjParaAsync(ITcObjParaAsyncRes* ipRes, TCOM_OBJPARA_ASYNC_INFO& info, PTCID pid, ULONG nGetData, ULONG nSetData, PVOID pSetData, PTCGP pgp=0));
};
_TCOM_SMARTPTR_TYPEDEF(ITcObjParaAsync, IID_ITcObjParaAsync);

///////////////////////////////////////////////////////////////////////////////
// ITComObjRes ( implemented by Ads Ports (Ctrl and Tasks) )
struct	__declspec(novtable)	ITComObjRes : public ITcUnknown
{
	virtual	HRESULT	GetCurrentAmsPort( AmsPortNo& port ) = 0;
	virtual	HRESULT	ReadRes( AmsAddr& rAddr, ULONG invokeId, HRESULT nResult,
		ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	WriteRes( AmsAddr& rAddr, ULONG invokeId, HRESULT nResult ) = 0;
	virtual	HRESULT	ReadWriteRes( AmsAddr& rAddr, ULONG invokeId, HRESULT nResult,
		ULONG cbLength, PVOID pData ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjRes, IID_ITComObjRes);

///////////////////////////////////////////////////////////////////////////////
// ITComObjReq ( implemented by Ads Ports (Ctrl and Tasks) )
struct	__declspec(novtable)	ITComObjReq : public ITcUnknown
{
	virtual	HRESULT	ReadReq( ITComObjCon* ipCon, LONG timeout, AmsAddr& rAddr, 
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength ) = 0;
	virtual	HRESULT	WriteReq( ITComObjCon* ipCon, LONG timeout, AmsAddr& rAddr, 
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	ReadWriteReq( ITComObjCon* ipCon, LONG timeout, AmsAddr& rAddr, 
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, 
		ULONG cbWriteLength, PVOID pData ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjReq, IID_ITComObjReq);

///////////////////////////////////////////////////////////////////////////////
// ITComObjInd ( implemented by TCom Objects )
struct	__declspec(novtable)	ITComObjInd : public ITcUnknown
{
	virtual	HRESULT	GetData( ULONG indexGroup, ULONG indexOffset, PVOID& pData, 
		ULONG& nData ) = 0;
	virtual	HRESULT	ReadInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, 
		ULONG indexGroup,	ULONG indexOffset, ULONG cbLength ) = 0;
	virtual	HRESULT	ReadWriteInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, 
		ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, 
		PVOID pData ) = 0;
	virtual	HRESULT	SetData( ULONG indexGroup, ULONG indexOffset, PVOID pData, 
		ULONG nData ) = 0;
	virtual	HRESULT	WriteInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, 
		ULONG indexGroup,	ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjInd, IID_ITComObjInd);

///////////////////////////////////////////////////////////////////////////////
// ITComObjCon ( possible implemented by TCom Objects )
struct	__declspec(novtable)	ITComObjCon : public ITcUnknown
{
	virtual	HRESULT	ReadCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, 
		ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	ReadWriteCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult, 
		ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	WriteCon( AmsAddr& rAddr, ULONG invokeId, ULONG nResult ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComObjCon, IID_ITComObjCon);

///////////////////////////////////////////////////////////////////////////////
// ITComObjFrw ( implemented by Ads Ports (Ctrl and Tasks) )
struct	__declspec(novtable)	ITComObjFrw : public ITcUnknown
{
	virtual	HRESULT	ReadFrw( AmsAddr& rAddr, AmsAddr& rNewDestAddr,
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength ) = 0;
	virtual	HRESULT	ReadWriteFrw( AmsAddr& rAddr, AmsAddr& rNewDestAddr,
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, 
		ULONG cbWriteLength, PVOID pData ) = 0;
	virtual	HRESULT	WriteFrw( AmsAddr& rAddr, AmsAddr& rNewDestAddr,
		ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0;
};	
_TCOM_SMARTPTR_TYPEDEF(ITComObjFrw, IID_ITComObjFrw);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITComAmsMem
// implemented by Tasks allowing memory allocation via AMS
struct	__declspec(novtable)	ITComAmsMem : public ITcUnknown
{
	virtual PVOID	AllocOsMem( int nSize ) = 0;
	virtual void	FreeOsMem( PVOID pVoid ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComAmsMem, IID_ITComAmsMem);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITComAmsMemEx
// implemented by Tasks allowing executable memory allocation via AMS
struct	__declspec(novtable)	ITComAmsMemEx : public ITcUnknown
{
	virtual PVOID	AllocOsMemEx( int nSize ) = 0;
	virtual void	FreeOsMemEx( PVOID pVoid ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComAmsMemEx, IID_ITComAmsMemEx);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITComAdsLog
// implemented by Tasks allowing to send log messages via ADS
struct	__declspec(novtable)	ITComAdsLog : public ITcUnknown
{
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, PCHAR szFormat, ... ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, PCHAR szFormat, ... ));
	
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg, LONG nArg1 ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, LONG nArg, LONG nArg1, LONG nArg2 ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg0, DOUBLE fArg1 ));
	TCOMMETHOD(TcAdsReportLog( DWORD msgCtrlMask, ULONG nResourceId, DOUBLE fArg0, DOUBLE fArg1, DOUBLE fArg2 ));
};
_TCOM_SMARTPTR_TYPEDEF(ITComAdsLog, IID_ITComAdsLog);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITcAdsInvoker
// implemented by tasks to allow usage of their ADS port in cyclic processing
typedef USHORT TcAdsInvokerStamp; 
typedef BYTE	TcAdsInvokerCnt; 
struct	__declspec(novtable)	ITcAdsInvoker : public ITcUnknown
{
	virtual HRESULT TCOMAPI CreateStamp( TcAdsInvokerStamp& stamp ) = 0;
	virtual HRESULT TCOMAPI ReadDeviceInfoReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr ) = 0;
	virtual HRESULT TCOMAPI ReadReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr, ULONG nIdxGrp, ULONG nIdxOffs, ULONG cbLength, PVOID pData ) = 0;
	virtual HRESULT TCOMAPI WriteReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr, ULONG nIdxGrp, ULONG nIdxOffs, ULONG cbLength, PVOID pData ) = 0;
	virtual HRESULT TCOMAPI ReadStateReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr, PULONG pState ) = 0;
	virtual HRESULT TCOMAPI WriteControlReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr, USHORT adsState, USHORT deviceState, ULONG cbLength, PVOID pData ) = 0;
	virtual HRESULT TCOMAPI ReadWriteReqInv( TcAdsInvokerStamp stamp, TcAdsInvokerCnt cnt, AmsAddr& rAddr, ULONG nIdxGrp, ULONG nIdxOffs, ULONG cbReadLength, PVOID pRead, ULONG cbWriteLength, PVOID pWrite) = 0;
	virtual HRESULT TCOMAPI GetAdsCon( TcAdsInvokerStamp stamp, PULONG pResult, PULONG pcbLength, PPVOID ppData) = 0;
	virtual VOID TCOMAPI RemoveAdsCon( TcAdsInvokerStamp stamp ) = 0;
	virtual HRESULT TCOMAPI ResolveAmsNetId( PCCH szNetId, AmsNetId& netId ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAdsInvoker, IID_ITcAdsInvoker);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITcAdsInvoker2
// implemented by tasks to allow usage of their ADS port in cyclic processing
struct	__declspec(novtable)	ITcAdsInvoker2 : public ITcAdsInvoker
{
	virtual VOID TCOMAPI AdsInvokerRemoveContextByOwner(ITcUnknown* ipOwner) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAdsInvoker2, IID_ITcAdsInvoker2);

//////////////////////////////////////////////////////////////////////////////////

#if !defined(TC_ENVIRONMENT_CE_RT) && !defined(TC_ENVIRONMENT_CE)
#define ITCRTADSPORT
#endif

#ifdef ITCRTADSPORT
struct ITcRtAdsUser;
struct __declspec(novtable) ITcRtAdsPort : public ITcUnknown					
{																																					
	virtual	HRESULT	TCOMAPI	RegisterNotificationHandler(ITcRtAdsUser* ipUser, PULONG pHandle)=0;	
	virtual	HRESULT	TCOMAPI	DeregisterNotificationHandler(ULONG handle)=0;	
	virtual	HRESULT	TCOMAPI	SendAdsReadReq(ITcRtAdsUser* ipUser, AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, ULONG timeoutMs=5000)=0;	
	virtual	HRESULT	TCOMAPI	SendAdsWriteReq(ITcRtAdsUser* ipUser, AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData, ULONG timeoutMs=5000)=0;	
	virtual	HRESULT	TCOMAPI	SendAdsReadWriteReq(ITcRtAdsUser* ipUser, AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData, ULONG timeoutMs=5000)=0;	
};
_TCOM_SMARTPTR_TYPEDEF(ITcRtAdsPort, IID_ITcRtAdsPort);

struct __declspec(novtable) ITcRtAdsUser : public ITcUnknown		
{																																					
	virtual	HRESULT	TCOMAPI	OnNotificationHandler(ULONG handle, ULONG nPayload, PVOID pPayload)=0;
	virtual	HRESULT	TCOMAPI	OnAdsReadCon(ULONG invokeId, ULONG result, ULONG cbLength, PVOID pData)=0;
	virtual	HRESULT	TCOMAPI	OnAdsWriteCon(ULONG invokeId, ULONG result)=0;
	virtual	HRESULT	TCOMAPI	OnAdsReadWriteCon(ULONG invokeId, ULONG result, ULONG cbLength, PVOID pData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcRtAdsUser, IID_ITcRtAdsUser);
#endif

//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITcVersionProvider : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetVersion(T_Version& version) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcVersionProvider, IID_ITcVersionProvider);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITComAmsTaskPort
// implemented by Tasks allowing to control the Ams Task port 
struct	__declspec(novtable)	ITComAmsTaskPort : public ITcUnknown
{
	TCOMMETHOD(SetAsyncAmsCmdProcessing(BOOL bAsync));
};
_TCOM_SMARTPTR_TYPEDEF(ITComAmsTaskPort, IID_ITComAmsTaskPort);


//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITcDynPoolObject : public ITcUnknown					// must be implemented by dynamic pool objects
{																																					
	virtual	HRESULT	TCOMAPI	ActivateDynPoolObject(ITcUnknown* ipOwner)=0;	// called from temp owner before using it
	virtual	HRESULT	TCOMAPI	DeactivateDynPoolObject()=0;							// called from temp owner before returning
};
_TCOM_SMARTPTR_TYPEDEF(ITcDynPoolObject, IID_ITcDynPoolObject);

//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITcDynPoolManager : public ITcUnknown
{																																					
	virtual	HRESULT	TCOMAPI	GetDynPoolObject(ITcDynPoolObject** pipObj)=0;		
	virtual	HRESULT	TCOMAPI	ReturnDynPoolObject(ITcDynPoolObject* ipObj)=0;
	virtual	HRESULT	TCOMAPI	GetDynPoolClassId(CTCID& classId)=0;
	virtual	HRESULT	TCOMAPI	GetDynPoolCount(UINT& count)=0;
	virtual	HRESULT	TCOMAPI	GetDynPoolFreeCount(UINT& count)=0;
	virtual	HRESULT	TCOMAPI	IncreaseDynPool(UINT count)=0;
	virtual	HRESULT	TCOMAPI	DecreaseDynPool(UINT count)=0;
	virtual	HRESULT	TCOMAPI	InDecreaseDynPoolStatus()=0;		// returns S_OK, S_PENDING or any error of the last request
};
_TCOM_SMARTPTR_TYPEDEF(ITcDynPoolManager, IID_ITcDynPoolManager);

//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITcDynMemManager : public ITcUnknown
{
	virtual bool    TCOMAPI IsOccupied() = 0;
	virtual HRESULT TCOMAPI Resize(ULONG count) = 0;
	virtual ULONG   TCOMAPI Size() = 0;
	virtual HRESULT TCOMAPI Occupy(PPVOID p) = 0;
	virtual HRESULT TCOMAPI Release(PPVOID p) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcDynMemManager, IID_ITcDynMemManager);

//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComCallbackClient : public ITcUnknown
{										
	virtual	HRESULT	TCOMAPI	WindowsCallback(ULONG invokeId, ULONG nData=0, PVOID pData=NULL)=0;
	virtual	HRESULT	TCOMAPI	RealtimeCallback(ULONG invokeId, ULONG nData=0, PVOID pData=NULL)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComCallbackClient, IID_ITComCallbackClient);

//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComCallbackServer : public ITcUnknown
{										
	virtual	HRESULT	TCOMAPI	GenerateWindowsCallback(OTCID oidClient, ULONG invokeId, ULONG nData=0, PVOID pData=NULL)=0;
	virtual	HRESULT	TCOMAPI	GenerateRealtimeCallback(OTCID oidClient, ULONG invokeId, ULONG nData=0, PVOID pData=NULL)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComCallbackServer, IID_ITComCallbackServer);


//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComCallbackServer2 : public ITComCallbackServer
{										
	virtual	HRESULT	TCOMAPI	GenerateWindowsCallbackPassiveLevel(OTCID oidClient, ULONG invokeId, ULONG nData=0, PVOID pData=NULL)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComCallbackServer2, IID_ITComCallbackServer2);


//////////////////////////////////////////////////////////////////////////////////
struct __declspec(novtable) ITComContextCallbackServer : public ITcUnknown
{
	enum Context {
		Rtime = 0,
		Passive_Level = 1,
		Dispatch_Level = 2,
	};
	virtual	HRESULT	TCOMAPI	GenerateContextCallback(OTCID oidClient, ULONG invokeId, Context context, ULONG timeout = 0, ULONG nData = 0, PVOID pData = NULL) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComContextCallbackServer, IID_ITComContextCallbackServer);

//////////////////////////////////////////////////////////////////////////////////
// ITComSystemInstance ( implemented by system instances like router, rtime, io )
struct	__declspec(novtable) ITComSystemInstance : ITcUnknown
{
};
_TCOM_SMARTPTR_TYPEDEF(ITComSystemInstance, IID_ITComSystemInstance);

///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcErrorLogger : public ITcUnknown
{
	 virtual long AdsReportLogV( DWORD msgCtrlMask, DWORD msgDest, HRESULT nResourceId, unsigned long long &nTicket, PCHAR pszFormat, va_list pArgs ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcErrorLogger, IID_ITcErrorLogger);

///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable)	ITcObjPara : public ITcUnknown
{
	TCOMMETHOD(TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0));
	TCOMMETHOD(TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0));
};
_TCOM_SMARTPTR_TYPEDEF(ITcObjPara, IID_ITcObjPara);

///////////////////////////////////////////////////////////////////////////////
#ifdef TCTMCHANDLER_SUPPORT

#define	MAX_TmcHandlerData_Contexts	8
#define	MAX_TmcHandlerData_LibraryId	128
struct TmcInstData
{
	// filled by TMC Handler
	char						libraryId[MAX_TmcHandlerData_LibraryId];
	GUID						guidLibrary;	// hash of libraryId
	GUID						guidModule;
	BYTE						reserved[96];
};

struct	__declspec(novtable)	ITComOnlineChange : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	PrepareOnlineChange(ITComObject* ipOldObj, TmcInstData* pOldInfo) = 0;	// before CS
	virtual	HRESULT	TCOMAPI	PerformOnlineChange(ITComObject* ipOldObj, TmcInstData* pOldInfo) = 0;	// while CS
};
_TCOM_SMARTPTR_TYPEDEF(ITComOnlineChange, IID_ITComOnlineChange);
#endif

#ifdef	ADS_EXTERNALTIME_PROVIDER
///////////////////////////////////////////////////////////////////////////////
// ITcExternalTime
struct	__declspec(novtable)	ITcExternalTime : public ITcUnknown
{	// all times based on 1.1.1601 - 100ns (FILETIME)
	enum TimeType {
		SystemTime = 0,
		ExternalTimeHard = 1,	// hardware synchronised - no drift
		ExternalTimeMedium = 2,	// e.g. IEEE 1588
		ExternalTimeSoft = 3,	// e.g. NTP
	};
	virtual	HRESULT	TCOMAPI SystemTimeToExternalTime(TimeType type, __int64& time) = 0;
	virtual	HRESULT	TCOMAPI ExternalTimeToSystemTime(TimeType type, __int64& time) = 0;
	virtual	HRESULT	TCOMAPI GetExternalTimeOffset(TimeType type, __int64& offset) = 0;
	virtual	HRESULT	TCOMAPI GetExternalTimeProvider(TimeType type, OTCID& oidProvider) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcExternalTime, IID_ITcExternalTime);

///////////////////////////////////////////////////////////////////////////////
// ITcSetExternalTime
struct	__declspec(novtable)	ITcSetExternalTime : public ITcExternalTime
{
	virtual	HRESULT	TCOMAPI RegisterExternalTimeProvider(OTCID oidProvider, TimeType type) = 0;
	virtual	HRESULT	TCOMAPI UnregisterExternalTimeProvider(OTCID oidProvider, TimeType type) = 0;
	virtual	HRESULT	TCOMAPI SetExternalTimeOffset(OTCID oidProvider, TimeType type, __int64 offset) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcSetExternalTime, IID_ITcSetExternalTime);
#endif

///////////////////////////////////////////////////////////////////////////////
// ITcModuleLibraryHandler
struct __declspec(novtable) ITcModuleLibraryHandler : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetReferenceCount(UINT& referenceCount) = 0;
	virtual HRESULT TCOMAPI IncrementReference() = 0;
	virtual HRESULT TCOMAPI DecrementReference() = 0;
	virtual HRESULT TCOMAPI SetVersionedLibraryInfo(TcTmlVersionedLibraryInfo* pVersionedLibraryInfo) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcModuleLibraryHandler, IID_ITcModuleLibraryHandler);

///////////////////////////////////////////////////////////////////////////////
// ITcData
struct __declspec(novtable) ITcData : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetSize(ULONGLONG& nSize)=0;
	virtual HRESULT TCOMAPI CheckDataPointer()=0;
	virtual HRESULT TCOMAPI GetDataPointer(PVOID* ppData, ULONGLONG* pnData=NULL)=0;
	virtual HRESULT TCOMAPI ReleaseDataPointer(PVOID* ppData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcData, IID_ITcData);

///////////////////////////////////////////////////////////////////////////////
struct	__declspec(novtable) ITcLockable : ITcUnknown
{
	virtual UINT TCOMAPI AcquireLock(ULONG_PTR contex) = 0;
	virtual UINT TCOMAPI ReleaseLock(ULONG_PTR contex) = 0;
	TCOMMETHOD(IsLocked(ULONG_PTR context, BOOL& bLocked));
};
_TCOM_SMARTPTR_TYPEDEF(ITcLockable, IID_ITcLockable);

#define TC_INVALID_LOCK 0xFFFFFFFF

template<UINT NCTX> class CLockableInstance : public ITcLockable
{
	public:

		CLockableInstance()
		{
			memset(m_locks, 0, sizeof(m_locks));
		}

		virtual UINT TCOMAPI AcquireLock(ULONG_PTR context)
		{
			if (context < NCTX)
			{
				return InterlockedIncrementR0(&(m_locks[context]));
			}
			else
				return TC_INVALID_LOCK;
		}

		virtual UINT TCOMAPI ReleaseLock(ULONG_PTR context)
		{
			if (context < NCTX)
			{
				return InterlockedDecrementR0(&(m_locks[context]));
			}
			else
				return TC_INVALID_LOCK;
		}

		virtual HRESULT TCOMAPI IsLocked(ULONG_PTR context, BOOL& bLocked)
		{
			if (context < NCTX)
			{
				bLocked = m_locks[context] == 0 ? FALSE : TRUE;
				return S_OK;
			}
			else
				return ADS_E_INVALIDPARM;
		}

	private:
		ULONG m_locks[NCTX];
};

template<class ITF>
struct DLL_EXPORT SIftEntry
{
	SIftEntry() 
	{
		memset(&list, 0, sizeof(list));
		listHead = NULL;
		ip			= NULL;
	}
	void Release()
	{
		safe_release(ip);
		memset(&list, 0, sizeof(list));
		listHead = NULL;
	}
	bool IsValid()
	{
		return ip != NULL;
	}
	LIST_ENTRY	list;
	LIST_ENTRY*	listHead;
	ITF*			ip;
};

template<class ITF, class DATA>
struct DLL_EXPORT SIftDataEntry : public SIftEntry<ITF>
{
	SIftDataEntry() 
	{
		memset(&data, 0, sizeof(data));
	}
	void Release()
	{
		SIftEntry<ITF>::Release();
		memset(&data, 0, sizeof(data));
	}
	DATA			data;
};

template<class ITF, class DATA>
struct DLL_EXPORT SIftEntrySorted : public SIftDataEntry<ITF, DATA>
{
	SIftEntrySorted() : sortOrder(0) {};
	void Release()
	{
		SIftDataEntry<ITF, DATA>::Release();
		sortOrder = 0;
	}
	ULONG			sortOrder;
};

template<class TYPE, class ITF>
class DLL_EXPORT CItfList
{
public:
	CItfList() : m_count(0)
	{
		InitializeListHead(&m_head);
	}
	virtual	HRESULT Add(TYPE* p, ITF* ipMod)
	{
		ASSERT(p->listHead == NULL);
		if ( p->listHead != NULL )
			return E_FAIL;
		p->ip = ipMod;

		ASSERT(p->ip != NULL);
		if ( p->ip == NULL )
			return E_NOINTERFACE;

		InsertTailList(&m_head, &p->list);	// InsertTailList inserts para2 before para1
		p->listHead	= &m_head;
		p->ip->TcAddRef();
		m_count++;
		return S_OK;
	}
	virtual	HRESULT Remove(TYPE* p)
	{
		ASSERT(p->ip != NULL);
		ASSERT(p->listHead == &m_head);
		if ( p->listHead != &m_head )
			return E_FAIL;
		p->listHead = NULL;
		RemoveEntryList(&p->list);
		safe_release(p->ip);
		m_count--;
		return S_OK;
	}
	virtual	HRESULT RemoveFirst(TYPE*& p)
	{
		p = (TYPE*)m_head.Flink;
		if ( &p->list == &m_head )
		{
			p = NULL;
			return E_FAIL;
		}
		else
		{
			RemoveEntryList(&p->list);
			safe_release(p->ip);
			m_count--;
			return S_OK;
		}
	}
	virtual	bool	GetNext(TYPE*& p)
	{
		if ( p == NULL )
			p = (TYPE*)m_head.Flink;
		else
			p = (TYPE*)p->list.Flink;
		if ( &p->list == &m_head )
		{
			p = NULL;
			return false;
		}
		else
			return true;
	}
	virtual	bool	GetPrev(TYPE*& p)
	{
		if ( p == NULL )
			p = (TYPE*)m_head.Blink;
		else
			p = (TYPE*)p->list.Blink;
		if ( &p->list == &m_head )
		{
			p = NULL;
			return false;
		}
		else
			return true;
	}
	virtual	bool	ListContains(TYPE* p)
	{
		return p->listHead == &m_head;
	}
	virtual	ULONG	Count()
	{
		return m_count;
	}

protected:
	LIST_ENTRY	m_head;
	ULONG			m_count;
};

template<class TYPE, class ITF, class DATA>
class DLL_EXPORT CItfListData : public CItfList<TYPE, ITF>
{
protected:
	using CItfList<TYPE, ITF>::m_head;
	using CItfList<TYPE, ITF>::m_count;
public:
	virtual	HRESULT Add(TYPE* p, ITF* ipMod, DATA data)
	{
		DATA data0;
		memset(&data0, 0, sizeof(DATA));
		ASSERT(p->listHead == NULL);
		if ( p->listHead != NULL )
			return E_FAIL;
		if ( memcmp(&data, &data0, sizeof(DATA)) != 0 )
			p->data = data;
		p->ip = ipMod;

		ASSERT(p->ip != NULL);
		if ( p->ip == NULL )
			return E_NOINTERFACE;

		InsertTailList(&m_head, &p->list);	// InsertTailList inserts para2 before para1
		p->listHead	= &m_head;
		p->ip->TcAddRef();
		m_count++;
		return S_OK;
	}
};

template<class TYPE, class ITF, class DATA, ULONG DEFAULTSORT=100>
class DLL_EXPORT CItfListSorted : public CItfListData<TYPE, ITF, DATA>
{
protected:
	using CItfListData<TYPE, ITF, DATA>::m_head;
	using CItfListData<TYPE, ITF, DATA>::m_count;
public:
	virtual	HRESULT Add(TYPE* p, ITF* ipMod, DATA data, ULONG sortOrder)
	{
		DATA data0;
		memset(&data0, 0, sizeof(DATA));
		ASSERT(p->listHead == NULL);
		if ( p->listHead != NULL )
			return E_FAIL;
		if ( sortOrder != 0 )
			p->sortOrder = sortOrder;
		else if ( p->sortOrder == 0 )
			p->sortOrder = DEFAULTSORT;
		if ( memcmp(&data, &data0, sizeof(DATA)) != 0 )
			p->data = data;
		p->ip = ipMod;

		ASSERT(p->ip != NULL);
		if ( p->ip == NULL )
			return E_NOINTERFACE;

		TYPE* t = (TYPE*)&m_head;
		while ( t->list.Blink != &m_head )
		{
			if ( ((TYPE*)t->list.Blink)->sortOrder <= p->sortOrder )
				break;
			t = (TYPE*)t->list.Blink;
		}
		InsertTailList(&t->list, &p->list);	// InsertTailList inserts para2 before para1
		p->listHead	= &m_head;
		p->ip->TcAddRef();
		m_count++;
		return S_OK;
	}
};


template <typename ValueType, ULONG ValueCount>
class TTcArrayStorageStatic
{
public: 
	typedef ValueType VALUE; 
	typedef ValueType* VALUE_PTR;
	typedef const ValueType* VALUE_CONST_PTR;
	typedef ValueType& VALUE_REF;
	typedef const ValueType& VALUE_CONST_REF;

	TTcArrayStorageStatic()
		: m_nValues(0)
	{
	}
	~TTcArrayStorageStatic()
	{
	}

	bool IsInitialized() const
	{
		return (m_nValues != 0);
	}

	HRESULT Init(ULONG nValues)
	{
		HRESULT hr = S_OK;
		if (nValues != ValueCount)
		{
			hr = ADS_E_INVALIDSIZE;
		}
		else
		{
			m_nValues = nValues;
		}
		return hr;
	}

	VALUE m_pValues[ValueCount];
	ULONG m_nValues;
}; 

template <class ValueType>
class TTcArrayStorageDynamic
{
public: 
	typedef ValueType VALUE; 
	typedef ValueType* VALUE_PTR;
	typedef const ValueType* VALUE_CONST_PTR;
	typedef ValueType& VALUE_REF;
	typedef const ValueType& VALUE_CONST_REF;

	TTcArrayStorageDynamic() 
		: m_pValues(NULL)
		, m_nValues(0)
	{
	}

	~TTcArrayStorageDynamic() 
	{
		safe_delete_a(m_pValues);
	}

	bool IsInitialized() const
	{
		return (m_nValues != 0);
	}

	HRESULT Init(ULONG nValues)
	{
		HRESULT hr = S_OK;
		if (m_pValues != NULL)
		{
			hr = ADS_E_INVALIDSTATE;
		}
		else if (nValues > 0)
		{
			m_pValues = new VALUE[nValues]; 
			if (m_pValues == NULL)
			{
				hr = ADS_E_NOMEMORY;
			}
			else
			{
				m_nValues = nValues; 
			}
		}
		return hr;
	}

	ValueType* m_pValues; 
	ULONG m_nValues;
}; 


template<typename StorageType>
class TTcValueArrayBase
{
public:
	TTcValueArrayBase()
		: m_Storage()
	{
	}

	~TTcValueArrayBase()
	{
	}

	typename StorageType::VALUE_REF operator[](ULONG idx)
	{
		return m_Storage.m_pValues[idx];
	}

	typename StorageType::VALUE_CONST_REF operator[](ULONG idx) const
	{
		return m_Storage.m_pValues[idx];
	}

	operator const typename StorageType::VALUE*() const
	{
		return m_Storage.m_pValues;
	}

	ULONG Count() const 
	{
		return m_Storage.m_nValues;
	}

	ULONG ByteSize() const
	{
		return m_Storage.m_nValues*sizeof(typename StorageType::VALUE);
	}

	PVOID GetBuffer()
	{
		return m_Storage.m_pValues;
	}

	PCVOID GetBuffer() const
	{
		return m_Storage.m_pValues;
	}

protected:
	StorageType m_Storage; 
};

// non-member implementation of begin() and end() to support range based loops
// for classes derived from TTcValueArrayBase
template< typename StorageType >
typename StorageType::VALUE_PTR begin(TTcValueArrayBase< StorageType >& values)
{
	return static_cast<typename StorageType::VALUE_PTR>(values.GetBuffer());
}

template< typename StorageType >
typename StorageType::VALUE_PTR end(TTcValueArrayBase< StorageType >& values)
{
	return static_cast<typename StorageType::VALUE_PTR>(values.GetBuffer()) + values.Count();
}

template< typename StorageType >
typename StorageType::VALUE_CONST_PTR begin(const TTcValueArrayBase< StorageType >& values)
{
	return static_cast<typename StorageType::VALUE_CONST_PTR>(values.GetBuffer());
}

template< typename StorageType >
typename StorageType::VALUE_CONST_PTR end(const TTcValueArrayBase< StorageType >& values)
{
	return static_cast<typename StorageType::VALUE_CONST_PTR>(values.GetBuffer()) + values.Count();
}

template<typename T>
class TTcValueArrayDynamic : public TTcValueArrayBase<TTcArrayStorageDynamic<T>>
{
protected:
	using TTcValueArrayBase<TTcArrayStorageDynamic<T>>::m_Storage;
public:
	HRESULT Init(ULONG nData, PCVOID pData)
	{
		HRESULT hr = S_OK;
		ULONG nValues = nData/sizeof(T);
		if (nValues * sizeof(T) != nData)
		{
			hr = ADS_E_INVALIDSIZE;
		}
		else
		{
			if (!m_Storage.IsInitialized())
			{
				hr = m_Storage.Init(nValues);
			}
			if (SUCCEEDED(hr))
			{
				if (m_Storage.m_nValues != nValues)
				{
					hr = ADS_E_INVALIDSIZE;
				}
				else
				{
					memcpy(m_Storage.m_pValues, pData, nData);
				}
			}
		}
		return hr;
	}

	HRESULT CopyTo(ULONG& nData, PVOID pData)
	{
		HRESULT hr = S_OK;
		if (m_Storage.m_pValues == NULL)
		{
			hr = ADS_E_INVALIDDATA;
		}
		else 
		{
			if (nData < m_Storage.m_nValues * sizeof(T))
			{
				hr = ADS_E_INVALIDSIZE;
			}
			else
			{
				memcpy(pData, m_Storage.m_pValues, m_Storage.m_nValues * sizeof(T));
			}
			nData = m_Storage.m_nValues * sizeof(T);
		}
		return hr;
	}
};


#if defined(IS_R0) || defined(WIN32_RUNTIME)	|| defined(TC_ENVIRONMENT_OS) || defined(POSIX)

#pragma warning(disable:4068)
#pragma region TCOM_MACROS
#pragma warning(default:4068)
///////////////////////////////////////////////////////////////////////////////
struct DLL_EXPORT AUTO_NAMESTR {
	PCHAR	str;
	AUTO_NAMESTR(void) { str=new CHAR[1]; if (str) str[0]=0;}
	AUTO_NAMESTR(PCHAR name) { str=new CHAR[strlen(name)+1]; if (str) strcpy(str, name); }
	~AUTO_NAMESTR() { safe_delete_a(str); }
	AUTO_NAMESTR& operator=(const AUTO_NAMESTR& rhs) {if (this == &rhs) return *this; if (str) safe_delete_a(str); str=new CHAR[strlen(rhs.str)+1]; if (str) strcpy(str, rhs.str); return *this;}
	void	Clear(void) { if (str) str[0]=0; }
};

struct DLL_EXPORT AUTO_TCOM_STATE {
	TCOM_STATE value;
	AUTO_TCOM_STATE(void) : value(TCOM_STATE_INIT) {}
	inline TCOM_STATE *operator & (void) { return &value; }
	inline operator TCOM_STATE (void) { return value; }
	inline bool operator != (const TCOM_STATE& rhs) const { return       value != rhs;       }
	inline bool operator == (const TCOM_STATE& rhs) const { return       value == rhs;       }
	inline bool operator >= (const TCOM_STATE& rhs) const { return (UINT)value >= (UINT)rhs; }
	inline bool operator >  (const TCOM_STATE& rhs) const { return (UINT)value >  (UINT)rhs; }
	inline bool operator <= (const TCOM_STATE& rhs) const { return (UINT)value <= (UINT)rhs; }
	inline bool operator <  (const TCOM_STATE& rhs) const { return (UINT)value <  (UINT)rhs; }
	inline TCOM_STATE & operator = (TCOM_STATE newValue) { return value = newValue; }
};

struct DLL_EXPORT AUTO_TCOM_STATE_INVALID {
	TCOM_STATE value;
	AUTO_TCOM_STATE_INVALID(void) : value(TCOM_STATE_INVALID) {}
	inline TCOM_STATE *operator & (void) { return &value; }
	inline operator TCOM_STATE (void) { return value; }
	inline bool operator != (const TCOM_STATE& rhs) const { return       value != rhs;       }
	inline bool operator == (const TCOM_STATE& rhs) const { return       value == rhs;       }
	inline bool operator >= (const TCOM_STATE& rhs) const { return (UINT)value >= (UINT)rhs; }
	inline bool operator >  (const TCOM_STATE& rhs) const { return (UINT)value >  (UINT)rhs; }
	inline bool operator <= (const TCOM_STATE& rhs) const { return (UINT)value <= (UINT)rhs; }
	inline bool operator <  (const TCOM_STATE& rhs) const { return (UINT)value <  (UINT)rhs; }
	inline TCOM_STATE & operator = (TCOM_STATE newValue) { return value = newValue; }
};

struct AUTO_TCOMADMIN {
	ITComAdmin*	ip;
	AUTO_TCOMADMIN(void) : ip(NULL) {}
};

/*struct DLL_EXPORT AUTO_TCOMOBJECTSERVER {
	ITComObjectServer*	ip;
	AUTO_TCOMOBJECTSERVER(void) : ip(NULL) {}
	~AUTO_TCOMOBJECTSERVER(void) { if (ip) ip->TcRelease(); }
	ITComObjectServer** operator&() {return &ip; }
	operator ITComObjectServer*() const { return ip; }
	operator ITComObjectServer&() const { return *ip; }
	ITComObjectServer& operator*() const { return *ip; }
	ITComObjectServer* operator->() const { return ip; }
	operator bool() const { return ip != NULL; }
	bool operator==(ITComObjectServer* p) { return (ip == p); }
	bool operator==(const AUTO_TCOMOBJECTSERVER& p) { return operator==(p.ip); }
	bool operator==(AUTO_TCOMOBJECTSERVER& p) { return operator==(p.ip); }
	bool operator==(int null) { return ip == NULL; }
	AUTO_TCOMOBJECTSERVER& operator=(int null) { ip = (ITComObjectServer*)null; return *this; }
};
*/

static HRESULT	__hr;

#ifdef _DEBUG
#define DECLARE_THIS_FILE

inline HRESULT TcReportLogWrp(ITComObjectServer* ipSrv, DWORD msgCtrlMask, PCHAR szFormat, ...)
{
	HRESULT hr = S_OK;
	if (ipSrv != NULL)
	{
		va_list pArgs;
		va_start(pArgs, szFormat);
		hr = ipSrv->TcReportLogV(msgCtrlMask, szFormat, pArgs);
		va_end(pArgs);
	}
	return hr;
}

inline HRESULT TcReportLogWrp(ITComObjectServerPtr& spSrv, DWORD msgCtrlMask, PCHAR szFormat, ...)
{
	HRESULT hr = S_OK;
	if (spSrv != NULL)
	{
		va_list pArgs;
		va_start(pArgs, szFormat);
		hr = spSrv->TcReportLogV(msgCtrlMask, szFormat, pArgs);
		va_end(pArgs);
	}
	return hr;
}

#define SUCCEEDED_DBG(hr)	(bool)(((__hr = (HRESULT)(hr)) >= 0) || ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : SUCCEEDED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr))),(TRACE(_T("\n%hs(%d) : ########## SUCCEEDED FAILED '%s' (0x%08X, '%hs')\n"), THIS_FILE, __LINE__, _T(#hr), __hr, AdsGetHResultText(__hr))),0))
#define SUCCEEDED_DBGT(hr, txt)	(bool)(((__hr = (HRESULT)(hr)) >= 0) || ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : SUCCEEDED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, txt) ),(TRACE(_T("\n%hs(%d) : ########## SUCCEEDED FAILED '%s' (0x%08X, '%hs')\n"), THIS_FILE, __LINE__, _T(#hr), __hr, txt)),0))
#define SUCCEEDED_DBG1(hr)	(bool)(((__hr = (HRESULT)(hr)) >= 0) || ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL1 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : SUCCEEDED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ),(TRACE(_T("\n%hs(%d) : ########## SUCCEEDED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr))),0))
#define SUCCEEDED_DBG2(hr)	(bool)(((__hr = (HRESULT)(hr)) >= 0) || ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL2 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : SUCCEEDED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ),(TRACE(_T("\n%hs(%d) : ########## SUCCEEDED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr))),0))
#define SUCCEEDED_DBG3(hr)	(bool)(((__hr = (HRESULT)(hr)) >= 0) || ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL3 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : SUCCEEDED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ),(TRACE(_T("\n%hs(%d) : ########## SUCCEEDED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr))),0))
#define FAILED_DBG(hr)		(bool)(((__hr = (HRESULT)(hr)) < 0) && ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : FAILED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ), TRACE(_T("\n%hs(%d) : ########## FAILED FAILED '%s' (0x%08X, '%hs')\n"), THIS_FILE, __LINE__, _T(#hr), __hr, AdsGetHResultText(__hr)),1))
#define FAILED_DBGT(hr, txt)		(bool)(((__hr = (HRESULT)(hr)) < 0) && ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : FAILED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, txt) ), TRACE(_T("\n%s(%d) : ########## FAILED FAILED '%s' (0x%08X, '%hs')\n"), THIS_FILE, __LINE__, _T(#hr), __hr, txt),1))
#define FAILED_DBG1(hr)		(bool)(((__hr = (HRESULT)(hr)) < 0) && ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL1 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : FAILED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ), TRACE(_T("\n%hs(%d) : ########## FAILED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr)),1))
#define FAILED_DBG2(hr)		(bool)(((__hr = (HRESULT)(hr)) < 0) && ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL2 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : FAILED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ), TRACE(_T("\n%hs(%d) : ########## FAILED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr)),1))
#define FAILED_DBG3(hr)		(bool)(((__hr = (HRESULT)(hr)) < 0) && ( (TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARNLEVEL3 | ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : FAILED('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr)) ), TRACE(_T("\n%hs(%d) : ########## FAILED FAILED '%s'\n"), THIS_FILE, __LINE__, _T(#hr)),1))
#define VERIFY_DBG(hr)			if ((__hr = (HRESULT)(hr)) < 0 && m_spSrv) TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : VERIFY('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, AdsGetHResultText(__hr))
#define VERIFY_DBGT(hr, txt)	if ((__hr = (HRESULT)(hr)) < 0 && m_spSrv) TcReportLogWrp(m_spSrv, ADSLOG_MSGTYPE_WARN | ADSLOG_MSGTYPE_LOG |  ADSLOG_MSGTYPE_STRING, "%s(%d) : VERIFY('%s') failed (0x%08X, '%s')", THIS_FILE, __LINE__, #hr, __hr, txt)
#else
#define DECLARE_THIS_FILE
#define SUCCEEDED_DBG(hr)			(bool)((((HRESULT)(hr)) >= 0))
#define SUCCEEDED_DBGT(hr, txt)	(bool)((((HRESULT)(hr)) >= 0))
#define SUCCEEDED_DBG1(hr)			(bool)((((HRESULT)(hr)) >= 0))
#define SUCCEEDED_DBG2(hr)			(bool)((((HRESULT)(hr)) >= 0))
#define SUCCEEDED_DBG3(hr)			(bool)((((HRESULT)(hr)) >= 0))
#define FAILED_DBG(hr)				(bool)((((HRESULT)(hr)) < 0))
#define FAILED_DBGT(hr, txt)		(bool)((((HRESULT)(hr)) < 0))
#define FAILED_DBG1(hr)				(bool)((((HRESULT)(hr)) < 0))	
#define FAILED_DBG2(hr)				(bool)((((HRESULT)(hr)) < 0))
#define FAILED_DBG3(hr)				(bool)((((HRESULT)(hr)) < 0))
#define VERIFY_DBG(hr)
#define VERIFY_DBGT(hr, txt)
#endif

#if defined(DECLARE_THIS_FILE)
#define DEFINE_THIS_FILE() \
	static LPCSTR THIS_FILE = __FILE__;
#else
#define DEFINE_THIS_FILE()
#endif

#define INTERFACE_ENTRY_ITCOMOBJECT() \
if ( iid == IID_ITcUnknown )\
*pipItf = static_cast<ITComObject*>(this);\
else if ( iid == IID_ITcPersist )\
*pipItf = static_cast<ITComObject*>(this);\
else if ( iid == IID_ITComObject )\
*pipItf = static_cast<ITComObject*>(this);\
else 

#define DECLARE_IPERSIST( CLASSID ) \
virtual	HRESULT TCOMAPI GetClassId( CTCID& classId )	\
{ classId = CLASSID; return S_OK; } \
virtual	CTCID	TCOMAPI GetClassId(void)	\
{ return CLASSID; }

inline GUID	_XorGuids(GUID a, const GUID& b)
{
	for (int i=0; i < 4; ++i) 
		((PULONG)&a)[i] ^= ((PULONG)&b)[i]; 
	return a;
}

inline void	_XorGuids(GUID* pDestGuid, const GUID& a, const GUID& b)
{
	for (int i=0; i < 4; ++i) 
		((PULONG)pDestGuid)[i] = ((PULONG)&a)[i] ^ ((PULONG)&b)[i]; 
}

inline bool _CmpXorGuids(const GUID* pRefGuid, const GUID& a, const GUID& b)
{
	for (int i=0; i < 4; ++i) 
		if(((PULONG)pRefGuid)[i] != (((PULONG)&a)[i] ^ ((PULONG)&b)[i]))
			return false;
	return true;
}

#define DECLARE_IPERSIST_LIB() \
virtual	HRESULT TCOMAPI GetClassId( CTCID& classId ); \
virtual	CTCID	TCOMAPI GetClassId(void);

#define IMPLEMENT_IPERSIST_LIB( theClass, VERID, CLASSID ) \
HRESULT theClass::GetClassId( CTCID& classId )	\
{ _XorGuids(&classId, CLASSID, VERID); return S_OK; } \
CTCID	theClass::GetClassId(void)	\
{ return _XorGuids(CLASSID, VERID); }

#define DECLARE_ITCOMOBJECT() \
protected: \
AUTO_ULONG	m_objId;\
AUTO_ULONG	m_parentObjId;\
AUTO_NAMESTR m_objName; \
ITComObjectServerPtr m_spSrv; \
AUTO_TCOM_STATE m_eTcomState;	\
public: \
virtual	HRESULT TCOMAPI TcGetObjectId( OTCID& objId ) \
{ objId = m_objId; return S_OK; } \
virtual	OTCID	TCOMAPI TcGetObjectId(void) \
{ return m_objId; } \
virtual	HRESULT TCOMAPI TcSetObjectId( OTCID objId ) \
{ m_objId.value = objId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetObjectName( CHAR* objName ); \
virtual	HRESULT TCOMAPI TcGetObjectName( CHAR* objName, ULONG nameLen ); \
virtual	CHAR* TCOMAPI TcGetObjectName(void) \
{ return m_objName.str; } \
virtual	HRESULT TCOMAPI TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	HRESULT TCOMAPI TcGetObjState(TCOM_STATE* pState); \
virtual	HRESULT TCOMAPI TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0); \
virtual	HRESULT TCOMAPI TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0); \
virtual	HRESULT TCOMAPI TcGetParentObjId( OTCID& objId ) \
{ objId = m_parentObjId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetParentObjId( OTCID objId ) \
{ m_parentObjId.value = objId; return S_OK; } 

#define DECLARE_ITCOMOBJECT_NOPARA() \
AUTO_ULONG	m_objId;\
AUTO_ULONG	m_parentObjId;\
AUTO_NAMESTR m_objName; \
ITComObjectServerPtr m_spSrv; \
AUTO_TCOM_STATE m_eTcomState;	\
virtual	HRESULT TCOMAPI TcGetObjectId( OTCID& objId ) \
{ objId = m_objId; return S_OK; } \
virtual	OTCID	TCOMAPI TcGetObjectId(void) \
{ return m_objId; } \
virtual	HRESULT TCOMAPI TcSetObjectId( OTCID objId ) \
{ m_objId.value = objId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetObjectName( CHAR* objName ); \
virtual	HRESULT TCOMAPI TcGetObjectName( CHAR* objName, ULONG nameLen ); \
virtual	CHAR* TCOMAPI TcGetObjectName(void) \
{ return m_objName.str; } \
virtual	HRESULT TCOMAPI TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	HRESULT TCOMAPI TcGetObjState(TCOM_STATE* pState); \
virtual	HRESULT TCOMAPI TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0) \
{ return ADS_E_INVALIDOFFSET; } \
virtual	HRESULT TCOMAPI TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0) \
{ return ADS_E_INVALIDOFFSET; } \
virtual	HRESULT TCOMAPI TcGetParentObjId( OTCID& objId ) \
{ objId = m_parentObjId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetParentObjId( OTCID objId ) \
{ m_parentObjId.value = objId; return S_OK; } 

#define DECLARE_ITCOMOBJECT_LOCKOP_IMPL() \
virtual	HRESULT TCOMAPI TcLockOpState(void) \
{ \
	if ( InterlockedIncrementR0(&m_accessCnt) > 1 )	\
		return S_OK; \
	else { \
		InterlockedDecrementR0(&m_accessCnt); \
		return E_FAIL; \
	} \
}\
virtual	HRESULT TCOMAPI TcReleaseOpState(void) \
{\
	if ( m_eTcomState != TCOM_STATE_OP ) \
		return ADS_E_INVALIDSTATE; \
	ULONG accessCnt = InterlockedDecrementR0(&m_accessCnt); \
	if ( accessCnt == 0 && m_ePendState != TCOM_STATE_INVALID) { \
		TcSetObjState(m_ePendState, NULL, NULL); \
	} \
	return S_OK; \
}\
virtual	HRESULT TCOMAPI TcTryLockOpState(void) \
{ \
	HRESULT hr = S_OK; \
	if ( FAILED(hr = TcLockOpState()) ) \
	{ \
		if (SUCCEEDED(hr = TcSetObjState(TCOM_STATE_OP, NULL, NULL))) \
		{ \
			hr = TcLockOpState(); \
		} \
	} \
	return hr; \
}
	
#define DECLARE_ITCOMOBJECT_LOCKOP() \
AUTO_ULONG	m_objId;\
AUTO_ULONG	m_parentObjId;\
AUTO_NAMESTR m_objName; \
ITComObjectServerPtr m_spSrv; \
AUTO_TCOM_STATE m_eTcomState;	\
AUTO_TCOM_STATE_INVALID	m_ePendState;	\
AUTO_ULONG	m_accessCnt;\
virtual	HRESULT TCOMAPI TcGetObjectId( OTCID& objId ) \
{ objId = m_objId; return S_OK; } \
virtual	OTCID	TCOMAPI TcGetObjectId(void) \
{ return m_objId; } \
virtual	HRESULT TCOMAPI TcSetObjectId( OTCID objId ) \
{ m_objId.value = objId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetObjectName( CHAR* objName ); \
virtual	HRESULT TCOMAPI TcGetObjectName( CHAR* objName, ULONG nameLen ); \
virtual	CHAR* TCOMAPI TcGetObjectName(void) \
{ return m_objName.str; } \
virtual	HRESULT TCOMAPI TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	HRESULT TCOMAPI TcGetObjState(TCOM_STATE* pState); \
virtual	HRESULT TCOMAPI TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0); \
virtual	HRESULT TCOMAPI TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0); \
virtual	HRESULT TCOMAPI TcGetParentObjId( OTCID& objId ) \
{ objId = m_parentObjId; return S_OK; } \
virtual	HRESULT TCOMAPI TcSetParentObjId( OTCID objId ) \
{ m_parentObjId.value = objId; return S_OK; } \
virtual	BOOL	TCOMAPI TcTryToReleaseOpState(); \
DECLARE_ITCOMOBJECT_LOCKOP_IMPL();

#define DECLARE_ITCOMOBJECT_LOCKOP_DERIVED() \
AUTO_TCOM_STATE_INVALID	m_ePendState;	\
AUTO_ULONG	m_accessCnt;\
virtual	HRESULT TCOMAPI TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	BOOL	TCOMAPI TcTryToReleaseOpState(); \
DECLARE_ITCOMOBJECT_LOCKOP_IMPL();

#define DECLARE_PARA() \
virtual	HRESULT TCOMAPI TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp=0); \
virtual	HRESULT TCOMAPI TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp=0);

#define DECLARE_ITCOMOBJECT_SETSTATE() \
virtual	HRESULT	SetObjStateIP(ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	HRESULT	SetObjStatePS(PTComInitDataHdr pInitData); \
virtual	HRESULT	SetObjStateSO(); \
virtual	HRESULT	SetObjStateOS(); \
virtual	HRESULT	SetObjStateSP(); \
virtual	HRESULT	SetObjStatePI(); 

#define DECLARE_ITCOMOBJECT_SETSTATE_RT() \
virtual	HRESULT	SetObjStateIP_RT(ITComObjectServer* ipSrv, PTComInitDataHdr pInitData); \
virtual	HRESULT	SetObjStatePS_RT(PTComInitDataHdr pInitData); \
virtual	HRESULT	SetObjStateSO(); \
virtual	HRESULT	SetObjStateOS(); \
virtual	HRESULT	SetObjStateSP_RT(); \
virtual	HRESULT	SetObjStatePI_RT(); 

#define DECLARE_ITCOMOBJECTCATEGORY() \
virtual	HRESULT	TCOMAPI	EnumCategory(int& idx, CATTCID& catId);

#define BEGIN_TCOM_CATEGORY_MAP(theClass) \
HRESULT	theClass::EnumCategory(int& idx, CATTCID& catId)\
{	int tmp = idx;	\
	if ( tmp < 0 ) return S_FALSE;

#define TCOM_CATEGORY_ENTRY( cid ) \
	else if ( tmp-- == 0 ) catId = cid;

#define END_TCOM_CATEGORY_MAP()\
	else return S_FALSE; \
	idx++;	\
	return S_OK; }

#define END_TCOM_CATEGORY_MAP2(theBase)\
	else {\
		HRESULT hr = theBase::EnumCategory(tmp, catId);\
		idx++;\
		return hr;\
	}\
	idx++;	\
	return S_OK; }

/*
HRESULT	theClass::SetObjStateIP(ITComObjectServer* ipSrv, PTComInitDataHdr pInitData)
{
	HRESULT hr = S_OK;
	m_spSrv = ipSrv;
	if ( m_spSrv == NULL )
		return E_POINTER;

	if ( m_objId == 0 || SUCCEEDED_DBG(hr = m_spSrv->TcAddToObjMap(m_objId, THIS_ITCOMOBJECT)) )
	{
		if ( SUCCEEDED_DBG(hr) && pInitData )
		{
			PTComInitDataElmHdr pInitElmData = PTComInitDataHdrNEXTHDR(pInitData);
			for (int i = 0; i < pInitData->uiElmCnt; i++)
			{
				if ( FAILED_DBG(hr=TcSetObjPara(pInitElmData->indexOffset, pInitElmData->cbData, PTComInitDataElmHdrDATA(pInitElmData), pInitElmData->indexGroup)) )
					break;

				pInitElmData = PTComInitDataElmHdrNEXTHDR(pInitElmData);
			}
		}
		if ( m_objId != 0 && FAILED_DBG(hr) )
			m_spSrv->TcRemoveFromObjMap(m_objId);
	}

	return hr;
}

HRESULT	theClass::SetObjStatePS(PTComInitDataHdr pInitData)
{
	HRESULT hr = S_OK;
	if ( pInitData )
	{
		PTComInitDataElmHdr pInitElmData = PTComInitDataHdrNEXTHDR(pInitData);
		for (int i = 0; i < pInitData->uiElmCnt; i++)
		{
			if ( FAILED(hr=TcSetObjPara(pInitElmData->indexOffset, pInitElmData->cbData, PTComInitDataElmHdrDATA(pInitElmData), pInitElmData->indexGroup)) )
				break;

			pInitElmData = PTComInitDataElmHdrNEXTHDR(pInitElmData);
		}
	}
	return hr;
}

HRESULT	theClass::SetObjStateSO()
{
	HRESULT hr = S_OK;
	return hr;
}

HRESULT	theClass::SetObjStateOS()
{
	HRESULT hr = S_OK;
	return hr;
}

HRESULT	theClass::SetObjStateSP()
{
	HRESULT hr = S_OK;
	return hr;
}

HRESULT	theClass::SetObjStatePI() 
{
	HRESULT hr = S_OK;
	if ( m_objId != 0 )
		hr = m_spSrv->TcRemoveFromObjMap(m_objId);
	if ( SUCCEEDED(hr) )
	{
		m_spSrv				= NULL;
	}
	return hr;
}
*/

#define IMPLEMENT_ITCOMOBJECT(theClass) \
HRESULT	theClass::TcSetObjectName( CHAR* objName ) \
{	safe_delete_a(m_objName.str); \
	m_objName.str = new CHAR[strlen(objName)+1]; \
	if ( m_objName.str ) { \
		strcpy( m_objName.str, objName ); \
		return S_OK; } \
	else return E_OUTOFMEMORY; \
} \
HRESULT	theClass::TcGetObjectName( CHAR* objName, ULONG nameLen ) \
{	if ( objName && nameLen > 0 )	\
	{	strncpy( objName, m_objName.str, nameLen-1 ); objName[nameLen-1] = 0;	} \
	return S_OK; \
}\
HRESULT theClass::TcGetObjState(TCOM_STATE* pState) \
{ *pState = m_eTcomState; return S_OK; }

#ifdef _TRACE_TCOM_STATE_CHANGES
#define TRACE_TCOM_STATE_CHANGES TRACE
#else
#define TRACE_TCOM_STATE_CHANGES 
#endif

#define IMPLEMENT_ITCOMOBJECT_SETSTATE(theClass) \
HRESULT theClass::TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	if ( state > m_eTcomState ) \
	{ \
		if ( m_eTcomState != TCOM_STATE_SAFEOP && state == TCOM_STATE_OP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_INIT ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStateIP(ipSrv, pInitData)) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				pInitData = NULL; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateIP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && state > m_eTcomState ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStatePS(pInitData)) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && state > m_eTcomState ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStateSO()) ) \
					m_eTcomState = TCOM_STATE_OP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSO('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	else if ( state < m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_OP && state != TCOM_STATE_SAFEOP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_OP ) \
			{ \
				m_eTcomState = TCOM_STATE_SAFEOP; \
				if ( FAILED(hr = SetObjStateOS()) ) \
					m_eTcomState = TCOM_STATE_OP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateOS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && state < m_eTcomState ) \
			{ \
				m_eTcomState = TCOM_STATE_PREOP; \
				if ( FAILED(hr = SetObjStateSP()) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && state < m_eTcomState ) \
			{ \
				m_eTcomState = TCOM_STATE_INIT; \
				if ( FAILED(hr = SetObjStatePI()) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePI('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	return hr; \
}
#define IMPLEMENT_ITCOMOBJECT_SETSTATE_RT(theClass) \
HRESULT theClass::TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	if ( state > m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_INIT ) \
		{ \
			if ( SUCCEEDED(hr = SetObjStateIP_RT(ipSrv, pInitData)) ) \
				m_eTcomState = TCOM_STATE_PREOP; \
			pInitData = NULL; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateIP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_PREOP && state > m_eTcomState ) \
		{ \
			if ( SUCCEEDED(hr = SetObjStatePS_RT(pInitData)) ) \
				m_eTcomState = TCOM_STATE_SAFEOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_SAFEOP && state > m_eTcomState ) \
		{ \
			if ( SUCCEEDED(hr = SetObjStateSO()) ) \
				m_eTcomState = TCOM_STATE_OP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSO('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
	} \
	else if ( state < m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_OP ) \
		{ \
			m_eTcomState = TCOM_STATE_SAFEOP; \
			if ( FAILED(hr = SetObjStateOS()) ) \
				m_eTcomState = TCOM_STATE_OP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateOS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_SAFEOP && state < m_eTcomState ) \
		{ \
			m_eTcomState = TCOM_STATE_PREOP; \
			if ( FAILED(hr = SetObjStateSP_RT()) ) \
				m_eTcomState = TCOM_STATE_SAFEOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_PREOP && state < m_eTcomState ) \
		{ \
			m_eTcomState = TCOM_STATE_INIT; \
			if ( FAILED(hr = SetObjStatePI_RT()) ) \
				m_eTcomState = TCOM_STATE_PREOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePI('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
	} \
	return hr; \
}
#define IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP(theClass) \
HRESULT theClass::TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	if ( state > m_eTcomState ) \
	{ \
		if ( m_eTcomState != TCOM_STATE_SAFEOP && state == TCOM_STATE_OP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_INIT ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStateIP(ipSrv, pInitData)) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				pInitData = NULL; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateIP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && state > m_eTcomState ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStatePS(pInitData)) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && state > m_eTcomState ) \
			{ \
				ULONG accessCnt = InterlockedIncrementR0(&m_accessCnt); \
				if ( accessCnt == 1 && SUCCEEDED(hr = SetObjStateSO()) ) \
					m_eTcomState = TCOM_STATE_OP; \
				else {\
					InterlockedDecrementR0(&m_accessCnt); \
					if ( accessCnt != 1 ) \
						hr = ADS_E_INVALIDACCESS; \
				} \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSO('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	else if ( state < m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_OP && state != TCOM_STATE_SAFEOP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_OP ) \
			{ \
				ULONG accessCnt = m_accessCnt; \
				if ( m_ePendState == TCOM_STATE_INVALID ) \
					accessCnt = InterlockedDecrementR0(&m_accessCnt); \
				if ( accessCnt > 0 ) { \
					InterlockedIncrementR0(&m_accessCnt); \
					TcTryToReleaseOpState(); \
					accessCnt = InterlockedDecrementR0(&m_accessCnt); \
				} \
				if ( accessCnt == 0 ) \
				{ \
					m_ePendState = TCOM_STATE_INVALID; \
					m_eTcomState = TCOM_STATE_SAFEOP; \
					if ( FAILED(hr = SetObjStateOS()) ) \
						m_eTcomState = TCOM_STATE_OP; \
				} \
				else \
				{ \
					m_ePendState	= state; \
					state				= m_eTcomState; \
				} \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateOS('%hs') : hr=0x%x pendState %d \n"), m_objName.str, hr, m_ePendState); \
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && state < m_eTcomState ) \
			{ \
				m_eTcomState = TCOM_STATE_PREOP; \
				if ( FAILED(hr = SetObjStateSP()) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && state < m_eTcomState ) \
			{ \
				m_eTcomState = TCOM_STATE_INIT; \
				if ( FAILED(hr = SetObjStatePI()) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePI('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP_WAIT(theClass, waitTimeout) \
HRESULT theClass::TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	if ( (UINT)state > (UINT)m_eTcomState ) \
	{ \
		if ( m_eTcomState != TCOM_STATE_SAFEOP && state == TCOM_STATE_OP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_INIT ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStateIP(ipSrv, pInitData)) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				pInitData = NULL; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateIP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && (UINT)state > (UINT)m_eTcomState ) \
			{ \
				if ( SUCCEEDED(hr = SetObjStatePS(pInitData)) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && (UINT)state > (UINT)m_eTcomState ) \
			{ \
				ULONG accessCnt = InterlockedIncrementR0(&m_accessCnt); \
				if ( accessCnt == 1 && SUCCEEDED(hr = SetObjStateSO()) ) \
					m_eTcomState = TCOM_STATE_OP; \
				else {\
					InterlockedDecrementR0(&m_accessCnt); \
					if ( accessCnt != 1 ) \
						hr = ADS_E_INVALIDACCESS; \
				} \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSO('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	else if ( (UINT)state < (UINT)m_eTcomState ) \
	{ \
		if ( m_ePendState != TCOM_STATE_INVALID && (UINT)state != m_ePendState )\
		{\
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS_LockOp('%hs'), SafeOp->Preop pending : hr=0x%x\n"), m_objName.str, hr);\
			CTimeout	timeout(waitTimeout);\
			while ( m_ePendState != TCOM_STATE_INVALID )\
			{\
				OsDelayExecutionThread(1);\
				if ( timeout.IsElapsed() )\
				{\
					TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS_LockOp('%hs'), Timeout elapsed!: hr=0x%x\n"), m_objName.str, hr);\
					break;\
				}\
			}\
		}\
		if ( m_eTcomState == TCOM_STATE_OP && state != TCOM_STATE_SAFEOP ) \
			hr = ADS_E_INVALIDSTATE; \
		else { \
			if ( m_eTcomState == TCOM_STATE_OP ) \
			{ \
				ULONG accessCnt = m_accessCnt; \
				if ( m_ePendState == TCOM_STATE_INVALID ) \
					accessCnt = InterlockedDecrementR0(&m_accessCnt); \
				if ( accessCnt > 0 ) { \
					InterlockedIncrementR0(&m_accessCnt); \
					TcTryToReleaseOpState(); \
					accessCnt = InterlockedDecrementR0(&m_accessCnt); \
				} \
				if ( accessCnt == 0 ) \
				{ \
					TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS_LockOp('%hs'), Set to SafeOp!: hr=0x%x\n"), m_objName.str, hr);\
					m_eTcomState = TCOM_STATE_SAFEOP; \
					if ( FAILED(hr = SetObjStateOS()) ) \
						m_eTcomState = TCOM_STATE_OP; \
					m_ePendState = TCOM_STATE_INVALID; \
				} \
				else \
				{ \
					TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS_LockOp('%hs'), Set pend state!: hr=0x%x\n"), m_objName.str, hr);\
					m_ePendState	= state; \
					state				= m_eTcomState; \
				} \
					TRACE_TCOM_STATE_CHANGES(_T("SetObjStateOS('%hs') : pendState=%d, hr=0x%x\n"), m_objName.str, m_ePendState, hr);\
			} \
			if ( m_eTcomState == TCOM_STATE_SAFEOP && (UINT)state < (UINT)m_eTcomState ) \
			{ \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS_LockOp('%hs'), SafeOp, set to PreOp!: hr=0x%x\n"), m_objName.str, hr);\
				m_eTcomState = TCOM_STATE_PREOP; \
				if ( FAILED(hr = SetObjStateSP()) ) \
					m_eTcomState = TCOM_STATE_SAFEOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
			if ( m_eTcomState == TCOM_STATE_PREOP && (UINT)state < (UINT)m_eTcomState ) \
			{ \
				m_eTcomState = TCOM_STATE_INIT; \
				if ( FAILED(hr = SetObjStatePI()) ) \
					m_eTcomState = TCOM_STATE_PREOP; \
				TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePI('%hs') : hr=0x%x\n"), m_objName.str, hr); \
			} \
		} \
	} \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP_RT(theClass) \
HRESULT theClass::TcSetObjState(TCOM_STATE state, ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	if ( state > m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_INIT ) \
		{ \
			if ( SUCCEEDED(hr = SetObjStateIP_RT(ipSrv, pInitData)) ) \
				m_eTcomState = TCOM_STATE_PREOP; \
			pInitData = NULL; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateIP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_PREOP && state > m_eTcomState ) \
		{ \
			if ( SUCCEEDED(hr = SetObjStatePS_RT(pInitData)) ) \
				m_eTcomState = TCOM_STATE_SAFEOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePS('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_SAFEOP && state > m_eTcomState ) \
		{ \
			ULONG accessCnt = InterlockedIncrementR0(&m_accessCnt); \
			if ( accessCnt == 1 && SUCCEEDED(hr = SetObjStateSO()) ) \
				m_eTcomState = TCOM_STATE_OP; \
			else {\
				InterlockedDecrementR0(&m_accessCnt); \
				if ( accessCnt != 1 ) \
					hr = ADS_E_INVALIDACCESS; \
			} \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSO('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
	} \
	else if ( state < m_eTcomState ) \
	{ \
		if ( m_eTcomState == TCOM_STATE_OP ) \
		{ \
			ULONG accessCnt = m_accessCnt; \
			if ( m_ePendState == TCOM_STATE_INVALID ) \
				accessCnt = InterlockedDecrementR0(&m_accessCnt); \
			if ( accessCnt > 0 ) { \
				InterlockedIncrementR0(&m_accessCnt); \
				TcTryToReleaseOpState(); \
				accessCnt = InterlockedDecrementR0(&m_accessCnt); \
			} \
			if ( accessCnt == 0 ) \
			{ \
				m_ePendState = TCOM_STATE_INVALID; \
				m_eTcomState = TCOM_STATE_SAFEOP; \
				if ( FAILED(hr = SetObjStateOS()) ) \
					m_eTcomState = TCOM_STATE_OP; \
			} \
			else \
			{ \
				m_ePendState	= state; \
				state				= m_eTcomState; \
			} \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateOS('%hs') : hr=0x%x pendState %d \n"), m_objName.str, hr, m_ePendState); \
		} \
		if ( m_eTcomState == TCOM_STATE_SAFEOP && state < m_eTcomState ) \
		{ \
			m_eTcomState = TCOM_STATE_PREOP; \
			if ( FAILED(hr = SetObjStateSP_RT()) ) \
				m_eTcomState = TCOM_STATE_SAFEOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStateSP('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
		if ( m_eTcomState == TCOM_STATE_PREOP && state < m_eTcomState ) \
		{ \
			m_eTcomState = TCOM_STATE_INIT; \
			if ( FAILED(hr = SetObjStatePI_RT()) ) \
				m_eTcomState = TCOM_STATE_PREOP; \
			TRACE_TCOM_STATE_CHANGES(_T("SetObjStatePI('%hs') : hr=0x%x\n"), m_objName.str, hr); \
		} \
	} \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(theClass) \
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP(theClass) \
BOOL	theClass::TcTryToReleaseOpState() {	return FALSE; }

#define IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2_RT(theClass) \
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP_RT(theClass) \
BOOL	theClass::TcTryToReleaseOpState() {	return FALSE; }

#define DECLARE_ITCOMENSUREOPSTATE() \
virtual	HRESULT TCOMAPI EnsureAndLockOpState(); \
virtual	HRESULT TCOMAPI ReleaseOpState();

#define IMPLEMENT_ITCOMENSUREOPSTATE(theClass) \
HRESULT	theClass::EnsureAndLockOpState() { \
	HRESULT hr; \
	if (m_eTcomState == TCOM_STATE_SAFEOP) \
		if (FAILED(hr = TcSetObjState(TCOM_STATE_OP, NULL, NULL))) return hr; \
	if (m_eTcomState == TCOM_STATE_OP) return TcLockOpState(); \
	else return ADS_E_INVALIDSTATE; \
} \
HRESULT	theClass::ReleaseOpState() {\
	return TcReleaseOpState(); }

#define DECLARE_ITComObjInd() \
virtual	HRESULT	ReadInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, \
						ULONG indexOffset, ULONG cbLength ) = 0; \
virtual	HRESULT	WriteInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, \
		ULONG indexGroup,	ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0; \
virtual	HRESULT	ReadWriteInd( ITComObjRes* ipRes, AmsAddr& rAddr, ULONG invokeId, \
		ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, \
		PVOID pData ) = 0; \
virtual	HRESULT	GetData( ULONG indexGroup, ULONG indexOffset, PVOID& pData, \
		ULONG& nData ) = 0; \
virtual	HRESULT	SetData( ULONG indexGroup, ULONG indexOffset, PVOID pData, \
		ULONG nData ) = 0;

#define	PTR_ARRAY_SIZE(p)	(sizeof(p)/sizeof(PVOID))

#define	RELEASE_IF_DEFINED(ipUnk) \
{ if ( ipUnk ) { ipUnk->TcRelease(); ipUnk = NULL; } } 

#define	RELEASE_IF_DEFINED_ARRAY(ipUnkArr) \
{ for ( int nipUnkArr=0; nipUnkArr < sizeof(ipUnkArr)/sizeof(ITcUnknown*); nipUnkArr++ ) \
	RELEASE_IF_DEFINED(ipUnkArr[nipUnkArr]); } 

#define IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(P) \
if ( SUCCEEDED(hr) && P ) \
{ \
	PTComInitDataElmHdr pInitElmData = PTComInitDataHdrNEXTHDR(P); \
	for (int i = 0; i < pInitData->uiElmCnt; i++) \
	{ \
		if ( FAILED(hr=TcSetObjPara(pInitElmData->indexOffset, pInitElmData->cbData, PTComInitDataElmHdrDATA(pInitElmData), pInitElmData->indexGroup)) ) \
		{ \
			m_spSrv->TcReportLog(ADSLOG_MSGTYPE_LERROR, "TcSetObjPara failed ('%s' OID 0x%08X) hr = 0x%08X, PID = 0x%08X, LEN = %d", m_objName.str, m_objId, hr, pInitElmData->indexOffset, pInitElmData->cbData); \
			if ((hr&0x7FFFF000) == (FACILITY_TC_ADS<<16) && i < 15) \
				hr |= ((i+1) << 12); \
			break; \
		} \
		pInitElmData = PTComInitDataElmHdrNEXTHDR(pInitElmData); \
	} \
}

#define IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(theClass) \
HRESULT theClass::SetObjStateIP(ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	m_spSrv = ipSrv; \
	if ( m_spSrv == NULL ) \
		return E_POINTER; \
	if ( m_objId == 0 || SUCCEEDED(hr = m_spSrv->TcAddToObjMap(m_objId, (ITcUnknownPtr)this)) ) \
	{ \
		IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData) \
		if ( m_objId != 0 && FAILED(hr) ) \
			m_spSrv->TcRemoveFromObjMap(m_objId); \
	} \
	return hr; \
} \
HRESULT theClass::SetObjStatePI() \
{ \
	HRESULT hr = S_OK; \
	if ( m_objId != 0 ) \
		hr = m_spSrv->TcRemoveFromObjMap(m_objId); \
	m_spSrv = NULL; \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_PS_SP(theClass) \
HRESULT theClass::SetObjStatePS(PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData); \
	return hr; \
} \
HRESULT theClass::SetObjStateSP() \
{ \
	HRESULT hr = S_OK; \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_SO_OS(theClass) \
HRESULT theClass::SetObjStateSO() \
{ \
	HRESULT hr = S_OK; \
	return hr; \
} \
HRESULT theClass::SetObjStateOS() \
{ \
	HRESULT hr = S_OK; \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI_RT(theClass) \
HRESULT theClass::SetObjStateIP_RT(ITComObjectServer* ipSrv, PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	m_spSrv = ipSrv; \
	if ( m_spSrv == NULL ) \
		return E_POINTER; \
	if ( m_objId == 0 || SUCCEEDED(hr = m_spSrv->TcAddToObjMap(m_objId, (ITcUnknownPtr)this)) ) \
	{ \
		IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData) \
		if ( m_objId != 0 && FAILED(hr) ) \
			m_spSrv->TcRemoveFromObjMap(m_objId); \
	} \
	return hr; \
} \
HRESULT theClass::SetObjStatePI_RT() \
{ \
	HRESULT hr = S_OK; \
	if ( m_objId != 0 ) \
		hr = m_spSrv->TcRemoveFromObjMap(m_objId); \
	m_spSrv = NULL; \
	return hr; \
}

#define IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_PS_SP_RT(theClass) \
HRESULT theClass::SetObjStatePS_RT(PTComInitDataHdr pInitData) \
{ \
	HRESULT hr = S_OK; \
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData); \
	return hr; \
} \
HRESULT theClass::SetObjStateSP_RT() \
{ \
	HRESULT hr = S_OK; \
	return hr; \
}

#define OBJDATAAREA_INDICATE_GET 0x00000001
#define OBJDATAAREA_INDICATE_SET 0x00000002

#ifdef TC_UNLIMITED_MAP_ENTRIES
#define FINISH_SETOBJPARA \
	SUCCEEDED_DBG(hr); \
	return hr; \
}
#define FINISH_GETOBJPARA \
	return hr; \
}
#else
#define FINISH_SETOBJPARA } else
#define FINISH_GETOBJPARA } else
#endif

#define	BEGIN_SETOBJPARA_MAP(theClass) \
HRESULT theClass::TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp) \
{ \
	HRESULT hr=S_OK; \
	if ( pgp != 0 ) \
		return ADS_E_INVALIDGRP; 

#define	BEGIN_SETOBJPARA_MAP2(theClass, theBase) \
HRESULT theClass::TcSetObjPara(PTCID pid, ULONG nData, PVOID pData, PTCGP pgp) \
{ \
	HRESULT hr=S_OK; \
	if ( pgp != 0 ) \
		return theBase::TcSetObjPara(pid, nData, pData, pgp); 

#define	BEGIN_GETOBJPARA_MAP(theClass) \
HRESULT theClass::TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp) \
{ \
	HRESULT hr=S_OK; \
	if ( pgp != 0 ) \
		return ADS_E_INVALIDGRP; 

#define	BEGIN_GETOBJPARA_MAP2(theClass, theBase) \
HRESULT theClass::TcGetObjPara(PTCID pid, ULONG& nData, PVOID& pData, PTCGP pgp) \
{ \
	HRESULT hr=S_OK; \
	if ( pgp != 0 ) \
		return theBase::TcGetObjPara(pid, nData, pData, pgp); 

#define END_SETOBJPARA_MAP() \
	hr = ((pid&TCOMINITDATAELM_IOFFS_OPTIONAL) == 0) ? ADS_E_INVALIDOFFSET : S_FALSE; \
	SUCCEEDED_DBG(hr); \
	return hr; \
}

#define END_SETOBJPARA_MAP2(theBase) \
	hr = theBase::TcSetObjPara(pid, nData, pData, pgp); \
	SUCCEEDED_DBG(hr); \
	return hr; \
}

#define END_GETOBJPARA_MAP() \
	hr = ADS_E_INVALIDOFFSET; \
	return hr; \
}

#define END_GETOBJPARA_MAP2(theBase) \
	hr = theBase::TcGetObjPara(pid, nData, pData, pgp); \
	return hr; \
}

#define	SETOBJPARA_ITFPTR(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( nData == sizeof(OTCID) )  \
		ITFPTR.SetOID(*(OTCID*)pData);  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
FINISH_SETOBJPARA 

#define	SETOBJPARA_SORTORDER(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( nData == sizeof(ULONG) )  \
		ITFPTR.GetInfo()->sortOrder=(*(ULONG*)pData);  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
FINISH_SETOBJPARA 

#define	SETOBJPARA_TYPE_VALUE(PID, TYPE, VALUE)	\
if (PID==pid) {  \
	if ( nData == sizeof(TYPE) )  \
		VALUE = *(TYPE*)pData;  \
	else hr = ADS_E_INVALIDSIZE;  \
FINISH_SETOBJPARA 

#define SETOBJPARA_PTR_SIZE(PID, PTR, SIZE) \
if ((PID) == pid) { \
	if (nData == (SIZE)) { \
		memcpy(PTR, pData, (size_t)SIZE); \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTR_CNT_ALLOC(PID, TYPE, PTR, CNT) \
if ((PID) == pid) { \
	safe_delete_a(PTR); \
	CNT = nData/sizeof(TYPE); \
	if ( nData > 0 ) { \
		PTR = (TYPE*)new BYTE[nData]; \
		if ( PTR ) \
			memcpy(PTR, pData, (size_t)nData); \
		else { \
			CNT = 0; \
			hr = ADS_E_NOMEMORY; \
		} \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTR_ARR_ALLOC(PID, TYPE, PTR) \
if ((PID) == pid) { \
	if (nData > 0 && (nData % sizeof(TYPE)) == 0) { \
		safe_delete_a(PTR); \
		PTR = new TYPE[nData/sizeof(TYPE)]; \
		if ( PTR ) \
			memcpy(PTR, pData, (size_t)nData); \
		else \
			hr = ADS_E_NOMEMORY; \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTR_ALLOC(PID, TYPE, PTR) \
if ((PID) == pid) { \
	if (nData >= sizeof(TYPE)) { \
		safe_delete_a(PTR); \
		PTR = (TYPE*)new BYTE[nData]; \
		if ( PTR ) \
			memcpy(PTR, pData, (size_t)nData); \
		else \
			hr = ADS_E_NOMEMORY; \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTR_CNT_ARR_ALLOC(PID, TYPE, PTR, CNT) \
if ((PID) == pid) { \
	if ((nData % sizeof(TYPE)) == 0) { \
		safe_delete_a(PTR); \
		CNT = nData/sizeof(TYPE); \
		if (nData > 0){\
			PTR = new TYPE[CNT]; \
			if ( PTR ) \
				memcpy(PTR, pData, (size_t)nData); \
			else { \
				CNT = 0; \
				hr = ADS_E_NOMEMORY; \
			} \
		} \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
FINISH_SETOBJPARA

#define SETOBJPARA_TYPE_PTR_SIZE_ALLOC(PID, TYPE, PTR, SIZE) \
if ((PID) == pid) { \
	safe_delete_a(PTR); \
	SIZE = nData; \
	if ( nData > 0 ) { \
		PTR = (TYPE*)new BYTE[nData]; \
		if ( PTR ) \
			memcpy(PTR, pData, (size_t)nData); \
		else { \
			SIZE = 0; \
			hr = ADS_E_NOMEMORY; \
		} \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTRARR_SIZE_ALLOC(PID, TYPE, PTR, SIZE, ARRSIZE) \
if (pid >= (PID) && pid < (PID)+ARRSIZE) { \
	safe_delete_a(PTR[pid-(PID)]); \
	SIZE[pid-(PID)] = nData; \
	if ( nData > 0 ) { \
		PTR[pid-(PID)] = (TYPE*)new BYTE[nData]; \
		if ( PTR[pid-(PID)] ) \
			memcpy(PTR[pid-(PID)], pData, (size_t)nData); \
		else { \
			SIZE[pid-(PID)] = 0; \
			hr = ADS_E_NOMEMORY; \
		} \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_TYPE_PTRARR_ALLOC(PID, TYPE, PTR, ARRSIZE) \
if (pid >= (PID) && pid < (PID)+ARRSIZE) { \
	safe_delete_a(PTR[pid-(PID)]); \
	if ( nData > 0 ) { \
		PTR[pid-(PID)] = (TYPE*)new BYTE[nData]; \
		if ( PTR[pid-(PID)] ) \
			memcpy(PTR[pid-(PID)], pData, (size_t)nData); \
		else \
			hr = ADS_E_NOMEMORY; \
	} \
FINISH_SETOBJPARA 

#define SETOBJPARA_VALUE(PID, VALUE) SETOBJPARA_PTR_SIZE(PID, &VALUE, sizeof(VALUE))

#define SETOBJPARA_VALUE_ARRAY(PID, VALUE_ARRAY) \
if ((PID) == pid) { \
	hr = VALUE_ARRAY.Init(nData, pData); \
FINISH_SETOBJPARA 

#define SETOBJPARA_DATAAREA_MAP() \
if ( TcDataAreaPidCheck(pid) ) { \
	PVOID pDataArea = NULL; \
	hr = TcGetObjDataAreaPtr(TcDataAreaPidGetAreaNo(pid), TcDataAreaPidGetByteOffset(pid), nData, &pDataArea, OBJDATAAREA_INDICATE_SET); \
	if (SUCCEEDED(hr)) TcDataAreaPidSetValue(pid, pDataArea, pData, nData); \
FINISH_SETOBJPARA 

#define SETOBJPARA_WATCH_MAP() \
if ( 1 ) { \
	PVOID pMember = NULL; \
	hr = TcGetObjWatchPtr(pid, nData, &pMember); \
	if (SUCCEEDED(hr)) memcpy(pMember, pData, nData); \
FINISH_SETOBJPARA 

#define	SETOBJPARA_CODE(PID, CODE)	\
if (PID==pid) { \
	CODE; \
FINISH_SETOBJPARA 

#define	SETOBJPARA_EXP_CODE(EXP, CODE)	\
if (EXP(pid)) { \
	CODE; \
FINISH_SETOBJPARA 

#define SETOBJPARA_FUNC(PID, FUNC) \
if ((PID) == pid) { \
	hr = FUNC(pid, nData, pData); \
FINISH_SETOBJPARA 

#define	SETOBJPARA_TYPE_CODE(PID, TYPE, CODE)	\
if (PID==pid) {  \
	if ( nData == sizeof(TYPE) ) {  \
		TYPE* p = (TYPE*)pData; \
		CODE; \
	} else hr = ADS_E_INVALIDSIZE; \
FINISH_SETOBJPARA 

#define	SETOBJPARA_TYPE_SIZE_CODE(PID, TYPE, SIZE, CODE)	\
if (PID==pid) { \
	if ( nData >= sizeof(TYPE) ) { \
		TYPE* p = (TYPE*)pData; \
		if ( SIZE == nData ) { \
			CODE; \
		} else \
			hr = ADS_E_INVALIDSIZE; \
	} else hr = ADS_E_INVALIDSIZE; \
FINISH_SETOBJPARA 

#define SETOBJPARA_PCHAR(PID, PTR) \
if ((PID) == pid) { \
	safe_delete_a(PTR); \
	if ( nData > 0 ) { \
		PTR = new CHAR[nData+1]; \
		if ( PTR ) { \
			memcpy(PTR, pData, (size_t)nData); \
			PTR[nData] = 0; \
		} else { \
			hr = ADS_E_NOMEMORY; \
		} \
	} \
FINISH_SETOBJPARA 

#define	SETOBJPARA_DATAPTR(PID, DATAPTR)	\
if (PID==pid) {  \
	if ( nData == sizeof(TcIoAdiInitData) )  \
		DATAPTR.SetADI(reinterpret_cast<TcIoAdiInitData*>(pData));  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
FINISH_SETOBJPARA 

#define SETOBJPARA_DATAPTR_ARRAY(PID, DATAPTR_ARRAY) \
if ((PID) == pid) { \
	hr = DATAPTR_ARRAY.Init(nData, pData); \
FINISH_SETOBJPARA 

#define SETOBJPARA_DATAAREAPID_VALUE(PID, VALUE) \
	if (TcDataAreaPidCheck(pid, TcDataAreaPidGetAreaNo(PID), TcDataAreaPidGetByteOffset(PID), sizeof(VALUE))) { \
		hr = TcGetSizePtr(&VALUE, sizeof(VALUE), TcDataAreaPidGetByteOffset(pid)-TcDataAreaPidGetByteOffset(PID), nData, &pMember, OBJDATAAREA_INDICATE_SET); \
		if (SUCCEEDED(hr))  memcpy(pMember, pData, (size_t)nData); \
	FINISH_SETOBJPARA 

#define SETOBJPARA_DATAAREAPID_VALUE_CODE(PID, VALUE, CODE) \
	if (TcDataAreaPidCheck(pid, TcDataAreaPidGetAreaNo(PID), TcDataAreaPidGetByteOffset(PID), sizeof(VALUE))) { \
		hr = TcGetSizePtr(&VALUE, sizeof(VALUE), TcDataAreaPidGetByteOffset(pid)-TcDataAreaPidGetByteOffset(PID), nData, &pMember, OBJDATAAREA_INDICATE_SET); \
		if (SUCCEEDED(hr)) { \
			memcpy(pMember, pData, (size_t)nData); \
			CODE \
		} \
	FINISH_SETOBJPARA 

#define SETOBJPARA_DATAAREAPID_VALUE_DENIED(PID, VALUE) \
	if (TcDataAreaPidCheck(pid, TcDataAreaPidGetAreaNo(PID), TcDataAreaPidGetByteOffset(PID), sizeof(VALUE))) { \
		hr=ADS_E_ACCESSDENIED; \
	FINISH_SETOBJPARA 

#pragma deprecated("SETOBJPARA_DATAAREAPID_VALUE", "SETOBJPARA_DATAAREAPID_VALUE_CODE", "SETOBJPARA_DATAAREAPID_VALUE_DENIED" )

#define SETOBJPARA_VALUE_DENIED(PID, VALUE) \
	SETOBJPARA_CODE(PID, hr=ADS_E_ACCESSDENIED)

#define	SETOBJPARA_AGGREGATE(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( ITFPTR )  \
		return ITFPTR->TcSetObjPara(pid, nData, pData, pgp);  \
	else hr = ADS_E_NOINTERFACE;  \
FINISH_SETOBJPARA 

#define	SETOBJPARA_AGGREGATE2(PID, ITFPTR)	\
if (PID==pid) {  \
	ITComObjectPtr spObj(ITFPTR);  \
	if ( spObj )  \
		return spObj->TcSetObjPara(pid, nData, pData, pgp);  \
	else  \
		hr = ADS_E_NOINTERFACE;  \
FINISH_SETOBJPARA 

#define SETOBJPARA_STRING(PID, STR) \
if ((PID) == pid) { \
	if (nData > 0)	{ \
		if (((PCHAR)pData)[nData - 1] == '\0')	STR = (PCHAR)pData; \
		else { \
			STR.assign((PCCH)pData, nData); \
			STR.resize(strlen(STR.c_str())); \
		} \
	} else STR.clear(); \
FINISH_SETOBJPARA

#define SETOBJPARA_VECTOR(PID, VEC) \
if ((PID) == pid) { \
	VEC.resize(nData/sizeof(*VEC.data())); \
	if (nData > 0)	{ \
		memcpy(VEC.data(), pData, (nData/sizeof(*VEC.data()))*sizeof(*VEC.data())); \
	} \
FINISH_SETOBJPARA


#define	GETOBJPARA_ITFPTR(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( nData >= sizeof(OTCID) )  \
		*(OTCID*)pData = ITFPTR.GetOID();  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
	nData = sizeof(OTCID);  \
FINISH_GETOBJPARA 

#define	GETOBJPARA_SORTORDER(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( nData >= sizeof(ULONG) )  \
		*(ULONG*)pData = ITFPTR.GetInfo()->sortOrder;  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
	nData = sizeof(ULONG);  \
FINISH_GETOBJPARA 

#define	GETOBJPARA_TYPE_VALUE(PID, TYPE, VALUE)	\
if (PID==pid) {  \
	if ( nData >= sizeof(TYPE) )  \
		*(TYPE*)pData = VALUE;  \
	else  \
		hr = ADS_E_INVALIDSIZE;  \
	nData = sizeof(TYPE);  \
FINISH_GETOBJPARA 

#define GETOBJPARA_PTR_SIZE(PID, PTR, SIZE) \
if ((PID) == pid) { \
	if (nData >= (SIZE)) { \
		memcpy(pData, PTR, (size_t)SIZE); \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
	nData = (SIZE);\
FINISH_GETOBJPARA 

#define GETOBJPARA_VALUE(PID, VALUE) GETOBJPARA_PTR_SIZE(PID, &VALUE, sizeof(VALUE))

#define GETOBJPARA_TYPE_PTR_CNT(PID, TYPE, PTR, CNT) \
if ((PID) == pid) { \
	if (nData >= (CNT)*sizeof(TYPE)) { \
		memcpy(pData, PTR, (size_t)(CNT)*sizeof(TYPE)); \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
	nData = (CNT)*sizeof(TYPE);\
FINISH_GETOBJPARA 

#define GETOBJPARA_VALUE_ARRAY(PID, VALUE_ARRAY) \
if ((PID) == pid) { \
	hr = VALUE_ARRAY.CopyTo(nData, pData); \
FINISH_GETOBJPARA 

#define	GETOBJPARA_DATAAREA_MAP() \
if ( TcDataAreaPidCheck(pid) ) { \
	PVOID pDataArea = NULL; \
	hr = TcGetObjDataAreaPtr(TcDataAreaPidGetAreaNo(pid), TcDataAreaPidGetByteOffset(pid), nData, &pDataArea, OBJDATAAREA_INDICATE_GET); \
	if (SUCCEEDED(hr)) TcDataAreaPidGetValue(pid, pDataArea, pData, nData); \
FINISH_GETOBJPARA 

#define GETOBJPARA_WATCH_MAP() \
if ( 1 ) { \
	PVOID pMember = NULL; \
	hr = TcGetObjWatchPtr(pid, nData, &pMember); \
	if (SUCCEEDED(hr)) memcpy(pData, pMember, (size_t)nData); \
FINISH_GETOBJPARA 

#define	GETOBJPARA_AGGREGATE(PID, ITFPTR)	\
if (PID==pid) {  \
	if ( ITFPTR )  \
		return ITFPTR->TcGetObjPara(pid, nData, pData, pgp);  \
	else hr = ADS_E_NOINTERFACE;  \
FINISH_GETOBJPARA 

#define	GETOBJPARA_AGGREGATE2(PID, ITFPTR)	\
if (PID==pid) {  \
	ITComObjectPtr spObj(ITFPTR);  \
	if ( spObj )  \
		return spObj->TcGetObjPara(pid, nData, pData, pgp);  \
	else  \
		hr = ADS_E_NOINTERFACE;  \
FINISH_GETOBJPARA 

#define	GETOBJPARA_CODE(PID, CODE)	\
if (PID==pid) { \
	CODE; \
FINISH_GETOBJPARA 

#define GETOBJPARA_FUNC(PID, FUNC) \
if ((PID) == pid) { \
	hr = FUNC(pid, nData, pData); \
FINISH_GETOBJPARA 

#define	GETOBJPARA_EXP_CODE(EXP, CODE)	\
if (EXP(pid)) { \
	CODE; \
FINISH_GETOBJPARA 

#define	GETOBJPARA_TYPE_CODE(PID, TYPE, CODE)	\
if (PID==pid) {  \
	if ( nData >= sizeof(TYPE) ) {  \
		TYPE* p = (TYPE*)pData; \
		CODE; \
	} else  \
		hr = ADS_E_INVALIDSIZE;  \
	nData = sizeof(TYPE);  \
FINISH_GETOBJPARA 

#define	GETOBJPARA_TYPE_SIZE_CODE(PID, TYPE, SIZE, CODE)	\
if (PID==pid) {  \
	if ( nData >= SIZE ) {  \
		TYPE* p = (TYPE*)pData; \
		CODE; \
	} else  \
		hr = ADS_E_INVALIDSIZE;  \
	nData = SIZE;  \
FINISH_GETOBJPARA 

#define GETOBJPARA_PCHAR(PID, PTR) \
if ((PID) == pid) { \
	if (PTR) { \
		if (nData >= strlen(PTR)) { \
			memcpy(pData, PTR, strlen(PTR)); \
		} else {\
			hr = ADS_E_INVALIDSIZE; \
		} \
		nData = (UINT)strlen(PTR);\
	} else \
		nData = 0;\
FINISH_GETOBJPARA 

#define GETOBJPARA_DATAAREAPID_VALUE(PID, VALUE) \
	if (TcDataAreaPidCheck(pid, TcDataAreaPidGetAreaNo(PID), TcDataAreaPidGetByteOffset(PID), sizeof(VALUE))) { \
		hr = TcGetSizePtr(&VALUE, sizeof(VALUE), TcDataAreaPidGetByteOffset(pid)-TcDataAreaPidGetByteOffset(PID), nData, &pMember, OBJDATAAREA_INDICATE_GET); \
		if (SUCCEEDED(hr)) memcpy(pData, pMember, (size_t)nData); \
	FINISH_GETOBJPARA 

#pragma deprecated("GETOBJPARA_DATAAREAPID_VALUE")

#define	GETOBJPARA_ITFLIST_MEMBERS(PID, LIST, TYPE)	\
if (PID==pid) {  \
	if ( nData >= sizeof(OTCID)*LIST.Count() ) { \
		UINT n=0; \
		TYPE* i=NULL; \
		ITComObjectPtr spObj; \
		while (LIST.GetNext(i)) { \
			if ( SUCCEEDED(i->ip->TcQueryInterface(IID_ITComObject, (PVOID*)&spObj)) ) { \
				if ( SUCCEEDED(spObj->TcGetObjectId((((OTCID*)pData)[n]))) ) \
					n++; \
			} \
		} \
		nData = sizeof(OTCID)*n;  \
	} else  \
		hr = ADS_E_INVALIDSIZE;  \
FINISH_GETOBJPARA

#define	GETOBJPARA_ITFLIST_MEMBERS_CRITICAL(PID, LIST, TYPE)	\
if (PID==pid) {  \
	if ( SUCCEEDED(hr=EnterCriticalSection()) ) { \
		if ( nData >= sizeof(OTCID)*LIST.Count() ) { \
			UINT n=0; \
			TYPE* i=NULL; \
			ITComObjectPtr spObj; \
			while (LIST.GetNext(i)) { \
				if ( SUCCEEDED(i->ip->TcQueryInterface(IID_ITComObject, (PVOID*)&spObj)) ) { \
					if ( SUCCEEDED(spObj->TcGetObjectId((((OTCID*)pData)[n]))) ) \
						n++; \
				} \
			} \
			nData = sizeof(OTCID)*n;  \
		} else  \
			hr = ADS_E_INVALIDSIZE;  \
		LeaveCriticalSection(); \
	} \
FINISH_GETOBJPARA

#define GETOBJPARA_STRING(PID, STR) \
if ((PID) == pid) { \
	if (nData >= STR.length()) { \
			memcpy(pData, STR.c_str(), STR.length()); \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
	nData = (UINT)STR.length();\
FINISH_GETOBJPARA 

#define GETOBJPARA_VECTOR(PID, VEC) \
if ((PID) == pid) { \
	if (nData >= VEC.size() * sizeof(*VEC.data())) { \
			memcpy(pData, VEC.data(), VEC.size() * sizeof(*VEC.data())); \
	} else {\
		hr = ADS_E_INVALIDSIZE; \
	} \
	nData = (UINT)VEC.size() * sizeof(*VEC.data());\
FINISH_GETOBJPARA 

#define	IMPLEMENT_ITCOMOBJECT_GENERIC_SETTER(HR, IP, PID, LEN, DATA) \
switch ( PID ) \
{ \
case PID_TComObjName: \
	if ( LEN > 0 ) \
	{ \
		PCHAR pChar = (PCHAR)DATA; \
		CHAR name[TCOMOBJ_NAME_LEN+1]={0}; \
		strncpy(name, pChar, TCOMOBJ_NAME_LEN); \
		HR = IP->TcSetObjectName(name); \
	} \
	else \
		HR = IP->TcSetObjectName(""); \
	break; \
case PID_TComObjParentId: \
	if ( LEN == sizeof(OTCID) ) \
		HR = IP->TcSetParentObjId(*(OTCID*)DATA); \
	else \
		HR = ADS_E_INVALIDSIZE; \
	break; \
}

#define	IMPLEMENT_ITCOMOBJECT_GENERIC_GETTER(HR, IP, PID, LEN, DATA) \
switch ( PID ) \
{ \
case PID_TComObjName: \
	if ( SUCCEEDED(HR=IP->TcGetObjectName((PCHAR)DATA, LEN-1)) ) \
		LEN = (ULONG)strlen((PCHAR)DATA)+1; \
	break; \
case PID_TComObjParentId: \
	if ( LEN >= sizeof(OTCID) ) \
	{ \
		if ( SUCCEEDED(HR=IP->TcGetParentObjId(*(OTCID*)DATA)) ) \
			LEN = sizeof(OTCID); \
	} \
	else HR = ADS_E_INVALIDSIZE; \
	break; \
case PID_TComObjState: \
	if ( LEN >= sizeof(TCOM_STATE) ) \
	{ \
		if ( SUCCEEDED(HR=IP->TcGetObjState((TCOM_STATE*)DATA)) ) \
			LEN = sizeof(TCOM_STATE); \
	} \
	else HR = ADS_E_INVALIDSIZE; \
	break; \
case PID_TComObjRefCount: \
	if ( LEN >= sizeof(ULONG) ) \
	{ \
		ITcUnknown* ipUnk; \
		if ( SUCCEEDED(HR=IP->TcQueryInterface(IID_ITcUnknown, (PPVOID)&ipUnk)) ) \
		{ \
			*(PULONG)DATA = ipUnk->TcRelease(); \
			LEN = sizeof(ULONG); \
		} \
	} \
	else HR = ADS_E_INVALIDSIZE; \
	break; \
case PID_TComObjClassId: \
	if ( LEN >= sizeof(CTCID) ) \
	{ \
		ITcPersistPtr spPersist(IP); \
		if ( spPersist ) \
		{ \
			if ( SUCCEEDED(HR=spPersist->GetClassId(*(CTCID*)DATA)) ) \
				LEN = sizeof(CTCID); \
		} \
		else \
			hr = ADS_E_NOINTERFACE; \
	} \
	else HR = ADS_E_INVALIDSIZE; \
	break; \
}

#define 	TCOBJPARAASYNC_DEFAULT_RESULT(PID, INFO, IPRES)	((PID&TCOMINITDATAELM_IOFFS_OPTIONAL) == 0 || INFO.serviceId == ADSSRVID_READ || INFO.serviceId == ADSSRVID_WRITE) \
	? ADS_E_INVALIDOFFSET : IPRES->TcObjParaRes(INFO, S_FALSE, 0, NULL)

template <class TYPE> void IncrementPointerNBytes(TYPE* p, UINT n)
{
	p = (TYPE*)&((PBYTE)p)[n];
}

#define	PID_TCOMOBJSUMUPREAD_IMPLEMENTATION(PADS, RADDR, INVOKEID, OBJ, RLEN, WLEN, PDATA)	 \
if ( WLEN%(2*sizeof(ULONG)) == 0 ) \
{ \
	PULONG pUWrite = (PULONG)PDATA; \
	UINT i, cnt = WLEN / (2*sizeof(ULONG)); \
	UINT readLength = cnt*sizeof(HRESULT) + cnt*sizeof(ULONG); \
	for ( i=0; i < cnt; i++ ) \
		readLength += pUWrite[i*2 + 1]; \
	if ( readLength <= RLEN ) \
	{											   \
		PAmsCmd  pRes = (PAmsCmd)PADS->AdsAlloc(sizeof(AmsHead)+SIZEOF_TAdsReadWriteResHead+readLength); \
		if ( pRes ) \
		{ \
			PTAdsReadWriteRes pAds		= (PTAdsReadWriteRes)ENDOF(pRes); \
			readLength = 0; \
			PULONG pURead = (PULONG)&pAds->firstDataWord; \
			for ( i=0; i < cnt; i++ ) \
			{ \
				pURead[1] = pUWrite[i*2 + 1]; \
				PVOID pVoid = &pURead[2]; \
				if ( FAILED(pURead[0] = OBJ->TcGetObjPara(pUWrite[i*2 + 0], pURead[1], pVoid)) ) \
					pURead[1] = 0; \
				if ( pURead[1] > 0 && pVoid != &pURead[2] ) \
					memcpy(&pURead[2], pVoid, pURead[1]); \
				IncrementPointerNBytes<ULONG>(pURead, 2*sizeof(ULONG)+pURead[1]); \
			} \
			PADS->AmsMakeHead( pRes->head, ADSSRVID_READWRITE, SIZEOF_TAdsReadWriteResHead+readLength, RADDR.netId, \
								RADDR.port, INVOKEID, 0, AMSCMDSF_ADSCMD | AMSCMDSF_RESPONSE ); \
			pAds->result			= ADSERR_NOERR;   \
			pAds->cbLength			= readLength; \
			PADS->AmsSend( pRes ); \
		} \
		else \
			PADS->AdsReadWriteRes(RADDR, INVOKEID, ADSERR_DEVICE_NOMEMORY, 0, NULL); \
	} \
	else \
		PADS->AdsReadWriteRes(RADDR, INVOKEID, ADSERR_DEVICE_INVALIDSIZE, 0, NULL); \
} \
else \
	PADS->AdsReadWriteRes(RADDR, INVOKEID, ADSERR_DEVICE_INVALIDSIZE, 0, NULL);

#define	PID_TCOMOBJSUMUPWRITE_IMPLEMENTATION(PADS, RADDR, INVOKEID, OBJ, WLEN, PDATA)	 \
UINT i, offs=0, cnt=0; \
PBYTE pByte = (PBYTE)PDATA; \
while ( offs < WLEN ) \
{ \
	if ( WLEN >= offs + 2*sizeof(ULONG) ) \
	{ \
		PULONG pUWrite = (PULONG)pByte[offs]; \
		if ( WLEN >= offs + 2*sizeof(ULONG) + pUWrite[1] ) \
		{ \
			cnt++; \
			offs += 2*sizeof(ULONG) + pUWrite[1]; \
		} \
		else \
		{ \
			PADS->AdsReadWriteRes(RADDR, INVOKEID, ADSERR_DEVICE_INVALIDDATA, 0, NULL); \
			return; \
		} \
	} \
} \
PAmsCmd  pRes = (PAmsCmd)PADS->AdsAlloc(sizeof(AmsHead)+SIZEOF_TAdsReadWriteResHead+cnt*sizeof(HRESULT)); \
if ( pRes ) \
{				  \
	PTAdsReadWriteRes pAds		= (PTAdsReadWriteRes)ENDOF(pRes); \
	PULONG pURead = (PULONG)&pAds->firstDataWord; \
	PULONG pUWrite = (PULONG)PDATA; \
	for ( i=0; i < cnt; i++ ) \
	{																				  \
		pURead[i] = OBJ->TcSetObjPara(pUWrite[0], pUWrite[1], &pUWrite[2]); \
		IncrementPointerNBytes<ULONG>(pUWrite, 2*sizeof(ULONG)+pUWrite[1]); \
	} \
	PADS->AmsMakeHead( pRes->head, ADSSRVID_READWRITE, SIZEOF_TAdsReadWriteResHead+cnt*sizeof(HRESULT), RADDR.netId, \
						RADDR.port, INVOKEID, 0, AMSCMDSF_ADSCMD | AMSCMDSF_RESPONSE ); \
	pAds->result			= ADSERR_NOERR;   \
	pAds->cbLength			= cnt*sizeof(HRESULT); \
	PADS->AmsSend( pRes );	 \
} \
else \
	PADS->AdsReadWriteRes(RADDR, INVOKEID, ADSERR_DEVICE_NOMEMORY, 0, NULL);

///////////////////////////////////////////////////////////////////////////////
// TcDataAreaPid 
inline VOID TcDataAreaPidSetValue(PTCID pid, PVOID pDataArea, PVOID pData, UINT nData)
{
	if (TcDataAreaPidIsBitType(pid))
	{
		if (*(PBYTE)pData == 0)
		{
			*(PBYTE)pDataArea &= ~(1 << (TcDataAreaPidGetBitOffset(pid)%8));
		}
		else
		{
			*(PBYTE)pDataArea |= (1 << (TcDataAreaPidGetBitOffset(pid)%8));
		}
	}
	else
	{
		memcpy(pDataArea, pData, nData); 
	}
}

inline VOID TcDataAreaPidGetValue(PTCID pid, PVOID pDataArea, PVOID pData, UINT nData)
{
	if (TcDataAreaPidIsBitType(pid))
	{
		*(PBYTE)pData = ((*(PBYTE)pDataArea) & (1 << (TcDataAreaPidGetBitOffset(pid)%8))) != 0 ? 1 : 0;
	}
	else
	{
		memcpy(pData, pDataArea, nData);
	}
}

inline HRESULT TcGetSizePtr(PVOID pPtr, ULONG nPtr, ULONG nOffset, ULONG& nData, PVOID* ppData, ULONG flags=0)
{
	HRESULT hr = S_OK;
	if ( nData > 0 )
	{
		if (ppData == NULL || pPtr == NULL)
			hr = E_POINTER;
		else if (nOffset >= nPtr)
			hr = ADS_E_INVALIDDATA;
		else
		{
			if ((nData+nOffset > nPtr) && (flags & OBJDATAAREA_INDICATE_GET) != 0)
			{
				nData = nPtr - nOffset;
			}
			
			if ( nData+nOffset <= nPtr)
			{
				*ppData = reinterpret_cast<PBYTE>(pPtr)+nOffset;
			}
			else
				hr = ADS_E_INVALIDSIZE;
		}
	}
	else
	{
		if ( ppData == NULL && nOffset <= nPtr )
			nData = nPtr - nOffset;
		else
			hr = ADS_E_INVALIDPARM;
	}
	return hr;
}

template<typename T>
inline HRESULT TcGetSizePtr(T* pPtr, ULONG nOffset, ULONG& nData, PVOID* ppData, ULONG flags)
{
	return TcGetSizePtr(pPtr, sizeof(*pPtr), nOffset, nData, ppData, flags);
}

///////////////////////////////////////////////////////////////////////////////
// Data area map

#define OBJDATAAREA_DISABLE_GET OBJDATAAREA_INDICATE_GET
#define OBJDATAAREA_DISABLE_SET OBJDATAAREA_INDICATE_SET

#ifdef TC_UNLIMITED_MAP_ENTRIES
#define FINISH_OBJDATAAREA \
	return hr; \
}
#else
#define FINISH_OBJDATAAREA } else
#endif

#define DECLARE_OBJDATAAREA_MAP() \
virtual	HRESULT TCOMAPI TcGetObjDataAreaPtr(UINT areaNo, ULONG nOffset, ULONG& nData, PVOID* ppData, ULONG flags=0);

#define	BEGIN_OBJDATAAREA_MAP(theClass) \
HRESULT theClass::TcGetObjDataAreaPtr(UINT areaNo, ULONG nOffset, ULONG& nData, PVOID* ppData, ULONG flags) \
{ \
	HRESULT hr=S_OK; \

#define	BEGIN_OBJDATAAREA_MAP2(theClass) \
HRESULT theClass::TcGetObjDataAreaPtr(UINT areaNo, ULONG nOffset, ULONG& nData, PVOID* ppData, ULONG flags) \
{ \
	HRESULT hr=S_OK; \


#define END_OBJDATAAREA_MAP() \
	hr = ADS_E_INVALIDPARM;  \
	return hr; \
}

#define END_OBJDATAAREA_MAP2(theBase) \
	hr = theBase::TcGetObjDataAreaPtr(areaNo, nOffset, nData, ppData, flags); \
	return hr; \
}

#define OBJDATAAREA_PTR_SIZE(AREANO, PTR, SIZE) \
	if ( (AREANO) == areaNo ) { \
		hr = TcGetSizePtr(PTR, SIZE, nOffset, nData, ppData, flags); \
	FINISH_OBJDATAAREA

#define OBJDATAAREA_VALUE(AREANO, VALUE) OBJDATAAREA_PTR_SIZE(AREANO, &VALUE, sizeof(VALUE))

#define OBJDATAAREA_SPAN_PTR_SIZE_FLAGS(AREANO, SPAN, PTR, SIZE, FLAGS) \
	if ((AREANO) <= areaNo &&  areaNo < ((AREANO) + (SPAN))) \
	{ \
		if (((FLAGS) & flags) == 0) \
		{ \
			ULONG spanAreaOffset = ((areaNo - (AREANO)) * TcDataAreaOffsetMax); \
			PVOID pSpanAreaBase = ((PBYTE)PTR) + spanAreaOffset; \
			hr = TcGetSizePtr(pSpanAreaBase, SIZE - spanAreaOffset, nOffset, nData, ppData, flags); \
		} \
		else \
		{ \
			hr = ADS_E_ACCESSDENIED; \
		} \
	FINISH_OBJDATAAREA

#define OBJDATAAREA_SPAN_VALUE_FLAGS(AREANO, SPAN, VALUE, FLAGS) OBJDATAAREA_SPAN_PTR_SIZE_FLAGS(AREANO, SPAN, &VALUE, sizeof(VALUE), FLAGS)
#define OBJDATAAREA_SPAN_VALUE(AREANO, SPAN, VALUE) OBJDATAAREA_SPAN_PTR_SIZE_FLAGS(AREANO, SPAN, &VALUE, sizeof(VALUE), 0)
#define OBJDATAAREA_VALUE_FLAGS(AREANO, VALUE, FLAGS) OBJDATAAREA_SPAN_PTR_SIZE_FLAGS(AREANO, TcDataAreaSpanDefault, &VALUE, sizeof(VALUE), FLAGS)

///////////////////////////////////////////////////////////////////////////////
// Watch map
#ifdef TC_UNLIMITED_MAP_ENTRIES
#define FINISH_OBJPARAWATCH \
	return hr; \
}
#else
#define FINISH_OBJPARAWATCH } else
#endif

#define DECLARE_OBJPARAWATCH_MAP() \
virtual	HRESULT TCOMAPI TcGetObjWatchPtr(PTCID pid, ULONG& nData, PVOID* ppData);

#define	BEGIN_OBJPARAWATCH_MAP(theClass) \
HRESULT theClass::TcGetObjWatchPtr(PTCID pid, ULONG& nData, PVOID* ppData) \
{ \
	HRESULT hr=S_OK;

#define	BEGIN_OBJPARAWATCH_MAP2(theClass) \
HRESULT theClass::TcGetObjWatchPtr(PTCID pid, ULONG& nData, PVOID* ppData) \
{ \
	HRESULT hr=S_OK;

#define END_OBJPARAWATCH_MAP() \
	{	hr = ADS_E_INVALIDOFFSET; } \
	return hr; \
}

#define END_OBJPARAWATCH_MAP2(theBase) \
	hr = theBase::TcGetObjWatchPtr(pid, nData, ppData); \
	return hr; \
}

#define OBJPARAWATCH_PTR_SIZE(PID, PTR, SIZE) \
	if ( (PID) == pid ) { \
		hr = TcGetSizePtr(PTR, SIZE, 0, nData, ppData); \
	FINISH_OBJPARAWATCH
#define OBJPARAWATCH_VALUE(PID, VALUE) OBJPARAWATCH_PTR_SIZE(PID, &VALUE, sizeof(VALUE))

#define OBJPARAWATCH_VALUE_ARRAY(PID, VALUE_ARRAY) \
	if ( (PID) == pid ) { \
		hr = TcGetSizePtr(VALUE_ARRAY.GetBuffer(), VALUE_ARRAY.ByteSize(), 0, nData, ppData); \
	FINISH_OBJPARAWATCH 

#define OBJPARAWATCH_DATAAREA_MAP() \
if ( TcDataAreaPidCheck(pid) ) { \
	hr = TcGetObjDataAreaPtr(TcDataAreaPidGetAreaNo(pid), TcDataAreaPidGetByteOffset(pid), nData, ppData); \
FINISH_OBJPARAWATCH

#define OBJPARAWATCH_DATAAREAPID_PTR_SIZE(PID, PTR, SIZE) \
	if (TcDataAreaPidCheck(pid, TcDataAreaPidGetAreaNo(PID), TcDataAreaPidGetByteOffset(PID), SIZE)) { \
		hr = TcGetSizePtr(PTR, SIZE, TcDataAreaPidGetByteOffset(pid)-TcDataAreaPidGetByteOffset(PID), nData, ppData); \
	FINISH_OBJPARAWATCH

#define OBJPARAWATCH_DATAAREAPID_VALUE(PID, VALUE) OBJPARAWATCH_DATAAREAPID_PTR_SIZE(PID, &VALUE, sizeof(VALUE))

#pragma deprecated("OBJPARAWATCH_DATAAREAPID_PTR_SIZE", "OBJPARAWATCH_DATAAREAPID_VALUE" )

#pragma warning(disable:4068)
#pragma endregion
#pragma warning(default:4068)

///////////////////////////////////////////////////////////////////////////////
// CTcTrace 
// 
// Allows to send trace messages using ADS Logging mechanism.
// The class contains references to the maximal trace level and to the 
// TwinCAT object server, which must be provided by modules using
// this class.
class CTcTrace
{
public: 
	CTcTrace(TcTraceLevel& TraceLevelMax, ITComObjectServerPtr& spSrv)
		: m_TraceLevelMax(TraceLevelMax)
		, m_spSrv(spSrv)
	{}

	void Log(TcTraceLevel TraceLevel, PCHAR szFormat, ...)
	{
		if (m_spSrv != NULL && m_TraceLevelMax>=TraceLevel)
		{
			va_list pArgs;
			va_start( pArgs, szFormat );
			DWORD msgCtrlMask = ADSLOG_MSGTYPE_STRING;
			if (TraceLevel==tlInfo)
			{
				msgCtrlMask |= ADSLOG_MSGTYPE_HINT;
			} 
			else if (TraceLevel==tlWarning)
			{
				msgCtrlMask |= ADSLOG_MSGTYPE_WARN;
			}
			else if (TraceLevel==tlError)
			{
				msgCtrlMask |= ADSLOG_MSGTYPE_ERROR;
			}
			m_spSrv->TcReportLogV( msgCtrlMask, szFormat, pArgs );
			va_end( pArgs );
		}
	}
private:
	TcTraceLevel& m_TraceLevelMax;
	ITComObjectServerPtr& m_spSrv;
};


#endif	// IS_R0
