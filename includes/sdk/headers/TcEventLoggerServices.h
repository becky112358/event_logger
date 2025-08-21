///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBaseServices.h"

#if defined(TC_ENVIRONMENT_RT) || defined(ROUTER_TCOM) || defined(TC_DEFINE_EVENT_GUIDS) || defined(TC_ENVIRONMENT_OS)
TCOM_DECL_INTERFACE("B2D5D4E2-07F6-44F4-A292-92CA8035AA86", ITcEventLogger)
TCOM_DECL_INTERFACE("428FA42C-A445-4A65-8B1C-E156F288BF2B", ITcEventLogger2)
TCOM_DECL_INTERFACE("BFC9A87A-F6DE-499A-AC45-F3B1A59315F9", ITcSerializedArguments)
TCOM_DECL_INTERFACE("4A9CB0E9-8969-4B85-B567-605110511200", ITcEvent)
TCOM_DECL_INTERFACE("6474ED2C-E483-454E-A67D-233E6D337C08", ITcMessage)
TCOM_DECL_INTERFACE("77D5D639-16DD-48F7-8490-F632AA095917", ITcMessage2)
TCOM_DECL_INTERFACE("47B6BEE8-0ECB-4C92-9D93-FB11D3BA0336", ITcMessageListener)
TCOM_DECL_INTERFACE("EC6D4FF7-5805-4DDB-A316-27894E77D644", ITcAlarm)
TCOM_DECL_INTERFACE("9C3FF78D-97E8-4F85-8187-ADB3BCB87387", ITcAlarm2)
TCOM_DECL_INTERFACE("C0CCD9D7-DDCD-4C2D-A24C-B1F3257C9A64", ITcAlarmListener)
TCOM_DECL_INTERFACE("C3BF7AA5-0A83-4CFA-9A7A-04C1DFD0E5DD", ITcAsyncResult)
TCOM_DECL_INTERFACE("0C376246-D573-4991-8A88-49FC3AD141E2", ITcAsyncResult2)
TCOM_DECL_INTERFACE("23293450-14C5-484C-B74F-4E0A8DFD115D", ITcAsyncStringResult)
TCOM_DECL_INTERFACE("F7BF6767-548B-493C-899B-06A477976F11", ITcSourceInfo)
TCOM_DECL_INTERFACE("5E5A2C0C-D379-40FB-80C5-F2383CD75FE0", ITcArguments)
TCOM_DECL_INTERFACE("70904B1B-F00E-4FCB-BE59-151086E9B8F6", ITcEventFilterConfig)
TCOM_DECL_INTERFACE("60A20A6E-CEBB-49F9-AC90-8E4AB112E9C0", ITcExportSettings)
TCOM_DECL_INTERFACE("98778832-1913-4171-9E9D-5B0D53C5EA9E", ITcCsvExportSettings)
TCOM_DECL_INTERFACE("C47387FE-3C19-4548-ACA8-C346C352E370", ITcClearLoggedEventsSettings)
TCOM_DECL_INTERFACE("7404CD52-3776-4B1A-9525-B7C1D691DFC4", ITcEventFilter)
TCOM_DECL_INTERFACE("68F42581-09B1-43D1-A4EA-EC93B57AEB57", ITcEtherCATDeviceEventFilter)
TCOM_DECL_INTERFACE("7DDECC5B-08E8-490C-AA9C-5F20E7834731", ITcAlarmFilter)
TCOM_DECL_INTERFACE("0D73E69C-2D9B-4B12-A5F7-3E8AE9DD2149", ITcEventUniqueIdProvider)
TCOM_DECL_INTERFACE("D6EFF8F5-187C-48E1-8151-33BB73C8399D", ITcEventUniqueIdFilter)
#endif

#define TCEVENT_MAXARGS 16
#define TCEVENT_MAXBUFFERSIZE 1024
#define GENERIC_INSTANCE_ID (ULONG)0
const ULONG SOURCE_INFO_MAX_BUFFER_SIZE = 1024;

// {E7A4B1E0-F4CF-4733-95D5-73DF084B60F8}
static const GUID UninitializedGuid = { 0xe7a4b1e0, 0xf4cf, 0x4733,{ 0x95, 0xd5, 0x73, 0xdf, 0x8, 0x4b, 0x60, 0xf8 } };

#define S_TCEVENT_ALREADY_EXISTS  (HRESULT)183L

#if !defined(_TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_)
#define _TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_
BEGIN_SCOPED_TYPED_ENUM(TcEventSeverity, SHORT)
{
	Verbose = 0,
	Info,
	Warning,
	Error,
	Critical,
};
END_SCOPED_TYPED_ENUM(TcEventSeverity, SHORT)
#endif // !defined(_TC_TYPE_B57D3F4A_0836_49B0_81C3_BED5F4817EC9_INCLUDED_)

#if !defined(_TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_)
#define _TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_
struct TcEventEntry
{
	GUID uuidEventClass;
	ULONG nEventId;
	TcEventSeverity eSeverity;
};
#endif // !defined(_TC_TYPE_F00C83AD_DEC8_486E_AE99_5E0A75C26DE0_INCLUDED_)


BEGIN_SCOPED_TYPED_ENUM(TcEventConfirmationState, SHORT)
{
	NotSupported = 0,
	NotRequired,
	WaitForConfirmation,
	Confirmed,
	Reset
};
END_SCOPED_TYPED_ENUM(TcEventConfirmationState, SHORT)

BEGIN_SCOPED_TYPED_ENUM(TcEventArgumentType, SHORT)
{
	Undefined,
	Boolean,
	Int8,
	Int16,
	Int32,
	Int64,
	UInt8,
	UInt16,
	UInt32,
	UInt64,
	Float,
	Double,
	Char,
	WChar,
	StringType,
	WStringType,
	EventReference,
	FormatString,
	ExternalTimestamp,
	Blob,
	AdsNotificationStream,
	UTF8EncodedString,
	UTF16EncodedString,
	UTF32EncodedString
};
END_SCOPED_TYPED_ENUM(TcEventArgumentType, SHORT)

BEGIN_SCOPED_TYPED_ENUM(TcSourceInfoType, ULONG)
{
	Undefined = 0x0,
	Id = 0x1,
	Guid = 0x2,
	Name = 0x4
};
END_SCOPED_TYPED_ENUM(TcSourceInfoType, ULONG)
DEFINE_ENUM_OPERATORS(TcSourceInfoType, ULONG)

BEGIN_SCOPED_TYPED_ENUM(TcExportFormat, SHORT)
{
	 Csv = 0,
	 Json,
	 Xml
};
END_SCOPED_TYPED_ENUM(TcExportFormat, SHORT)
DEFINE_ENUM_OPERATORS(TcExportFormat, SHORT)

BEGIN_SCOPED_TYPED_ENUM(TcEventField, uint16_t)
{
	 Id = 0,
	 SeverityLevel,
	 EventClass,
	 EventClassName,
	 EventId,
	 EventText,
	 TimeRaised,
	 TimeConfirmed,
	 TimeCleared,
	 SourceName,
	 SourceId,
	 SourceGuid,
	 JsonAttribute
};
END_SCOPED_TYPED_ENUM(TcEventField, uint16_t)
DEFINE_ENUM_OPERATORS(TcEventField, uint16_t)

BEGIN_SCOPED_TYPED_ENUM(TcEventSortOrder, SHORT)
{
	Descending = 0,
	Ascending
};
END_SCOPED_TYPED_ENUM(TcEventSortOrder, SHORT)
DEFINE_ENUM_OPERATORS(TcEventSortOrder, SHORT)

BEGIN_SCOPED_TYPED_ENUM(TcEventLimitType, uint16_t)
{
	First = 0,
	Last
};
END_SCOPED_TYPED_ENUM(TcEventLimitType, uint16_t)
DEFINE_ENUM_OPERATORS(TcEventLimitType, uint16_t)


BEGIN_SCOPED_TYPED_ENUM(TcExportTimeType, uint16_t)
{
	 UTC = 0,
	 LocaleTime
};
END_SCOPED_TYPED_ENUM(TcExportTimeType, uint16_t)
DEFINE_ENUM_OPERATORS(TcExportTimeType, uint16_t)

BEGIN_SCOPED_TYPED_ENUM(TcExportTimeFormat, uint16_t)
{
	Filetime = 0,
	Iso8601,
	IecDateAndTime,
	VariantTime,
	Localized,
	Custom
};
END_SCOPED_TYPED_ENUM(TcExportTimeFormat, uint16_t)
DEFINE_ENUM_OPERATORS(TcExportTimeFormat, uint16_t)

#pragma warning( push )
#pragma warning( disable: 4341 )
BEGIN_SCOPED_TYPED_ENUM(TcExportTimePrecision, int16_t)
{
	Floating = -1,
	Seconds = 0,
	Milliseconds = 3,
	Microseconds = 6,
	OneHundertNanoseconds = 7,
	Nanoseconds = 9
};
END_SCOPED_TYPED_ENUM(TcExportTimePrecision, int16_t)
#pragma warning( pop )

BEGIN_SCOPED_TYPED_ENUM(TcLogicalOperator, int16_t)
{
	And = 0,
	Or
};
END_SCOPED_TYPED_ENUM(TcLogicalOperator, int16_t)

BEGIN_SCOPED_TYPED_ENUM(TcComparisonOperator, int16_t)
{
		EqualTo = 0,
		NotEqualTo,
		LessThan,
		GreaterThan,
		LessThanOrEqualTo,
		GreaterThanOrEqualTo
};
END_SCOPED_TYPED_ENUM(TcComparisonOperator, int16_t)


BEGIN_SCOPED_TYPED_ENUM(TcStringComparisonOperator, int16_t)
{
	EqualTo = 0,
	NotEqualTo,
	Like,
	IsNull,
	IsNotNull
};
END_SCOPED_TYPED_ENUM(TcStringComparisonOperator, int16_t)

BEGIN_SCOPED_TYPED_ENUM(TcEventType, SHORT)
{
	Message = 0,
	Alarm
};
END_SCOPED_TYPED_ENUM(TcEventType, SHORT)


BEGIN_SCOPED_TYPED_ENUM(TcEventTimeStampType, int16_t)
{
	Raised,
	Confirmed,
	Cleared
};
END_SCOPED_TYPED_ENUM(TcEventTimeStampType, int16_t)

struct TcSerializedSourceInfoType
{
	TcSourceInfoType eType;
	ULONG obData;
	ULONG cbData;
};

struct TcEventReference
{
	TcEventReference() : EventId(0)
	{
	}

	explicit TcEventReference(ULONG eventId)
		: EventClass(UninitializedGuid)
		, EventId(eventId)
	{
	}

	TcEventReference(GUID sourceGuid, ULONG eventId)
		: EventClass(sourceGuid)
		, EventId(eventId)
	{
	}

	GUID EventClass;
	ULONG EventId;
};

struct TcBlobArgument
{
	TcBlobArgument(const BYTE* pData, const ULONG cbData)
		: pData(pData)
		, cbData(cbData)
	{
	}

	const BYTE* pData;
	const ULONG cbData;
};

#if !defined(_TC_TYPE_97933333_E672_4590_AE31_3F2C0F1FC391_INCLUDED_)
#define _TC_TYPE_97933333_E672_4590_AE31_3F2C0F1FC391_INCLUDED_
namespace TcEvents
{
	namespace AdsLogMessage
	{
		static CONSTEXPR const char* sEventClass = "{97933333-E672-4590-AE31-3F2C0F1FC391}";
		//{97933333-E672-4590-AE31-3F2C0F1FC391}
		CONSTEXPR const GUID EventClass = { 0x97933333,0xe672,0x4590,{ 0xae,0x31,0x3f,0x2c,0x0f,0x1f,0xc3,0x91 } };

		struct EventIds
		{
			enum
			{
				AdsLogMessage = 0x1, //
			};
		};

		CONSTEXPR const TcEventEntry AdsLogMessage = { EventClass, EventIds::AdsLogMessage, TcEventSeverity::Verbose };
	};
};
#endif // !defined(_TC_TYPE_97933333_E672_4590_AE31_3F2C0F1FC391_INCLUDED_)
