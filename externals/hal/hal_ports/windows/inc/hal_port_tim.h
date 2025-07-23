/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_tim.h
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

#ifndef HAL_PORT_TIM_H
#define HAL_PORT_TIM_H

#include "hal_tim.h"
#include "hal_config.h"

#ifndef HALPORT_USE_TIM1
#define HALPORT_USE_TIM1    0
#endif

#ifndef HALPORT_USE_TIM2
#define HALPORT_USE_TIM2    0
#endif

#if (HALPORT_USE_TIM1 == 1)
extern TIMPeripheralDesc hal_tim_desc1;
#define HAL_TIM1 (&hal_tim_desc1)
#endif

#if (HALPORT_USE_TIM2 == 1)
extern TIMPeripheralDesc hal_tim_desc2;
#define HAL_TIM2 (&hal_tim_desc2)
#endif


#endif /* HAL_PORT_TIM_H */
