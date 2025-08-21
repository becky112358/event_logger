///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcError.h"

////////////////////////////////////////////////////////////////////////////////
// ADS error codes
#define ADSERR_NOERR							0x00
//
#define ADSERR_DEVICE_ERROR				(0x00 + ERR_ADSERRS) // Error class < device error >
#define ADSERR_DEVICE_SRVNOTSUPP			(0x01 + ERR_ADSERRS) // Service is not supported by server
#define ADSERR_DEVICE_INVALIDGRP 		(0x02 + ERR_ADSERRS) // invalid indexGroup
#define ADSERR_DEVICE_INVALIDOFFSET		(0x03 + ERR_ADSERRS) // invalid indexOffset
#define ADSERR_DEVICE_INVALIDACCESS		(0x04 + ERR_ADSERRS) // reading/writing not permitted
#define ADSERR_DEVICE_INVALIDSIZE		(0x05 + ERR_ADSERRS) // parameter size not correct
#define ADSERR_DEVICE_INVALIDDATA		(0x06 + ERR_ADSERRS) // invalid parameter value(s)
#define ADSERR_DEVICE_NOTREADY			(0x07 + ERR_ADSERRS) // device is not in a ready state
#define ADSERR_DEVICE_BUSY					(0x08 + ERR_ADSERRS) // device is busy
#define ADSERR_DEVICE_INVALIDCONTEXT	(0x09 + ERR_ADSERRS) // invalid context (must be InWindows)
#define ADSERR_DEVICE_NOMEMORY			(0x0A + ERR_ADSERRS) // out of memory
#define ADSERR_DEVICE_INVALIDPARM		(0x0B + ERR_ADSERRS) // invalid parameter value(s)
#define ADSERR_DEVICE_NOTFOUND			(0x0C + ERR_ADSERRS) // not found (files, ...)
#define ADSERR_DEVICE_SYNTAX				(0x0D + ERR_ADSERRS) // syntax error in comand or file
#define ADSERR_DEVICE_INCOMPATIBLE		(0x0E + ERR_ADSERRS) // objects do not match
#define ADSERR_DEVICE_EXISTS				(0x0F + ERR_ADSERRS) // object already exists
#define ADSERR_DEVICE_SYMBOLNOTFOUND	(0x10 + ERR_ADSERRS) // symbol not found
#define ADSERR_DEVICE_SYMBOLVERSIONINVALID	(0x11 + ERR_ADSERRS) // symbol version invalid
#define ADSERR_DEVICE_INVALIDSTATE		(0x12 + ERR_ADSERRS) // server is in invalid state
#define ADSERR_DEVICE_TRANSMODENOTSUPP	(0x13 + ERR_ADSERRS) // AdsTransMode not supported
#define ADSERR_DEVICE_NOTIFYHNDINVALID	(0x14 + ERR_ADSERRS) // Notification handle is invalid
#define ADSERR_DEVICE_CLIENTUNKNOWN		(0x15 + ERR_ADSERRS) // Notification client not registered	
#define ADSERR_DEVICE_NOMOREHDLS			(0x16 + ERR_ADSERRS) // no more notification handles	
#define ADSERR_DEVICE_INVALIDWATCHSIZE	(0x17 + ERR_ADSERRS) // size for watch to big	
#define ADSERR_DEVICE_NOTINIT				(0x18 + ERR_ADSERRS) // device not initialized	
#define ADSERR_DEVICE_TIMEOUT				(0x19 + ERR_ADSERRS) // device has a timeout
#define ADSERR_DEVICE_NOINTERFACE		(0x1A + ERR_ADSERRS) // query interface failed
#define ADSERR_DEVICE_INVALIDINTERFACE	(0x1B + ERR_ADSERRS) // wrong interface required
#define ADSERR_DEVICE_INVALIDCLSID		(0x1C + ERR_ADSERRS) // class ID is invalid
#define ADSERR_DEVICE_INVALIDOBJID		(0x1D + ERR_ADSERRS) // object ID is invalid
#define ADSERR_DEVICE_PENDING				(0x1E + ERR_ADSERRS) // request is pending
#define ADSERR_DEVICE_ABORTED				(0x1F + ERR_ADSERRS) // request is aborted
#define ADSERR_DEVICE_WARNING				(0x20 + ERR_ADSERRS) // signal warning
#define ADSERR_DEVICE_INVALIDARRAYIDX	(0x21 + ERR_ADSERRS) // invalid array index
#define ADSERR_DEVICE_SYMBOLNOTACTIVE	(0x22 + ERR_ADSERRS) // symbol not active -> release handle and try again
#define ADSERR_DEVICE_ACCESSDENIED		(0x23 + ERR_ADSERRS) // access denied
#define ADSERR_DEVICE_LICENSENOTFOUND	(0x24 + ERR_ADSERRS) // no license found
#define ADSERR_DEVICE_LICENSEEXPIRED	(0x25 + ERR_ADSERRS) // license expired
#define ADSERR_DEVICE_LICENSEEXCEEDED	(0x26 + ERR_ADSERRS) // license exceeded
#define ADSERR_DEVICE_LICENSEINVALID	(0x27 + ERR_ADSERRS) // license invalid 
#define ADSERR_DEVICE_LICENSESYSTEMID	(0x28 + ERR_ADSERRS) // license invalid system id
#define ADSERR_DEVICE_LICENSENOTIMELIMIT	(0x29 + ERR_ADSERRS) // license not time limited
#define ADSERR_DEVICE_LICENSEFUTUREISSUE	(0x2A + ERR_ADSERRS) // license issue time in the future
#define ADSERR_DEVICE_LICENSETIMETOLONG	(0x2B + ERR_ADSERRS) // license time period to long
#define ADSERR_DEVICE_EXCEPTION				(0x2C + ERR_ADSERRS) // exception in device specific code
#define ADSERR_DEVICE_LICENSEDUPLICATED	(0x2D + ERR_ADSERRS) // license file read twice
#define ADSERR_DEVICE_SIGNATUREINVALID		(0x2E + ERR_ADSERRS) // invalid signature
#define ADSERR_DEVICE_CERTIFICATEINVALID	(0x2F + ERR_ADSERRS) // public key certificate
#define ADSERR_DEVICE_LICENSEOEMNOTFOUND	(0x30 + ERR_ADSERRS) // public key of OEM unknown
#define ADSERR_DEVICE_LICENSERESTRICTED	(0x31 + ERR_ADSERRS) // license not valid for this system id type
#define ADSERR_DEVICE_LICENSEDEMODENIED	(0x32 + ERR_ADSERRS) // trial license denied
#define ADSERR_DEVICE_INVALIDFNCID			(0x33 + ERR_ADSERRS) // function id is invalid
#define ADSERR_DEVICE_OUTOFRANGE				(0x34 + ERR_ADSERRS) // a parameter, an index, an iterator, ... is out of range
#define ADSERR_DEVICE_INVALIDALIGNMENT		(0x35 + ERR_ADSERRS) // invalid alignment
#define ADSERR_DEVICE_LICENSEPLATFORM		(0x36 + ERR_ADSERRS) // license invalid platform level
#define ADSERR_DEVICE_FORWARD_PL				(0x37 + ERR_ADSERRS) // wrong context - forward to passive level (port 12)
#define ADSERR_DEVICE_FORWARD_DL				(0x38 + ERR_ADSERRS) // wrong context - forward to dispatch level (port 10)
#define ADSERR_DEVICE_FORWARD_RT				(0x39 + ERR_ADSERRS) // wrong context - forward to real time (port 11)
#define ADSERR_DEVICE_CERTIFICATENTRUST	(0x3A + ERR_ADSERRS) // oem certificate not in trusted list

//
#define ADSERR_CLIENT_ERROR				(0x40 + ERR_ADSERRS) // Error class < client error >
#define ADSERR_CLIENT_INVALIDPARM		(0x41 + ERR_ADSERRS) // invalid parameter at service call
#define ADSERR_CLIENT_LISTEMPTY			(0x42 + ERR_ADSERRS) // polling list	is empty
#define ADSERR_CLIENT_VARUSED				(0x43 + ERR_ADSERRS) // var connection already in use
#define ADSERR_CLIENT_DUPLINVOKEID		(0x44 + ERR_ADSERRS) // invoke id in use
#define ADSERR_CLIENT_SYNCTIMEOUT		(0x45 + ERR_ADSERRS) // timeout elapsed
#define ADSERR_CLIENT_W32ERROR			(0x46 + ERR_ADSERRS) // error in win32 subsystem
#define ADSERR_CLIENT_TIMEOUTINVALID	(0x47 + ERR_ADSERRS) // ?
#define ADSERR_CLIENT_PORTNOTOPEN		(0x48 + ERR_ADSERRS) // ads dll
#define ADSERR_CLIENT_NOAMSADDR			(0x49 + ERR_ADSERRS) // ads dll 
#define ADSERR_CLIENT_SYNCINTERNAL		(0x50 + ERR_ADSERRS) // internal error in ads sync 
#define ADSERR_CLIENT_ADDHASH				(0x51 + ERR_ADSERRS) // hash table overflow 
#define ADSERR_CLIENT_REMOVEHASH			(0x52 + ERR_ADSERRS) // key not found in hash table 
#define ADSERR_CLIENT_NOMORESYM			(0x53 + ERR_ADSERRS) // no more symbols in cache 
#define ADSERR_CLIENT_SYNCRESINVALID	(0x54 + ERR_ADSERRS) // invalid response received 
#define ADSERR_CLIENT_SYNCPORTLOCKED	(0x55 + ERR_ADSERRS) // sync port is locked 


#ifdef __cplusplus
inline	HRESULT	MAKE_ADS_HRESULT(ULONG code)
{
	return (code == 0) ? S_OK : MAKE_HRESULT(0, FACILITY_TC_ADS, (code&(~0x80000000))) | ((~code) & 0x80000000);
}
inline	ULONG	HRESULT_ADS_CODE(HRESULT result)
{
	return SUCCEEDED(result) ? ADSERR_NOERR : ((((result >> 16) & 0x7fff) == FACILITY_TC_ADS) ? HRESULT_CODE(result) | ((~result) & 0x80000000) : ADSERR_DEVICE_ERROR);
}
#endif // __cplusplus

#define ADS_E_ERROR						((HRESULT)0x98110000+ADSERR_DEVICE_ERROR)						// Error class < device error >
#define ADS_E_SRVNOTSUPP				((HRESULT)0x98110000+ADSERR_DEVICE_SRVNOTSUPP)				// Service is not supported by server
#define ADS_E_INVALIDGRP 				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDGRP)				// invalid indexGroup
#define ADS_E_INVALIDOFFSET			((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDOFFSET)			// invalid indexOffset
#define ADS_E_INVALIDACCESS			((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDACCESS)			// reading/writing not permitted
#define ADS_E_INVALIDSIZE				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDSIZE)				// parameter size not correct
#define ADS_E_INVALIDDATA				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDDATA)				// invalid parameter value(s)
#define ADS_E_NOTREADY					((HRESULT)0x98110000+ADSERR_DEVICE_NOTREADY)					// device is not in a ready state
#define ADS_E_BUSY						((HRESULT)0x98110000+ADSERR_DEVICE_BUSY)						// device is busy
#define ADS_E_INVALIDCONTEXT			((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDCONTEXT)			// invalid context (must be InWindows)
#define ADS_E_NOMEMORY					((HRESULT)0x98110000+ADSERR_DEVICE_NOMEMORY)					// out of memory
#define ADS_E_INVALIDPARM				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDPARM)				// invalid parameter value(s)
#define ADS_E_NOTFOUND					((HRESULT)0x98110000+ADSERR_DEVICE_NOTFOUND)					// not found (files, ...)
#define ADS_E_SYNTAX						((HRESULT)0x98110000+ADSERR_DEVICE_SYNTAX)					// syntax error in comand or file
#define ADS_E_INCOMPATIBLE				((HRESULT)0x98110000+ADSERR_DEVICE_INCOMPATIBLE)			// objects do not match
#define ADS_E_EXISTS						((HRESULT)0x98110000+ADSERR_DEVICE_EXISTS)					// object already exists
#define ADS_E_SYMBOLNOTFOUND			((HRESULT)0x98110000+ADSERR_DEVICE_SYMBOLNOTFOUND)			// symbol not found
#define ADS_E_SYMBOLVERSIONINVALID	((HRESULT)0x98110000+ADSERR_DEVICE_SYMBOLVERSIONINVALID) // symbol version invalid
#define ADS_E_INVALIDSTATE				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDSTATE)			// server is in invalid state
#define ADS_E_TRANSMODENOTSUPP		((HRESULT)0x98110000+ADSERR_DEVICE_TRANSMODENOTSUPP)		// AdsTransMode not supported
#define ADS_E_NOTIFYHNDINVALID		((HRESULT)0x98110000+ADSERR_DEVICE_NOTIFYHNDINVALID)		// Notification handle is invalid
#define ADS_E_CLIENTUNKNOWN			((HRESULT)0x98110000+ADSERR_DEVICE_CLIENTUNKNOWN)			// Notification client not registered	
#define ADS_E_NOMOREHDLS				((HRESULT)0x98110000+ADSERR_DEVICE_NOMOREHDLS)				// no more notification handles	
#define ADS_E_INVALIDWATCHSIZE		((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDWATCHSIZE)		// size for watch to big	
#define ADS_E_NOTINIT					((HRESULT)0x98110000+ADSERR_DEVICE_NOTINIT)					// device not initialized	
#define ADS_E_TIMEOUT					((HRESULT)0x98110000+ADSERR_DEVICE_TIMEOUT)					// device has a timeout
#define ADS_E_NOINTERFACE				((HRESULT)0x98110000+ADSERR_DEVICE_NOINTERFACE)				// query interface failed
#define ADS_E_INVALIDINTERFACE		((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDINTERFACE)		// wrong interface required
#define ADS_E_INVALIDCLSID				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDCLSID)			// class ID is invalid
#define ADS_E_INVALIDOBJID				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDOBJID)			// object ID is invalid
#define ADS_E_PENDING					((HRESULT)0x98110000+ADSERR_DEVICE_PENDING)					// request is pending
#define ADS_E_ABORTED					((HRESULT)0x98110000+ADSERR_DEVICE_ABORTED)					// request is aborted
#define ADS_E_WARNING					((HRESULT)0x98110000+ADSERR_DEVICE_WARNING)					// signal warning
#define ADS_E_INVALIDARRAYIDX			((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDARRAYIDX)		// invalid array index
#define ADS_E_SYMBOLNOTACTIVE			((HRESULT)0x98110000+ADSERR_DEVICE_SYMBOLNOTACTIVE)		// symbol not active -> release handle and try again
#define ADS_E_ACCESSDENIED				((HRESULT)0x98110000+ADSERR_DEVICE_ACCESSDENIED)			// access denied
#define ADS_E_LICENSENOTFOUND			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSENOTFOUND)		// no license found
#define ADS_E_LICENSEEXPIRED			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEEXPIRED)			// license expired
#define ADS_E_LICENSEEXCEEDED			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEEXCEEDED)		// license exceeded
#define ADS_E_LICENSEINVALID			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEINVALID)			// license invalid
#define ADS_E_LICENSESYSTEMID			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSESYSTEMID)		// license invalid system id
#define ADS_E_LICENSENOTIMELIMIT		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSENOTIMELIMIT)	// license not time limited
#define ADS_E_LICENSEFUTUREISSUE		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEFUTUREISSUE)	// license issue time in the future
#define ADS_E_LICENSETIMETOLONG		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSETIMETOLONG)		// license time period to long
#define ADS_E_EXCEPTION					((HRESULT)0x98110000+ADSERR_DEVICE_EXCEPTION)				// exception in device specific code
#define ADS_E_LICENSEDUPLICATED		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEDUPLICATED)		// license file read twice
#define ADS_E_SIGNATUREINVALID		((HRESULT)0x98110000+ADSERR_DEVICE_SIGNATUREINVALID)		// invalid signature
#define ADS_E_CERTIFICATEINVALID		((HRESULT)0x98110000+ADSERR_DEVICE_CERTIFICATEINVALID)	// public key certificate
#define ADS_E_LICENSEOEMNOTFOUND		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEOEMNOTFOUND)	// public key of OEM unknown
#define ADS_E_LICENSERESTRICTED		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSERESTRICTED)		// license not valid for this system id type
#define ADS_E_LICENSEDEMODENIED		((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEDEMODENIED)		// trial license denied
#define ADS_E_INVALIDFNCID				((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDFNCID)			// function id is invalid
#define ADS_E_OUTOFRANGE				((HRESULT)0x98110000+ADSERR_DEVICE_OUTOFRANGE)				// a parameter, an index, an iterator, ... is out of range
#define ADS_E_INVALIDALIGNMENT		((HRESULT)0x98110000+ADSERR_DEVICE_INVALIDALIGNMENT)		// invalid alignment
#define ADS_E_LICENSEPLATFORM			((HRESULT)0x98110000+ADSERR_DEVICE_LICENSEPLATFORM)		// license invalid platform level
#define ADS_E_FORWARD_PL				((HRESULT)0x98110000+ADSERR_DEVICE_FORWARD_PL)				// wrong context - forward to passive level (port 12)
#define ADS_E_FORWARD_DL				((HRESULT)0x98110000+ADSERR_DEVICE_FORWARD_DL)				// wrong context - forward to dispatch level (port 10)
#define ADS_E_FORWARD_RT				((HRESULT)0x98110000+ADSERR_DEVICE_FORWARD_RT)				// wrong context - forward to real time (port 11)
#define ADS_E_CERTIFICATENTRUST		((HRESULT)0x98110000+ADSERR_DEVICE_CERTIFICATENTRUST)		// oem certificate not trusted

//
// transport errors are signaled with their original code
//#define ADSERR_TRANSPORT_ERROR			(0x80+ERR_ADSERRS) // Error class <error in tranport layer>
																		 // error codes of transport layer are added

