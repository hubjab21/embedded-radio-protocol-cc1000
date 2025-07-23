/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_core.h
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CORE module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_CORE_H
#define HAL_PORT_CORE_H

// -----------------------------------------------------------------------------
//  Public macros
// -----------------------------------------------------------------------------

// A variable that keeps count of nested critical sections
extern unsigned int HAL_PORT_InterruptState;

// Implementation of the CORE_EnterCritical macro for Atmel SAM3S with nested critical sections
#define CORE_PORT_EnterCritical() \
    do { \
    	asm volatile ("cpsid i"); \
        HAL_PORT_InterruptState++; \
    } while (0)


// Implementation of the CORE_ExitCritical macro for Atmel SAM3S with nested critical sections
#define CORE_PORT_ExitCritical() \
    do { \
        if (HAL_PORT_InterruptState) { \
            HAL_PORT_InterruptState--; \
        } \
        if (0 == HAL_PORT_InterruptState) { \
        	asm volatile ("cpsie i"); \
        } \
    } while (0)

#define CORE_PORT_EnableInterrupts()        asm volatile ("cpsie i")

#define CORE_PORT_DisableInterrupts()       asm volatile ("cpsid i")


// Implementation of the CORE_Deinit macro for SAM3S - infinite loop
#define CORE_PORT_Deinit()                  while(1) {;}

// Implementation of the HAL_CORE_GetSystemTime macro for SAM3S
#define CORE_PORT_GetSystemTime()           (0)

// Implementation of the CORE_Init macro for SAM3S
void CORE_PORT_Init(void);


#endif /* HAL_PORT_CORE_H */
