///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <TcServices.h>
#include <TcInterfaces.h>

// -------------------------------------------------------------------------------------------------
#define TCMARK_START			0xE0000000
#define TCMARK_STOP			0xC0000000
#define TCMARK_SEQ_START	0xA0000000
#define TCMARK_SEQ_STOP		0x80000000
#define TCMARK_IVAL_START	0x60000000
#define TCMARK_IVAL_STOP	0x40000000
#define TCMARK_REF_CALLER	0x08000000

// -------------------------------------------------------------------------------------------------
typedef struct {
	USHORT		ContextId;
	USHORT		GroupId;
	USHORT		EventId;
} TcMark16;

// ---------------------------------------------------------------------------------------------------
TCOM_DECL_INTERFACE("02000102-0000-0000-e001-000000000129", ITcLogMark16);

// ---------------------------------------------------------------------------------------------------
struct __declspec(novtable) ITcLogMark16 : public ITcUnknown
{
	virtual HRESULT TCOMAPI LogMark16(USHORT ContextId, USHORT GroupId, USHORT EventId, ULONG Ctrl) = 0;
	virtual HRESULT TCOMAPI LogMarkEx16(TcMark16* pMark, ULONG Ctrl) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcLogMark16, IID_ITcLogMark16);


// ---------------------------------------------------------------------------------------------------
class DLL_EXPORT CTcLogMark
{
public:
	DECLARE_OPERATOR_NEW_DELETE()

	CTcLogMark(USHORT nContextId, ITComObjectServer* ipSrv = NULL);
	virtual ~CTcLogMark();
	virtual void		SetOidLogMark(OTCID oid);
	virtual bool		HasOidLogMark();
	virtual bool		IsInitializedLogMark();
	virtual HRESULT	InitLogMark(ITComObjectServer* ipSrv);
	virtual HRESULT	InitLogMark(OTCID oid, ITComObjectServer* ipSrv);
	virtual HRESULT	ReleaseLogMark();
	virtual HRESULT	LogMark(USHORT GroupId, USHORT EventId, ULONG CtrlId);
	virtual HRESULT	LogMarkEx(TcMark16* pMark, ULONG CtrlId);
	virtual HRESULT	LogMark(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogStart(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogStop(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogSequenceStart(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogSequenceStop(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogIntervalStart(USHORT GroupId, USHORT EventId);
	virtual HRESULT	LogIntervalStop(USHORT GroupId, USHORT EventId);
	virtual USHORT		GetContextId();
	virtual void		SetContextId(USHORT nContextId);
	virtual void		EnableLogCallerId(BOOL bEnable);

private:
	ITcLogMark16Ptr	m_spLogMark;
	ULONG					m_nCtrlId;
	USHORT				m_nContextId;
};
