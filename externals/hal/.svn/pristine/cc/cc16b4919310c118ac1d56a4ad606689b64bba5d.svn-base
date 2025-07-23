/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_core.h
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


#ifndef HAL_PORT_CORE_H
#define HAL_PORT_CORE_H

// _WIN32_WINNT must be defined as 0x0403 or later to use InitializeCriticalSectionAndSpinCount
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0403 
//#endif 

#include <windows.h>
#include "hal_config.h"

#if defined HAL_PORT_CORE_USE_SEMAPHORES_FOR_CRITICAL_SECTION && (HAL_PORT_CORE_USE_SEMAPHORES_FOR_CRITICAL_SECTION == 1)

extern HANDLE CriticalSection;

#define CORE_PORT_EnterCritical()		do { WaitForSingleObject(CriticalSection, 65530); } while (0)
#define CORE_PORT_ExitCritical()		do { ReleaseSemaphore(CriticalSection, 1, NULL); } while (0)
#define CORE_PORT_Init()				do { CriticalSection = CreateSemaphore(NULL, 1, 1, NULL); } while (0)
#define CORE_PORT_Deinit()				do { CloseHandle(CriticalSection); } while (0)
#define CORE_PORT_EnableInterrupts()
#define CORE_PORT_DisableInterrupts()
#else

extern CRITICAL_SECTION CriticalSection;

#define CORE_PORT_EnterCritical()		do { EnterCriticalSection(&CriticalSection); } while (0)
#define CORE_PORT_ExitCritical()		do { LeaveCriticalSection(&CriticalSection); } while (0)
#define CORE_PORT_Init()				do { InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400); } while (0)
#define CORE_PORT_Deinit()				do { DeleteCriticalSection(&CriticalSection); } while (0)
#define CORE_PORT_EnableInterrupts()
#define CORE_PORT_DisableInterrupts()

#endif


#define CORE_PORT_GetSystemTime()		GetTickCount()

#endif /* HAL_PORT_CORE_H */
