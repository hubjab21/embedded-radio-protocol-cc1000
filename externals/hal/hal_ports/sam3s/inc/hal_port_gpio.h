/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_gpio.h
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       GPIO module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_GPIO_H
#define HAL_PORT_GPIO_H

// Port structure
typedef struct {
  volatile uint32_t PIO_PER;        // PIO Enable Register
  volatile uint32_t PIO_PDR;        // PIO Disable Register
  volatile uint32_t PIO_PSR;        // PIO Status Register
  volatile uint32_t Reserved1[1];
  volatile uint32_t PIO_OER;        // Output Enable Register
  volatile uint32_t PIO_ODR;        // Output Disable Register
  volatile uint32_t PIO_OSR;        // Output Status Register
  volatile uint32_t Reserved2[1];
  volatile uint32_t PIO_IFER;       // Glitch Input Filter Enable Register
  volatile uint32_t PIO_IFDR;       // Glitch Input Filter Disable Register
  volatile uint32_t PIO_IFSR;       // Glitch Input Filter Status Register
  volatile uint32_t Reserved3[1];
  volatile uint32_t PIO_SODR;       // Set Output Data Register
  volatile uint32_t PIO_CODR;       // Clear Output Data Register
  volatile uint32_t PIO_ODSR;       // Output Data Status Register
  volatile uint32_t PIO_PDSR;       // Pin Data Status Register
  volatile uint32_t PIO_IER;        // Interrupt Enable Register
  volatile uint32_t PIO_IDR;        // Interrupt Disable Register
  volatile uint32_t PIO_IMR;        // Interrupt Mask Register
  volatile uint32_t PIO_ISR;        // Interrupt Status Register
  volatile uint32_t PIO_MDER;       // Multi-driver Enable Register
  volatile uint32_t PIO_MDDR;       // Multi-driver Disable Register
  volatile uint32_t PIO_MDSR;       // Multi-driver Status Register
  volatile uint32_t Reserved4[1];
  volatile uint32_t PIO_PUDR;       // Pull-up Disable Register
  volatile uint32_t PIO_PUER;       // Pull-up Enable Register
  volatile uint32_t PIO_PUSR;       // Pad Pull-up Status Register
  volatile uint32_t Reserved5[1];
  volatile uint32_t PIO_ABCDSR[2];  // Peripheral Select Register
  volatile uint32_t Reserved6[2];
  volatile uint32_t PIO_IFSCDR;     // Input Filter Slow Clock Disable Register
  volatile uint32_t PIO_IFSCER;     // Input Filter Slow Clock Enable Register
  volatile uint32_t PIO_IFSCSR;     // Input Filter Slow Clock Status Register
  volatile uint32_t PIO_SCDR;       // Slow Clock Divider Debouncing Register
  volatile uint32_t PIO_PPDDR;      // Pad Pull-down Disable Register
  volatile uint32_t PIO_PPDER;      // Pad Pull-down Enable Register
  volatile uint32_t PIO_PPDSR;      // Pad Pull-down Status Register
  volatile uint32_t Reserved7[1];
  volatile uint32_t PIO_OWER;       // Output Write Enable
  volatile uint32_t PIO_OWDR;       // Output Write Disable
  volatile uint32_t PIO_OWSR;       // Output Write Status Register
  volatile uint32_t Reserved8[1];
  volatile uint32_t PIO_AIMER;      // Additional Interrupt Modes Enable Register
  volatile uint32_t PIO_AIMDR;      // Additional Interrupt Modes Disables Register
  volatile uint32_t PIO_AIMMR;      // Additional Interrupt Modes Mask Register
  volatile uint32_t Reserved9[1];
  volatile uint32_t PIO_ESR;        // Edge Select Register
  volatile uint32_t PIO_LSR;        // Level Select Register
  volatile uint32_t PIO_ELSR;       // Edge/Level Status Register
  volatile uint32_t Reserved10[1];
  volatile uint32_t PIO_FELLSR;     // Falling Edge/Low Level Select Register
  volatile uint32_t PIO_REHLSR;     // Rising Edge/ High Level Select Register
  volatile uint32_t PIO_FRLHSR;     // Fall/Rise - Low/High Status Register
  volatile uint32_t Reserved11[1];
  volatile uint32_t PIO_LOCKSR;     // Lock Status
  volatile uint32_t PIO_WPMR;       // Write Protect Mode Register
  volatile uint32_t PIO_WPSR;       // Write Protect Status Register
  volatile uint32_t Reserved12[5];
  volatile uint32_t PIO_SCHMITT;    // Schmitt Trigger Register
  volatile uint32_t Reserved13[19];
  volatile uint32_t PIO_PCMR;       // Parallel Capture Mode Register
  volatile uint32_t PIO_PCIER;      // Parallel Capture Interrupt Enable Register
  volatile uint32_t PIO_PCIDR;      // Parallel Capture Interrupt Disable Register
  volatile uint32_t PIO_PCIMR;      // Parallel Capture Interrupt Mask Register
  volatile uint32_t PIO_PCISR;      // Parallel Capture Interrupt Status Register
  volatile uint32_t PIO_PCRHR;      // Parallel Capture Reception Holding Register
  volatile uint32_t PIO_RPR;        // Receive Pointer Register
  volatile uint32_t PIO_RCR;        // Receive Counter Register
  volatile uint32_t Reserved14[2];
  volatile uint32_t PIO_RNPR;       // Receive Next Pointer Register
  volatile uint32_t PIO_RNCR;       // Receive Next Counter Register
  volatile uint32_t Reserved15[2];
  volatile uint32_t PIO_PTCR;       // Transfer Control Register
  volatile uint32_t PIO_PTSR;       // Transfer Status Register
} TGPIO;

// Available ports
#define GPIOA	((volatile TGPIO*)0x400E0E00)
#define GPIOB	((volatile TGPIO*)0x400E1000)
#define GPIOC	((volatile TGPIO*)0x400E1200)

// Modes of ports
#define GPIO_MODE_INPUT                               0x00
#define GPIO_MODE_OUTPUT                              0x01

// Pull-up Pull-down resistor
#define GPIO_MODE_PULL_DOWN                           0x02
#define GPIO_MODE_PULL_UP                             0x04

// Push-pull Open Drain configuration for MODE_OUTPUT
#define GPIO_MODE_PUSH_PULL                           0x00
#define GPIO_MODE_OPEN_DRAIN                          0x08

// Alternative pin's modes
#define GPIO_MODE_PERIPH_MASK					      0x70
#define GPIO_MODE_PERIPH_A							  0x40
#define GPIO_MODE_PERIPH_B							  0x50
#define GPIO_MODE_PERIPH_C							  0x60
#define GPIO_MODE_PERIPH_D							  0x70

// Types of event
#define GPIO_TRIGGER_EDGE_BOTH						  0x0
#define	GPIO_TRIGGER_EDGE_RISING					  0x3
#define GPIO_TRIGGER_EDGE_FALLING					  0x1
#define	GPIO_TRIGGER_LEVEL_LOW						  0x5
#define	GPIO_TRIGGER_LEVEL_HIGH						  0x7

// Masks for events
// Additional interrupt mode
#define ADD_INT										  0x1
// High/rising low/falling
#define HIGH_LOW									  0x2
// Level or edge
#define LEVEL_EDGE									  0x4

// Interrupt priority
#if(!defined HAL_USE_CUSTOM_EXTI_PRIORITY || HAL_USE_CUSTOM_EXTI_PRIORITY == 0)
#define HALPORT_EXTI_GPIOA_IRQ_PRE_PRIORITY			0
#define HALPORT_EXTI_IRQ_GPIOA_SUB_PRIORITY			0
#define HALPORT_EXTI_GPIOB_IRQ_PRE_PRIORITY			0
#define HALPORT_EXTI_IRQ_GPIOB_SUB_PRIORITY			0
#define HALPORT_EXTI_GPIOC_IRQ_PRE_PRIORITY			0
#define HALPORT_EXTI_IRQ_GPIOC_SUB_PRIORITY			0
#endif
// Maximum number of interrupt sources that can be defined.
#ifndef MAX_INTERRUPT_SOURCES
#define MAX_INTERRUPT_SOURCES       7
#endif

// -----------------------------------------------------------------------------
//  PUBLIC MACROS
// -----------------------------------------------------------------------------

void HAL_GPIO_PORT_Init(void);

void HAL_GPIO_PORT_Deinit(void);

#define HAL_GPIO_PORT_GetConfig(port, pin)          (0)

#define HAL_GPIO_PORT_ReadPin(port, pin) 			(((port)->PIO_PDSR >> (pin)) & 0x00000001)

#define HAL_GPIO_PORT_SetPinHigh(port, pin) 		((port)->PIO_SODR = ((uint32_t)(1 << (pin))))

#define HAL_GPIO_PORT_SetPinLow(port, pin) 			((port)->PIO_CODR = ((uint32_t)(1 << (pin))))

#define HAL_GPIO_PORT_TogglePin(port, pin) 			do { \
	                                       				if ((port)->PIO_ODSR & (1 << (pin))) { \
	                                       					(port)->PIO_CODR = ((uint32_t)(1 << (pin))); \
	                                       				} else { \
	                                       					(port)->PIO_SODR = ((uint32_t)(1 << (pin))); \
                                            			} \
                                           			} while (0)

#define HAL_GPIO_PORT_ReadPort(port) 				((port)->PIO_PDSR)

#define HAL_GPIO_PORT_WritePort(port, data)         do { \
														(port)->PIO_SODR = (data); (port)->PIO_CODR = ~(data); \
													} while (0)

#define HAL_GPIO_PORT_SetPortHigh(port, data)       ((port)->PIO_SODR = (data))

#define HAL_GPIO_PORT_SetPortLow(port, data)        ((port)->PIO_CODR = (data))

void HAL_GPIO_PORT_ConfigurePin(volatile TGPIO* port, uint32_t pin, uint32_t mode);

void HAL_GPIO_PORT_ConfigurePort(volatile TGPIO* port, uint32_t port_mask, uint32_t mode);

void HAL_GPIO_PORT_EnableEvent(volatile TGPIO* port, uint8_t pin, uint8_t source);

void HAL_GPIO_PORT_DisableEvent(volatile TGPIO* port, uint32_t pin);

void HAL_GPIO_PORT_SetEventHandler(volatile TGPIO* port, uint8_t pin, void (*handler)(void));

int HAL_GPIO_PORT_IsEventEnabled(volatile TGPIO* port, uint8_t pin);

#endif /* HAL_PORT_GPIO_H */

