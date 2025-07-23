/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_gpio.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       GPIO module port for ATMEL SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_port_gpio.h"

// Describes a GPIO interrupt source, including the PIO
// pin and the associated interrupt handler.
struct s_interrupt_source {
	uint8_t port;
	uint32_t pin;
	/* Interrupt handler. */
	void (*handler) (void);
};

// List of interrupt sources.
static struct s_interrupt_source gs_interrupt_sources[MAX_INTERRUPT_SOURCES];
// Number of currently defined interrupt sources.
static uint32_t gs_ul_nb_sources = 0;

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_Init
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_Init(void)
{

	int i=0;
	// Set all ports as input and clear all other options
	// Clear interrupt variables
	gs_ul_nb_sources = 0;
	for(i=0;i<MAX_INTERRUPT_SOURCES;i++){
		gs_interrupt_sources[i].port=0;
		gs_interrupt_sources[i].pin=0;
		gs_interrupt_sources[i].handler=NULL;
	}
}
/* HAL_GPIO_PORT_Init */

// -----------------------------------------------------------------------------
// 	HAL_GPIO_PORT_Deinit
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_Deinit(void)
{
	int i=0;

	// disable clock for gpio's interface
	PMC_PCDR0 = (1<<ID_PIOA) | (1<<ID_PIOB) | (1<<ID_PIOC);

	//disable all interrupts
	HAL_PORT_NVIC_IRQDeinit(PIOA_IRQn);
	HAL_PORT_NVIC_IRQDeinit(PIOB_IRQn);
	HAL_PORT_NVIC_IRQDeinit(PIOC_IRQn);

	// Clear variables for interrupts
	gs_ul_nb_sources = 0;
	for(i=0;i<MAX_INTERRUPT_SOURCES;i++){
		gs_interrupt_sources[i].port=0;
		gs_interrupt_sources[i].pin=0;
		gs_interrupt_sources[i].handler=NULL;
	}
}
/* HAL_GPIO_PORT_Deinit */

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_ConfigurePin
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_ConfigurePin(volatile TGPIO* port, uint32_t pin, uint32_t mode)
{

	// Enable peripheral clock
	if (GPIOA == port) {
		//PORTA
		PMC_PCER0 = (1<<ID_PIOA);
	} else 	if (GPIOB == port) {
		//PORTB
		PMC_PCER0 = (1<<ID_PIOB);
	} else if (GPIOC == port) {
		//PORTC
		PMC_PCER0 = (1<<ID_PIOC);
	} else {
		// Unknown port
		return;
	}

	if ((mode) & GPIO_MODE_PULL_DOWN) {
		// Enable pull-down
		port->PIO_PUDR = 1<<pin;
		port->PIO_PPDER = 1<<pin;
	} else {
		// Disable pull-down
		port->PIO_PPDDR = 1<<pin;
	}

	if ((mode) & GPIO_MODE_PULL_UP) {
		// Enable pull-up
		port->PIO_PUER = 1<<pin;
	} else {
		// Disable pull-up
		port->PIO_PUDR = 1<<pin;
	}
	if((mode) & GPIO_MODE_OPEN_DRAIN ){
		// Enable Open-drain
		port->PIO_MDER = 1<<pin;
	} else {
		// Disable Open-drain
		port->PIO_MDDR = 1<<pin;
	}

	if ((mode) & GPIO_MODE_OUTPUT) {
		// Enable output
		port->PIO_OER = 1<<pin;
	} else {
		// Disable output
		port->PIO_ODR = 1<<pin;
	}

	//Set alternative function
	switch ((mode) & GPIO_MODE_PERIPH_MASK) {
	case GPIO_MODE_PERIPH_A:

		port->PIO_PDR = 1<<pin;
		port->PIO_ABCDSR[0] &= ~(1<<pin);
		port->PIO_ABCDSR[1] &= ~(1<<pin);
		break;

	case GPIO_MODE_PERIPH_B:

		port->PIO_PDR = 1<<pin;
		port->PIO_ABCDSR[0] |= (1<<pin);
		port->PIO_ABCDSR[1] &= ~(1<<pin);
		break;

	case GPIO_MODE_PERIPH_C:

		port->PIO_PDR = 1<<pin;
		port->PIO_ABCDSR[0] &= ~(1<<pin);
		port->PIO_ABCDSR[1] |= (1<<pin);
		break;

	case GPIO_MODE_PERIPH_D:

		port->PIO_PDR = 1<<pin;
		port->PIO_ABCDSR[0] |= (1<<pin);
		port->PIO_ABCDSR[1] |= (1<<pin);
		break;

	default:
		// GPIO Enable Register
		port->PIO_PER = 1<<pin;
		break;
	}

} /* HAL_GPIO_PORT_ConfigurePin */

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_ConfigurePort
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_ConfigurePort(volatile TGPIO* port, uint32_t port_mask, uint32_t mode)
{

	// Enable peripheral clock
	if (GPIOA == port) {
		//Port A
		PMC_PCER0 = (1<<ID_PIOA);
	} else 	if (GPIOB == port) {
		//Port B
		PMC_PCER0 = (1<<ID_PIOB);
	} else if (GPIOC == port) {
		//Port C
		PMC_PCER0 = (1<<ID_PIOC);
	} else {
		// Unknown port
		return;
	}

	if ((mode) & GPIO_MODE_PULL_DOWN) {
		// Enable pull-down
		port->PIO_PUDR = (port_mask);
		port->PIO_PPDER = (port_mask);
	} else {
		// Disable pull-down
		port->PIO_PPDDR = (port_mask);
	}

	if ((mode) & GPIO_MODE_PULL_UP) {
		// Enable pull-up
		port->PIO_PUER = (port_mask);
	} else {
		// Disable pull-up
		port->PIO_PUDR = (port_mask);
	}
	if((mode) & GPIO_MODE_OPEN_DRAIN ){
		// Enable Open-drain
		port->PIO_MDER = (port_mask);
	} else {
		// Disable Open-drain
		port->PIO_MDDR = (port_mask);
	}

	if ((mode) & GPIO_MODE_OUTPUT) {
		// Enable output for masked bits
		port->PIO_OER = (port_mask);
	} else {
		// Disable output for others
		port->PIO_ODR = (port_mask);
	}


	//Set alternative function
	switch ((mode) & GPIO_MODE_PERIPH_MASK) {

	case GPIO_MODE_PERIPH_A:

		port->PIO_PDR = port_mask;
		port->PIO_ABCDSR[0] &= ~(port_mask);
		port->PIO_ABCDSR[1] &= ~(port_mask);
		break;

	case GPIO_MODE_PERIPH_B:

		port->PIO_PDR = port_mask;
		port->PIO_ABCDSR[0] |= (port_mask);
		port->PIO_ABCDSR[1] &= ~(port_mask);
		break;

	case GPIO_MODE_PERIPH_C:

		port->PIO_PDR =port_mask;
		port->PIO_ABCDSR[0] &= ~(port_mask);
		port->PIO_ABCDSR[1] |= (port_mask);
		break;

	case GPIO_MODE_PERIPH_D:

		port->PIO_PDR = port_mask;
		port->PIO_ABCDSR[0] |= (port_mask);
		port->PIO_ABCDSR[1] |= (port_mask);
		break;

	default:
		// GPIO Enable Register
		port->PIO_PER = (port_mask);
		break;
	}

}
/* HAL_GPIO_PORT_ConfigurePort */

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_EnableEvent
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_EnableEvent(volatile TGPIO* port,uint8_t pin, uint8_t source)
{

	// Turn on NVIC interrupt from GPIO
	if (GPIOA == port) {
		HAL_PORT_NVIC_IRQInit(PIOA_IRQn,HALPORT_EXTI_GPIOA_IRQ_PRE_PRIORITY,HALPORT_EXTI_IRQ_GPIOA_SUB_PRIORITY);
	} else 	if (GPIOB == port) {
		HAL_PORT_NVIC_IRQInit(PIOB_IRQn,HALPORT_EXTI_GPIOA_IRQ_PRE_PRIORITY,HALPORT_EXTI_IRQ_GPIOA_SUB_PRIORITY);
	} else if (GPIOC == port) {
		HAL_PORT_NVIC_IRQInit(PIOC_IRQn,HALPORT_EXTI_GPIOA_IRQ_PRE_PRIORITY,HALPORT_EXTI_IRQ_GPIOA_SUB_PRIORITY);
	} else {
		// Unknown port
		return;
	}


	// Enables additional interrupt mode if needed
	if (source & ADD_INT) {

		// Enables additional interrupt mode
		port->PIO_AIMER = 1<<pin;

		//Configures the Polarity of the event detection
		if (source & HIGH_LOW) {
			/* Rising Edge or High Level */
			port->PIO_REHLSR = 1<<pin;
		} else {
			/* Falling Edge or Low Level */
			port->PIO_FELLSR = 1<<pin;
		}

		// Configures the type of event detection (Edge or Level)
		if (source & LEVEL_EDGE) {
			/* Level select */
			port->PIO_LSR = 1<<pin;
		} else {
			/* Edge select */
			port->PIO_ESR = 1<<pin;
		}

	}
	// Clear interrupt status register
	port ->PIO_ISR;
	// Enable interrupt on this pin
	port -> PIO_IER = (1<<pin);
	// Clear interrupt status register


}
/* HAL_GPIO_PORT_EnableEvent */

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_DisableEvent
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_DisableEvent(volatile TGPIO* port, uint32_t pin)
{
	// Clear interrupt status register
	(port)->PIO_ISR;
	(port)->PIO_IDR = ((uint32_t)(1 << (pin)));

}
// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_SetEventHandler
// -----------------------------------------------------------------------------
void HAL_GPIO_PORT_SetEventHandler(volatile TGPIO* port, uint8_t pin, void (*handler)(void))
{
	uint8_t i=0;
	uint8_t nr_port=0;
	struct s_interrupt_source *pSource;

	if (GPIOA == port) {
		nr_port = 1;
	} else 	if (GPIOB == port) {
		nr_port = 2;
	} else if (GPIOC == port) {
		nr_port = 3;
	} else {
		nr_port = 0;
		return;
		// This port no exist
	}

	// Check if for this port and pin isn't any handler
	for(i=0; i<MAX_INTERRUPT_SOURCES; i++){
		if(gs_interrupt_sources[i].port==nr_port){
			if(gs_interrupt_sources[i].pin==(1<<pin)){
				return;
				// Error this pin has got event
			}
		}
	}

	if (gs_ul_nb_sources < MAX_INTERRUPT_SOURCES){
		//  Define new source
		pSource = &(gs_interrupt_sources[gs_ul_nb_sources]);
		pSource->port = nr_port;
		pSource->pin = (1<<pin);
		pSource->handler = handler;
		gs_ul_nb_sources++;

	} else {
		return;
		// To much interrupt sources ... next one is omitted
	}
}
/* HAL_GPIO_PORT_SetEventHandler */

// -----------------------------------------------------------------------------
//  HAL_GPIO_PORT_IsEventEnabled
// -----------------------------------------------------------------------------

int HAL_GPIO_PORT_IsEventEnabled(volatile TGPIO* port, uint8_t pin)
{
	if ( ((port->PIO_IMR) & (1<<pin)) )
		return 1;
	else
		return 0;

}
/* HAL_GPIO_PORT_IsEventEnabled */

// -----------------------------------------------------------------------------
//  PIOA_IrqHandler
// -----------------------------------------------------------------------------
void PIOA_IrqHandler()
{
	uint32_t status;
	uint32_t i;

	// Read GPIOA controller status
	status = GPIOA->PIO_ISR ;
	status &= (GPIOA->PIO_IMR);


	// Check pending events
	if (status != 0) {
		// Find triggering source
		i = 0;
		while (status != 0) {
			// Source is configured on the same controller
			if (gs_interrupt_sources[i].port == 1) {
				// Source has GPIO whose statuses have changed
				if ((status & gs_interrupt_sources[i].pin) != 0) {
					gs_interrupt_sources[0].handler();
					status &= ~(gs_interrupt_sources[i].pin);
				}
			}
			i++;
		}
	}



}
/* PIOA_IrqHandler */

// -----------------------------------------------------------------------------
//  PIOB_IrqHandler()
// -----------------------------------------------------------------------------
void PIOB_IrqHandler()
{
	uint32_t status;
	uint32_t i;

	// Read GPIOB controller status
	status = GPIOB->PIO_ISR;
	status &= (GPIOB->PIO_IMR );

	// Check pending events
	if (status != 0) {
		// Find triggering source
		i = 0;
		while (status != 0) {
			// Source is configured on the same controller
			if (gs_interrupt_sources[i].port == 2) {
				// Source has PIOs whose statuses have changed
				if ((status & gs_interrupt_sources[i].pin) != 0) {
					gs_interrupt_sources[i].handler();
					status &= ~(gs_interrupt_sources[i].pin);
				}
			}
			i++;
		}
	}
}
/* PIOB_IrqHandler() */

// -----------------------------------------------------------------------------
//  PIOC_IrqHandler()
// -----------------------------------------------------------------------------
void PIOC_IrqHandler()
{
	uint32_t status;
	uint32_t i;

	// Read GPIOc controller status
	status = GPIOC->PIO_ISR;
	status &= (GPIOC->PIO_IMR );

	// Check pending events
	if (status != 0) {
		// Find triggering source
		i = 0;
		while (status != 0) {
			// Source is configured on the same controller
			if (gs_interrupt_sources[i].port == 3) {
				// Source has PIOs whose statuses have changed
				if ((status & gs_interrupt_sources[i].pin) != 0) {
					gs_interrupt_sources[i].handler();
					status &= ~(gs_interrupt_sources[i].pin);
				}
			}
			i++;
		}
	}
}
/* PIOC_IrqHandler() */
