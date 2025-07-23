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

#include "hal_txtdevice.h"
#include <string.h>
#include <stdio.h>

// -----------------------------------------------------------------------------
//  TXTDEV_WriteString
// -----------------------------------------------------------------------------
void TXTDEV_WriteString(IODevice device, const char* str)
{
    IODEV_Write(device, (char*)str, strlen(str), 0);

} /* TXTDEV_WriteString */


// -----------------------------------------------------------------------------
//  TXTDEV_WriteINT
// -----------------------------------------------------------------------------
void TXTDEV_WriteINT(IODevice device, int32_t value, uint8_t base)
{
    char buffLogUINT[32];
    int32_t i, size;
    int32_t x, digit; // digit value

    if (device) {
        //check sign
        if (value < 0) {
            buffLogUINT[0] = '-';
            value = -value;
            size = 2;
        } else {
            size = 1;
        }

        //compute number of digits
        digit = base;

        for (; value >= digit; size++) {
            x = digit * base;

            if (digit > x) {
                //overflow - 0xFFFFFFFF reached
                size++;
                break;
            } else {
                digit = x;
            }
        }

        //convert
        x = 1;

        for (i = 1; size - i >= 0; i++) {
            digit = (value / x) % base;
            buffLogUINT[size - i] = '0' + digit + (digit > 9) * ('A' - 10 - '0');
            x *= base;
        }

        IODEV_Write(device, buffLogUINT, size, 0);
    }
} /* TXTDEV_WriteINT */


// -----------------------------------------------------------------------------
//  TXTDEV_WriteUINT
// -----------------------------------------------------------------------------
void TXTDEV_WriteUINT(IODevice device, uint32_t value, uint8_t base)
{
    char buffLogUINT[32];
    int32_t i, size;
    uint32_t x, digit;

    if (device) {
        //compute number of digits
        digit = base;

        for (size = 1; value >= digit; size++) {
            x = digit * base;

            if (digit > x) {
                //overflow - 0xFFFFFFFF reached
                size++;
                break;
            } else {
                digit = x;
            }
        }

        //convert
        x = 1;

        for (i = 1; size - i >= 0; i++) {
            digit = (value / x) % base;
            buffLogUINT[size - i] = '0' + (char)digit + (digit > 9) * ('A' - 10 - '0');
            x *= base;
        }

        IODEV_Write(device, buffLogUINT, size, 0);
    }
} /* TXTDEV_WriteUINT */


// -----------------------------------------------------------------------------
//  TXTDEV_WriteFLOAT
// -----------------------------------------------------------------------------
void TXTDEV_WriteFLOAT(IODevice device, float value, int precision)
{
    if (device) {
		TXTDEV_WriteINT(device, (int32_t)value, 10);

		value = value - (int32_t)value;

		if (precision > 0) {
			while (precision--) {
				value *= 10;
			}
		}
		if ((int32_t)value) {
			IODEV_Write(device, ".", 1, 0);
			TXTDEV_WriteINT(device, (int32_t)value, 10);
		}
    }

} /* TXTDEV_WriteFLOAT */


// -----------------------------------------------------------------------------
//  TXTDEV_WriteNL
// -----------------------------------------------------------------------------
void TXTDEV_WriteNL(IODevice device)
{
    IODEV_Write(device, "\n\r", 2, 0);
} /* TXTDEV_WriteNL */


// -----------------------------------------------------------------------------
//  TXTDEV_ReadString
// -----------------------------------------------------------------------------
void TXTDEV_ReadString(IODevice input_device, IODevice mirror_device, char* str, size_t max_len)
{
    unsigned int i = 0;

    do {
        i = 0;

        do {
            if (IODEV_Read(input_device, (void*)(str + i), 1, 0)) {
                if (! ((i == 0) && (*(str + i) == '\n' || *(str + i) == '\r'))) {
                    if (mirror_device) {
                        IODEV_Write(mirror_device, (char*)(str + i), 1, 0);
                    }
                }

                i++;
            }
        } while ( (str[i - 1] != '\n') && (str[i - 1] != '\r') && (i < max_len) );

        i--;
    } while (i < 1);

    str[i] = 0;
} /* TXTDEV_ReadString */
