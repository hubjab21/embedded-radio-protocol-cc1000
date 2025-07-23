/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_core.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CLK module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_CLK_H
#define HAL_CLK_H

#include <stdint.h>
#include "hal_config.h"
#include "hal_defs.h"

/** \defgroup hal_clk CLK module
 *
 * <b>Introduction.</b>
 *
 * This module handles clock generation, configuration and distribution through
 * a concept of ClockController.
 *
 */
/*@{*/

// -----------------------------------------------------------------------------
//  PUBLIC TYPEDEFS
// -----------------------------------------------------------------------------

/// Clock controller handler
typedef struct ClockControllerDesc* ClockController;

/// Clock controller descriptor
struct ClockControllerDesc {
    HALRESULT (*Init)(ClockController cc);
    HALRESULT (*Deinit)(ClockController cc);
    HALRESULT (*SetClockSource)(ClockController cc, int clk, int clk_src, uint32_t freq);
    int (*GetClockSource)(ClockController cc, int clk);
    uint32_t (*GetClockSourceFreq)(ClockController cc, int clk_src);
    uint32_t (*SetClockFrequency)(ClockController cc, int clk, uint32_t freq);
    uint32_t (*GetClockFrequency)(ClockController cc, int clk);
};


// -----------------------------------------------------------------------------
//  PUBLIC API
// -----------------------------------------------------------------------------

/// Identifier of a default system clock (usually main clock of the CPU)
#define CC_DEFAULT_CLOCK				0

/**
 *  Initializes the clock controller.
 *
 *  \param cc handle of the clock controller
*/
#define CC_Init(cc)						(cc)->Init(cc)

/**
 *  Deinitializes the clock controller.
 *
 *  \param cc handle of the clock controller
 */
#define CC_Deinit(cc)					(cc)->Deinit(cc)

/**
 *  Sets a clock source for a given clock
 *
 *  \param cc handle of the clock controller
 *  \param clk clock (CORE_DEFAULT_CLOCK for default clock)
 *  \param clk_src clock source
 *  \param freq frequency of the clock source (in ex. XTAL frequency) or 0 if default frequency should be used
 *  \return HALRESULT_OK if the operation was successful, HALRESULT_ERROR otherwise
 */
#define CC_SetClockSource(cc, clk, clk_src, freq)	(cc)->SetClockSource((cc), (clk), (clk_src), (freq))

/**
 * Gets the clock source that is currently used for a given clock
 *
 *  \param cc handle of the clock controller
 *  \param clk clock (CORE_DEFAULT_CLOCK for default clock)
 *  \return currently used clock source number
 */
#define CC_GetClockSource(cc, clk)				(cc)->GetClockSource((cc), (clk))

/**
 *  Gets the frequency of the clock source, that is currently used for a given clock
 *  \param cc handle of the clock controller
 *  \param clk clock (CORE_DEFAULT_CLOCK for default clock)
 *  \return clock source frequency (0 means that the clock is not enabled or not available)
 */
#define CC_GetClockSourceFreq(cc, clk)			(cc)->GetClockSourceFreq((cc), (clk))

/**
 * Sets frequency of a given clock
 *
 *  \param cc handle of the clock controller
 *  \param clk clock to set (CORE_DEFAULT_CLOCK for default clock)
 *  \param freq frequency that we want to set (depending on the port capabilities, value of 0 may switch off the clock)
 *  \return HALRESULT_OK if the operation was successful, HALRESULT_ERROR otherwise
 */
#define CC_SetClockFreq(cc, clk, freq)			(cc)->SetClockFreq((cc), (clk), (freq))

/**
 * Gets frequency of a given clock
 *
 *  \param cc handle of the clock controller
 *  \param clk clock (CORE_DEFAULT_CLOCK for default clock)
 *  \return frequency of the clock (0 means that the clock is not enabled or not available)
 */
#define CC_GetClockFreq(cc, clk)					(cc)->GetClockFrequency((cc), (clk))

/*@}*/


#endif /* HAL_CLK_H */
