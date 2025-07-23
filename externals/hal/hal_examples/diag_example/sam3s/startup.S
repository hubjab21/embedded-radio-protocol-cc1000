/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			startup.S
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's OS module example
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Interrupt vectors and startup code
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_config.h"

.cpu cortex-m3
.fpu softvfp   
.syntax unified
.thumb


/*******************************************************************************
              Initial stack
*******************************************************************************/
.section .bss
_sstack:
.fill HAL_STACK_SIZE
.align 8
_estack:
_initial_stack_ptr:


   /**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/*******************************************************************************
              MCU and peripherals IRQ handlers address table
*******************************************************************************/

.global	Default_Handler
.section .vector_flash, "ax"

.global Reset_Vector

Reset_Vector:
.word   _initial_stack_ptr
.word   Reset_Handler
.word   UnhandledException
.word   UnhandledException
.word   UnhandledException
.word   UnhandledException
.word   UnhandledException
.word   0                       /* Reserved */
.word   0                       /* Reserved */
.word   0                       /* Reserved */
.word   0                       /* Reserved */ 
.word   SVCHandler
.word   DebugMonitor
.word   0                       /* Reserved */
.word   PendSVC
.word   SysTick_Handler   /* Sys Tick Handler */
.word	SupplyController_IrqHandler  /* 0  Supply Controller */
.word	ResetController_IrqHandler   /* 1  Reset Controller */
.word 	RealTimeClock_IrqHandler     /* 2  Real Time Clock */
.word 	RealTimeTimer_IrqHandler   /* 3  Real Time Timer */
.word 	WatchdogTimer_IrqHandler     /* 4  Watchdog Timer */
.word 	PMC_IrqHandler    /* 5  PMC */
.word 	EEFC_IrqHandler    /* 6  EEFC */
.word 	0  /* 7  Reserved */
.word 	UART0_IrqHandler   /* 8  UART0 */
.word 	UART1_IrqHandler   /* 9  UART1 */
.word 	SMC_IrqHandler    /* 10 SMC */
.word 	PIOA_IrqHandler   /* 11 Parallel IO Controller A */
.word 	PIOB_IrqHandler    /* 12 Parallel IO Controller B */
.word 	PIOC_IrqHandler    /* 13 Parallel IO Controller C */
.word 	USART0_IrqHandler  /* 14 USART 0 */
.word 	USART1_IrqHandler  /* 15 USART 1 */
.word 	0  /* 16 Reserved */
.word 	0  /* 17 Reserved */
.word 	MCI_IrqHandler   /* 18 MCI */
.word 	TWI0_IrqHandler   /* 19 TWI 0 */
.word 	TWI1_IrqHandler   /* 20 TWI 1 */
.word 	SPI1_IrqHandler   /* 21 SPI */
.word 	SSC_IrqHandler   /* 22 SSC */
.word 	T0_IrqHandler     /* 23 Timer Counter 0 */
.word 	T1_IrqHandler     /* 24 Timer Counter 1 */
.word 	T2_IrqHandler    /* 25 Timer Counter  2 */
.word 	T3_IrqHandler     /* 26 Timer Counter 3 */
.word 	T4_IrqHandler     /* 27 Timer Counter 4 */
.word 	T5_IrqHandler     /* 28 Timer Counter 5 */
.word 	ADC_IrqHandler     /* 29 ADC controller */
.word 	DAC_IrqHandler     /* 30 DAC controller */
.word 	PWM_IrqHandler     /* 31 PWM */
.word 	CRC_IrqHandler   /* 32 CRC Calculation Unit */
.word 	AC_IrqHandler    /* 33 Analog Comparator */
.word 	USB_IrqHandler    /* 34 USB Device Port */
.word 	0   /* 35 not used */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak	UART0_IrqHandler
	.thumb_set UART0_IrqHandler,Default_Handler

  .weak	UART1_IrqHandler
	.thumb_set UART1_IrqHandler,Default_Handler

  .weak	USART0_IrqHandler
	.thumb_set USART0_IrqHandler,Default_Handler

  .weak	USART1_IrqHandler
	.thumb_set USART1_IrqHandler,Default_Handler

  .weak	PIOA_IrqHandler
	.thumb_set PIOA_IrqHandler,Default_Handler

  .weak PIOB_IrqHandler
	.thumb_set PIOB_IrqHandler,Default_Handler

  .weak	PIOC_IrqHandler
	.thumb_set PIOC_IrqHandler,Default_Handler

  .weak	SPI1_IrqHandler
	.thumb_set SPI1_IrqHandler,Default_Handler

  .weak	T0_IrqHandler
	.thumb_set T0_IrqHandler,Default_Handler

  .weak	T1_IrqHandler
	.thumb_set T1_IrqHandler,Default_Handler

  .weak	PendSVC
	.thumb_set PendSVC,Default_Handler

  .weak	SVCHandler
    .thumb_set SVCHandler,Default_Handler

  .weak	SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

  .weak	SupplyController_IrqHandler
    .thumb_set SupplyController_IrqHandler,Default_Handler

 .weak	ResetController_IrqHandler
    .thumb_set ResetController_IrqHandler,Default_Handler

 .weak	RealTimeClock_IrqHandler
    .thumb_set RealTimeClock_IrqHandler,Default_Handler

 .weak	RealTimeTimer_IrqHandler
    .thumb_set RealTimeTimer_IrqHandler,Default_Handler

  .weak	WatchdogTimer_IrqHandler
    .thumb_set WatchdogTimer_IrqHandler,Default_Handler

 .weak	PMC_IrqHandler
    .thumb_set PMC_IrqHandler,Default_Handler

 .weak	EEFC_IrqHandler
    .thumb_set EEFC_IrqHandler,Default_Handler

 .weak	SMC_IrqHandler
    .thumb_set SMC_IrqHandler,Default_Handler

 .weak	MCI_IrqHandler
    .thumb_set MCI_IrqHandler,Default_Handler

 .weak	TWI0_IrqHandler
    .thumb_set TWI0_IrqHandler,Default_Handler

 .weak	TWI1_IrqHandler
    .thumb_set TWI1_IrqHandler,Default_Handler

 .weak	SSC_IrqHandler
    .thumb_set SSC_IrqHandler,Default_Handler

 .weak	T2_IrqHandler
    .thumb_set T2_IrqHandler,Default_Handler

 .weak	T3_IrqHandler
    .thumb_set T3_IrqHandler,Default_Handler

 .weak	T4_IrqHandler
    .thumb_set T4_IrqHandler,Default_Handler

 .weak	T5_IrqHandler
    .thumb_set T5_IrqHandler,Default_Handler

 .weak	ADC_IrqHandler
    .thumb_set ADC_IrqHandler,Default_Handler

 .weak	DAC_IrqHandler
    .thumb_set DAC_IrqHandler,Default_Handler

 .weak	PWM_IrqHandler
    .thumb_set PWM_IrqHandler,Default_Handler

 .weak	CRC_IrqHandler
    .thumb_set CRC_IrqHandler,Default_Handler

 .weak	AC_IrqHandler
    .thumb_set AC_IrqHandler,Default_Handler

 .weak	USB_IrqHandler
    .thumb_set USB_IrqHandler,Default_Handler

.text
.pool
.thumb_func


.global Reset_Handler

Reset_Handler:

/* initialize data - copy initial values from FLASH to SRAM*/
    LDR     r1, =_sidata
    LDR     r2, =_sdata
    LDR     r3, =_edata
1:
    CMP     r2, r3
    BGE     2f
    LDR     r0, [r1]
    ADD     r1, #4
    STR     r0, [r2]
    ADD     r2, #4
    B       1b
2:

/* clear BBS data section */
    MOV     r0, #0
    LDR     r1, =_sbss
    LDR     r2, =_ebss
3:
    CMP     r1, r2
    BGE     4f
    STR     r0, [r1]
    ADD     r1, #4
    BLT     3b
4:

    LDR     r0, =main
    BX      r0

.end
