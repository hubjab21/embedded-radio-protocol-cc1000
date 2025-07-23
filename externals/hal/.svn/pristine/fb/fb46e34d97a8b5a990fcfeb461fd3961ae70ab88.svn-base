/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda, Michał Kochanowski
 Purpose:       HALFRED's GPIO port test
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       test of GPIO capabilities
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/


// include the one and only HAL header
#include "hal.h"

static int handler;
uint8_t number_of_tests=0;
uint8_t test_result=0;
// -----------------------------------------------------------------------------
//  delay function
// -----------------------------------------------------------------------------
void delay_ticks(uint32_t ticks)
{
	uint32_t temp;
	for(temp = 0; temp < ticks; temp++)
	{
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
	}
}

// -----------------------------------------------------------------------------
//  event handlers
// -----------------------------------------------------------------------------
void MyHandler(void)
 {
	handler = 1;

	HAL_GPIO_DisableEvent(INPUT_PIN);
 }

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
	DIAG0_LogMsg(0, "///////////// HALFRED - GPIO port test ////////////");
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
	DIAG0_LogMsg(0, "Your task: Connect your INPUT_PIN to TEST_PIN");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// configure input pin
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_UP);

	// configure test pin
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);

	HAL_GPIO_SetPinLow(TEST_PIN);

	// dummy wait for low pin state
	while(HAL_GPIO_ReadPin(INPUT_PIN))
	{
		asm volatile ("nop");
	}

	DIAG0_LogMsg(0, "\tHAL_GPIO_ReadPin:					OK!");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	test_result++;
	number_of_tests++;

	DIAG0_LogMsg(0, "//////////////////// TEST 2 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// Set pin low
	HAL_GPIO_SetPinLow(TEST_PIN);

	delay_ticks(0xfff);

		number_of_tests++;
	if(HAL_GPIO_ReadPin(INPUT_PIN))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPinLow:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPinLow:					OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	// Set pin high
	HAL_GPIO_SetPinHigh(TEST_PIN);

	delay_ticks(0xfff);

	number_of_tests++;
	if(!HAL_GPIO_ReadPin(INPUT_PIN))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPinHigh:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPinHigh:					OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	// Set pin toggle
	HAL_GPIO_TogglePin(TEST_PIN);

	delay_ticks(0xfff);

	number_of_tests++;
	if(HAL_GPIO_ReadPin(INPUT_PIN))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_TogglePin:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_TogglePin:					OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	// Configure port
	HAL_GPIO_ConfigurePort(TEST_PORT, DEFAULT_CONFIG);

	// Set port low
	HAL_GPIO_SetPortLow(TEST_PORT, TEST_PORT_PORT_MASK);

	delay_ticks(0xfff);

	number_of_tests++;
	if(HAL_GPIO_ReadPort(TEST_PORT) & TEST_PORT_PORT_MASK)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPortLow:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPortLow:					OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	// Set port low
	HAL_GPIO_SetPortHigh(TEST_PORT, TEST_PORT_PORT_MASK);

	delay_ticks(0xfff);

	number_of_tests++;
	if(!(HAL_GPIO_ReadPort(TEST_PORT) & TEST_PORT_PORT_MASK))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPortHigh:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_SetPortHigh:					OK!");
		test_result++;
	}
	DIAG0_LogNL(0);


	// Set port low
	HAL_GPIO_WritePort(TEST_PORT, TEST_PORT_PORT_MASK);

	delay_ticks(0xfff);

	number_of_tests++;
	if(!(HAL_GPIO_ReadPort(TEST_PORT) & TEST_PORT_PORT_MASK))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_WritePort:					failed!");
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_WritePort:					OK!");
		test_result++;
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "//////////////////// TEST 3 ///////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Your task: None");
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

	// set pin low
	HAL_GPIO_SetPinLow(TEST_PIN);

	// set event handler
	HAL_GPIO_SetEventHandler(INPUT_PIN, MyHandler);

#if defined INPUT_PIN_EXT_TRIGGER_RISING
	number_of_tests++;
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_DOWN);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_RISING);
	delay_ticks(0xfff);

	HAL_GPIO_SetPinHigh(TEST_PIN);

	delay_ticks(0xfff);

	if(!handler)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_RISING:		failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_RISING:		OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	handler = 0;

#endif

#if defined INPUT_PIN_EXT_TRIGGER_FALLING
	number_of_tests++;
	HAL_GPIO_SetPinHigh(TEST_PIN);
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_UP);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_FALLING);
	delay_ticks(0xfff);

	HAL_GPIO_SetPinLow(TEST_PIN);

	delay_ticks(0xfff);

	if(!handler)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_FALLING:		failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_FALLING:		OK!");
		test_result++;
	}

	DIAG0_LogNL(0);

	handler = 0;
#endif


#if defined INPUT_PIN_EXT_TRIGGER_BOTH
	number_of_tests++;
	HAL_GPIO_SetPinHigh(TEST_PIN);
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_UP);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_BOTH);
	delay_ticks(0xfff);

	HAL_GPIO_SetPinLow(TEST_PIN);

	delay_ticks(0xfff);

	if(!handler)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_BOTH:		failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_EDGE_BOTH:		OK!");
		test_result++;
	}

	handler = 0;

	DIAG0_LogNL(0);

#endif


#if defined INPUT_PIN_EXT_TRIGGER_LEVEL_LOW
	number_of_tests++;
	HAL_GPIO_SetPinHigh(TEST_PIN);
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_UP);
	delay_ticks(0xfff);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_LEVEL_LOW);
	delay_ticks(0xfff);
	HAL_GPIO_SetPinLow(TEST_PIN);
	delay_ticks(0xfff);

	if(!handler)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_LEVEL_LOW:		failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_LEVEL_LOW:		OK!");
		test_result++;
	}

	handler = 0;

	DIAG0_LogNL(0);

#endif

#if defined INPUT_PIN_EXT_TRIGGER_LEVEL_HIGH
	number_of_tests++;
	HAL_GPIO_SetPinLow(TEST_PIN);
	HAL_GPIO_ConfigurePin(INPUT_PIN, DEFAULT_CONFIG_PULL_DOWN);
	delay_ticks(0xfff);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_LEVEL_HIGH);

	delay_ticks(0xfff);

	HAL_GPIO_TogglePin(TEST_PIN);

	delay_ticks(0xfff);

	if(!handler)
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_LEVEL_HIGH:		failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_Event in GPIO_TRIGGER_LEVEL_HIGH:		OK!");
		test_result++;
	}

	handler = 0;

	DIAG0_LogNL(0);

#endif

#if defined INPUT_PIN_EXT_TRIGGER_RISING
	number_of_tests++;
	HAL_GPIO_SetPinLow(TEST_PIN);
	HAL_GPIO_EnableEvent(INPUT_PIN, INPUT_PIN_EXT_TRIGGER_RISING);
	delay_ticks(0xfff);

	if(!HAL_GPIO_IsEventEnabled(INPUT_PIN))
	{
		DIAG0_LogMsg(0, "\tHAL_GPIO_IsEventEnabled:				failed!");
		HAL_GPIO_DisableEvent(INPUT_PIN);
	}else{
		DIAG0_LogMsg(0, "\tHAL_GPIO_IsEventEnabled:				OK!");
		test_result++;
	}
#endif

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "///////////////////////////////////////////////////");
	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "/////////// HALFRED - GPIO port test DONE!/////////");
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
		asm volatile ("nop");
	}

	// deinitialize HAL
	HAL_GPIO_Deinit();
	CORE_Deinit();

	return 0;

} /* main */
