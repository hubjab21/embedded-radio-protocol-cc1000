/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_usart.h
 Author:        Łukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (USART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_USART_H
#define HAL_PORT_USART_H

#include "hal.h"
#include "hal_io.h"
#include "hal_iobuf.h"


#define HALPORT_USART_MODE_POLLING              1
#define HALPORT_USART_MODE_BUFFERED             2

#ifndef HALPORT_USE_USART0
#define HALPORT_USE_USART0                      0
#define HALPORT_USART0_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART0_DEFAULT_BAUDRATE         9600
#define HALPORT_USART0_ENABLE_POLLING_MODE      1
#define HALPORT_USART0_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART0_RXBUF_SIZE               0
#define HALPORT_USART0_TXBUF_SIZE               0
#define HALPORT_USART0_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART0_IRQ_SUB_PRIORITY		    0
#endif

#ifndef HALPORT_USE_USART1
#define HALPORT_USE_USART1                      0
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE         9600
#define HALPORT_USART1_ENABLE_POLLING_MODE      1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART1_RXBUF_SIZE               0
#define HALPORT_USART1_TXBUF_SIZE               0
#define HALPORT_USART1_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART1_IRQ_SUB_PRIORITY		    0
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

#define IO_USART0                               ((IODevice)io_usart0)
extern USART_IODevice io_usart0;

#define IO_USART1                               ((IODevice)io_usart1)
extern USART_IODevice io_usart1;

#endif /* HAL_PORT_USART_H */
