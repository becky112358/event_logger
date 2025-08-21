///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcError.h"
#include "TcStructuredExceptionHandling.h"

#define TCSTL_ERROR TC_SEH_ERROR
#define TCSTL_DEBUG_ERROR TC_SEH_DEBUG_ERROR
#define TCSTL_CONDITIONAL_ERROR TC_SEH_CONDITIONAL_ERROR
#define TCSTL_CONDITIONAL_DEBUG_ERROR TC_SEH_CONDITIONAL_DEBUG_ERROR
#define TCSTL_ERROR_DYNAMIC TC_SEH_ERROR_DYNAMIC
#define TCSTL_BUGVERIFY(bCondition) TC_SEH_BUGVERIFY(bCondition, FACILITY_TC_STL)
#define TCSTL_ASSERT(bCondition) TC_SEH_ASSERT(bCondition, FACILITY_TC_STL)

inline bool IsTcStlExceptionCode(const NTSTATUS nCode)
{
	return TCCHECK_FACILITY_CODE(FACILITY_TC_STL, nCode);
}

inline const char *GetTcStlExceptionDescription(const NTSTATUS nCode)
{
	switch(nCode)
	{
		case STATUS_TCSTL_ITERATOR_NOT_INCREMENTABLE:
			return "STL: Iterator not incrementable";
		case STATUS_TCSTL_ITERATOR_NOT_DECREMENTABLE:
			return "STL: Iterator not decrementable";
		case STATUS_TCSTL_ITERATOR_NOT_DEREFERENCABLE:
			return "STL: Iterator not dereferencable";
		case STATUS_TCSTL_ABORT:
			return "STL: Abort";
		case STATUS_TCSTL_BAD_WEAK_PTR:
			return "STL: Bad weak_ptr";
		case STATUS_TCSTL_BAD_OPTIONAL_ACCESS:
			return "STL: Bad optional access";
		case STATUS_TCSTL_SE_OPERATION_NOT_PERMITTED:
			return "STL (system error): Operation not permitted";
		case STATUS_TCSTL_SE_RESOURCE_DEADLOCK_WOULD_OCCUR:
			return "STL (system error): Resource deadlock would occur";
		case STATUS_TCSTL_MEMORY_ALLOCATION_FAILED:
			return "STL: Memory allocation failed";
		case STATUS_TCSTL_MEMORY_CORRUPTION:
			return "STL: Memory corruption";
		case STATUS_TCSTL_INCOMPATIBLE:
			return "STL: Incompatible object (allocator, iterator, ...)";
		case STATUS_TCSTL_OUT_OF_RANGE:
			return "STL: Out of range";
		case STATUS_TCSTL_INVALID_PARAMETER:
			return "STL: Invalid parameter";
		case STATUS_TCSTL_LENGTH_ERROR:
			return "STL: Length error";
		case STATUS_TCSTL_OVERFLOW:
			return "STL: Overflow";
		case STATUS_TCSTL_NOT_SUPPORTED:
			return "STL: Attempt to use unsupported functionality";
		case STATUS_TCSTL_CRITICAL_SECTION_ERROR:
			return "STL: Mutex error";
		case STATUS_TCSTL_ASSERTION_FAILED:
			return "STL: Assertion failed";
		default:
			return "STL: Unknown exception code";
	}
}
