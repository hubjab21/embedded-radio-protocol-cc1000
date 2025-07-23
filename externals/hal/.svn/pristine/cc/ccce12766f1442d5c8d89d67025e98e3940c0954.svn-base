/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_gpio.h
 Author:        Lukasz Krzak, Piotr Wojtowicz
 Purpose:       HALFRED's AVR port
 Compiler:      %COMPILER%
 Hardware:      AVR
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       GPIO module port for AVR
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_GPIO_H
#define HAL_PORT_GPIO_H

#include <avr/io.h>
#include <stdint.h>

typedef struct {
    uint8_t PIN;
    uint8_t DDR;
    uint8_t PORT;
} TGPIO;

#define GPIOA   ((volatile TGPIO*)&PINA)
#define GPIOB   ((volatile TGPIO*)&PINB)
#define GPIOC   ((volatile TGPIO*)&PINC)
#define GPIOD   ((volatile TGPIO*)&PIND)
#define GPIOE   ((volatile TGPIO*)&PINE)
#define GPIOG   ((volatile TGPIO*)&PING)

#define GPIO_MODE_IN                                        0
#define GPIO_MODE_OUT_PP                                    1
#define GPIO_MODE_PULL_UP									2

// -----------------------------------------------------------------------------
//  PUBLIC MACROS
// -----------------------------------------------------------------------------

#define GPIO_PORT_Init()

#define GPIO_PORT_Deinit()

#define GPIO_PORT_GetConfig(port, pin)                  (((port)->DDR & (1<<(pin))) ? GPIO_MODE_OUT_PP : GPIO_MODE_INPUT)

#define GPIO_PORT_ReadPin(port, pin)                    (((port)->PIN >> (pin)) & 0x01)

#define GPIO_PORT_SetPinHigh(port, pin)                 ((port)->PORT |= ((uint8_t)(1 << (pin))))

#define GPIO_PORT_SetPinLow(port, pin)                  ((port)->PORT &= (uint8_t)(~((uint8_t)(1 << (pin)))))

#define GPIO_PORT_TogglePin(port, pin)                  ((port)->PORT ^= ((uint8_t)(1 << (pin))))

#define GPIO_PORT_ReadPort(port)                        (port)->PIN

#define GPIO_PORT_WritePort(port, data)                 ((port)->PORT = (data))

#define GPIO_PORT_SetPortHigh(port, data)               ((port)->PORT |= (data))

#define GPIO_PORT_SetPortLow(port, data)                ((port)->PORT &= ~(data))

#define GPIO_PORT_ConfigurePin(port, pin, mode)         if ((mode) & GPIO_MODE_OUT_PP) { \
        (port)->DDR |= (1<<(pin));     \
    } else {                          \
        (port)->DDR &= (uint8_t)(~(1<<(pin)));    \
        if ((mode) & GPIO_MODE_PULL_UP) { \
        	(port)->PORT |= (uint8_t)(1<<(pin));  \
        } else { \
        	(port)->PORT &= (uint8_t)(~(1<<(pin))); \
        } \
    }

#define GPIO_PORT_ConfigurePort(port, port_mask, mode)  if ((mode) == GPIO_MODE_OUT_PP) { \
        (port)->DDR |= (port_mask));   \
    } else {                          \
        (port)->DDR &= ~(port_mask));  \
    }

#define GPIO_PORT_EnableEvent(port, pin, source)

#define GPIO_PORT_DisableEvent(port, pin)

#define GPIO_PORT_SetEventHandler(port, pin, handler)

#define GPIO_PORT_IsEventEnabled(port, pin)

#endif /* HAL_PORT_GPIO_H */

