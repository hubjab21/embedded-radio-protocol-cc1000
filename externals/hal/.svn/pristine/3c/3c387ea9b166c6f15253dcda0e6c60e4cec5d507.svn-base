/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's CLK module example
 Compiler:      %COMPILER%
 Hardware:      independent
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

int main(void){

	volatile unsigned int c = 0;

	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();

	// initialize clock controller
	CC_Init(cc_stm32);

	// setup LSE clock
	CC_SetClockSource(cc_stm32, STM32_LSE_CLOCK, STM32_XTAL32_CLOCK_SOURCE, STM32_XTAL32_FREQ);
	// setup HSE clock
	CC_SetClockSource(cc_stm32, STM32_HSE_CLOCK, STM32_XTAL_CLOCK_SOURCE, STM32_XTAL_FREQ);
	// setup PLL
	CC_SetClockSource(cc_stm32, STM32_PLL_CLOCK, STM32_HSE_CLOCK_SOURCE, 84000000);
	// setup SYSCLK (At the end)
	CC_SetClockSource(cc_stm32, STM32_SYSCLK_CLOCK, STM32_PLL_CLOCK_SOURCE, 84000000);
	// setup HCLK
	CC_SetClockSource(cc_stm32, STM32_HCLK_CLOCK, STM32_SYSCLK_CLOCK_SOURCE, 84000000);
	// setup PCLK1 max 42MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK1_CLOCK, STM32_HCLK_CLOCK_SOURCE, 42000000);
	// setup PCLK2 max 84MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK2_CLOCK, STM32_HCLK_CLOCK_SOURCE, 84000000);
	// setup RTC clock
	CC_SetClockSource(cc_stm32, STM32_RTC_CLOCK, STM32_HSE_CLOCK_SOURCE, STM32_XTAL32_FREQ);

	HAL_GPIO_Init();

    IODEV_Init(IO_DEV);
    IODEV_EnableWrite(IO_DEV);
    IODEV_EnableRead(IO_DEV);

	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV);
    DIAG_ActivateChannel(0);

	DIAG0_LogMsg(0,"Test zegara na STM32F4 - START");
	DIAG0_LogNL(0);

	const char clock_sources_name[13][30] = {
			"STM32_RC_CLOCK_SOURCE",
			"STM32_RC32_CLOCK_SOURCE",
			"STM32_XTAL_CLOCK_SOURCE",
			"STM32_EXTERNAL_CLOCK_SOURCE",
			"STM32_XTAL32_CLOCK_SOURCE",
			"STM32_EXTERNAL32_CLOCK_SOURCE",
			"STM32_HCLK_CLOCK_SOURCE",
			"STM32_SYSCLK_CLOCK_SOURCE",
			"STM32_HSE_CLOCK_SOURCE",
			"STM32_HSI_CLOCK_SOURCE",
			"STM32_LSE_CLOCK_SOURCE",
			"STM32_LSI_CLOCK_SOURCE",
			"STM32_PLL_CLOCK_SOURCE"
		};

	DIAG0_LogNL(0);

	DIAG_LogMsg(0, "**********************************************************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "****************** CC_GetClockSource() *******************");
	DIAG0_LogNL(0);
	DIAG_LogMsg(0, "**********************************************************");

	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_SYSCLK_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_SYSCLK_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_HSE_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_HSE_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_HSI_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_HSI_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_LSE_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_LSE_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_LSI_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_LSI_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_PLL_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_PLL_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_HCLK_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_HCLK_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_PCLK1_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_PCLK1_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_PCLK2_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_PCLK2_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_RTC_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_RTC_CLOCK)]);
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

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_RC_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_RC_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_RC32_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_RC32_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_XTAL_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_XTAL_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_EXT_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_EXTERNAL_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_XTAL32_CLOCK_SOURCE): ");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_XTAL32_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_EXT32_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_EXTERNAL32_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_HCLK_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_HCLK_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_SYSCLK_CLOCK_SOURCE): ");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_SYSCLK_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_HSE_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_HSE_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_HSI_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_HSI_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_LSE_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_LSE_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_LSI_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_LSI_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_PLL_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_PLL_CLOCK_SOURCE), 10);
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

	DIAG0_LogMsg(0,"GetClockFreq (STM32_SYSCLK_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_SYSCLK_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_HSE_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HSE_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_HSI_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HSI_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_LSE_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_LSE_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_LSI_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_LSI_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_PLL_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_PLL_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_HCLK_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HCLK_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_PCLK1_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_PCLK1_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_PCLK2_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_PCLK2_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_RTC_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_RTC_CLOCK), 10);
	DIAG0_LogNL(0);

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
