/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_iocomposite.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's universal components
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IODevice that reads and writes to multiple other IODevices
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hal.h"

struct COMPOSITE_IODeviceDesc {
    struct IODeviceDesc iodev;
    unsigned int cnt;
    IODevice *association;
};


typedef struct COMPOSITE_IODeviceDesc* COMPOSITE_IODevice;

// function prototypes
HALRESULT IOCOMPOSITE_Init(COMPOSITE_IODevice dev);
HALRESULT IOCOMPOSITE_Deinit(COMPOSITE_IODevice dev);
HALRESULT IOCOMPOSITE_EnableWrite(COMPOSITE_IODevice dev);
HALRESULT IOCOMPOSITE_DisableWrite(COMPOSITE_IODevice dev);
HALRESULT IOCOMPOSITE_EnableRead(COMPOSITE_IODevice dev);
HALRESULT IOCOMPOSITE_DisableRead(COMPOSITE_IODevice dev);
size_t IOCOMPOSITE_GetReadCount(COMPOSITE_IODevice dev);
size_t IOCOMPOSITE_GetWriteSpace(COMPOSITE_IODevice dev);
size_t IOCOMPOSITE_Read(COMPOSITE_IODevice dev, void* data, size_t size, unsigned int timeout);
size_t IOCOMPOSITE_Write(COMPOSITE_IODevice dev, const void* data, size_t size, unsigned int timeout);


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_Create
// -----------------------------------------------------------------------------
IODevice IOCOMPOSITE_Create(unsigned int max_associates)
{
	COMPOSITE_IODevice dev = NULL;

	dev = (COMPOSITE_IODevice)HEAP_Alloc(sizeof(struct COMPOSITE_IODeviceDesc));
	if (dev) {
		memset(dev, 0x00, sizeof(struct COMPOSITE_IODeviceDesc));
		dev->association = (IODevice*)HEAP_Alloc(max_associates*sizeof(IODevice));
		if (dev->association) {
			memset(dev->association, 0x00, max_associates*sizeof(IODevice));
			dev->cnt = max_associates;
			dev->iodev.Init = (IODeviceCtrlFunc)IOCOMPOSITE_Init;
			dev->iodev.Deinit = (IODeviceCtrlFunc)IOCOMPOSITE_Deinit;
			dev->iodev.EnableWrite = (IODeviceCtrlFunc)IOCOMPOSITE_EnableWrite;
			dev->iodev.EnableRead = (IODeviceCtrlFunc)IOCOMPOSITE_EnableRead;
			dev->iodev.DisableWrite = (IODeviceCtrlFunc)IOCOMPOSITE_DisableWrite;
			dev->iodev.DisableRead = (IODeviceCtrlFunc)IOCOMPOSITE_DisableRead;
			dev->iodev.GetReadCount = (IODeviceGetCountFunc)IOCOMPOSITE_GetReadCount;
			dev->iodev.GetWriteSpace = (IODeviceGetCountFunc)IOCOMPOSITE_GetWriteSpace;
			dev->iodev.Write = (IODeviceWriteFunc)IOCOMPOSITE_Write;
			dev->iodev.Read = (IODeviceReadFunc)IOCOMPOSITE_Read;
		} else {
			free(dev);
			dev = NULL;
		}
	}

	return (IODevice)dev;

} /* IOCOMPOSITE_Create */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_Destroy
// -----------------------------------------------------------------------------
void IOCOMPOSITE_Destroy(IODevice iodevice)
{
	COMPOSITE_IODevice dev;

	if (iodevice) {
		dev = (COMPOSITE_IODevice)iodevice;
		if (dev->association) {
			HEAP_Free(dev->association);
		}
		HEAP_Free(dev);
	}

} /* IOCOMPOSITE_Destroy */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_Init
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_Init(COMPOSITE_IODevice dev)
{
	
	return HALRESULT_OK;

} /* IOCOMPOSITE_Init */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_Deinit
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_Deinit(COMPOSITE_IODevice dev)
{
	
	return HALRESULT_OK;

} /* IOCOMPOSITE_Deinit */



// -----------------------------------------------------------------------------
//  IOCOMPOSITE_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_EnableWrite(COMPOSITE_IODevice dev)
{
	return HALRESULT_OK;

} /* IOCOMPOSITE_EnableWrite */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_EnableRead
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_EnableRead(COMPOSITE_IODevice dev)
{
	return HALRESULT_OK;

} /* IOCOMPOSITE_EnableRead */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_DisableWrite(COMPOSITE_IODevice dev)
{
	return HALRESULT_OK;

} /* IOCOMPOSITE_DisableWrite */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_DisableRead
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_DisableRead(COMPOSITE_IODevice dev)
{
	return HALRESULT_OK;

} /* IOCOMPOSITE_DisableRead */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_GetReadCount
// -----------------------------------------------------------------------------
size_t IOCOMPOSITE_GetReadCount(COMPOSITE_IODevice dev)
{	
	unsigned int i,cnt;

	if (dev) {
		for (i = 0; i < dev->cnt; i++) {
			if (dev->association[i]) {
				cnt = IODEV_GetReadCount(dev->association[i]);
				if (cnt) {
					return cnt;
				}
			}
		}
	}
	
	return 0;
	
} /* IOCOMPOSITE_GetReadCount */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_GetWriteSpace
// -----------------------------------------------------------------------------
size_t IOCOMPOSITE_GetWriteSpace(COMPOSITE_IODevice dev)
{
	return 1;
} /* IOCOMPOSITE_GetWriteSpace */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_ReadDirect
// -----------------------------------------------------------------------------
size_t IOCOMPOSITE_Read(COMPOSITE_IODevice dev, void* data, size_t size, unsigned int timeout)
{

    return 0;

} /* IOCOMPOSITE_ReadDirect */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_WriteDirect
// -----------------------------------------------------------------------------
size_t IOCOMPOSITE_Write(COMPOSITE_IODevice dev, const void* data, size_t size, unsigned int timeout)
{
	unsigned int i;

	if (dev) {
		for (i = 0; i < dev->cnt; i++) {
			if (dev->association[i]) {
				IODEV_Write(dev->association[i], data, size, timeout);
			}
		}

		return size;
	}

    return 0;

} /* IOCOMPOSITE_WriteDirect */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_SetAssociation
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_SetAssociation(IODevice iodevice, unsigned int _index, IODevice iodev)
{
	COMPOSITE_IODevice dev = (COMPOSITE_IODevice)iodevice;

	if (dev) {
		if ((_index >= 0) && (_index < dev->cnt)) {
			dev->association[_index] = iodev;
			return HALRESULT_OK;
		}
	}

    return HALRESULT_ERROR;

} /* IOCOMPOSITE_SetAssociation */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_ClearAssociation
// -----------------------------------------------------------------------------
HALRESULT IOCOMPOSITE_ClearAssociation(IODevice iodevice, unsigned int _index)
{
	COMPOSITE_IODevice dev = (COMPOSITE_IODevice)iodevice;

	if (dev) {
		if ((_index >= 0) && (_index < dev->cnt)) {
			dev->association[_index] = NULL;

			return HALRESULT_OK;
		}
	}

	return HALRESULT_ERROR;

} /* IOCOMPOSITE_ClearAssociation */


// -----------------------------------------------------------------------------
//  IOCOMPOSITE_GetAssociation
// -----------------------------------------------------------------------------
IODevice IOCOMPOSITE_GetAssociation(IODevice iodevice, unsigned int _index)
{
	COMPOSITE_IODevice dev = (COMPOSITE_IODevice)iodevice;

	if (dev) {
		if ((_index >= 0) && (_index < dev->cnt)) {
			return dev->association[_index];
		}
	}

	return NULL;

} /* IOCOMPOSITE_GetAssociation */

