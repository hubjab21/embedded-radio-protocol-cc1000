/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			cc1000.c
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


#include "hal.h"

#include "cc1000.h"

#include "cc1000defs.h"


#define CC1000_EXT_OSC 14745600ULL
#define CC1000_DF      10000ULL
#define CC1000_FREF    (CC1000_EXT_OSC / 9)
#define CC1000_FSEP    ((CC1000_DF * 16384ULL) / CC1000_FREF)
#define CC1000_FREQ(f) (((f)*16384ULL / CC1000_FREF) - (CC1000_FSEP / 2) - 8192)


// CC1000 register definitions
#define CC1000_MAIN      0x00
#define CC1000_FREQ_2A   0x01
#define CC1000_FREQ_1A   0x02
#define CC1000_FREQ_0A   0x03
#define CC1000_FREQ_2B   0x04
#define CC1000_FREQ_1B   0x05
#define CC1000_FREQ_0B   0x06
#define CC1000_FSEP1     0x07
#define CC1000_FSEP0     0x08
#define CC1000_CURRENT   0x09
#define CC1000_FRONT_END 0x0a
#define CC1000_PA_POW    0x0b
#define CC1000_PLL       0x0c
#define CC1000_LOCK      0x0d
#define CC1000_CAL       0x0e
#define CC1000_MODEM2    0x0f
#define CC1000_MODEM1    0x10
#define CC1000_MODEM0    0x11
#define CC1000_MATCH     0x12
#define CC1000_FSCTRL    0x13
#define CC1000_FSHAPE7   0x14
#define CC1000_FSHAPE6   0x15
#define CC1000_FSHAPE5   0x16
#define CC1000_FSHAPE4   0x17
#define CC1000_FSHAPE3   0x18
#define CC1000_FSHAPE2   0x19
#define CC1000_FSHAPE1   0x1a
#define CC1000_FSDELAY   0x1b
#define CC1000_PRESCALER 0x1c
#define CC1000_TEST6     0x40
#define CC1000_TEST5     0x41
#define CC1000_TEST4     0x42
#define CC1000_TEST3     0x43
#define CC1000_TEST2     0x44
#define CC1000_TEST1     0x45
#define CC1000_TEST0     0x46

// CC1000 register bit definitions
#define RESET_N         0x01
#define LOCK_CONTINUOUS 0x01


// -----------------------------------------------------------------------------
//  CC1000_ClkPulse
//  Generates a negative pulse on PCLK line (falling edge first)
// -----------------------------------------------------------------------------
static inline void CC1000_ClkPulse(void) {
    GPIO_SetPinLow(PCLK);
    // small delay for data settling (approx. 125ns for 8MHz clock)
    __asm volatile("NOP" ::);
    GPIO_SetPinHigh(PCLK);

} /* CC1000_ClkPulse */


// -----------------------------------------------------------------------------
//  CC1000_WriteAddr
//  Writes 7bits of register address to CC1000
// -----------------------------------------------------------------------------
static void CC1000_WriteAddr(uint8_t addr) {
    uint8_t i;

    // to write address set PALE to 0
    GPIO_SetPinLow(PALE);

    // write 7 bits of address
    for (i = 0x40; i != 0; i >>= 1) {
        if (addr & i) {
            GPIO_SetPinHigh(PDATA);
        } else {
            GPIO_SetPinLow(PDATA);
        }
        // wait for data settling
        __asm volatile("NOP" ::);

        CC1000_ClkPulse();
    }
} /* CC1000_WriteAddr */


// -----------------------------------------------------------------------------
//  CC1000_Init
// -----------------------------------------------------------------------------
void CC1000_Init(void) {
    // initialize pins
    GPIO_ConfigurePin(PCLK, OUTPUT);
    GPIO_SetPinHigh(PCLK);
    GPIO_ConfigurePin(PDATA, OUTPUT);
    GPIO_SetPinHigh(PDATA);
    GPIO_ConfigurePin(PALE, OUTPUT);
    GPIO_SetPinHigh(PALE);

} /* CC1000_Init */


// -----------------------------------------------------------------------------
//  CC1000_DefaultConfiguration
// -----------------------------------------------------------------------------
void CC1000_DefaultConfiguration(void) {
    CC1000_WriteRegister(CC1000_MAIN, CC1000_REG00);
    CC1000_WriteRegister(CC1000_FREQ_2A, CC1000_REG01);
    CC1000_WriteRegister(CC1000_FREQ_1A, CC1000_REG02);
    CC1000_WriteRegister(CC1000_FREQ_0A, CC1000_REG03);
    CC1000_WriteRegister(CC1000_FREQ_2B, CC1000_REG04);
    CC1000_WriteRegister(CC1000_FREQ_1B, CC1000_REG05);
    CC1000_WriteRegister(CC1000_FREQ_0B, CC1000_REG06);
    CC1000_WriteRegister(CC1000_FSEP1, CC1000_REG07);
    CC1000_WriteRegister(CC1000_FSEP0, CC1000_REG08);
    CC1000_WriteRegister(CC1000_CURRENT, CC1000_REG09);
    CC1000_WriteRegister(CC1000_FRONT_END, CC1000_REG0A);
    CC1000_WriteRegister(CC1000_PA_POW, CC1000_REG0B);
    CC1000_WriteRegister(CC1000_PLL, CC1000_REG0C);
    CC1000_WriteRegister(CC1000_LOCK, CC1000_REG0D);
    CC1000_WriteRegister(CC1000_CAL, CC1000_REG0E);
    CC1000_WriteRegister(CC1000_MODEM2, CC1000_REG0F);
    CC1000_WriteRegister(CC1000_MODEM1, CC1000_REG10);
    CC1000_WriteRegister(CC1000_MODEM0, CC1000_REG11);
    CC1000_WriteRegister(CC1000_MATCH, CC1000_REG12);
    CC1000_WriteRegister(CC1000_FSCTRL, CC1000_REG13);
    CC1000_WriteRegister(CC1000_PRESCALER, CC1000_REG1C);

} /* CC1000_DefaultConfiguration */


// -----------------------------------------------------------------------------
//  CC1000_WriteRegister
// -----------------------------------------------------------------------------
uint8_t CC1000_WriteRegister(uint8_t addr, uint8_t data) {
    uint8_t i;

    // write register address
    CC1000_WriteAddr(addr);

    // to indicate write mode, LSB is set to 1
    GPIO_SetPinHigh(PDATA);
    CC1000_ClkPulse();
    // after writing register address we set PALE signal to 1
    GPIO_SetPinHigh(PALE);

    // write data to the register
    for (i = 0x80; i != 0; i >>= 1) {
        if (data & i) {
            GPIO_SetPinHigh(PDATA);
        } else {
            GPIO_SetPinLow(PDATA);
        }
        // small delay to settle the data
        __asm volatile("NOP" ::);

        CC1000_ClkPulse();
    }

    // verify register write by reading it and comparing to the given value
    if (CC1000_ReadRegister(addr) == data) {
        // write successful
        return 0;
    }

    // writing to the register failed
    return 1;

} /* CC1000_WriteRegister */


// -----------------------------------------------------------------------------
//  CC1000_ReadRegister
// -----------------------------------------------------------------------------
uint8_t CC1000_ReadRegister(uint8_t addr) {
    uint8_t i, result;

    // write register address
    CC1000_WriteAddr(addr);

    // to indicate write mode, LSB is set to 0
    GPIO_SetPinLow(PDATA);
    CC1000_ClkPulse();
    __asm volatile("NOP" ::);

    // set PDATA pin as input
    GPIO_ConfigurePin(PDATA, INPUT);

    // after writing register address we set PALE signal to 1
    GPIO_SetPinHigh(PALE);

    // read the register data
    result = 0;
    for (i = 0x80; i != 0; i >>= 1) {
        // read bit on the falling edge of PCLK
        GPIO_SetPinLow(PCLK);
        __asm volatile("NOP" ::);
        if (GPIO_ReadPin(PDATA)) {
            result |= i;
        }
        GPIO_SetPinHigh(PCLK);
    }

    // switch back PDATA pin to output
    GPIO_ConfigurePin(PDATA, OUTPUT);

    return result;

} /* CC1000_ReadRegister */


// -----------------------------------------------------------------------------
//  CC1000_Reset
// -----------------------------------------------------------------------------
void CC1000_Reset(void) {
    uint8_t main_reg_value;

    // save current state of MAIN register
    main_reg_value = CC1000_ReadRegister(CC1000_MAIN);

    // clear the RESET_N bit, this will also bring all other registers except MAIN
    // to default values.
    CC1000_WriteRegister(CC1000_MAIN, (uint8_t)(main_reg_value & (~RESET_N)));
    // set RESET_N bit high again to complete the reset procedure
    CC1000_WriteRegister(CC1000_MAIN, main_reg_value | RESET_N);

} /* CC1000_Reset */


// ---------------------------------------------------- -------------------------
//  CC1000_PowerDown
// -----------------------------------------------------------------------------
inline void CC1000_PowerDown(void) {
    // this brings CC1000 into power down mode
    CC1000_WriteRegister(CC1000_MAIN, 0x3f);
} /* CC1000_PowerDown */


// -----------------------------------------------------------------------------
//  CC1000_Calibrate
// -----------------------------------------------------------------------------
uint8_t CC1000_Calibrate(void) {
    uint8_t  pa_val;
    uint16_t timer;

    // save current state of PA_POW register (output power)
    pa_val = CC1000_ReadRegister(CC1000_PA_POW);
    // disable RF power amplifier during calibration
    CC1000_WriteRegister(CC1000_PA_POW, 0x00);
    // start calibration process
    CC1000_WriteRegister(CC1000_CAL, 0xA6);

    // poll the CAL register until calibration is finished or assumed timeout occurred
    timer = 0;
    while (((CC1000_ReadRegister(CC1000_CAL) & 0x08) == 0) && (timer < 10000)) {
        timer++;
    }

    // end the calibration process
    CC1000_WriteRegister(CC1000_CAL, 0x26);
    // bring power amplifier to it's saved state
    CC1000_WriteRegister(CC1000_PA_POW, pa_val);

    // check calibration
    if (CC1000_ReadRegister(CC1000_LOCK) & LOCK_CONTINUOUS) {
        // all OK!
        return 0;
    }

    // calibration failed
    return 1;

} /* CC1000_Calibrate */


// -----------------------------------------------------------------------------
//  CC1000_SetFrequency
// -----------------------------------------------------------------------------
void CC1000_SetFrequency(uint32_t frequency) {
    uint32_t freq;


    // channel A - RX
    freq = (uint32_t)CC1000_FREQ(frequency - (uint32_t)10700000);
    CC1000_WriteRegister(1, (uint8_t)(freq >> 16));
    CC1000_WriteRegister(2, (uint8_t)(freq >> 8));
    CC1000_WriteRegister(3, (uint8_t)(freq));

    // channel B - TX
    freq = (uint32_t)CC1000_FREQ(frequency);
    CC1000_WriteRegister(4, (uint8_t)(freq >> 16));
    CC1000_WriteRegister(5, (uint8_t)(freq >> 8));
    CC1000_WriteRegister(6, (uint8_t)(freq));

} /* CC1000_SetFrequency */


// -----------------------------------------------------------------------------
//  CC1000_SwitchToRX
// -----------------------------------------------------------------------------
void CC1000_SwitchToRX(void) {
    CC1000_WriteRegister(CC1000_CURRENT, 0x44);
    CC1000_WriteRegister(CC1000_PLL, 0x48);
    CC1000_WriteRegister(CC1000_MAIN, 0x11);

} /* CC1000_SwitchToRX */


// -----------------------------------------------------------------------------
//  CC1000_SwitchToTX
// -----------------------------------------------------------------------------
void CC1000_SwitchToTX(void) {
    CC1000_WriteRegister(CC1000_CURRENT, 0x81);
    CC1000_WriteRegister(CC1000_PLL, 0x48);
    CC1000_WriteRegister(CC1000_MAIN, 0xE1);

} /* CC1000_SwitchToTX */


// -----------------------------------------------------------------------------
//  CC1000_GetState
// -----------------------------------------------------------------------------
CC1000_State CC1000_GetState(void) {
    if (CC1000_ReadRegister(CC1000_MAIN) & 0x80) {
        return CC1000_TX;
    } else {
        return CC1000_RX;
    }
} /* CC1000_GetState */
uint8_t PA_POW[] = {0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0E, 0x0F, 0x40, 0x50, 0x50, 0x60, 0x70, 0x80, 0x90, 0xC0, 0xE0, 0xFF};

void CC1000_SetLevel(int8_t level) {
    CC1000_WriteRegister(CC1000_PA_POW, PA_POW[level + 10]);
}
