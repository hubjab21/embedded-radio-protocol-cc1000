/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_nvic.h
 Author:        Michal Kochanowski
 Purpose:       HALFRED's SAM3S port
 Compiler:      %COMPILER%
 Hardware:      Atmel SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       NVIC module port for Atmel SAM3S
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PORT_NVIC_H_
#define HAL_PORT_NVIC_H_

// -----------------------------------------------------------------------------
//  Defines of PriorityGroup
// -----------------------------------------------------------------------------

#define HAL_NVIC_PRIORITY_GROUP_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define HAL_NVIC_PRIORITY_GROUP_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define HAL_NVIC_PRIORITY_GROUP_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define HAL_NVIC_PRIORITY_GROUP_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define HAL_NVIC_PRIORITY_GROUP_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */

// -----------------------------------------------------------------------------
//  Public macros
// -----------------------------------------------------------------------------

void HAL_PORT_NVIC_IRQInit(uint8_t chanell, uint8_t preemption_priority, uint8_t sub_priority);

void HAL_PORT_NVIC_IRQDeinit(uint8_t chanell);

void HAL_PORT_NVIC_PriorityGroupConfig(uint32_t nvic_priority_group);


#endif /* HAL_PORT_NVIC_H_ */
