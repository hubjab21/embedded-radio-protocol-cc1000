/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_tim.c
 Author:        Lukasz Duda, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       TIM module port for SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <stdlib.h>
#include "hal.h"

#if !defined HAL_ENABLE_CLK || (HAL_ENABLE_CLK == 0)
#error SAM3S TIM driver requires CLK module
#error Enable CLK module in your hal_config.h
#endif

// Function prototypes
static void 	HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase);
static void 	HAL_PORT_TIM_Deinit(void *TIM);
static void 	HAL_PORT_TIM_ResetCounter(void *TIM);
static void 	HAL_PORT_TIM_GetCapabilities(void *TIM, TIM_Capabilities* caps);
static int32_t 	HAL_PORT_TIM_GetError(void *TIM, uint32_t TickTimeBase);

// Additional function

#if (HALPORT_USE_TIM0 == 1)

static TIM_Time HAL_PORT_TIM0_GetTime(void *TIM);
static int HAL_PORT_TIM0_ScheduleEvent(void* TIM, TIM_Time time);

// Period counter
static volatile uint32_t TIM0_PeriodCounter;
// Interrupt-level event table
static TIM_Event TIM0_IntEventTable[HALPORT_TIM0_MAX_INTERRUPT_EVENTS];

// Interrupt-level events descriptor
static TIM_EventTable HAL_TIM0_IntEvents = {
	HALPORT_TIM0_MAX_INTERRUPT_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM0_IntEventTable
};

// Task-level event table
static TIM_Event TIM0_TskEventTable[HALPORT_TIM0_MAX_TASK_EVENTS];

// Task-level events descriptor
static TIM_EventTable HAL_TIM0_TskEvents = {
	HALPORT_TIM0_MAX_TASK_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM0_TskEventTable
};

// TIM0 object definition
TIMDeviceDesc HAL_TIM0_desc = {
		0,
		&HAL_TIM0_IntEvents,
		&HAL_TIM0_TskEvents,
		HAL_PORT_TIM_Init,
		HAL_PORT_TIM_Deinit,
		HAL_PORT_TIM0_GetTime,
		HAL_PORT_TIM_ResetCounter,
		HAL_PORT_TIM_GetCapabilities,
		HAL_PORT_TIM_GetError,
		HAL_PORT_TIM0_ScheduleEvent,
};

#endif // HALPORT_USE_TIM0

#if (HALPORT_USE_TIM1 == 1)

static TIM_Time HAL_PORT_TIM1_GetTime(void *TIM);
static int HAL_PORT_TIM1_ScheduleEvent(void* TIM, TIM_Time time);

// Period counter
static volatile uint32_t TIM1_PeriodCounter;
// Interrupt-level event table
static TIM_Event TIM1_IntEventTable[HALPORT_TIM1_MAX_INTERRUPT_EVENTS];

// Interrupt-level events descriptor
static TIM_EventTable HAL_TIM1_IntEvents = {
	HALPORT_TIM1_MAX_INTERRUPT_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM1_IntEventTable
};

// Task-level event table
static TIM_Event TIM1_TskEventTable[HALPORT_TIM1_MAX_TASK_EVENTS];

// Task-level events descriptor
static TIM_EventTable HAL_TIM1_TskEvents = {
	HALPORT_TIM1_MAX_TASK_EVENTS,
	0,
	{TIM_NO_EVENT},
	TIM1_TskEventTable
};

// TIM0 object definition
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


/*
 * We can use 5 different types of clock input:
 * TC_CMR_TCCLKS_TIMER_CLOCK1  MCK/2
 * TC_CMR_TCCLKS_TIMER_CLOCK2  MCK/8
 * TC_CMR_TCCLKS_TIMER_CLOCK3  MCK/32
 * TC_CMR_TCCLKS_TIMER_CLOCK4  MCK/128
 * TC_CMR_TCCLKS_TIMER_CLOCK5  SLCK or SLCK*(MUL+1)/DIV
 *
 * So algorithm is:
 *
 * prescaler = min { abs(PRESCALERX * (10^9) / F_CPU) - TickTimeBase)}
 * 							 ||         ||
 *                       2|8|32|128   in ns
 */


// DEFINE Tick period = (PRESCALER/F_CPU) * 10^9 [ns]

#define T_2     ((uint32_t)(1000000000/(CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/2)))
#define T_8     ((uint32_t)(1000000000/(CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/8)))
#define T_32    ((uint32_t)(1000000000/(CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/32)))
#define T_128   ((uint32_t)(1000000000/(CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/128)))
#define T_32768	((uint32_t)(1000000000/(CC_GetClockFreq(cc_sam3s, SAM3S_SLOW_CLOCK))))

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_FreqError
// -----------------------------------------------------------------------------
static inline uint32_t HAL_PORT_TIM_FreqError(uint32_t mck, uint8_t presc, uint32_t tick)
{
	uint32_t fmck, ft;

	fmck = mck / presc;
	ft = 1000000000 / tick;

	if (fmck >= ft) {
		return fmck - ft;
	}

	return ft - fmck;

} /* HAL_PORT_TIM_FreqError */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_CalculatePrescaler
// -----------------------------------------------------------------------------
static int8_t HAL_PORT_TIM_CalculatePrescaler(uint32_t TickTimeBase)
{
	uint8_t presc;
	uint32_t fmck, ferr, best;

	// Get value of MCK
	fmck = CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK);

	// default prescaler is /2
	presc = TC_CMR_TCCLKS_TIMER_CLOCK1;

	// Calculate frequency error for /2 prescaler
	best = HAL_PORT_TIM_FreqError(fmck, 2, TickTimeBase);

	// Calculate frequency error for /8 prescaler
	ferr = HAL_PORT_TIM_FreqError(fmck, 8, TickTimeBase);
	if (ferr < best) {
		// This setting is better than the last one
		presc = TC_CMR_TCCLKS_TIMER_CLOCK2;
		best = ferr;
	}

	// Calculate frequency error for /32 prescaler
	ferr = HAL_PORT_TIM_FreqError(fmck, 32, TickTimeBase);
	if (ferr < best) {
		// This setting is better than the last one
		presc = TC_CMR_TCCLKS_TIMER_CLOCK3;
		best = ferr;
	}

	// Calculate frequency error for /128 prescaler
	ferr = HAL_PORT_TIM_FreqError(fmck, 128, TickTimeBase);
	if (ferr < best) {
		// This setting is better than the last one
		presc = TC_CMR_TCCLKS_TIMER_CLOCK4;
		best = ferr;
	}

	// Calculate frequency error for SLCK
	ferr = HAL_PORT_TIM_FreqError(CC_GetClockFreq(cc_sam3s, SAM3S_SLOW_CLOCK), 1, TickTimeBase);
	if (ferr < best) {
		// This setting is better than the last one
		presc = TC_CMR_TCCLKS_TIMER_CLOCK5;
		best = ferr;
	}

	return presc;

} /* HAL_PORT_TIM_CalculatePrescaler */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Init
// -----------------------------------------------------------------------------
void HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase)
{
#if (HALPORT_USE_TIM0 == 1)
	if (TIM == &HAL_TIM0_desc) {

		// First, make sure the timer is stopped
		TC0_CCR0 = TC_CCR_CLKDIS;
		TC0_IDR0 = 0xffffffff;

		// Enable interrupt from TC0
		HAL_PORT_NVIC_IRQInit((IRQn_Type)TC0_IRQn,HALPORT_TIM0_IRQ_PRE_PRIORITY,HALPORT_TIM0_IRQ_SUB_PRIORITY)

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_TC0;

		// Enable clock ticking and trigger a restart
		TC0_CCR0 = TC_CCR_CLKEN | TC_CCR_SWTRG;

		// Calculate the best prescaler
		TC0_CMR0 = HAL_PORT_TIM_CalculatePrescaler(TickTimeBase);

		// Set timer overflow interrupt enable bit
		CORE_PORT_EnterCritical();
		TC0_IER0 = TC_IER_COVFS;
		CORE_PORT_ExitCritical();

	}
#endif // HALPORT_USE_TIM0


#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc) {

		// first, make sure the timer is stopped
		TC0_CCR1 = TC_CCR_CLKDIS;
		TC0_IDR1 = 0xffffffff;

		// Enable interrupt from TC1
		HAL_PORT_NVIC_IRQInit((IRQn_Type)TC1_IRQn, HALPORT_TIM1_IRQ_PRE_PRIORITY, HALPORT_TIM1_IRQ_SUB_PRIORITY);

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_TC1;

		// Enable clock ticking and trigger a restart
		TC0_CCR1 = TC_CCR_CLKEN | TC_CCR_SWTRG;

		// Calculate the best prescaler
		TC0_CMR1 = HAL_PORT_TIM_CalculatePrescaler(TickTimeBase);

		// Set timer overflow interrupt enable bit
		CORE_PORT_EnterCritical();
		TC0_IER1 = TC_IER_COVFS;
		CORE_PORT_ExitCritical();

	}
#endif // HALPORT_USE_TIM0

} /* HAL_PORT_TIM_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Deinit
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_Deinit(void *TIM)
{
#if (HALPORT_USE_TIM0 == 1)
	if (TIM == &HAL_TIM0_desc) {

		// Stop timer and deinitialize interrupts
		TC0_CCR0 = TC_CCR_CLKDIS;
		TC0_IDR0 = 0xffffffff;

		//Disable interrupt
		HAL_PORT_NVIC_IRQDeinit((IRQn_Type) TC0_IRQn);

		//disable peripheral clock
		PMC_PCER0 = 1ul <<ID_TC0;
	}
#endif
	
#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc) {

		// Stop timer and deinitialize interrupts
		TC0_CCR1 = TC_CCR_CLKDIS;
		TC0_IDR1 = 0xffffffff;

		//Disable interrupt
		HAL_PORT_NVIC_IRQDeinit((IRQn_Type) TC1_IRQn);

		//Disable peripheral clock
		PMC_PCER0 = 1ul <<ID_TC0;
	}
#endif

} /* HAL_PORT_TIM_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_ResetCounter
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_ResetCounter(void *TIM)
{

#if (HALPORT_USE_TIM0 == 1)
	if (TIM == &HAL_TIM0_desc) {

		TIM0_PeriodCounter = 0;
	}
#endif

#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc) {

		TIM1_PeriodCounter = 0;
	}
#endif

} /* HAL_PORT_TIM_ResetCounter */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_GetCapabilities
// -----------------------------------------------------------------------------
static void HAL_PORT_TIM_GetCapabilities(void *TIM, TIM_Capabilities* caps)
{
	caps->MinTickBase = T_2;
	caps->MaxTickBase = T_128;
	caps->CounterRange = 0xffff;

} /* HAL_PORT_TIM_GetCapabilities */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_GetError
// -----------------------------------------------------------------------------
static int32_t HAL_PORT_TIM_GetError(void *TIM, uint32_t TickTimeBase)
{

#if (HALPORT_USE_TIM0 == 1)
	if (TIM == &HAL_TIM0_desc) {

		// Get prescaler setting from Control Register
		switch (TC0_CMR0 & 0x07) {
		case 0:
			return T_2 - TickTimeBase;
			break;
		case 1:
			return T_8 - TickTimeBase;
			break;
		case 2:
			return T_32 - TickTimeBase;
			break;
		case 3:
			return T_128 - TickTimeBase;
			break;
		case 4:
			return T_32768 - TickTimeBase;
			break;
		default:
			break;
		} // switch
	} // if

#endif // HALPORT_USE_TIM0

#if (HALPORT_USE_TIM1 == 1)
	if (TIM == &HAL_TIM1_desc) {

		// Get prescaler setting from Control Register
		switch (TC0_CMR1 & 0x07) {
			case 0:
				return T_2 - TickTimeBase;
				break;
			case 1:
				return T_8 - TickTimeBase;
				break;
			case 2:
				return T_32 - TickTimeBase;
				break;
			case 3:
				return T_128 - TickTimeBase;
				break;
			case 4:
				return T_32768 - TickTimeBase;
				break;
			default:
				break;
		} // switch
	} // if

#endif // HALPORT_USE_TIM0
	
	return 0;
	
} /* HAL_PORT_TIM_GetError */


#if (HALPORT_USE_TIM0 == 1)
// -----------------------------------------------------------------------------
//  HAL_PORT_TIM0_GetTime
// -----------------------------------------------------------------------------
static TIM_Time HAL_PORT_TIM0_GetTime(void *TIM)
{
	TIM_Time t;

	CORE_EnterCritical();
	t.counter_periods = TIM0_PeriodCounter;

	// Get actually timer register value
	t.counter_ticks = TC0_CV0;

	CORE_ExitCritical();

	return t;
} /* HAL_PORT_TIM0_GetTime */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM0_ScheduleEvent
// -----------------------------------------------------------------------------
static int HAL_PORT_TIM0_ScheduleEvent(void* TIM, TIM_Time time)
{

	CORE_EnterCritical();
	if (time.counter_periods == TIM0_PeriodCounter) {

		// the event happens in this time slot
		// Setup output compare value to RC register
		TC0_RC0 = time.counter_ticks;

		// Enable output compare interrupt on TC0_CV0 = T0_RC0
		TC0_IER0 = TC_IER_CPCS;
	}
	CORE_ExitCritical();
	return 1;

} /* HAL_PORT_TIM0_ScheduleEvent */

#endif // HALPORT_USE_TIM0


#if (HALPORT_USE_TIM1 == 1)

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM0_GetTime
// -----------------------------------------------------------------------------
static TIM_Time HAL_PORT_TIM1_GetTime(void *TIM)
{
	TIM_Time t;

	CORE_EnterCritical();
	t.counter_periods = TIM1_PeriodCounter;

	// Get actually timer register value
	t.counter_ticks = TC0_CV1;

	CORE_ExitCritical();

	return t;
} /* HAL_PORT_TIM1_GetTime */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM0_ScheduleEvent
// -----------------------------------------------------------------------------
static int HAL_PORT_TIM1_ScheduleEvent(void* TIM, TIM_Time time)
{

	CORE_EnterCritical();
	if (time.counter_periods == TIM1_PeriodCounter) {

		// The event happens in this time slot
		// setup output compare value to RC register
		TC0_RC1 = time.counter_ticks;

		// Enable output compare interrupt on TC1_CV0 = T0_RC0
		TC0_IER1 = TC_IER_CPCS;
	}
	CORE_ExitCritical();
	return 1;

} /* HAL_PORT_TIM1_ScheduleEvent */

#endif // HALPORT_USE_TIM1


void T0_IrqHandler()
{
#if (HALPORT_USE_TIM0 == 1)

	// Get TC0 Status Register
	uint32_t sr = TC0_SR0;

	// Overflow staff
	if(sr & TC_SR_COVFS){

		// Increase period counter
		TIM0_PeriodCounter++;

		// check scheduled tasks
		TIM_InterruptProc(HAL_TIM0);
	}

	// Compare staff
	if (sr & TC_SR_CPCS) {

		// Disable interrupt
		TC0_IDR0 = TC_IDR_CPCS;
		TIM_InterruptProc(HAL_TIM0);
	}
#endif
}


void T1_IrqHandler()
{
#if (HALPORT_USE_TIM1 == 1)

	// Get TC1 Status Register
	uint32_t sr = TC0_SR1;

	// Overflow staff
	if(sr & TC_SR_COVFS){

		// Increase period counter
		TIM1_PeriodCounter++;

		// check scheduled tasks
		TIM_InterruptProc(HAL_TIM1);
	}

	// Compare staff
	if (sr & TC_SR_CPCS) {

		// Disable interrupt
		TC1_IDR0 = TC_IDR_CPCS;
		TIM_InterruptProc(HAL_TIM1);
	}
#endif
}
