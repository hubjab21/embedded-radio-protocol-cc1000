/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_delay.c
 Author:        Lukasz Duda, Michał Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DELAY module port for ATMEL SAM3S
--------------------------------------------------------------------------------
 Comments:		At this time has 6 latency cycle
================================================================================
*/

#if !defined HAL_F_CPU || (HAL_F_CPU == 0)
#error ATMEL SAM3S DELAY require define HAL_F_CPU
#error Type frequency of CPU in your hal_config.h
#endif


// Define multiply factor for ms
#define HAL_DELAY_MULTIPLY_FOR_MS 			(uint32_t)(((HAL_F_CPU+2000)/4000))

// Define multiply factor for us
#define HAL_DELAY_MULTIPLY_FOR_US			(uint32_t)(((HAL_F_CPU+2000000)/4000000))

// -------------------------------------------------------------------------------
// HAL_PORT_DELAY_MS
// -------------------------------------------------------------------------------
void HAL_PORT_DELAY_MS(uint32_t ms)
{
	// Constant 4 cycle delay + 2 cycle { move ms to r0, jmp to func}

	asm volatile ("mov r1, %0" :: "r" (ms));		   	                 // 1 cycle
	asm volatile ("movw r2, %0" :: "i" (HAL_DELAY_MULTIPLY_FOR_MS));     // 1 cycle
	asm volatile ("mul r3, r1, r2\n\t");								 // 2 cycle (r3 is used in next instr)

	// 4 cycle loop
	asm volatile ("DELAY_MS_LOOP: subs r3, #1   \n\t" 			   // 1 cycle
				  "nop						    \n\t"			   // 1 cycle to prevent /3
				  "bne DELAY_MS_LOOP            \n\t"			   // 2 cycle
				  );

} /* HAL_PORT_DELAY_MS */

// -------------------------------------------------------------------------------
// HAL_PORT_DELAY_MS
// -------------------------------------------------------------------------------
void HAL_PORT_DELAY_US(uint32_t us)
{
	// Constant 4 cycle delay + 2 cycle { move ms to r0, jmp to funcs}

	asm volatile ("mov r1, %0" :: "r" (us));		   	                 // 1 cycle
	asm volatile ("movw r2, %0" :: "i" (HAL_DELAY_MULTIPLY_FOR_US));     // 1 cycle
	asm volatile ("mul r3, r1, r2\n\t");								 // 2 cycle (cus r3 is used in next instr)

	// 4 cycle loop
	asm volatile ("DELAY_US_LOOP: subs r3, #1   \n\t" 			   // 1 cycle
				  "nop						    \n\t"			   // 1 cycle to prevent /3
				  "bne DELAY_US_LOOP            \n\t"			   // 2 cycle
				  );

} /* HAL_PORT_DELAY_MS */
