/*
 ================================================================================
 %LICENSE%
 --------------------------------------------------------------------------------
 File:          hal_port_core.c
 Author:        Lukasz Krzak, Michal Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
 --------------------------------------------------------------------------------
 Content:       CORE module port for Atmel SAM3S
 --------------------------------------------------------------------------------
 Comments:      This core provide 1 main system oscillator (index 0)
 ================================================================================
 */

// A variable that keeps count of nested critical sections
unsigned int HAL_PORT_InterruptState;

// -----------------------------------------------------------------------------
//  CORE_PORT_Init
// -----------------------------------------------------------------------------
void CORE_PORT_Init(void)
{
	// Turn off interrupts


	// Turn off watchdog
	WDT_MR = WDT_MR_WDDIS;

	//
#ifndef HAL_CORE_NVIC_PRIORITY_GROUP
#define HAL_CORE_NVIC_PRIORITY_GROUP HAL_NVIC_PRIORITY_GROUP_2
#endif
	// Set division between pre-emption priority and subpriority part
	HAL_PORT_NVIC_PriorityGroupConfig(HAL_CORE_NVIC_PRIORITY_GROUP);
} /* CORE_PORT_Init */
