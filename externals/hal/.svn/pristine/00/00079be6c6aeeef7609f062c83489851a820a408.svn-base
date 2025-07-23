/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's 1WIRE module example
 Compiler:      %COMPILER%
 Hardware:      independent
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses IOBus module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// include the one and only HAL header
#include "hal.h"
#include "hal_port_ds18s20.h"

// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------
int main(void)
{

// -----------------------------------------------------------------------------
//  Low Lewel HAL Init Section
// -----------------------------------------------------------------------------

	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();

	// initialize clock controller
	CC_Init(cc_stm32);

	// setup HSE clock
	CC_SetClockSource(cc_stm32, STM32_HSE_CLOCK, STM32_XTAL_CLOCK_SOURCE, STM32_XTAL_FREQ);
	// setup PLL
	CC_SetClockSource(cc_stm32, STM32_PLL_CLOCK, STM32_HSE_CLOCK_SOURCE, 64000000);
	// setup SYSCLK (At the end)
	CC_SetClockSource(cc_stm32, STM32_SYSCLK_CLOCK, STM32_PLL_CLOCK_SOURCE, 64000000);
	// setup HCLK
	CC_SetClockSource(cc_stm32, STM32_HCLK_CLOCK, STM32_SYSCLK_CLOCK_SOURCE, 64000000);
	// setup PCLK1 max 42MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK1_CLOCK, STM32_HCLK_CLOCK_SOURCE, 32000000);
	// setup PCLK2 max 82MHz
	CC_SetClockSource(cc_stm32, STM32_PCLK2_CLOCK, STM32_HCLK_CLOCK_SOURCE, 32000000);

	HAL_GPIO_Init();

// -----------------------------------------------------------------------------
//  Diagnostic Declaration Section
// -----------------------------------------------------------------------------

	IODEV_Init(IO_DEV);
	IODEV_EnableWrite(IO_DEV);
	IODEV_EnableRead(IO_DEV);

	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV);
    DIAG_ActivateChannel(0);

// -----------------------------------------------------------------------------
//  IOBUS Declaration Section
// -----------------------------------------------------------------------------

	IOBUS_Init(IO_BUS);
	IOBUS_EnableRead(IO_BUS);
	IOBUS_EnableWrite(IO_BUS);

// -----------------------------------------------------------------------------
//  Search all devices on the bus
// -----------------------------------------------------------------------------

	IOBusAddr devices_rom[10];

	size_t number_of_devices = 0;

	if((number_of_devices = IOBUS_SearchDevices(IO_BUS, devices_rom, 0)))
	{
		DIAG0_LogMsg(0, "Found ");
		DIAG0_LogUINT(0, number_of_devices, 10);
		DIAG0_LogMsg(0, "devices on bus!");
		DIAG0_LogNL(0);

		int i;
		for(i=0; i<number_of_devices; i++){
			DIAG0_LogUINT(0, i, 10);
			DIAG0_LogMsg(0, ". ");
			DIAG0_LogUINT(0, devices_rom[i]>>0x20, 16);
			DIAG0_LogUINT(0, devices_rom[i], 16);
			DIAG0_LogNL(0);
		}
	}

// -----------------------------------------------------------------------------
//  IOBUS Device Declaration and Initialization Section
// -----------------------------------------------------------------------------

	// create bus devices
	IOBUS_DEVICE_DECLARE(DS18S20_SENSOR1, IO_BUS, 0x3500080274DA0610, 0);
	// eg. IOBUS_DEVICE_DECLARE(DS18S20_SENSOR2, IO_BUS, 0x0560A402DFCA051A, 0);
    // or take id from search device algorithm

	// initialize ds18s20 abstraction
	DS18S20_Init(DS18S20_SENSOR1);

// -----------------------------------------------------------------------------
//  Read Rom Section
// -----------------------------------------------------------------------------

	// This section works only, when one device is on the bus
	uint64_t rom = 0;

	// read ROM from DS18S20_SENSOR1
	if(DS18S20_OK != DS18S20_ReadROM(DS18S20_SENSOR1, &rom)){
		DIAG0_LogMsg(0, "Can't read ROM number\n");
		DIAG0_LogMsg(0, "Error of connection or more than 1 device on the bus!\n\n");
	}else{

		DIAG0_LogMsg(0, "Rom is: ");

		DIAG0_LogUINT(0, rom>>0x20, 16);
		DIAG0_LogUINT(0, rom, 16);

		DIAG0_LogNL(0);
		DIAG0_LogNL(0);
	}

// -----------------------------------------------------------------------------
//  Copy Alarm From EEPROM Section
// -----------------------------------------------------------------------------

	DIAG0_LogMsg(0, "Trying to restore alarm from EEPROM memory: ");

	if(DS18S20_OK != DS18S20_LoadAlarmTrigger(DS18S20_SENSOR1)){
		DIAG0_LogMsg(0, "Can't load Alarm Trigger from EEPROM \n");
	}else{
		DIAG0_LogMsg(0, " OK!");
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Write Alarm in scrathpad Section
// -----------------------------------------------------------------------------

	DS18S20_Alarm alarm;

	// high value alarm (+25)
	alarm.TH.sign = 0;
	alarm.TH.value = 25;

	// low value alarm (-10)
	alarm.TL.sign = 1;
	alarm.TL.value = 10;

	DIAG0_LogMsg(0, "Alarm will set if temperature is not <-10, 25) celcius ");
	DIAG0_LogNL(0);

	// read ROM from DS18S20_SENSOR1
	if(DS18S20_OK != DS18S20_WriteAlarmTrigger(DS18S20_SENSOR1, &alarm)){
		DIAG0_LogMsg(0, "Can't set Alarm Trigger\n");
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Read Alarm from scrathpad
// -----------------------------------------------------------------------------

	// read ROM from DS18S20_SENSOR1
	if(DS18S20_OK != DS18S20_ReadAlarmTrigger(DS18S20_SENSOR1, &alarm)){
	DIAG0_LogMsg(0, "Can't read Alarm Trigger\n");
	}

	DIAG0_LogMsg(0, "Alarm is set to: ");
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "\tTH = ");
	if(alarm.TH.sign){
		DIAG0_LogMsg(0, "-");
	}
	DIAG0_LogUINT(0, alarm.TH.value, 10);
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "\tTL = ");
	if(alarm.TL.sign){
		DIAG0_LogMsg(0, "-");
	}
	DIAG0_LogUINT(0, alarm.TL.value, 10);

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Write Alarm to EEPROM Section
// -----------------------------------------------------------------------------

	DIAG0_LogMsg(0, "Trying to save alarm on EEPROM memory: ");

	if(DS18S20_OK != DS18S20_SaveAlarmTrigger(DS18S20_SENSOR1)){
		DIAG0_LogMsg(0, "Can't save Alarm Trigger on EEPROM \n");
	}else{
		DIAG0_LogMsg(0, " OK!");
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Read Temperature Section
// -----------------------------------------------------------------------------

	// declaration of Temperature structure
	DS18S20_Temperature pomiar;

	for (; ;){

		// read temperature from DS18S20_SENSOR1
		if(DS18S20_OK != DS18S20_ReadTemperature(DS18S20_SENSOR1, &pomiar)){
			DIAG0_LogMsg(0, "Can't read temperature!\n");
		}

		DIAG0_LogMsg(0, "Temperature is: ");

		if(pomiar.sign){
			DIAG0_LogMsg(0, "-");
		}

		DIAG0_LogUINT(0, pomiar.decimal, 10);
		DIAG0_LogMsg(0, ",");
		DIAG0_LogUINT(0, pomiar.fraction, 10);
		DIAG0_LogNL(0);

		// global search for all ds18s20 devices on bus
		if(DS18S20_OK != DS18S20_SearchAlarm(IO_BUS)){
			DIAG0_LogMsg(0, "DS18S20 device signaling alarm!\n");
		}

		DELAY_MS(1000);
	}

// -----------------------------------------------------------------------------
//  Deinitialization HAL Section
// -----------------------------------------------------------------------------

	// deinitialize ds18s20 devices
	DS18S20_Deinit(DS18S20_SENSOR1);

	// deinitialize IOBus
	IOBUS_Deinit(IO_BUS);

	// deinitialize IODevice
	IODEV_Deinit(IO_DEV);

	// deinitialize HAL core
	CORE_Deinit();
	
	return 0;

} /* main */

/*! \file main.c
    \brief Exemplary application, that uses IOBUS module.

*/
