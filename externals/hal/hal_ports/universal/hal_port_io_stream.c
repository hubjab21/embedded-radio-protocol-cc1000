/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_stream.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's Windows port
 Compiler:      %COMPILER%
 Hardware:      PC
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       definition of IODevice using iostreams
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include <iostream.h>
#endif


// function prototypes
HALRESULT HAL_PORT_IOSTREAM_Init(IODevice dev);
HALRESULT HAL_PORT_IOSTREAM_Deinit(IODevice dev);
HALRESULT HAL_PORT_IOSTREAM_EnableWrite(IODevice dev);
HALRESULT HAL_PORT_IOSTREAM_DisableWrite(IODevice dev);
HALRESULT HAL_PORT_IOSTREAM_EnableRead(IODevice dev);
HALRESULT HAL_PORT_IOSTREAM_DisableRead(IODevice dev);
size_t HAL_PORT_IOSTREAM_GetReadCount(IODevice dev);
size_t HAL_PORT_IOSTREAM_GetWriteSpace(IODevice dev);
size_t HAL_PORT_IOSTREAM_Write(IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_IOSTREAM_Read(IODevice dev, void* data, size_t size, IOTime timeout);


#if defined HALPORT_USE_STDIO && (HALPORT_USE_STDIO != 0)
struct IODeviceDesc io_std = {
	0,
	0,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_Init,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_Deinit,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_EnableWrite,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_DisableWrite,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_EnableRead,
	(IODeviceCtrlFunc)HAL_PORT_IOSTREAM_DisableRead,
	(IODeviceGetCountFunc)HAL_PORT_IOSTREAM_GetReadCount,
	(IODeviceGetCountFunc)HAL_PORT_IOSTREAM_GetWriteSpace,
	(IODeviceWriteFunc)HAL_PORT_IOSTREAM_Write,
	(IODeviceReadFunc)HAL_PORT_IOSTREAM_Read
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
};

#endif // HALPORT_USE_STDIO


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_Init(IODevice dev)
{
	dev->write_enabled = 0;
	dev->read_enabled = 0;

	return  HALRESULT_OK;

} /* HAL_PORT_IOSTREAM_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_Deinit(IODevice dev)
{
	dev->write_enabled = 0;
	dev->read_enabled = 0;
	
	return  HALRESULT_OK;
	
} /* HAL_PORT_IOSTREAM_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_EnableWrite(IODevice dev)
{
	dev->write_enabled = 1;

	return  HALRESULT_OK;

} /* HAL_PORT_IOSTREAM_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_DisableWrite(IODevice dev)
{
	dev->write_enabled = 0;

	return  HALRESULT_OK;

} /* HAL_PORT_IOSTREAM_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_EnableRead(IODevice dev)
{
	dev->read_enabled = 1;

	return  HALRESULT_OK;
	
} /* HAL_PORT_IOSTREAM_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSTREAM_DisableRead(IODevice dev)
{
	dev->read_enabled = 0;

	return  HALRESULT_OK;
	
} /* HAL_PORT_IOSTREAM_DisableRead */


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

	if(select(1, &read_fd, NULL, NULL, &tv) == -1)
		return 0;

	if(FD_ISSET(0,&read_fd))
		return 1;

	return 0;
	
} /* _kbhit */


// -----------------------------------------------------------------------------
//  getch
// -----------------------------------------------------------------------------
int getch(void) {
	struct termios oldt,
	newt;
	int            ch;
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
//  HAL_PORT_IOSTREAM_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSTREAM_GetReadCount(IODevice dev)
{
    if (_kbhit()) {
        return 1;
    }

	return 0;

} /* HAL_PORT_IOSTREAM_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSTREAM_GetWriteSpace(IODevice dev)
{
	return 1024;

} /* HAL_PORT_IOSTREAM_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSTREAM_Read(IODevice dev, void* data, size_t size, IOTime timeout)
{
	char key;

    if (_kbhit()) {
        key = getch();
        if (size) {
            ((char*)data)[0] = key;
            return 1;
        }
    }

    return 0;

} /* HAL_PORT_IOSTREAM_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSTREAM_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSTREAM_Write(IODevice dev, const void* data, size_t size, IOTime timeout)
{
    size_t i = 0;

    while (size--) {
        putchar(((uint8_t*)data)[i++]);
    }
    fflush(stdout);
    return i;
	
} /* HAL_PORT_IOSTREAM_Write */


/*! \file hal_port_io_std.c
    \brief STDIO port in polling mode
*/
