/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_config.h
 Author:        Łukasz Duda
 Purpose:       HALFRED's IO module example
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

#define HAL_HEAP_MODE			                1

// Size of heap when HALFRED's internal heap manager is used (HAL_HEAP_MODE == 1 or 2)
#define HAL_HEAP_SIZE							 8*1024

#define HAL_HEAP_DEBUG							0

// -----------------------------------------------------------------------------
//  STACK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// Size reserved for stack 
#define HAL_STACK_SIZE							2048

// -----------------------------------------------------------------------------
//  CLK MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the CLK module will be enabled
#define HAL_ENABLE_CLK							1

#define CC										cc_efm32


// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the GPIO module will be enabled
#define HAL_ENABLE_GPIO							1

// For each GPIO pin you want to provide for your application, you should prepare
// at least 3 definitions, specifying port, pin and at least one configuration.
#define TEST_PIN_PORT							GPIOE
#define TEST_PIN_PIN							2
#define TEST_PIN_DEFAULT_CONFIG					GPIO_MODE_PUSH_PULL

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
#define IO_DEV									IO_UART1


#define HALPORT_USE_USART0						1
#define HALPORT_USART0_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART0_DEFAULT_BAUDRATE			9600
#define HALPORT_USART0_ENABLE_POLLING_MODE		1
#define HALPORT_USART0_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART0_RXBUF_SIZE				0
#define HALPORT_USART0_TXBUF_SIZE				0
#define HALPORT_USART0_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART0_IRQ_SUB_PRIORITY		    0
#define HALPORT_USART0_LOCATION					USART_ROUTE_LOCATION_LOC5
#define HALPORT_USART0_DATABITS					USART_FRAME_DATABITS_EIGHT
#define HALPORT_USART0_STOPBITS					USART_FRAME_STOPBITS_ONE
#define HALPORT_USART0_PARITY					USART_FRAME_PARITY_NONE
#define HALPORT_USART0_OVERSAMPLING				USART_CTRL_OVS_X16

#define HALPORT_USE_USART1						1
#define HALPORT_USART1_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART1_DEFAULT_BAUDRATE			9600
#define HALPORT_USART1_ENABLE_POLLING_MODE		1
#define HALPORT_USART1_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART1_RXBUF_SIZE				0
#define HALPORT_USART1_TXBUF_SIZE				0
#define HALPORT_USART1_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART1_IRQ_SUB_PRIORITY		    0
#define HALPORT_USART1_LOCATION					USART_ROUTE_LOCATION_LOC1
#define HALPORT_USART1_DATABITS					USART_FRAME_DATABITS_EIGHT
#define HALPORT_USART1_STOPBITS					USART_FRAME_STOPBITS_ONE
#define HALPORT_USART1_PARITY					USART_FRAME_PARITY_NONE
#define HALPORT_USART1_OVERSAMPLING				USART_CTRL_OVS_X16

#define HALPORT_USE_USART2						1
#define HALPORT_USART2_MODE						HALPORT_USART_MODE_POLLING
#define HALPORT_USART2_DEFAULT_BAUDRATE			9600
#define HALPORT_USART2_ENABLE_POLLING_MODE		1
#define HALPORT_USART2_ENABLE_BUFFERED_MODE		0
#define HALPORT_USART2_RXBUF_SIZE				0
#define HALPORT_USART2_TXBUF_SIZE				0
#define HALPORT_USART2_IRQ_PRE_PRIORITY		    0
#define HALPORT_USART2_IRQ_SUB_PRIORITY		    0
#define HALPORT_USART2_LOCATION					USART_ROUTE_LOCATION_LOC0
#define HALPORT_USART2_DATABITS					USART_FRAME_DATABITS_EIGHT
#define HALPORT_USART2_STOPBITS					USART_FRAME_STOPBITS_ONE
#define HALPORT_USART2_PARITY					USART_FRAME_PARITY_NONE
#define HALPORT_USART2_OVERSAMPLING				USART_CTRL_OVS_X16

#define HALPORT_USE_UART0                       1
#define HALPORT_UART0_MODE                      HALPORT_UART_MODE_POLLING
#define HALPORT_UART0_DEFAULT_BAUDRATE          9600
#define HALPORT_UART0_ENABLE_POLLING_MODE       1
#define HALPORT_UART0_ENABLE_BUFFERED_MODE      0
#define HALPORT_UART0_RXBUF_SIZE                0
#define HALPORT_UART0_TXBUF_SIZE                0
#define HALPORT_UART0_IRQ_PRE_PRIORITY			0
#define HALPORT_UART0_IRQ_SUB_PRIORITY			0
#define HALPORT_UART0_LOCATION					UART_ROUTE_LOCATION_LOC1
#define HALPORT_UART0_DATABITS					UART_FRAME_DATABITS_EIGHT
#define HALPORT_UART0_STOPBITS					UART_FRAME_STOPBITS_ONE
#define HALPORT_UART0_PARITY					UART_FRAME_PARITY_NONE
#define HALPORT_UART0_OVERSAMPLING				UART_CTRL_OVS_X16

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
#define HAL_ENABLE_TIM							0

// -----------------------------------------------------------------------------
//  OS MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------

// If defined as 1, the OS module will be enabled
#define HAL_ENABLE_OS							1

#endif /* HAL_CONFIG_H */
