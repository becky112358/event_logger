///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcInterfaces.h"

class DLL_EXPORT CTcDbgUnit 
	: public ITcDbgUnit
	, public ITcDbgUnitVersion
	, public ITcDbgUnitFlags
{
public:
	CTcDbgUnit(PCSTR szImageName = NULL, TcDbgUnitFlags flags = TcDbgUnitFlagsNone);
	virtual ~CTcDbgUnit();

	VOID SetImageName(PCSTR szImageName);

	VOID TComObjectServerAdd
	(	
		ITComObjectServer* ipTComObjectServer
	);

	VOID TComObjectServerRemove
	(	
		ITComObjectServer* ipTComObjectServer
	);

	VOID SetImageVersion(ULONG nMajor, ULONG nMinor, ULONG nBuild, ULONG nRevision);
	VOID TcDbgUnitSetFlags(TcDbgUnitFlags flags);

	// ITcUnknown
	DECLARE_IUNKNOWN_NODELETE()

	// ITcDbgUnit
	TCOMMETHODITF(TcDbgUnitIsValid()); 
	TCOMMETHODITF(TcDbgUnitGetImageName(PCSTR& szImageName));
	TCOMMETHODITF(TcDbgUnitGetInfo(PCSTR& szImageName, ULONG_PTR& pImageBase, ULONG& nImageSize));
	TCOMMETHODITF(TcDbgUnitGetImageFullName(PSTR pszImageFullName, SIZE_T nImageFullName));

	// ITcDbgFileVersion
	TCOMMETHODITF(TcDbgUnitGetImageVersion(DbgUnitVersion& ImageVersion));

	// ITcDbgUnitFlags
	TCOMMETHODITF(TcDbgUnitCheckFlags(TcDbgUnitFlags flags, bool& bIsSet)); 

private: 

	VOID RetrieveInfo();

	PCSTR m_szImageName;
	ULONG_PTR m_pImageBase;
	ULONG m_nImageSize;
	PSTR m_szImageFullName; 
	DbgUnitVersion m_ImageVersion;
	TcDbgUnitFlags m_flags;
};



