/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Krzak, MIchal Kochanowski
 Purpose:       HALFRED's GPIO module example
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses GPIO module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


// Include the one and only HAL header
#include "hal.h"


// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------

// Handler of gpio - TEST_PIN
void MyHandler(void)
{
	HAL_GPIO_TogglePin(TEST1_PIN);
}

 int main(void)
{
	volatile int i;
	uint8_t k=0;

	// initialize HAL core
	CORE_Init();

	// initialize GPIO module
	HAL_GPIO_Init();

	// Configure test ports
	HAL_GPIO_SetPinHigh(TEST_PIN);
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);
	HAL_GPIO_SetPinHigh(TEST1_PIN);
	HAL_GPIO_ConfigurePin(TEST1_PIN, DEFAULT_CONFIG);

	//Set event
	HAL_GPIO_SetEventHandler(TEST_PIN, MyHandler);
	HAL_GPIO_EnableEvent(TEST_PIN, TEST_PIN_TRIGGER);

	// do some GPIO stuff
    while (1) {
    	if(k==10){
    		//if event is turn on, turn off it
    		if(HAL_GPIO_IsEventEnabled(TEST_PIN)){
    			HAL_GPIO_DisableEvent(TEST_PIN);
    		}
    	}else if(k==16){
    		// turn on event
    		HAL_GPIO_EnableEvent(TEST_PIN, TEST_PIN_TRIGGER);
    	}
    	HAL_GPIO_TogglePin(TEST_PIN);


    	// delay
    	for (i=0; i < 100000;i++) {
    		i++;
    		i--;
    	}k++;
    }

	// deinitialize HAL
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
