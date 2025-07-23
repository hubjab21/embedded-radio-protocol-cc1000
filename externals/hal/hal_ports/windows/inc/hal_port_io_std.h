/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_std.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_IO_STD_H
#define HAL_PORT_IO_STD_H

#include "hal_iodevice.h"

struct IOSTD_IODeviceDesc {
    struct IODeviceDesc iodev;
    int write_enabled;
    int read_enabled;
};

typedef struct IOSTD_IODeviceDesc* IOSTD_IODevice;

// IODevice declarations
#define IO_STD   								((IODevice)&io_std)

extern struct IOSTD_IODeviceDesc io_std;

#endif // HAL_PORT_IO_STD_H
