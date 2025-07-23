/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			cc1000.h
 Author:        Lukasz Krzak, based on the work of M.Szczurkowski & T.Kruszec
 Purpose:       universal module
 Compiler:      %COMPILER%
 Hardware:      independent, based on HALFRED
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       CC1000 radio transceiver driver
--------------------------------------------------------------------------------
 Comments:		This driver uses GPIO pins to configure CC1000. The following
                GPIO signals must be defined:
                                PDATA (input/output), PCLK (output), PALE (output)
================================================================================
*/

#ifndef CC1000_H
#define CC1000_H

#include <stdint.h>

/** \defgroup cc1000 CC1000 transceiver driver
 *  \code
 *  #include "cc1000.h"
 *  \endcode
 *
 *  This module provides basic low level functions that handle CC1000 transceiver
 *  from Texas Instruments.
 */
/*@{*/

/// Enumeration denoting state of the CC1000 transceiver
typedef enum {
    CC1000_IDLE,
    CC1000_SLEEP,
    CC1000_RX,
    CC1000_TX,
} CC1000_State;

/**
 *  Initializes resources needed for the driver. Must be called prior to any other
 *  function of this module.
 */
void CC1000_Init(void);

/**
 *  Configures CC1000 using a set of default register values.
 */
void CC1000_DefaultConfiguration(void);

/**
 *  Low level function that writes to a CC1000 register under a given address with
 *  a given byte of data.
 *  \param addr register address
 *  \param data byte to write
 *  \return 0 if successful, !0 otherwise
 */
uint8_t CC1000_WriteRegister(uint8_t addr, uint8_t data);

/**
 *  Low level function that reads from a CC1000 register under a given address.
 *  \param addr register address
 *  \return data read from the register
 */
uint8_t CC1000_ReadRegister(uint8_t addr);

/**
 *  Resets CC1000.
 */
void CC1000_Reset(void);

/**
 *  Puts CC1000 into power down mode.
 */
void CC1000_PowerDown(void);

/**
 *  Initializes VCO in CC1000. This function should be called after each power-up
 *  of CC1000 transceiver.
 *  \return 0 if calibration was successful, !0 otherwise
 */
uint8_t CC1000_Calibrate(void);

/**
 *  Sets center frequency.
 *  \param frequency frequency in Hz
 */
void CC1000_SetFrequency(uint32_t frequency);

/**
 *  Switches CC1000 into transmission mode.
 */
void CC1000_SwitchToTX(void);

/**
 *  Switches CC1000 into reception mode.
 */
void CC1000_SwitchToRX(void);

/**
 *  Gets current state of operation.
 */
CC1000_State CC1000_GetState(void);


void CC1000_SetLevel(int8_t level);
/*@}*/

#endif // CC1000_H
