/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_tim.h
 Author:        Lukasz Duda, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       TIM module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_TIM_H
#define HAL_PORT_TIM_H

#include "hal_tim.h"

// HAL TIM Section
#ifndef HALPORT_USE_TIM0
#define HALPORT_USE_TIM0						0
#define HALPORT_TIM0_MAX_INTERRUPT_EVENTS       0
#define HALPORT_TIM0_MAX_TASK_EVENTS            0
#define HALPORT_TIM0_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM0_IRQ_SUB_PRIORITY			0
#endif

#ifndef HALPORT_USE_TIM1
#define HALPORT_USE_TIM1						0
#define HALPORT_TIM1_MAX_INTERRUPT_EVENTS       0
#define HALPORT_TIM1_MAX_TASK_EVENTS            0
#define HALPORT_TIM1_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM1_IRQ_SUB_PRIORITY			0
#endif

// TIM1 descriptors
extern TIMDeviceDesc HAL_TIM0_desc;
extern TIMDeviceDesc HAL_TIM1_desc;


// TIM identifiers (use it in TIM API calls)
#define HAL_TIM0	         (&HAL_TIM0_desc)
#define HAL_TIM1	         (&HAL_TIM1_desc)

#endif /* HAL_PORT_TIM_H */
