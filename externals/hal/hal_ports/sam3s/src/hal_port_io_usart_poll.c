/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_usart_poll.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (USART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_iodevice.h"
#include "hal_port_io_usart.h"

// Function prototypes
HALRESULT HAL_PORT_USART_POLL_Init(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_Deinit(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_EnableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_DisableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_EnableRead(USART_IODevice dev);
HALRESULT HAL_PORT_USART_POLL_DisableRead(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_GetReadCount(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_GetWriteSpace(USART_IODevice dev);
size_t HAL_PORT_USART_POLL_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_USART_POLL_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout);

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
struct USART_IODeviceDesc io_usart0_poll = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_POLL_Read
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
        ,
        .EventHandler = NULL
#endif // HAL_IO_USE_EVENTS
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
        ,
        .lock = NULL,
        .rx_notifier = { NULL, 0 },
        .tx_notifier = { NULL, 0 }
#endif // HAL_IO_OS_INTEGRATION
    },
    // Port extensions:
    NULL,
    NULL
};
#endif // HALPORT_USE_USART0


#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
struct USART_IODeviceDesc io_usart1_poll = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_POLL_Read
#if defined HAL_IO_USE_EVENTS && (HAL_IO_USE_EVENTS != 0)
        ,
        .EventHandler = NULL
#endif // HAL_IO_USE_EVENTS
#if defined HAL_IO_OS_INTEGRATION && (HAL_IO_OS_INTEGRATION != 0)
        ,
        .lock = NULL,
        .rx_notifier = { NULL, 0 },
        .tx_notifier = { NULL, 0 }
#endif // HAL_IO_OS_INTEGRATION
    },
    // Port extensions:
    NULL,
    NULL
};
#endif // HALPORT_USE_USART1


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_Init(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// First reset ALL
		USART0_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_USART0;

		// Setup 8N1 transmission scheme
		USART0_MR =  US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL ;

		// Calculate Baud rate
		USART0_BRGR = ((CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK))/(16*HALPORT_USART0_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// First reset ALL
		USART1_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_USART1;

		// Setup 8N1 transmission scheme
		USART1_MR =  US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL ;

		// Calculate Baud rate
		USART1_BRGR = ((CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK))/(16*HALPORT_USART1_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_Deinit(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// disable baudrate clock
		USART0_BRGR = 0;

		// Disable receiver and transmitter
		USART0_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_USART0;

	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// Disable baudrate clock
		USART1_BRGR = 0;

		// Disable receiver and transmitter
		USART1_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_USART1;

	}
#endif
	return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_EnableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// Configure TXD1 I/O line (PA6)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 6, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Enable transmitter
		USART0_CR = US_CR_TXEN;
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// Configure TXD1 I/O line (PA22)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 22, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Configure nEN I/I line (PA23) -only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_UP );

		// Enable transmitter
		USART1_CR = US_CR_TXEN;
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_DisableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// Disable transmitter
		USART0_CR = US_CR_TXDIS;

		// Configure TXD1 I/O line (PA6)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 6, GPIO_MODE_INPUT);

	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// Disable transmitter
		USART1_CR = US_CR_TXDIS;

		// Configure TXD1 I/O line (PA22)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 22, GPIO_MODE_INPUT);

		// Disable nEN -only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_DOWN);
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_EnableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// Configure RXD1 I/O line (PA5)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 5, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Enable receiver
		USART0_CR = US_CR_RXEN;
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 21, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Enable receiver
		USART1_CR = US_CR_RXEN;

		// Configure nEN I/I line (PA23) -only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_UP );
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_POLL_DisableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		// Disable receiver
		USART0_CR = US_CR_RXDIS;

		// Configure RXD0 I/O line (PA5)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 5, GPIO_MODE_INPUT);

	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		// Disable receiver
		USART1_CR = US_CR_RXDIS;

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 21, GPIO_MODE_INPUT);

		// Disable nEN -only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_DOWN);

	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_POLL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_GetReadCount(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		if (USART0_CSR & US_CSR_RXRDY) {
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		if (USART1_CSR & US_CSR_RXRDY) {
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_USART_POLL_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_GetWriteSpace(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_poll) {

		if (USART0_CSR & US_CSR_TXRDY) {
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_poll) {

		if (USART1_CSR & US_CSR_TXRDY) {
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_USART_POLL_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout)
{
#if (defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)) || (defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)) // All possible USART
    size_t i = size;

    if (data) {

	#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
			if (dev == &io_usart0_poll) {
				while (i--) {
					// Wait until US_RHR is ready to be read
					while (0 == (USART0_CSR & US_CSR_RXRDY)) {
						;
					}
					// Read data
					*((uint8_t*)(data)) = (uint8_t)(USART0_RHR);
				#if(HAL_IO_USE_EVENTS)
					// If declared - call EventHandler
					if (dev->iodev.EventHandler) {
						dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_RECEPTION, (void*)data, 1);
					}

				#endif
					data = (void*)((size_t)data + 1);
				}
				return size;
			}
	#endif // HALPORT_USE_USART0

	#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
			if (dev == &io_usart1_poll) {
				while (i--) {
					// Wait until US_RHR is ready to be read
					while (0 == (USART1_CSR & US_CSR_RXRDY)) {
						;
					}
					// Read data
					*((uint8_t*)(data)) = (uint8_t)(USART1_RHR);
				#if(HAL_IO_USE_EVENTS)
					// If declared - call EventHandler
					if (dev->iodev.EventHandler) {
						dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_RECEPTION, (void*)data, 1);
					}

				#endif
					data = (void*)((size_t)data + 1);

				}
				return size;
			}
	#endif // HALPORT_USE_USART1

	} // if (data)

#endif// HALPORT_USE all possible usart
    return 0;

} /* HAL_PORT_USART_POLL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_POLL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_POLL_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout)
{
#if (defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)) || (defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)) // All possible USART
    uint8_t* ptr;
    size_t i;

    ptr = (uint8_t*)data;
    i = size;

    if (data) {
	#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
			if (dev == &io_usart0_poll) {
				while (i--) {
					// Wait until US_THR is ready to be written
					while (0 == (USART0_CSR & US_CSR_TXEMPTY)) {
						;
					}
					// Write data
					USART0_THR = *ptr;
				#if(HAL_IO_USE_EVENTS)

					// If declared - call EventHandler
					if (dev->iodev.EventHandler) {
						dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_TRANSMISSION, (void*)ptr, 1);
					}

				#endif
					ptr++;
				}

				return  size;
			}
	#endif // HALPORT_USE_USART0

	#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
			if (dev == &io_usart1_poll) {
				while (i--) {
					// Wait until US_THR is ready to be written
					while (0 == (USART1_CSR & US_CSR_TXEMPTY)) {
						;
					}
					// Write data
					USART1_THR = *ptr;

				#if(HAL_IO_USE_EVENTS)

					// If declared - call EventHandler
					if (dev->iodev.EventHandler) {
						dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_TRANSMISSION, (void*)ptr, 1);
					}

				#endif
					ptr++;
				}

				return  size;
			}
	#endif // HALPORT_USE_USART1

	} // if (data)

#endif// HALPORT_USE all possible usart
    return 0;

} /* HAL_PORT_USART_POLL_Write */
