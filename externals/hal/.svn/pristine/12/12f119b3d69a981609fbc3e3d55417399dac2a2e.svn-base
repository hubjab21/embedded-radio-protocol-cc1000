/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_core.h
 Author:        Łukasz Krzak, Piotr Wojtowicz
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CORE module API
--------------------------------------------------------------------------------
 Comments:      
================================================================================
*/

#ifndef HAL_CORE_H
#define HAL_CORE_H

#include <stdint.h>
#include "hal_config.h"

/** \defgroup hal_core CORE module
 * 
 * <b>Introduction.</b>
 * 
 * This module implements the basic functionality of a processor core.
 * It provides the main initialization and deinitialization functions,
 * that can be used to implement startup/system setup and safe shutdown.
 * It also provides necessary abstraction functions to implement atomic
 * code blocks (critical sections).
 * 
 * <b>Initialization and deinitialization.</b>
 * 
 * The CORE initialization is used to initialize the port of HAL. The exact
 * functionality behind this may vary with processor architecture. Some
 * examples include configuring power management, clocks, internal PLLs etc.
 * Note, that \ref CORE_Init invokes port's <b>CORE_PORT_Init</b>.
 * 
 * The deinitialization of CORE module also strongly depends on the 
 * system architecture. Typical examples of \ref CORE_Deinit usage would be:
 * shutting down voltage regulators, external reset, dumping volatile memories
 * etc. 
 * 
 * <b>Interrupts.</b>
 *
 * The CORE module handles global interrupt state through \ref CORE_EnableInterrupts
 * and \ref CORE_DisableInterrupts.
 * 
 * <b>Critical sections.</b>
 * 
 * Very often it is necessary to make a block of code indivisible. Such blocks
 * are called critical sections. The implementation of critical section is
 * processor and system dependent, however the most common way of achieving
 * such behavior is to block (disable) all interrupts at the beginning of
 * the atomic code block and re-enable them at it's end. In such implementation
 * the \ref CORE_EnterCritical would disable interrupts and \ref CORE_ExitCritical
 * would re-enable them. Some care must be taken in order to implement nestable 
 * critical section, however the HAL interface does not specify whether they
 * should or shouldn't be nestable. It's up to the user, or more precisely: 
 * HAL port developer.
 * 
 */ 
/*@{*/

/** 
 * Initializes HAL and all the underlying hardware 
 */ 
#define CORE_Init()					CORE_PORT_Init()

/** 
 * Deinitializes HAL and all the underlying hardware 
 */
#define CORE_Deinit()				CORE_PORT_Deinit()

/**
 * Starts a critical section 
 */
#define CORE_EnterCritical()    	CORE_PORT_EnterCritical()

/** 
 * Ends a critical section
 */
#define CORE_ExitCritical()     	CORE_PORT_ExitCritical()

/** 
 * Enables interrupts globally
 */
#define CORE_EnableInterrupts()		CORE_PORT_EnableInterrupts()

/** 
 * Disables interrupts globally
 */
#define CORE_DisableInterrupts()	CORE_PORT_DisableInterrupts()

#if (defined HAL_ENABLE_OS) && (HAL_ENABLE_OS)
#define CORE_GetSystemTime()    	OS_PORT_GetSystemTime()
#else
/**
 * Returns the current system time (usually the number of system ticks that elapsed since reset.
 * If OS module is enabled, the implementation of this function is the HAL_OS_PORT_GetSystemTime, else
 * the implementation is actually CORE_PORT_GetSystemTime
 */
#define CORE_GetSystemTime()    	CORE_PORT_GetSystemTime()
#endif


/*@}*/

/*! \file hal_core.h
    \brief HAL CORE module definition

 */

#endif /* HAL_CORE_H */
