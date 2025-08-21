///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// framework version
#ifndef TC_VER
#define TC_VER	300
#endif

#define	FRAMEWORK_VERSION			3
#if TC_VER >= 302
	#define	FRAMEWORK_REVISION		2
	#define	FRAMEWORK_BUILD			1
	#define TC_REGISTRY_VERSION_STRING			_T("3.2")
#elif TC_VER >= 301
	#define	FRAMEWORK_REVISION		1
	#define	FRAMEWORK_BUILD			7
	#define TC_REGISTRY_VERSION_STRING			_T("3.1")
#else
	#define	FRAMEWORK_REVISION		0
	#define	FRAMEWORK_BUILD			1
	#define TC_REGISTRY_VERSION_STRING			_T("3.0")
#endif

#define TC_REGISTRY_VERSION_STRING_W2(b,r)	L ## #b L"." L ## #r
#define TC_REGISTRY_VERSION_STRING_W1(b,r)	TC_REGISTRY_VERSION_STRING_W2(b,r)
#define TC_REGISTRY_VERSION_STRING_W			TC_REGISTRY_VERSION_STRING_W1(FRAMEWORK_VERSION, FRAMEWORK_REVISION)

#define TC_REGISTRY_VERSION_STRING_A2(b,r)	#b "." #r
#define TC_REGISTRY_VERSION_STRING_A1(b,r)	TC_REGISTRY_VERSION_STRING_A2(b,r)
#define TC_REGISTRY_VERSION_STRING_A			TC_REGISTRY_VERSION_STRING_A1(FRAMEWORK_VERSION, FRAMEWORK_REVISION)


///////////////////////////////////////////////////////////////////////////////
// Platform             Build enviroment
// TwinCAT CE6/WEC7  -> TC_ENVIRONMENT_CE
// TwinCAT WEC7 + RT -> TC_ENVIRONMENT_CE_RT
// TwinCAT UM        -> TC_ENVIRONMENT_UM
// TwinCAT RT        -> TC_ENVIRONMENT_RT
// TwinCAT OS        -> TC_ENVIRONMENT_OS
// Win32             -> TC_ENVIRONMENT_APP (System Service, System Manager, TCATAdsAms.dll)
#if defined(WIN32_RUNTIME)
	#if defined(UNDER_CE)
		#if defined(TCRTOS)
			#ifndef TC_ENVIRONMENT_CE_RT
				#define TC_ENVIRONMENT_CE_RT
			#endif
		#else
			#define TC_ENVIRONMENT_CE
		#endif
	#else
		#define TC_ENVIRONMENT_UM
	#endif
#elif defined(IS_R0)
	#define TC_ENVIRONMENT_RT
#elif defined(TC_ENVIRONMENT_OS)
	//TC_ENVIRONMENT_OS is defined in Platforms Preprocessor Definition, no further definitions are necesassary
#else 
	#define TC_ENVIRONMENT_APP
#endif

#if !defined(TC_ENVIRONMENT_APP) && !defined(TC_ENVIRONMENT_CE) && !defined(TC_ENVIRONMENT_RT) && \
		!defined(TC_ENVIRONMENT_CE_RT) && !defined(TC_ENVIRONMENT_UM) && !defined(TC_ENVIRONMENT_OS)
#error "Invalid TwinCAT build enviroment"
#endif


///////////////////////////////////////////////////////////////////////////////
// Macros for a slim TcFramework as built by "Debug static"
/* TC_FRAMEWORK_SLIM is defined in the project settings as a preprocessor
define, handed in during compile time*/
#ifdef TC_FRAMEWORK_SLIM

/* Certain function names collide with the function names from standard C
functions (on purpose!). However it can be necessary to distinguish between
implementations. For that purpose namespaces are used. */
#define TC_FRAMEWORK_USE_RTLR0_NAMESPACE           (1)
#else

#endif

/* To make things easier the following 2 makros can be added respectively at
the beginning or the end of a file to put it into a namespace */
#ifdef TC_FRAMEWORK_USE_RTLR0_NAMESPACE
/* The name for a namespace if TC_FRAMEWORK_USE_SLIM_NAMESPACE is set. */
#define RTLR0_NAMESPACE             RtlR0
#define RTLR0_NAMESPACE_BEGIN       namespace RTLR0_NAMESPACE {
#define RTLR0_NAMESPACE_END         }
/* note that there is a semicolon at the end! */
#define RTLR0_NAMESPACE_USING       using namespace RTLR0_NAMESPACE;
#else
#ifdef __cplusplus
#define RTLR0_NAMESPACE_BEGIN       extern "C" {
#define RTLR0_NAMESPACE_END         }
#else
#define RTLR0_NAMESPACE_BEGIN       
#define RTLR0_NAMESPACE_END         
#endif
#define RTLR0_NAMESPACE_USING
#define RTLR0_NAMESPACE
#endif


///////////////////////////////////////////////////////////////////////////////
// DLL_EXPORT
///////////////////////////////////////////////////////////////////////////////
#ifdef	TCFRAMEWORK_EXPORTS
	#ifdef NO_TCDLL_EXPORT
		#define	DLL_EXPORT
	#else
		#define	DLL_EXPORT _declspec( dllexport )
	#endif
	#ifdef _AFXDLL
		#define	TCAT_AFX_MANAGE_STATE(x) AFX_MANAGE_STATE(x)
	#else
		#define	TCAT_AFX_MANAGE_STATE(x) 
	#endif 
#else
	#ifdef TCDLL_EXPORT
		#define	DLL_EXPORT _declspec( dllexport )
	#else
		#define	DLL_EXPORT
	#endif
	#ifdef _AFXDLL
		#define	TCAT_AFX_MANAGE_STATE(x) AFX_MANAGE_STATE(x)
	#else
		#define	TCAT_AFX_MANAGE_STATE(x) 
	#endif 
#endif
#ifndef POSIX
#define TCFRAMEWORKAPI __stdcall
#else
#define TCFRAMEWORKAPI
#endif

typedef	unsigned int SIZE_T_32;

//define nullptr if C++11 is not supported
#if defined(_MSC_VER) && _MSC_VER < 1600 
#ifndef nullptr
#define nullptr NULL
#endif // !nullptr
#endif

#if defined(TC_ENVIRONMENT_RT)

typedef	unsigned int	BOOL;
typedef BOOL*			PBOOL;
typedef	unsigned int	UINT;
typedef	UINT*		PUINT;
typedef	int		INT;
typedef	INT*		PINT;
typedef	unsigned short WORD;
typedef	WORD*		PWORD;
typedef	unsigned long	DWORD;
typedef	DWORD*	PDWORD;
typedef	unsigned char	BYTE;
typedef	BYTE*		PBYTE;
typedef	const void* PCVOID;
typedef	void**	PPVOID;
typedef	float*	PFLOAT;
typedef	double*	PDOUBLE;
typedef	float		FLOAT;
typedef	double	DOUBLE;

#ifndef __cplusplus
#ifdef  _X64_
typedef unsigned __int64  size_t;
#else
typedef unsigned int size_t;
#endif
#endif
#endif

#if defined(TC_ENVIRONMENT_OS)
#include <stdarg.h>
#include "TcOsDef.h"
#include "RtlR0.h"
#endif // defined(TC_ENVIRONMENT_OS)

#if defined(TC_ENVIRONMENT_RT) || defined(TC_ENVIRONMENT_CE_RT)

#define	LOBYTE(x)	((BYTE)(x))
#define	HIBYTE(x)	((BYTE)(((WORD)(x) >> 8) & 0xFF))
#define	LOWORD(x)	((WORD)(x))
#define	HIWORD(x)	((WORD)(((DWORD)(x) >> 16) & 0xFFFF))
#define	LODWORD(x)	((DWORD)(x))
#define	HIDWORD(x)	(*((DWORD*)&(x)+1))
#define	MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define	MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))

#endif

#if defined(TC_ENVIRONMENT_RT)

#define _T(x) x

// use intrinsic functions instead of secure functions decleared in string.h
#define _CRT_MEMORY_DEFINED
#define _CPP_MEMCHR_DEFINED

// functions must be declared before including DDK header
#ifdef __cplusplus
extern "C" {
#endif
int    __cdecl memcmp(const void *, const void *, size_t);
void * __cdecl memcpy(void *, const void *, size_t);
void * __cdecl memset(void *, int, size_t);
#ifdef __cplusplus
}
#endif
#pragma intrinsic(memcmp)
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)

#ifndef TC_SDK_ONLY
#include <ntddk.h>
#include <winerror.h>
#include <guiddef.h>
#include "platform/Common/crt/tcstdint.h"
#ifndef MAX_PATH
#define MAX_PATH		260
#endif

#else
#include "platform/TcRT/TcRtDef.h"
#endif // TC_NOWDK

///////////////////////////////////////////////////////////////////////////////
// compiler intrinsics 
#ifdef __cplusplus
extern "C" {
#endif
void   __cdecl _disable(void);
void   __cdecl _enable(void);
#ifdef __cplusplus
}
#endif
#pragma intrinsic(_disable)
#pragma intrinsic(_enable)

typedef unsigned short VARTYPE;

typedef struct tagVARIANT  
{
	VARTYPE vt;    
	unsigned short wReserved1;
	unsigned short wReserved2;    
	unsigned short wReserved3;    
	union 
	{
		unsigned char				bVal;                        // VT_UI1.
		short							iVal;                        // VT_I2    .
		LONG							lVal;                        // VT_I4    .
		float							fltVal;                    // VT_R4    .
		double						dblVal;                    // VT_R8    .
//		VARIANT_BOOL				boolVal;                        // VT_BOOL.
//		SCODE							scode;                    // VT_ERROR.
//		CY								cyVal;                    // VT_CY    .
//		DATE							date;                        // VT_DATE.
//		BSTR							bstrVal;                    // VT_BSTR.
//		IUnknown				*	punkVal;            // VT_UNKNOWN.
//		IDispatch			*	pdispVal;            // VT_DISPATCH.
//		SAFEARRAY			*	parray;            // VT_ARRAY|*.
		unsigned char		*	pbVal;                // VT_BYREF|VT_UI1.
		short					*	piVal;                // VT_BYREF|VT_I2.
		LONG					*	plVal;                // VT_BYREF|VT_I4.
		float					*	pfltVal;            // VT_BYREF|VT_R4.
		double				*	pdblVal;            // VT_BYREF|VT_R8.
//		VARIANT_BOOL		*	pboolVal;                // VT_BYREF|VT_BOOL.
//		SCODE					*	pscode;            // VT_BYREF|VT_ERROR.
//		CY						*	pcyVal;            // VT_BYREF|VT_CY.
//		DATE					*	pdate;                // VT_BYREF|VT_DATE.
//		BSTR					*	pbstrVal;            // VT_BYREF|VT_BSTR.
//		IUnknown FAR*		*	ppunkVal;            // VT_BYREF|VT_UNKNOWN.
//		IDispatch FAR*		*	ppdispVal;        // VT_BYREF|VT_DISPATCH.
//		SAFEARRAY FAR*		*	pparray;            // VT_ARRAY|*.
//		VARIANT				*	pvarVal;            // VT_BYREF|VT_VARIANT.
		void					*	byref;                // Generic ByRef.
	};
} VARIANT;

typedef	LONG		HRESULT;

typedef struct _FILETIME
    {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
    }	FILETIME;
typedef struct _FILETIME *PFILETIME;
typedef struct _FILETIME *LPFILETIME;

typedef struct _SYSTEMTIME
    {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
    }	SYSTEMTIME;
typedef struct _SYSTEMTIME *PSYSTEMTIME;
typedef struct _SYSTEMTIME *LPSYSTEMTIME;

#ifndef _TM_DEFINED
struct tm {
	int tm_sec;     /* seconds after the minute - [0,59] */
	int tm_min;     /* minutes after the hour - [0,59] */
	int tm_hour;    /* hours since midnight - [0,23] */
	int tm_mday;    /* day of the month - [1,31] */
	int tm_mon;     /* months since January - [0,11] */
	int tm_year;    /* years since 1900 */
	int tm_wday;    /* days since Sunday - [0,6] */
	int tm_yday;    /* days since January 1 - [0,365] */
	int tm_isdst;   /* daylight savings time flag */
};
#define _TM_DEFINED
#endif

#elif defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_APP) && (!defined(TCRTOS) && !defined(TC_ENVIRONMENT_OS) && !defined(POSIX))

#include <windows.h>
#if (_MSC_VER >= 1900)
#include <VersionHelpers.h>
#endif
#include <tchar.h>
#ifndef LODWORD
#define	LODWORD(x)	((DWORD)(x))
#endif
#ifndef HIDWORD
#define	HIDWORD(x)	(*((DWORD*)&(x)+1))
#endif

#ifdef UNDER_CE
	#include "vmlayout.h"
	#include "ceddk.h"
#else
	#ifdef _WINNT_
		typedef long NTSTATUS, *PNTSTATUS;
		#define STATUS_SUCCESS            ((NTSTATUS)0x00000000L) // ntsubauth
		#define NT_SUCCESS(Status)        ((NTSTATUS)(Status) >= 0)
		#define STATUS_UNSUCCESSFUL       ((NTSTATUS)0xC0000001L)
		#define STATUS_NOT_IMPLEMENTED           ((NTSTATUS)0xC0000002L)
		#define STATUS_INSUFFICIENT_RESOURCES    ((NTSTATUS)0xC000009AL)     // ntsubauth
		#define STATUS_DEVICE_BUSY        ((NTSTATUS)0x80000011L)
		#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)
		#define STATUS_INVALID_BLOCK_LENGTH      ((NTSTATUS)0xC0000173L)
		#define STATUS_FILE_ENCRYPTED            ((NTSTATUS)0xC0000293L)
		#define STATUS_INVALID_IMAGE_HASH        ((NTSTATUS)0xC0000428L)
		#define STATUS_INVALID_IMAGE_FORMAT      ((NTSTATUS)0xC000007BL)
		#define STATUS_INCOMPATIBLE_DRIVER_BLOCKED ((NTSTATUS)0xC0000424L)
		#define STATUS_IMAGE_CHECKSUM_MISMATCH   ((NTSTATUS)0xC0000221L)
		#define STATUS_MEMORY_NOT_ALLOCATED      ((NTSTATUS)0xC00000A0L)
		#define STATUS_OBJECT_PATH_NOT_FOUND     ((NTSTATUS)0xC000003AL)
		#define STATUS_IMAGE_CERT_REVOKED        ((NTSTATUS)0xC0000603L)

		#ifndef STATUS_INVALID_PARAMETER
			#define STATUS_INVALID_PARAMETER         ((NTSTATUS)0xC000000DL)
		#endif
	#else
		#include "ntstatus.h"
	#endif
#endif

	#include <stdio.h>
	#include <stddef.h>
	#include <stdlib.h>

	typedef double		DOUBLE;
	typedef double*	PDOUBLE;
	typedef const void* PCVOID;
	typedef PVOID* PPVOID;
	typedef	ULONG	DWORD;

#ifndef HAS_NTCOMPAT_H
	typedef	PVOID PIRP;
	typedef	PVOID	KIRQL;

	///////////////////////////////////////////////////////////////////////////////
	// class to encapsulate nt's unicode string implementation
	typedef struct _UNICODE_STRING {
		 USHORT Length;
		 USHORT MaximumLength;
	#ifdef MIDL_PASS
		 [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
	#else // MIDL_PASS
		 PWSTR  Buffer;
	#endif // MIDL_PASS
	} UNICODE_STRING;
	typedef UNICODE_STRING *PUNICODE_STRING;
	typedef const UNICODE_STRING *PCUNICODE_STRING;
	#define UNICODE_NULL ((WCHAR)0) // winnt

	///////////////////////////////////////////////////////////////////////////////
	// class to encapsulate nt's ansi string implementation
	typedef struct _STRING
	{
	  USHORT	Length;
	  USHORT	MaximumLength;
	  CHAR*	Buffer;
	} ANSI_STRING;
	typedef ANSI_STRING *PANSI_STRING;

#endif// !HAS_NTCOMPAT_H

#if defined(TC_ENVIRONMENT_CE) || (!defined(DISABLE_TWINCAT_STL) && !defined(TCFRAMEWORK_TESTS) && defined(TC_ENVIRONMENT_UM))
	#include "platform/Common/crt/tcstdint.h"
#else
	#include <stdint.h>
#endif

//#endif  // elif defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_CE) || defined(TC_ENVIRONMENT_APP) && !defined(TCRTOS)

#elif defined(TC_ENVIRONMENT_CE_RT)

#include "TcDefCeRt.h"

#elif defined(TC_ENVIRONMENT_OS)
	#include "stddef.h"
	#include "stdlib.h"
#elif defined(TCOS_APP)
	#include "OsUserTools.h"
#else

#error "Combination missing. Please implement me"

#endif

#if defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_APP) || defined(TC_ENVIRONMENT_OS)
	typedef enum _INTERFACE_TYPE {
		 InterfaceTypeUndefined = -1,
		 Internal,
		 Isa,
		 Eisa,
		 MicroChannel,
		 TurboChannel,
		 PCIBus,
		 VMEBus,
		 NuBus,
		 PCMCIABus,
		 CBus,
		 MPIBus,
		 MPSABus,
		 ProcessorInternal,
		 InternalPowerBus,
		 PNPISABus,
		 MaximumInterfaceType
	}INTERFACE_TYPE, *PINTERFACE_TYPE;
#endif  // defined(TC_ENVIRONMENT_UM) || defined(TC_ENVIRONMENT_APP)	|| defined(TC_ENVIRONMENT_OS)

typedef struct _CONTEXT TC_TASK_CONTEXT;

#define	IOSTATUS_SUCCESS					STATUS_SUCCESS
#define	IOSTATUS_PENDING					STATUS_PENDING
#define	IOSTATUS_NOT_IMPLEMENTED		STATUS_NOT_IMPLEMENTED
#define	IOSTATUS					LONG

///////////////////////////////////////////////////////////////////////////////
// compute the size of a struct member
#define sizeofmember(s,m) ((size_t) (sizeof(((s *)0)->m)))

///////////////////////////////////////////////////////////////////////////////
// Construct debug message with file name and line number
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "(" __STR1__(__LINE__)") : message: "

///////////////////////////////////////////////////////////////////////////////
#define ENDOF(p)				((p)+1)			//	pointer to end of *p
#define INBETWEEN(l,x,u)	( ((x)>=(l)) && ((x)<=(u)) ) 

///////////////////////////////////////////////////////////////////////////////
// Macros to support debug message with function name 
#define FNAMEA                  __FUNCTION__ "() "
#define FENTERA                 FNAMEA ">>> "
#define FLEAVEA                 FNAMEA "<<< "

#ifndef __FUNCTION_NAME__
    #ifndef POSIX
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else
		  #define __FUNCTION_NAME__   ""
    #endif
#endif
	
#define FTEXT(aCompileTimeString) _T(__FUNCTION_NAME__) _T("() ") _T(aCompileTimeString) _T("\n")

///////////////////////////////////////////////////////////////////////////////
// Macros to support debug message with system time
#define SYSTEMTIME_FMTSTRA "%04d/%02d/%02d %02d:%02d:%02d"
#define SYSTEMTIME_PARAMS(st) st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond

///////////////////////////////////////////////////////////////////////////////
// Macros used to implement function which map enum values or macros to a 
// constant string

// TCHAR variant
#define	DECLARE_VALUE_TO_STRING(GetTextFunc, ValueType) \
	const TCHAR* GetTextFunc( ValueType value)
#define	BEGIN_VALUE_TO_STRING(GetTextFunc, ValueType) \
	const TCHAR* GetTextFunc( ValueType value) {	switch (value)	{
#define ENTRY_VALUE_TO_STRING(macro) case macro: return (TCHAR*) _T(#macro);
#define DEFAULT_VALUE_TO_STRING(macro) default: return (TCHAR*) _T("!! unknown ") _T(#macro) _T(" !!");
#define END_VALUE_TO_STRING() } }

// CHAR variant
#define	DECLARE_VALUE_TO_STRINGA(GetTextFunc, ValueType) \
	PCCH GetTextFunc( ValueType value)
#define	BEGIN_VALUE_TO_STRINGA(GetTextFunc, ValueType) \
	PCCH GetTextFunc( ValueType value) {	switch (value)	{
#define ENTRY_VALUE_TO_STRINGA(macro) case macro: return #macro;
#define DEFAULT_VALUE_TO_STRINGA(macro) default: return "!! unknown " #macro " !!";
#define END_VALUE_TO_STRINGA() } }

// WCHAR variant
#define	DECLARE_VALUE_TO_STRINGW(GetTextFunc, ValueType) \
	PCWCH GetTextFunc( ValueType value)
#define	BEGIN_VALUE_TO_STRINGW(GetTextFunc, ValueType) \
	PCWCH GetTextFunc( ValueType value) {	switch (value)	{
#define ENTRY_VALUE_TO_STRINGW(macro) case macro: return #macro;
#define DEFAULT_VALUE_TO_STRINGW(macro) default: return L"!! unknown " L ## #macro L" !!";
#define END_VALUE_TO_STRINGW() } }

///////////////////////////////////////////////////////////////////////////////
// Macros used to calculate data structure sizes
#define	BIT2BYTE(x)			(((x)+7)/8)
#define	BIT2BYTECOND(x, b) (b?(((x)+7)/8):(x))
#define	BIT2WORD(x)			(((x)+15)/16)
#define	BIT2DWORD(x)		(((x)+31)/32)
#define	BYTE2WORD(x)		(((x)+1)/2)
#define	BYTE2DWORD(x)		(((x)+3)/4)
#define	BYTE2QWORD(x)		(((x)+7)/8)
#define	ROUNDUPBIT2NIBBLE(x)	(4*(((x)+3)/4))
#define	ROUNDUPBIT2BYTE(x)	(8*(((x)+7)/8))
#define	ROUNDUPBIT2WORD(x)	(16*(((x)+15)/16))
#define	ROUNDUPBIT2DWORD(x)	(32*(((x)+31)/32))
#define	ROUNDUPBIT2QWORD(x)	(64*(((x)+63)/64))
#define	ROUNDUPBYTE2WORD(x)	(2*(((x)+1)/2))
#define	ROUNDUPWORD2DWORD(x)	(2*(((x)+1)/2))
#define	ROUNDUPBYTE2DWORD(x)	(4*(((x)+3)/4))
#define	ROUNDUPBYTE2QWORD(x)	(8*(((x)+7)/8))


//////////////////////////////////////////////////////////////////////////////////
// Scoped Enum

#if (_MSC_VER < 1700)  && (__cplusplus < 201103L) // c++11 not supported
#define BEGIN_SCOPED_TYPED_ENUM(EnumName, EnumType)\
struct EnumName\
{\
	public:\
		enum E_EnumName : EnumType

#define BEGIN_SCOPED_ENUM(EnumName) BEGIN_SCOPED_TYPED_ENUM(EnumName, int)

#define END_SCOPED_TYPED_ENUM(EnumName, EnumType)\
	EnumName() {}\
	EnumName(E_EnumName value) { m_value = value; }\
	EnumName(EnumType value) { m_value = (E_EnumName)value; }\
	operator E_EnumName() const { return m_value; }\
	\
private:\
	 E_EnumName m_value;\
};

#define END_SCOPED_ENUM(EnumName) END_SCOPED_TYPED_ENUM(EnumName, int)
#else
#define BEGIN_SCOPED_TYPED_ENUM(EnumName, EnumType) enum class EnumName : EnumType
#define BEGIN_SCOPED_ENUM(EnumName) BEGIN_SCOPED_TYPED_ENUM(EnumName, int)
#define END_SCOPED_TYPED_ENUM(EnumName, EnumType)
#define END_SCOPED_ENUM(EnumName) END_SCOPED_TYPED_ENUM(EnumName, int)
#endif

#define DEFINE_ENUM_OPERATORS(EnumName, EnumType)\
inline EnumName operator~(const EnumName &rhs) {return static_cast<EnumName>(~static_cast<EnumType>(rhs));};\
inline EnumName operator&(const EnumName &lhs, const EnumName &rhs) { return static_cast<EnumName>(static_cast<EnumType>(lhs) & static_cast<EnumType>(rhs)); };\
inline EnumName operator|(const EnumName &lhs, const EnumName &rhs) { return static_cast<EnumName>(static_cast<EnumType>(lhs) | static_cast<EnumType>(rhs)); };\
inline EnumName operator^(const EnumName &lhs, const EnumName &rhs) { return static_cast<EnumName>(static_cast<EnumType>(lhs) ^ static_cast<EnumType>(rhs)); };\
inline EnumName& operator &=(EnumName &lhs, const EnumName &rhs) { return (EnumName&)(((EnumType&)lhs) &= static_cast<EnumType>(rhs)); };\
inline EnumName& operator |=(EnumName &lhs, const EnumName &rhs) { return (EnumName&)(((EnumType&)lhs) |= static_cast<EnumType>(rhs)); };\
inline EnumName& operator ^=(EnumName &lhs, const EnumName &rhs) { return (EnumName&)(((EnumType&)lhs) ^= static_cast<EnumType>(rhs)); };\
inline EnumType operator<<(const EnumName &lhs, const EnumType &rhs) { return static_cast<EnumType>(lhs) << rhs; };\
inline EnumType operator>>(const EnumName &lhs, const EnumType &rhs) { return static_cast<EnumType>(lhs) >> rhs; };

#ifndef CONSTEXPR
#if _MSC_VER >= 1800 || defined(__cpp_constexpr)
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif
#endif // !CONSTEXPR

#ifdef UNICODE
#ifndef CT2A8
#define CT2A8(x) CT2A(x, CP_UTF8)
#endif
#ifndef CA2T8
#define CA2T8(x) CA2T(x, CP_UTF8)
#endif
#else
#ifndef CT2A8
#define CT2A8(x)		x
#endif
#ifndef CA2T8
#define CA2T8(x)		x
#endif
#endif

