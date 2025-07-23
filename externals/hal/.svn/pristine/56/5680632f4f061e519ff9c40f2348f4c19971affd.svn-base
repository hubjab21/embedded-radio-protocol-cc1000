/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HALFRED port for Windows
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/
#include "hal.h"

#include "src/hal_port_core.c"

#if (HAL_ENABLE_GPIO)
#include "src/hal_port_gpio.c"
#endif

#if (HAL_ENABLE_IO)
#include "src/hal_port_io_std.c"
#include "src/hal_port_io_serial.c"
#include "src/hal_port_io_virtual.c"
#if defined HALPORT_USE_IOSOCKET && (HALPORT_USE_IOSOCKET != 0)
#include "src/hal_port_io_socket.c"
#endif
#endif
