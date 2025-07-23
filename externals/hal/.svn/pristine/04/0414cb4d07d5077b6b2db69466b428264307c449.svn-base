/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_gpio.h
 Author:        Łukasz Krzak
 Purpose:       HALFRED's WIN32 port
 Compiler:      %COMPILER%
 Hardware:      PC/Windows
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       GPIO module port for Windows
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_GPIO_H
#define HAL_PORT_GPIO_H

#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------
//  PORT CONFIGURATION
// -----------------------------------------------------------------------------

#ifndef HAL_PORT_GPIO_NUMBER_OF_PORTS
#define HAL_PORT_GPIO_NUMBER_OF_PORTS						8
#endif

#ifndef HAL_PORT_GPIO_LOG
#define HAL_PORT_GPIO_LOG									1
#endif


// -----------------------------------------------------------------------------
//  PUBLIC MACROS
// -----------------------------------------------------------------------------

#define CONFIG_IN											0
#define CONFIG_OUT											1


#if defined HAL_PORT_GPIO_LOG && (HAL_PORT_GPIO_LOG)
// with log
#define HAL_GPIO_PORT_Init()								do { \
																memset(hal_port_gpio_config, 0x00, sizeof(hal_port_gpio_config)); \
																memset(hal_port_gpio_output_state, 0x00, sizeof(hal_port_gpio_config)); \
																printf("\nGPIO Init"); \
															} while (0)

#define HAL_GPIO_PORT_Deinit()								do { \
																memset(hal_port_gpio_config, 0x00, sizeof(hal_port_gpio_config)); \
																memset(hal_port_gpio_output_state, 0x00, sizeof(hal_port_gpio_config)); \
																printf("\nGPIO Deinit"); \
															} while (0)

#define HAL_GPIO_PORT_GetConfig(port, pin) 					((hal_port_gpio_config[port] & 1<<pin)>>pin)

#define HAL_GPIO_PORT_ReadPin(port, pin) 					((hal_port_gpio_input_state[port] & 1<<pin)>>pin)

#define HAL_GPIO_PORT_SetPinHigh(port, pin) 				do { \
																hal_port_gpio_output_state[port] |= 1<<pin; \
																printf("\nPort %d pin %d = 1", port, pin); \
															} while (0)

#define HAL_GPIO_PORT_SetPinLow(port, pin) 					do { \
																hal_port_gpio_output_state[port] &= ~(1<<pin); \
																printf("\nPort %d pin %d = 0", port, pin); \
															} while (0)

#define HAL_GPIO_PORT_ConfigurePin(port, pin, mode)			do { \
																if (mode) { \
																	hal_port_gpio_config[port] |= 1<<pin; \
																	printf("\nPort %d pin %d set as output", port, pin); \
																} else { \
																	hal_port_gpio_config[port] &= ~(1<<pin); \
																	printf("\nPort %d pin %d set as output", port, pin); \
																} \
															} while (0)

#define HAL_GPIO_PORT_TogglePin(port, pin)					do { \
																hal_port_gpio_output_state[port] ^= (1<<pin); \
																printf("\nPort %d pin %d toggled to %d", port, pin, (hal_port_gpio_output_state[port]>>pin) & 1); \
															} while (0)

#else
// no log

#define HAL_GPIO_PORT_Init()								do { \
																memset(hal_port_gpio_config, 0x00, sizeof(hal_port_gpio_config)); \
																memset(hal_port_gpio_output_state, 0x00, sizeof(hal_port_gpio_config)); \
															} while (0)

#define HAL_GPIO_PORT_Deinit()								HAL_GPIO_PORT_Init()

#define HAL_GPIO_PORT_GetConfig(port, pin) 					((hal_port_gpio_config[port] & 1<<pin)>>pin)

#define HAL_GPIO_PORT_ReadPin(port, pin) 					((hal_port_gpio_input_state[port] & 1<<pin)>>pin)

#define HAL_GPIO_PORT_SetPinHigh(port, pin) 				do { \
																hal_port_gpio_output_state[port] |= 1<<pin; \
															} while (0)

#define HAL_GPIO_PORT_SetPinLow(port, pin) 					do { \
																hal_port_gpio_output_state[port] &= ~(1<<pin); \
															} while (0)

#define HAL_GPIO_PORT_ConfigurePin(port, pin, mode)			do { \
																if (mode) { \
																	hal_port_gpio_config[port] |= 1<<pin; \
																} else { \
																	hal_port_gpio_config[port] &= ~(1<<pin); \
																} \
															} while (0)

#define HAL_GPIO_PORT_TogglePin(port, pin)					do { \
																hal_port_gpio_output_state[port] ^= (1<<pin); \
															} while (0)
#endif

extern uint32_t hal_port_gpio_input_state[HAL_PORT_GPIO_NUMBER_OF_PORTS];
extern uint32_t hal_port_gpio_output_state[HAL_PORT_GPIO_NUMBER_OF_PORTS];
extern uint32_t hal_port_gpio_config[HAL_PORT_GPIO_NUMBER_OF_PORTS];

#endif /* HAL_PORT_GPIO_H */

