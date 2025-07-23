/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_socket.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IODevice wrapper for berkeley sockets communication
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#ifndef HAL_PORT_SOCKET_H
#define HAL_PORT_SOCKET_H

#include "hal.h"

IODevice HAL_PORT_IOSOCKET_Create(uint32_t port, size_t tx_buf_size, size_t rx_buf_size);

void HAL_PORT_IOSOCKET_Destroy(IODevice iodevice);


/*! \file hal_port_socket.c
    \brief Berkeley sockets port for HAL on Win32/PC

    Berkeley sockets port for HAL on Win32/PC.
 */

#endif /* HAL_PORT_SOCKET_H */
