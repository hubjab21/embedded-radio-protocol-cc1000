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
 Comments:      DS2431 EEPROM 1Kbit - 1Wire
================================================================================
*/

// include the one and only HAL header
#include "hal.h"
#include "hal_port_ds2431.h"
#include "string.h"

// helper macro for better visual protection state
#define PROTECTION_STATE_TO_STRING(state)  (((state) == 0x55) ? "Write protected" : ((state) == 0xAA) ? "EEPROM mode" : "Unprotected")

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
		DIAG0_LogMsg(0, " devices on bus!");
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

	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  IOBUS Device Declaration Section
// -----------------------------------------------------------------------------

	// create bus devices
	IOBUS_DEVICE_DECLARE(DS2431_MEMORY, IO_BUS, 0x05000005EDC22F2D, 0);
	// eg. IOBUS_DEVICE_DECLARE(DS18S20_SENSOR2, IO_BUS, 0x0560A402DFCA051A, 0);
    // or take id from search device algorithm

// -----------------------------------------------------------------------------
//  Configure DS2431 Memory Device
// -----------------------------------------------------------------------------

	// initialize DS2431 abstraction
	DS2431_Init(DS2431_MEMORY);

	DIAG0_LogMsg(0, "Initalized DS2431 Memory Device!");
	DIAG0_LogNL(0);

	// configure protection byte, not needed
	// in default, all protection register are set as unprotected
	// it's very important that ONCE programmed to DS2431_WRITE_PROTECT or DS2431_EEPROM_MODE
    // and configuration register becomes read only.
	DS2431_ProtectConfigTypeDef DS2431_ProtectConfigStruct;

	DS2431_ProtectConfigStruct.Memory_Page_0 = DS2431_NO_WRITE_PROTECT;
	DS2431_ProtectConfigStruct.Memory_Page_1 = DS2431_NO_WRITE_PROTECT;
	DS2431_ProtectConfigStruct.Memory_Page_2 = DS2431_EEPROM_MODE;
	DS2431_ProtectConfigStruct.Memory_Page_3 = DS2431_NO_WRITE_PROTECT;
	DS2431_ProtectConfigStruct.Copy_Protect  = DS2431_NO_WRITE_PROTECT;

	// configure protection setting
	if(DS2431_OK != DS2431_SetProtectMode(DS2431_MEMORY, &DS2431_ProtectConfigStruct)){
		DIAG0_LogMsg(0, "Cannot set protect mode!\n");
	}

	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Read DS2431 Memory Protection Modes
// -----------------------------------------------------------------------------

	// get protection setting
	if(DS2431_OK != DS2431_GetProtectMode(DS2431_MEMORY, &DS2431_ProtectConfigStruct)){
		DIAG0_LogMsg(0, "Cannot get protect mode!\n");
	}

	DIAG0_LogMsg(0, "Actual protection state is: ");
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "Memory Page 0: ");
	DIAG0_LogMsg(0, PROTECTION_STATE_TO_STRING(DS2431_ProtectConfigStruct.Memory_Page_0));
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "Memory Page 1: ");
	DIAG0_LogMsg(0, PROTECTION_STATE_TO_STRING(DS2431_ProtectConfigStruct.Memory_Page_1));
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "Memory Page 2: ");
	DIAG0_LogMsg(0, PROTECTION_STATE_TO_STRING(DS2431_ProtectConfigStruct.Memory_Page_2));
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "Memory Page 3: ");
	DIAG0_LogMsg(0, PROTECTION_STATE_TO_STRING(DS2431_ProtectConfigStruct.Memory_Page_3));
	DIAG0_LogNL(0);

	DIAG0_LogMsg(0, "Copy protect:  ");
	DIAG0_LogMsg(0, PROTECTION_STATE_TO_STRING(DS2431_ProtectConfigStruct.Copy_Protect));
	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Example of filling first two page and read from there
// -----------------------------------------------------------------------------

	DIAG0_LogMsg(0, "Trying to fill 2 first page of memory: ");
	DIAG0_LogNL(0);

	// declare 2
	uint8_t buff[DS2431_DATA_MEMORY_PAGE_SIZE*2];

	// fill buffer incrementing number
	int i = 0;
	for(i = 0;i<DS2431_DATA_MEMORY_PAGE_SIZE*2;i++){
		buff[i] = i;
	}

	// fill 2 first page
	if(DS2431_OK != DS2431_Write(DS2431_MEMORY, // IOBusDevice
								 buff, // data to be write
								 DS2431_DATA_MEMORY_PAGE_0, // start address
								 DS2431_DATA_MEMORY_PAGE_SIZE*2, // size of data
								 DS2431_SECURE_TRANSMISION))  // type of transmision
	{
		DIAG0_LogMsg(0, "Cannot write to memory!\n");
	}else{
		DIAG0_LogMsg(0, "Write OK!\n");
	}

	// clear buffer
	memset(buff, 0, DS2431_DATA_MEMORY_PAGE_SIZE*2);

	// read 2 first page
	if(DS2431_OK != DS2431_Read(DS2431_MEMORY, // IOBusDevice
			                    buff, // read buffer
			                    DS2431_DATA_MEMORY_PAGE_0, // start address
			                    DS2431_DATA_MEMORY_PAGE_SIZE*2)) // size of data
	{
		DIAG0_LogMsg(0, "Can't read memory! \n");
	}else{
		DIAG0_LogMsg(0, "Read OK!\n");
	}

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Page 0: ");
	DIAG0_LogNL(0);

	for(i=0;i<32;i++){
		DIAG0_LogUINT(0, buff[i], 10);
		DIAG0_LogNL(0);
	}

	DIAG0_LogNL(0);

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "Page 1: ");
	DIAG0_LogNL(0);

	for(i=32;i<64;i++){
		DIAG0_LogUINT(0, buff[i], 10);
		DIAG0_LogNL(0);
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Example of Page 2 in EEPROM mode (boolean AND on write)
// -----------------------------------------------------------------------------

	DIAG0_LogMsg(0, "Trying to fill 2nd page of memory (EEPROM mode)!\n");
	DIAG0_LogMsg(0, "To use EEPROM mode is highly recommended to fill all rows in 0xFF before change protect mode!");
	DIAG0_LogNL(0);

	// then write for example only 0xFF
	memset(buff, 0xFF, DS2431_DATA_MEMORY_PAGE_SIZE);

	DIAG0_LogMsg(0, "Writing only 0xFF: ");
	DIAG0_LogNL(0);

	// fill 2 page
	if(DS2431_OK != DS2431_Write(DS2431_MEMORY, // IOBusDevice
								 buff, // data to be write
								 DS2431_DATA_MEMORY_PAGE_2, // start address
								 DS2431_DATA_MEMORY_PAGE_SIZE, // size of data
								 DS2431_SECURE_CRC_TRANSMISION))  // type of transmision
	{
		DIAG0_LogMsg(0, "Cannot write to memory!\n");
	}else{
		DIAG0_LogMsg(0, "Write OK!\n");
	}

	// clear buffer
	memset(buff, 0, DS2431_DATA_MEMORY_PAGE_SIZE*2);

	// read 2 first page
	if(DS2431_OK != DS2431_Read(DS2431_MEMORY, // IOBusDevice
								buff, // read buffer
								DS2431_DATA_MEMORY_PAGE_2, // start address
								DS2431_DATA_MEMORY_PAGE_SIZE)) // size of data
	{
		DIAG0_LogMsg(0, "Can't read memory! \n");
	}else{
		DIAG0_LogMsg(0, "Read OK!\n");
	}

	DIAG0_LogNL(0);
	DIAG0_LogMsg(0, "2nd page: ");
	DIAG0_LogNL(0);

	for(i=0;i<32;i++){
		DIAG0_LogUINT(0, buff[i], 10);
		DIAG0_LogNL(0);
	}

	DIAG0_LogNL(0);
	DIAG0_LogNL(0);

// -----------------------------------------------------------------------------
//  Dummy loop
// -----------------------------------------------------------------------------

	while(1){
		;
	}

// -----------------------------------------------------------------------------
//  Deinitialization HAL Section
// -----------------------------------------------------------------------------

	// deinitialize ds18s20 devices
	DS2431_Deinit(DS2431_MEMORY);

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
