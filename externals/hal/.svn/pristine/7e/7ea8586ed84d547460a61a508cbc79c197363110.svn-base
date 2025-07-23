/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_config.h
 Author:        Lukasz Duda, Michal Kochanowski
 Purpose:       HALFRED's
 Compiler:      %COMPILER%
 Hardware:      EFM32GG
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HALFRED configuration file
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

//  Note:
//  The HAL_ENABLE_xxx definitions control which HAL modules will be used by 
//  your application. You should enable only the modules you use, to avoid 
//  compilation of unnecessary code.

// -----------------------------------------------------------------------------
//  CORE MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

#define HAL_CORE_USE_SYSCLK_MANAGEMENT			1

// -----------------------------------------------------------------------------
//  HEAP MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

#define HAL_HEAP_MODE			                1

// Size of heap when HALFRED's internal heap manager is used (HAL_HEAP_MODE == 1 or 2)
#define HAL_HEAP_SIZE							1024

#define HAL_HEAP_DEBUG							0

// -----------------------------------------------------------------------------
//  STACK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Size reserved for stack 
#define HAL_STACK_SIZE							512

// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										cc_efm32

// -----------------------------------------------------------------------------
//  DELAY MODULE CONFIGURATION
// -----------------------------------------------------------------------------

// If defined as 1, the DELAY module will be enabled
#define HAL_ENABLE_DELAY						1

// To use delays loop, we must set AHB(HCLK) frequency here
#define HAL_F_CPU								14000000
// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO						1

#define SPI1_CUSTOM_PIN_NSS
#define CS_PIN_PORT							GPIOD
#define CS_PIN_PIN							3
#define CS_PIN_DEFAULT_CONFIG				GPIO_MODE_PUSH_PULL
#define CS_PIN_DISABLE_CONFIG				GPIO_MODE_DISABLED

//---------------------------------------------------
//  DIAG MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the DIAG module will be enabled
#define HAL_ENABLE_DIAG                         1

// If defined as 1, the DIAG module will use buffering
#define HAL_DIAG_USE_ERROR_BUFFERING            0

// This definition controlls how many errors will be buffered when DIAG
#define HAL_DIAG_ERROR_BUFFER_SIZE              0

// If defined as 1, the DIAG module will use error descriptions
#define HAL_DIAG_USE_ERROR_DESCRIPTIONS         0

// If defined as 1, the DIAG module will use error time stamps
#define HAL_DIAG_USE_ERROR_TIME_STAMPS          0

// If defined as 1, the DIAG module will output formatted data
#define HAL_DIAG_ERROR_SEND_AS_FORMATED_DATA    0
// -----------------------------------------------------------------------------
//  IO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the IO module will be enabled
#define HAL_ENABLE_IO							1

// If defined as 1, the OS integration mode will be enabled for IO operations
#define HAL_IO_OS_INTEGRATION 					0

// If defined as 1, events in IO module will be enabled
#define HAL_IO_USE_EVENTS						0


/// The handle of the iodevice used by the application
#define IO_DIAG									IO_UART1

#define IO_DEV1                          		IO_SPI1
#define IO_DEV2                                 IO_SPI2


#define HALPORT_USE_SPIS1						0
#define HALPORT_SPIS1_MODE                      HALPORT_SPI_MODE_SOFTWARE
#define HALPORT_SPIS1_DEFAULT_BAUDRATE          1000000
#define HALPORT_SPIS1_MASTER_MODE				1   /* slave, master */
#define HALPORT_SPIS1_DIRECTION                 0   /* FullDuplex, 1-wire */
#define HALPORT_SPIS1_ENABLE_POLLING_MODE       0
#define HALPORT_SPIS1_ENABLE_BUFFERED_MODE      0
#define HALPORT_SPIS1_ENABLE_SOFT_MODE          1
#define HALPORT_SPIS1_DATASIZE                  8   /* 8bit, 16bit */
#define HALPORT_SPIS1_CLK_POLARITY              1   /* low polarity, 	high polarity */
#define HALPORT_SPIS1_CLK_PHASE                 0   /* (1st edge, 2nd edge) */
#define HALPORT_SPIS1_MSB_FIRST                 1
#define HALPORT_SPIS1_RXBUF_SIZE				1024


#define HALPORT_USE_SPI1                        1
#define HALPORT_SPI1_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI1_DEFAULT_BAUDRATE           1000000 /* only Fpclk/{2,4,8,16,32,64,128,256} */
#define HALPORT_SPI1_MASTER_MODE				1   /* slave, master */
#define HALPORT_SPI1_DIRECTION                  0   /* FullDuplex, 1-wire */
#define HALPORT_SPI1_ENABLE_POLLING_MODE        1
#define HALPORT_SPI1_ENABLE_BUFFERED_MODE       1
#define HALPORT_SPI1_DATASIZE                   HALPORT_SPI_DATASIZE_8   /* 8bit, 16bit */
#define HALPORT_SPI1_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPI1_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE   /* (1st edge, 2nd edge) */
#define HALPORT_SPI1_MSB_FIRST                  HALPORT_SPI_MSB_FIRST
#define HALPORT_SPI1_RXBUF_SIZE                 1024
#define HALPORT_SPI1_TXBUF_SIZE                 1024
#define HALPORT_SPI1_IRQ_PRE_PRIORITY			0
#define HALPORT_SPI1_IRQ_SUB_PRIORITY			0
#define HALPORT_SPI1_LOCATION					SPI_ROUTE_LOCATION_LOC1


#define HALPORT_USE_SPI2                        1
#define HALPORT_SPI2_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI2_DEFAULT_BAUDRATE           1000000 /* only Fpclk/{2,4,8,16,32,64,128,256} */
#define HALPORT_SPI2_MASTER_MODE				0   /* slave, master */
#define HALPORT_SPI2_DIRECTION                  0   /* FullDuplex, 1-wire */
#define HALPORT_SPI2_ENABLE_POLLING_MODE        1
#define HALPORT_SPI2_ENABLE_BUFFERED_MODE       1
#define HALPORT_SPI2_DATASIZE                   HALPORT_SPI_DATASIZE_8  /* 8bit, 16bit */
#define HALPORT_SPI2_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPI2_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE   /* (1st edge, 2nd edge) */
#define HALPORT_SPI2_MSB_FIRST                  HALPORT_SPI_MSB_FIRST
#define HALPORT_SPI2_RXBUF_SIZE                 1024
#define HALPORT_SPI2_TXBUF_SIZE                 1024
#define HALPORT_SPI2_IRQ_PRE_PRIORITY			0
#define HALPORT_SPI2_IRQ_SUB_PRIORITY			0
#define HALPORT_SPI2_LOCATION					SPI_ROUTE_LOCATION_LOC0

#define HALPORT_USE_UART1                       1
#define HALPORT_UART1_MODE                      HALPORT_UART_MODE_POLLING
#define HALPORT_UART1_DEFAULT_BAUDRATE          9600
#define HALPORT_UART1_ENABLE_POLLING_MODE       1
#define HALPORT_UART1_ENABLE_BUFFERED_MODE      0
#define HALPORT_UART1_RXBUF_SIZE                0
#define HALPORT_UART1_TXBUF_SIZE                0
#define HALPORT_UART1_IRQ_PRE_PRIORITY			0
#define HALPORT_UART1_IRQ_SUB_PRIORITY			0
#define HALPORT_UART1_LOCATION					UART_ROUTE_LOCATION_LOC2
#define HALPORT_UART1_DATABITS					UART_FRAME_DATABITS_EIGHT
#define HALPORT_UART1_STOPBITS					UART_FRAME_STOPBITS_ONE
#define HALPORT_UART1_PARITY					UART_FRAME_PARITY_NONE
#define HALPORT_UART1_OVERSAMPLING				UART_CTRL_OVS_X16

// -----------------------------------------------------------------------------
//  TIM MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the TIM module will be enabled
// If defined as 0, the TIM module will be enabled
#define HAL_ENABLE_TIM                          0


// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS							0

#endif /* HAL_CONFIG_H */
