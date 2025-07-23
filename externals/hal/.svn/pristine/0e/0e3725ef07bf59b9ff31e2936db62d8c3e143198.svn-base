/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_tim.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       TIM module port for Windows
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"
#include "hal_config.h"
#include <stdint.h>

#include "windows.h"

void HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase, uint32_t EventTimeBase);
void HAL_PORT_TIM_Deinit(void *TIM);


#if (HALPORT_USE_TIM1 == 1)
uint64_t TIMER1_GetTimeElapsed(void *TIM);
static TIM_Event eTIM1[TIM_MAX_NUM_INTERRUPT_EVENTS + TIM_MAX_NUM_TASK_EVENTS];
TIMPeripheralDesc hal_tim_desc1 = {
		0,
		0,
		eTIM1,
		HAL_PORT_TIM_Init,
		HAL_PORT_TIM_Deinit,
        0
//		TIMER2_GetTimeElapsed
};
#endif

// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Init
// -----------------------------------------------------------------------------
void HAL_PORT_TIM_Init(void *TIM, uint32_t TickTimeBase, uint32_t EventTimeBase) 
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    freq = freq;
} /* HAL_PORT_TIM_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_TIM_Deinit
// -----------------------------------------------------------------------------
void HAL_PORT_TIM_Deinit(void *TIM) 
{
} /* HAL_PORT_TIM_Deinit */
