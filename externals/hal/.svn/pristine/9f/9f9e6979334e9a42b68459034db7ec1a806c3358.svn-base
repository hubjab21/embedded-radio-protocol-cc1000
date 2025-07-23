/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_serial.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IODevice wrapper for serial ports on Windows
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "windows.h"
#include <string.h>
#include <tchar.h>

#include "hal.h"

struct IOSERIAL_IODeviceDesc {
    struct IODeviceDesc iodev;
    LPCSTR port_name;
    HANDLE hport;
//    HANDLE hthread;
//    DWORD  thread_id;
	int write_enabled;
	int read_enabled;
    uint32_t baudrate;
    size_t rx_count;
    size_t tx_count;
} IOSERIAL_IODeviceDesc;

typedef struct IOSERIAL_IODeviceDesc* IOSERIAL_IODevice;


// function prototypes
HALRESULT HAL_PORT_SERIAL_Init(IOSERIAL_IODevice dev);
HALRESULT HAL_PORT_SERIAL_Deinit(IOSERIAL_IODevice dev);
HALRESULT HAL_PORT_SERIAL_EnableWrite(IOSERIAL_IODevice dev);
HALRESULT HAL_PORT_SERIAL_DisableWrite(IOSERIAL_IODevice dev);
HALRESULT HAL_PORT_SERIAL_EnableRead(IOSERIAL_IODevice dev);
HALRESULT HAL_PORT_SERIAL_DisableRead(IOSERIAL_IODevice dev);
size_t HAL_PORT_SERIAL_GetReadCount(IOSERIAL_IODevice dev);
size_t HAL_PORT_SERIAL_GetWriteSpace(IOSERIAL_IODevice dev);
size_t HAL_PORT_SERIAL_Read(IOSERIAL_IODevice dev, void* data, size_t size, unsigned int timeout);
size_t  HAL_PORT_SERIAL_Write(IOSERIAL_IODevice dev, const void* data, size_t size, unsigned int timeout);

static const char* HAL_PORT_SERIAL_EnumeratedDevice[64];


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Create
// -----------------------------------------------------------------------------
IODevice HAL_PORT_SERIAL_Create(const char* name, uint32_t baudrate)
{
    IOSERIAL_IODevice com;
    

	// reserve space for IODevice descriptor
    com = (IOSERIAL_IODevice)malloc(sizeof(IOSERIAL_IODeviceDesc));
    if (com) {
		// reset data
        memset(com, 0x00, sizeof(IOSERIAL_IODeviceDesc));
		com->iodev.Init = (IODeviceCtrlFunc) HAL_PORT_SERIAL_Init;
		com->iodev.Deinit = (IODeviceCtrlFunc) HAL_PORT_SERIAL_Deinit;
		com->iodev.EnableWrite = (IODeviceCtrlFunc) HAL_PORT_SERIAL_EnableWrite;
		com->iodev.EnableRead = (IODeviceCtrlFunc) HAL_PORT_SERIAL_EnableRead;
		com->iodev.DisableWrite = (IODeviceCtrlFunc) HAL_PORT_SERIAL_DisableWrite;
		com->iodev.DisableRead = (IODeviceCtrlFunc) HAL_PORT_SERIAL_DisableRead;
		com->iodev.GetReadCount = (IODeviceGetCountFunc) HAL_PORT_SERIAL_GetReadCount,
		com->iodev.GetWriteSpace = (IODeviceGetCountFunc) HAL_PORT_SERIAL_GetWriteSpace,
		com->iodev.Write = (IODeviceWriteFunc) HAL_PORT_SERIAL_Write,
		com->iodev.Read = (IODeviceReadFunc) HAL_PORT_SERIAL_Read,
		com->baudrate = baudrate;
		com->write_enabled = 0;
		com->read_enabled = 0;
        com->rx_count = 0;
        com->tx_count = 0;
		if (name) {
			com->port_name = (LPCSTR)malloc(strlen(name)+1);
			if (com->port_name) {
				strcpy((char*)com->port_name, name);
			}
		}

    }

    return (IODevice)com;

} /* HAL_PORT_SERIAL_Create */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Destroy
// -----------------------------------------------------------------------------
void HAL_PORT_SERIAL_Destroy(IODevice iodevice)
{
	IOSERIAL_IODevice com;

    if (iodevice) {
	   	com = (IOSERIAL_IODevice)iodevice;
		free(com);
    }

} /* HAL_PORT_SERIAL_Destroy */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_Init(IOSERIAL_IODevice dev)
{
	DCB dcb;

	// open stream
	dev->hport = CreateFileA (
		dev->port_name,
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	// check result
	if (INVALID_HANDLE_VALUE == dev->hport) {
		return HALRESULT_ERROR;
     }

	// get state of the communication device
	if (!GetCommState(dev->hport,&dcb)) {
		return HALRESULT_ERROR;
	}

	// configure COM port
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = dev->baudrate;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = DTR_CONTROL_DISABLE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fAbortOnError = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;

	// save configuration
	if(!SetCommState(dev->hport, &dcb)) {
		return HALRESULT_ERROR;
	}

    return HALRESULT_OK;

} /* HAL_PORT_SERIAL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_Deinit(IOSERIAL_IODevice dev)
{
	
    // close stream
	if (dev->hport) {
		CloseHandle(dev->hport);
		dev->hport = 0;
	}
    return HALRESULT_OK;

} /* HAL_PORT_SERIAL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_EnableRead(IOSERIAL_IODevice dev)
{
	if (dev) {
		dev->read_enabled = 1;

		return HALRESULT_OK;
	}
	return HALRESULT_ERROR;

} /* HAL_PORT_SERIAL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_EnableWrite(IOSERIAL_IODevice dev)
{
	if (dev) {
		dev->write_enabled = 1;

		return HALRESULT_OK;
	}
	return HALRESULT_ERROR;

} /* HAL_PORT_SERIAL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_DisableRead(IOSERIAL_IODevice dev)
{
	if (dev) {
		dev->read_enabled = 0;

		return HALRESULT_OK;
	}
	return HALRESULT_ERROR;

} /* HAL_PORT_SERIAL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SERIAL_DisableWrite(IOSERIAL_IODevice dev)
{
	if (dev) {
		dev->write_enabled = 0;

		return HALRESULT_OK;
	}
	return HALRESULT_ERROR;

} /* HAL_PORT_SERIAL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_SERIAL_GetReadCount(IOSERIAL_IODevice dev)
{
	size_t rx_buf_size = 0;
	COMSTAT status;
	DWORD errors;

	if (dev) {
		ClearCommError(dev->hport,&errors,&status);

		return status.cbInQue;
	}

	return 0;

} /* HAL_PORT_SERIAL_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_SERIAL_GetWriteSpace(IOSERIAL_IODevice dev)
{	
	//in COMMPROP structure:
	//The dwMaxTxQueue and dwMaxRxQueue fields indicate the maximum size of 
	//the output and input buffers internal to the driver. The value 0 in these 
	//fields indicates that you'll encounter no limit in the size of the internal queues.
	return 1;

} /* HAL_PORT_SERIAL_GetWriteSpace */



// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_SERIAL_Read(IOSERIAL_IODevice dev, void* data, size_t size, unsigned int timeout)
{
    DWORD count = 0;

	// check if read path is enabled
	if (dev->read_enabled) {
		// check if stream is opened
		if (dev->hport >= 0) {
			// read from stream
			ReadFile(dev->hport, data, size, &count, NULL);
			// increase read count (statistics)
			dev->rx_count += count;
		}
	}

	// return number of bytes read
	return count;

} /* HAL_PORT_SERIAL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_SERIAL_Write(IOSERIAL_IODevice dev, const void* data, size_t size, unsigned int timeout)
{  
    DWORD count = 0;

	// check if read path is enabled
	if (dev->write_enabled) {
		// check if stream is opened
		if (dev->hport >= 0) {
			WriteFile(dev->hport, data, size, &count, NULL);
			dev->tx_count += count;
		}
	}

    return count;

} /* HAL_PORT_SERIAL_Write */

#ifndef __GNUC__

// -----------------------------------------------------------------------------
//  IsNumeric
// -----------------------------------------------------------------------------
static int IsNumeric(TCHAR* pszString, int bIgnoreColon)
{
	//What will be the return value from this function (assume the best)
	int bNumeric = 1;
	size_t i=0;

	size_t nLen = _tcslen(pszString);
	if (nLen == 0) {
		return 0;
	}

	for (i=0; i<nLen && bNumeric; i++)
	{
		bNumeric = (iswdigit(pszString[i]) != 0);
		if (bIgnoreColon && (pszString[i] == L':')) {
			bNumeric = 1;
		}
	}

	return bNumeric;

} /* IsNumeric */

// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Enumerate
// -----------------------------------------------------------------------------
unsigned int HAL_PORT_SERIAL_Enumerate(void)
{
	TCHAR szDevices[65536];
	char pattern[] = "\\\\.\\COM";
	char devname[32], num[16];
	unsigned int j, count = 0;
	OSVERSIONINFO osvi;
	int bGetVer;
	size_t i = 0;

	//Make sure we clear out any elements which may already be in the array
	for (j = 0; j < 64; j++) {
		if (HAL_PORT_SERIAL_EnumeratedDevice[j]) {
			free((void*)HAL_PORT_SERIAL_EnumeratedDevice[j]);
			HAL_PORT_SERIAL_EnumeratedDevice[j] = NULL;
		}
	}

	//Determine what OS we are running on
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	bGetVer = GetVersionEx(&osvi);

	//On NT use the QueryDosDevice API
	if (bGetVer && (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)) {

		//Use QueryDosDevice to look for all devices of the form COMx. Since QueryDosDevice does
		//not consitently report the required size of buffer, lets start with a reasonable buffer size
		//of 4096 characters and go from there
		DWORD dwChars = QueryDosDevice(NULL, szDevices, 65536);

		if (dwChars > 0) {

			while (szDevices[i] != _T('\0')) {
				//Get the current device name
				TCHAR* pszCurrentDevice = &(szDevices[i]);

				//If it looks like "COMX" then
				//add it to the array which will be returned
				size_t nLen = _tcslen(pszCurrentDevice);
				if (nLen > 3) {
					if ((_tcsnicmp(pszCurrentDevice, _T("COM"), 3) == 0) && IsNumeric(&(pszCurrentDevice[3]), FALSE)) {
						//Work out the port number
						int nPort = _ttoi(&pszCurrentDevice[3]);

						// construct valid port name
						strcpy(devname, pattern);
						_itoa(nPort, num, 10);
						strcat(devname, num);

						// add to the enumerated devices list
						for (j = 0; j < 64; j++) {
							if (NULL == HAL_PORT_SERIAL_EnumeratedDevice[j]) {
								HAL_PORT_SERIAL_EnumeratedDevice[j] = (const char*)malloc(strlen(devname)+1);
								if (HAL_PORT_SERIAL_EnumeratedDevice[j]) {
									strcpy((char*)HAL_PORT_SERIAL_EnumeratedDevice[j], devname);
									count++;
									j = 64;
								}
							}
						}
					}
				}

				//Go to next device name
				i += (nLen + 1);
			}
		}
	}

	return count;

} /* HAL_PORT_SERIAL_Enumerate */

#else // __GNUC__

// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_Enumerate
// -----------------------------------------------------------------------------
unsigned int HAL_PORT_SERIAL_Enumerate(void)
{
	return 0;

} /* HAL_PORT_SERIAL_Enumerate */

#endif  // __GNUC__


// -----------------------------------------------------------------------------
//  HAL_PORT_SERIAL_GetEnumeratedDeviceName
// -----------------------------------------------------------------------------
const char* HAL_PORT_SERIAL_GetEnumeratedDeviceName(unsigned int index)
{
	return HAL_PORT_SERIAL_EnumeratedDevice[index];

} /* HAL_PORT_SERIAL_GetEnumeratedDeviceName */


/*! \file hal_port_io_serial.c
    \brief Serial port for HAL on Win32/PC

    Serial port for HAL on Win32/PC.
 */

