/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_nvic.c
 Author:        Michał Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       NVIC module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal_port_nvic.h"

// -----------------------------------------------------------------------------
//  HAL_PORT_NVIC_IRQInit
// -----------------------------------------------------------------------------
void HAL_PORT_NVIC_IRQInit(uint8_t chanell, uint8_t preemption_priority, uint8_t sub_priority)
{
	uint32_t tmppriority = 0x00, tmpreg = 0x00, tmpmask = 0x00;
	uint32_t tmppre = 0, tmpsub = 0x0F;

	// Compute the Corresponding IRQ Priority
	tmppriority = (0x700 - (SCB->AIRCR & (uint32_t)0x700))>> 0x08;
	tmppre = (0x4 - tmppriority);
	tmpsub = tmpsub >> tmppriority;

	tmppriority = (uint32_t)preemption_priority << tmppre;
	tmppriority |=  sub_priority & tmpsub;

	tmppriority = tmppriority << 0x04;
	tmppriority = ((uint32_t)tmppriority) << ((chanell & 0x03) * 0x08);

	tmpreg = NVIC->IP[(chanell >> 0x02)];
	tmpmask = (uint32_t)0xFF << ((chanell & 0x03) * 0x08);
	tmpreg &= ~tmpmask;
	tmppriority &= tmpmask;
	tmpreg |= tmppriority;

	NVIC->IP[(chanell >> 0x02)] = tmpreg;

	// Enable the Selected IRQ Channel
	NVIC->ISER[(chanell >> 0x05)] = (uint32_t)0x01 << (chanell & 0x1F);
} /* HAL_PORT_NVIC_IRQInit */


// -----------------------------------------------------------------------------
//  HAL_PORT_NVIC_IRQDeinit
// -----------------------------------------------------------------------------
void HAL_PORT_NVIC_IRQDeinit(uint8_t chanell)
{
	// Disable the Selected IRQ Channel
	NVIC->ICER[(chanell >> 0x05)] = (uint32_t)0x01 << (chanell & 0x1F);

} /* HAL_PORT_NVIC_IRQDeinit */


/* -----------------------------------------------------------------------------
    HAL_PORT_NVIC_PriorityGroupConfig
   -----------------------------------------------------------------------------
   *      This parameter can be one of the following values:
   *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
   *                                4 bits for subpriority
   *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
   *                                3 bits for subpriority
   *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
   *                                2 bits for subpriority
   *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
   *                                1 bits for subpriority
   *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
   *                                0 bits for subpriority
*/

void HAL_PORT_NVIC_PriorityGroupConfig(uint32_t nvic_priority_group)
{
	 // Set proper priority group
	 SCB->AIRCR = ((uint32_t)0x05FA0000) | nvic_priority_group;

} /* HAL_PORT_NVIC_PriorityGroupConfig */

