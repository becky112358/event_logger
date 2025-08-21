///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"

#if !defined(UNDER_CE)
#define LICENSE_PRIVKEY
#endif

const		ULONG		DrvID_TcLicense					= 0x01010000;

// interface IDs
TCOM_DECL_INTERFACE("01010001-0000-0000-e000-000000000064", ITComLicenseServer)
TCOM_DECL_INTERFACE("01010002-0000-0000-e000-000000000064", ITComLicenseServer2)
#ifdef LICENSE_USERMNG
TCOM_DECL_INTERFACE("9A81A84B-D1AA-4940-A782-9AD6D90516AC", ITComLicenseUserMng)
#endif

typedef	BYTE	Sha1Hash[20];
typedef	BYTE	Sha256Hash[32];

// ADS IGRPs
const		ULONG		IGRP_LIC_CheckExpireTime			= DrvID_TcLicense | 0x0001;
const		ULONG		IGRP_LIC_LicenseData					= DrvID_TcLicense | 0x0002;
const		ULONG		IGRP_LIC_SystemInfo					= DrvID_TcLicense | 0x0004;
	const		ULONG		IOFFS_LIC_SystemId					= 1;
	const		ULONG		IOFFS_LIC_DeviceTypeId				= 15;

const		ULONG		IGRP_LIC_CheckLicense				= DrvID_TcLicense | 0x0007;
const		ULONG		IGRP_LIC_TakeLicense					= DrvID_TcLicense | 0x0008;		// AdsRW: W(16): licenseId; 
																												//   R(20): TcLicenseTakeLicenseInfo; AdsResult = 0
																												//   R(16): hReturn; AdsResult = HRESULT(licenseResult)
																												//   R(4): licenseResult; AdsResult = 0
																												//   R(0): AdsResult = HRESULT(licenseResult)
																												// AdsRW: W(32): oemId, licenseId; 
																												//   R(20): TcLicenseTakeLicenseInfo; AdsResult = 0
																												//   R(16): hReturn; AdsResult = HRESULT(licenseResult)
																												//   R(4): licenseResult; AdsResult = 0
																												//   R(0): AdsResult = HRESULT(licenseResult)
																												// AdsW: W(16): licenseId; AdsResult = HRESULT(licenseResult)
const		ULONG		IGRP_LIC_ReturnLicense				= DrvID_TcLicense | 0x0009;
const		ULONG		IGRP_LIC_VerifyVolumeNumber		= DrvID_TcLicense | 0x001E;		// AdsRW: W(16): volsysid;
																												//   R(4): hresult (check result)

typedef struct	_TcLicenseEntry
{
	GUID			licenseId;
	ULONG			nCount;
	ULONG			nVolumeNo;	// 0 == no volumeNo
	WORD			nRestriction;
	USHORT		nReserved1;
	ULONG			nPending;
} TcLicenseEntry, *PTcLicenseEntry;

typedef struct _TcCheckLicense
{
	GUID			licenseId;
	__int64		tExpireTime;
	HRESULT		result;
	ULONG			nCount;
} TcCheckLicense, *PTcCheckLicense;

typedef struct	_TcLicenseTakeLicenseInfo
{
	GUID			hReturn;
	HRESULT		hr;
} TcLicenseTakeLicenseInfo, *PTcLicenseTakeLicenseInfo;
