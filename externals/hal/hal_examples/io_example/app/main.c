/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's IO module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses IO module
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
	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();
	HAL_GPIO_Init();
	// initialize IODevice

	IODEV_Init(IO_DEV);

	IODEV_EnableWrite(IO_DEV);
	IODEV_EnableRead(IO_DEV);
	IODEV_Write(IO_DEV, "Hello", 5, 0);

	uint8_t key;
	for(;;) {
		if (IODEV_Read(IO_DEV, &key, 1, 0)) {
			if (key == 'r') {
				IODEV_Write(IO_DEV, "OK", 2, 0);
			}
		}
	}
	// deinitialize IODevice
	IODEV_Deinit(IO_DEV);
	HAL_GPIO_Deinit();
	// deinitialize HAL core
	CORE_Deinit();
	
	return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses IO module.

*/
