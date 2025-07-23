/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_config.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's IO module example
 Compiler:      %COMPILER%
 Hardware:      STM32
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

#define HAL_CORE_USE_SYSCLK_MANAGEMENT          1


// -----------------------------------------------------------------------------
//  HEAP MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

#define HAL_HEAP_MODE                           1

// Size of heap when HALFRED's internal heap manager is used (HAL_HEAP_MODE == 1 or 2)
#define HAL_HEAP_SIZE                           8*1024

#define HAL_HEAP_DEBUG                          0

// -----------------------------------------------------------------------------
//  STACK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Size reserved for stack
#define HAL_STACK_SIZE                          1024

// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										stm32f4_cc

// frequency of external crystal
#define STM32_XTAL_FREQ							8000000
// frequency of 32k external crystal
#define STM32_XTAL32_FREQ						32768

// -----------------------------------------------------------------------------
//  DELAY MODULE CONFIGURATION
// -----------------------------------------------------------------------------

// If defined as 1, the DELAY module will be enabled
#define HAL_ENABLE_DELAY						1

// To use delays loop, we must set AHB(HCLK) frequency here
#define HAL_F_CPU								64000000

// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO                         1

#define LIS302DL_CS_PORT						GPIOE
#define LIS302DL_CS_PIN							3
#define LIS302DL_CS_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define X_AXIS_LOW_PORT							GPIOD
#define X_AXIS_LOW_PIN							13
#define X_AXIS_LOW_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define X_AXIS_HIGH_PORT						GPIOD
#define X_AXIS_HIGH_PIN							15
#define X_AXIS_HIGH_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define Y_AXIS_LOW_PORT							GPIOD
#define Y_AXIS_LOW_PIN							12
#define Y_AXIS_LOW_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define Y_AXIS_HIGH_PORT						GPIOD
#define Y_AXIS_HIGH_PIN							14
#define Y_AXIS_HIGH_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define LIS302DL_INT1_PORT						GPIOE
#define LIS302DL_INT1_PIN						0
#define LIS302DL_INT1_DEFAULT_CONFIG			GPIO_MODE_INPUT | GPIO_MODE_PULL_DOWN


// -----------------------------------------------------------------------------
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
#define HAL_ENABLE_IO                           1

// If defined as 1, the OS integration mode will be enabled for IO operations
#define HAL_IO_OS_INTEGRATION                   0

// If defined as 1, events in IO module will be enabled
#define HAL_IO_USE_EVENTS                       0


/// The handle of the iodevice used by the application
#define IO_DEV                                  IO_USART1

#define IO_SPI									IO_SPI1

#define HALPORT_USE_SPI1                        1
#define HALPORT_SPI1_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI1_DEFAULT_BAUDRATE           1000000 /* only Fpclk/{2,4,8,16,32,64,128,256} */
#define HALPORT_SPI1_MASTER_MODE			    1   /* slave, master */
#define HALPORT_SPI1_DIRECTION                  0   /* FullDuplex, 1-wire */
#define HALPORT_SPI1_ENABLE_POLLING_MODE        1
#define HALPORT_SPI1_ENABLE_BUFFERED_MODE       0
#define HALPORT_SPI1_ENABLE_SOFT_MODE           0
#define HALPORT_SPI1_DATASIZE                   8   /* 8bit, 16bit */
#define HALPORT_SPI1_CLK_POLARITY               HALPORT_SPI_POLARITY_HIGH
#define HALPORT_SPI1_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE
#define HALPORT_SPI1_MSB_FIRST                  1

/// Port configuration
#define HALPORT_USE_USART1                     	1
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE         115200
#define HALPORT_USART1_ENABLE_POLLING_MODE      1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART1_ENABLE_EVENT_MODE        0
#define HALPORT_USART1_ENABLE_DMA_MODE          0
#define HALPORT_USART1_RXBUF_SIZE               1024
#define HALPORT_USART1_TXBUF_SIZE               1024
#define HALPORT_USART1_IRQ_PRE_PRIORITY			0
#define HALPORT_USART1_IRQ_SUB_PRIORITY			0


// -----------------------------------------------------------------------------
//  IO DEVICES (for multipli SPI) SECTION
// -----------------------------------------------------------------------------

#define LIS302DL_SENSOR1_IO						IO_SPI
#define LIS302DL_SENSOR1_CS						LIS302DL_CS

// -----------------------------------------------------------------------------
//  IOBUS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the IOBUS module will be enabled
#define HAL_ENABLE_IOBUS                        0

// -----------------------------------------------------------------------------
//  TIM MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the TIM module will be enabled
#define HAL_ENABLE_TIM                          0

// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS                           0

#endif /* HAL_CONFIG_H */
