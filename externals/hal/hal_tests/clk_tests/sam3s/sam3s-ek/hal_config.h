/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_config.h
 Author:        Michal Kochanowski
 Purpose:       HALFRED's CLK module test
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

// Declare how many bits are used for preemption and subpriority part
#define HAL_CORE_NVIC_PRIORITY_GROUP   			HAL_NVIC_PRIORITY_GROUP_2

// -----------------------------------------------------------------------------
//  HEAP MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

#define HAL_HEAP_MODE			                0

// Size of heap when HALFRED's internal heap manager is used (HAL_HEAP_MODE == 1 or 2)
#define HAL_HEAP_SIZE							1024

#define HAL_HEAP_DEBUG							0

// -----------------------------------------------------------------------------
//  STACK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Size reserved for stack 
#define HAL_STACK_SIZE							1024

// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										sam3s_cc

#define SAM3S_XTAL_FREQ							12000000

#define HAL_CLK_CLOCK_ON_PIN 					1
// -----------------------------------------------------------------------------
//  DELAY MODULE CONFIGURATION
// -----------------------------------------------------------------------------

// If defined as 1, the DELAY module will be enabled
#define HAL_ENABLE_DELAY						0

// To use delays loop, we must set AHB(HCLK) frequency here
#define HAL_F_CPU								4000000

// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO							1

// For each GPIO pin you want to provide for your application, you should prepare
// at least 3 definitions, specifying port, pin and at least one configuration.

#define CLK_ON_PIN_MCK_PORT							GPIOA
#define CLK_ON_PIN_MCK_PIN							6
#define CLK_ON_PIN_MCK_CLK							MCK

#define CLK_ON_PIN_SLOW_PORT						GPIOA
#define CLK_ON_PIN_SLOW_PIN							17
#define CLK_ON_PIN_SLOW_CLK							SLOW_CLK

#define CLK_ON_PIN_MAIN_PORT						GPIOA
#define CLK_ON_PIN_MAIN_PIN							18
#define CLK_ON_PIN_MAIN_CLK							MAIN_CLK

// -----------------------------------------------------------------------------
//  DIAG MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the DIAG module will be enabled
#define HAL_ENABLE_DIAG							1

// If defined as 1, the DIAG module will use buffering
#define HAL_DIAG_USE_ERROR_BUFFERING			0

// This definition controls how many errors will be buffered when DIAG
#define HAL_DIAG_ERROR_BUFFER_SIZE				0

// If defined as 1, the DIAG module will use error descriptions
#define HAL_DIAG_USE_ERROR_DESCRIPTIONS			0

// If defined as 1, the DIAG module will use error time stamps
#define HAL_DIAG_USE_ERROR_TIME_STAMPS			0

// If defined as 1, the DIAG module will output formatted data
#define HAL_DIAG_ERROR_SEND_AS_FORMATED_DATA	0

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
#define IO_DIAG									IO_USART1

/// Port configuration
#define HALPORT_USE_USART1						1
#define HALPORT_USART1_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE			9600
#define HALPORT_USART1_ENABLE_POLLING_MODE		1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART1_RXBUF_SIZE				256
#define HALPORT_USART1_TXBUF_SIZE				256
#define HALPORT_USART1_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART1_IRQ_SUB_PRIORITY		    0

// -----------------------------------------------------------------------------
//  TIM MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the TIM module will be enabled
#define HAL_ENABLE_TIM							0

// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS							0

#endif /* HAL_CONFIG_H */
