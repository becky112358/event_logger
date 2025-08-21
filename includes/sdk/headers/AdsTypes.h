///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// OLE data types
#if IS_R0
enum VARENUM
    {	VT_EMPTY	= 0,
	VT_NULL	= 1,
	VT_I2	= 2,
	VT_I4	= 3,
	VT_R4	= 4,
	VT_R8	= 5,
	VT_CY	= 6,
	VT_DATE	= 7,
	VT_BSTR	= 8,
	VT_DISPATCH	= 9,
	VT_ERROR	= 10,
	VT_BOOL	= 11,
	VT_VARIANT	= 12,
	VT_UNKNOWN	= 13,
	VT_DECIMAL	= 14,
	VT_I1	= 16,
	VT_UI1	= 17,
	VT_UI2	= 18,
	VT_UI4	= 19,
	VT_I8	= 20,
	VT_UI8	= 21,
	VT_INT	= 22,
	VT_UINT	= 23,
	VT_VOID	= 24,
	VT_HRESULT	= 25,
	VT_PTR	= 26,
	VT_SAFEARRAY	= 27,
	VT_CARRAY	= 28,
	VT_USERDEFINED	= 29,
	VT_LPSTR	= 30,
	VT_LPWSTR	= 31,
	VT_FILETIME	= 64,
	VT_BLOB	= 65,
	VT_STREAM	= 66,
	VT_STORAGE	= 67,
	VT_STREAMED_OBJECT	= 68,
	VT_STORED_OBJECT	= 69,
	VT_BLOB_OBJECT	= 70,
	VT_CF	= 71,
	VT_CLSID	= 72,
	VT_VECTOR	= 0x1000,
	VT_ARRAY	= 0x2000,
	VT_BYREF	= 0x4000,
	VT_RESERVED	= 0x8000,
	VT_ILLEGAL	= 0xffff,
	VT_ILLEGALMASKED	= 0xfff,
	VT_TYPEMASK	= 0xfff
    };
#endif // #ifdef IS_R0

////////////////////////////////////////////////////////////////////////////////
// ADS data types
typedef char					ADS_INT8;
typedef unsigned char		ADS_UINT8;
typedef short					ADS_INT16;
typedef unsigned short		ADS_UINT16;
#ifndef POSIX
typedef long					ADS_INT32;
typedef unsigned long		ADS_UINT32;
#else
typedef LONG					ADS_INT32;
typedef ULONG					ADS_UINT32;
#endif
typedef __int64				ADS_INT64;
typedef unsigned __int64	ADS_UINT64;
typedef float					ADS_REAL32;
typedef double					ADS_REAL64;
typedef long double			ADS_REAL80;

typedef enum AdsDataTypeId
{
	ADST_VOID		= VT_EMPTY,
	ADST_INT8		= VT_I1,
	ADST_UINT8		= VT_UI1,
	ADST_INT16		= VT_I2,
	ADST_UINT16		= VT_UI2,
	ADST_INT32		= VT_I4,
	ADST_UINT32		= VT_UI4,
	ADST_INT64		= VT_I8,
	ADST_UINT64		= VT_UI8,
	ADST_REAL32		= VT_R4,
	ADST_REAL64		= VT_R8,
	ADST_STRING		= VT_LPSTR,
	ADST_WSTRING	= VT_LPWSTR,
	ADST_REAL80		= VT_LPWSTR+1,
	ADST_BIT			= VT_LPWSTR+2,
	ADST_BIGTYPE	= VT_BLOB,
	ADST_MAXTYPES	= VT_STORAGE,
} ADS_DATATYPE;

typedef union
{
	double			dVal;
	float				fVal;
	LONG				lVal;
	ULONG				ulVal;
	char				cVal;
	unsigned char	ucVal;
	short				iVal;
	unsigned short	uiVal;
	__int64			i64Val;
} ADST_VALUE, *PADST_VALUE;

const int ADST_TYPESIZE[]=
{
	0,					// VT_EMPTY	= 0,
	0,					//	VT_NULL	= 1,
	sizeof(short),	//	VT_I2	= 2,
	sizeof(LONG),	//	VT_I4	= 3,
	sizeof(float),	//	VT_R4	= 4,
	sizeof(double),//	VT_R8	= 5,
	-1,				//	VT_CY	= 6,
	sizeof(double),//	VT_DATE	= 7,
	sizeof(short),	//	VT_BSTR	= 8,
	sizeof(PVOID),	//	VT_DISPATCH	= 9,
	sizeof(HRESULT),//VT_ERROR	= 10,
	sizeof(short),	//	VT_BOOL	= 11,
	sizeof(VARIANT),//VT_VARIANT	= 12,
	sizeof(PVOID),	//	VT_UNKNOWN	= 13,
	sizeof(PVOID),	//	VT_DECIMAL	= 14,
	-1,				//	not defined = 15,
	sizeof(char),	//	VT_I1	= 16,
	sizeof(char),	//	VT_UI1	= 17,
	sizeof(short),	//	VT_UI2	= 18,
	sizeof(LONG),	//	VT_UI4	= 19,
	sizeof(__int64),//VT_I8	= 20,
	sizeof(__int64),//VT_UI8	= 21,
	sizeof(int),	//	VT_INT	= 22,
	sizeof(int),	//	VT_UINT	= 23,
	0,					//	VT_VOID	= 24,
	sizeof(HRESULT),//VT_HRESULT	= 25,
	sizeof(PVOID),	//	VT_PTR	= 26,
	-1,				//	VT_SAFEARRAY	= 27,
	-1,				//	VT_CARRAY	= 28,
	-1,				//	VT_USERDEFINED	= 29,
	sizeof(char),	//	VT_LPSTR	= 30,
	sizeof(short),	//	VT_LPWSTR	= 31,
	-1,				// ADST_REAL80	= 32,
	sizeof(BYTE),	//	ADST_BIT		= 33
	-1,				//	not defined = 34,
	-1,				//	not defined = 35,
	-1,				//	not defined = 36,
	-1,				//	not defined = 37,
	-1,				//	not defined = 38,
	-1,				//	not defined = 39,
	-1,				//	not defined = 40,
	-1,				//	not defined = 41,
	-1,				//	not defined = 42,
	-1,				//	not defined = 43,
	-1,				//	not defined = 44,
	-1,				//	not defined = 45,
	-1,				//	not defined = 46,
	-1,				//	not defined = 47,
	-1,				//	not defined = 48,
	-1,				//	not defined = 49,
	-1,				//	not defined = 50,
	-1,				//	not defined = 51,
	-1,				//	not defined = 52,
	-1,				//	not defined = 53,
	-1,				//	not defined = 54,
	-1,				//	not defined = 55,
	-1,				//	not defined = 56,
	-1,				//	not defined = 57,
	-1,				//	not defined = 58,
	-1,				//	not defined = 59,
	-1,				//	not defined = 60,
	-1,				//	not defined = 61,
	-1,				//	not defined = 62,
	-1,				//	not defined = 63,
	sizeof(__int64),//VT_FILETIME	= 64,
	-1,				//	VT_BLOB		= 65,
	sizeof(PVOID),	//	VT_STREAM	= 66,
	sizeof(PVOID)	//	VT_STORAGE	= 67,
};
