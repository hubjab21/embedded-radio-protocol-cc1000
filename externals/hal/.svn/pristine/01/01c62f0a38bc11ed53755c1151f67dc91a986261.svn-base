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

#define HAL_CORE_USE_SYSCLK_MANAGEMENT

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

#define CC										cc_efm32



// -----------------------------------------------------------------------------
//  GPIO MODULE CONFIGURATION SECTION
// -----------------------------------------------------------------------------
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
#define IO_DIAG									IO_UART1
#define IO_DEV1                          		IO_SPI1
#define IO_DEV2                                 IO_SPI2

#define HALPORT_USE_SPI1                        1
#define HALPORT_SPI1_MODE                       HALPORT_SPI_MODE_POLLING
#define HALPORT_SPI1_DEFAULT_BAUDRATE           1000000 /* only Fpclk/{2,4,8,16,32,64,128,256} */
#define HALPORT_SPI1_MASTER_MODE				1   /* slave, master */
#define HALPORT_SPI1_DIRECTION                  0   /* FullDuplex, 1-wire */
#define HALPORT_SPI1_ENABLE_POLLING_MODE        1
#define HALPORT_SPI1_ENABLE_BUFFERED_MODE       0
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
#define HALPORT_SPI2_ENABLE_BUFFERED_MODE       0
#define HALPORT_SPI2_DATASIZE                   HALPORT_SPI_DATASIZE_8  /* 8bit, 16bit */
#define HALPORT_SPI2_CLK_POLARITY               HALPORT_SPI_POLARITY_LOW   /* low polarity, 	high polarity */
#define HALPORT_SPI2_CLK_PHASE                  HALPORT_SPI_PHASE_1EDGE   /* (1st edge, 2nd edge) */
#define HALPORT_SPI2_MSB_FIRST                  HALPORT_SPI_MSB_FIRST
#define HALPORT_SPI2_RXBUF_SIZE                 1024
#define HALPORT_SPI2_TXBUF_SIZE                 1024
#define HALPORT_SPI2_IRQ_PRE_PRIORITY			0
#define HALPORT_SPI2_IRQ_SUB_PRIORITY			0
#define HALPORT_SPI2_LOCATION					SPI_ROUTE_LOCATION_LOC0

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
#define HAL_ENABLE_OS							0

#endif /* HAL_CONFIG_H */
