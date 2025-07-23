/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_delay.h
 Author:        Lukasz Duda, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DELAY module port for  Atmel SAM3S
================================================================================
*/

#ifndef HAL_PORT_DELAY_H
#define HAL_PORT_DELAY_H

// -----------------------------------------------------------------------------
//  Public macros
// -----------------------------------------------------------------------------

void HAL_PORT_DELAY_MS(uint32_t ms);

void HAL_PORT_DELAY_US(uint32_t us);


#endif /* HAL_PORT_DELAY_H */
