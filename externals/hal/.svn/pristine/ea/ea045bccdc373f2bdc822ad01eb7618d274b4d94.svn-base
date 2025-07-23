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

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										stm32f4_cc

// frequency of external crystal
#define STM32_XTAL_FREQ							8000000
// frequency of external clock
#define STM32_EXT_FREQ							0
// frequency of internal RC oscillator
#define STM32_RC_FREQ							16000000

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
#define HALPORT_USE_USART1                      1
#define HALPORT_USART1_MODE                     HALPORT_USART_MODE_BUFFERED
#define HALPORT_USART1_DEFAULT_BAUDRATE         9600
#define HALPORT_USART1_ENABLE_POLLING_MODE      0
#define HALPORT_USART1_ENABLE_BUFFERED_MODE     1
#define HALPORT_USART1_ENABLE_EVENT_MODE        0
#define HALPORT_USART1_ENABLE_DMA_MODE          0
#define HALPORT_USART1_RXBUF_SIZE               1024
#define HALPORT_USART1_TXBUF_SIZE               1024
#define HALPORT_USART1_IRQ_PRE_PRIORITY			0
#define HALPORT_USART1_IRQ_SUB_PRIORITY			0

/// Port configuration
#define HALPORT_USE_USART2                      2
#define HALPORT_USART2_MODE                     HALPORT_USART_MODE_BUFFERED
#define HALPORT_USART2_DEFAULT_BAUDRATE         9600
#define HALPORT_USART2_ENABLE_POLLING_MODE      0
#define HALPORT_USART2_ENABLE_BUFFERED_MODE     1
#define HALPORT_USART2_ENABLE_EVENT_MODE        0
#define HALPORT_USART2_ENABLE_DMA_MODE          0
#define HALPORT_USART2_RXBUF_SIZE               1024
#define HALPORT_USART2_TXBUF_SIZE               1024
#define HALPORT_USART2_IRQ_PRE_PRIORITY			0
#define HALPORT_USART2_IRQ_SUB_PRIORITY			0

// -----------------------------------------------------------------------------
//  TIM MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 0, the TIM module will be enabled
#define HAL_ENABLE_TIM                          1

#define HAL_TIM_USE_TASK_EVENTS                 1
#define HAL_TIM_USE_INTERRUPT_EVENTS            1

#define TEST_TIM                                HAL_TIM9

#define HALPORT_USE_TIM2    					0
#define HALPORT_TIM2_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM2_MAX_TASK_EVENTS			0
#define HALPORT_TIM2_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM2_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM3						0
#define HALPORT_TIM3_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM3_MAX_TASK_EVENTS			0
#define HALPORT_TIM3_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM3_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM4						0
#define HALPORT_TIM4_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM4_MAX_TASK_EVENTS			0
#define HALPORT_TIM4_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM4_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM5						0
#define HALPORT_TIM5_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM5_MAX_TASK_EVENTS			0
#define HALPORT_TIM5_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM5_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM9						1
#define HALPORT_TIM9_MAX_INTERRUPT_EVENTS		4
#define HALPORT_TIM9_MAX_TASK_EVENTS			4
#define HALPORT_TIM9_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM9_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM10						0
#define HALPORT_TIM10_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM10_MAX_TASK_EVENTS			0
#define HALPORT_TIM10_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM10_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM11						0
#define HALPORT_TIM11_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM11_MAX_TASK_EVENTS			0
#define HALPORT_TIM11_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM11_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM12						0
#define HALPORT_TIM12_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM12_MAX_TASK_EVENTS			0
#define HALPORT_TIM12_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM12_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM13						0
#define HALPORT_TIM13_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM13_MAX_TASK_EVENTS			0
#define HALPORT_TIM13_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM13_IRQ_SUB_PRIORITY			0

#define HALPORT_USE_TIM14						0
#define HALPORT_TIM14_MAX_INTERRUPT_EVENTS		0
#define HALPORT_TIM14_MAX_TASK_EVENTS			0
#define HALPORT_TIM14_IRQ_PRE_PRIORITY			0
#define HALPORT_TIM14_IRQ_SUB_PRIORITY			0


// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS                           0

#endif /* HAL_CONFIG_H */
