/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda, Michał Kochanowski
 Purpose:       HALFRED's HALFRED port test
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test of IO capabilities
--------------------------------------------------------------------------------
 Comments:		Test require three instance of IO device (one for debugging)
 	 	 	 	Your task: CONNTECT TWO INSTANCE OF IO DEVICES
 	 	 	 	(IO_DEV1 as master with IO_DEV2 as slave, )
 	 	 	 	ATTENTION: Don't forget about CS pin:)
================================================================================
*/

// include the one and only HAL header
#include "hal.h"
// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{
	// test result
	uint8_t test_result=0;

	// key
	uint8_t key;

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

	// Number of tests
	uint8_t number_of_tests=16;

	// Configure master's chip select (must be conncted to slave's NSS!)
	HAL_GPIO_ConfigurePin(CS_PIN, DEFAULT_CONFIG);
	HAL_GPIO_SetPinLow(CS_PIN);

	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////// HALFRED - IO port test //////////");
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
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// initialize IODevices used by the DEV1 module
	IODEV_Init(IO_DEV1);
	IODEV_EnableWrite(IO_DEV1);
	IODEV_EnableRead(IO_DEV1);

	DIAG0_LogMsg(0, "\tIO_DEV1 Initialize:			OK!");
	DIAG0_LogNL(0);
	test_result++;

	// initialize IODevices used by the DEV2 module
	IODEV_Init(IO_DEV2);
	IODEV_EnableWrite(IO_DEV2);
	IODEV_EnableRead(IO_DEV2);

	DIAG0_LogMsg(0, "\tIO_DEV2 Initialize:			OK!");
	DIAG0_LogNL(0);
	test_result++;

	if(!IODEV_GetWriteSpace(IO_DEV1) || !IODEV_GetWriteSpace(IO_DEV2)){
		DIAG0_LogMsg(0, "\tIODEV_GetWriteSpace:			FAILED!");
		DIAG0_LogNL(0);
	}else{
		DIAG0_LogMsg(0, "\tIODEV_GetWriteSpace:			OK!");
		DIAG0_LogNL(0);
		test_result++;
	}

	if(IODEV_Write(IO_DEV1, "a", 1, 0))
	{
		DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Sending message:	OK!");
		DIAG0_LogNL(0);
		test_result++;
	}else{
		DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Sending message:	FAILED!");
		DIAG0_LogNL(0);
	}

	DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Waiting for message: ");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	if (IODEV_Read(IO_DEV2, &key, 1, 0)) {

		DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Got message:		OK!");
		DIAG0_LogNL(0);

		if (key == 'a') {
			DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Got right message:	OK!");
			DIAG0_LogNL(0);
			test_result++;
		}else{
			DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Got right message:	FAILED!");
			DIAG0_LogUINT(0, key, 10);
			DIAG0_LogNL(0);
		}
	}else{
		DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Got message:		FAILED!");
		DIAG0_LogNL(0);
	}

	HAL_GPIO_SetPinHigh(CS_PIN);

	// initialize IODevices used by the DEV2 module
	IODEV_DisableWrite(IO_DEV2);
    IODEV_DisableRead(IO_DEV2);
	IODEV_Deinit(IO_DEV2);

	DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Deinitialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;

	// initialize IODevices used by the DEV1 module
	IODEV_DisableWrite(IO_DEV1);
	IODEV_DisableRead(IO_DEV1);
	IODEV_Deinit(IO_DEV1);

	DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Deinitialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;
	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 2 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// initialize IODevices used by the DEV1 module
	IODEV_Init(IO_DEV1);
	IODEV_EnableWrite(IO_DEV1);
	IODEV_EnableRead(IO_DEV1);

	DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Initialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;

	// initialize IODevices used by the DEV2 module
	IODEV_Init(IO_DEV2);
	IODEV_EnableWrite(IO_DEV2);
	IODEV_EnableRead(IO_DEV2);

	DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Initialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;

	HAL_GPIO_SetPinLow(CS_PIN);

	if(!IODEV_GetWriteSpace(IO_DEV1) || !IODEV_GetWriteSpace(IO_DEV2)){
		DIAG0_LogMsg(0, "\tIODEV_GetWriteSpace : FAILED!");
		DIAG0_LogNL(0);
	}

	if(IODEV_Write(IO_DEV2, "b", 1, 0))
	{
		DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Sending message:	OK!");
		DIAG0_LogNL(0);
		test_result++;
	}else{
		DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Sending message:	FAILED!");
		DIAG0_LogNL(0);
	}

	DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Waiting for message: ");
	DIAG0_LogNL(0);
	test_result++;

	if (IODEV_Read(IO_DEV1, &key, 1, 0)) {

		DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Got message:		OK!");
		DIAG0_LogNL(0);
		test_result++;

		if (key == 'b') {
			DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Got right message:	OK!");
			DIAG0_LogNL(0);
			test_result++;
		}else{
			DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Got right message:		FAILED!");
			DIAG0_LogNL(0);
		}
	}else{
		DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Got message:		FAILED!");
		DIAG0_LogNL(0);
	}

	// initialize IODevices used by the DEV2 module
	IODEV_DisableWrite(IO_DEV2);
	IODEV_DisableRead(IO_DEV2);
	IODEV_Deinit(IO_DEV2);

	DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) Deinitialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;

	// initialize IODevices used by the DEV1 module
	IODEV_DisableWrite(IO_DEV1);
	IODEV_DisableRead(IO_DEV1);
	IODEV_Deinit(IO_DEV1);
	DIAG0_LogMsg(0, "\tIO_DEV1 (Master) Deinitialize:		OK!");
	DIAG0_LogNL(0);
	test_result++;

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 3 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// turn off slave
	HAL_GPIO_SetPinHigh(CS_PIN);

	// initialize IODevices used by the DEV1 module
	IODEV_Init(IO_DEV1);
	IODEV_EnableWrite(IO_DEV1);
	IODEV_EnableRead(IO_DEV1);

	// initialize IODevices used by the DEV2 module
	IODEV_Init(IO_DEV2);
	IODEV_EnableWrite(IO_DEV2);
	IODEV_EnableRead(IO_DEV2);


	IODEV_Write(IO_DEV2, "f", 1, 0);
	if (IODEV_Read(IO_DEV1, &key, 1, 0)) {
		if (key != 'f') {
			DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) CS PIN works:		OK!");
			DIAG0_LogNL(0);
			test_result++;
		}else{
			DIAG0_LogMsg(0, "\tIO_DEV2 (Slave) CS PIN works:		FAILED!");
			DIAG0_LogNL(0);

		}
	}
	// initialize IODevices used by the DEV2 module
	IODEV_DisableWrite(IO_DEV2);
    IODEV_DisableRead(IO_DEV2);
	IODEV_Deinit(IO_DEV2);

	// initialize IODevices used by the DEV1 module
	IODEV_DisableWrite(IO_DEV1);
	IODEV_DisableRead(IO_DEV1);
	IODEV_Deinit(IO_DEV1);

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////// HALFRED - IO port test DONE!/////////");
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

	// deinitialize HAL
	IODEV_Deinit(IO_DIAG);
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
