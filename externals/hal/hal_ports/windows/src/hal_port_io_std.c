/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_std.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's Windows port
 Compiler:      %COMPILER%
 Hardware:      PC
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for stdio
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <stdio.h>
#ifdef WIN32
#include <conio.h>
#else
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#endif

#include "hal_port_io_std.h"


// function prototypes
HALRESULT HAL_PORT_STDIO_Init(IOSTD_IODevice dev);
HALRESULT HAL_PORT_STDIO_Deinit(IOSTD_IODevice dev);
HALRESULT HAL_PORT_STDIO_EnableWrite(IOSTD_IODevice dev);
HALRESULT HAL_PORT_STDIO_DisableWrite(IOSTD_IODevice dev);
HALRESULT HAL_PORT_STDIO_EnableRead(IOSTD_IODevice dev);
HALRESULT HAL_PORT_STDIO_DisableRead(IOSTD_IODevice dev);
size_t HAL_PORT_STDIO_GetReadCount(IODevice dev);
size_t HAL_PORT_STDIO_GetWriteSpace(IODevice dev);
size_t HAL_PORT_STDIO_Write(IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_STDIO_Read(IODevice dev, void* data, size_t size, IOTime timeout);

struct IOSTD_IODeviceDesc io_std = {
	{
		(IODeviceCtrlFunc)HAL_PORT_STDIO_Init,
		(IODeviceCtrlFunc)HAL_PORT_STDIO_Deinit,
		(IODeviceCtrlFunc)HAL_PORT_STDIO_EnableWrite,
		(IODeviceCtrlFunc)HAL_PORT_STDIO_DisableWrite,
		(IODeviceCtrlFunc)HAL_PORT_STDIO_EnableRead,
		(IODeviceCtrlFunc)HAL_PORT_STDIO_DisableRead,
		(IODeviceGetCountFunc)HAL_PORT_STDIO_GetReadCount,
		(IODeviceGetCountFunc)HAL_PORT_STDIO_GetWriteSpace,
		(IODeviceWriteFunc)HAL_PORT_STDIO_Write,
		(IODeviceReadFunc)HAL_PORT_STDIO_Read
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
		,
		NULL
#endif // HAL_IO_USE_EVENTS
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
		,
		NULL,
		{ NULL, 0 },
		{ NULL, 0 }
#endif // HAL_IO_OS_INTEGRATION
	},
	0,
	0
};


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_Init(IOSTD_IODevice dev)
{
	dev->write_enabled = 0;
	dev->read_enabled = 0;

	return  HALRESULT_OK;

} /* HAL_PORT_STDIO_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_Deinit(IOSTD_IODevice dev)
{
	dev->write_enabled = 0;
	dev->read_enabled = 0;
	
	return  HALRESULT_OK;
	
} /* HAL_PORT_STDIO_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_EnableWrite(IOSTD_IODevice dev)
{
	dev->write_enabled = 1;

	return  HALRESULT_OK;

} /* HAL_PORT_STDIO_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_DisableWrite(IOSTD_IODevice dev)
{
	dev->write_enabled = 0;

	return  HALRESULT_OK;

} /* HAL_PORT_STDIO_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_EnableRead(IOSTD_IODevice dev)
{
	dev->read_enabled = 1;

	return  HALRESULT_OK;
	
} /* HAL_PORT_STDIO_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_STDIO_DisableRead(IOSTD_IODevice dev)
{
	dev->read_enabled = 0;

	return  HALRESULT_OK;
	
} /* HAL_PORT_STDIO_DisableRead */


#ifndef WIN32

// -----------------------------------------------------------------------------
//  _kbhit
// -----------------------------------------------------------------------------
int _kbhit(void)
{
	struct timeval tv;
	fd_set read_fd;

	tv.tv_sec=0;
	tv.tv_usec=0;
	FD_ZERO(&read_fd);
	FD_SET(0,&read_fd);

	if (select(1, &read_fd, NULL, NULL, &tv) == -1) {
		return 0;
	}

	if (FD_ISSET(0,&read_fd)) {
		return 1;
	}
	return 0;
	
} /* _kbhit */


// -----------------------------------------------------------------------------
//  getch
// -----------------------------------------------------------------------------
int getch(void)
{
	struct termios oldt, newt;
	int ch;

	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

	return ch;
	
} /* getch */

#endif


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_STDIO_GetReadCount(IODevice dev)
{
    if (_kbhit()) {
        return 1;
    }

	return 0;

} /* HAL_PORT_STDIO_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_STDIO_GetWriteSpace(IODevice dev)
{
	return 1024;

} /* HAL_PORT_STDIO_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_STDIO_Read(IODevice dev, void* data, size_t size, IOTime timeout)
{
	size_t i = 0;
	IOTime start_time;

	start_time = CORE_GetSystemTime();
    while (size) {
    	while (!_kbhit()) {
    		if (CORE_GetSystemTime() > start_time + timeout) {
    			return i;
    		}
    	}
        ((char*)data)[i++] = _getch();
        size--;
    }

    return i;

} /* HAL_PORT_STDIO_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_STDIO_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_STDIO_Write(IODevice dev, const void* data, size_t size, IOTime timeout)
{
    size_t i = 0;

    while (size--) {
        putchar(((uint8_t*)data)[i++]);
    }
    fflush(stdout);

    return i;
	
} /* HAL_PORT_STDIO_Write */


/*! \file hal_port_io_std.c
    \brief STDIO port in polling mode
*/
