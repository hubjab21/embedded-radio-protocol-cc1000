/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_tim.h
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

#ifndef HAL_PORT_TIM_H
#define HAL_PORT_TIM_H

#include "hal_tim.h"
#include "hal_config.h"

#ifndef HALPORT_USE_TIM1
#define HALPORT_USE_TIM1                        0
#define HALPORT_TIM1_MAX_INTERRUPT_EVENTS       0
#define HALPORT_TIM1_MAX_TASK_EVENTS            0
#endif

#ifndef HALPORT_USE_TIM3
#define HALPORT_USE_TIM3                        0
#define HALPORT_TIM3_MAX_INTERRUPT_EVENTS       0
#define HALPORT_TIM3_MAX_TASK_EVENTS            0
#endif

/// TIM1 descriptor
extern TIMDeviceDesc HAL_TIM1_desc;
/// TIM3 descriptor
extern TIMDeviceDesc HAL_TIM3_desc;

/// TIM1 identifier (use it in TIM API calls)
#define HAL_TIM1            (&HAL_TIM1_desc)

/// TIM3 identifier (use it in TIM API calls)
#define HAL_TIM3            (&HAL_TIM3_desc)


#endif /* HAL_PORT_TIM_H */
