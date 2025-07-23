/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_delay.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       HAL DELAY module API
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_DELAY_H
#define HAL_DELAY_H

#include "hal_port_delay.h"

/** \defgroup hal_delay DELAY module
 *
 * <b>Introduction.</b>
 *
 * DELAY module provides functionality of delay loops.
 */
/*@{*/

/**
 *  Delays further operation by a specified time (in miliseconds)
 *  \param ms time in miliseconds
 */
#define DELAY_MS(ms) HAL_PORT_DELAY_MS((ms))

/**
 *  Delays further operation by a specified time (in microseconds)
 *  \param us time in microseconds
 */
#define DELAY_US(us) HAL_PORT_DELAY_US((us))

/**
 *  Delays further operation by a specified time (in nanoseconds)
 *  \param ns time in nanoseconds
 */
#define DELAY_NS(ns) HAL_PORT_DELAY_NS((ns))

/*@}*/

/*! \file hal_delay.h
    \brief delay module api
*/

#endif /* HAL_DELAY_H */
