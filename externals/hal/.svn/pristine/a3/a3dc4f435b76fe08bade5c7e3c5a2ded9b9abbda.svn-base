/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_spi.h
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

#ifndef HAL_PORT_SPI_H
#define HAL_PORT_SPI_H

#include "hal.h"
#include "hal_io.h"
#include "hal_iobuf.h"

#define HALPORT_SPI_MODE_POLLING              1
#define HALPORT_SPI_MODE_BUFFERED             2
#define HALPORT_SPI_MODE_SOFTWARE	          3

#define HALPORT_SPI_POLARITY_LOW              1
#define HALPORT_SPI_POLARITY_HIGH	          0

#define HALPORT_SPI_PHASE_1EDGE               0
#define HALPORT_SPI_PHASE_2EDGE               1


#ifndef HALPORT_USE_SPI1
#define HALPORT_USE_SPI1                        0
#define HALPORT_SPI1_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI1_DEFAULT_BAUDRATE           4000000
#define HALPORT_SPI1_MASTER_MODE				1    // master, slave
#define HALPORT_SPI1_ENABLE_POLLING_MODE        1
#define HALPORT_SPI1_ENABLE_BUFFERED_MODE       0
#define HALPORT_SPI1_DATASIZE                   8   //8bit, 16bit
#define HALPORT_SPI1_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   //low polarity, 	high polarity
#define HALPORT_SPI1_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE   // (1st edge, 2nd edge)
#define HALPORT_SPI1_RXBUF_SIZE                 1024
#define HALPORT_SPI1_TXBUF_SIZE                 1024
#define HALPORT_SPI1_IRQ_PRE_PRIORITY			0
#define HALPORT_SPI1_IRQ_SUB_PRIORITY			0

#endif

#ifndef SPIS1_CUSTOM_PINS
#define SPIS1_SCLK_PORT							GPIOA
#define SPIS1_SCLK_PIN							14
#define SPIS1_SCLK_DEFAULT_CONFIG				GPIO_MODE_OUTPUT| GPIO_MODE_PULL_UP
#define SPIS1_SCLK_DISABLE_CONFIG				GPIO_MODE_INPUT

#define SPIS1_MISO_PORT							GPIOA
#define SPIS1_MISO_PIN							12
#define SPIS1_MISO_DEFAULT_CONFIG				GPIO_MODE_INPUT| GPIO_MODE_PULL_UP
#define SPIS1_MISO_DISABLE_CONFIG				GPIO_MODE_INPUT

#define SPIS1_MOSI_PORT							GPIOA
#define SPIS1_MOSI_PIN							13
#define SPIS1_MOSI_DEFAULT_CONFIG				GPIO_MODE_OUTPUT| GPIO_MODE_PULL_UP
#define SPIS1_MOSI_DISABLE_CONFIG				GPIO_MODE_INPUT
#endif

#ifndef HALPORT_USE_SPIS1
#define HALPORT_USE_SPIS1						0
#define HALPORT_SPIS1_MODE                      HALPORT_SPI_MODE_SOFTWARE
#define HALPORT_SPIS1_DEFAULT_BAUDRATE          4000000
#define HALPORT_SPIS1_MASTER_MODE				1  /* master */
#define HALPORT_SPIS1_ENABLE_SOFT_MODE          1
#define HALPORT_SPIS1_DATASIZE                  8   /* 8bit, 16bit */
#define HALPORT_SPIS1_CLK_POLARITY              HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPIS1_CLK_PHASE                 HALPORT_SPI_PHASE_1EDGE   /* (1st edge, 2nd edge) */
#define HALPORT_SPIS1_MSB_FIRST                 1
#define HALPORT_SPIS1_RXBUF_SIZE				1024
#endif





// -----------------------------------------------------------------------------
//  Internal port declarations
// -----------------------------------------------------------------------------
struct SPI_IODeviceDesc {
    struct IODeviceDesc iodev;
    IOBuf tx_buf;
    IOBuf rx_buf;
};
typedef struct SPI_IODeviceDesc* SPI_IODevice;


// -----------------------------------------------------------------------------
//  IODevice object declarations
//  Only these should be used by the application code
// -----------------------------------------------------------------------------

#define IO_SPI1                               ((IODevice)io_spi1)
extern SPI_IODevice io_spi1;

// software SPI

#define IO_SPIS1                           	  ((IODevice)io_spiS1)
extern SPI_IODevice io_spiS1;

#endif /* HAL_PORT_SPI_H */
