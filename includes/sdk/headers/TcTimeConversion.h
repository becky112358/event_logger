///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBase.h"

//Input: day: range 0...30, month: range 1...12
//Output: 0: Sunday, 6 = Saturday.
DLL_EXPORT WORD TCFRAMEWORKAPI TcDayOfWeek(WORD day, WORD month, WORD year);
DLL_EXPORT BOOL TCFRAMEWORKAPI TcIsLeapYear(WORD year);
DLL_EXPORT WORD TCFRAMEWORKAPI TcDaysInYear(WORD year);
DLL_EXPORT WORD TCFRAMEWORKAPI TcDaysInMonth (WORD year, WORD month);
DLL_EXPORT VOID TCFRAMEWORKAPI TcSystemTimeToFileTime(const SYSTEMTIME* lpSystemTime, FILETIME *lpFileTime);
DLL_EXPORT VOID TCFRAMEWORKAPI TcFileTimeToSystemTime(const FILETIME *lpFileTime,  SYSTEMTIME* lpSystemTime);
DLL_EXPORT VOID TCFRAMEWORKAPI TcSystemTimeToFileTime(const SYSTEMTIME* lpSystemTime, ULONGLONG& ul64FileTime);
DLL_EXPORT VOID TCFRAMEWORKAPI TcFileTimeToSystemTime(const ULONGLONG& ul64FileTime, SYSTEMTIME* lpSystemTime);

DLL_EXPORT bool		TCFRAMEWORKAPI TcIsISO8601TimeFormat(PCCH sDT);
DLL_EXPORT ULONG		TCFRAMEWORKAPI TcDecodeDateTime(PCCH sDT);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcDecodeDcTime(PCCH sDT);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcDecodeFileTime(PCCH sFT);
DLL_EXPORT bool		TCFRAMEWORKAPI TcEncodeDateTime(ULONG value, PCHAR p, UINT len);
DLL_EXPORT bool		TCFRAMEWORKAPI TcEncodeDcTime(LONGLONG value, PCHAR p, UINT len);
DLL_EXPORT bool		TCFRAMEWORKAPI TcEncodeFileTime(LONGLONG value, PCHAR p, UINT len);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcDcTimeToFileTime(LONGLONG dcTime);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcFileTimeToDcTime(LONGLONG fileTime);
DLL_EXPORT ULONG		TCFRAMEWORKAPI TcDcTimeToDateTime(LONGLONG dcTime);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcDateTimeToDcTime(ULONG dateTime);
DLL_EXPORT ULONG		TCFRAMEWORKAPI TcFileTimeToDateTime(LONGLONG fileTime);
DLL_EXPORT LONGLONG  TCFRAMEWORKAPI TcDateTimeToFileTime(ULONG dateTime);
