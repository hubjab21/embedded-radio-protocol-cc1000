/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_socket.c
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

//#include <winsock2.h> 
#include <string.h>
#include <io.h>

#include "hal.h"

struct IOSOCKET_IODeviceDesc {
    struct IODeviceDesc iodev;
	SOCKET				sock;
    HANDLE				hthread;
    DWORD				thread_id;
	IOBuf				rxbuf;
	IOBuf				txbuf;
};

typedef struct IOSOCKET_IODeviceDesc* IOSOCKET_IODevice;


// function prototypes
HALRESULT HAL_PORT_IOSOCKET_Init(IOSOCKET_IODevice dev);
HALRESULT HAL_PORT_IOSOCKET_Deinit(IOSOCKET_IODevice dev);
HALRESULT HAL_PORT_IOSOCKET_EnableWrite(IOSOCKET_IODevice dev);
HALRESULT HAL_PORT_IOSOCKET_DisableWrite(IOSOCKET_IODevice dev);
HALRESULT HAL_PORT_IOSOCKET_EnableRead(IOSOCKET_IODevice dev);
HALRESULT HAL_PORT_IOSOCKET_DisableRead(IOSOCKET_IODevice dev);
size_t HAL_PORT_IOSOCKET_GetReadCount(IOSOCKET_IODevice dev);
size_t HAL_PORT_IOSOCKET_GetWriteSpace(IOSOCKET_IODevice dev);
size_t HAL_PORT_IOSOCKET_Read(IOSOCKET_IODevice dev, void* data, size_t size, unsigned int timeout);
size_t HAL_PORT_IOSOCKET_Write(IOSOCKET_IODevice dev, const void* data, size_t size, unsigned int timeout);


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Thread
// -----------------------------------------------------------------------------
DWORD WINAPI HAL_PORT_IOSOCKET_Thread(void* param)
{
	SOCKET sock, connection;
	IOSOCKET_IODevice iosock;
	int err;
	size_t s;
	uint8_t tmp[255];
	fd_set rxset;
	TIMEVAL timeout = {0,0};

	iosock = (IOSOCKET_IODevice)param;
	sock = iosock->sock;

	while (1) {
		// wait for connection
		connection = accept(sock, NULL, NULL);
		if (connection != INVALID_SOCKET) {
			// connection accepted
			err = 0;
			while (err != SOCKET_ERROR) {
				// check if there is something to send
				s = IOBUF_GetCount(iosock->txbuf);
				if (s) {
					// send data
					if (s > sizeof(tmp)) {
						s = sizeof(tmp);
					}
					s = IOBUF_Read(iosock->txbuf, tmp, s);
					if (s) {
						err = send(connection, (const char*)tmp, s, 0);
					}
				}
				// check if there is something to receive
				FD_ZERO(&rxset);
				FD_SET(connection, &rxset);
				s = select(0, &rxset, NULL, NULL, &timeout);
				if (s != 0) {
					recv(connection, (char*)tmp, 1, 0);
					IOBUF_Write(iosock->rxbuf, tmp, 1);
				}
				Sleep(10);
			}
		}
	}
    return 0;

} /* HAL_PORT_IOSOCKET_Thread */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Create
// -----------------------------------------------------------------------------
IODevice HAL_PORT_IOSOCKET_Create(uint32_t port, size_t tx_buf_size, size_t rx_buf_size)
{
    IOSOCKET_IODevice iosck = NULL;
	SOCKET sock;
	struct sockaddr_in saddr;
	int err;
	WSADATA wsa;

	// initialize sockets
	err = WSAStartup(0x0201, &wsa);
	if (0 != err) {
		// unable to initialize windows sockets for 2.1 spec
		return NULL;
	}

	// create new socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( -1 == sock)	{
		// unable to create socket
		return NULL;
    }

	saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;

	if (-1 == bind(sock,(const struct sockaddr *)&saddr, sizeof(struct sockaddr_in))) {      
      _close(sock);
      return NULL;
    }

	if (-1 == listen(sock, 10)) {
      _close(sock);
      return NULL;
    }

    iosck = (IOSOCKET_IODevice)malloc(sizeof(IOSOCKET_IODeviceDesc));
    if (iosck) {
		memset(iosck, 0x00, sizeof(IOSOCKET_IODeviceDesc));

		iosck->iodev.Init = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_Init;
		iosck->iodev.Deinit = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_Deinit;
		iosck->iodev.EnableWrite = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_EnableWrite;
		iosck->iodev.EnableRead = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_EnableRead;            
		iosck->iodev.DisableWrite = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_DisableWrite;
		iosck->iodev.DisableRead = (IODeviceCtrlFunc)HAL_PORT_IOSOCKET_DisableRead;            
		iosck->iodev.GetReadCount = (IODeviceGetCountFunc)HAL_PORT_IOSOCKET_GetReadCount;
		iosck->iodev.GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_IOSOCKET_GetWriteSpace;
		iosck->iodev.Write = (IODeviceWriteFunc)HAL_PORT_IOSOCKET_Write;
		iosck->iodev.Read = (IODeviceReadFunc)HAL_PORT_IOSOCKET_Read;
		iosck->rxbuf = IOBUF_Create(1, rx_buf_size);
		iosck->txbuf = IOBUF_Create(1, tx_buf_size);
		iosck->sock = sock;
	} 

    return (IODevice)iosck;

} /* HAL_PORT_IOSOCKET_Create */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Destroy
// -----------------------------------------------------------------------------
void HAL_PORT_IOSOCKET_Destroy(IODevice iodevice)
{
    if (iodevice) {
        free(iodevice);
    }
} /* HAL_PORT_IOSOCKET_Destroy */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_Init(IOSOCKET_IODevice dev)
{
	dev->hthread = CreateThread(
                    NULL, 0, HAL_PORT_IOSOCKET_Thread, dev, 0,
                    &dev->thread_id);

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_Deinit(IOSOCKET_IODevice dev)
{

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_EnableRead(IOSOCKET_IODevice dev)
{

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_EnableWrite(IOSOCKET_IODevice dev)
{

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_DisableRead(IOSOCKET_IODevice dev)
{

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOSOCKET_DisableWrite(IOSOCKET_IODevice dev)
{

    return HALRESULT_OK;

} /* HAL_PORT_IOSOCKET_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSOCKET_GetReadCount(IOSOCKET_IODevice dev)
{
	if (dev) {
		return IOBUF_GetCount(dev->rxbuf);
	}

	return 0;

} /* HAL_PORT_IOSOCKET_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSOCKET_GetWriteSpace(IOSOCKET_IODevice dev)
{
	if (dev) {
		return IOBUF_GetSpace(dev->txbuf);
	}

	return 0;

} /* HAL_PORT_IOSOCKET_GetWriteSpace */



// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSOCKET_Read(IOSOCKET_IODevice dev, void* data, size_t size, unsigned int timeout)
{
	if (dev) {
		return IOBUF_Read(dev->rxbuf, data, size);
	}
	
	return 0;

} /* HAL_PORT_IOSOCKET_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOSOCKET_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_IOSOCKET_Write(IOSOCKET_IODevice dev, const void* data, size_t size, unsigned int timeout)
{  
	if (dev) {
		return IOBUF_Write(dev->txbuf, data, size);
	}
	
	return 0;

} /* HAL_PORT_IOSOCKET_Write */


/*! \file hal_port_socket.c
    \brief Berkeley sockets port for HAL on Win32/PC

    Berkeley sockets port for HAL on Win32/PC.
 */

