/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's CLK module example
 Compiler:      %COMPILER%
 Hardware:      efm32
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses CLK module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// include the one and only HAL header
#include "hal.h"

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------

int main(void)
{
	volatile unsigned int c = 0;

	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();

	HAL_GPIO_Init();
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);

	// initialize clock controller
	CC_Init(cc_efm32);

	// setup EFM32_LFRCO_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_LFXO_CLOCK, EFM32_XTAL32_CLOCK_SOURCE, 32768);
	// setup EFM32_HFRCO_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_HFXO_CLOCK, EFM32_XTAL_CLOCK_SOURCE, 48000000);
	// setup EFM32_HF_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_HF_CLOCK, EFM32_HFXO_CLOCK_SOURCE, 16000000);
	// setup EFM32_HFRCO_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_HFRCO_CLOCK, EFM32_RC_CLOCK_SOURCE, 14000000);
	// setup EFM32_HF_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_HF_CLOCK, EFM32_HFRCO_CLOCK_SOURCE, 7000000);
	// setup EFM32_HFCORE_CLOCK
	CC_SetClockSource(cc_efm32, EFM32_HFCORE_CLOCK, EFM32_HF_CLOCK_SOURCE, 7000000);
	// setup EFM32_HFPER_CLOCKaaaa
	CC_SetClockSource(cc_efm32, EFM32_HFPER_CLOCK, EFM32_HF_CLOCK_SOURCE, 7000000);
	// setup LFA
	CC_SetClockSource(cc_efm32, EFM32_LFA_CLOCK, EFM32_LFRCO_CLOCK_SOURCE, 32768);
	// setup LFB
	CC_SetClockSource(cc_efm32, EFM32_LFB_CLOCK, EFM32_LFRCO_CLOCK_SOURCE, 32768);
	// setup EFM32_LESENSE
	CC_SetClockSource(cc_efm32, EFM32_LESENSE_CLOCK, EFM32_LFA_CLOCK_SOURCE, 9000);
	// setup EFM32_RTC
	CC_SetClockSource(cc_efm32, EFM32_RTC_CLOCK, EFM32_LFA_CLOCK_SOURCE, 100);
	// setup EFM32_LETIMER0
	CC_SetClockSource(cc_efm32, EFM32_LETIMER0_CLOCK, EFM32_LFA_CLOCK_SOURCE, 1000);
	// setup EFM32_LELCD
	CC_SetClockSource(cc_efm32, EFM32_LELCD_CLOCK, EFM32_LFA_CLOCK_SOURCE, 5000);
	// setup EFM32_LEUART0
	CC_SetClockSource(cc_efm32, EFM32_LEUART0_CLOCK, EFM32_LFB_CLOCK_SOURCE, 16384);
	// setup EFM32_LEUART1
	CC_SetClockSource(cc_efm32, EFM32_LEUART1_CLOCK, EFM32_LFB_CLOCK_SOURCE, 1000);

    IODEV_Init(IO_DEV);
    IODEV_EnableWrite(IO_DEV);
    IODEV_EnableRead(IO_DEV);

	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV);
    DIAG_ActivateChannel(0);

	DIAG0_LogMsg(0,"Test zegara na EFM32F4 - START");
	DIAG0_LogNL(0);

	const char clock_sources_name[14][30] = {
			"EFM32_HFRCO_CLOCK_SOURCE",
			"EFM32_LFRCO_CLOCK_SOURCE",
			"EFM32_HFXO_CLOCK_SOURCE",
			"EFM32_LFXO_CLOCK_SOURCE",
			"EFM32_RC_CLOCK_SOURCE",
			"EFM32_XTAL_CLOCK_SOURCE",
			"EFM32_EXTERNAL_CLOCK_SOURCE",
			"EFM32_XTAL32_CLOCK_SOURCE",
			"EFM32_EXTERNAL32_CLOCK_SOURCE",
			"EFM32_HF_CLOCK_SOURCE",
			"EFM32_HFCORE_CLOCK_SOURCE",
			"EFM32_LFA_CLOCK_SOURCE",
			"EFM32_LFB_CLOCK_SOURCE",
			"EFM32_ULFRC0_CLOCK_SOURCE"
		};

	DIAG_LogMsg(0, "**********************************************************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "****************** CC_GetClockSource() *******************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "**********************************************************");

	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_HF_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_HF_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_HFRCO_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_HFRCO_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_HFXO_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_HFXO_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LFXO_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LFXO_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_HFCORE_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_HFCORE_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_HFPER_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_HFPER_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LFA_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LFA_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LFB_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LFB_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_WDOG_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_WDOG_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LESENSE_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LESENSE_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_RTC_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_RTC_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LETIMER0_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LETIMER0_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LELCD_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LELCD_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LEUART0_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LEUART0_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (EFM32_LEUART1_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_efm32, EFM32_LEUART1_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);

	for(c=0;c<0x1ffff;c++){
		c++;
		c--;
		c++;
		c--;
	}

	DIAG_LogMsg(0, "**********************************************************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "*************** CC_GetClockSourceFreq() ******************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "**********************************************************");

	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_HFRCO_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_HFRCO_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_LFRCO_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_LFRCO_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_HFXO_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_HFXO_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_LFXO_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_LFXO_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_RC_CLOCK_SOURCE): ");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_RC_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_XTAL_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_XTAL_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_EXTERNAL_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_EXTERNAL_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_XTAL32_CLOCK_SOURCE): ");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_XTAL32_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_EXTERNAL32_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_EXTERNAL32_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_HF_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_HF_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_HFCORE_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_HFCORE_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_LFA_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_LFA_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_LFB_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_LFB_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (EFM32_ULFRC0_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_efm32, EFM32_ULFRC0_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	for(c=0;c<0x1ffff;c++){
		c++;
		c--;
		c++;
		c--;
	}

	DIAG0_LogNL(0);

	DIAG_LogMsg(0, "**********************************************************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "****************** CC_GetClockFreq() *********************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "**********************************************************");

	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_HF_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_HF_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_HFRCO_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_HFRCO_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_HFXO_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_HFXO_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LFXO_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LFXO_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_HFCORE_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_HFCORE_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_HFPER_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_HFPER_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LFA_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LFA_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LFB_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LFB_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_WDOG_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_WDOG_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LESENSE_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LESENSE_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_RTC_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_RTC_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LETIMER0_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LETIMER0_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LELCD_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LELCD_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LEUART0_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LEUART0_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (EFM32_LEUART1_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_efm32, EFM32_LEUART1_CLOCK), 10);
	DIAG0_LogNL(0);

	CC_ClockOnPin(EFM32_LFRCO_CLOCK, 1, 2);

	while(1){
		asm volatile ("nop");
	}

	// deinitialize IODevice
	IODEV_Deinit(IO_DEV);

	// deinitialize HAL core
	CORE_Deinit();
	
	return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses IO module.

*/
