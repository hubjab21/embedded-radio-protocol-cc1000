/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Krzak
 Purpose:       HALFRED's DIAG module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses DIAG module
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
	// initialize IODevices used by the DIAG module
	IODEV_Init(IO_DEV1);
	IODEV_EnableWrite(IO_DEV1);
	IODEV_EnableRead(IO_DEV1);

	IODEV_Init(IO_DEV2);
	IODEV_EnableWrite(IO_DEV2);
	IODEV_EnableRead(IO_DEV2);

	// initialize DIAG module
	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV1);
	DIAG_SetOutputDevice(1, IO_DEV2);
	DIAG_ActivateChannel(0);
	DIAG_ActivateChannel(1);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Level 0 diagnostic message on channel 0");
	DIAG0_LogNL(0);
	DIAG1_LogMsg(0, "Level 1 diagnostic message on channel 0");
	DIAG1_LogNL(0);
	DIAG2_LogMsg(0, "Level 2 diagnostic message on channel 0");
	DIAG2_LogNL(0);
	DIAG0_LogMsg(1, "Level 0 diagnostic message on channel 1");
	DIAG0_LogNL(1);
	DIAG1_LogMsg(1, "Level 1 diagnostic message on channel 1");
	DIAG1_LogNL(1);
	DIAG2_LogMsg(1, "Level 2 diagnostic message on channel 1");
	DIAG2_LogNL(1);


	// deinitialize DIAG module
	DIAG_Deinit();
	HAL_GPIO_Deinit();
	// deinitialize IODevices
	IODEV_Deinit(IO_DEV1);
	IODEV_Deinit(IO_DEV2);

	// deinitialize HAL core
	CORE_Deinit();
	
	return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses IO module.

*/
