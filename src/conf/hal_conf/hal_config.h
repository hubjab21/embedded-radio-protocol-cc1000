/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_config.h
 Author:        Lukasz Krzak
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

#define HAL_CORE_USE_SYSCLK_MANAGEMENT 1

// -----------------------------------------------------------------------------
//  HEAP MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Heap mode:
// 0 - use malloc/free
// 1 - use simplest table allocation (cannot free allocated memory)
// 2 - use block allocator
#define HAL_HEAP_MODE 1

// Size of heap when HALFRED's internal heap manager is used (HAL_HEAP_MODE == 1 or 2)
#define HAL_HEAP_SIZE 128

// Heap diagnostics
#define HAL_HEAP_DEBUG 0

// -----------------------------------------------------------------------------
//  STACK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Size reserved for stack
#define HAL_STACK_SIZE 128

// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO 1

// For each GPIO pin you want to provide for your application, you should prepare
// at least 3 definitions, specifying port, pin and at least one configuration.
#define LED0_PORT   GPIOC
#define LED0_PIN    3
#define LED0_OUTPUT GPIO_MODE_OUT_PP

#define LED1_PORT   GPIOC
#define LED1_PIN    2
#define LED1_OUTPUT GPIO_MODE_OUT_PP

#define LED2_PORT   GPIOC
#define LED2_PIN    1
#define LED2_OUTPUT GPIO_MODE_OUT_PP

#define LED3_PORT   GPIOC
#define LED3_PIN    0
#define LED3_OUTPUT GPIO_MODE_OUT_PP

#define PDATA_PORT   GPIOE
#define PDATA_PIN    3
#define PDATA_OUTPUT GPIO_MODE_OUT_PP
#define PDATA_INPUT  GPIO_MODE_IN

#define PCLK_PORT   GPIOE
#define PCLK_PIN    2
#define PCLK_OUTPUT GPIO_MODE_OUT_PP
#define PCLK_INPUT  GPIO_MODE_IN

#define PALE_PORT   GPIOE
#define PALE_PIN    4
#define PALE_OUTPUT GPIO_MODE_OUT_PP
#define PALE_INPUT  GPIO_MODE_IN

#define RFOUT_PORT   GPIOE
#define RFOUT_PIN    1
#define RFOUT_OUTPUT GPIO_MODE_OUT_PP

#define RFIN_PORT  GPIOE
#define RFIN_PIN   0
#define RFIN_INPUT GPIO_MODE_IN

// -----------------------------------------------------------------------------
//  DIAG MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the DIAG module will be enabled
#define HAL_ENABLE_DIAG 0

// If defined as 1, the DIAG module will use buffering
#define HAL_DIAG_USE_ERROR_BUFFERING 0

// This definition controlls how many errors will be buffered when DIAG
#define HAL_DIAG_ERROR_BUFFER_SIZE 0

// If defined as 1, the DIAG module will use error descriptions
#define HAL_DIAG_USE_ERROR_DESCRIPTIONS 0

// If defined as 1, the DIAG module will use error time stamps
#define HAL_DIAG_USE_ERROR_TIME_STAMPS 0

// If defined as 1, the DIAG module will output formatted data
#define HAL_DIAG_ERROR_SEND_AS_FORMATED_DATA 0

// -----------------------------------------------------------------------------
//  IO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the IO module will be enabled
#define HAL_ENABLE_IO 1

// If defined as 1, the OS integration mode will be enabled for IO operations
#define HAL_IO_OS_INTEGRATION 0

// If defined as 1, events in IO module will be enabled
#define HAL_IO_USE_EVENTS 0

/// The handle of the iodevice used by the application
#define IO_RADIO    IO_USART0
#define IO_TERMINAL IO_USART1

/// Port configuration
#define HALPORT_USE_USART0                  1
#define HALPORT_USART0_MODE                 HALPORT_USART_MODE_BUFFERED
#define HALPORT_USART0_DEFAULT_BAUDRATE     9600
#define HALPORT_USART0_ENABLE_POLLING_MODE  0
#define HALPORT_USART0_ENABLE_BUFFERED_MODE 1
#define HALPORT_USART0_ENABLE_EVENT_MODE    0
#define HALPORT_USART0_ENABLE_DMA_MODE      0
#define HALPORT_USART0_RXBUF_SIZE           32
#define HALPORT_USART0_TXBUF_SIZE           128

#define HALPORT_USE_USART1                  1
#define HALPORT_USART1_MODE                 HALPORT_USART_MODE_BUFFERED
#define HALPORT_USART1_DEFAULT_BAUDRATE     19200
#define HALPORT_USART1_ENABLE_POLLING_MODE  0
#define HALPORT_USART1_ENABLE_BUFFERED_MODE 1
#define HALPORT_USART1_ENABLE_EVENT_MODE    0
#define HALPORT_USART1_ENABLE_DMA_MODE      0
#define HALPORT_USART1_RXBUF_SIZE           32
#define HALPORT_USART1_TXBUF_SIZE           100

// -----------------------------------------------------------------------------
//  TIM MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the TIM module will be enabled
#define HAL_ENABLE_TIM 1

#define TIMER     HAL_TIM1
#define TIME_BASE 138888

#define HALPORT_USE_TIM1                  1
#define HALPORT_TIM1_MAX_INTERRUPT_EVENTS 4
#define HALPORT_TIM1_MAX_TASK_EVENTS      4

#define HALPORT_USE_TIM3                  1
#define HALPORT_TIM3_MAX_INTERRUPT_EVENTS 4
#define HALPORT_TIM3_MAX_TASK_EVENTS      4

// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS 0

// -----------------------------------------------------------------------------
//  CLI MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLI module will be enabled
#define HAL_ENABLE_CLI 1

#define CLI_CONSOLE_TITLE    "--== BSKS NODE CONSOLE ==--"
#define CLI_LEFT_MARGIN      3
#define CLI_COL_SEPARATION   35
#define CLI_NO_OF_COLUMNS    2
#define CLI_COMMAND_BUF_SIZE 127

#endif /* HAL_CONFIG_H */
