/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.c
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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "hal_defs.h"
#include "hal_port_os.h"
#include <winnt.h>

#ifndef __cplusplus
#define TRUE 1
#define FALSE 0
#endif


typedef struct {
	void (*task_impl)(void*);
	void *arg;
} ostask_thread_desc;

HANDLE OSStopSem; 
int HAL_OS_RunningTaskCnt = 0;
int HAL_OS_CreatedTaskCnt = 0;

// -----------------------------------------------------------------------------
//  OSTASK_thread_wrapper
// -----------------------------------------------------------------------------
DWORD WINAPI OSTASK_thread_wrapper(LPVOID arg)
{
	// indicate that the task started operating
	HAL_OS_RunningTaskCnt++;
	// run the task
	((ostask_thread_desc*)arg)->task_impl(((ostask_thread_desc*)arg)->arg);
	// free task descriptor
	free(arg);
	HAL_OS_RunningTaskCnt--;
	return 0;
} /* OSTASK_thread_wrapper */



// -----------------------------------------------------------------------------
//  OSTASK_PORT_Create
// -----------------------------------------------------------------------------
OSTask OSTASK_PORT_Create(void (*task_impl)(void*), int priority, size_t stack_size, void* arg)
{
	OSTask result = 0;
	ostask_thread_desc *thread_desc;

	thread_desc = (ostask_thread_desc*)malloc(sizeof(ostask_thread_desc));
	if (thread_desc) {
		thread_desc->task_impl = task_impl;
		thread_desc->arg = arg;
		CreateThread(NULL, stack_size, OSTASK_thread_wrapper, (LPVOID)thread_desc, 0, &result);
		HAL_OS_CreatedTaskCnt++;
	}
	return result;
} /* OSTASK_PORT_Create */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_Destroy
// -----------------------------------------------------------------------------
void OSTASK_PORT_Destroy(OSTask task)
{
	HANDLE handle;
	handle = OpenThread(THREAD_TERMINATE, FALSE, task);

	if (handle) {
		TerminateThread(handle, 0);
		CloseHandle(handle);
		HAL_OS_CreatedTaskCnt--;
		HAL_OS_RunningTaskCnt--;
	}
} /* OSTASK_PORT_Destroy */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_Suspend
// -----------------------------------------------------------------------------
void OSTASK_PORT_Suspend(OSTask task)
{
	HANDLE handle;
	handle = OpenThread(SYNCHRONIZE | THREAD_SUSPEND_RESUME, FALSE, task);

	if (handle) {
		SuspendThread(handle);
		CloseHandle(handle);
	}

} /* OSTASK_PORT_Suspend */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_Resume
// -----------------------------------------------------------------------------
void OSTASK_PORT_Resume(OSTask task)
{
	HANDLE handle;
	handle = OpenThread(SYNCHRONIZE | THREAD_SUSPEND_RESUME, FALSE, task);

	if (handle) {
		ResumeThread(handle);
		CloseHandle(handle);
	}

} /* OSTASK_PORT_Resume */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_SetThreadPriority
// -----------------------------------------------------------------------------
void OSTASK_PORT_SetThreadPriority(OSTask task, int priority)
{
	HANDLE handle;
	handle = OpenThread(SYNCHRONIZE | THREAD_SUSPEND_RESUME, FALSE, task);

	if (handle) {
		SetThreadPriority(handle, priority);
		CloseHandle(handle);
	}

} /* OSTASK_PORT_SetThreadPriority */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_GetThreadPriority
// -----------------------------------------------------------------------------
int OSTASK_PORT_GetThreadPriority(OSTask task)
{
	HANDLE handle;
	int priority=0;

	handle = OpenThread(SYNCHRONIZE | THREAD_SUSPEND_RESUME, FALSE, task);

	if (handle) {
		priority = GetThreadPriority(handle);
		CloseHandle(handle);
	}

	return priority;

} /* OSTASK_PORT_GetThreadPriority */


// -----------------------------------------------------------------------------
//  OS_PORT_Start
// -----------------------------------------------------------------------------
void OS_PORT_Start(void)
{
    OSStopSem = CreateSemaphore(NULL, 0, 1, NULL);
    WaitForSingleObject(OSStopSem, INFINITE);

} /* OS_PORT_Start */


// -----------------------------------------------------------------------------
//  OS_PORT_Stop
// -----------------------------------------------------------------------------
void OS_PORT_Stop(void)
{
    ReleaseSemaphore(OSStopSem,1, NULL);

} /* OS_PORT_Stop */


// -----------------------------------------------------------------------------
//  OSCALTIME_Get
// -----------------------------------------------------------------------------
OSCalTime OSCALTIME_Get(void)
{
	FILETIME t;

    GetSystemTimeAsFileTime(&t);

	return (uint64_t) t.dwHighDateTime << 32 | t.dwLowDateTime;

} /* OSCALTIME_Get */


// -----------------------------------------------------------------------------
//  OSCALTIME_Set
// -----------------------------------------------------------------------------
HALRESULT OSCALTIME_Set(OSCalTime time)
{
	return HALRESULT_ERROR;

} /* OSCALTIME_Set */


// -----------------------------------------------------------------------------
//  OSCALTIME_Adjust
// -----------------------------------------------------------------------------
HALRESULT OSCALTIME_Adjust(OSCalTime timeadj)
{

	return HALRESULT_ERROR;

} /* OSCALTIME_Adjust */


// -----------------------------------------------------------------------------
//  OSCALTIME_ToNS
// -----------------------------------------------------------------------------
int64_t OSCALTIME_ToNS(OSCalTime time)
{
	return time*100;

} /* OSCALTIME_ToNS */



// -----------------------------------------------------------------------------
//  OSCALTIME_ToString
// -----------------------------------------------------------------------------
HALRESULT OSCALTIME_ToString(OSCalTime time, char* str)
{

	return HALRESULT_ERROR;

} /* OSCALTIME_ToString */