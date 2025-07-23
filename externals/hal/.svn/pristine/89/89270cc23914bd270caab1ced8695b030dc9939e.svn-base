/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          main.c
 Author:        Łukasz Krzak, Łukasz Duda
 Purpose:       HALFRED's TIM module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses TIM module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// HAL files
#include <stdint.h>
#include "hal.h"

#define MAX_NO_OF_EVENTS        8

// this structure holds the IDs of events
TIM_EventID eid[MAX_NO_OF_EVENTS];

// -----------------------------------------------------------------------------
//  event_handler
// -----------------------------------------------------------------------------
void event_handler(TIMDevice tim, TIM_EventID event_id, TIM_Time expire_time)
{
    TIM_Time t;

    // log some info
    DIAG0_LogMsg(0,"Event handler executed, ID=0x");
    DIAG0_LogUINT(0,event_id.id, 16);

    if (TIM_GetEventType(tim, event_id) == TIM_EVENT_TYPE_INTERRUPT) {
        DIAG0_LogMsg(0,", interrupt-level ");
    } else {
        DIAG0_LogMsg(0,", task-level ");
    }

    DIAG0_LogNL(0);
    DIAG0_LogMsg(0,"  scheduled at ");
    DIAG0_LogUINT(0,expire_time.counter_periods, 10);
    DIAG0_LogMsg(0,":");
    DIAG0_LogUINT(0,expire_time.counter_ticks, 10);
    DIAG0_LogNL(0);

    // re-schedule event
    t = expire_time;
    t.counter_periods += 10;
    TIM_ScheduleEventAt(tim, event_id, t);

} /* event_handler */


// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
    TIM_Time t;
    int i;

    // initialize HAL core
    CORE_Init();

    // initialize CLOCK
    CC_Init(cc_stm32);

    IODEV_Init(IO_DEV);
    IODEV_EnableWrite(IO_DEV);
    IODEV_EnableRead(IO_DEV);

    // initialize DIAG0nostics
    DIAG_Init();
    DIAG_SetOutputDevice(0,IO_DEV);
    DIAG_ActivateChannel(0);
    // initialize and setup the timer
    // tick every 10us (or as close as possible)
    TIM_Init(TEST_TIM, 10000);

	DIAG0_LogMsg(0,"Timer ticks every ");
	DIAG0_LogINT(0,10000+TIM_GetError(TEST_TIM, 10000), 10);
	DIAG0_LogMsg(0,"ns");
	DIAG0_LogNL(0);

    // create task-level events
    for (i = 0; i < 4; i++) {
        eid[i] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_TASK);
        DIAG0_LogMsg(0,"Created task-level event, ID=0x");
        DIAG0_LogUINT(0,eid[i].id, 16);
        DIAG0_LogNL(0);
        t.counter_periods = 10+2*i;
        t.counter_ticks = 1000;
        TIM_ScheduleEventAt(TEST_TIM, eid[i], t);
    }

    i = 0;
    // create interrupt-level events
    for (i = 0; i < 4; i++) {
        eid[i] = TIM_InitEvent(TEST_TIM, event_handler, TIM_EVENT_TYPE_INTERRUPT);
        DIAG0_LogMsg(0,"Created interrupt-level event, ID=0x");
        DIAG0_LogUINT(0,eid[i].id, 16);
        DIAG0_LogNL(0);
        t.counter_periods = 10+2*i;
        t.counter_ticks = 600;
        TIM_ScheduleEventAt(TEST_TIM, eid[i], t);
    }

    while (1) {
        TIM_TaskEventProc(TEST_TIM);
    }

    // deinitialize HAL core
    CORE_Deinit();

    return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses TIM module

*/

