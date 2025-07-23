/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_uart_poll.c
 Author:        Lukasz Krzak
 Purpose:       HALFRED's SAM3S port
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (UART)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_iodevice.h"
#include "hal_port_io_uart.h"


// Function prototypes
HALRESULT HAL_PORT_UART_POLL_Init(UART_IODevice dev);
HALRESULT HAL_PORT_UART_POLL_Deinit(UART_IODevice dev);
HALRESULT HAL_PORT_UART_POLL_EnableWrite(UART_IODevice dev);
HALRESULT HAL_PORT_UART_POLL_DisableWrite(UART_IODevice dev);
HALRESULT HAL_PORT_UART_POLL_EnableRead(UART_IODevice dev);
HALRESULT HAL_PORT_UART_POLL_DisableRead(UART_IODevice dev);
size_t HAL_PORT_UART_POLL_GetReadCount(UART_IODevice dev);
size_t HAL_PORT_UART_POLL_GetWriteSpace(UART_IODevice dev);
size_t HAL_PORT_UART_POLL_Write(UART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_UART_POLL_Read(UART_IODevice dev, void* data, size_t size, IOTime timeout);

#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
struct UART_IODeviceDesc io_uart0_poll = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_UART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_UART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_UART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_UART_POLL_Read
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
    // port extensions:
    NULL,
    NULL
};
#endif // HALPORT_USE_UART0


#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
struct UART_IODeviceDesc io_uart1_poll = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_UART_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_UART_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_UART_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_UART_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_UART_POLL_Read
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
#endif // HALPORT_USE_UART1


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_Init(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// First reset and disable ALL
		UART0_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RSTSTA | UART_CR_RXDIS | UART_CR_TXDIS;

		// Disable PDC channel
		UART0_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_UART0;

		// Setup 8N1 transmission scheme
		UART0_MR =  UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO;

		// Calculate Baud rate
		UART0_BRGR = ((CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK))/(16*HALPORT_UART0_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// First reset and disable ALL
		UART1_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RSTSTA | UART_CR_RXDIS | UART_CR_TXDIS;

		// Disable PDC channel
		UART1_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_UART1;

		// Setup 8N1 transmission scheme
		UART1_MR =  UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO;

		// Calculate Baud rate
		UART1_BRGR = ((CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK))/(16*HALPORT_UART1_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_Deinit(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// Disable baudrate clock
		UART0_BRGR = 0;

		// Disable receiver and transmitter
		UART0_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_UART0;

	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// Disable baudrate clock
		UART1_BRGR = 0;

		// Disable receiver and transmitter
		UART1_CR = UART_CR_RXDIS | UART_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_UART1;
	}
#endif
	return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_EnableWrite(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// Configure UTXD0 I/O line (PA10)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 10, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Enable transmitter
		UART0_CR = UART_CR_TXEN;
	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// Configure TXD1 I/O line (PB3)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 3, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// enable transmitter
		UART1_CR = UART_CR_TXEN;
	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_DisableWrite(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// Disable transmitter
		UART0_CR = UART_CR_TXDIS;

		// Configure TXD1 I/O line (PA10)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 10, GPIO_MODE_INPUT);

	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// Disable transmitter
		UART1_CR = UART_CR_TXDIS;

		// Configure TXD1 I/O line (PB3)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 3, GPIO_MODE_INPUT);
	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_EnableRead(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// Configure URXD0 I/O line (PA9)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 9, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);
		// Enable receiver
		UART0_CR = UART_CR_RXEN;
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// Configure RXD1 I/O line (PB2)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 2, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Enable receiver
		UART1_CR = UART_CR_RXEN;
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_POLL_DisableRead(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		// Disable receiver
		UART0_CR = UART_CR_RXDIS;

		// Configure RXD0 I/O line (PA9)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 9, GPIO_MODE_INPUT);

	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		// Enable receiver
		UART1_CR = UART_CR_RXDIS;

		// Configure RXD1 I/O line (PB2)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 2, GPIO_MODE_INPUT);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_UART_POLL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_POLL_GetReadCount(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		if (UART0_SR & UART_SR_RXRDY) {
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		if (UART1_SR & UART_SR_RXRDY) {
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_UART_POLL_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_POLL_GetWriteSpace(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_poll) {

		if (UART0_SR & UART_SR_TXRDY) {
			return 1;
		}
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_poll) {

		if (UART1_SR & UART_SR_TXRDY) {
			return 1;
		}
	}
#endif

    return 0;

} /* HAL_PORT_UART_POLL_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_POLL_Read(UART_IODevice dev, void* data, size_t size, IOTime timeout)
{
#if (defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)) || (defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)) // All possible uart
    size_t i = size;

    if (data) {

	#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
			if (dev == &io_uart0_poll) {
				while (i--) {
					// Wait until US_RHR is ready to be read
					while (0 == (UART0_SR & UART_SR_RXRDY)) {
						;
					}
					// Read data
					*((uint8_t*)(data)) = (uint8_t)(UART0_RHR);
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
	#endif // HALPORT_USE_UART0

	#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
			if (dev == &io_uart1_poll) {
				while (i--) {
					// Wait until US_RHR is ready to be read
					while (0 == (UART1_SR & UART_SR_RXRDY)) {
						;
					}
					// Read data
					*((uint8_t*)(data)) = (uint8_t)(UART1_RHR);
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
	#endif // HALPORT_USE_UART1

	} // if (data)

#endif// HALPORT_USE all possible UART
    return 0;

} /* HAL_PORT_UART_POLL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_POLL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_POLL_Write(UART_IODevice dev, const void* data, size_t size, IOTime timeout)
{
#if (defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)) || (defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)) // All possible uart
    uint8_t* ptr;
    size_t i;
    ptr = (uint8_t*)data;
    i = size;

    if (data) {
	#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
			if (dev == &io_uart0_poll) {
				while (i--) {
					// Wait until US_THR is ready to be written
					while (0 == (UART0_SR & UART_SR_TXEMPTY)) {
						;
					}
					// Write data
					UART0_THR = *ptr;

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
	#endif // HALPORT_USE_UART0

	#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
			if (dev == &io_uart1_poll) {
				while (i--) {
					// Wait until US_THR is ready to be written
					while (0 == (UART1_SR & UART_SR_TXEMPTY)) {
						;
					}
					// Write data
					UART1_THR = *ptr;

				#if(HAL_IO_USE_EVENTS)
					// if declared - call EventHandler
					if (dev->iodev.EventHandler) {
						dev->iodev.EventHandler((IODevice)dev, IOEVENT_SINGLE_ELEMENT_TRANSMISSION, (void*)ptr, 1);
					}
				#endif

					ptr++;
				}

				return  size;
			}
	#endif // HALPORT_USE_UART1

	} // if (data)

#endif // HALPORT_USE all possible UART
    return 0;

} /* HAL_PORT_UART_POLL_Write */
