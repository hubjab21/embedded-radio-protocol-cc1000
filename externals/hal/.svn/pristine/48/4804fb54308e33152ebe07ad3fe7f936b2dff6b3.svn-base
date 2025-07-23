/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_uart.h
 Author:        Łukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (UART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_UART_H
#define HAL_PORT_UART_H

#include "hal.h"
#include "hal_io.h"
#include "hal_iobuf.h"


#define HALPORT_UART_MODE_POLLING              1
#define HALPORT_UART_MODE_BUFFERED             2

#ifndef HALPORT_USE_UART0
#define HALPORT_USE_UART0                      0
#define HALPORT_UART0_MODE                     HALPORT_UART_MODE_POLLING
#define HALPORT_UART0_DEFAULT_BAUDRATE         9600
#define HALPORT_UART0_ENABLE_POLLING_MODE      1
#define HALPORT_UART0_ENABLE_BUFFERED_MODE     0
#define HALPORT_UART0_RXBUF_SIZE               0
#define HALPORT_UART0_TXBUF_SIZE               0
#define HALPORT_UART0_IRQ_PRE_PRIORITY		   0
#define HALPORT_UART0_IRQ_SUB_PRIORITY		   0
#endif

#ifndef HALPORT_USE_UART1
#define HALPORT_USE_UART1                      0
#define HALPORT_UART1_MODE                     HALPORT_UART_MODE_POLLING
#define HALPORT_UART1_DEFAULT_BAUDRATE         9600
#define HALPORT_UART1_ENABLE_POLLING_MODE      1
#define HALPORT_UART1_ENABLE_BUFFERED_MODE     0
#define HALPORT_UART1_RXBUF_SIZE               0
#define HALPORT_UART1_TXBUF_SIZE               0
#define HALPORT_UART1_IRQ_PRE_PRIORITY		   0
#define HALPORT_UART1_IRQ_SUB_PRIORITY		   0
#endif




// -----------------------------------------------------------------------------
//  Internal port declarations
// -----------------------------------------------------------------------------

struct UART_IODeviceDesc {
    struct IODeviceDesc iodev;
    IOBuf tx_buf;
    IOBuf rx_buf;
};

typedef struct UART_IODeviceDesc* UART_IODevice;


// -----------------------------------------------------------------------------
//  IODevice object declarations
//  Only these should be used by the application code
// -----------------------------------------------------------------------------

#define IO_UART0                               ((IODevice)io_uart0)
extern UART_IODevice io_uart0;

#define IO_UART1                               ((IODevice)io_uart1)
extern UART_IODevice io_uart1;

#endif /* HAL_PORT_UART_H */
