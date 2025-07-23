/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_iodevice.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IODevice API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


#ifndef HAL_IODEVICE_H
#define HAL_IODEVICE_H

#include <stdint.h>
#include <stddef.h>
#include <signal.h>
#include "hal_config.h"
#include "hal_defs.h"
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
#include "hal_os.h"
#endif

/** \defgroup hal_iodevice IODevice interface
 * 
 * The most important IO module interface is the <b>IODevice</b> interface. The application 
 * interacts with the IODevice objects. Each peripheral entity in use has it's own 
 * IODevice object instance but any of these objects provide a common, unified 
 * interface for sending and receiving data. For example, if there are two UARTs 
 * used on board of the microcontroller, there will be two IODevice instances present,
 * but they will all share a common API. The IODevice object basically acts as a data 
 * endpoint and bridge between periperals and application, but the application may
 * not care what type of underlying peripheral is in use, as long as it's sends/receives
 * the desired data. The IODevice functionality includes buffering of data, signalling
 * transaction events including transfer errors, utilizing DMA transfers. The IODevice API 
 * provides several functions, below is the complete list with short descriptions. 
 * <center>
 * <table>
 * <tr><td colspan = "2"> <center><b>Initialization</b></center> </td></tr>
 * <tr><td>\ref IODEV_Init          </td><td>  Initializes the IODevice</td></tr>
 * <tr><td>\ref IODEV_Deinit        </td><td>  Deinitializes the IODevice</td></tr>
 * 
 * <tr><td colspan = "2"> <center><b>Controlling flow of data</b></center> </td></tr>
 * <tr><td>\ref IODEV_EnableRead    </td><td>  Enables reception for the specified IODevice</td></tr>
 * <tr><td>\ref IODEV_EnableWrite   </td><td>  Enables transmission for the specified IODevice</td></tr>
 * <tr><td>\ref IODEV_DisableRead   </td><td>  Disables reception for the specified IODevice</td></tr>
 * <tr><td>\ref IODEV_DisableWrite  </td><td>  Disables transmission for the specified IODevice</td></tr>
 * 
 * <tr><td colspan = "2"> <center><b>Controlling state of transfer</b></center> </td></tr>
 * <tr><td>\ref IODEV_GetReadCount  </td><td>  Gets the amount of data available for reading in the IODevice</td></tr>
 * <tr><td>\ref IODEV_GetWriteSpace </td><td>  Gets the amount of free buffering space in the IODevice</td></tr>
 * 
 * <tr><td colspan = "2"> <center><b>Reading and writing</b></center> </td></tr>
 * <tr><td>\ref IODEV_Read          </td><td>  Reads data from IODevice</td></tr>
 * <tr><td>\ref IODEV_Write         </td><td>  Writes data to IODevice</td></tr>
 * 
 * <tr><td colspan = "2"> <center><b>Event handling</b></center> </td></tr>
 * <tr><td>\ref IODEV_SetReceiveEventHandler    </td><td>  Sets a handler for reception events</td></tr>
 * <tr><td>\ref IODEV_SetReceiveErrorHandler    </td><td>  Sets a handler for reception errors</td></tr>
 * <tr><td>\ref IODEV_SetTransmitEventHandler   </td><td>  Sets a handler for transmission events</td></tr>
 * <tr><td>\ref IODEV_SetTransmitErrorHandler   </td><td>  Sets a handler for transmission errors</td></tr>
 * </table> 
 * </center>
 *
 *  
 * <b>Using IODevices.</b>
 *
 * 
 *  
 * <b>Controlling the flow of data.</b>
 * 
 * Application can enable or disable the receive or transmit path for the IODevice. Disabling
 * the transmit path by calling \ref IODEV_DisableWrite results in no output from the
 * microcontroller. That means there is no data flow. However, it does not mean that 
 * application cannot write to the IODevice. The application can write to it as long as
 * there is enough buffering space. Application may check that space it by calling 
 * \ref IODEV_GetWriteSpace. This is particulary useful when the underlying driver supports
 * buffering, where data can be prepared before it is actually sent, especially if the 
 * preparing time is quite long.
 * When disabling the receive path by calling \ref IODEV_DisableRead, the external data 
 * will not be received any longer. However, the data that came before the disable call,
 * but have not been processed can still be read from the IODevice. The IODEV_GetReadCount
 * always shows how much data is left in the IODevice to read.  
 * 
 * <b>IO events.</b>
 * 
 * The application may be notified about several transfer events. This feature is useful
 * for synchronizing application tasks.
 */
/*@{*/


// -----------------------------------------------------------------------------
//  PUBLIC TYPEDEFS
// -----------------------------------------------------------------------------

// Definition of time type used in IO module
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
typedef OSTime IOTime;
#else
typedef unsigned int IOTime;
#endif

/**
 * Possible IODevice events
 */
typedef enum {
    IOEVENT_SINGLE_ELEMENT_RECEPTION,
    IOEVENT_SINGLE_ELEMENT_TRANSMISSION,
    IOEVENT_END_OF_TRANSMISSION,
    IOEVENT_END_OF_RECEPTION,
    IOEVENT_DATA_UNDERRUN,
    IOEVENT_DATA_OVERFLOW
} IOEventType;


#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
struct IONotifierDesc {
    OSSem  sem;
    size_t threshold;
};
#endif

typedef struct IODeviceDesc* IODevice;

struct IODeviceDesc {
    HALRESULT (*Init)(IODevice);
    HALRESULT (*Deinit)(IODevice);
    HALRESULT (*EnableWrite)(IODevice);
    HALRESULT (*DisableWrite)(IODevice);
    HALRESULT (*EnableRead)(IODevice);
    HALRESULT (*DisableRead)(IODevice);
    size_t (*GetReadCount)(IODevice);
    size_t (*GetWriteSpace)(IODevice);
    size_t (*Write)(IODevice, const void*, size_t, IOTime);
    size_t (*Read)(IODevice, void*, size_t, IOTime);
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
    size_t (*EventHandler)(IODevice, IOEventType, void* data, size_t size);
#endif
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
    OSMutex lock;
    struct IONotifierDesc rx_notifier;
    struct IONotifierDesc tx_notifier;
#endif
};

typedef HALRESULT (*IODeviceCtrlFunc)(IODevice);
typedef size_t (*IODeviceGetCountFunc)(IODevice);
typedef size_t (*IODeviceWriteFunc)(IODevice, const void*, size_t, IOTime);
typedef size_t (*IODeviceReadFunc)(IODevice, void*, size_t, IOTime);
typedef size_t (*IODeviceEventHandlerFunc)(IODevice, IOEventType, void* data, size_t size);


// -----------------------------------------------------------------------------
//  PUBLIC API
// -----------------------------------------------------------------------------

/**
 *  Initializes the hardware peripheral, represented by the the iodevice.
 *
 *  \param iodevice handle of the iodevice
*/
HALRESULT IODEV_Init(IODevice iodevice);

/**
 *  Deinitializes the hardware peripheral, associated with the iodevice.
 *
 *  \param iodevice handle of the iodevice
*/
HALRESULT IODEV_Deinit(IODevice iodevice);

/**
 *  Enables the transmit path.
 *
 *  \param iodevice handle of the iodevice
*/
#define IODEV_EnableWrite(iodevice)                     (iodevice)->EnableWrite((iodevice))

/**
 *  Disables the transmit path.
 *
 *  \param iodevice handle of the iodevice
*/
#define IODEV_DisableWrite(iodevice)                    (iodevice)->DisableWrite((iodevice))

/**
 *  Enables the receive path.
 *
 *  \param iodevice handle of the iodevice
*/
#define IODEV_EnableRead(iodevice)                      (iodevice)->EnableRead((iodevice))

/**
 *  Disables the receive path.
 *
 *  \param iodevice handle of the iodevice
*/
#define IODEV_DisableRead(iodevice)                     (iodevice)->DisableRead((iodevice))


/**
 *  Returns the number of bytes available for reading from the device. 
 *
 *  \param iodevice handle of the iodevice
 *  \return Numbers of bytes in read buffer
*/
#define IODEV_GetReadCount(iodevice)                    (iodevice)->GetReadCount((iodevice))

/**
 *  Returns the number of bytes that can be written to the device.
 *
 *  \param iodevice handle of the iodevice
 *  \return Number of bytes of free space in write buffer
*/
#define IODEV_GetWriteSpace(iodevice)                   (iodevice)->GetWriteSpace((iodevice))

/**
 *  Reads a specified number of elements from the iodevice.
 *
 *  \param iodevice handle of the iodevice
 *  \param data pointer to the location where data will be stored
 *  \param size size of data to read
 *  \param timeout timeout value (in miliseconds). This parameter is ignored and
 *  should be set to 0 when OS integration is disabled.
 *  \return Number of bytes read into the buffer
*/
#define IODEV_Read(iodevice, data, size, timeout)       (iodevice)->Read((iodevice), (data), (size), (timeout))

/**
 *  Writes a specified number of elements to the iodevice.
 *
 *  \param iodevice handle of the iodevice
 *  \param data pointer to the data to write
 *  \param size size of the data to write
 *  \param timeout timeout value (in miliseconds). This parameter is ignored and
 *  should be set to 0 when OS integration is disabled.
 *  \return Number of bytes written.
*/
#define IODEV_Write(iodevice, data, size, timeout)      (iodevice)->Write((iodevice), (data), (size), (timeout))

/**
 *  Blocks the calling task until a specified number of elements is received by IODevice
 *  or timeout occurs. Works in IO_INTEGRATION_MODE only!
 *  \param iodevice handle of the iodevice
 *  \param size number of elements to wait for
 *  \param timeout timeout value (in miliseconds)
 *  \return 1 if the specified amount of data was received in the specified time
 *         0 if timeout occurred before the specified amount of data was received
 */
size_t IODEV_WaitForData(IODevice iodevice, size_t size, IOTime timeout);

/**
 *  Locks access to a specified IODevice prohibiting concurrent access. This function
 *  is used to guard access to shared IODevice. After acquiring lock it must be released
 *  through a call to \ref IODEV_Unlock.
 *  This function requires HAL_IO_OS_INTEGRATION to be set to non-zero value in hal_config.h
 *
 *  \param iodevice handle of the iodevice
 *  \param timeout maximum time waiting for device
 *
 */
int IODEV_Lock(IODevice iodevice, unsigned int timeout);

/**
 *  Unlocks access to a specified IODevice re-enabling access to it.
 *  This function requires HAL_IO_OS_INTEGRATION to be set to non-zero value in hal_config.h
 *
 *  \param iodevice handle of the iodevice
 *
 */
void IODEV_Unlock(IODevice iodevice);

/*@}*/


#endif // HAL_IODEVICE_H
