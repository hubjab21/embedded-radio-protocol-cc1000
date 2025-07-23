/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_config.h
 Author:        Łukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's SPI module example
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
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

#define CC										sam3s_cc

// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										sam3s_cc

#define SAM3S_XTAL_FREQ							12000000

// if defined as 1, the CLK will apear on PA17 pin
#define HALPORT_USE_CLOCK_PIN					1

// -----------------------------------------------------------------------------
//  DELAY MODULE CONFIGURATION
// -----------------------------------------------------------------------------

// If defined as 1, the DELAY module will be enabled
#define HAL_ENABLE_DELAY						1

// To use delays loop, we must set AHB(HCLK) frequency here
#define HAL_F_CPU								12000000

// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO                         1

#define TEST_PIN_PORT							GPIOA
#define TEST_PIN_PIN							19
#define TEST_PIN_DEFAULT_CONFIG					GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define TEST_PIN2_PORT							GPIOA
#define TEST_PIN2_PIN							6
#define TEST_PIN2_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

#define CS_PIN_PORT							    GPIOA
#define CS_PIN_PIN							    16
#define CS_PIN_DEFAULT_CONFIG				    GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

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

/// Port configuration
#define HALPORT_USE_USART0                      0
#define HALPORT_USART0_MODE                     HALPORT_USART_MODE_BUFFERED
#define HALPORT_USART0_DEFAULT_BAUDRATE         9600
#define HALPORT_USART0_ENABLE_POLLING_MODE      0
#define HALPORT_USART0_ENABLE_BUFFERED_MODE     1
#define HALPORT_USART0_RXBUF_SIZE               1024
#define HALPORT_USART0_TXBUF_SIZE               1024
#define HALPORT_USART0_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART0_IRQ_SUB_PRIORITY		    0

/// Port configuration
#define HALPORT_USE_USART1                      1
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE         9600
#define HALPORT_USART1_ENABLE_POLLING_MODE      1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART1_RXBUF_SIZE               1024
#define HALPORT_USART1_TXBUF_SIZE               1024
#define HALPORT_USART1_IRQ_PRE_PRIORITY			0
#define HALPORT_USART1_IRQ_SUB_PRIORITY			0
#define HALPORT_USART1_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART1_IRQ_SUB_PRIORITY		    0

#define HALPORT_USE_UART0                      0
#define HALPORT_UART0_MODE                     HALPORT_USART_MODE_BUFFERED
#define HALPORT_UART0_DEFAULT_BAUDRATE         9600
#define HALPORT_UART0_ENABLE_POLLING_MODE      0
#define HALPORT_UART0_ENABLE_BUFFERED_MODE     1
#define HALPORT_UART0_RXBUF_SIZE               1024
#define HALPORT_UART0_TXBUF_SIZE               1024
#define HALPORT_UART0_IRQ_PRIORITY             4
#define HALPORT_UART0_IRQ_PRE_PRIORITY		   0
#define HALPORT_UART0_IRQ_SUB_PRIORITY		   0

//The handle of the iodevice used by the application
#define IO_SPI                                  IO_SPI1

#define HALPORT_USE_SPI1                        1
#define HALPORT_SPI1_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI1_DEFAULT_BAUDRATE           4000000
#define HALPORT_SPI1_MASTER_MODE				1   /* slave, master */
#define HALPORT_SPI1_ENABLE_POLLING_MODE        1
#define HALPORT_SPI1_ENABLE_BUFFERED_MODE       0
#define HALPORT_SPI1_DATASIZE                   8   /* 8bit, 16bit */
#define HALPORT_SPI1_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPI1_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE   /* (1st edge, 2nd edge) */
#define HALPORT_SPI1_RXBUF_SIZE                 1024
#define HALPORT_SPI1_TXBUF_SIZE                 1024
#define HALPORT_SPI1_IRQ_PRE_PRIORITY			0
#define HALPORT_SPI1_IRQ_SUB_PRIORITY			0


#define HALPORT_USE_SPIS1                        1
#define HALPORT_SPIS1_MODE                       HALPORT_SPI_MODE_SOFTWARE
#define HALPORT_SPIS1_DEFAULT_BAUDRATE           4000000
#define HALPORT_SPIS1_MASTER_MODE				 1   /* slave, master */
#define HALPORT_SPIS1_ENABLE_SOFT_MODE           1
#define HALPORT_SPIS1_DATASIZE                   8   /* 8bit, 16bit */
#define HALPORT_SPIS1_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPIS1_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE  /* (1st edge, 2nd edge) */
#define HALPORT_SPIS1_MSB_FIRST                  1
#define HALPORT_SPIS1_RXBUF_SIZE                 1024

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
