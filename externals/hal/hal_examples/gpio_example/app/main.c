/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's GPIO module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses GPIO module
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
	volatile int i;

	// initialize HAL core
	CORE_Init();

	// initialize GPIO module
	HAL_GPIO_Init();

	// configure test port
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);

	// do some GPIO stuff
    while (1) {
    	HAL_GPIO_TogglePin(TEST_PIN);

    	// delay
    	for (i=0; i < 100000;i++) {
    		i++;
    		i--;
    	}
    }

	// deinitialize HAL
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
