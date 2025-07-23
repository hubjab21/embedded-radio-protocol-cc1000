/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_os.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's FreeRTOS port
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       OS module port for FreeRTOS
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


#include "hal_port_os.h"
#include "hal_heap.h"
#include "hal_diag.h"

// -----------------------------------------------------------------------------
//  OS_PORT_SleepUntil
// -----------------------------------------------------------------------------
void OS_PORT_SleepUntil(OSTime time)
{	
	OSTime ostime;
	
	ostime = xTaskGetTickCount();
	time = time - ostime;
	vTaskDelayUntil(&ostime, time);
} /* OS_PORT_SleepUntil */


// -----------------------------------------------------------------------------
//  OSTASK_PORT_Create
// -----------------------------------------------------------------------------
OSTask OSTASK_PORT_Create(pdTASK_CODE task_impl, int priority, size_t stack_size, void* arg)
{
	OSTask task;
#if defined configUSE_APPLICATION_TASK_TAG && configUSE_APPLICATION_TASK_TAG > 0
	static int os_cnt;
#endif

	if (stack_size == 0) {
		stack_size = configMINIMAL_STACK_SIZE;
	}
	priority += tskIDLE_PRIORITY;
	if (pdPASS != xTaskCreate( task_impl, NULL, stack_size, arg, priority, &task )) {
		return NULL;
	}

#if defined configUSE_APPLICATION_TASK_TAG && configUSE_APPLICATION_TASK_TAG > 0
	vTaskSetApplicationTaskTag(task, (void*)os_cnt++);
#endif

	return task;
} /* OSTASK_PORT_Create */


#if defined HAL_HEAP_MODE && HAL_HEAP_MODE == 1

// -----------------------------------------------------------------------------
//  pvPortMalloc
// -----------------------------------------------------------------------------
void *pvPortMalloc( size_t xWantedSize )
{
	// just a wrapper on HAL heap manager
	return HEAP_Alloc(xWantedSize);
} /* pvPortMalloc */


// -----------------------------------------------------------------------------
//  vPortFree
// -----------------------------------------------------------------------------
void vPortFree( void *pv )
{
	// just a wrapper on HAL heap manager
	HEAP_Free(pv);
} /* vPortFree */

#endif // HAL_HEAP_MODE == 1


#if defined configCHECK_FOR_STACK_OVERFLOW && (configCHECK_FOR_STACK_OVERFLOW != 0)

// -----------------------------------------------------------------------------
//  vApplicationStackOverflowHook
// -----------------------------------------------------------------------------
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
	DIAG_LogMsg(0,"STACK OVERFLOW IN OS TASK: ");
	DIAG_LogMsg(0,(char*)pcTaskName);
	DIAG_LogNL(0);

} /* vApplicationStackOverflowHook */

#endif // configCHECK_FOR_STACK_OVERFLOW != 0
