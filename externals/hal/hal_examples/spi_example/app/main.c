/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's HALFRED SPI Demo
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       demo of SPI
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

	// Configure master's chip select (must be conncted to slave's NSS!)
	HAL_GPIO_ConfigurePin(CS_PIN, DEFAULT_CONFIG);
	HAL_GPIO_SetPinLow(CS_PIN);

	// initialize IODevices used by the DEV1 module
	IODEV_Init(IO_DEV1);
	IODEV_EnableWrite(IO_DEV1);
	IODEV_EnableRead(IO_DEV1);

	// initialize IODevices used by the DEV2 module
	IODEV_Init(IO_DEV2);
	IODEV_EnableWrite(IO_DEV2);
	IODEV_EnableRead(IO_DEV2);

	HAL_GPIO_SetPinLow(CS_PIN);

	IODEV_Write(IO_DEV1, "t", 1, 0);

	uint8_t read;
	IODEV_Read(IO_DEV2, &read, 1, 0);

	if(read == 't'){
		DIAG0_LogMsg(0, "SPI Works!");
		DIAG0_LogNL(0);
	}else{
		DIAG0_LogMsg(0, "SPI Failed!");
		DIAG0_LogNL(0);
	}

	HAL_GPIO_SetPinHigh(CS_PIN);

	IODEV_DisableWrite(IO_DEV2);
    IODEV_DisableRead(IO_DEV2);
	IODEV_Deinit(IO_DEV2);

	IODEV_DisableWrite(IO_DEV1);
	IODEV_DisableRead(IO_DEV1);
	IODEV_Deinit(IO_DEV1);

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
