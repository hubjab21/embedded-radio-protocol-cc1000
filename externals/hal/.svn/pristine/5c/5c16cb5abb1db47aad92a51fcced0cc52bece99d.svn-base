/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_txtdevice.h
 Author:        Lukasz Krzak
 Purpose:       HALFRED utilities
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       Textual IODevice
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#ifndef HAL_TXTDEVICE_H
#define HAL_TXTDEVICE_H

/** \defgroup hal_txtdevice TXTDevice interface
 *
 * <b>Introduction.</b>
 *
 * The TXTDevice interface is used for sending and receiving textual data through
 * IODevices (see \ref hal_iodevice) such as UART.
 *
 */
/*@{*/

#include <stdint.h>
#include "hal_iodevice.h"

/**
 *  Writes a NULL-terminated string to an IODevice.
 *
 *  \param device IODevice to write to
 *  \param str NULL-terminated string to write
 */
void TXTDEV_WriteString(IODevice device, const char *str);

/**
 *  Converts a 32bit signed integer to string using specified base, and writes the result
 *  to the provided IODevice.
 *
 *  \param device IODevice to write to
 *  \param value signed 32bit integer value to write
 *  \param base conversion base (10 for decimal number, 16 for hex etc.)
 */
void TXTDEV_WriteINT(IODevice device, int32_t value, uint8_t base);

/**
 *  Converts a 32bit unsigned integer to string using specified base, and writes the result
 *  to the provided IODevice.
 *
 *  \param device IODevice to write to
 *  \param value unsigned 32bit integer value to write
 *  \param base conversion base (10 for decimal number, 16 for hex etc.)
 */
void TXTDEV_WriteUINT(IODevice device, uint32_t value, uint8_t base);

/**
 *  Converts a float number to a string and writes the result to the provided IODevice.
 *
 *  \param device IODevice to write to
 *  \param value float value to write
 *  \param precision number of digits after the dot
 */
void TXTDEV_WriteFLOAT(IODevice device, float value, int precision);

/**
 *  Writes new line terminator to a specified IODevice.
 *
 *  \param device IODevice to write to
 */
void TXTDEV_WriteNL(IODevice device);

/**
 *  Reads a string from input IODevice.
 *
 *  \param input_device input IODevice
 *  \param mirror_device an optional device that will receive the characters that
 *                       are received by input_device
 *  \param str destination buffer for the string
 *  \param max_len maximum size of the read string
 */
void TXTDEV_ReadString(IODevice input_device, IODevice mirror_device, char *str, size_t max_len);

/*@}*/

#endif /* HAL_TXTDEVICE_H */
