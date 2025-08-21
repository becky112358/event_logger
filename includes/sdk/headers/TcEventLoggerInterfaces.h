///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBaseInterfaces.h"
#include "TcEventLoggerServices.h"

///////////////////////////////////////////////////////////////////////////////
struct ITcMessageListener;
struct ITcAlarmListener;

struct __declspec(novtable) ITcSourceInfo : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetNumTypes(ULONG& nCount) = 0;
	virtual HRESULT TCOMAPI GetTypes(const TcSerializedSourceInfoType** ppSourceInfoTypes) = 0;
	virtual HRESULT TCOMAPI GetDataSize(ULONG& cbData) = 0;
	virtual HRESULT TCOMAPI GetData(const void** ppData) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcSourceInfo, IID_ITcSourceInfo);


struct __declspec(novtable) ITcArguments : public ITcUnknown
{
	virtual HRESULT TCOMAPI Count(ULONG& nCount) = 0;
	virtual HRESULT TCOMAPI AddArgument(TcEventArgumentType eType, void* pData, ULONG cbData) = 0;
	virtual HRESULT TCOMAPI Get(ULONG nIndex, TcEventArgumentType& eType, const void** ppData, ULONG& cbData) = 0;
	virtual HRESULT TCOMAPI Clear() = 0;

	virtual HRESULT TCOMAPI GetArgumentTypes(TcEventArgumentType* pArgumentTypes) = 0;
	virtual HRESULT TCOMAPI GetDataSize(ULONG& nCount) = 0;
	virtual HRESULT TCOMAPI GetData(BYTE* pData) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcArguments, IID_ITcArguments);

struct __declspec(novtable) ITcAsyncResult : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetIsBusy(BOOL& bIsBusy) = 0;
	virtual HRESULT TCOMAPI GetHasError(BOOL& bError) = 0;
	virtual HRESULT TCOMAPI GetErrorCode(HRESULT& hresult) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAsyncResult, IID_ITcAsyncResult);

struct __declspec(novtable) ITcAsyncResult2 : public ITcAsyncResult
{
	virtual HRESULT TCOMAPI GetErrorDescription(PCHAR sError, ULONG& nError) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAsyncResult2, IID_ITcAsyncResult2);

struct __declspec(novtable) ITcAsyncStringResult : public ITcAsyncResult
{
	virtual HRESULT TCOMAPI GetString(PCHAR pResult, ULONG& nResult) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAsyncStringResult, IID_ITcAsyncStringResult);

struct __declspec(novtable) ITcEvent : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetEventClass(GUID& eventClass) = 0;
	virtual HRESULT TCOMAPI GetEventId(ULONG& eventId) = 0;
	virtual HRESULT TCOMAPI GetSeverity(TcEventSeverity& severity) = 0;

	virtual HRESULT TCOMAPI GetSourceInfo(ITcSourceInfo** pipSourceInfo) = 0;
	
	virtual HRESULT TCOMAPI GetJsonAttribute(PCHAR sJsonAttribute, ULONG& nJsonAttribute) = 0;

	virtual HRESULT TCOMAPI GetText(LONG nLangId, ITcAsyncStringResult** pipResult) = 0;
	virtual HRESULT TCOMAPI GetEventClassName(LONG nLangId, ITcAsyncStringResult** pipResult) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEvent, IID_IITcEvent);

struct __declspec(novtable) ITcMessage : public ITcEvent
{
	virtual HRESULT TCOMAPI SetJsonAttribute(PCCH sJsonAttribute) = 0;
	virtual HRESULT TCOMAPI GetArguments(ITcArguments** pipArguments) = 0;
	virtual HRESULT TCOMAPI Send(ULONGLONG timeStamp) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcMessage, IID_ITcMessage);

struct __declspec(novtable) ITcMessage2 : public ITcMessage
{
	virtual HRESULT TCOMAPI GetTimeSent(ULONGLONG& timeStamp) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcMessage2, IID_ITcMessage2);

struct __declspec(novtable) ITcAlarm : public ITcEvent
{
	virtual HRESULT TCOMAPI SetJsonAttribute(PCCH sJsonAttribute) = 0;
	virtual HRESULT TCOMAPI GetArguments(ITcArguments** pipArguments) = 0;
	virtual HRESULT TCOMAPI GetIsRaised(BOOL& bIsRaised) = 0;
	virtual HRESULT TCOMAPI Raise(ULONGLONG timeStamp) = 0;
	virtual HRESULT TCOMAPI Clear(ULONGLONG timeStamp, BOOL bResetConfirmation) = 0;

	virtual HRESULT TCOMAPI GetConfirmationState(TcEventConfirmationState& state) = 0;
	virtual HRESULT TCOMAPI Confirm(ULONGLONG timeStamp) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAlarm, IID_ITcAlarm);

struct __declspec(novtable) ITcAlarm2 : public ITcAlarm
{
	virtual HRESULT TCOMAPI GetTimeRaised(ULONGLONG& timeStamp) = 0;
	virtual HRESULT TCOMAPI GetTimeConfirmed(ULONGLONG& timeStamp) = 0;
	virtual HRESULT TCOMAPI GetTimeCleared(ULONGLONG& timeStamp) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAlarm2, IID_ITcAlarm2);

struct __declspec(novtable) ITcEventUniqueIdProvider : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetUniqueId(ULONG& id) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventUniqueIdProvider, IID_ITcEventUniqueIdProvider);

struct __declspec(novtable) ITcEventLogger : public ITcUnknown
{
	virtual HRESULT TCOMAPI CreateMessage(const GUID& eventClass, ULONG eventId, TcEventSeverity severity, ITcSourceInfo* ipSourceInfo, ITcMessage** pipMessage) = 0;

	virtual HRESULT TCOMAPI CreateAlarm(const GUID& eventClass, ULONG eventId, TcEventSeverity severity, BOOL bWithConfirmation, ITcSourceInfo* ipSourceInfo, ITcAlarm** pipAlarm) = 0;
	virtual HRESULT TCOMAPI GetAlarm(const GUID& eventClass, ULONG eventId, ITcSourceInfo* ipSourceInfo, ITcAlarm** pipAlarm) = 0;

	virtual HRESULT TCOMAPI IsAlarmRaised(const GUID& eventClass, ULONG eventId, ITcSourceInfo* ipSourceInfo, BOOL& bIsRaised) = 0;

	virtual HRESULT TCOMAPI ConfirmAllAlarms(ULONGLONG timeStamp) = 0;
	virtual HRESULT TCOMAPI ClearAllAlarms(ULONGLONG timeStamp, BOOL bResetConfirmation) = 0;

	virtual HRESULT TCOMAPI SendTcMessage(const GUID& eventClass, ULONG eventId, TcEventSeverity severity, ITcSourceInfo* ipSourceInfo, ULONGLONG timeStamp, ITcArguments* ipArguments) = 0;

	virtual HRESULT TCOMAPI AddMessageListener(ITcMessageListener* ipListener, ITcEventFilterConfig** pipFilterConfig) = 0;
	virtual HRESULT TCOMAPI RemoveMessageListener(ITcMessageListener* ipListener) = 0;
	virtual HRESULT TCOMAPI NotifyMessageListener(ITcMessageListener* ipListener) = 0;

	virtual HRESULT TCOMAPI AddAlarmListener(ITcAlarmListener* ipListener, ITcEventFilterConfig** pipFilterConfig) = 0;
	virtual HRESULT TCOMAPI RemoveAlarmListener(ITcAlarmListener* ipListener) = 0;
	virtual HRESULT TCOMAPI NotifyAlarmListener(ITcAlarmListener* ipListener) = 0;

	virtual HRESULT TCOMAPI GetEventText(const GUID& eventClass, ULONG eventId,ITcSourceInfo* ipSourceInfo, ITcArguments* ipArguments, LONG nLangId, ITcAsyncStringResult** pipResult) = 0;
	virtual HRESULT TCOMAPI GetEventClassName(const GUID& eventClass, LONG nLangId, ITcAsyncStringResult** pipResult) = 0;

	virtual HRESULT TCOMAPI CreateArguments(ITcArguments** pipArguments) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventLogger, IID_ITcEventLogger);

struct __declspec(novtable) ITcEventLogger2 : public ITcEventLogger
{
	virtual HRESULT TCOMAPI SendTcMessage2(const GUID& eventClass, ULONG eventId, TcEventSeverity severity, ITcSourceInfo* ipSourceInfo, ULONGLONG timeStamp, ITcArguments* ipArguments, PCCH sJsonAttribute) = 0;

	virtual HRESULT TCOMAPI CreateEventFilter(ITcEventFilter** pipFilter) = 0;
	virtual HRESULT TCOMAPI ConfirmAlarms(ULONGLONG timeStamp, ITcEventFilter* ipFilter) = 0;
	virtual HRESULT TCOMAPI ClearAlarms(ULONGLONG timeStamp, BOOL bResetConfirmation, ITcEventFilter* ipFilter) = 0;

	virtual HRESULT TCOMAPI CreateExportSettings(TcExportFormat eFormat, ITcExportSettings** pipSettings) = 0;
	virtual HRESULT TCOMAPI ExportLoggedEvents(PCCH sFileName, ITcExportSettings* ipSettings, ITcAsyncResult** pipResult) = 0;

	virtual HRESULT TCOMAPI CreateClearLoggedEventsSettings(ITcClearLoggedEventsSettings** pipSettings) = 0;
	virtual HRESULT TCOMAPI ClearLoggedEvents(ITcClearLoggedEventsSettings* ipSettings, ITcAsyncResult** pipResult) = 0;

	virtual HRESULT TCOMAPI AddMessageListener2(ITcMessageListener* ipListener, ITcEventFilter* ipFilter) = 0;
	virtual HRESULT TCOMAPI AddAlarmListener2(ITcAlarmListener* ipListener, ITcEventFilter* ipFilter) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventLogger2, IID_ITcEventLogger2);

struct __declspec(novtable) ITcEventFilter : public ITcUnknown
{
	virtual HRESULT TCOMAPI Clear() = 0;
	virtual HRESULT TCOMAPI AddEventTypeExpression(TcEventType type, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddEventClassExpression(const GUID& eventClass, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddEventIdExpression(ULONG eventId, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddSeverityExpression(TcEventSeverity severity, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddTimeStampExpression(TcEventTimeStampType type, ULONGLONG timeStamp, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddSourceGuidExpression(const GUID& sourceGuid, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddSourceIdExpression(ULONG sourceId, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddSourceNameExpression(const char* sourceName, TcStringComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddJsonAttributeExpression(const char* path, const char* value, TcStringComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddLogicalOperator(TcLogicalOperator type) = 0;
	virtual HRESULT TCOMAPI AddNotOperator() = 0;

	virtual HRESULT TCOMAPI CreateExpressionGroup(ITcEventFilter** pipGroup) = 0;
	virtual HRESULT TCOMAPI AddExpressionGroup(ITcEventFilter* ipGroup) = 0;

	virtual HRESULT TCOMAPI Validate(bool& bResult) = 0;
	virtual HRESULT TCOMAPI Clone(ITcEventFilter** pipClone) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventFilter, IID_ITcEventFilter);

struct __declspec(novtable) ITcEventUniqueIdFilter : public ITcUnknown
{
	virtual HRESULT TCOMAPI AddUniqueIdExpression(ULONG id, TcComparisonOperator op) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventUniqueIdFilter, IID_ITcEventUniqueIdFilter);

struct __declspec(novtable) ITcEtherCATDeviceEventFilter : public ITcUnknown
{
	virtual HRESULT TCOMAPI AddIsEtherCATDeviceEventExpression(TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddVendorIdExpression(ULONG vendorId, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddProductCodeExpression(ULONG productCode, TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddRevisionNoExpression(ULONG revisionNo, TcComparisonOperator op) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEtherCATDeviceEventFilter, IID_ITcEtherCATDeviceEventFilter);

struct __declspec(novtable) ITcAlarmFilter : public ITcUnknown
{
	virtual HRESULT TCOMAPI AddIsActiveExpression(TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddIsRaisedExpression(TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddIsWaitForConfirmationExpression(TcComparisonOperator op) = 0;
	virtual HRESULT TCOMAPI AddConfirmationStateExpression(TcEventConfirmationState state, TcComparisonOperator op) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAlarmFilter, IID_ITcAlarmFilter);

struct __declspec(novtable) ITcExportSettings : public ITcUnknown
{
	virtual HRESULT TCOMAPI SetSorting(TcEventField eField, TcEventSortOrder eOrder) = 0;
	virtual HRESULT TCOMAPI SetLimit(TcEventLimitType eType, LONG nLimit, LONG nOffset) = 0;
	virtual HRESULT TCOMAPI SetTimeFormat(TcExportTimeFormat eFormat, TcExportTimeType eType, TcExportTimePrecision ePrecision, LONG nLangId, PCCH sFormat) = 0;

	virtual HRESULT TCOMAPI AddLanguage(LONG nLangId, PCCH sHeader) = 0;
	virtual HRESULT TCOMAPI AddField(TcEventField eType, PCCH sHeader, PCCH sPath) = 0;
	
	virtual HRESULT TCOMAPI CreateFilter(ITcEventFilter** pipFilter) = 0;
	virtual HRESULT TCOMAPI AddFilter(ITcEventFilter* ipFilter) = 0;

	virtual HRESULT TCOMAPI Clear() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcExportSettings, IID_ITcExportSettings);

struct __declspec(novtable) ITcClearLoggedEventsSettings : public ITcUnknown
{
	virtual HRESULT TCOMAPI SetSorting(TcEventField eField, TcEventSortOrder eOrder) = 0;
	virtual HRESULT TCOMAPI SetLimit(TcEventLimitType eType, LONG nLimit, LONG nOffset) = 0;

	virtual HRESULT TCOMAPI AddFilter(ITcEventFilter* ipFilter) = 0;

	virtual HRESULT TCOMAPI Clear() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcClearLoggedEventsSettings, IID_ITcClearLoggedEventsSettings);

struct __declspec(novtable) ITcCsvExportSettings : public ITcExportSettings
{
	virtual HRESULT TCOMAPI SetDelimiter(PCCH sDelimiter) = 0;
	virtual HRESULT TCOMAPI GetDelimiter(PCHAR sDelimiter, ULONG& nDelimiter) = 0;

	virtual HRESULT TCOMAPI SetWithHeader(BOOL bValue) = 0;
	virtual HRESULT TCOMAPI GetWithHeader(BOOL& bValue) = 0;

	virtual HRESULT TCOMAPI SetLocale(LONG nLangId) = 0;
	virtual HRESULT TCOMAPI GetLocale(LONG& nLangId) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCsvExportSettings, ITcCsvExportSettings);

struct __declspec(novtable) ITcEventFilterConfig : public ITcUnknown
{
	virtual HRESULT TCOMAPI AddEventClass(const GUID& eventClass, TcEventSeverity severity) = 0;
	virtual HRESULT TCOMAPI RemoveEventClass(const GUID& eventClass) = 0;

	virtual HRESULT TCOMAPI AddSourceInfo(ITcSourceInfo* ipSourceInfo, TcEventSeverity severity) = 0;
	virtual HRESULT TCOMAPI RemoveSourceInfo(ITcSourceInfo* ipSourceInfo) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcEventFilterConfig, IID_ITcEventFilterConfig);

struct __declspec(novtable) ITcMessageListener : public ITcUnknown
{
	virtual HRESULT TCOMAPI OnMessageSent(ITcEvent* ipEvent) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcMessageListener, IID_ITcMessageListener);

struct __declspec(novtable) ITcAlarmListener : public ITcUnknown
{
	virtual HRESULT TCOMAPI OnAlarmRaised(ITcEvent* ipEvent) = 0;
	virtual HRESULT TCOMAPI OnAlarmCleared(ITcEvent* ipEvent) = 0;
	virtual HRESULT TCOMAPI OnAlarmConfirmed(ITcEvent* ipEvent) = 0;
	virtual HRESULT TCOMAPI OnAlarmDisposed(ITcEvent* ipEvent) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcAlarmListener, IID_ITcAlarmListener);


class TcSourceInfo : public ITcSourceInfo
{
public:

	DECLARE_IUNKNOWN()

	TcSourceInfo()
	{
		Init(0, 0);
	}

	TcSourceInfo(const TcSourceInfo &reference)
	{
		m_nCount = reference.m_nCount;
		m_cbData = reference.m_cbData;

		m_pTypes = new TcSerializedSourceInfoType[m_nCount];
		memcpy(m_pTypes, reference.m_pTypes, m_nCount * sizeof(TcSerializedSourceInfoType));

		m_pData = new BYTE[m_cbData];
		memcpy(m_pData, reference.m_pData, m_cbData);
	}

	explicit TcSourceInfo(ULONG sourceId)
	{
		Init(1, sizeof(ULONG));
		AddValue(TcSourceInfoType::Id, &sourceId, sizeof(ULONG));
	}

	explicit TcSourceInfo(const GUID& sourceGuid)
	{
		Init(1, sizeof(GUID));
		AddValue(TcSourceInfoType::Guid, &sourceGuid, sizeof(GUID));
	}

	explicit TcSourceInfo(const char* sourceName)
	{
		if (sourceName == NULL)
		{
			Init(0, 0);
			return;
		}

		Init(1, (ULONG)strlen(sourceName) + 1);
		AddValue(TcSourceInfoType::Name, sourceName, strlen(sourceName) + 1);
	}

	explicit TcSourceInfo(const char* sourceName, ULONG sourceId)
	{
		Init(2, sizeof(ULONG) + (ULONG)strlen(sourceName) + 1);
		AddValue(TcSourceInfoType::Id, &sourceId, sizeof(ULONG));
		AddValue(TcSourceInfoType::Name, sourceName, strlen(sourceName) + 1);
	}

	explicit TcSourceInfo(const char* sourceName, GUID sourceGuid)
	{
		Init(2, sizeof(GUID) + (ULONG)strlen(sourceName) + 1);
		AddValue(TcSourceInfoType::Guid, &sourceGuid, sizeof(GUID));
		AddValue(TcSourceInfoType::Name, sourceName, strlen(sourceName) + 1);
	}

	explicit TcSourceInfo(ITcSourceInfo* ipSourceInfo)
	{
		ULONG numSourceTypes = 0;
		ULONG cbSourceDara = 0;
		const void* pSourceData = NULL;
		const TcSerializedSourceInfoType* pSourceTypes;

		if (ipSourceInfo != NULL)
		{
			ipSourceInfo->GetNumTypes(numSourceTypes);
			ipSourceInfo->GetData(&pSourceData);
			ipSourceInfo->GetDataSize(cbSourceDara);
			ipSourceInfo->GetTypes(&pSourceTypes);
		}

		Init(numSourceTypes, cbSourceDara);

		m_nCount = numSourceTypes;
		if (pSourceData != NULL && pSourceTypes != NULL)
		{
			memcpy(m_pData, pSourceData, m_cbData);
			memcpy(m_pTypes, pSourceTypes, m_nCount * sizeof(TcSerializedSourceInfoType));
		}
	}

	virtual ~TcSourceInfo()
	{
		if (m_pTypes != NULL)
		{
			delete[] m_pTypes;
			m_pTypes = NULL;
		}

		if (m_pData)
		{
			delete[] m_pData;
			m_pData = NULL;
		}
	}

	TcSourceInfo& operator=(const TcSourceInfo& other) {
		TcSourceInfo tmp(other);

		m_nCount = tmp.m_nCount;
		m_cbData = tmp.m_cbData;
		swap(m_pTypes, tmp.m_pTypes);
		swap(m_pData, tmp.m_pData);

		return *this;
	}
	operator ITcSourceInfo**() { return NULL; }

	ULONG GetTypeInfoSize() const
	{
		return sizeof(TcSerializedSourceInfoType) * m_nCount;
	}

	ULONG GetUsedDataSize() const
	{
		ULONG cbData = 0;
		for (ULONG i = 0; i < m_nCount; ++i)
		{
			if (m_pTypes[i].eType != TcSourceInfoType::Undefined)
				cbData += m_pTypes[i].cbData;
		}
		return cbData;
	}

	HRESULT SetSourceId(ULONG sourceId)
	{
		return SetValue(TcSourceInfoType::Id, &sourceId, sizeof(ULONG));
	}

	HRESULT SetSourceGuid(const GUID& sourceGuid)
	{
		return SetValue(TcSourceInfoType::Guid, &sourceGuid, sizeof(GUID));
	}

	HRESULT SetSourceName(const char* sourceName)
	{
		if (sourceName == NULL)
			return SetValue(TcSourceInfoType::Name, "", 1);

		return SetValue(TcSourceInfoType::Name, sourceName, (ULONG)strlen(sourceName) + 1);
	}

	HRESULT GetSourceId(ULONG& sourceId)
	{
		for (ULONG i = 0; i < m_nCount; ++i)
		{
			if (m_pTypes[i].eType == TcSourceInfoType::Id)
			{
				sourceId = *(ULONG*)((BYTE*)m_pData + m_pTypes[i].obData);
				return S_OK;
			}
		}
		return S_FALSE;
	}


	HRESULT GetSourceGuid(GUID& eventClass)
	{
		for (ULONG i = 0; i < m_nCount; ++i)
		{
			if (m_pTypes[i].eType == TcSourceInfoType::Guid)
			{
				eventClass = *(GUID*)((BYTE*)m_pData + m_pTypes[i].obData);
				return S_OK;
			}
		}
		return S_FALSE;
	}

	HRESULT GetSourceName(CHAR* pBuffer, ULONG cbBuffer)
	{
		for (ULONG i = 0; i < m_nCount; ++i)
		{
			if (m_pTypes[i].eType == TcSourceInfoType::Name)
			{

				if (m_pTypes[i].cbData > 1)
				{
					const char* name = (const char*)((BYTE*)m_pData + m_pTypes[i].obData);
					size_t cbLength = m_pTypes[i].cbData > cbBuffer ? cbBuffer : m_pTypes[i].cbData;

					memcpy(pBuffer, name, cbLength - 1);
					pBuffer[cbLength - 1] = '\0';
				}
				else
				{
					pBuffer[0] = '\0';
				}
				return S_OK;
			}
		}
		return S_FALSE;
	}

#pragma region "ITcSourceInfo"
	HRESULT TCOMAPI GetNumTypes(ULONG& nCount) override
	{
		nCount = m_nCount;
		return S_OK;
	}

	virtual HRESULT TCOMAPI GetTypes(const TcSerializedSourceInfoType** pSourceInfoTypes) override
	{
		*pSourceInfoTypes = m_pTypes;
		return S_OK;
	}

	virtual HRESULT TCOMAPI GetDataSize(ULONG& cbData) override
	{
		cbData = GetUsedDataSize();
		return S_OK;
	}
	virtual HRESULT TCOMAPI GetData(const void** pData) override
	{
		*pData = m_pData;
		return S_OK;
	}
#pragma endregion

private:
	ULONG m_nCount;
	ULONG m_cbData;
	TcSerializedSourceInfoType* m_pTypes;
	BYTE* m_pData;

	template<typename T>
	inline void swap(T& left, T& right)
	{
		T tmp = left;
		left = right;
		right = tmp;
	}

	void Init(ULONG nCount, ULONG cbData)
	{
		m_nCount = 0;
		m_cbData = cbData;

		m_pTypes = NULL;
		m_pData = NULL;

		if (nCount > 0 && cbData > 0)
		{
			m_pTypes = new TcSerializedSourceInfoType[nCount];
			memset(m_pTypes, 0, nCount * sizeof(TcSerializedSourceInfoType));

			m_pData = new BYTE[m_cbData];
		}
	}

	HRESULT AddValue(TcSourceInfoType eType, const void* pValue, size_t size)
	{
		m_pTypes[m_nCount].eType = eType;
		m_pTypes[m_nCount].obData = m_nCount == 0 ? 0 : m_pTypes[m_nCount - 1].obData + m_pTypes[m_nCount - 1].cbData;
		m_pTypes[m_nCount].cbData = (ULONG)size;

		memcpy(&m_pData[m_pTypes[m_nCount].obData], pValue, m_pTypes[m_nCount].cbData);

		m_nCount++;

		return S_OK;
	}

	HRESULT SetValue(TcSourceInfoType type, const void* pValue, ULONG size)
	{
		LONG index = -1;
		ULONG cbUsedData = 0;

		for (ULONG i = 0; i < m_nCount; ++i)
		{
			if (m_pTypes[i].eType == type)
			{
				index = i;
			}

			if (m_pTypes[i].eType  != TcSourceInfoType::Undefined)
				cbUsedData += m_pTypes[i].cbData;
		}

		if (index < 0)
		{
			ULONG cbNewUsedData = cbUsedData + size;

			if (cbNewUsedData > m_cbData)
			{
				if (m_pData != NULL)
				{
					BYTE* pOldData = m_pData;
					m_pData = new BYTE[cbNewUsedData];

					memcpy(m_pData, pOldData, m_cbData);

					delete[] pOldData;

				}
				else
				{
					m_pData = new BYTE[cbNewUsedData];
				}

				if (m_pTypes != NULL)
				{
					TcSerializedSourceInfoType* pOldTypes = m_pTypes;

					m_pTypes = new TcSerializedSourceInfoType[m_nCount + 1];
					memcpy(m_pTypes, pOldTypes, m_nCount * sizeof(TcSerializedSourceInfoType));

					delete[] pOldTypes;
				}
				else
				{
					m_pTypes = new TcSerializedSourceInfoType[m_nCount + 1];
				}


				m_cbData = cbNewUsedData;
			}

			AddValue(type, pValue, size);
		}
		else
		{
			if (m_pTypes[index].cbData == size)
			{
				memcpy(m_pData + m_pTypes[index].obData, pValue, size);
			}
			else
			{
				BYTE* pOldData = m_pData;

				ULONG cbNewUsedData = +size;

				m_cbData = cbUsedData - m_pTypes[index].cbData + size;
				m_pData = new BYTE[cbNewUsedData];


				ULONG obData = 0;
				for (ULONG i = 0; i < m_nCount; ++i)
				{
					if (i != static_cast<ULONG>(index))
					{
						memcpy(m_pData + obData, pOldData + m_pTypes[index].obData, m_pTypes[index].cbData);
					}
					else
					{
						m_pTypes[index].cbData = size;
						memcpy(m_pData + obData, pValue, m_pTypes[index].cbData);
					}
					m_pTypes[index].obData = obData;
					obData += m_pTypes[index].cbData;
				}
			}
		}
		return S_OK;
	}
};

inline BEGIN_INTERFACE_MAP(TcSourceInfo)
INTERFACE_ENTRY(IID_ITcSourceInfo, ITcSourceInfo)
END_INTERFACE_MAP()
