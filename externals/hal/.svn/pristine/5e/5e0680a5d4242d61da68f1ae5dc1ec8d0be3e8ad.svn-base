/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's OS port for WIN32 API
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for WIN32 API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <Windows.h>
#include <time.h>

#ifndef HAL_OS_PORT_TIME_FACTOR
#define HAL_OS_PORT_TIME_FACTOR                         1
#endif

// -----------------------------------------------------------------------------
//  OS CORE PORT
// -----------------------------------------------------------------------------

typedef DWORD OSTime;

void OS_PORT_Start(void);

void OS_PORT_Stop(void);

#define OS_PORT_GetSystemTime()							((OSTime)(GetTickCount()/HAL_OS_PORT_TIME_FACTOR))

#define OS_PORT_Sleep(ticks)   							Sleep((OSTime)((ticks)*HAL_OS_PORT_TIME_FACTOR))

#define OS_PORT_SleepUntil(ostime)						do { Sleep(2);  } while ((ostime) > OS_PORT_GetSystemTime())


// -----------------------------------------------------------------------------
//  OS TASK PORT
// -----------------------------------------------------------------------------

typedef DWORD OSTask;

OSTask OSTASK_PORT_Create(void (*task_impl)(void*), int priority, size_t stack_size, void* arg);

void OSTASK_PORT_Destroy(OSTask task);

void OSTASK_PORT_Suspend(OSTask task);

void OSTASK_PORT_Resume(OSTask task);

#define OSTASK_PORT_Yield()								Sleep(0)

void OSTASK_PORT_SetPriority(OSTask task, int priority);

int OSTASK_PORT_GetPriority(OSTask task);

#define OSTASK_PORT_GetCurrentTask()					GetCurrentThreadId()


// -----------------------------------------------------------------------------
//  OS SEM PORT
// -----------------------------------------------------------------------------

typedef HANDLE OSSem;

#define OSSEM_PORT_Create()								CreateSemaphore(NULL, 0, 1, NULL)

#define OSSEM_PORT_Destroy(sem)							CloseHandle(sem)

#define OSSEM_PORT_Give(sem)							ReleaseSemaphore(sem, 1, NULL)

#define OSSEM_PORT_Take(sem, timeout)					WaitForSingleObject(sem, timeout)

// -----------------------------------------------------------------------------
//  OS CNTSEM PORT
// -----------------------------------------------------------------------------

typedef HANDLE OSCntSem;

#define OSCNTSEM_PORT_Create(init, max)                 CreateSemaphore(NULL, init, max, NULL)

#define OSCNTSEM_PORT_Destroy(sem)						CloseHandle(sem)

#define OSCNTSEM_PORT_Give(sem)							ReleaseSemaphore(sem, 1, NULL)

#define OSCNTSEM_PORT_Take(sem, timeout)				WaitForSingleObject(sem, timeout)

// -----------------------------------------------------------------------------
//  OS MUTEX PORT
// -----------------------------------------------------------------------------

typedef HANDLE OSMutex;

#define OSMUTEX_PORT_Create()					CreateMutex(NULL, 0, NULL)

#define OSMUTEX_PORT_Destroy(mutex) 			CloseHandle(mutex)

#define OSMUTEX_PORT_Give(mutex) 				ReleaseMutex(mutex)

#define OSMUTEX_PORT_Take(mutex, timeout) 		WaitForSingleObject(mutex, timeout)

// -----------------------------------------------------------------------------
//  CALENDAR TIME (CALTIME) API
// -----------------------------------------------------------------------------

/// Type representing OS calendar time
typedef int64_t OSCalTime;

