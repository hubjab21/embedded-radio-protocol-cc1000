/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_usart.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (USART)
--------------------------------------------------------------------------------
 Comments:      this file only maps io_usartx pointer to an actual devices
                handling particular modes of operation
================================================================================
*/

#include "hal_config.h"
#include "hal_port_io_usart.h"

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USART0_MODE

#if HALPORT_USART0_MODE == HALPORT_USART_MODE_BUFFERED
// USART0 by default works in buffered mode
#if defined HALPORT_USART0_ENABLE_BUFFERED_MODE
extern struct USART_IODeviceDesc io_usart0_buf;
USART_IODevice io_usart0 = &io_usart0_buf;
#else
#error Conflicting definitions:
#error HALPORT_USART0_MODE and HALPORT_USART0_ENABLE_BUFFERED_MODE
#error Buffered mode not enabled for USART0. Check your hal_config.h        
#endif
#elif HALPORT_USART0_MODE == HALPORT_USART_MODE_POLLING
// USART0 by default works in polling mode
#if defined HALPORT_USART0_ENABLE_POLLING_MODE
extern struct USART_IODeviceDesc io_usart0_poll;
USART_IODevice io_usart0 = &io_usart0_poll;
#else
#error Conflicting definitions:
#error HALPORT_USART0_MODE and HALPORT_USART0_ENABLE_POLLING_MODE
#error Polling mode not enabled for USART0. Check your hal_config.h     
#endif
#else
#error Wrong HALPORT_USART0_MODE definition! Possible values:
#error HALPORT_USART_MODE_POLLING, HALPORT_USART_MODE_BUFFERED
#error Check your hal_config.h!
#endif

#else
#error Missing HALPORT_USART0_MODE definition! Check your hal_config.h  
#endif

#endif // HALPORT_USART0_MODE

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

#if defined HALPORT_USART1_MODE

#if HALPORT_USART1_MODE == HALPORT_USART_MODE_BUFFERED
// USART1 by default works in buffered mode
#if defined HALPORT_USART1_ENABLE_BUFFERED_MODE
extern struct USART_IODeviceDesc io_usart1_buf;
USART_IODevice io_usart1 = &io_usart1_buf;
#else
#error Conflicting definitions:
#error HALPORT_USART1_MODE and HALPORT_USART1_ENABLE_BUFFERED_MODE
#error Buffered mode not enabled for USART1. Check your hal_config.h        
#endif
#elif HALPORT_USART1_MODE == HALPORT_USART_MODE_POLLING
// USART1 by default works in polling mode
#if defined HALPORT_USART1_ENABLE_POLLING_MODE
extern struct USART_IODeviceDesc io_usart1_poll;
USART_IODevice io_usart1 = &io_usart1_poll;
#else
#error Conflicting definitions:
#error HALPORT_USART1_MODE and HALPORT_USART1_ENABLE_POLLING_MODE
#error Polling mode not enabled for USART1. Check your hal_config.h     
#endif
#else
#error Wrong HALPORT_USART1_MODE definition! Possible values:
#error HALPORT_USART_MODE_POLLING, HALPORT_USART_MODE_BUFFERED
#error Check your hal_config.h!
#endif

#else
#error Missing HALPORT_USART1_MODE definition! Check your hal_config.h  
#endif

#endif // HALPORT_USART1_MODE



