/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_ioperiph.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL IOPeripheral interface implementation
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_ioperiph.h"
#include "hal_core.h"

// -----------------------------------------------------------------------------
//  IOPERIPH_WaitForData
// -----------------------------------------------------------------------------
int IOPERIPH_WaitForData(IOPeripheral ioperipheral, size_t size, unsigned int timeout)
{
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
	// disable notification
	CORE_EnterCritical();
	ioperipheral->rx_notification_threshold = 0;
	CORE_ExitCritical();
	// make sure the semaphore is not taken
	if (OSSEM_Take(ioperipheral->rx_notification_sem, 0)) {
		;
	}
	// enable notification
	CORE_EnterCritical();
	ioperipheral->rx_notification_threshold = size;
	CORE_ExitCritical();

	// it is possible that at this point an ISR occurred and there is data in IOBuf,
	// available for reading, but the notification was not triggered
	// we must check that condition
	if (IOBUF_GetCount(ioperipheral->RXBuf) >= size) {
		// data is already in IOBuf
		// disable notification
		CORE_EnterCritical();
		ioperipheral->rx_notification_threshold = 0;
		CORE_ExitCritical();
		return 1;
	}
	// we must wait for data
	if (OSSEM_Take(ioperipheral->rx_notification_sem, timeout)) {
		// disable notification
		CORE_EnterCritical();
		ioperipheral->rx_notification_threshold = 0;
		CORE_ExitCritical();
		return 1;
	}
	return 0;
#else
	return 1;
#endif
} /* IOPERIPH_WaitForData */


/*! \file hal_ioperiph.c
    \brief HAL IOPeripheral interface implementation
 */
