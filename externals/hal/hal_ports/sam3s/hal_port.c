/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"

#include <sam3s4c.h>
#include "../../third_party/CMSIS_SAM3S/core_cm3.h"
#include "hal_port_common.h"

#include "src/hal_port_nvic.c"

#include "src/hal_port_core.c"

#if (HAL_ENABLE_CLK)
#include "src/hal_port_clk.c"
#endif

#if (HAL_ENABLE_DELAY)
#include "src/hal_port_delay.c"
#endif

#if (HAL_ENABLE_GPIO) || (HAL_ENABLE_IO)
#include "src/hal_port_gpio.c"
#endif

#if defined HAL_ENABLE_IO && HAL_ENABLE_IO == 1

    #include "src/hal_port_io_usart.c"
    #if (defined HALPORT_USART0_ENABLE_POLLING_MODE && HALPORT_USART0_ENABLE_POLLING_MODE == 1) || \
        (defined HALPORT_USART1_ENABLE_POLLING_MODE && HALPORT_USART1_ENABLE_POLLING_MODE == 1)
        #include "src/hal_port_io_usart_poll.c"
    #endif
    #if (defined HALPORT_USART0_ENABLE_BUFFERED_MODE && HALPORT_USART0_ENABLE_BUFFERED_MODE == 1) || \
        (defined HALPORT_USART1_ENABLE_BUFFERED_MODE && HALPORT_USART1_ENABLE_BUFFERED_MODE == 1)
        #include "src/hal_port_io_usart_buf.c"
    #endif

	#include "src/hal_port_io_uart.c"
    #if (defined HALPORT_UART0_ENABLE_POLLING_MODE && HALPORT_UART0_ENABLE_POLLING_MODE == 1) || \
        (defined HALPORT_UART1_ENABLE_POLLING_MODE && HALPORT_UART1_ENABLE_POLLING_MODE == 1)
        #include "src/hal_port_io_uart_poll.c"
    #endif
    #if (defined HALPORT_UART0_ENABLE_BUFFERED_MODE && HALPORT_UART0_ENABLE_BUFFERED_MODE == 1) || \
        (defined HALPORT_UART1_ENABLE_BUFFERED_MODE && HALPORT_UART1_ENABLE_BUFFERED_MODE == 1)
        #include "src/hal_port_io_uart_buf.c"
    #endif
	#include "src/hal_port_io_spi.c"
    #if (defined HALPORT_SPI1_ENABLE_POLLING_MODE && HALPORT_SPI1_ENABLE_POLLING_MODE == 1)
        #include "src/hal_port_io_spi_poll.c"
    #endif
    #if (defined HALPORT_SPI1_ENABLE_BUFFERED_MODE && HALPORT_SPI1_ENABLE_BUFFERED_MODE == 1)
        #include "src/hal_port_io_spi_buf.c"
    #endif
   #if (defined HALPORT_SPIS1_ENABLE_SOFT_MODE && HALPORT_SPIS1_ENABLE_SOFT_MODE == 1)
        #include "src/hal_port_io_spi_soft.c"
    #endif
#endif

#if (HAL_ENABLE_TIM)
#include "src/hal_port_tim.c"
#endif
