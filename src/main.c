/*
================================================================================
 File: main.c
--------------------------------------------------------------------------------
 Author:
 Purpose:
 Compiler:      GCC
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Includes:
--------------------------------------------------------------------------------
 Comments:      Requires HAL
================================================================================
*/

#include "hal.h"

#include "cc1000.h"
#include "cli_cmd_proc.h"


// Declare Command Line Interface (CLI) console
CLI_DECLARE(cli, IO_TERMINAL, CLI_CommandProcessor, );

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void) {
    // Initialize HAL core
    CORE_Init();
    CORE_EnableInterrupts();

    // Initialize GPIO module
    GPIO_Init();

    // Configure LED pins
    GPIO_ConfigurePin(LED0, OUTPUT);
    GPIO_ConfigurePin(LED1, OUTPUT);
    GPIO_ConfigurePin(LED2, OUTPUT);
    GPIO_ConfigurePin(LED3, OUTPUT);
    GPIO_SetPinHigh(LED0);
    GPIO_SetPinHigh(LED1);
    GPIO_SetPinHigh(LED2);
    GPIO_SetPinHigh(LED3);

    // Initialize IODevices
    IODEV_Init(IO_TERMINAL);
    IODEV_EnableWrite(IO_TERMINAL);
    IODEV_EnableRead(IO_TERMINAL);

    IODEV_Init(IO_RADIO);
    IODEV_EnableWrite(IO_RADIO);
    IODEV_EnableRead(IO_RADIO);

    // Initialize application timer
    TIM_Init(TIMER, 1000000);

    // Initialize CC1000
    CC1000_Init();
    CC1000_Reset();
    CC1000_DefaultConfiguration();
    CC1000_SwitchToTX();
    CC1000_Calibrate();
    CC1000_SwitchToRX();
    CC1000_Calibrate();

    // Clear console screen and display main menu
    CLI_DisplayMainScreen(cli);
    // Force command mode
    CLI_ForceCommandMode(cli);

    while (1) {
        // Process the console
        CLI_ProcessConsole(cli);
        CLI_ContinuousTxProc();
        CLI_DataReception();
    }

    // Deinitialize HAL
    GPIO_Deinit();
    CORE_Deinit();
    return 0;

} /* main */
