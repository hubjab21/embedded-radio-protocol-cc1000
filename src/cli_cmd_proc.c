/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			cli_cmd_proc.c
 Author:
 Purpose:       BSKS Lab
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       command line procedure definitions
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

#include "hal.h"

#include "cc1000.h"

#include <stdbool.h>
#include <string.h>


// temporary buffer for commands
static char item[32];
static bool txProc;
const char  CLI_CMD_OK[]     = " OK";
const char  CLI_CMD_FAILED[] = " FAILED";

static uint16_t UpdateCRC(uint8_t byte, uint16_t crc) {
    // CRC-CCITT without LUT
    byte ^= (uint8_t)(crc & 0x00ff);
    byte ^= (uint8_t)(byte << 4);
    return ((((uint16_t)byte << 8) | (uint8_t)(crc >> 8)) ^ (uint8_t)(byte >> 4) ^ ((uint16_t)byte << 3));
}

// -----------------------------------------------------------------------------
//  CLI_CommandProcessor
// -----------------------------------------------------------------------------
void CLI_CommandProcessor(CLIConsole cli) {
    IODevice iodevice;
    int32_t  addr, value;
    uint64_t time;

    iodevice = CLI_GetIODevice(cli);

    // get command from command line
    CLI_GetCommand(cli, item);

    if (0 == strcmp((char*)item, "rr")) {
        // read register command
        // get address
        CLI_GetNextArgInt32(cli, &addr);
        TXTDEV_WriteString(iodevice, "=0x");
        TXTDEV_WriteINT(iodevice, CC1000_ReadRegister((uint8_t)addr), 16);
        TXTDEV_WriteNL(iodevice);
        return;
    }
    if (0 == strcmp((char*)item, "wr")) {
        // write register command
        // get address
        CLI_GetNextArgInt32(cli, &addr);
        // get value
        CLI_GetNextArgInt32(cli, &value);
        CC1000_WriteRegister((uint8_t)addr, (uint8_t)value);
        // check if write was successful
        if ((uint8_t)value == CC1000_ReadRegister((uint8_t)addr)) {
            // write OK
            TXTDEV_WriteString(iodevice, CLI_CMD_OK);
        } else {
            // write failed
            TXTDEV_WriteString(iodevice, CLI_CMD_FAILED);
        }
        TXTDEV_WriteNL(iodevice);
        return;
    }
    if (0 == strcmp((char*)item, "setfreq")) {
        // write register command
        // get value
        CLI_GetNextArgInt32(cli, &value);
        CC1000_SetFrequency((uint32_t)value);
        TXTDEV_WriteNL(iodevice);
        return;
    }
    if (0 == strcmp((char*)item, "def")) {
        // default config command
        CC1000_Reset();
        CC1000_DefaultConfiguration();
        CC1000_Calibrate();
        TXTDEV_WriteNL(iodevice);
        return;
    }
    if (0 == strcmp((char*)item, "t")) {
        // get time command
        TXTDEV_WriteString(iodevice, "=");
        time = TIM_GetTimeInNS(TIMER);
        TXTDEV_WriteINT(iodevice, (int32_t)(time / 1000000), 10);
        TXTDEV_WriteString(iodevice, "ms");
        TXTDEV_WriteNL(iodevice);

        return;
    }
    if (0 == strcmp((char*)item, "tl")) {
        // test leds command
        GPIO_SetPinLow(LED0);
        DELAY_MS(500);
        GPIO_SetPinLow(LED1);
        DELAY_MS(500);
        GPIO_SetPinLow(LED2);
        DELAY_MS(500);
        GPIO_SetPinLow(LED3);
        DELAY_MS(500);
        GPIO_SetPinHigh(LED0);
        DELAY_MS(500);
        GPIO_SetPinHigh(LED1);
        DELAY_MS(500);
        GPIO_SetPinHigh(LED2);
        DELAY_MS(500);
        GPIO_SetPinHigh(LED3);
        DELAY_MS(500);
        TXTDEV_WriteNL(iodevice);
        return;
    }
    if (0 == strcmp((char*)item, "txc")) {
        // 1.02
        CC1000_SwitchToTX();
        TXTDEV_WriteString(iodevice, "\n work");
    }
    if (0 == strcmp((char*)item, "setlev")) {
        // 1.03
        int32_t power;
        CLI_GetNextArgInt32(cli, &power);
        TXTDEV_WriteString(iodevice, "\n setlevel ");
        TXTDEV_WriteINT(iodevice, power, 10);
        if (power < -10) {
            power = -10;
        } else if (power > 10) {
            power = 10;
        }
        CC1000_SetLevel((int8_t)power);
    }
    // unrecognized command
    TXTDEV_WriteNL(iodevice);

    if (0 == strcmp((char*)item, "txmodon")) {
        txProc = true;
        CC1000_SwitchToTX();
    }


    if (0 == strcmp((char*)item, "txmodoff")) {
        txProc = false;
        // wait for buffer flush
        while (IODEV_GetWriteSpace(IO_RADIO) < HALPORT_USART0_TXBUF_SIZE) {
            ;
        }
        DELAY_MS(2); // wait for the last character to be sent
        CC1000_SwitchToRX();
    }

    if (0 == strcmp((char*)item, "rxon")) {
        CC1000_SwitchToRX();
        while (1) {
            if (IODEV_GetReadCount(IO_RADIO)) {
                uint8_t bufor;
                IODEV_Read(IO_RADIO, &bufor, sizeof(bufor), 0);
                IODEV_Write(IO_TERMINAL, &bufor, sizeof(bufor), 0);
            }
        }
    }

    if (0 == strcmp((char*)item, "sendb")) {
        uint8_t data[100];
        CLI_GetNextArg(cli, (char*)&data[0]);
        TXTDEV_WriteNL(iodevice);
        TXTDEV_WriteString(iodevice, (char*)data);
        TXTDEV_WriteNL(iodevice);

        CC1000_SwitchToTX();
        uint8_t d = 0x55;
        for (size_t i = 0; i < 6; ++i) {
            IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        }
        d = 0xff;
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        d = 0x3c;
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        d            = 0x11;
        uint16_t crc = 0xffff;
        crc          = UpdateCRC(d, crc);
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        d   = 0xff;
        crc = UpdateCRC(d, crc);
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        d   = (uint8_t)strlen((char*)data);
        crc = UpdateCRC(d, crc);
        IODEV_Write(IO_RADIO, &d, sizeof(d), 0);
        IODEV_Write(IO_RADIO, data, d, 0);
        for (size_t i = 0; i < d; ++i) {
            crc = UpdateCRC(data[i], crc);
        }
        IODEV_Write(IO_RADIO, &crc, sizeof(crc), 0);

        while (IODEV_GetWriteSpace(IO_RADIO) < HALPORT_USART0_TXBUF_SIZE) {
            ;
        }
        DELAY_MS(2); // wait for the last character to be sent
        CC1000_SwitchToRX();
    }


    if (0 == strcmp((char*)item, "listen")) {
        TXTDEV_WriteString(IO_TERMINAL, "crc ");
    }
} /* CLI_CommandProcessor */


void CLI_ContinuousTxProc(void) {
    if (txProc) {
        static const uint8_t dane = 0x55;
        if (IODEV_GetWriteSpace(IO_RADIO)) {
            IODEV_Write(IO_RADIO, &dane, sizeof(dane), 0);
        }
    }
}


typedef enum {
    SFD_1,
    SFD_2,
    SRC_ADDR,
    DST_ADDR,
    DATA_SIZE,
    DATA,
    CRC_1,
    CRC_2,
} State;

bool CLI_DataReception(void) {
    static char     data[41];
    static uint8_t  src_addr;
    static uint8_t  dst_addr;
    static uint8_t  size;
    static size_t   data_index;
    static uint16_t crc;


    uint8_t d;
    if (0 == IODEV_GetReadCount(IO_RADIO)) {
        return false;
    }

    IODEV_Read(IO_RADIO, &d, sizeof(d), 0);

    static State state;
    switch (state) {
        case SFD_1:
            if (d == 0x3c) {
                state = SFD_2;
            } else {
                state = SFD_1;
            }
            break;
        case SFD_2:
            if (d == 0x3c) {
                state = SRC_ADDR;
            } else {
                state = SFD_1;
            }
            break;
        case SRC_ADDR:
            src_addr = d;
            state    = DST_ADDR;
            break;
        case DST_ADDR:
            dst_addr = d;
            state    = DATA_SIZE;
            break;
        case DATA_SIZE:
            size = d;
            if (size > 40) {
                state = SFD_1;
            } else {
                data_index = 0;
                state      = DATA;
            }
            // TXTDEV_WriteString(IO_TERMINAL, "DATA SIZE: ");
            // TXTDEV_WriteUINT(IO_TERMINAL, size, 10);
            // TXTDEV_WriteNL(IO_TERMINAL);
            break;
        case DATA:
            data[data_index] = (char)d;
            ++data_index;
            if (size == data_index) {
                data[data_index] = '\0';
                state            = CRC_1;
            }
            break;
        case CRC_1:
            crc   = d;
            state = CRC_2;
            break;
        case CRC_2:
            crc += (uint16_t)d << 8;
            state = SFD_1;
            // TXTDEV_WriteString(IO_TERMINAL, "CRC: ");
            // TXTDEV_WriteUINT(IO_TERMINAL, crc, 16);
            // TXTDEV_WriteNL(IO_TERMINAL);
            // TXTDEV_WriteString(IO_TERMINAL, data);
            // TXTDEV_WriteNL(IO_TERMINAL);
            uint16_t test_crc = 0xffff;
            test_crc          = UpdateCRC(src_addr, test_crc);
            test_crc          = UpdateCRC(dst_addr, test_crc);
            test_crc          = UpdateCRC(size, test_crc);
            for (size_t i = 0; i < size; ++i) {
                test_crc = UpdateCRC(data[i], test_crc);
            }
            // TXTDEV_WriteString(IO_TERMINAL, "Test CRC: ");
            // TXTDEV_WriteUINT(IO_TERMINAL, test_crc, 16);
            // TXTDEV_WriteNL(IO_TERMINAL);
            break;
        default:
            break;
            if (test_crc == crc) {
                return true;
            }
    }

    return false;
}
