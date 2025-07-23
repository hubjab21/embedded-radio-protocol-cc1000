/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_ds18s20.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's Universal port
 Compiler:      %COMPILER%
 Hardware:      Embedded
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DS18S20 device
--------------------------------------------------------------------------------
 Comments:		High-Precision 1-Wire Digital Thermometer
================================================================================
*/

#include "hal_port_ds18s20.h"
#include "string.h"

// -----------------------------------------------------------------------------
//	helper function
// -----------------------------------------------------------------------------
uint8_t DS18S20_CalculateCRC(IOBusDevice dev, uint8_t *data_in, uint16_t number_of_byte);

// -----------------------------------------------------------------------------
//  DS18S20_init
// -----------------------------------------------------------------------------
void DS18S20_Init(IOBusDevice dev)
{

} /* DS18S20_Init */

// -----------------------------------------------------------------------------
//  DS18S20_Deinit
// -----------------------------------------------------------------------------
void DS18S20_Deinit(IOBusDevice dev)
{

} /* DS18S20_Deinit */

// -----------------------------------------------------------------------------
//  DS18S20_ReadTemperature
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_ReadTemperature(IOBusDevice dev, DS18S20_Temperature *temperature)
{
	// clear old value
	temperature->sign = 0;
	temperature->decimal = 0;
	temperature->fraction = 0;

	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	static const uint8_t cmd1[1] = { DEV_DS18S20_CONVERT_T };

	// force DS18S20 to convert temperature
	IOBUS_Write(dev->bus, dev->address, cmd1, 1, 0);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	// wait maximum convert time
	DELAY_MS(750);

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	uint8_t read_table[9] = {0,0,0,0,0,0,0,0,0};

	if(DS18S20_OK != DS18S20_ReadScratchpad(dev, read_table)){
		return DS18S20_BAD_CRC;
	}

	// calculate temperature
	if(read_table[1] == 0){
		// save temperature to buffer
		temperature->sign = 0;
		temperature->decimal = read_table[0] >> 1;
		temperature->fraction = ((read_table[0] & 0x01) ? 5 : 0);

	}else if(read_table[1] == 255){

		temperature->sign = 1;

		if((read_table[0] & 0x01)){
			temperature->decimal = (-1)*((128-(read_table[0] >> 1)) - 1);
			temperature->fraction = 5;
		}else{
			temperature->decimal = (-1)*(128-(read_table[0] >> 1));
			temperature->fraction = 0;
		}

	}else{
		return DS18S20_BAD_CRC;
	}

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_ReadTemperature */

// -----------------------------------------------------------------------------
//  DS18S20_ReadROM
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_ReadROM(IOBusDevice dev, uint64_t *rom)
{
	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	static const uint8_t cmd[1] = { DEV_DS18S20_READ_ROM };

	// force DS18S20 to send read ROM
	IOBUS_RawWrite(dev->bus, cmd, 1, 0);

	// read ROM to buffer
	IOBUS_Read(dev->bus, dev->address, rom, 8, 0);

	// compare first byte (CRC) with calculate CRC
	if(!((*rom >> 0x38) == DS18S20_CalculateCRC(dev, (uint8_t *)rom, 7))){
		return DS18S20_BAD_CRC;
	}

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_ReadROM */

// -----------------------------------------------------------------------------
//  DS18S20_WriteAlarmTrigger
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_WriteAlarmTrigger(IOBusDevice dev, DS18S20_Alarm *alarm)
{
	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	uint8_t data[2];
	data[0] = ((alarm->TH).value | ((alarm->TH).sign & 0x80));
	data[1] = ((alarm->TL).value | ((alarm->TH).sign & 0x80));

	// write scrathpad
	DS18S20_WriteScratchpad(dev, data);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_WriteAlarmTrigger */

// -----------------------------------------------------------------------------
//  DS18S20_ReadAlarmTrigger
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_ReadAlarmTrigger(IOBusDevice dev, DS18S20_Alarm *alarm)
{
	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	uint8_t read_table[9] = {0,0,0,0,0,0,0,0,0};

	if(DS18S20_OK != DS18S20_ReadScratchpad(dev, read_table)){
		return DS18S20_BAD_CRC;
	}

	// set alarm from a 2,3 byte of scrathpad
	(alarm->TH).value = (read_table[2] & 0x7f);
	(alarm->TH).sign = (read_table[2] & 0x80);

	(alarm->TL).value = (read_table[3] & 0x7f);
	(alarm->TL).sign = (read_table[3] & 0x80);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_ReadAlarmTrigger */

// -----------------------------------------------------------------------------
//  DS18S20_SaveAlarmTrigger
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_SaveAlarmTrigger(IOBusDevice dev)
{
	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	// write scrathpad on EEPROM
	DS18S20_CopyScratchpad(dev);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_SaveAlarmTrigger */

// -----------------------------------------------------------------------------
//  DS18S20_LoadAlarmTrigger
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_LoadAlarmTrigger(IOBusDevice dev)
{
	if(!(dev->bus)){
		return DS18S20_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS18S20_NO_RESET_PRESENCE_PULSE;
	}

	// write scrathpad on EEPROM
	DS18S20_RecallEE(dev);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS18S20_OK;

} /* DS18S20_LoadAlarmTrigger */

// -----------------------------------------------------------------------------
//  DS18S20_SearchAlarm
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_SearchAlarm(IOBus bus)
{
	static const uint8_t cmd[1] = { DEV_DS18S20_ALARM_SEARCH };
	uint8_t result;

	IOBUS_StartTransaction(bus);

	// force DS18S20 to send read SCRATCHPAD
	IOBUS_RawWrite(bus, cmd, 1, 0);

	// read ROM to buffer
	IOBUS_Read(bus, 0, &result, 1, 0);

	if(!(result & 0x01)){
		return DS18S20_ALARM_TRIGGER;
	}

	IOBUS_EndTransaction(bus);

	return DS18S20_OK;

} /* DS18S20_SearchAlarm */

// -----------------------------------------------------------------------------
//  DS18S20_ReadScratchpad
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_ReadScratchpad(IOBusDevice dev, uint8_t *scratchpad)
{
	static const uint8_t cmd[1] = { DEV_DS18S20_READ_SCRATCHPAD };
	uint8_t temp[9];

	// force DS18S20 to send read SCRATCHPAD
	IOBUS_Write(dev->bus, dev->address, cmd, 1, 0);

	// read ROM to buffer
	IOBUS_Read(dev->bus, dev->address, &temp, 9, 0);

	// copy temporary value to scratchpad
	memcpy(scratchpad, temp, 9);

	// compare CRC
	if(!(scratchpad[8] == DS18S20_CalculateCRC(dev, scratchpad, 8))){
		return DS18S20_BAD_CRC;
	}

	return DS18S20_OK;

} /* DS18S20_ReadScratchpad */

// -----------------------------------------------------------------------------
//  DS18S20_CopyScratchpad
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_CopyScratchpad(IOBusDevice dev)
{
	static const uint8_t cmd[1] = { DEV_DS18S20_COPY_SCRATCHPAD};

	// force DS18S20 to copy data from SCRATCHPAD to EEPROM
	IOBUS_Write(dev->bus, dev->address, cmd, 1, 0);

	return DS18S20_OK;

} /* DS18S20_CopyScratchpad */

// -----------------------------------------------------------------------------
//  DS18S20_WriteScratchpad
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_WriteScratchpad(IOBusDevice dev, uint8_t *data)
{
	static const uint8_t cmd[1] = { DEV_DS18S20_WRITE_SCRATCHPAD };

	// force DS18S20 to send write SCRATCHPAD
	IOBUS_Write(dev->bus, dev->address, cmd, 1, 0);

	// send 2 data bytes
	IOBUS_Write(dev->bus, dev->address, data, 2, 0);

	return DS18S20_OK;

} /* DS18S20_WriteScratchpad */

// -----------------------------------------------------------------------------
//  DS18S20_RecallEE
// -----------------------------------------------------------------------------
DS18S20_RESULT DS18S20_RecallEE(IOBusDevice dev)
{
	static const uint8_t cmd[1] = { DEV_DS18S20_RECALL_EE };

	// force DS18S20 to copy data from EEPROM to SCRATCHPAD
	IOBUS_Write(dev->bus, dev->address, cmd, 1, 0);

	return DS18S20_OK;

} /* DS18S20_RecallEE */

// -----------------------------------------------------------------------------
//  DS18S20_CalculateCRC
// -----------------------------------------------------------------------------
uint8_t DS18S20_CalculateCRC(IOBusDevice dev, uint8_t *data_in, uint16_t number_of_byte)
{
	uint8_t	 crc;
	uint16_t loop_count;
	uint8_t  bit_counter;
	uint8_t  data;
	uint8_t  feedback_bit;

	crc = DS18S20_CRC8INIT;

	for (loop_count = 0; loop_count != number_of_byte; loop_count++)
	{
		data = data_in[loop_count];

		bit_counter = 8;
		do {
			feedback_bit = (crc ^ data) & 0x01;

			if ( feedback_bit == 0x01 ) {
				crc = crc ^ DS18S20_CRC8POLY;
			}
			crc = (crc >> 1) & 0x7F;
			if ( feedback_bit == 0x01 ) {
				crc = crc | 0x80;
			}

			data = data >> 1;
			bit_counter--;

		} while (bit_counter > 0);
	}

	return crc;

} /* DS18S20_CalculateCRC */

