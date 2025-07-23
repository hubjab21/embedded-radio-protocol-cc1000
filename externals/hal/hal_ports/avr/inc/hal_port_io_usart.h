/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_usart.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for AVR (USART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_USART_H
#define HAL_PORT_USART_H

#include "hal.h"
#include "hal_io.h"
#include "hal_iobuf.h"

#include <avr/io.h>

#define HALPORT_USART_MODE_POLLING              1
#define HALPORT_USART_MODE_BUFFERED             2

#ifndef HALPORT_USE_USART0
#define HALPORT_USE_USART0                      0
#define HALPORT_USART0_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART0_DEFAULT_BAUDRATE         9600
#define HALPORT_USART0_ENABLE_POLLING_MODE      1
#define HALPORT_USART0_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART0_ENABLE_EVENT_MODE        0
#define HALPORT_USART0_ENABLE_DMA_MODE          0
#define HALPORT_USART0_RXBUF_SIZE               0
#define HALPORT_USART0_TXBUF_SIZE               0
#endif

#ifndef HALPORT_USE_USART1
#define HALPORT_USE_USART1                      0
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE         9600
#define HALPORT_USART1_ENABLE_POLLING_MODE      1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART1_ENABLE_EVENT_MODE        0
#define HALPORT_USART1_ENABLE_DMA_MODE          0
#define HALPORT_USART1_RXBUF_SIZE               0
#define HALPORT_USART1_TXBUF_SIZE               0
#endif




// -----------------------------------------------------------------------------
//  Internal port declarations
// -----------------------------------------------------------------------------

struct USART_IODeviceDesc {
    struct IODeviceDesc iodev;
    IOBuf tx_buf;
    IOBuf rx_buf;
};

typedef struct USART_IODeviceDesc* USART_IODevice;


// -----------------------------------------------------------------------------
//  IODevice object declarations
//  Only these should be used by the application code
// -----------------------------------------------------------------------------

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	#if defined HALPORT_USART0_MODE
		#if HALPORT_USART0_MODE == HALPORT_USART_MODE_BUFFERED
			// USART0 by default works in buffered mode
			#if defined HALPORT_USART0_ENABLE_BUFFERED_MODE
				extern struct USART_IODeviceDesc io_usart0_buf;
				#define IO_USART0                               ((IODevice)&io_usart0_buf)
			#else
				#error Conflicting definitions:
				#error HALPORT_USART0_MODE and HALPORT_USART0_ENABLE_BUFFERED_MODE
				#error Buffered mode not enabled for USART0. Check your hal_config.h
			#endif
		#elif HALPORT_USART0_MODE == HALPORT_USART_MODE_POLLING
			// USART0 by default works in polling mode
			#if defined HALPORT_USART0_ENABLE_POLLING_MODE
				extern struct USART_IODeviceDesc io_usart0_poll;
				#define IO_USART0                               ((IODevice)&io_usart0_poll)
			#else
				#error Conflicting definitions:
				#error HALPORT_USART0_MODE and HALPORT_USART0_ENABLE_POLLING_MODE
				#error Polling mode not enabled for USART0. Check your hal_config.h
			#endif
		#else
			#error Unsupported HALPORT_USART0_MODE definition! Possible values:
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
				#define IO_USART1                               ((IODevice)&io_usart1_buf)
			#else
				#error Conflicting definitions:
				#error HALPORT_USART1_MODE and HALPORT_USART1_ENABLE_BUFFERED_MODE
				#error Buffered mode not enabled for USART1. Check your hal_config.h
			#endif
		#elif HALPORT_USART1_MODE == HALPORT_USART_MODE_POLLING
			// USART1 by default works in polling mode
			#if defined HALPORT_USART1_ENABLE_POLLING_MODE
				extern struct USART_IODeviceDesc io_usart1_poll;
				#define IO_USART1                               ((IODevice)&io_usart1_poll)
			#else
				#error Conflicting definitions:
				#error HALPORT_USART1_MODE and HALPORT_USART1_ENABLE_POLLING_MODE
				#error Polling mode not enabled for USART1. Check your hal_config.h
			#endif
		#else
			#error Unsupported HALPORT_USART1_MODE definition! Possible values:
			#error HALPORT_USART_MODE_POLLING, HALPORT_USART_MODE_BUFFERED
			#error Check your hal_config.h!
		#endif
	#else
		#error Missing HALPORT_USART1_MODE definition! Check your hal_config.h
	#endif
#endif // HALPORT_USART1_MODE


/*! \file hal_port_usart.h
    \brief USART port for HAL on AVR

    USART port for HAL on AVR.
 */

#endif /* HAL_PORT_USART_H */
