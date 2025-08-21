///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBase.h"

#ifdef TC_ENVIRONMENT_OS_UM_SUPPORT
#include "OsBase.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// CSyncDefault
class DLL_EXPORT CSyncDefault
{
public: 
	CSyncDefault()
	{
		INIT_CRITSEC;
	}

	~CSyncDefault()
	{
		DELETE_CRITSEC
	}

	void Lock()
	{
		ENTER_CRITSEC 
	}

	void Unlock()
	{
		LEAVE_CRITSEC 
	}

private: 
	DECLARE_CRITSEC
}; 

/* CNoSync is needed to create a FiFo/Hashtable which 
	does not need any synchronization.
*/
class DLL_EXPORT CNoSync
{
public: 
	CNoSync()
	{
	}

	~CNoSync()
	{
	}

	void Lock()
	{
	}

	void Unlock()
	{
	}
}; 

