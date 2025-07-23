/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda, Michał Kochanowski
 Purpose:       HALFRED's DELAY port test
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test of DELAY capabilities
--------------------------------------------------------------------------------
 Comments: 		-To run this test you need oscilloscope
 	 	 	 	-To have more accurate delays you should use high frequency PLL
  	  	  	    as master clock and write its value in hal_config.h - HAL_F_CPU
================================================================================
*/

// include the one and only HAL header
#include "hal.h"

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
	// initialize HAL core
	CORE_Init();

	// initialize GPIO module
	HAL_GPIO_Init();

	// initialize IODevices used by the DIAG module
	IODEV_Init(IO_DIAG);
	IODEV_EnableWrite(IO_DIAG);
	IODEV_EnableRead(IO_DIAG);

	// initialize DIAG module
	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DIAG);
	DIAG_ActivateChannel(0);

	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////// HALFRED - DELAY port test //////////");
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
	DIAG0_LogMsg(0, "/////////////// Testing 1 ms delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);


	//helper variable to get char from usart
	uint8_t key;

	// configure test pin
	HAL_GPIO_SetPinHigh(TEST_PIN);
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_MS(1);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_MS(1);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogMsg(0, "/////////////// Testing 10 ms delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_MS(10);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_MS(10);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
	IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogMsg(0, "/////////////// Testing 100 ms delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_MS(100);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_MS(100);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
	IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogMsg(0, "/////////////// Testing 1 us delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_US(1);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_US(1);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogMsg(0, "/////////////// Testing 10 us delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////// To go to next test push any button ////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_US(10);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_US(10);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogMsg(0, "/////////////// Testing 100 us delay //////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: Connect your oscilloscope probe to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "and measure negative pulse width. ");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "////////// To end test push any button /////////// ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	//wait for measurement
	while(!IODEV_GetReadCount(IO_DIAG)) {
		HAL_GPIO_SetPinLow(TEST_PIN);
		HAL_PORT_DELAY_US(100);
		HAL_GPIO_SetPinHigh(TEST_PIN);
		HAL_PORT_DELAY_US(100);
	}

	//get char from usart
	while(IODEV_GetReadCount(IO_DIAG)){
		IODEV_Read(IO_DIAG, &key, 1, 0);
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////// HALFRED - DELAY port test DONE!////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);


	while(1)
	{
		;
	}
	// deinitialize HAL
	IODEV_Deinit(IO_DIAG);
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
