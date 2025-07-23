/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's CLK port test
 Compiler:      %COMPILER%
 Hardware:      STM32F0
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test of CLK capabilities
--------------------------------------------------------------------------------
 Comments: 		-To run this test you need oscilloscope
 	 	 	 	-Before run this test you should turn off
 	 	 	 	and next turn on your power supply
 	 	 	 	-At internal embedded oscillators you can
 	 	 	 	measure a bit different frequency then reference
================================================================================
*/

// HAL files
#include "hal.h"

#define PLL_FREQUENCY 24000000
#define SYSCLK_FREQUENCY 24000000

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void){


    // initialize HAL core
    CORE_Init();
	// initialize clock controller
	CC_Init(cc_stm32);

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
	CC_SetClockSource(cc_stm32, STM32_PLL_CLOCK, STM32_HSE_CLOCK_SOURCE, 24000000);
	// setup SYSCLK (At the end)
	CC_SetClockSource(cc_stm32, STM32_SYSCLK_CLOCK, STM32_PLL_CLOCK_SOURCE, 24000000);
	// setup HCLK
	CC_SetClockSource(cc_stm32, STM32_HCLK_CLOCK, STM32_SYSCLK_CLOCK_SOURCE, 24000000);
	// setup PCLK1 max 42MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK_CLOCK, STM32_HCLK_CLOCK_SOURCE, 12000000);
	// setup RTC clock
	CC_SetClockSource(cc_stm32, STM32_RTC_CLOCK, STM32_HSE_CLOCK_SOURCE, 12000000);
	// setup USART1 clock (default PCLK)
	CC_SetClockSource(cc_stm32, STM32_USART1_CLOCK, STM32_SYSCLK_CLOCK_SOURCE, 12000000);
	// setup ADC clock
	CC_SetClockSource(cc_stm32, STM32_ADC_CLOCK, STM32_HSI14_CLOCK_SOURCE, 14000000);


	//helper variables
	//to get char from usart
	uint8_t key;

	// Initialize IODevices used by the DIAG module
	IODEV_Init(IO_DIAG);
	IODEV_EnableRead(IO_DIAG);
	IODEV_EnableWrite(IO_DIAG);

	// Initialize DIAG module
    DIAG_Init();
    DIAG_SetOutputDevice(0, IO_DIAG);
    DIAG_ActivateChannel(0);

    DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "////////////// HALFRED - CLK port test ///////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/// Read comments in main.c file before testing! //");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "//////////////////// TEST 1 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Check proper settings");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	const char clock_sources_name[15][30] = {
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
				"STM32_PLL_CLOCK_SOURCE",
				"STM32_PCLK_CLOCK_SOURCE",
				"STM32_HSI14_CLOCK_SOURCE"
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

	DIAG0_LogMsg(0,"GetClockSource (STM32_PCLK_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_PCLK_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_RTC_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_RTC_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_USART1_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_USART1_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSource (STM32_ADC_CLOCK): \t");
	DIAG0_LogMsg(0,clock_sources_name[CC_GetClockSource(cc_stm32, STM32_ADC_CLOCK)]);
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);

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

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_PCLK_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_PCLK_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockSourceFreq (STM32_HSI14_CLOCK_SOURCE): \t");
	DIAG0_LogUINT(0,CC_GetClockSourceFreq(cc_stm32, STM32_HSI14_CLOCK_SOURCE), 10);
	DIAG0_LogNL(0);

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

	DIAG0_LogMsg(0,"GetClockFreq (STM32_PCLK_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_PCLK_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_RTC_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_RTC_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_USART1_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_USART1_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"GetClockFreq (STM32_ADC_CLOCK): \t");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_ADC_CLOCK), 10);
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 2 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to PA8 pin");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to the test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_PLL_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get PLL/2 frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_PLL_CLOCK)/2, 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_HSI_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get HSI frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HSI_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_HSI14_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get HSI14 frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HSI14_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_HSE_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get HSE frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_HSE_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_SYSCLK_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get SYSCLK frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_SYSCLK_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_LSI_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get LSI frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_LSI_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);

	CC_ClockOnPin(STM32_LSE_CLOCK, MCO_PIN);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get LSE frequency now: ~");
	DIAG0_LogUINT(0,CC_GetClockFreq(cc_stm32, STM32_LSE_CLOCK), 10);
	DIAG0_LogMsg(0, " Hz");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to end push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Get char from usart
	while(!IODEV_GetReadCount(IO_DIAG)){
		;
	}

	// dummy read
	IODEV_Read(IO_DIAG, &key, 1, 0);


	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////// HALFRED - CLK port test DONE!/////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);

	while(1)
	{
		;
	}

	// deinitialize DIAG module
	DIAG_Deinit();

	// deinitialize IODevices
	IODEV_Deinit(IO_DIAG);

	CC_Deinit(cc_stm32);
    CORE_Deinit();

    return 0;

} /* main */

