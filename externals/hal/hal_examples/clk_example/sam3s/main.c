/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          main.c
 Author:        Łukasz Krzak, Piotr Wojtowicz, Michal Kochanowski
 Purpose:       HALFRED's TIM module example
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses CLK module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// HAL files
#include <stdint.h>
#include "hal.h"



void reInitUsart(IODevice iodevice){
	IODEV_Deinit(iodevice);
	IODEV_Init(iodevice);
	IODEV_EnableRead(iodevice);
	IODEV_EnableWrite(iodevice);
}

void printClockInfo(){

	const char clock_sources_name[8][30] = {
			"SAM3S_RC_CLOCK_SOURCE",
			"SAM3S_XTAL_CLOCK_SOURCE",
			"SAM3S_EXTERNAL_CLOCK_SOURCE",
			"SAM3S_SLOW_CLOCK_SOURCE",
			"SAM3S_MAIN_CLOCK_SOURCE",
			"SAM3S_PLLA_CLOCK_SOURCE",
			"SAM3S_PLLB_CLOCK_SOURCE",
			"SAM3S_UNKNOWN_CLOCK_SOURCE"
	};

    DIAG0_LogMsg(0,"GetClockSource (MAIN_CLK): ");
    DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK)]);

    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSource (SLCK_CLK): ");
    DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_sam3s, SAM3S_SLOW_CLOCK)]);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSource (MASTER_CLK): ");
    DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK)]);
    DIAG0_LogNL(0);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSourceFreq (SAM3S_RC_CLOCK_SOURCE): ");
    DIAG0_LogINT(0,CC_GetClockSourceFreq(cc_sam3s, SAM3S_RC_CLOCK_SOURCE), 10);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSourceFreq (SAM3S_XTAL_CLOCK_SOURCE): ");
    DIAG0_LogINT(0,CC_GetClockSourceFreq(cc_sam3s, SAM3S_XTAL_CLOCK_SOURCE), 10);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSourceFreq (SAM3S_SLOW_CLOCK_SOURCE): ");
    DIAG0_LogINT(0,CC_GetClockSourceFreq(cc_sam3s, SAM3S_SLOW_CLOCK_SOURCE), 10);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockSourceFreq (SAM3S_MAIN_CLOCK_SOURCE): ");
    DIAG0_LogINT(0,CC_GetClockSourceFreq(cc_sam3s, SAM3S_MAIN_CLOCK_SOURCE), 10);
    DIAG0_LogNL(0);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockFrequency (MAIN_CLK): ");
    DIAG0_LogINT(0,CC_GetClockFreq(cc_sam3s, SAM3S_MAIN_CLOCK), 10);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockFrequency (SLCK_CLK): ");
    DIAG0_LogINT(0,CC_GetClockFreq(cc_sam3s, SAM3S_SLOW_CLOCK), 10);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"GetClockFrequency (MASTER_CLK): ");
    DIAG0_LogINT(0,CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK), 10);
    DIAG0_LogNL(0);
    DIAG0_LogNL(0);

}

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void){


    // initialize HAL core
    CORE_Init();
	// initialize clock controller
	CC_Init(cc_sam3s);
	// Master clock on pin
	SAM3S_Clock_On_Pin(CLK_ON_PIN);
	// setup main clock
	CC_SetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK, SAM3S_RC_CLOCK_SOURCE, 7000000);

	// setup master clock
	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_MAIN_CLOCK_SOURCE, 3500000);

	// initialize IO interface for the lamp
	IODEV_Init(IO_DEBUG);
	IODEV_EnableRead(IO_DEBUG);
	IODEV_EnableWrite(IO_DEBUG);

    // initialize diagnostics
    DIAG_Init();
    DIAG_SetOutputDevice(0, IO_DEBUG);
    DIAG_ActivateChannel(0);

    DIAG0_LogMsg(0,"Clock Module demo:");
    DIAG0_LogNL(0);
    DIAG0_LogMsg(0,"Algorithm will try to choose the best possibility clock setting.");
    DIAG0_LogNL(0);
    DIAG0_LogNL(0);

    DIAG0_LogMsg(0,"I. Actual setting: Embedded RC Oscillator set to 7Mhz, Internal 32kHz Oscillator");
    DIAG0_LogNL(0);
    DIAG0_LogMsg(0,"I. Result of trying 3 500 000 Hz Master Clock");
    DIAG0_LogNL(0);

	printClockInfo();

	CC_SetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK, SAM3S_XTAL_CLOCK_SOURCE, SAM3S_XTAL_FREQ);
	CC_SetClockSource(cc_sam3s, SAM3S_SLOW_CLOCK, SAM3S_XTAL_CLOCK_SOURCE, 32768);
	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_MAIN_CLOCK_SOURCE, 8000000);

	reInitUsart(IO_DEBUG);

	DIAG0_LogNL(0);
    DIAG0_LogMsg(0,"II. Actual setting: External 12MHz, External 32768Hz Oscillator");
    DIAG0_LogNL(0);
    DIAG0_LogMsg(0,"II. Result of trying 8 000 000 Hz Master Clock");
    DIAG0_LogNL(0);

	printClockInfo();

	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_MAIN_CLOCK_SOURCE, 15000000);

	reInitUsart(IO_DEBUG);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"III. Actual setting: External 12MHz, External 32768Hz Oscillator");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"III. Result of trying 15 000 000 Hz Master Clock");
	DIAG0_LogNL(0);



	printClockInfo();


	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_PLLA_CLOCK_SOURCE,47500000);

	reInitUsart(IO_DEBUG);
	IODEV_Write(IO_DEBUG, "OK", 2, 0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"IV. Actual setting: External 12MHz with PLL, External 32768Hz Oscillator");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"IV. Result of trying 47 500 000 Hz Master Clock");
	DIAG0_LogNL(0);

	//PLLA on pin
	SAM3S_Clock_On_Pin(CLK_ON_PIN1);
	printClockInfo();

	// deinitialize DIAG module
	DIAG_Deinit();

	// deinitialize IODevices
	IODEV_Deinit(IO_DEBUG);

	CC_Deinit(cc_sam3s);
    CORE_Deinit();

    return 0;

} /* main */

