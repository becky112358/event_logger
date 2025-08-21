///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once


#include "TcBase.h"
#include "TcInterfaces.h"
#include "TcLicenseServices.h"

struct	__declspec(novtable)	ITComLicenseServer : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetLicenseEntry(GUID licenseId, TcLicenseEntry* pEntry)=0;
	virtual	HRESULT	TCOMAPI	TakeLicense(const GUID& licenseId, GUID* pHReturn=NULL, UINT count=1)=0;
	virtual	HRESULT	TCOMAPI	ReturnLicense(const GUID& hReturn)=0;
	virtual	HRESULT	TCOMAPI	ReportLicenseViolation(ITComObject* ipObj, GUID licenseId, HRESULT reason, PCHAR pszLicenseName=NULL)=0;
	virtual	HRESULT	TCOMAPI	GetSystemId(GUID* pSystemId)=0;
	virtual	HRESULT	TCOMAPI	ReportLicenseViolation(ITComObject* ipObj, GUID licenseId, HRESULT reason, PCHAR pszLicenseName, PCHAR pszComment)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComLicenseServer, IID_ITComLicenseServer);

struct	__declspec(novtable)	ITComLicenseServer2 : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	GetVolumeId(GUID* pVolumeId)=0;
	virtual	HRESULT	TCOMAPI	GetSystemSpecificKey(GUID sessionId, BOOL bVolumeSpecific, GUID* pKey)=0;
	virtual	HRESULT	TCOMAPI	LEGACY_VerifyOemSignature(const PBYTE pData, ULONG nData, const PBYTE pSig, ULONG nSig, GUID oemId)=0;
	virtual	HRESULT	TCOMAPI	TakeOemLicense(const GUID& oemId, const GUID& licenseId, GUID* pHReturn=NULL, UINT count=1)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComLicenseServer2, IID_ITComLicenseServer2);

struct	__declspec(novtable)	ITComDecryptHelper
{
	virtual	HRESULT	DecryptData(PBYTE pbInput, ULONG cbInput, PBYTE pbIV, ULONG cbIV, PBYTE pbOutput, ULONG cbOutput, PULONG pcbResult, DWORD dwFlags)=0;
	virtual	HRESULT	VerifySignature(PBYTE pbSign, ULONG cbSign, ULONG nDataBlocks, PBYTE* ppbData, PULONG pcbData)=0;
	virtual	HRESULT	CalcSha256Hash(PVOID pData, ULONG nData, Sha256Hash& hash)=0;
};

#ifdef LICENSE_USERMNG
static char* g_sUmSplNames[] = { "Read", "Write", "Execute" };

struct	__declspec(novtable)	ITComLicenseUserMng : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI	HasUserRight(const GUID* pUserId, const GUID* pRight) = 0;
	virtual	HRESULT	TCOMAPI	HasUserSpLevel(const GUID* pUserId, const GUID* pSpLevel, const EAdsSymProtection spl) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITComLicenseUserMng, IID_ITComLicenseUserMng);
#endif
