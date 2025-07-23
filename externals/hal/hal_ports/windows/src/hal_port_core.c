/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_core.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CORE module port for Windows
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/
#include "hal_port_core.h"

#if defined HAL_PORT_CORE_USE_SEMAPHORES_FOR_CRITICAL_SECTION && (HAL_PORT_CORE_USE_SEMAPHORES_FOR_CRITICAL_SECTION == 1)
HANDLE CriticalSection;
#else
CRITICAL_SECTION CriticalSection;
#endif

