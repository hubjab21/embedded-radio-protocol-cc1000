/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_serial.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IODevice wrapper for COM ports
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#ifndef HAL_PORT_IO_SERIAL_H
#define HAL_PORT_IO_SERIAL_H

#include "hal.h"


IODevice HAL_PORT_SERIAL_Create(const char* name, uint32_t baudrate);

void HAL_PORT_SERIAL_Destroy(IODevice iodevice);

unsigned int HAL_PORT_SERIAL_Enumerate(void);

const char* HAL_PORT_SERIAL_GetEnumeratedDeviceName(unsigned int index);

/*! \file hal_port_io_serial.h
    \brief Serial port for HAL on Win32/PC

    Serial port for HAL on Win32/PC.
 */

#endif /* HAL_PORT_IO_SERIAL_H */
