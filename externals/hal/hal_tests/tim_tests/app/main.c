/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda, Michał Kochanowski
 Purpose:       HALFRED's TIM port test
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test of TIM capabilities
--------------------------------------------------------------------------------
 Comments:		Test, some time require CLK module (eg. stm32f4, f0, sam3s)
================================================================================
*/


// include the one and only HAL header
#include "hal.h"

#define MAX_NO_OF_EVENTS        8

// this structure holds the IDs of events
TIM_EventID eid[MAX_NO_OF_EVENTS];

// helper variable
uint8_t executed = 0;
uint8_t test_result = 0;


// -----------------------------------------------------------------------------
//  event_handler
// -----------------------------------------------------------------------------
void event_handler(TIMDevice tim, TIM_EventID event_id, TIM_Time expire_time)
{

	// log some info
	DIAG0_LogNL(0);

	if (TIM_GetEventType(tim, event_id) == TIM_EVENT_TYPE_INTERRUPT) {
		DIAG0_LogMsg(0,",\t Interrupt-level ");
	} else {
		DIAG0_LogMsg(0,",\t Task-level ");
	}

	DIAG0_LogMsg(0,"event executed successfully:		OK!");
	DIAG0_LogNL(0);
	test_result++;
	DIAG0_LogNL(0);
	executed++;
} /* event_handler */

// -----------------------------------------------------------------------------
//  event_handler2
// -----------------------------------------------------------------------------
void event_handler2(TIMDevice tim, TIM_EventID event_id, TIM_Time expire_time)
{
    TIM_Time t;

	DIAG0_LogNL(0);
    DIAG0_LogMsg(0,",\tTask-level event executed successfully:			OK!");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	test_result++;
	if(executed < 2)
	{
		DIAG0_LogNL(0);
	    DIAG0_LogMsg(0,",\tRescheduling event:					OK!");
		DIAG0_LogNL(0);

		// re-schedule event
		t = expire_time;
		t.counter_periods += 2;
		TIM_ScheduleEventAt(tim, event_id, t);
		test_result++;
	}

	executed++;

} /* event_handler2 */

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
	// initialize HAL core
	CORE_Init();

	// initialize GPIO module
	HAL_GPIO_Init();

	// initialize IODevices used by the DIAG module
	IODEV_Init(IO_DIAG);
	IODEV_EnableWrite(IO_DIAG);
	IODEV_EnableRead(IO_DIAG);

	// initialize DIAG module
	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DIAG);
	DIAG_ActivateChannel(0);

	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////// HALFRED - TIM port test ////////////");
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

	TIM_Time t;

	// initialize and setup the timer
	// tick every 10us (or as close as possible)
	TIM_Init(TEST_TIM, 10000);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tInitialize timer with 10us (or close as possible):	OK!");
	DIAG0_LogNL(0);
	test_result++;
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tTIM_GetError return: ");
	DIAG0_LogINT(0,TIM_GetError(TEST_TIM, 10000), 10);
	DIAG0_LogMsg(0,"ns");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	TIM_Capabilities caps;

	TIM_GetCapabilities(TEST_TIM, &caps);

	DIAG0_LogMsg(0,"\tTIM_Capabilities return: ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"\t\tMinimum Tick Base return: ");
	DIAG0_LogUINT(0, caps.MinTickBase, 10);
	DIAG0_LogMsg(0,"ns");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"\t\tMaximum Tick Base return: ");
	DIAG0_LogUINT(0, caps.MaxTickBase, 10);
	DIAG0_LogMsg(0,"ns");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"\t\tCounter range is: ");
	DIAG0_LogUINT(0, caps.CounterRange, 10);
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	TIM_Deinit(TEST_TIM);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tDeinitialize timer:					OK!");
	test_result++;
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);


	DIAG0_LogMsg(0, "//////////////////// TEST 2 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);

	// initialize and setup the timer
	// tick every 1s (or as close as possible)
	TIM_Init(TEST_TIM, 1000000);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tInitialize timer with 1ms (or close as possible):	OK!");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	test_result++;
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tCreate 1st task-level event (after 400 ticks)");
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tCreate 1st interrupt-level event (after 800 ticks)");
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tCreate 2nd task-level event (after 600 ticks)");
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tCreate 2nd interrupt-level event (after 1000 ticks)");
	DIAG0_LogNL(0);

	eid[0] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_TASK);
	eid[1] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_TASK);
	eid[2] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_INTERRUPT);
	eid[3] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_INTERRUPT);

	TIM_ResetCounter(TEST_TIM);

	t.counter_periods = 0;
	t.counter_ticks = 400;
	TIM_ScheduleEventAt(TEST_TIM, eid[0], t);

	t.counter_periods = 0;
	t.counter_ticks = 800;
	TIM_ScheduleEventAt(TEST_TIM, eid[1], t);

	t.counter_periods = 0;
	t.counter_ticks = 600;
	TIM_ScheduleEventAt(TEST_TIM, eid[2], t);

	t.counter_periods = 0;
	t.counter_ticks = 800;
	TIM_ScheduleEventAt(TEST_TIM, eid[3], t);


	while (1 & (executed < 3)) {
		TIM_TaskEventProc(TEST_TIM);

		if(executed == 3){
			break;
		}
	}

	TIM_Deinit(TEST_TIM);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tDeinitialize timer:					OK!");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	test_result++;

	executed = 0;

	DIAG0_LogMsg(0, "//////////////////// TEST 3 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);


	// initialize and setup the timer
	// tick every 10us (or as close as possible)
	TIM_Init(TEST_TIM, 10000);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tInitialize timer with 10us (or close as possible):	OK!");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	test_result++;

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "\tCreate task-level event (after 2 periods and 100 ticks)");
	DIAG0_LogNL(0);

	eid[0] = TIM_InitEvent(TEST_TIM, event_handler2, TIM_EVENT_TYPE_TASK);

	t.counter_periods = 2;
	t.counter_ticks = 100;
	TIM_ScheduleEventAt(TEST_TIM, eid[0], t);

	while (1 & (executed < 3)) {
		TIM_TaskEventProc(TEST_TIM);
	}

	uint8_t number_of_tests = 14;

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////// HALFRED - TIM port test DONE!//////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////SUMMARY/////////////////////");
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
	while(1)
	{
		asm volatile ("nop");
	}

	// deinitialize HAL
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
