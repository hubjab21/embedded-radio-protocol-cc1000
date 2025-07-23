/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_uart.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (UART)
--------------------------------------------------------------------------------
 Comments:      this file only maps io_uartx pointer to an actual devices
                handling particular modes of operation
================================================================================
*/

#include "hal_config.h"
#include "hal_port_io_uart.h"

#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_UART0_MODE

#if HALPORT_UART0_MODE == HALPORT_UART_MODE_BUFFERED
// UART0 by default works in buffered mode
#if defined HALPORT_UART0_ENABLE_BUFFERED_MODE
extern struct UART_IODeviceDesc io_uart0_buf;
UART_IODevice io_uart0 = &io_uart0_buf;
#else
#error Conflicting definitions:
#error HALPORT_UART0_MODE and HALPORT_UART0_ENABLE_BUFFERED_MODE
#error Buffered mode not enabled for UART0. Check your hal_config.h
#endif
#elif HALPORT_UART0_MODE == HALPORT_UART_MODE_POLLING
// UART0 by default works in polling mode
#if defined HALPORT_UART0_ENABLE_POLLING_MODE
extern struct UART_IODeviceDesc io_uart0_poll;
UART_IODevice io_uart0 = &io_uart0_poll;
#else
#error Conflicting definitions:
#error HALPORT_UART0_MODE and HALPORT_UART0_ENABLE_POLLING_MODE
#error Polling mode not enabled for UART0. Check your hal_config.h
#endif
#else
#error Wrong HALPORT_UART0_MODE definition! Possible values:
#error HALPORT_UART_MODE_POLLING, HALPORT_UART_MODE_BUFFERED
#error Check your hal_config.h!
#endif

#else
#error Missing HALPORT_UART0_MODE definition! Check your hal_config.h
#endif

#endif // HALPORT_UART0_MODE

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

#if defined HALPORT_UART1_MODE

#if HALPORT_UART1_MODE == HALPORT_UART_MODE_BUFFERED
// UART1 by default works in buffered mode
#if defined HALPORT_UART1_ENABLE_BUFFERED_MODE
extern struct UART_IODeviceDesc io_uart1_buf;
UART_IODevice io_uart1 = &io_uart1_buf;
#else
#error Conflicting definitions:
#error HALPORT_UART1_MODE and HALPORT_UART1_ENABLE_BUFFERED_MODE
#error Buffered mode not enabled for UART1. Check your hal_config.h
#endif
#elif HALPORT_UART1_MODE == HALPORT_UART_MODE_POLLING
// UART1 by default works in polling mode
#if defined HALPORT_UART1_ENABLE_POLLING_MODE
extern struct UART_IODeviceDesc io_uart1_poll;
UART_IODevice io_uart1 = &io_uart1_poll;
#else
#error Conflicting definitions:
#error HALPORT_UART1_MODE and HALPORT_UART1_ENABLE_POLLING_MODE
#error Polling mode not enabled for UART1. Check your hal_config.h
#endif
#else
#error Wrong HALPORT_UART1_MODE definition! Possible values:
#error HALPORT_UART_MODE_POLLING, HALPORT_UART_MODE_BUFFERED
#error Check your hal_config.h!
#endif

#else
#error Missing HALPORT_UART1_MODE definition! Check your hal_config.h
#endif

#endif // HALPORT_UART1_MODE
