/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_uart_buf.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
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

#if (HAL_IO_OS_INTEGRATION)
#include "hal_os.h"
#endif


// Function prototypes
HALRESULT HAL_PORT_UART_BUF_Init(UART_IODevice dev);
HALRESULT HAL_PORT_UART_BUF_Deinit(UART_IODevice dev);
HALRESULT HAL_PORT_UART_BUF_EnableWrite(UART_IODevice dev);
HALRESULT HAL_PORT_UART_BUF_DisableWrite(UART_IODevice dev);
HALRESULT HAL_PORT_UART_BUF_EnableRead(UART_IODevice dev);
HALRESULT HAL_PORT_UART_BUF_DisableRead(UART_IODevice dev);
size_t HAL_PORT_UART_BUF_GetReadCount(UART_IODevice dev);
size_t HAL_PORT_UART_BUF_GetWriteSpace(UART_IODevice dev);
size_t HAL_PORT_UART_BUF_Write(UART_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_UART_BUF_Read(UART_IODevice dev, void* data, size_t size, IOTime timeout);


#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

IOBUF_DECLARE(io_uart0_txbuf, HALPORT_UART0_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_uart0_rxbuf, HALPORT_UART0_RXBUF_SIZE, 1);

struct UART_IODeviceDesc io_uart0_buf = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_UART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_UART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_UART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_UART_BUF_Read
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
    .tx_buf = &io_uart0_txbuf,
    .rx_buf = &io_uart0_rxbuf
};
#endif // HALPORT_USE_UART0


#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

IOBUF_DECLARE(io_uart1_txbuf, HALPORT_UART1_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_uart1_rxbuf, HALPORT_UART1_RXBUF_SIZE, 1);

struct UART_IODeviceDesc io_uart1_buf = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_UART_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_UART_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_UART_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_UART_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_UART_BUF_Read
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
    .tx_buf = &io_uart1_txbuf,
    .rx_buf = &io_uart1_rxbuf
};
#endif // HALPORT_USE_UART1


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_Init(UART_IODevice dev)
{

#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Disable all interrupts
		UART0_IDR = 0xFFFFFFFF;

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

		// Enable interrupts
		HAL_PORT_NVIC_IRQInit(UART0_IRQn, HALPORT_UART0_IRQ_PRE_PRIORITY, HALPORT_UART0_IRQ_SUB_PRIORITY);

	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

	if (dev == &io_uart1_buf) {

		// Disable all interrupts
		UART0_IDR = 0xFFFFFFFF;

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

		// Enable interrupts
		HAL_PORT_NVIC_IRQInit(UART1_IRQn, HALPORT_UART1_IRQ_PRE_PRIORITY, HALPORT_UART1_IRQ_SUB_PRIORITY);

	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_Deinit(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

	if (dev == &io_uart0_buf) {

		// Disable interrupt
		HAL_PORT_NVIC_IRQDeinit(UART0_IRQn);
		// Disable baudrate clock
		UART0_BRGR = 0;

		// Disable receiver and transmitter
		UART0_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_UART0;

		// Clear buffer
		IOBUF_Clear(dev->rx_buf);
		IOBUF_Clear(dev->tx_buf);
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

	if (dev == &io_uart1_buf) {

		// Disable all interrupt
		HAL_PORT_NVIC_IRQDeinit(UART1_IRQn);

		// Disable baudrate clock
		UART1_BRGR = 0;

		// Dislable receiver and transmitter
		UART1_CR = US_CR_RXDIS | US_CR_TXDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_UART1;

		// Clear buffer
		IOBUF_Clear(dev->rx_buf);
		IOBUF_Clear(dev->tx_buf);

	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_EnableWrite(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Configure UTXD0 I/O line (PA10)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 10, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Enable transmitter
		UART0_CR = UART_CR_TXEN;

		if (IOBUF_GetCount(&io_uart0_txbuf)) {
			// There is some data waiting to be send - enable transmitter interrupt
			UART0_IER = UART_IER_TXRDY;
		}
	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_buf) {

		// Configure TXD1 I/O line (PB3)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 3, GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL | GPIO_MODE_PERIPH_A);

		// Enable transmitter
		UART1_CR = UART_CR_TXEN;

		if (IOBUF_GetCount(&io_uart1_txbuf)) {
			// There is some data waiting to be send - enable transmitter interrupt
			UART1_IER = UART_IER_TXRDY;
		}
	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_DisableWrite(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Disable interrupt
		UART0_IDR = UART_IDR_TXRDY;

		// Disable transmitter
		UART0_CR = UART_CR_TXDIS;

		//Configure TXD1 I/O line (PA10)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 10, GPIO_MODE_INPUT);
	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_buf) {

		// Disable interrupt
		UART1_IDR = UART_IDR_TXRDY;

		// Disable transmitter
		UART1_CR = UART_CR_TXDIS;

		// Configure TXD1 I/O line (PB3)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 3, GPIO_MODE_INPUT);
	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_EnableRead(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Configure URXD0 I/O line (PA9)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 9, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);

		// Enable receiver
		UART0_CR = UART_CR_RXEN;

		// Enable RX interrupt
		UART0_IER = UART_IER_RXRDY;
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_buf) {

		// Configure RXD1 I/O line (PB2)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 2, GPIO_MODE_INPUT | GPIO_MODE_PULL_UP);
		// Enable receiver
		UART1_CR = UART_CR_RXEN;

		// Enable RX interrupt
		UART1_IER = UART_IER_RXRDY;
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_UART_BUF_DisableRead(UART_IODevice dev)
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Disable RX interrupt
		UART0_IDR = UART_IDR_RXRDY;
		// Disable receiver
		UART0_CR = UART_CR_RXDIS;
		// Configure RXD0 I/O line (PA9)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 9, GPIO_MODE_INPUT);
	}
#endif

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_buf) {

		// Disable RX interrupt
		UART1_IDR = UART_IDR_RXRDY;

		// Enable receiver
		UART1_CR = UART_CR_RXDIS;

		// Configure RXD1 I/O line (PB2)
		HAL_GPIO_PORT_ConfigurePin(GPIOB, 2, GPIO_MODE_INPUT);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_UART_BUF_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_BUF_GetReadCount(UART_IODevice dev)
{
	return IOBUF_GetCount(dev->rx_buf);

} /* HAL_PORT_UART_BUF_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_BUF_GetWriteSpace(UART_IODevice dev)
{
	return IOBUF_GetSpace(dev->tx_buf);

} /* HAL_PORT_UART_BUF_GetWriteSpace */



// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_BUF_Read(UART_IODevice dev, void* data, size_t size, IOTime timeout)
{
    return IOBUF_Read(dev->rx_buf, data, size);

} /* HAL_PORT_UART_BUF_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_UART_BUF_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_UART_BUF_Write(UART_IODevice dev, const void* data, size_t size, IOTime timeout)
{

#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)
	if (dev == &io_uart0_buf) {

		// Write data to the transmit buffer
		size = IOBUF_Write(&io_uart0_txbuf, data, size);

		if (IOBUF_GetCount(&io_uart0_txbuf)) {
			// Some data was written successfully, enable TX interrupt to send it
			UART0_IER = UART_IER_TXRDY;
		}

	}
#endif // #if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0)

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)
	if (dev == &io_uart1_buf) {

		// Write data to the transmit buffer
		size = IOBUF_Write(&io_uart1_txbuf, data, size);

		if (IOBUF_GetCount(&io_uart1_txbuf)) {
			// Some data wass written successfully, enable TX interrupt to send it
			UART1_IER = UART_IER_TXRDY;
		}

	}
#endif // #if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0)

    return size;

} /* HAL_PORT_UART_BUF_Write */


// -----------------------------------------------------------------------------
//  UART0_IrqHandler
// -----------------------------------------------------------------------------
void UART0_IrqHandler()
{
#if defined HALPORT_USE_UART0 && (HALPORT_USE_UART0 != 0) && HALPORT_UART0_ENABLE_BUFFERED_MODE

	volatile uint8_t data;

	uint32_t sr = UART0_SR;

	if(sr & UART_SR_RXRDY){
		// Get data from UART register
		data = UART0_RHR;
		// Insert it into IOBuffer
		IOBUF_WriteFast(&io_uart0_rxbuf, (const void*)&data);
	}

	if (sr & UART_SR_TXRDY) {
		// Send data to UART
		if ((io_uart0->tx_buf) && (IOBUF_ReadFast(&io_uart0_txbuf, (void*)&data))) {
			// Got data from a buffer - send it
			UART0_THR = data;
		} else {
			// Disable interrupt
			UART0_IDR = UART_IDR_TXRDY;
		}
	}
#endif

} /* UART0_IrqHandler */


// -----------------------------------------------------------------------------
//  UART1_IrqHandler
// -----------------------------------------------------------------------------
void UART1_IrqHandler()
{

#if defined HALPORT_USE_UART1 && (HALPORT_USE_UART1 != 0) && HALPORT_UART1_ENABLE_BUFFERED_MODE

	volatile uint8_t data;

	uint32_t sr = UART1_SR;

	if (sr & UART_SR_RXRDY) {
		// Get data from UART register
		data = UART1_RHR;
		// Insert it into IOBuffer
		IOBUF_WriteFast(&io_uart1_rxbuf, (const void*)&data);

	}

	if (sr & UART_SR_TXRDY) {
		// Send data to UART
		if (IOBUF_ReadFast(&io_uart1_txbuf, (void*)&data)) {
			// Got data from a buffer - send it
			UART1_THR = data;
		} else {
			// Disable interrupt
			UART1_IDR = UART_IDR_TXRDY;
		}
	}


#endif

} /* UART1_IrqHandler */
