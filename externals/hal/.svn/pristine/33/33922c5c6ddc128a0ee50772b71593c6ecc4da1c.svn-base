/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Michał Kochanowski
 Purpose:       HALFRED's CLK port test
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
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

void reInitUsart(IODevice iodevice){
	IODEV_Deinit(iodevice);
	IODEV_Init(iodevice);
	IODEV_EnableRead(iodevice);
	IODEV_EnableWrite(iodevice);
}

typedef struct {
	uint8_t source_main_clock;
	uint8_t source_slow_clock;
	uint8_t source_master_clock;
	uint32_t source_frequency_slow_clock;
	uint32_t source_frequency_main_clock;
	uint32_t frequency_slow_clock;
	uint32_t frequency_main_clock;
	uint32_t frequency_master_clock;

} T_clocks;
// result of tests
uint8_t test_result=0;
void CheckClock(T_clocks *clock)
{

	DIAG0_LogMsg(0, "\tSetClockSource:  	OK!");
	DIAG0_LogNL(0);
	test_result++;
	// GetClockSource test
	if(CC_GetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK)==(clock->source_main_clock) &&
	CC_GetClockSource(cc_sam3s, SAM3S_SLOW_CLOCK)==(clock->source_slow_clock) &&
	CC_GetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK)==(clock->source_master_clock))
	{
		DIAG0_LogMsg(0, "\tGetClockSource:  	OK!");
		DIAG0_LogNL(0);
		test_result++;
	}else{
		DIAG0_LogMsg(0, "\tGetClockSource:  	FAILED!");
		DIAG0_LogNL(0);
	}

	// GetClockSourceFreq test
	if(CC_GetClockSourceFreq(cc_sam3s, SAM3S_SLOW_CLOCK_SOURCE)==(clock->source_frequency_slow_clock)&&
	CC_GetClockSourceFreq(cc_sam3s, SAM3S_MAIN_CLOCK_SOURCE)==(clock->source_frequency_main_clock))
	{
		DIAG0_LogMsg(0, "\tGetClockSourceFreq:  	OK!");
		DIAG0_LogNL(0);
		test_result++;
	}else{
		DIAG0_LogMsg(0, "\tGetClockSourceFreq:  	FAILED!");
		DIAG0_LogNL(0);
	}

	// GetClockFreq test
	if(CC_GetClockFreq(cc_sam3s, SAM3S_MAIN_CLOCK)==(clock->frequency_main_clock)&&
	CC_GetClockFreq(cc_sam3s, SAM3S_SLOW_CLOCK)==(clock->frequency_slow_clock)&&
	CC_GetClockFreq(cc_sam3s, SAM3S_MASTER_CLOCK)==(clock->frequency_master_clock))
	{
		DIAG0_LogMsg(0, "\tGetClockFreq:  		OK!");
		DIAG0_LogNL(0);
		test_result++;
	}else{
		DIAG0_LogMsg(0, "\tGetClockFreq:  		FAILED!");
		DIAG0_LogNL(0);
	}

}

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void){


    // initialize HAL core
    CORE_Init();
	// initialize clock controller
	CC_Init(cc_sam3s);

	//helper variables
	//to get char from usart
	uint8_t key;
	//to reduce the size of the code
	T_clocks clocks;

	// Set clocks on pins
	// Master clock on pin
	SAM3S_Clock_On_Pin(CLK_ON_PIN_MCK);
	// Main clock on pin
	SAM3S_Clock_On_Pin(CLK_ON_PIN_MAIN);
	// Slow clock on pin
	SAM3S_Clock_On_Pin(CLK_ON_PIN_SLOW);

	// Setup main clock
	CC_SetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK, SAM3S_RC_CLOCK_SOURCE, 7000000);
	// Setup master clock
	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_MAIN_CLOCK_SOURCE, 3500000);

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
	DIAG0_LogMsg(0, "///////Testing embedded RC oscillator/////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////internal 32.768Hz slow clock////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "////////////and algorithms finding //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////the closest possible frequency///////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"///// Embedded RC Oscillator try to set to 7Mhz////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"//////////// and master clock to 3.5 Mhz////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to CLK_ON_PIN_MCK");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "CLK_ON_PIN_MAIN and CLK_ON_PIN_SLOW and measure frequency. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get: 4Mhz 8Mhz and ~32khz ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);


	// Wait for char from usart
	while(!IODEV_GetReadCount(IO_DIAG))
	{
		;
	}
	// Get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	//write correct data
	clocks.frequency_main_clock= 8000000;
	clocks.frequency_master_clock= 4000000;
	clocks.frequency_slow_clock=32000;
	clocks.source_frequency_main_clock=8000000;
	clocks.source_frequency_slow_clock=32000;
	clocks.source_main_clock=0;
	clocks.source_master_clock=4;
	clocks.source_slow_clock=0;
	//check data
	CheckClock(&clocks);


	//setup clocks
	CC_SetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK, SAM3S_XTAL_CLOCK_SOURCE, SAM3S_XTAL_FREQ);
	CC_SetClockSource(cc_sam3s, SAM3S_SLOW_CLOCK, SAM3S_XTAL_CLOCK_SOURCE, 32768);
	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_MAIN_CLOCK_SOURCE, 8000000);
	//reinit usart
	reInitUsart(IO_DIAG);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 2 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////Testing External 12Mhz oscillator/////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////external 32.768Hz slow clock/////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "////////////and algorithms finding //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////the closest possible frequency///////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"////// Main external Oscillator  set to 12Mhz//////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"////// and master clock try to set to 8 Mhz////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to CLK_ON_PIN_MCK");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "CLK_ON_PIN_MAIN and CLK_ON_PIN_SLOW and measure frequency. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get: 6Mhz 12Mhz and 32768khz ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Wait for char from usart
	while(!IODEV_GetReadCount(IO_DIAG))
	{
		;
	}
	// Get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	//write correct data
	clocks.frequency_main_clock= 12000000;
	clocks.frequency_master_clock= 6000000;
	clocks.frequency_slow_clock=32768;
	clocks.source_frequency_main_clock=12000000;
	clocks.source_frequency_slow_clock=32768;
	clocks.source_main_clock=1;
	clocks.source_master_clock=4;
	clocks.source_slow_clock=1;
	//check data
	CheckClock(&clocks);

	//setup clocks
	CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_PLLA_CLOCK_SOURCE,47500000);
	//reinit usart
	reInitUsart(IO_DIAG);


	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 3 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "////////Testing PLLA and algorithms finding ///////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////the closest possible frequency/////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0,"/////////Try to set master clock  to  47.5 Mhz////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to CLK_ON_PIN_MCK");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "CLK_ON_PIN_MAIN and CLK_ON_PIN_SLOW and measure frequency. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "You should get: 12Mhz 48Mhz and 32768khz ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Wait for char from usart
	while(!IODEV_GetReadCount(IO_DIAG))
	{
		;
	}
	// Get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	//write correct data
	clocks.frequency_main_clock= 12000000;
	clocks.frequency_master_clock= 48000000;
	clocks.frequency_slow_clock=32768;
	clocks.source_frequency_main_clock=12000000;
	clocks.source_frequency_slow_clock=32768;
	clocks.source_main_clock=1;
	clocks.source_master_clock=5;
	clocks.source_slow_clock=1;
	//check data
	CheckClock(&clocks);

		//setup clocks
		CC_SetClockSource(cc_sam3s, SAM3S_MASTER_CLOCK, SAM3S_PLLB_CLOCK_SOURCE,64000000);

		//reinit usart
		reInitUsart(IO_DIAG);

		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "//////////////////// TEST 4 ///////////////////////");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "////////Testing PLLB and algorithms finding ///////////");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "///////////the closest possible frequency/////////////");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0,"/////////Try to set master clock  to  64 Mhz////////");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to CLK_ON_PIN_MCK");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "CLK_ON_PIN_MAIN and CLK_ON_PIN_SLOW and measure frequency. ");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "You should get: 12Mhz 64Mhz and 32768khz ");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);

		// Wait for char from usart
		while(!IODEV_GetReadCount(IO_DIAG))
		{
			;
		}
		// Get char from usart
		while(IODEV_GetReadCount(IO_DIAG)){
			IODEV_Read(IO_DIAG, &key, 1, 0);
		}

		//write correct data
		clocks.frequency_main_clock= 12000000;
		clocks.frequency_master_clock= 64000000;
		clocks.frequency_slow_clock=32768;
		clocks.source_frequency_main_clock=12000000;
		clocks.source_frequency_slow_clock=32768;
		clocks.source_main_clock=1;
		clocks.source_master_clock=6;
		clocks.source_slow_clock=1;
		//check data
		CheckClock(&clocks);

		// number of tests
		uint8_t number_of_tests =16;

		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "/////////// HALFRED - CLK port test DONE!/////////");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "///////////////////////SUMMARY/////////////////////");
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, " TEST PASSED ");
		DIAG0_LogUINT(0,test_result,10);
		DIAG0_LogMsg(0," of ");
		DIAG0_LogUINT(0,number_of_tests,10);
		DIAG0_LogNL(0);
		DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
	while(1)
	{
		;
	}

	// deinitialize DIAG module
	DIAG_Deinit();

	// deinitialize IODevices
	IODEV_Deinit(IO_DIAG);

	CC_Deinit(cc_sam3s);
    CORE_Deinit();

    return 0;

} /* main */

