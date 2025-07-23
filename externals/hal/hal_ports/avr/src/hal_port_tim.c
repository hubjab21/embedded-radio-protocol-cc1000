/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_tim.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       TIM module port for AVR
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal_port_tim.h"
#include "hal_port_core.h"
#include "hal_core.h"

#define T_1 (1000000000 / F_CPU)
#define T_8 ((uint32_t)(((uint64_t)(8000000000llu)) / (uint32_t)F_CPU))
#define T_64 ((uint32_t)(((uint64_t)(64000000000llu)) / (uint32_t)F_CPU))
#define T_256 ((uint32_t)(((uint64_t)(256000000000llu)) / (uint32_t)F_CPU))
#define T_1024 ((uint32_t)(((uint64_t)(1024000000000llu)) / (uint32_t)F_CPU))

/// function prototypes
static void HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase);
static void HAL_PORT_TIM_Deinit(void *TIM);
static void HAL_PORT_TIM_ResetCounter(void *TIM);
static void HAL_PORT_TIM_GetCapabilities(void *TIM, TIM_Capabilities *caps);
static int32_t HAL_PORT_TIM_GetError(void *TIM, uint32_t TickTimeBase);

/// Differences between ATmega128 and ATmega1281/2561
#ifndef TIMSK1
#define TIMSK1 TIMSK
#endif

#ifndef TIMSK3
#define TIMSK3 TIMSK
#endif

#if (HALPORT_USE_TIM1 == 1)

static TIM_Time HAL_PORT_TIM1_GetTime(void *TIM);
static int HAL_PORT_TIM1_ScheduleEvent(void *TIM, TIM_Time time);

// period counter
static volatile uint32_t TIM1_PeriodCounter;
// interrupt-level event table
static TIM_Event TIM1_IntEventTable[HALPORT_TIM1_MAX_INTERRUPT_EVENTS];

// interrupt-level events descriptor
static TIM_EventTable HAL_TIM1_IntEvents = {
	HALPORT_TIM1_MAX_INTERRUPT_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM1_IntEventTable};

// task-level event table
static TIM_Event TIM1_TskEventTable[HALPORT_TIM1_MAX_TASK_EVENTS];

// task-level events descriptor
static TIM_EventTable HAL_TIM1_TskEvents = {
	HALPORT_TIM1_MAX_TASK_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM1_TskEventTable};

// TIM1 object definition
TIMDeviceDesc HAL_TIM1_desc = {
	0,
	&HAL_TIM1_IntEvents,
	&HAL_TIM1_TskEvents,
	HAL_PORT_TIM_Init,
	HAL_PORT_TIM_Deinit,
	HAL_PORT_TIM1_GetTime,
	HAL_PORT_TIM_ResetCounter,
	HAL_PORT_TIM_GetCapabilities,
	HAL_PORT_TIM_GetError,
	HAL_PORT_TIM1_ScheduleEvent,
};

#endif // HALPORT_USE_TIM1

#if (HALPORT_USE_TIM3 == 1)

static TIM_Time HAL_PORT_TIM3_GetTime(void *TIM);
static int HAL_PORT_TIM3_ScheduleEvent(void *TIM, TIM_Time time);

// period counter
static volatile uint32_t TIM3_PeriodCounter;
// interrupt-level event table
static TIM_Event TIM3_IntEventTable[HALPORT_TIM3_MAX_INTERRUPT_EVENTS];

// interrupt-level events descriptor
static TIM_EventTable HAL_TIM3_IntEvents = {
	HALPORT_TIM3_MAX_INTERRUPT_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM3_IntEventTable};

// task-level event table
static TIM_Event TIM3_TskEventTable[HALPORT_TIM3_MAX_TASK_EVENTS];

// task-level events descriptor
static TIM_EventTable HAL_TIM3_TskEvents = {
	HALPORT_TIM3_MAX_TASK_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM3_TskEventTable};

// TIM3 object definition
TIMDeviceDesc HAL_TIM3_desc = {
	0,
	&HAL_TIM3_IntEvents,
	&HAL_TIM3_TskEvents,
	HAL_PORT_TIM_Init,
	HAL_PORT_TIM_Deinit,
	HAL_PORT_TIM3_GetTime,
	HAL_PORT_TIM_ResetCounter,
	HAL_PORT_TIM_GetCapabilities,
	HAL_PORT_TIM_GetError,
	HAL_PORT_TIM3_ScheduleEvent,
};

#endif // HALPORT_USE_TIM3

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Init
// -----------------------------------------------------------------------------
void HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase)
{
	int8_t presc;
	int32_t err, cmp;

	// find the best timer prescaler
	// only 5 tick prescalers are available:
	// F_CPU /1 /8 /64 /256 /1024
	presc = 1;
	err = labs(T_1 - TickTimeBase);
	cmp = labs(T_8 - TickTimeBase);
	if (cmp < err)
	{
		presc = 2;
		err = cmp;
	}
	cmp = labs(T_64 - TickTimeBase);
	if (cmp < err)
	{
		presc = 3;
		err = cmp;
	}
	cmp = labs(T_256 - TickTimeBase);
	if (cmp < err)
	{
		presc = 4;
		err = cmp;
	}
	cmp = labs(T_1024 - TickTimeBase);
	if (cmp < err)
	{
		presc = 5;
		err = cmp;
	}

#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc)
	{
		// first, make sure the timer is stopped
		TCCR1B = 0x00;

		// reset all the other registers
		TCCR1A = 0x00;
		TCCR1C = 0x00;
		OCR1A = 0x0000;
		OCR1B = 0x0000;
		OCR1C = 0x0000;
		ICR1 = 0x0000;

		// set timer overflow interrupt enable bit
		CORE_PORT_EnterCritical();

		TIMSK1 |= (1 << TOIE1);
		CORE_PORT_ExitCritical();

		// save the prescaler (this also enables the timer)
		TCCR1B = presc;
	}
#endif // HALPORT_USE_TIM1

#if (HALPORT_USE_TIM3 == 1)
	if (TIM == &HAL_TIM3_desc)
	{
		// first, make sure the timer is stopped
		TCCR3B = 0x00;

		// reset all the other registers
		TCCR3A = 0x00;
		TCCR3C = 0x00;
		OCR3A = 0x0000;
		OCR3B = 0x0000;
		OCR3C = 0x0000;
		ICR3 = 0x0000;

		// set timer overflow interrupt enable bit
		CORE_PORT_EnterCritical();
		TIMSK3 |= (1 << TOIE3);
		CORE_PORT_ExitCritical();

		// save the prescaler (this also enables the timer)
		TCCR3B = presc;
	}
#endif // HALPORT_USE_TIM3

} /* HAL_PORT_TIM_Init */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Deinit
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_Deinit(void *TIM)
{

#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc)
	{
		TCCR1B = 0x00;
	}
#endif

#if (HALPORT_USE_TIM3 == 1)
	if (TIM == &HAL_TIM3_desc)
	{
		TCCR3B = 0x00;
	}
#endif

} /* HAL_PORT_TIM_Deinit */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_ResetCounter
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_ResetCounter(void *TIM)
{

#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc)
	{
		TIM1_PeriodCounter = 0;
	}
#endif

#if (HALPORT_USE_TIM3 == 1)
	if (TIM == &HAL_TIM3_desc)
	{
		TIM3_PeriodCounter = 0;
	}
#endif

} /* HAL_PORT_TIM_ResetCounter */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_GetCapabilities
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_GetCapabilities(void *TIM, TIM_Capabilities *caps)
{

	caps->MinTickBase = T_1;
	caps->MaxTickBase = T_1024;
	caps->CounterRange = 0xffff;

} /* HAL_PORT_TIM_GetCapabilities */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_GetError
// -----------------------------------------------------------------------------
static int32_t HAL_PORT_TIM_GetError(void *TIM, uint32_t TickTimeBase)
{
#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc)
	{
		switch (TCCR1B & 0x07)
		{
		case 0:
			// timer stopped
			return 0;
			break;
		case 1:
			// timer runs at F_CPU
			return T_1 - TickTimeBase;
			break;
		case 2:
			// timer runs at F_CPU/8
			return T_8 - TickTimeBase;
			break;
		case 3:
			// timer runs at F_CPU/64
			return T_64 - TickTimeBase;
			break;
		case 4:
			// timer runs at F_CPU/256
			return T_256 - TickTimeBase;
			break;
		case 5:
			// timer runs at F_CPU/1024
			return T_1024 - TickTimeBase;
			break;
		default:
			break;

		} // switch
	}	  // if
#endif	  // HALPORT_USE_TIM1

#if (HALPORT_USE_TIM3 == 1)
	if (TIM == &HAL_TIM3_desc)
	{
		switch (TCCR3B & 0x07)
		{
		case 0:
			// timer stopped
			return 0;
			break;
		case 1:
			// timer runs at F_CPU
			return T_1 - TickTimeBase;
			break;
		case 2:
			// timer runs at F_CPU/8
			return T_8 - TickTimeBase;
			break;
		case 3:
			// timer runs at F_CPU/64
			return T_64 - TickTimeBase;
			break;
		case 4:
			// timer runs at F_CPU/256
			return T_256 - TickTimeBase;
			break;
		case 5:
			// timer runs at F_CPU/1024
			return T_1024 - TickTimeBase;
			break;
		default:
			break;

		} // switch
	}	  // if
#endif	  // HALPORT_USE_TIM3

	return 0;

} /* HAL_PORT_TIM_GetError */

#if (HALPORT_USE_TIM1 == 1)

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM1_GetTime
// -----------------------------------------------------------------------------
static TIM_Time HAL_PORT_TIM1_GetTime(void *TIM)
{
	TIM_Time t;

	CORE_EnterCritical();
	t.counter_periods = TIM1_PeriodCounter;
	t.counter_ticks = TCNT1;
	CORE_ExitCritical();

	return t;
} /* HAL_PORT_TIM1_GetTime */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM1_ScheduleEvent
// -----------------------------------------------------------------------------
static int HAL_PORT_TIM1_ScheduleEvent(void *TIM, TIM_Time time)
{

	CORE_EnterCritical();
	if (time.counter_periods == TIM1_PeriodCounter)
	{
		// the event happens in this time slot
		// setup output compare value
		OCR1A = time.counter_ticks;
		// enable output compare interrupt
		TIMSK1 |= (1 << OCIE1A);
	}
	CORE_ExitCritical();

	return 1;

} /* HAL_PORT_TIM1_ScheduleEvent */

// -----------------------------------------------------------------------------
//  ISR(TIMER1_OVF_vect)
//  TIMER1 overflow interrupt handling routine
// -----------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)
{
	// increase period counter
	TIM1_PeriodCounter++;
	// check scheduled tasks
	TIM_InterruptProc(HAL_TIM1);

} /* TIMER1_OVF_vect */

// -----------------------------------------------------------------------------
//  ISR(TIMER1_COMPA_vect)
//  TIMER1 output compare interrupt handling routine
// -----------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
	// disable output compare interrupt
	TIMSK1 &= ~(1 << OCIE1A);
	// check scheduled tasks
	TIM_InterruptProc(HAL_TIM1);

} // TIMER1_COMPA_vect

#endif // HALPORT_USE_TIM1

#if (HALPORT_USE_TIM3 == 1)

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM3_GetTime
// -----------------------------------------------------------------------------
static TIM_Time HAL_PORT_TIM3_GetTime(void *TIM)
{
	TIM_Time t;

	CORE_EnterCritical();
	t.counter_periods = TIM3_PeriodCounter;
	t.counter_ticks = TCNT3;
	CORE_ExitCritical();

	return t;
} /* HAL_PORT_TIM3_GetTime */

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM3_ScheduleEvent
// -----------------------------------------------------------------------------
static int HAL_PORT_TIM3_ScheduleEvent(void *TIM, TIM_Time time)
{

	CORE_EnterCritical();
	if (time.counter_periods == TIM3_PeriodCounter)
	{
		// the event happens in this time slot
		// setup output compare value
		OCR3A = time.counter_ticks;
		// enable output compare interrupt
		TIMSK3 |= (1 << OCIE3A);
	}
	CORE_ExitCritical();

	return 1;

} /* HAL_PORT_TIM3_ScheduleEvent */

// -----------------------------------------------------------------------------
//  ISR(TIMER3_OVF_vect)
//  TIMER3 overflow interrupt handling routine
// -----------------------------------------------------------------------------
ISR(TIMER3_OVF_vect)
{
	// increase period counter
	TIM3_PeriodCounter++;
	// check scheduled tasks
	TIM_InterruptProc(HAL_TIM3);

} /* TIMER3_OVF_vect */

// -----------------------------------------------------------------------------
//  ISR(TIMER3_COMPA_vect)
//  TIMER3 output compare interrupt handling routine
// -----------------------------------------------------------------------------
ISR(TIMER3_COMPA_vect)
{
	// disable output compare interrupt
	TIMSK3 &= ~(1 << OCIE3A);
	// check scheduled tasks
	TIM_InterruptProc(HAL_TIM3);

} // TIMER3_COMPA_vect

#endif // HALPORT_USE_TIM3
