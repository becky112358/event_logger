///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef TCFRAMEWORK_TESTS
#include "RtlR0Test.h"
namespace RtlR0
{
#else
#include "TcDef.h"
#ifdef __cplusplus
extern "C" {
#endif
#endif

#if defined(_MSC_VER) && !defined(inline) && !defined(__cplusplus) 
#define inline __inline
#endif

#define _NOFLG_   0x00000000
#define _BLANK_   0x00000001
#define _CNTRL_   0x00000002
#define _DIGIT_   0x00000004
#define _GRAPH_   0x00000008
#define _LOWER_   0x00000010
#define _PRINT_   0x00000020
#define _PUNCT_   0x00000040
#define _SPACE_   0x00000080
#define _UPPER_   0x00000100
#define _XDIGIT_  0x00000200
#define _ALPHA_ (_UPPER_|_LOWER_)
#define _ALNUM_ (_ALPHA_|_DIGIT_)

DLL_EXPORT int _cdecl _CheckCharFlag(int c, unsigned int f);

inline int _cdecl isalnum(int c)  { return _CheckCharFlag(c, _ALNUM_); }
inline int _cdecl isalpha(int c)  { return _CheckCharFlag(c, _ALPHA_); }
inline int _cdecl isblank(int c)  { return _CheckCharFlag(c, _BLANK_); }
inline int _cdecl iscntrl(int c)  { return _CheckCharFlag(c, _CNTRL_); }
inline int _cdecl isdigit(int c)  { return _CheckCharFlag(c, _DIGIT_); }
inline int _cdecl isgraph(int c)  { return _CheckCharFlag(c, _GRAPH_); }
inline int _cdecl islower(int c)  { return _CheckCharFlag(c, _LOWER_); }
inline int _cdecl isprint(int c)  { return _CheckCharFlag(c, _PRINT_); }
inline int _cdecl ispunct(int c)  { return _CheckCharFlag(c, _PUNCT_); }
inline int _cdecl isspace(int c)  { return _CheckCharFlag(c, _SPACE_); }
inline int _cdecl isupper(int c)  { return _CheckCharFlag(c, _UPPER_); }
inline int _cdecl isxdigit(int c) { return _CheckCharFlag(c, _XDIGIT_); }
inline int _cdecl tolower(int c)  { return isupper(c) ? (c)+('a'-'A') : (c); }
inline int _cdecl toupper(int c)  { return islower(c) ? (c)-('a'-'A') : (c); }

#pragma push_macro("__isascii")
#if defined(__isascii)
#undef __isascii
#endif
inline int _cdecl __isascii(int c) { return (unsigned)c < 0x80; }
#pragma pop_macro("__isascii")

#pragma push_macro("__toascii")
#if defined(__toascii)
#undef __toascii
#endif
inline int _cdecl __toascii(int c) { return c & 0x7f; }
#pragma pop_macro("__toascii")

#ifdef TCFRAMEWORK_TESTS
}
#else
#ifdef __cplusplus
}
#endif
#endif
