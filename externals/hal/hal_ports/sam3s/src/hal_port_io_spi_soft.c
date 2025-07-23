/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_spi_soft.c
 Author:        Lukasz Duda, MIchał Kochanowski
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
HALRESULT HAL_PORT_SPI_SOFT_Init(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_SOFT_Deinit(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_SOFT_EnableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_SOFT_DisableWrite(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_SOFT_EnableRead(SPI_IODevice dev);
HALRESULT HAL_PORT_SPI_SOFT_DisableRead(SPI_IODevice dev);
size_t HAL_PORT_SPI_SOFT_GetReadCount(SPI_IODevice dev);
size_t HAL_PORT_SPI_SOFT_GetWriteSpace(SPI_IODevice dev);
size_t HAL_PORT_SPI_SOFT_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout);
size_t HAL_PORT_SPI_SOFT_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout);

#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

IOBUF_DECLARE(io_spiS1_rxbuf, HALPORT_SPIS1_RXBUF_SIZE, 1);

struct SPI_IODeviceDesc io_spiS1_soft = {
    // Base iodev IODevice struct:
    {
        .Init = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_Init,
        .Deinit = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_Deinit,
        .EnableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_EnableWrite,
        .DisableWrite = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_DisableWrite,
        .EnableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_EnableRead,
        .DisableRead = (IODeviceCtrlFunc)HAL_PORT_SPI_SOFT_DisableRead,
        .GetReadCount = (IODeviceGetCountFunc)HAL_PORT_SPI_SOFT_GetReadCount,
        .GetWriteSpace = (IODeviceGetCountFunc)HAL_PORT_SPI_SOFT_GetWriteSpace,
        .Write = (IODeviceWriteFunc)HAL_PORT_SPI_SOFT_Write,
        .Read = (IODeviceReadFunc)HAL_PORT_SPI_SOFT_Read
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
    // Pointer to SPIS1 registers
    NULL,
    // Port extensions:
    NULL,
    .rx_buf = &io_spiS1_rxbuf
};
#endif // HALPORT_USE_SPIS1

// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_Init
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_Init(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

	  // Configure sclk pin
	  HAL_GPIO_ConfigurePin(SPIS1_SCLK, DEFAULT_CONFIG);
	}
#endif

    return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_Init */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_Deinit
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_Deinit(SPI_IODevice dev)
{

#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

		// Disable SCLK pin
		HAL_GPIO_ConfigurePin(SPIS1_SCLK, DISABLE_CONFIG);

		// Clear buffer
		IOBUF_Clear(dev->rx_buf);
	}
#endif // #if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

	return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_Deinit */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_EnableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_EnableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

		// Configure SPIS1 MOSI
		HAL_GPIO_ConfigurePin(SPIS1_MOSI, DEFAULT_CONFIG);
		HAL_GPIO_ConfigurePin(SPIS1_MISO, DEFAULT_CONFIG);
	}
#endif // #if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_EnableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_DisableWrite
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_DisableWrite(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

		// Configure SPIS1 MOSI
		HAL_GPIO_ConfigurePin(SPIS1_MOSI, DISABLE_CONFIG);
		HAL_GPIO_ConfigurePin(SPIS1_MISO, DISABLE_CONFIG);
	}
#endif // #if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_DisableWrite */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_EnableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_EnableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

		// Configure SPIS1 MISO
		HAL_GPIO_ConfigurePin(SPIS1_MISO, DEFAULT_CONFIG);
		HAL_GPIO_ConfigurePin(SPIS1_MOSI, DEFAULT_CONFIG);

	}
#endif // #if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

	return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_EnableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_DisableRead
// -----------------------------------------------------------------------------
HALRESULT HAL_PORT_SPI_SOFT_DisableRead(SPI_IODevice dev)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

		// Configure SPIS1 MISO
		HAL_GPIO_ConfigurePin(SPIS1_MISO, DISABLE_CONFIG);
		HAL_GPIO_ConfigurePin(SPIS1_MOSI, DISABLE_CONFIG);
	}
#endif // #if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

    return  HALRESULT_OK;

} /* HAL_PORT_SPI_SOFT_DisableRead */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_GetReadCount
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_SOFT_GetReadCount(SPI_IODevice dev)
{
	return IOBUF_GetCount(dev->rx_buf);

} /* HAL_PORT_SPI_SOFT_GetReadCount */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_GetWriteSpace
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_SOFT_GetWriteSpace(SPI_IODevice dev)
{
	return 1;

} /* HAL_PORT_SPI_SOFT_GetWriteSpace */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_Read
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_SOFT_Read(SPI_IODevice dev, void* data, size_t size, IOTime timeout)
{
	// If master doesn't have all data in buffer
	if(size > IOBUF_GetCount(dev->rx_buf))
	{
		int i;
		for(i = 0; i < (size-IOBUF_GetCount(dev->rx_buf)); i++){

			uint16_t dummy = 0xffff;
			HAL_PORT_SPI_SOFT_Write(dev, &dummy, 1, 0);
		}
	}

	return IOBUF_Read(dev->rx_buf, data, size);

} /* HAL_PORT_SPI_SOFT_Read */


// -----------------------------------------------------------------------------
//  HAL_PORT_SPI_SOFT_Write
// -----------------------------------------------------------------------------
size_t HAL_PORT_SPI_SOFT_Write(SPI_IODevice dev, const void* data, size_t size, IOTime timeout)
{
#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)
	if (dev == &io_spiS1_soft) {

#if (HALPORT_SPIS1_DATASIZE == 16)
		uint16_t* ptr;
		uint16_t edge, data_in = 0;
		ptr = (uint16_t*)data;
#else
		uint8_t* ptr;
		uint8_t edge, data_in = 0;
		ptr = (uint8_t*)data;
#endif

		size_t i = size;

	    if (data) {
	        while (i) {

#if (HALPORT_SPIS1_DATASIZE == 16)
	        	edge = 16;
#else
	        	edge = 8;
#endif

#if (HALPORT_SPIS1_MSB_FIRST == 1)
				while(edge--){
#else
				uint16_t end = edge;
				edge = 0;
				while(edge < end){
#endif
					// Write word to output register
					if( (*ptr) & (1 << edge) ){
						HAL_GPIO_SetPinHigh(SPIS1_MOSI);
					}else{
						HAL_GPIO_SetPinLow(SPIS1_MOSI);
					}

#if (HALPORT_SPIS1_CLK_POLARITY == HALPORT_SPI_POLARITY_LOW)
					HAL_GPIO_SetPinLow(SPIS1_SCLK);
#else
					HAL_GPIO_SetPinHigh(SPIS1_SCLK);
#endif
					DELAY_US((1000000/HALPORT_SPIS1_DEFAULT_BAUDRATE)+1);

					if(HAL_GPIO_PORT_ReadPin(SPIS1_MISO_PORT, SPIS1_MISO_PIN)){
								data_in |= (1 << edge);
					}

#if (HALPORT_SPIS1_CLK_POLARITY == HALPORT_SPI_POLARITY_LOW)
					HAL_GPIO_SetPinHigh(SPIS1_SCLK);
#else
					HAL_GPIO_SetPinLow(SPIS1_SCLK);
#endif

#if (HALPORT_SPIS1_MSB_FIRST == 0)
					edge++;
#endif
				}

	            ptr++;
	            i--;

				IOBUF_WriteFast(&io_spiS1_rxbuf, (const void*)&data_in);
	        }

	        return  size;
	    }
    }
#endif

    return 0;

} /* HAL_PORT_SPI_SOFT_Write */
