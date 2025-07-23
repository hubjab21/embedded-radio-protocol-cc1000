/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_pwr.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       PWR module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_PWR_H
#define HAL_PWR_H

#include <stdint.h>
#include "hal_config.h"
#include "hal_defs.h"

/** \defgroup hal_pwr PWR module
 *
 * <b>Introduction.</b>
 *
 * This module handles power mode switching.
 *
 * TODO!
 */
/*@{*/

// -----------------------------------------------------------------------------
//  PUBLIC TYPEDEFS
// -----------------------------------------------------------------------------

//typedef enum {
//	/**
//	 * Default power mode for the port. This usually maps to ACTIVE mode.
//	 * Check port documentation for details.
//	 */
//	HAL_CORE_POWER_MODE_DEFAULT = 0,
//	/**
//	 *
//	 */
//	HAL_CORE_POWER_MODE_ACTIVE,
//	/**
//	 *
//	 */
//	HAL_CORE_POWER_MODE_LOW_POWER,
//	/**
//	 *
//	 */
//	HAL_CORE_POWER_MODE_SLEEP,
//	/**
//     *
//	 */
//	HAL_CORE_POWER_MODE_HIBERNATE,
//	/**
//	 * The core can be waken up just by reset or any other event
//	 * with this same result. After wake-up the program starts from
//	 * the beginning.
//	 */
//	HAL_CORE_POWER_MODE_STOP
//} HAL_CORE_POWER_MODES;

// -----------------------------------------------------------------------------
//  PUBLIC API
// -----------------------------------------------------------------------------

/**
 * Sets processor power mode
 * This function should never be called from an interrupt!
 *
 *  \param mode power mode that we want to set
 *  \return set mode or -1 if this operation was not possible
 */
#define CORE_SetPowerMode(mode)			CORE_PORT_SetPowerMode(mode)

/**
 * Gets processor power mode
 */
#define CORE_GetPowerMode()				CORE_PORT_GetPowerMode()

/**
 * Refreshes processor power mode
 */
#define CORE_RefreshPowerMode()			CORE_PORT_RefreshPowerMode()


/*@}*/



#endif /* HAL_PWR_H */
