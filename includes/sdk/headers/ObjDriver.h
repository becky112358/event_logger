///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "GenDrv.h"

///////////////////////////////////////////////////////////////////////////////
//	CObjDriver 

class CObjClassFactory;

class CObjDriver : public CGenDrv
{
public:
	virtual	IOSTATUS	OnIoControl( IOCTL_PARAMETERS& ioCtrlParams );
	virtual	IOSTATUS	OnSystemShutdown();

protected:

	CObjClassFactory*  m_pObjClassFactory;
};

