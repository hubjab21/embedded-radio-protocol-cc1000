/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_iodevice.c
 Author:        Łukasz Krzak, Dominik Rzepka
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IODevice interface
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"


// -----------------------------------------------------------------------------
//  IODEV_Init
// -----------------------------------------------------------------------------
HALRESULT IODEV_Init(IODevice iodevice)
{
    HALRESULT result = HALRESULT_ERROR;

    if (iodevice) {
        if (iodevice->Init) {
            result = iodevice->Init(iodevice);
        }

#if (HAL_IO_OS_INTEGRATION)
		if (HALRESULT_OK == result) {
			// in OS INTEGRATION MODE, create synchronization semaphores for transmission notification
			iodevice->rx_notifier.threshold = 0;
			iodevice->rx_notifier.sem = OSSEM_Create();

			if (iodevice->rx_notifier.sem == NULL) {
				IODEV_Deinit(iodevice);
				return HALRESULT_OSSEM_CREATION_FAILED;
			}

			iodevice->tx_notifier.threshold = 0;
			iodevice->tx_notifier.sem = OSSEM_Create();

			if (iodevice->tx_notifier.sem == NULL) {
				OSSEM_Destroy(iodevice->rx_notifier.sem);
				IODEV_Deinit(iodevice);
				return HALRESULT_OSSEM_CREATION_FAILED;
			}
		}
#endif

    }

    return result;

} /* IODEV_Init */


// -----------------------------------------------------------------------------
//  IODEV_Deinit
// -----------------------------------------------------------------------------
HALRESULT IODEV_Deinit(IODevice iodevice)
{
    HALRESULT result = HALRESULT_ERROR;

    if (iodevice) {
        if (iodevice->Deinit) {
            result = iodevice->Deinit(iodevice);
        }

#if (HAL_IO_OS_INTEGRATION)

        // in OS INTEGRATION MODE, destroy synchronization semaphores
        if (iodevice->rx_notifier.sem != NULL) {
            OSSEM_Destroy(iodevice->rx_notifier.sem);
            iodevice->rx_notifier.sem = NULL;
        }

        if (iodevice->tx_notifier.sem != NULL) {
            OSSEM_Destroy(iodevice->tx_notifier.sem);
            iodevice->tx_notifier.sem = NULL;
        }

#endif
    }

    return result;

} /* IODEV_Deinit */


// -----------------------------------------------------------------------------
//  IODEV_Lock
// -----------------------------------------------------------------------------
int IODEV_Lock(IODevice iodevice, unsigned int timeout)
{
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)

    if (iodevice) {
        if (NULL == iodevice->lock) {
            // first call to IODEV_Lock must create the semaphore
            iodevice->lock = OSMUTEX_Create();
        }

        if (iodevice->lock) {
            return OSMUTEX_Take(iodevice->lock, timeout);
        }
    }

    return 1;

#endif

    return 0;

} /* IODEV_Lock */


// -----------------------------------------------------------------------------
//  IODEV_Unlock
// -----------------------------------------------------------------------------
void IODEV_Unlock(IODevice iodevice)
{
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)

    if (iodevice) {
        if (iodevice->lock) {
            OSMUTEX_Give(iodevice->lock);
        }
    }

#endif

} /* IODEV_Unlock */


// -----------------------------------------------------------------------------
//  IODEV_WaitForData
// -----------------------------------------------------------------------------
size_t IODEV_WaitForData(IODevice iodevice, size_t size, IOTime timeout)
{
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
    // disable notification
    CORE_EnterCritical();
    iodevice->rx_notifier.threshold = 0;
    CORE_ExitCritical();

    // make sure the semaphore is not taken
    if (OSSEM_Take(iodevice->rx_notifier.sem, 0)) {
        ;
    }

    // enable notification
    CORE_EnterCritical();
    iodevice->rx_notifier.threshold = size;
    CORE_ExitCritical();

    // it is possible that at this point an ISR occurred and there is data in device,
    // available for reading, but the notification was not triggered
    // we must check that condition
    if (iodevice->GetReadCount(iodevice) >= size) {
        // data is already in device
        // disable notification
        CORE_EnterCritical();
        iodevice->rx_notifier.threshold = 0;
        CORE_ExitCritical();
        return size;
    }

    // we must wait for data
    if (0 == OSSEM_Take(iodevice->rx_notifier.sem, timeout)) {
        // got data!
        // disable notification
        CORE_EnterCritical();
        iodevice->rx_notifier.threshold = 0;
        CORE_ExitCritical();
        return size;
    }

    // unable to get notification
    // disable notification
    CORE_EnterCritical();
    iodevice->rx_notifier.threshold = 0;
    CORE_ExitCritical();
    return iodevice->GetReadCount(iodevice);
#else
    return iodevice->GetReadCount(iodevice);
#endif
} /* IODEV_WaitForData */


/*! \file hal_iodevice.c
    \brief HAL IODevice class definition

 */

