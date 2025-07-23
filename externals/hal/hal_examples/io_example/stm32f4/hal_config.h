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

#define HAL_CORE_NVIC_PRIORITY_GROUP 			HAL_NVIC_PRIORITY_GROUP_2

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

// -----------------------------------------------------------------------------
//  DELAY MODULE CONFIGURATION
// -----------------------------------------------------------------------------

// If defined as 1, the DELAY module will be enabled
#define HAL_ENABLE_DELAY						0

// To use delays loop, we must set AHB(HCLK) frequency here
#define HAL_F_CPU								32000000

// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO                         1

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
#define HALPORT_USE_USART1                     	1
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE         9600
#define HALPORT_USART1_ENABLE_POLLING_MODE      0
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     1
#define HALPORT_USART1_RXBUF_SIZE               1024
#define HALPORT_USART1_TXBUF_SIZE               1024
#define HALPORT_USART1_IRQ_PRE_PRIORITY			0
#define HALPORT_USART1_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_USART2                      1
#define HALPORT_USART2_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART2_DEFAULT_BAUDRATE         9600
#define HALPORT_USART2_ENABLE_POLLING_MODE      0
#define HALPORT_USART2_ENABLE_BUFFERED_MODE     1
#define HALPORT_USART2_RXBUF_SIZE               2048
#define HALPORT_USART2_TXBUF_SIZE               2048
#define HALPORT_USART2_IRQ_PRE_PRIORITY			0
#define HALPORT_USART2_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_USART3                      0
#define HALPORT_USART3_MODE                     HALPORT_USART_MODE_POLLING
#define HALPORT_USART3_DEFAULT_BAUDRATE         9600
#define HALPORT_USART3_ENABLE_POLLING_MODE      1
#define HALPORT_USART3_ENABLE_BUFFERED_MODE     0
#define HALPORT_USART3_RXBUF_SIZE               1024
#define HALPORT_USART3_TXBUF_SIZE               1024
#define HALPORT_USART3_IRQ_PRE_PRIORITY			0
#define HALPORT_USART3_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_UART4                       1
#define HALPORT_UART4_MODE                      HALPORT_UART_MODE_POLLING
#define HALPORT_UART4_DEFAULT_BAUDRATE          9600
#define HALPORT_UART4_ENABLE_POLLING_MODE       1
#define HALPORT_UART4_ENABLE_BUFFERED_MODE      0
#define HALPORT_UART4_RXBUF_SIZE                1024
#define HALPORT_UART4_TXBUF_SIZE                1024
#define HALPORT_UART4_IRQ_PRE_PRIORITY			0
#define HALPORT_UART4_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_UART5                       1
#define HALPORT_UART5_MODE                      HALPORT_UART_MODE_POLLING
#define HALPORT_UART5_DEFAULT_BAUDRATE          9600
#define HALPORT_UART5_ENABLE_POLLING_MODE       1
#define HALPORT_UART5_ENABLE_BUFFERED_MODE      0
#define HALPORT_UART5_RXBUF_SIZE                1024
#define HALPORT_UART5_TXBUF_SIZE                1024
#define HALPORT_UART5_IRQ_PRE_PRIORITY			0
#define HALPORT_UART5_IRQ_SUB_PRIORITY			0

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
