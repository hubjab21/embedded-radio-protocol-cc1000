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

#if (HAL_IO_OS_INTEGRATION)
#include "hal_os.h"
#endif

// Function prototypes
HALRESULT HAL_PORT_USART_BUF_Init(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_Deinit(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_EnableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_DisableWrite(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_EnableRead(USART_IODevice dev);
HALRESULT HAL_PORT_USART_BUF_DisableRead(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_GetReadCount(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_GetWriteSpace(USART_IODevice dev);
size_t HAL_PORT_USART_BUF_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_USART_BUF_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout);


#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

IOBUF_DECLARE(io_usart0_txbuf, HALPORT_USART0_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_usart0_rxbuf, HALPORT_USART0_RXBUF_SIZE, 1);

struct USART_IODeviceDesc io_usart0_buf = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_BUF_Read
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
    .tx_buf = &io_usart0_txbuf,
    .rx_buf = &io_usart0_rxbuf
};
#endif // HALPORT_USE_USART0


#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

IOBUF_DECLARE(io_usart1_txbuf, HALPORT_USART1_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_usart1_rxbuf, HALPORT_USART1_RXBUF_SIZE, 1);

struct USART_IODeviceDesc io_usart1_buf = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_USART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_USART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_USART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_USART_BUF_Read
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
    .tx_buf = &io_usart1_txbuf,
    .rx_buf = &io_usart1_rxbuf
};
#endif // HALPORT_USE_USART1


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_Init(USART_IODevice dev)
{

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Disable all interrupts
		USART0_IDR = 0xFFFFFFFF;

		// Enable interrupts
		HAL_PORT_NVIC_IRQInit(USART0_IRQn, HALPORT_USART0_IRQ_PRE_PRIORITY, HALPORT_USART0_IRQ_SUB_PRIORITY);

		// First reset ALL
		USART0_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_USART0;

		// Setup 8N1 transmission scheme
		USART0_MR =  US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL ;

		// Calculate Baud rate
		USART0_BRGR = (CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/(16*HALPORT_USART0_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {

		// Disable all interrupts
		USART1_IDR = 0xFFFFFFFF;

		// Enable interrupts
		 HAL_PORT_NVIC_IRQInit(USART1_IRQn,HALPORT_USART1_IRQ_PRE_PRIORITY, HALPORT_USART1_IRQ_SUB_PRIORITY);

		// First reset ALL
		USART1_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RSTSTA;

		// Enable peripheral clock
		PMC_PCER0 = 1ul <<ID_USART1;

		// Setup 8N1 transmission scheme
		USART1_MR =  US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHRL_8_BIT | US_MR_PAR_NO | US_MR_NBSTOP_1_BIT | US_MR_CHMODE_NORMAL ;

		// Calculate Baud rate
		USART1_BRGR = (CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)/(16*HALPORT_USART1_DEFAULT_BAUDRATE));
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_Deinit(USART_IODevice dev)
{

#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Disable baudrate clock
		USART0_BRGR = 0;

		// Disable receiver and transmitter
		USART0_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_USART0;

		// Disable all interrupts
		HAL_PORT_NVIC_IRQDeinit(USART0_IRQn);

		// Clear buffer
		IOBUF_Clear(dev->rx_buf);
		IOBUF_Clear(dev->tx_buf);
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

	if (dev == &io_usart1_buf) {

		// Disable baudrate clock
		USART1_BRGR = 0;

		// Disable receiver and transmitter
		USART1_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_USART1;

		// Disable all interrupts
		HAL_PORT_NVIC_IRQDeinit(USART1_IRQn);

		// Clear buffer
		IOBUF_Clear(dev->rx_buf);
		IOBUF_Clear(dev->tx_buf);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_EnableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Configure TXD1 I/O line (PA6)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 6, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Enable transmitter
		USART0_CR = US_CR_TXEN;

		// Enable interrupt
		USART0_IER = US_IER_TXRDY;
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {
		// Configure TXD1 I/O line (PA22)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 22, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Configure nEN I/I line (PA23)-only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_UP );

		// Enable transmitter
		USART1_CR = US_CR_TXEN;

		// Enable interrupt
		USART1_IER = US_IER_TXRDY;
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_DisableWrite(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Disable transmitter
		USART0_CR = US_CR_TXDIS;

		// Configure TXD1 I/O line (PA22)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 6, GPIO_MODE_INPUT);
	}
#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {

		// Disable transmitter
		USART1_CR = US_CR_TXDIS;

		// Configure TXD1 I/O line (PA22)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 22, GPIO_MODE_INPUT);

		// Disable nEN -only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23,  GPIO_MODE_OUTPUT | GPIO_MODE_PULL_DOWN);
	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_EnableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 5, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Enable receiver
		USART0_CR = US_CR_RXEN;

		// Enable Rx interrupt
		USART0_IER = US_IER_RXRDY;
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 21, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Configure nEN I/I line (PA23)-only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_UP );

		// Enable receiver
		USART1_CR = US_CR_RXEN;

		// Enable Rx interrupt
		USART1_IER = US_IER_RXRDY;
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_USART_BUF_DisableRead(USART_IODevice dev)
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

		// Disable receiver
		USART0_CR = US_CR_RXDIS;

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 5, GPIO_MODE_INPUT);
	}
#endif

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {

		// Disable receiver
		USART1_CR = US_CR_RXDIS;

		// Configure RXD1 I/O line (PA21)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 21, GPIO_MODE_INPUT);

		// Disable nEN I/I line (PA23)-only use with sam3s ek board
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 23, GPIO_MODE_OUTPUT | GPIO_MODE_PULL_DOWN );

	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_USART_BUF_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_GetReadCount(USART_IODevice dev)
{
	return IOBUF_GetCount(dev->rx_buf);

} /* HAL_PORT_USART_BUF_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_GetWriteSpace(USART_IODevice dev)
{
	return IOBUF_GetSpace(dev->tx_buf);

} /* HAL_PORT_USART_BUF_GetWriteSpace */



// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_Read(USART_IODevice dev, void* data, size_t size, IOTime timeout)
{
    return IOBUF_Read(dev->rx_buf, data, size);

} /* HAL_PORT_USART_BUF_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_USART_BUF_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_USART_BUF_Write(USART_IODevice dev, const void* data, size_t size, IOTime timeout)
{
	if(dev){
		if(dev->tx_buf)
			size = IOBUF_Write(dev->tx_buf, data, size);
	}

	#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)
	if (dev == &io_usart0_buf) {

	    // Set interrupt flag
		USART0_IER = US_IER_TXRDY;

	}

#endif // #if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0)

#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)
	if (dev == &io_usart1_buf) {

	    // Set interrupt flag
		USART1_IER = US_IER_TXRDY;

	}
#endif // #if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0)

    return size;

} /* HAL_PORT_USART_BUF_Write */


// -----------------------------------------------------------------------------
//  USART0 data received interrupt handler
// -----------------------------------------------------------------------------
void USART0_IrqHandler()
{
#if defined HALPORT_USE_USART0 && (HALPORT_USE_USART0 != 0) && HALPORT_USART0_ENABLE_BUFFERED_MODE

	volatile uint8_t data;
	uint32_t sr = USART0_CSR;

	if(sr & US_CSR_RXRDY){
		// Get data from USART register
		data = USART0_RHR;
		// Insert it into IOBuffer
		IOBUF_WriteFast(&io_usart0_rxbuf, (const void*)&data);
	}

	if (sr & US_CSR_TXRDY) {
		// Send data to USART
		if ((io_usart0->tx_buf) && (IOBUF_ReadFast(&io_usart0_txbuf, (void*)&data))) {
			// Got data from a buffer - send it
	    	USART0_THR = data;
		}else{
			USART0_IDR = US_IDR_TXRDY;
		}
	}
#endif

}

// -----------------------------------------------------------------------------
//  USART1 data received interrupt handler
// -----------------------------------------------------------------------------
void USART1_IrqHandler()
{
#if defined HALPORT_USE_USART1 && (HALPORT_USE_USART1 != 0) && HALPORT_USART1_ENABLE_BUFFERED_MODE

	volatile uint8_t data;
	uint32_t sr = USART1_CSR;

	if(sr & US_CSR_RXRDY){
		// Get data from USART register
		data = USART1_RHR;
		// Insert it into IOBuffer
		IOBUF_WriteFast(&io_usart1_rxbuf, (const void*)&data);
	}

	if (sr & US_CSR_TXRDY) {
		// Send data to USART
			if (IOBUF_ReadFast(&io_usart1_txbuf, (void*)&data)) {
				// Got data from a buffer - send it
				USART1_THR = data;
			}else{
				USART1_IDR = US_IDR_TXRDY;
			}
	}


#endif
}
