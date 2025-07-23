/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_spi_poll.c
 Author:        Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (SPI)
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_iodevice.h"
#include "hal_port_io_spi.h"


// function prototypes
HALRESULT HAL_PORT_SPI_POLL_Init(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_POLL_Deinit(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_POLL_EnableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_POLL_DisableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_POLL_EnableRead(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_POLL_DisableRead(SPI_IODevice dev);
size_t HAL_PORT_SPI_POLL_GetReadCount(SPI_IODevice dev);
size_t HAL_PORT_SPI_POLL_GetWriteSpace(SPI_IODevice dev);
size_t HAL_PORT_SPI_POLL_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_SPI_POLL_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout);


#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
struct SPI_IODeviceDesc io_spi1_poll = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_POLL_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_SPI_POLL_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_SPI_POLL_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_SPI_POLL_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_SPI_POLL_Read
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
#endif // HALPORT_USE_SPI1

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_Init(SPI_IODevice dev)
{
#if (defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0))
	if (dev == &io_spi1_poll) {

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

	    // Configure transfer delay
	    SPI_CSR0 &= ~(SPI_CSR_DLYBS_Msk | SPI_CSR_DLYBCT_Msk);
	    SPI_CSR0 |= SPI_CSR_DLYBS(0x40) | SPI_CSR_DLYBCT(0x10);
	#endif

	    // Configure SPCK I/O line (PA14)
	#if (HALPORT_SPI1_MASTER_MODE == 1)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
	#else
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_INPUT | GPIO_MODE_PERIPH_A);
		// CS PIN
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 11, GPIO_MODE_INPUT | GPIO_MODE_PERIPH_A);
	#endif

	    // Enable spi
	    SPI_CR = SPI_CR_SPIEN;
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_SPI_POLL_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_Deinit(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

		// Disable spi
		SPI_CR = SPI_CR_SPIDIS;

		// Disable peripheral clock
		PMC_PCDR0 = 1<<ID_SPI;

		// Disable  SPCK
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 14, GPIO_MODE_INPUT);
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	return  HALRESULT_OK;

} /* HAL_PORT_SPI_POLL_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_EnableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

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

	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
    return  HALRESULT_OK;

} /* HAL_PORT_SPI_POLL_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_DisableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

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

} /* HAL_PORT_SPI_POLL_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_EnableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

	#if (HALPORT_SPI1_MASTER_MODE == 1)
		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_INPUT);
		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
	#else
		// Configure SPI1 MOSI I/O line (PA13)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 13, GPIO_MODE_INPUT );
		// Configure SPI1 MISO I/O line (PA12)
		HAL_GPIO_PORT_ConfigurePin(GPIOA, 12, GPIO_MODE_OUTPUT | GPIO_MODE_PERIPH_A);
	#endif

	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	return  HALRESULT_OK;

} /* HAL_PORT_SPI_POLL_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_POLL_DisableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

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

} /* HAL_PORT_SPI_POLL_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_POLL_GetReadCount(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

		if (SPI_SR & SPI_SR_RDRF ) {
			return 1;
		}
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

	  return 0;

} /* HAL_PORT_SPI_POLL_GetReadCount */

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_POLL_GetWriteSpace(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)
	if (dev == &io_spi1_poll) {

		if (SPI_SR & SPI_SR_TDRE) {
				return 1;
		}
	}
#endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

	return 0;

} /* HAL_PORT_SPI_POLL_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_POLL_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout)
{
#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0) // All possible spi
	size_t i = size;

	 if (data) {
	 #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)


		if (dev == &io_spi1_poll) {
			while (i--) {
				while (0 == (SPI_SR & SPI_SR_RDRF)) {
					;
				}

				 // Get data from receive register
				*((uint16_t*)(data)) = (uint16_t)(SPI_RDR & SPI_RDR_RD_Msk);

					// Save data in buffer
					data = (void*)((size_t)data + 1);
				}
			return size;
			}


	 #endif // #if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

	} // if (data)

#endif//  #if defined all spi
	 return 0;

} /* HAL_PORT_SPI_POLL_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_POLL_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_POLL_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout)
{

#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0) // All possible spi
	uint16_t* ptr;
	size_t i;

	ptr = (uint16_t*)data;
	i = size;

	if (data) {

			if (dev == &io_spi1_poll) {
				while (i--) {
					// Wait until ready to be written
					while(0 == (SPI_SR & SPI_SR_TXEMPTY)){
						;
					}
					// Write word to output register
					SPI_TDR = SPI_TDR_TD(*ptr);



					ptr++;
				}

				return  size;
			}


	} // if (data)

#endif//  #if defined all spi
	return 0;

} /* HAL_PORT_SPI_POLL_Write */
