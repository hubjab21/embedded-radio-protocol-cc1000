/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_io_virtual.h
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

#ifndef HAL_PORT_IO_VIRTUAL_H
#define HAL_PORT_IO_VIRTUAL_H

#include "hal.h"


/**
 * \page UNIVERSAL_ioloopback_page loopback IODevice
 *
 * <b>Overview.</b>
 *
 * The loopback IODevice buffers data that is written to it, and provides it back
 * as received data. It is designed mainly for testing purposes.
 *
 * <b>Creating and destroying file-based IODevices.</b>
 *
 * All loopback IODevice objects are created at runtime, by a call to \ref
 * HAL_PORT_LOOPBACK_Create function. This call allocates memory for a new IODevice
 * descriptor (plus additional memory for data buffer). Such IODevice is then ready
 * to operate as a regular IODevice object. When done using, all file-based IODevices
 * should be destroyed to free allocated memory, by a call to \ref HAL_PORT_LOOPBACK_Destroy
 * function.
 *
 * <b>Using loopback IODevices.</b>
 *
 * TODO
 */

/**
 * \addtogroup universal Universal components
 */
/*@{*/


/**
 * Creates a new virtual IODevice.
 * \param buf_size size of the data buffer (in bytes)
 * \return new virtual IODevice or NULL if creation failed
 */
IODevice HAL_PORT_IOVIRTUAL_Create(size_t buf_size, int number_of_gates);

/**
 * Destroys a virtual IODevice and frees all memory allocated for it.
 * Note, that this function should NOT be used to free other types of IODevices.
 * \param iodevice virtual IODevice
 */
void HAL_PORT_IOVIRTUAL_Destroy(IODevice iodevice);

HALRESULT HAL_PORT_IOVIRTUAL_Pair(IODevice iodev1, int gate1, IODevice iodev2, int gate2); 

/*@}*/


#endif /* HAL_PORT_IO_VIRTUAL_H */
