///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcDef.h" // set TC_ENVIRONMENT_*, etc.

#include "TcMath/math_config.h"


#define TCMATH_API _cdecl

// use C++ name mangling 
#if 0
#ifdef __cplusplus
#define TCMATH_EXTERN_BEGIN extern "C" {
#define TCMATH_EXTERN_END }
#endif
#else
#define TCMATH_EXTERN_BEGIN
#define TCMATH_EXTERN_END
#endif

// set this to 1 to replace the Windows CE standard math library with 
// the identical function set as available for x64
#if (defined(TC_ENVIRONMENT_CE) ) && (! defined(TCMATH_REPLACE_WCELIB))
#define TCMATH_REPLACE_WCELIB 0
#endif

#if defined(TC_ENVIRONMENT_CE_RT) || defined(TC_ENVIRONMENT_OS)
#define TCMATH_REPLACE_WCELIB 1
#endif

#include "TcMath/fpu_statuscontrol.h"
#include "TcMath/math_constants.h"

#ifdef __cplusplus

#if !defined(TCMATH_USE_STANDARDLIB)
#if defined(TC_ENVIRONMENT_RT) || defined(TC_ENVIRONMENT_CE_RT) || defined(TC_ENVIRONMENT_OS)
// use TwinCAT's real-time enabled replacement of the math standard library
#define TCMATH_USE_STANDARDLIB 0
#else
/* this uses the standard math library, which is the current default 
   for User Mode TwinCAT, WIN32 Apps and Windows CE */
#define TCMATH_USE_STANDARDLIB 1
#endif
#endif

#if TCMATH_USE_STANDARDLIB
// use windows standard library math functions
#include "TcMath/mathfuncs_standardlib.h"

#else // we want to use our own math lib (e.g. cephes)
#if !defined(TCFRAMEWORK_TESTS) && (defined(_INC_MATH_) || defined(_INC_MATH))
#pragma message(__LOC__"*******************************************************************************************************************")
#pragma message(__LOC__"* Warning: math.h included but should probably not because TwinCAT MathAPI is enabled. This is probably an error. *")
#pragma message(__LOC__"*******************************************************************************************************************")
#endif

#include "TcMath/mathfuncs_common.h"

#if TCMATH_REPLACE_WCELIB

/* this provides a comprehensive implementation for ARM CPUs which 
   is independent from the Windows CE standard library.
*/

#if defined(_ARM_)
/* this can branch to machine-specific code later. */
#include "TcMath/mathfuncs_generic.h"
#else
#include "TcMath/mathfuncs_generic.h"
#endif

#elif TCMATH_REPLACE_FPU87 

#include "TcMath/mathfuncs_sse.h"

#elif defined(_X86_)

// use inline assembly, calling fpu87 instructions 
#include "TcMath/mathfuncs_x86_fpu.h"

#elif defined(_X64_)

#ifndef TCMATH_REPLACE_FPU87_NOWARN
#pragma message(__LOC__"*******************************************************************************************************************")
#pragma message(__LOC__"* Warning: use of FPU on x64 platform is not recommended.")
#pragma message(__LOC__"*******************************************************************************************************************")
#endif

// use assembly source files, calling either fpu87 instructions, SSE2 instructions, or C routines
#include "TcMath/mathfuncs_x64_fpu.h"

#endif // defined(_X64_)
#endif 

// additional nonstandard math functions
#include "TcMath/mathfuncs_composite_extra.h"
 
#else
#include "TcMath/mathfuncs_cwrapper.h"
#endif

#if TCMATH_BLOCK_STANDARDLIB
// prevent use of C standard library math functions 
#include "TcMath/mathfuncs_block_standardlib.h"
#endif

#if TCMATH_REDIRECT_STANDARDLIB
// allow use of C standard library math functions
#include "TcMath/mathfuncs_define_standardlib.h"
#endif
