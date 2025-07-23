/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Michał Kochanowski, Łukasz Duda
 Purpose:       HALFRED's OS test module
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test application of OS module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


// HAL files
#include "hal.h"

OSSem binary_sem;
OSCntSem counting_sem;
OSMutex mutex;
uint8_t test_result=0;

// -----------------------------------------------------------------------------
//  TimerTask
// -----------------------------------------------------------------------------
void TimerTask(void* param)
{
	int i;
	static uint8_t number=0;
	while (1) {
	for (i = 0; i < 2; i++) {
		OS_Sleep(1000);
		if(!number){
			DIAG_LogNL(0);
			DIAG_LogMsg(0,"\tOs start:				OK");
			test_result++;
		}
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"Tick..");
		OSCNTSEM_Give(counting_sem);
		OSCNTSEM_Give(counting_sem);
		OSCNTSEM_Give(counting_sem);
		number++;
	}

	OS_Sleep(1000);
	DIAG_LogNL(0);
	DIAG_LogMsg(0,"Sending kill signal...");
	DIAG_LogNL(0);
	DIAG_LogMsg(0,"\tOs Send kill signal:			OK");
	DIAG_LogNL(0);
	test_result++;
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
	uint8_t number_of_tests= 8;
//	while (1) {
		if (0 == OSSEM_Take(binary_sem, 20000)) {
			DIAG_LogMsg(0,"Receiving kill signal.");
			DIAG_LogNL(0);
			DIAG_LogMsg(0,"\tOs Receive kill signal:			OK");
			DIAG_LogNL(0);
			test_result++;
			DIAG_LogMsg(0,"OS Stop.");
			DIAG_LogNL(0);
			OS_Stop();
			DIAG_LogMsg(0,"\tOs Stop:				OK");
			DIAG_LogNL(0);
			test_result++;
			DIAG0_LogNL(0);
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, "/////////// HALFRED - OS port test DONE!///////////");
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, "///////////////////////SUMMARY/////////////////////");
			DIAG0_LogNL(0);
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, " TEST PASSED ");
			DIAG0_LogUINT(0,test_result,10);
			DIAG0_LogMsg(0," of ");
			DIAG0_LogUINT(0,number_of_tests,10);
			DIAG0_LogNL(0);
			DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
			DIAG0_LogNL(0);
			DIAG0_LogNL(0);
			DIAG0_LogNL(0);

		} else {
			DIAG_LogMsg(0,"Receive kill signal:			Failed");
			DIAG_LogNL(0);
		}
		OS_Sleep(1000);
//	}
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
	DIAG0_LogMsg(0, "/////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////// HALFRED - IO port test /////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/// Read comments in main.c file before testing! //");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "//////////////////// TEST 1 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG_LogMsg(0,"Creating tasks...");
	DIAG_LogNL(0);
	// create tasks
	if (NULL == OSTASK_Create(TimerTask, 1, 0, NULL)) {
		DIAG_LogMsg(0,"Create TimerTask:			Failed");
		DIAG_LogNL(0);
		Failure();
		return -1;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)1)) {
		DIAG_LogMsg(0,"Create WorkerTask:			Failed");
		DIAG_LogNL(0);
		Failure();
		return -2;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)2)) {
		DIAG_LogMsg(0,"Create WorkerTask2:			Failed");
		DIAG_LogNL(0);
		Failure();
		return -3;
	}
	if (NULL == OSTASK_Create(WorkerTask, 1, 0, (void*)3)) {
		DIAG_LogMsg(0,"Create WorkerTask3:			Failed");
		DIAG_LogNL(0);
		Failure();
		return -4;
	}
	if (NULL == OSTASK_Create(KillerTask, 1, 0, (void*)3)) {
		DIAG_LogMsg(0,"Create KillerTask:			Failed");
		DIAG_LogNL(0);
		Failure();
		return -5;
	}
	DIAG0_LogMsg(0, "\tCreating tasks:				OK");
	DIAG0_LogNL(0);
	test_result++;
	DIAG_LogMsg(0,"Creating synchronization objects...");
	DIAG_LogNL(0);

	// create semaphores and mutex'es
	binary_sem = OSSEM_Create();
	if (NULL == binary_sem) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"\tCreate binary semaphore:		Failed");
		DIAG_LogNL(0);
		Failure();
		return -6;
	}else{
		DIAG_LogMsg(0,"\tCreate binary semaphore:		OK");
		DIAG_LogNL(0);
		test_result++;
	}
	counting_sem = OSCNTSEM_Create(0, 3);
	if (NULL == counting_sem) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"\tCreate counting semaphore:		Failed");
		DIAG_LogNL(0);
		OSSEM_Destroy(binary_sem);
		OSCNTSEM_Destroy(counting_sem);
		Failure();
		return -7;

	}else{
		DIAG_LogMsg(0,"\tCreate counting semaphore:		OK");
		DIAG_LogNL(0);
		test_result++;
	}
	mutex = OSMUTEX_Create();
	if (NULL == mutex) {
		DIAG_LogNL(0);
		DIAG_LogMsg(0,"\tCreate mutex semaphore:			Failed");
		DIAG_LogNL(0);
		OSSEM_Destroy(binary_sem);
		OSCNTSEM_Destroy(counting_sem);
		Failure();
		return -8;

	}else{
		DIAG_LogMsg(0,"\tCreate mutex semaphore:			OK");
		DIAG_LogNL(0);
		test_result++;
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



