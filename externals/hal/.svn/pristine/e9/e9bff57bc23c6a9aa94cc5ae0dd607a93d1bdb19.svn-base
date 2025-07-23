/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_core.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CORE module port for AVR
--------------------------------------------------------------------------------
 Comments:      This core provide 1 main system oscillator (index 0)
================================================================================
*/

#ifndef HAL_PORT_CORE_H
#define HAL_PORT_CORE_H

#include <avr/interrupt.h>


/// a variable that keeps count of nested critical sections
extern unsigned int HAL_PORT_InterruptState;

/// implementation of the CORE_EnterCritical macro for AVR with nested critical sections
#define CORE_PORT_EnterCritical() \
    do { \
        cli(); \
        HAL_PORT_InterruptState++; \
    } while (0)


/// implementation of the CORE_ExitCritical macro for AVR with nested critical sections
#define CORE_PORT_ExitCritical() \
    do { \
        if (HAL_PORT_InterruptState) { \
            HAL_PORT_InterruptState--; \
        } \
        if (0 == HAL_PORT_InterruptState) { \
            sei(); \
        } \
    } while (0)

#define CORE_PORT_EnableInterrupts()        sei()

#define CORE_PORT_DisableInterrupts()       cli()


/// implementation of the CORE_Deinit macro for AVR - infinite loop
#define CORE_PORT_Deinit()                  while(1) {;}

/// implementation of the HAL_CORE_GetSystemTime macro for AVR
#define CORE_PORT_GetSystemTime()           (0)

/// implementation of the CORE_Init macro for AVR
#define CORE_PORT_Init()                    do { } while (0)


#if defined HAL_CORE_USE_POWER_MANAGEMENT && (HAL_CORE_USE_POWER_MANAGEMENT > 0)
HAL_CORE_POWER_MODES CORE_PORT_SetPowerMode(HAL_CORE_POWER_MODES mode);

HAL_CORE_POWER_MODES CORE_PORT_GetPowerMode(void);

void CORE_PORT_RefreshPowerMode(void);
#endif

#if defined HAL_CORE_USE_SYSCLK_MANAGEMENT && (HAL_CORE_USE_SYSCLK_MANAGEMENT > 0)
#define CORE_PORT_SetClockFreq(clk, freq)       		do { } while (0)

#define CORE_PORT_GetClockFreq(clk)           			F_CPU

#define CORE_PORT_SetClockSource(clk, clk_src, freq)  	do { } while (0)

#define CORE_PORT_GetClockSource(clk)      				0

#endif

#endif /* HAL_PORT_CORE_H */
