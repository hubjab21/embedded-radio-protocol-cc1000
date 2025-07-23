/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_spi_buf.c
 Author:        Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (SPI)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_iodevice.h"
#include "hal_port_io_spi.h"

#if (HAL_IO_OS_INTEGRATION)
#include "hal_os.h"
#endif

// Function prototypes
HALRESULT HAL_PORT_SPI_BUF_Init(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_BUF_Deinit(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_BUF_EnableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_BUF_DisableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_BUF_EnableRead(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_BUF_DisableRead(SPI_IODevice dev);
size_t HAL_PORT_SPI_BUF_GetReadCount(SPI_IODevice dev);
size_t HAL_PORT_SPI_BUF_GetWriteSpace(SPI_IODevice dev);
size_t HAL_PORT_SPI_BUF_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_SPI_BUF_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout);
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

IOBUF_DECLARE(io_spi1_txbuf, HALPORT_SPI1_TXBUF_SIZE, 1);
IOBUF_DECLARE(io_spi1_rxbuf, HALPORT_SPI1_RXBUF_SIZE, 1);

struct SPI_IODeviceDesc io_spi1_buf = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_BUF_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_SPI_BUF_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_SPI_BUF_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_SPI_BUF_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_SPI_BUF_Read
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
    .tx_buf = &io_spi1_txbuf,
    .rx_buf = &io_spi1_rxbuf
};
#endif // HALPORT_USE_SPI1

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_Init(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

		// Disable all interrupts
		SPI_IDR = 0xFFFFFFFF;

		// Enable peripheral clock
		PMC_PCER0 = 1ul << ID_SPI;

		// Disable spi
		SPI_CR = SPI_CR_SPIDIS;

		// Reset spi
		SPI_CR = SPI_CR_SWRST;

		#if (HALPORT_SPI1_MASTER_MODE == 1)
			// Master mode
			SPI_MR |= SPI_MR_MSTR;
		#else
			// Slave mode
			SPI_MR &= (~SPI_MR_MSTR);
		#endif

			// Disable fault detection
			SPI_MR |= SPI_MR_MODFDIS;

			// Disable chip select decode
			SPI_MR &= (~SPI_MR_PCSDEC);

			// Fixed peripheral select
			SPI_MR &= (~SPI_MR_PS);

			// Wait Data Read Before Transfer
			SPI_MR |= SPI_MR_WDRBT;

			// Clock polarity
		#if (HALPORT_SPI1_CLK_POLARITY == 1)
			SPI_CSR0 |= SPI_CSR_CPOL;
		#else
			SPI_CSR0 &= (~SPI_CSR_CPOL);
		#endif

			// Clock phase
		#if (HALPORT_SPI1_CLK_PHASE == 1)
			SPI_CSR0 |= SPI_CSR_NCPHA;
		#else
			SPI_CSR0 &= (~SPI_CSR_NCPHA);

		#endif

			 // Data frame format
			SPI_CSR0 &= (~SPI_CSR_BITS_Msk);
		#if (HALPORT_SPI1_DATASIZE == 16)
			SPI_CSR0 |=SPI_CSR_BITS_16_BIT;
		#else
		    SPI_CSR0 |=SPI_CSR_BITS_8_BIT;
		#endif

		#if (HALPORT_SPI1_MASTER_MODE == 1)
		    // Baud rate
		    SPI_CSR0 &= (~SPI_CSR_SCBR_Msk);
		    SPI_CSR0 |= SPI_CSR_SCBR((CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK))/(HALPORT_SPI1_DEFAULT_BAUDRATE));

		    // Configure transmissions delays
		    SPI_CSR0 &= ~(SPI_CSR_DLYBS_Msk | SPI_CSR_DLYBCT_Msk);
		    SPI_CSR0 |= SPI_CSR_DLYBS(0x40) | SPI_CSR_DLYBCT(0x10);
		#endif

		    // Configure SPCK I/O line (PA14) and NPCS0 I/O line (PA11)
		#if (HALPORT_SPI1_MASTER_MODE == 1)
			HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
		#else
			HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_INPUT | GPIO_MODE_PERIPH_A);

			// CS PIN
			HAL_GPIO_PORT_ConfigurePin(GPIOA, 11, GPIO_MODE_INPUT | GPIO_MODE_PERIPH_A);
		#endif
			// Enable interrupts
			HAL_PORT_NVIC_IRQInit(SPI_IRQn, HALPORT_SPI1_IRQ_PRE_PRIORITY, HALPORT_SPI1_IRQ_SUB_PRIORITY);

		    // Enable spi
		    SPI_CR = SPI_CR_SPIEN;
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_Deinit(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

		// Disable interrupt
		HAL_PORT_NVIC_IRQDeinit(SPI_IRQn);

		// Disable spi
		SPI_CR = SPI_CR_SPIDIS;
		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_SPI;
		// Disable  SPCK
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_INPUT);
		IOBUF_Clear(dev->rx_buf);
		IOBUF_Clear(dev->tx_buf);
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_EnableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

	#if (HALPORT_SPI1_MASTER_MODE == 1)

		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
	#else

		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT );
	#endif

		if (IOBUF_GetCount(&io_spi1_txbuf)) {

			// There is some data waiting to be send - enable transmitter interrupt
			SPI_IER =SPI_IER_TDRE;
		}
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_EnableWrite */

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_DisableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

		// Disable interrupt
		SPI_IDR = SPI_IDR_TDRE;

	#if (HALPORT_SPI1_MASTER_MODE == 1)

		// Disable SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT );
		// Disable SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
	#else

		// Disable SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
		// Disable SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
	#endif
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_DisableWrite */

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_EnableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

	#if (HALPORT_SPI1_MASTER_MODE == 1)

		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT );
		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
	#else

		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT );
		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
	#endif

// Enable RX interrupt
SPI_IER = SPI_IER_RDRF;

	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_BUF_DisableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

	// Disable RX interrupt
	SPI_IDR = SPI_IDR_RDRF;

	#if (HALPORT_SPI1_MASTER_MODE == 1)

		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT);
	#else

		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT);
		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
	#endif


	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	 return  HALRESULT_OK;

} /* HAL_PORT_SPI_BUF_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_BUF_GetReadCount(SPI_IODevice dev)
{
	return IOBUF_GetCount(dev->rx_buf);

} /* HAL_PORT_SPI_BUF_GetReadCount */

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_BUF_GetWriteSpace(SPI_IODevice dev)
{
	return IOBUF_GetSpace(dev->tx_buf);

} /* HAL_PORT_SPI_BUF_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_BUF_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout)
{
	// If master doesn't have all data in buffer
	if(size > IOBUF_GetCount(dev->rx_buf))
	{
		int i;
		for(i = 0; i < (size-IOBUF_GetCount(dev->rx_buf)); i++){

			uint16_t dummy = 0xffff;
			HAL_PORT_SPI_BUF_Write(dev, &dummy, 1, 0);
		}
	}

	return IOBUF_Read(dev->rx_buf, data, size);

} /* HAL_PORT_SPI_BUF_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_BUF_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_BUF_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_buf) {

		// Write data to the transmit buffer
		size = IOBUF_Write(&io_spi1_txbuf, data, size);

		if (IOBUF_GetCount(&io_spi1_txbuf)) {
			// Some data was written successfully, enable TX interrupt to send it
			SPI_IER = SPI_IER_TDRE;
		}

	}
	#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

	return size;

} /* HAL_PORT_SPI_BUF_Write */

// -----------------------------------------------------------------------------
//  SPI1_IrqHandler
// -----------------------------------------------------------------------------

void SPI1_IrqHandler()
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0) && HALPORT_SPI1_ENABLE_BUFFERED_MODE

	volatile uint16_t data;
	uint32_t sr = SPI_SR;

	if(sr & SPI_SR_RDRF){

		// Get data from SPI register
		data = (SPI_RDR & SPI_RDR_RD_Msk);
		// Insert it into IOBuffer
		IOBUF_WriteFast(&io_spi1_rxbuf, (const void*)&data);
	}

	if (sr & SPI_SR_TDRE){

		// Send data to SPI
		if ((io_spi1->tx_buf) && (IOBUF_ReadFast(&io_spi1_txbuf, (void*)&data))) {
			// Got data from a buffer - send it
			SPI_TDR = SPI_TDR_TD(data);
		} else {
			// Disable interrupt
			SPI_IDR = SPI_IDR_TDRE;
		}
	}

#endif

} /* SPI1_IrqHandler */
