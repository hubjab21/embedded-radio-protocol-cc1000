/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_clk.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CLK module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_CLK_H
#define HAL_PORT_CLK_H


/// Available clocks
typedef enum {
	/// Main clock (default)
	SAM3S_MAIN_CLOCK = 0,
	/// Slow clock (32kHz)
	SAM3S_SLOW_CLOCK,
	/// Master clock (processor)
	SAM3S_MASTER_CLOCK,
} CORE_PORT_Clock;


/// Possible clock sources
typedef enum {
	/// Internal RC oscillator (default)
	SAM3S_RC_CLOCK_SOURCE = 0,
	/// External crystal
	SAM3S_XTAL_CLOCK_SOURCE,
	/// External clock (oscillator is bypassed)
	SAM3S_EXTERNAL_CLOCK_SOURCE,
	/// Slow clock
	SAM3S_SLOW_CLOCK_SOURCE,
	// Main clock
	SAM3S_MAIN_CLOCK_SOURCE,
	// PLL A
	SAM3S_PLLA_CLOCK_SOURCE,
	// PLL B
	SAM3S_PLLB_CLOCK_SOURCE,
	// Unknown clock source
	SAM3S_UNKNOWN_CLOCK_SOURCE = -1,
} CORE_PORT_ClockSource;

// Define startup timeout for MAIN clock XTAL
#ifndef SAM3S_MAIN_STARTUP_TIMEOUT
#define SAM3S_MAIN_STARTUP_TIMEOUT				((uint16_t)0x3F)
#endif

// Define startup timeout for PLLA clock
#ifndef SAM3S_PLLA_STARTUP_TIMEOUT
#define SAM3S_PLLA_STARTUP_TIMEOUT				((uint16_t)0x3F)
#endif

// Define startup timeout for PLLB clock
#ifndef SAM3S_PLLB_STARTUP_TIMEOUT
#define SAM3S_PLLB_STARTUP_TIMEOUT				((uint16_t)0x3F)
#endif

extern ClockController cc_sam3s;

// Clock on pin function available only if GPIO module is activated
#if defined HAL_CLK_CLOCK_ON_PIN && HAL_CLK_CLOCK_ON_PIN ==1
#if (HAL_ENABLE_GPIO) || (HAL_ENABLE_IO)

	// Available type of clocks
	#define SLOW_CLK 		 (0x0u << 0)
	#define MAIN_CLK 		 (0x1u << 0)
	#define PLLA_CLK		 (0x2u << 0)
	#define PLLB_CLK		 (0x3u << 0)
	#define MCK			 	 (0x4u << 0)

	// Helper registers declared to not duplicate hal_common.h
	#define PMC_PCK0   		 (*(volatile uint32_t*)0x400E0440U)
	#define PMC_PCK1 	     (*(volatile uint32_t*)0x400E0444U)
	#define PMC_PCK2   		 (*(volatile uint32_t*)0x400E0448U)
	#define PMC_SCDR_PMC   	 (*(volatile uint32_t*)0x400E0404U)
	#define PMC_SCER_PMC  	 (*(volatile uint32_t*)0x400E0400U)
	#define PMC_SR_PMC     	 (*(volatile uint32_t*)0x400E0468U)

	// Helper definitions
	#define PMC_SR_PCKRDY_0 		(0x1u << 8)
	#define PMC_SR_PCKRDY_1 		(0x1u << 9)
	#define PMC_SR_PCKRDY_2 		(0x1u << 10)
	#define PMC_SCDR_PCK_0 		(0x1u << 8)
	#define PMC_SCDR_PCK_1 		(0x1u << 9)
	#define PMC_SCDR_PCK_2 		(0x1u << 10)

	// Helper macros
	#define HAL_CLK_GET_CLK_NAME(name) 		name##_##CLK
	#define SAM3S_Clock_On_Pin(name)		HAL_CLK_PORT_Clock_On_Pin(HAL_GPIO_GET_PORT_NAME(name), HAL_GPIO_GET_PIN_NAME(name),  HAL_CLK_GET_CLK_NAME(name))

	// Main function clock on pin
	#define HAL_CLK_PORT_Clock_On_Pin(port, pin, clk) \
	{\
		port->PIO_PDR = (1<<pin); \
		port->PIO_ABCDSR[0] |= (1<<pin); \
		port->PIO_ABCDSR[1] &= ~(1<<pin); \
		if((port==GPIOA && pin==6) || (port==GPIOB && pin==13))\
		{\
			PMC_SCDR_PMC = PMC_SCDR_PCK_0;\
			PMC_PCK0  = clk;\
			while (!(PMC_SR_PMC & PMC_SR_PCKRDY_0)) {\
				;\
			}\
			PMC_SCER_PMC = PMC_SCDR_PCK_0;\
		}else if((port==GPIOA && pin==17))\
		{\
			PMC_SCDR_PMC = PMC_SCDR_PCK_1;\
			PMC_PCK1  = clk;\
			while (!(PMC_SR_PMC & PMC_SR_PCKRDY_1)) {\
				;\
			}\
			PMC_SCER_PMC = PMC_SCDR_PCK_1;\
		}else if((port==GPIOA && pin==18) || (port==GPIOA && pin==23)|| (port==GPIOB && pin==3))\
		{\
			PMC_SCDR_PMC = PMC_SCDR_PCK_2;\
			PMC_PCK2  = clk;\
			while (!(PMC_SR_PMC & PMC_SR_PCKRDY_2)) {\
				;\
			}\
			PMC_SCER_PMC = PMC_SCDR_PCK_2;\
		}\
	}

#endif
#endif


#endif /* HAL_PORT_CLK_H */
