/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_config.h
 Author:        Łukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's GPIO module example
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

#define HAL_CORE_USE_SYSCLK_MANAGEMENT			1

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
#define HAL_STACK_SIZE							512


// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										sam3s_cc
// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO							1

// For each GPIO pin you want to provide for your application, you should prepare
// at least 3 definitions, specifying port, pin and at least one configuration.
#define TEST_PIN_PORT							GPIOA
#define TEST_PIN_PIN							19
#define TEST_PIN_DEFAULT_CONFIG					GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL
#define TEST_PIN_PORT_MASK						0xFFFFFFFF
#define TEST_PIN_TRIGGER						GPIO_TRIGGER_EDGE_FALLING

#define TEST1_PIN_PORT							GPIOA
#define TEST1_PIN_PIN							20
#define TEST1_PIN_DEFAULT_CONFIG				GPIO_MODE_OUTPUT | GPIO_MODE_PUSH_PULL

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
//  DIAG MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the DIAG module will be enabled
#define HAL_ENABLE_DIAG							0

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
#define HAL_ENABLE_IO							0

// If defined as 1, the OS integration mode will be enabled for IO operations
#define HAL_IO_OS_INTEGRATION 					0

// If defined as 1, events in IO module will be enabled
#define HAL_IO_USE_EVENTS						0


/// The handle of the iodevice used by the application
#define IO_DIAG									IO_USART0
#define IO_DEV									IO_USART1

/// Port configuration
#define HALPORT_USE_USART0						1
#define HALPORT_USART0_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART0_DEFAULT_BAUDRATE			115200
#define HALPORT_USART0_ENABLE_POLLING_MODE		1
#define HALPORT_USART0_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART0_RXBUF_SIZE				100
#define HALPORT_USART0_TXBUF_SIZE				100
#define HALPORT_USART0_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART0_IRQ_SUB_PRIORITY		    0

#define HALPORT_USE_USART1						1
#define HALPORT_USART1_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE			115200
#define HALPORT_USART1_ENABLE_POLLING_MODE		1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART1_RXBUF_SIZE				0
#define HALPORT_USART1_TXBUF_SIZE				0
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
