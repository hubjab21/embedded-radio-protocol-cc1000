/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			stdint.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       missing C99 type definitions
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef STDINT_H
#define STDINT_H

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

typedef signed int   intptr_t;
typedef unsigned int uintptr_t;

#endif // STDINT_H
