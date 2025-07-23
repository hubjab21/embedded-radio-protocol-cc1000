/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_virtual.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's universal components
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Virtual IODevice
--------------------------------------------------------------------------------
 Comments:      implementation based on IOBuf
================================================================================
*/

#include "hal_port_io_virtual.h"

typedef struct IOVIRTUAL_IODeviceDesc IOVIRTUAL_IODeviceDesc;

struct IOVIRTUAL_IODeviceDesc {
    struct IODeviceDesc iodev;
	IOBuf rxbuf;
	IOVIRTUAL_IODeviceDesc** gates;
	int gate_count;
	int write_enabled;
	int read_enabled;
} ;

typedef struct IOVIRTUAL_IODeviceDesc* IOVIRTUAL_IODevice;


HALRESULT HAL_PORT_VIRTUAL_Init(IOVIRTUAL_IODevice dev);
HALRESULT HAL_PORT_VIRTUAL_Deinit(IOVIRTUAL_IODevice dev);
size_t HAL_PORT_VIRTUAL_GetReadCount(IOVIRTUAL_IODevice dev);
size_t HAL_PORT_VIRTUAL_GetWriteSpace(IOVIRTUAL_IODevice dev);
HALRESULT HAL_PORT_VIRTUAL_EnableWrite(IOVIRTUAL_IODevice dev);
HALRESULT HAL_PORT_VIRTUAL_DisableWrite(IOVIRTUAL_IODevice dev);
HALRESULT HAL_PORT_VIRTUAL_EnableRead(IOVIRTUAL_IODevice dev);
HALRESULT HAL_PORT_VIRTUAL_DisableRead(IOVIRTUAL_IODevice dev);
size_t HAL_PORT_VIRTUAL_Read(IOVIRTUAL_IODevice dev, void* data, size_t size, unsigned int timeout);
size_t HAL_PORT_VIRTUAL_Write(IOVIRTUAL_IODevice dev, const void* data, size_t size, unsigned int timeout);

// -----------------------------------------------------------------------------
//  HAL_PORT_IOVIRTUAL_Create
// -----------------------------------------------------------------------------
IODevice HAL_PORT_IOVIRTUAL_Create(size_t buf_size, int number_of_gates)
{
	IOVIRTUAL_IODevice vdev;

	// allocate memory for IODevice descriptor
	vdev = (IOVIRTUAL_IODevice)malloc(sizeof(IOVIRTUAL_IODeviceDesc));
	if (vdev) {
		vdev->gates = (IOVIRTUAL_IODevice*)malloc(number_of_gates * sizeof(IOVIRTUAL_IODevice));
		if (vdev->gates) {
			memset(vdev->gates, 0x00, number_of_gates * sizeof(IOVIRTUAL_IODevice));
			vdev->iodev.Init = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_Init;
			vdev->iodev.Deinit = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_Deinit;
			vdev->iodev.EnableWrite = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_EnableWrite;
			vdev->iodev.EnableRead = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_EnableRead;
			vdev->iodev.DisableWrite = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_DisableWrite;
			vdev->iodev.DisableRead = (IODeviceCtrlFunc) HAL_PORT_VIRTUAL_DisableRead;
			vdev->iodev.GetReadCount = (IODeviceGetCountFunc) HAL_PORT_VIRTUAL_GetReadCount;
			vdev->iodev.GetWriteSpace = (IODeviceGetCountFunc) HAL_PORT_VIRTUAL_GetWriteSpace;
			vdev->iodev.Write = (IODeviceWriteFunc) HAL_PORT_VIRTUAL_Write;
			vdev->iodev.Read = (IODeviceReadFunc) HAL_PORT_VIRTUAL_Read;		
			vdev->rxbuf = IOBUF_Create(1, buf_size);
			vdev->gate_count = number_of_gates;
			vdev->write_enabled = 0;
			vdev->read_enabled = 0;
		} else {
			free(vdev);
			vdev = NULL;
		}
	}
	return (IODevice)vdev;

} /* HAL_PORT_IOVIRTUAL_Create */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOVIRTUAL_Destroy
// -----------------------------------------------------------------------------
void HAL_PORT_IOVIRTUAL_Destroy(IODevice iodevice)
{
	IOVIRTUAL_IODevice vdev = (IOVIRTUAL_IODevice)iodevice;

	if (vdev) {
		free(vdev->gates);
		IOBUF_Destroy(vdev->rxbuf);
		free(vdev);
	}
} /* HAL_PORT_IOVIRTUAL_Destroy */


// -----------------------------------------------------------------------------
//  HAL_PORT_IOVIRTUAL_Pair
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_IOVIRTUAL_Pair(IODevice iodev1, int gate1, IODevice iodev2, int gate2)
{
	IOVIRTUAL_IODevice vdev1 = (IOVIRTUAL_IODevice)iodev1;
	IOVIRTUAL_IODevice vdev2 = (IOVIRTUAL_IODevice)iodev2;

	if ((gate1 < vdev1->gate_count) && (gate2 < vdev2->gate_count)) {
		vdev1->gates[gate1] = vdev2;
		vdev2->gates[gate2] = vdev1;
		
		return HALRESULT_OK;
	}

	return HALRESULT_ERROR;

} /* HAL_PORT_IOVIRTUAL_Pair */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_Init(IOVIRTUAL_IODevice dev)
{
	IOBUF_Clear(dev->rxbuf);
	
	return HALRESULT_OK;
} /* HAL_PORT_VIRTUAL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_Deinit(IOVIRTUAL_IODevice dev)
{
	IOBUF_Clear(dev->rxbuf);

	return HALRESULT_OK;
} /* HAL_PORT_VIRTUAL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_VIRTUAL_GetReadCount(IOVIRTUAL_IODevice dev)
{
	return IOBUF_GetCount(dev->rxbuf);

} /* HAL_PORT_VIRTUAL_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_VIRTUAL_GetWriteSpace(IOVIRTUAL_IODevice dev)
{
	int i;
	size_t result = 0x7fffffff;
	size_t space;

	// check if read path is enabled
	for (i = 0; i < dev->gate_count; i++) {
		if (NULL != dev->gates[i]) {
			if (dev->gates[i]->read_enabled) {
				space = IOBUF_GetSpace(dev->gates[i]->rxbuf);
				if (space < result) {
					result = space;
				}
			}
		}
	}

	return result;

} /* HAL_PORT_VIRTUAL_GetWriteSpace */

// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_EnableWrite(IOVIRTUAL_IODevice dev)
{
	dev->write_enabled = 1;
	
	return HALRESULT_OK;

} /* HAL_PORT_VIRTUAL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_EnableRead(IOVIRTUAL_IODevice dev)
{
	dev->read_enabled = 1;
	
	return HALRESULT_OK;

} /* HAL_PORT_VIRTUAL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_DisableWrite(IOVIRTUAL_IODevice dev)
{
	dev->write_enabled = 0;
	
	return HALRESULT_OK;

} /* HAL_PORT_VIRTUAL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_VIRTUAL_DisableRead(IOVIRTUAL_IODevice dev)
{
	dev->read_enabled = 0;
	
	return HALRESULT_OK;

} /* HAL_PORT_VIRTUAL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_VIRTUAL_Read(IOVIRTUAL_IODevice dev, void* data, size_t size, unsigned int timeout)
{
    DWORD count = 0;

	// check if read path is enabled
	if (dev->read_enabled) {
		return IOBUF_Read(dev->rxbuf, data, size);
	}

	// return number of bytes read
	return 0;

} /* HAL_PORT_VIRTUAL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_VIRTUAL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_VIRTUAL_Write(IOVIRTUAL_IODevice dev, const void* data, size_t size, unsigned int timeout)
{  
	int i;

	// check if read path is enabled
	if (dev->write_enabled) {
		for (i = 0; i < dev->gate_count; i++) {
			if (NULL != dev->gates[i]) {
				if (dev->gates[i]->read_enabled) {
					IOBUF_Write(dev->gates[i]->rxbuf, data, size);
				}
			}
		}
	}

    return size;

} /* HAL_PORT_VIRTUAL_Write */

