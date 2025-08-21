///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h"
#include "TcDbgR0.h"

RTLR0_NAMESPACE_BEGIN
//dummy to make sure namespace exists
RTLR0_NAMESPACE_END

#pragma warning(disable:4035)               // re-enable below
#if defined(IS_R0) || defined(TC_ENVIRONMENT_OS)		// on R3 the standard library functions should be used



#if !defined(TC_ENVIRONMENT_OS)
#include <stddef.h>
#endif
#include <stdarg.h>

#define safe_delete(p)		{if (p) delete (p); p = NULL;}
#define safe_delete_a(p)	{if (p) delete [] (p); p = NULL;}

#ifdef USE_CRT_OWN_IMPL
#include "ctypeR0.h"
#endif

RTLR0_NAMESPACE_BEGIN
	char *  __cdecl strcat(char *, const char *);
	int     __cdecl strcmp(const char *, const char *);
	char *  __cdecl strcpy(char *, const char *);
	size_t  __cdecl strlen(const char *);
	size_t __cdecl strnlen(const char* str, size_t count);

	wchar_t* __cdecl wcscat(wchar_t*, const wchar_t*);
	int      __cdecl wcscmp(const wchar_t*, const wchar_t*);
	wchar_t* __cdecl wcscpy(wchar_t*, const wchar_t*);
	size_t   __cdecl wcslen(const wchar_t*);

	int     __cdecl memcmp(const void *, const void *, size_t);
	void *  __cdecl memmove(void *, const void *, size_t);
	void *  __cdecl memset(void *, int, size_t);
	void *  __cdecl memcpy(void *, const void *, size_t);
RTLR0_NAMESPACE_END

#ifdef __cplusplus
namespace std
{
	using RTLR0_NAMESPACE::memcmp;
	using RTLR0_NAMESPACE::memmove;
	using RTLR0_NAMESPACE::memcpy;
	using RTLR0_NAMESPACE::memset;
}
#endif


RTLR0_NAMESPACE_BEGIN
	int __cdecl _inp( unsigned short port );
	int __cdecl _outp( unsigned short port, int databyte );
	unsigned short __cdecl _inpw( unsigned short port );
	unsigned short __cdecl _outpw(unsigned short,unsigned short);
	unsigned long __cdecl _inpd( unsigned short port );
	unsigned long __cdecl _outpd( unsigned short port, int data );
	unsigned int __cdecl _rotr(unsigned int, int);
	unsigned int __cdecl _rotl(unsigned int, int);
	void * _ReturnAddress(void);
RTLR0_NAMESPACE_END

EXTERN_C int __cdecl abs(int n);
EXTERN_C long __cdecl labs( long n );
EXTERN_C long long __cdecl llabs(long long n);

#ifndef ARM
EXTERN_C long __cdecl _InterlockedIncrement(long volatile *);
#endif
EXTERN_C long __cdecl _InterlockedDecrement(long volatile *);

#if !defined(_ARM_)
EXTERN_C long __cdecl _InterlockedExchange(long volatile *, long);
#ifdef _X64_
EXTERN_C LONGLONG __cdecl _InterlockedExchange64(LONGLONG volatile *Target, LONGLONG          Value);
#endif
#endif

#if !defined(_ARM_)
EXTERN_C long __cdecl _InterlockedCompareExchange(long volatile *, long, long);
#ifdef _X64_
EXTERN_C LONGLONG __cdecl _InterlockedCompareExchange64(LONGLONG volatile *, LONGLONG, LONGLONG);
#endif
#endif

#if defined(_ARM_)
EXTERN_C long _InterlockedAdd(long volatile * Addend, long Value);
#elif defined(_X64_)
EXTERN_C long __cdecl _InterlockedExchangeAdd(LONG volatile *Addend, LONG Increment);
#endif

EXTERN_C LONG _InterlockedOr(LONG volatile *Destination, LONG Value);
EXTERN_C LONG _InterlockedAnd(LONG volatile *Destination, LONG Value);


#define	_stprintf	sprintf
#define	_stnprintf	snprintf
#define	_tcscat		strcat
#define	_tcscpy		strcpy
#define	_tcsncat		strncat
#define	_tcsncpy		strncpy
#define	_tcslen		strlen
#define	_tcscmp		strcmp
#define	_tcsstr		strstr
#define	_tcschr		strchr
#define	_tcsrchr		strrchr
#define	_tcsncmp		strncmp
#define	_stscanf		sscanf


#ifndef TC_FRAMEWORK_SLIM
#pragma intrinsic(memcmp)
#pragma intrinsic(memcpy)
#pragma intrinsic(memset)
#pragma intrinsic(strcat)
#pragma intrinsic(strcmp)
#pragma intrinsic(strcpy)
#pragma intrinsic(wcscat)
#pragma intrinsic(wcscmp)
#pragma intrinsic(wcscpy)
#pragma intrinsic(wcslen)
#if !defined(_ARM_)
#pragma intrinsic(_inp)
#pragma intrinsic(_outp)
#pragma intrinsic(_inpd)
#pragma intrinsic(_outpd)
#pragma intrinsic(_inpw)
#pragma intrinsic(_outpw)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(llabs)
#endif
#pragma intrinsic(abs)
#pragma intrinsic(labs)
#if !defined(_ARM_)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedAnd)
#endif
#if defined(_ARM_)
#pragma intrinsic(_InterlockedAdd)
#elif defined(_X64_)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedCompareExchange64)
#endif

#pragma intrinsic(_rotr)
#pragma intrinsic(_rotl)
#pragma intrinsic(_ReturnAddress)
#endif

// these C++ wrappers must be placed after the pragma intrinsic, otherwise linker errors can occur
#ifdef __cplusplus
extern "C++"
{
	inline long abs(long n)
	{
		return labs(n);
	}

	inline long long abs(long long n)
	{
		return llabs(n);
	}
}
#endif

RTLR0_NAMESPACE_BEGIN

#ifdef USE_CRT_OWN_IMPL

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif

#if !defined(_SECURECRT_ERRCODE_VALUES_DEFINED)
#define _SECURECRT_ERRCODE_VALUES_DEFINED
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80
#endif

errno_t _cdecl strcpy_s(char* dest, size_t numberOfElements, const char* source);
char*  __cdecl strncpy(char* dest, const char* source, size_t count);
errno_t _cdecl strncpy_s(char * dest, size_t numberOfElements, const char* source, size_t count);
size_t __cdecl strnlen(const char* str, size_t count);
size_t __cdecl strnlen_s(const char* str, size_t count);
char*  __cdecl strncat(char* front, const char* back, size_t count);
int    __cdecl strncmp(const char* str1, const char* str2, size_t count);
int    __cdecl _stricmp(const char*, const char*);
int    __cdecl _strnicmp(const char* str1, const char* str2, size_t count);
char*  __cdecl strstr( const char* str1, const char* str2);
char*  __cdecl strchr( const char* s, int c);
char*  __cdecl strrchr(const char *str, int c);
size_t __cdecl strcspn(const char *str, const char *strCharSet);
char*  __cdecl strtok_s(char* str, const char *delim, char** ptr);
char*  __cdecl strupr(char* s);
char*  __cdecl _strupr(char* s);
char*  __cdecl _strlwr(char* s);

wchar_t* __cdecl wcsncpy(wchar_t* dest, const wchar_t* source, size_t count);
size_t   __cdecl wcsnlen(const wchar_t* str, size_t count);
wchar_t* __cdecl wcsncat(wchar_t* front, const wchar_t* back, size_t count);
int      __cdecl wcsncmp( const wchar_t *str1, const wchar_t * str2, size_t count);
wchar_t* __cdecl wcsstr(const wchar_t* str1, const wchar_t* str2);
_CONST_RETURN wchar_t* __cdecl wcschr(const wchar_t* string, wchar_t ch);
_CONST_RETURN wchar_t* __cdecl wcsrchr(const wchar_t* string, wchar_t ch);
size_t   __cdecl wcscspn(const wchar_t* str, const wchar_t* strCharSet);
wchar_t* __cdecl wstrtok_s(wchar_t* str, const wchar_t *delim, wchar_t** ptr);
wchar_t* __cdecl _wcsupr(wchar_t* s);
wchar_t* __cdecl _wcslwr(wchar_t* s);

void* __cdecl memmove(void *dest, const void *src, size_t count);
void  __cdecl qsort (void *base, size_t num, size_t width, int (__cdecl *comp)(const void *, const void *));
void  __cdecl qsort_s (void *base, size_t num, size_t width, int (__cdecl *comp)(void *, const void *, const void *), void *ctx);
#else
#include <search.h>
#endif
int __cdecl sprintf(char *buffer, const char *format, ...);
long __cdecl strtol(const char* s, char** pend, int radix);
long long __cdecl strtoll(const char* s, char** pend, int radix);
unsigned long __cdecl strtoul(const char* s, char** pend, int radix);
unsigned long long __cdecl strtoull(const char* s, char** pend, int radix);
double __cdecl strtod(const char* s, char** endptr);

double __cdecl atof(const char *buf);
long __cdecl atol(const char *buf);
int __cdecl atoi(const char *buf);

int __cdecl sscanf(const char* buf, const char* fmt, ...);
int __cdecl snprintf(char *buffer, size_t count, const char *format, ...);
int __cdecl vsnprintf(char *buffer, size_t Limit, const char *format, va_list Next);
int __cdecl vsprintf(char *buffer, const char *format, va_list Next);

int __cdecl _snwprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, ...);
int __cdecl _snprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, ...);

int __cdecl _vsnwprintf_sR0(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, va_list Next);
int __cdecl _vsnwprintfR0(wchar_t *buffer, size_t Limit, const wchar_t *format, va_list Next);
int __cdecl _vsnprintf_sR0(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list Next);

int __cdecl swscanf(const wchar_t* buf, const wchar_t* fmt, ...);

RTLR0_NAMESPACE_END

// inlined functions follow


__inline unsigned long InterlockedIncrementR0( unsigned long* lpAddend )  // pointer to the variable to increment
{
	return (unsigned long) _InterlockedIncrement((long *)lpAddend);
#if 0
	__asm 
	{
		mov     eax, 1
		mov     ecx, lpAddend
		lock xadd    [ecx], eax
		inc     eax
	}
#endif
}

__inline unsigned long InterlockedDecrementR0( unsigned long* lpAddend )  // pointer to the variable to decrement
{
	return (unsigned long) _InterlockedDecrement((long *)lpAddend);
#if 0
	__asm 
	{
		mov     eax, -1
		mov     ecx, lpAddend
		lock xadd    [ecx], eax
		dec     eax
	}
#endif
}

__inline unsigned long InterlockedExchangeR0(unsigned long* pDest, unsigned long nValue)
{
	return (unsigned long) _InterlockedExchange((long*)pDest, (long)nValue);
#if 0
	__asm
	{
		mov	eax, nValue
		mov	ecx, pDest
		xchg	[ecx], eax
	}
#endif
}

__inline unsigned long InterlockedCompareExchangeR0(unsigned long* pDest, unsigned long nValue, unsigned long nComparand)
{
	return (unsigned long) _InterlockedCompareExchange((long*)pDest, (long)nValue, (long)nComparand);
}

__inline LONG_PTR InterlockedExchangePtrR0(LONG_PTR* pDest, LONG_PTR nValue)
{
#ifdef  _X64_
	return (LONG_PTR) _InterlockedExchange64(pDest, nValue);
#else
	return (LONG_PTR) _InterlockedExchange(pDest, nValue);
#endif
}

__inline LONG_PTR InterlockedCompareExchangePtrR0(LONG_PTR* pDest, LONG_PTR nValue, LONG_PTR nComparand)
{
#ifdef  _X64_
	return (LONG_PTR) _InterlockedCompareExchange64(pDest, nValue, nComparand);
#else
	return (LONG_PTR) _InterlockedCompareExchange(pDest, nValue, nComparand);
#endif
}

__inline unsigned char InterlockedExchangeByteR0(unsigned char* pDest, unsigned char nValue)
{
#if defined(_X64_) || defined(_ARM_)
	return (unsigned char) _InterlockedExchange((long*)pDest, (long)nValue);
#else
	__asm
	{
		mov	al, nValue
		mov	ecx, pDest
		xchg	[ecx], al
	}
#endif
}

__inline unsigned long InterlockedAddR0( unsigned long* lpAddend, long addVal )  
{
#if defined(_ARM_)
	return (unsigned long) _InterlockedAdd((long*)lpAddend, (long)addVal);
#elif defined(_X64_)
	return _InterlockedExchangeAdd((long*)lpAddend, addVal) + addVal;
#else
	__asm 
	{
		mov     eax, addVal
		mov     ecx, lpAddend
		lock xadd    [ecx], eax
		add     eax, addVal
	}
#endif
}


__inline unsigned long InterlockedOrR0(unsigned long* pDest, unsigned long nValue)
{
	return (unsigned long) _InterlockedOr((long*)pDest, (long)nValue);
}

__inline unsigned long InterlockedAndR0(unsigned long* pDest, unsigned long nValue)
{
	return (unsigned long) _InterlockedAnd((long*)pDest, (long)nValue);
}

#elif defined(TC_ENVIRONMENT_CE_RT)

#include "RtlR0CeRt.h"
#include "ctypeR0.h"

#elif defined(WIN32_RUNTIME)
/* these must not appear in the global namespace if we build a minimal library */
#if defined(__cplusplus) && !defined(TC_FRAMEWORK_SLIM)
extern "C" {
#endif
#ifndef ARM
#if _MSC_VER >= 1700
	long _InterlockedOr(long volatile *, long);
	long _InterlockedAnd(long volatile *, long);
#else
	long __cdecl _InterlockedOr(long volatile *, long);
	long __cdecl _InterlockedAnd(long volatile *, long);
#endif
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedAnd)
#endif

#ifndef ARM
	unsigned short __cdecl _inpw(unsigned short port);
	unsigned short __cdecl _outpw(unsigned short, unsigned short);
	unsigned long __cdecl _outpd(unsigned short, unsigned long);
#pragma intrinsic(_inpw)
#pragma intrinsic(_outpw)
#pragma intrinsic(_outpd)
#endif
	/* these must not appear in the global namespace if we build a minimal library */
#if defined(__cplusplus) && !defined(TC_FRAMEWORK_SLIM)
}
#endif

__inline unsigned long InterlockedIncrementR0( unsigned long* lpAddend )
{
	return InterlockedIncrement((long*)lpAddend);
}

__inline unsigned long InterlockedDecrementR0( unsigned long* lpAddend )
{
	return InterlockedDecrement((long*)lpAddend);
}

__inline unsigned long InterlockedExchangeR0(unsigned long* pDest, unsigned long nValue)
{
	return InterlockedExchange((long*)pDest, (long)nValue);
}

__inline unsigned long InterlockedCompareExchangeR0(unsigned long* pDest, unsigned long nValue, unsigned long nComparand)
{
	return InterlockedCompareExchange((long*)pDest, (long)nValue, (long)nComparand);
}

__inline LONG_PTR InterlockedExchangePtrR0(LONG_PTR* pDest, LONG_PTR nValue)
{
	return (LONG_PTR)InterlockedExchangePointer((void**)pDest, (void*)nValue);
}

__inline LONG_PTR InterlockedCompareExchangePtrR0(LONG_PTR* pDest, LONG_PTR nValue, LONG_PTR nComparand)
{
	return (LONG_PTR)InterlockedCompareExchangePointer((void**)pDest, (void*)nValue, (void*)nComparand);
}

#ifdef _X86_
	__inline unsigned char InterlockedExchangeByteR0(unsigned char* pDest, unsigned char nValue)
	{
		__asm
		{
			mov	al, nValue
			mov	ecx, pDest
			xchg	[ecx], al
		}
	}
#else
	#define InterlockedExchangeByteR0(x, y)	{ ##pragma message ("InterlockedExchangeByteR0 not implemented yet") }
#endif

#ifdef ARM
#include "ArmHelper.h"
__inline unsigned long InterlockedOrR0(unsigned long* pDest, unsigned long nValue)
{
	unsigned long oldValue;
	unsigned long newValue;
	do 
	{
		oldValue = *pDest;
		newValue = oldValue | nValue; 
	} while (InterlockedCompareExchange((long*)pDest, newValue, oldValue) != oldValue);
	return oldValue;
}

__inline unsigned long InterlockedAndR0(unsigned long* pDest, unsigned long nValue)
{
	unsigned long oldValue;
	unsigned long newValue;
	do 
	{
		oldValue = *pDest;
		newValue = oldValue & nValue; 
	} while (InterlockedCompareExchange((long*)pDest, newValue, oldValue) != oldValue);
	return oldValue;
}
#else
#define InterlockedOrR0(x, y)	_InterlockedOr((long*)x, (long)y)
#define InterlockedAndR0(x, y) _InterlockedAnd((long*)x, (long)y)
#endif

#endif		// #ifdef IS_R0


/* these must not appear in the global namespace if we build a minimal library */
#if defined(__cplusplus) && !defined(TC_FRAMEWORK_SLIM)
extern "C" {
#endif

// NOTE: dst and src Address must be word aligned for CX9000 DPRAM.
__inline void *	__cdecl memcpy_word_swap(void *dst, const void *src, size_t len)	
{
	size_t i;
	for( i = 0; i<(len>>1); i++ )	
		((WORD*)dst)[i] = (WORD)(((((WORD*)src)[i])<< 8) | ((((WORD*)src)[i])>>8));	
	ASSERT( (len&0x1)==0);
	return dst;
}

//NOTE: only word aligned access to dst is allowed (dst is CX9000 DPRAM)
#pragma optimize( "", off )
__inline void *	__cdecl memcpy_word_swap_dst_aligned(void *dst, const void *src, size_t len)	
{	
	size_t i, alignedLen;
	BYTE* pDst=(BYTE*)dst;
	BYTE*	pSrc=(BYTE*)src;
	
	if ((DWORD_PTR)pDst&0x1)		
	{//copy start byte at odd address		
		*((WORD*)(pDst-1)) = ((*((WORD*)(pDst-1)))&0xFF00)|(WORD)pSrc[0];	 
		if (--len==0)
			return dst;
		pDst++;
		pSrc++;		
	}	
	alignedLen = len&(~0x1);
	//copy aligned words	
	for ( i=0; i<alignedLen; i+=2)	
	{
		((WORD*)pDst)[i>>1] = ((WORD)pSrc[i]<<8)|((WORD)pSrc[i+1]);	
	}
	
	if (alignedLen!=len)
		//copy end byte at aligned address
		*((WORD*)&pDst[alignedLen]) = (*((WORD*)&pDst[alignedLen])&0x00FF)|(((WORD)pSrc[alignedLen])<<8);
	
	return dst;
}
			
//NOTE: only word aligned access to src is allowed (src is CX9000 DPRAM)
__inline void *	__cdecl memcpy_word_swap_src_aligned(void *dst, const void *src, size_t len)	
{
	size_t i,alignedLen;
	BYTE* pDst=(BYTE*)dst;
	BYTE*	pSrc=(BYTE*)src;
	
	if ((DWORD_PTR)pSrc&0x1)		
	{//copy start byte at odd address
		pDst[0] = (BYTE)*((WORD*)(pSrc-1));

		if (--len==0)
			return dst;
		pDst++;
		pSrc++;		
	}	
	alignedLen = len&(~0x1);
	//copy aligned words
	for ( i=0; i<(alignedLen>>1); i++)	
	{
		pDst[(i<<1)]	= (((WORD*)pSrc)[i])>>8;
		pDst[(i<<1)+1]	= (BYTE)(((WORD*)pSrc)[i]);		
	}
	
	if (alignedLen!=len)
		//copy end byte at aligned address
		pDst[alignedLen] = (*(WORD*)&pSrc[alignedLen])>>8;
	return dst;
}
#pragma optimize( "", on )	


#ifdef _X86_
__inline void *	__cdecl memcpy_word_opt(void *dst, const void *src, size_t len)
{
	_asm
	{
		mov	ecx, len				// len
		mov	esi, src				// src
			mov	edi, dst				// dst
			mov	eax, ecx				// save len
			mov	edx, edi				// save dst
			shr	ecx, 02
			repz	movsd					// copy all DWORDs
			mov	ecx, eax
			and	ecx, 02
			shr	ecx, 01
			repz	movsw					// copy a WORD if rest is >= 2 Byte
			mov	ecx, eax
			and	ecx, 01
			repz	movsb					// copy last byte if size % 2 == 1
			mov	eax, edx				// return dst
	}
}
#else
#define memcpy_word_opt memcpy
#endif

#ifdef __cplusplus
__inline void * __cdecl memcpy_byte(void *dst, const void *src, size_t len)
{
	for ( size_t i=0; i<len; i++)
		((BYTE*)dst)[i] = ((BYTE*)src)[i];

	return dst;
}
#endif

#if	defined(IS_R0) || defined(UNDER_CE)	|| defined(TC_ENVIRONMENT_OS)
#if (_WIN32_WCE < 0x700)
DLL_EXPORT void*  __cdecl bsearch ( const void *key, const void *base, size_t num, size_t width,
											int (__cdecl *compare)(const void *, const void *));
DLL_EXPORT void*  __cdecl bsearch_s(const void *key, const void *base, size_t num, size_t width,
											int(__cdecl *compare)(void*, const void *, const void *), void* ctx);
#endif

#if defined (TC_ENVIRONMENT_OS) || defined (UNDER_CE)
EXTERN_C void DLL_EXPORT _tsplitpath(const TCHAR* pPath, TCHAR* pDrive, TCHAR* pDir, TCHAR* pFname, TCHAR* pExtension);
#endif


#ifdef UNDER_CE
//
// Define bit test intrinsics.
//

#define BitTest _bittest
#define BitTestAndComplement _bittestandcomplement
#define BitTestAndSet _bittestandset
#define BitTestAndReset _bittestandreset

unsigned char __cdecl _bittest (LONG const *Base, LONG Offset);
unsigned char __cdecl _bittestandcomplement (LONG *Base, LONG Offset);
unsigned char __cdecl _bittestandset (LONG *Base, LONG Offset);
unsigned char __cdecl _bittestandreset (LONG *Base,LONG Offset);

#pragma intrinsic(_bittest)
#pragma intrinsic(_bittestandcomplement)
#pragma intrinsic(_bittestandset)
#pragma intrinsic(_bittestandreset)

inline long long __cdecl strtoll(const char* s, char** pend, int radix)
{
#if	_WIN32_WCE < 0x700
	return strtol(s, pend, radix);
#else
	return _strtoi64(s, pend, radix);
#endif
}

inline unsigned long long __cdecl strtoull(const char* s, char** pend, int radix)
{
#if	_WIN32_WCE < 0x700
	return strtoul(s, pend, radix);
#else
	return _strtoui64(s, pend, radix);
#endif
}

#ifdef ARM
unsigned char DLL_EXPORT BitScanReverse( unsigned long * Index, unsigned long Mask );
unsigned char DLL_EXPORT BitScanForward( unsigned long * Index, unsigned long Mask );
#else
#define BitScanForward _BitScanForward
#define BitScanReverse _BitScanReverse
unsigned char BitScanReverse( unsigned long * Index, unsigned long Mask );
unsigned char BitScanForward( unsigned long * Index, unsigned long Mask );
#endif
#endif

#define safe_delete(p)		{if (p) delete (p); p = NULL;}
#define safe_delete_a(p)	{if (p) delete [] (p); p = NULL;}
#define safe_release(p)		{if (p) (p)->TcRelease(); p = NULL;}
#define safe_release_imgptr(i, p)	{if (p) (i)->ReleaseImagePtr(p); p = NULL;}

#elif defined(WIN32_RUNTIME)
#define safe_delete(p)		{if (p) delete (p); p = NULL;}
#define safe_delete_a(p)	{if (p) delete [] (p); p = NULL;}
#define safe_release(p)		{if (p) (p)->TcRelease(); p = NULL;}
#define safe_release_imgptr(i, p)	{if (p) (i)->ReleaseImagePtr(p); p = NULL;}
#endif

/* these must not appear in the global namespace if we build a minimal library */
#if defined(__cplusplus) && !defined(TC_FRAMEWORK_SLIM)
}
#endif


#pragma warning(default:4035)
