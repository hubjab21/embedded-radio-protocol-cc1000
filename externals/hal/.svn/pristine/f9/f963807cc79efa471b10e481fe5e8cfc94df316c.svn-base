/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's OS module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses OS module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


// HAL files
#include "hal.h"

OSSem binary_sem;
OSCntSem counting_sem;
OSMutex mutex;


// -----------------------------------------------------------------------------
//  TimerTask
// -----------------------------------------------------------------------------
void TimerTask(void* param)
{
	int i;

	while (1) {
		for (i = 0; i < 10; i++) {
			OS_Sleep(1000);
			DIAG_LogNL(0);
			DIAG_LogMsg(0,"Tick..");
			OSCNTSEM_Give(counting_sem);
			OSCNTSEM_Give(counting_sem);
			OSCNTSEM_Give(counting_sem);
		}
		OS_Sleep(1000);
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Sending kill signal...");
		DIAG_LogNL(0);
		OSSEM_Give(binary_sem);
		OS_Sleep(1000);
	}
} /* TimerTask */


// -----------------------------------------------------------------------------
//  WorkerTask
// -----------------------------------------------------------------------------
void WorkerTask(void* param)
{
	int task_no;

	task_no = (int)param;

	while (1) {
		if (0 == OSCNTSEM_Take(counting_sem, 2000)) {
			if (0 == OSMUTEX_Take(mutex, 1000)) {
				DIAG_LogMsg(0," Task");
				DIAG_LogINT(0,task_no, 10);
				OSMUTEX_Give(mutex);
			}
			OSTASK_Yield();
		}
	}
} /* WorkerTask */


// -----------------------------------------------------------------------------
//  KillerTask
// -----------------------------------------------------------------------------
void KillerTask(void* param)
{
	while (1) {
		if (0 == OSSEM_Take(binary_sem, 20000)) {
			DIAG_LogMsg(0,"Received kill signal.");
			DIAG_LogNL(0);
			DIAG_LogMsg(0,"OS Stop.");
			DIAG_LogNL(0);
			OS_Stop();
		} else {
			DIAG_LogMsg(0,"Timeout on kill signal.");
			DIAG_LogNL(0);
		}
		OS_Sleep(1000);
	}
} /* KillerTask */


// -----------------------------------------------------------------------------
//  Failure
// -----------------------------------------------------------------------------
static void Failure(void)
{
	DIAG_LogMsg(0,"Unable to continue");
	// deinitialize HAL
	CORE_Deinit();
} /* Failure */


// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
	/// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();

	HAL_GPIO_Init();

	// initialize communication device
	IODEV_Init(IO_DEV);
	IODEV_EnableWrite(IO_DEV);
	IODEV_EnableRead(IO_DEV);

	// initialize diagnostics
	DIAG_Init();
	DIAG_SetOutputDevice(0,IO_DEV);
	DIAG_ActivateChannel(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"Creating tasks...");
	DIAG0_LogNL(0);

	// create tasks
	if (NULL == OSTASK_Create(TimerTask, 1, 0, NULL)) {
		DIAG_LogMsg(0,"Failed to create TimerTask!");
		DIAG_LogNL(0);
		Failure();
		return -1;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)1)) {
		DIAG_LogMsg(0,"Failed to create WorkerTask 1!");
		DIAG_LogNL(0);
		Failure();
		return -2;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)2)) {
		DIAG_LogMsg(0,"Failed to create WorkerTask 2!");
		DIAG_LogNL(0);
		Failure();
		return -3;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)3)) {
		DIAG_LogMsg(0,"Failed to create WorkerTask 3!");
		DIAG_LogNL(0);
		Failure();
		return -4;
	}
	if (NULL == OSTASK_Create(KillerTask, 1, 0, (void*)3)) {
		DIAG_LogMsg(0,"Failed to create KillerTask!");
		DIAG_LogNL(0);
		Failure();
		return -5;
	}

	DIAG_LogMsg(0,"Creating synchronization objects...");
	DIAG_LogNL(0);

	// create semaphores and mutex'es
	binary_sem = OSSEM_Create();
	if (NULL == binary_sem) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Failed to create binary semaphore!");
		DIAG_LogNL(0);
		Failure();
		CORE_Deinit();
		return -6;
	}
	counting_sem = OSCNTSEM_Create(0, 3);
	if (NULL == counting_sem) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Failed to create counting semaphore!");
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Unable to continue");

		OSSEM_Destroy(binary_sem);
		OSCNTSEM_Destroy(counting_sem);

		// deinitialize HAL
		CORE_Deinit();
		return -7;

	}
	mutex = OSMUTEX_Create();
	if (NULL == mutex) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Failed to create mutex semaphore!");
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Unable to continue");

		OSSEM_Destroy(binary_sem);
		OSCNTSEM_Destroy(counting_sem);

		// deinitialize HAL
		CORE_Deinit();
		return -8;

	}


	DIAG_LogMsg(0,"Starting OS...");

	// start OS
	OS_Start();

	// now the OS has taken control over this control flow and executes scheduled tasks,
	// until one of the tasks call OS_Stop

	DIAG_LogMsg(0,"Done.");
	DIAG_LogNL(0);

	// free resources
	OSSEM_Destroy(binary_sem);
	OSCNTSEM_Destroy(counting_sem);
	OSMUTEX_Destroy(mutex);

	// deinitialize HAL
	CORE_Deinit();

	return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses OS module

*/

