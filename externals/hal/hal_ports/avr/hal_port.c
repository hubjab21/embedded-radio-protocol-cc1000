/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Port for AVR
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"

#include "src/hal_port_core.c"
#if (HAL_ENABLE_GPIO) || (HAL_ENABLE_IO)
//#include "src/hal_port_gpio.c"
#endif
#if defined HAL_ENABLE_IO && HAL_ENABLE_IO == 1
    //#include "src/hal_port_io_usart.c"
    #if (defined HALPORT_USART0_ENABLE_POLLING_MODE && HALPORT_USART0_ENABLE_POLLING_MODE == 1) || \
        (defined HALPORT_USART1_ENABLE_POLLING_MODE && HALPORT_USART1_ENABLE_POLLING_MODE == 1)
        #include "src/hal_port_io_usart_poll.c"
    #endif
    #if (defined HALPORT_USART0_ENABLE_BUFFERED_MODE && HALPORT_USART0_ENABLE_BUFFERED_MODE == 1) || \
        (defined HALPORT_USART1_ENABLE_BUFFERED_MODE && HALPORT_USART1_ENABLE_BUFFERED_MODE == 1)
        #include "src/hal_port_io_usart_buf.c"
    #endif
#endif // HAL_ENABLE_IO

#if (HAL_ENABLE_TIM)
    #include "src/hal_port_tim.c"
#endif
