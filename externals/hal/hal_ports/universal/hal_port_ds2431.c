/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			hal_port_ds2431.c
 Author:        Łukasz Duda
 Purpose:       HALFRED's Universal port
 Compiler:      %COMPILER%
 Hardware:      Embedded
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       DS2431 device
--------------------------------------------------------------------------------
 Comments:		DS2431 EEPROM 1Kbit - 1Wire
================================================================================
*/

#include "hal_port_ds2431.h"
#include "string.h"
#include <stdbool.h>

// -----------------------------------------------------------------------------
//	helper function
// -----------------------------------------------------------------------------
#define DS2431_PROTECTION_MODE(mode)     (uint8_t)(( ((mode) != 0xAA) && ((mode) != 0x55) ) ? 0x00 : (mode) )

bool DS2431_CheckMemoryRange(uint16_t address, size_t size, bool for_write);
uint16_t DS2431_CalculateNCRC(uint8_t *data_in1, uint8_t *data_in2, size_t number_of_byte1, size_t number_of_byte2);

// -----------------------------------------------------------------------------
//  DS2431_init
// -----------------------------------------------------------------------------
void DS2431_Init(IOBusDevice dev)
{

} /* DS2431_Init */

// -----------------------------------------------------------------------------
//  DS2431_Deinit
// -----------------------------------------------------------------------------
void DS2431_Deinit(IOBusDevice dev)
{

} /* DS2431_Deinit */

// -----------------------------------------------------------------------------
//  DS2431_Write
// -----------------------------------------------------------------------------
DS2431_RESULT DS2431_Write(IOBusDevice dev, uint8_t *src, uint16_t address, size_t size, DS2431_WriteType type)
{

	// buffer for commands and transmission staff and crc
	uint8_t cmd[4],i,j;
	uint16_t crc;

	if(!(dev->bus)){
		return DS2431_NO_BUS;
	}

	// check addressing range
	if(true != DS2431_CheckMemoryRange(address, size, true)){
		return DS2431_ADDRESS_ERROR;
	}

	// DS2431 support only full row transfer, so if more data fragmentation and sending
	for(i=0;i<(size/DS2431_DATA_MEMORY_ROW_SIZE);i++){

		// reset slaves on bus
		if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
			return DS2431_NO_RESET_PRESENCE_PULSE;
		}

		cmd[0] = DS2431_WRITE_SCRATCHPAD;
		cmd[1] = (uint8_t)(address & 0x00ff);
		cmd[2] = (uint8_t)(address >> 8);

		// send write scratchpad command and destination address
		IOBUS_Write(dev->bus, dev->address, cmd, 3, 0);

		// send a data
		IOBUS_Write(dev->bus, dev->address, src, DS2431_DATA_MEMORY_ROW_SIZE, 0);

		// read a CRC
		IOBUS_Read(dev->bus, dev->address, &crc, 2, 0);

		// compare a CRC
		if(type != DS2431_UNSECURE_FAST_TRANSMISION){
			// calculate a CRC
			if((uint16_t)crc != DS2431_CalculateNCRC(cmd, src, 3, DS2431_DATA_MEMORY_ROW_SIZE)){
				return DS2431_BAD_CRC;
			}
		}

		// end of transaction
		IOBUS_EndTransaction(dev->bus);

		// declare TA1,TA2,E/S
		uint8_t control_bit[3];
		control_bit[0] = cmd[1];
		control_bit[1] = cmd[2];
		control_bit[2] = DS2431_ES_REGISTER_FLAG;

		if(type == DS2431_SECURE_TRANSMISION){

			// reset slaves on bus
			if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
				return DS2431_NO_RESET_PRESENCE_PULSE;
			}

			cmd[0] = DS2431_READ_SCRATCHPAD;

			// send read scratchpad command and destination address
			IOBUS_Write(dev->bus, dev->address, cmd, 1, 0);

			// read a TA1,TA2,E/S
			IOBUS_Read(dev->bus, dev->address, &control_bit, 3, 0);

			// if security is essensial, read scratchpad and check if already is the same, also CRC
			uint8_t temp[10];

			IOBUS_Read(dev->bus, dev->address, &temp, 10, 0);

			for(j=0;j<8;j++){
				if(temp[j] != *(src+j)){
					return DS2431_SCRATCHPAD_VERIFY_FAILED;
				}
			}

			// crc temporary variables
			uint8_t crc_temp[4] = {cmd[0], control_bit[0], control_bit[1], control_bit[2]};

			// what is interested, when CRC is come from SCRATCHPAD READ command
			// is reverse first LSB second MSB, its different to WRITE command
			uint16_t crc_compute = (uint16_t)(temp[8] | (temp[9] << 8));

			// compare CRC
			if((uint16_t)crc_compute != DS2431_CalculateNCRC(crc_temp, temp, 4, DS2431_DATA_MEMORY_ROW_SIZE)){
				return DS2431_BAD_CRC;
			}

			// checking TA1,TA2 bit
			if((control_bit[0] != cmd[1]) || (control_bit[1] != cmd[2])){
				return DS2431_ADDRESS_ERROR;
			}

			// checkinh if some data loss due to power, not ended transmision or protection byte
			if(control_bit[2] != DS2431_ES_REGISTER_FLAG){
				if(control_bit[2] & 0x80){
					return DS2431_AUTHORIZATION_NOT_ACCEPTED;
				}else if(control_bit[2] & 0x20){
					return DS2431_LOSS_POWER_OR_NOT_ENOUGH_BIT_SEND;
				}else{
					return DS2431_NO_DATA_INTEGRITY;
				}
			}

			// end of transaction
			IOBUS_EndTransaction(dev->bus);
		}

		// reset slaves on bus
		if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
			return DS2431_NO_RESET_PRESENCE_PULSE;
		}

		cmd[0] = DS2431_COPY_SCRATCHPAD;
		cmd[1] = control_bit[0];
		cmd[2] = control_bit[1];
		cmd[3] = control_bit[2];

		// send copy scratchpad command and destination address
		IOBUS_Write(dev->bus, dev->address, cmd, 4, 0);

		// maximum save time
		DELAY_MS(20);

		// read status flag (0xAA = SUCCESS, 0xFF = FAILED)
		IOBUS_Read(dev->bus, dev->address, &cmd, 1, 0);

		if(cmd[0] != DS2431_COPY_SUCCESS_FLAG){
			return DS2431_COPY_STATUS_FAILED;
		}

		// end of transaction
		IOBUS_EndTransaction(dev->bus);

		src += DS2431_DATA_MEMORY_ROW_SIZE;
		address += DS2431_DATA_MEMORY_ROW_SIZE;
	}

	return DS2431_OK;

} /* DS2431_Write */

// -----------------------------------------------------------------------------
//  DS2431_Read
// -----------------------------------------------------------------------------
DS2431_RESULT DS2431_Read(IOBusDevice dev, uint8_t *dest, uint16_t address, size_t size)
{
	if(!(dev->bus)){
		return DS2431_NO_BUS;
	}

	if(true != DS2431_CheckMemoryRange(address, size, false)){
		return DS2431_ADDRESS_ERROR;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS2431_NO_RESET_PRESENCE_PULSE;
	}

	uint8_t cmd[3];

	cmd[0] = DS2431_READ_MEMORY;
	cmd[1] = (uint8_t)(address & 0x00ff);
	cmd[2] = (uint8_t)(address >> 8);

	// send read memory command and destination address
	IOBUS_Write(dev->bus, dev->address, cmd, 3, 0);

	// read a data
	IOBUS_Read(dev->bus, dev->address, dest, size, 0);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS2431_OK;

} /* DS2431_Read */

// -----------------------------------------------------------------------------
//  DS2431_GetProtectMode
// -----------------------------------------------------------------------------
DS2431_RESULT DS2431_GetProtectMode(IOBusDevice dev, DS2431_ProtectConfigTypeDef *config)
{
	if(!(dev->bus)){
		return DS2431_NO_BUS;
	}

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS2431_NO_RESET_PRESENCE_PULSE;
	}

	uint8_t cmd[3], buff[DS2431_DATA_MEMORY_ROW_SIZE];

	cmd[0] = DS2431_READ_MEMORY;
	cmd[1] = (uint8_t)(DS2431_PROTECTION_ROW & 0x00ff);
	cmd[2] = 0;

	// send read memory command and destination address
	IOBUS_Write(dev->bus, dev->address, cmd, 3, 0);

	// read a data
	IOBUS_Read(dev->bus, dev->address, buff, DS2431_DATA_MEMORY_ROW_SIZE, 0);

	config->Memory_Page_0 = DS2431_PROTECTION_MODE(buff[0]);
	config->Memory_Page_1 = DS2431_PROTECTION_MODE(buff[1]);
	config->Memory_Page_2 = DS2431_PROTECTION_MODE(buff[2]);
	config->Memory_Page_3 = DS2431_PROTECTION_MODE(buff[3]);
	config->Copy_Protect  = DS2431_PROTECTION_MODE(buff[4]);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS2431_OK;

} /* DS2431_GetProtectMode */

// -----------------------------------------------------------------------------
//  DS2431_SetProtectMode
// -----------------------------------------------------------------------------
DS2431_RESULT DS2431_SetProtectMode(IOBusDevice dev, DS2431_ProtectConfigTypeDef *config)
{
	if(!(dev->bus)){
		return DS2431_NO_BUS;
	}

	// read first to not change important data
	uint8_t cmd[3], buff[DS2431_DATA_MEMORY_ROW_SIZE];
	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS2431_NO_RESET_PRESENCE_PULSE;
	}

	cmd[0] = DS2431_READ_MEMORY;
	cmd[1] = (uint8_t)(DS2431_PROTECTION_ROW & 0x00ff);
	cmd[2] = 0;

	// send read memory command and destination address
	IOBUS_Write(dev->bus, dev->address, cmd, 3, 0);

	// read a data
	IOBUS_Read(dev->bus, dev->address, buff, DS2431_DATA_MEMORY_ROW_SIZE, 0);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	// reset slaves on bus
	if(HALRESULT_OK != IOBUS_StartTransaction(dev->bus)){
		return DS2431_NO_RESET_PRESENCE_PULSE;
	}

	buff[0] = DS2431_PROTECTION_MODE(config->Memory_Page_0);
	buff[1] = DS2431_PROTECTION_MODE(config->Memory_Page_1);
	buff[2] = DS2431_PROTECTION_MODE(config->Memory_Page_2);
	buff[3] = DS2431_PROTECTION_MODE(config->Memory_Page_3);
	buff[4] = DS2431_PROTECTION_MODE(config->Copy_Protect);

	DS2431_Write(dev, buff, DS2431_PROTECTION_ROW, DS2431_DATA_MEMORY_ROW_SIZE, DS2431_SECURE_TRANSMISION);

	// end of transaction
	IOBUS_EndTransaction(dev->bus);

	return DS2431_OK;
} /* DS2431_SetProtectMode */

// -----------------------------------------------------------------------------
//  DS2431_CheckMemoryRange
// -----------------------------------------------------------------------------
bool DS2431_CheckMemoryRange(uint16_t address, size_t size, bool for_write)
{
	if(address == 0x0080 && size == 0x08){
		return true;
	}

	if(address >= 0x0080 || (address + size) > 0x0080){
		return false;
	}

	if(for_write){
		if((address % DS2431_DATA_MEMORY_ROW_SIZE)){
			return false;
		}
	}

	return true;

} /* DS2431_CheckMemoryRange */

// -----------------------------------------------------------------------------
//  DS2431_CalculateNCRC
// -----------------------------------------------------------------------------
uint16_t DS2431_CalculateNCRC(uint8_t *data_in1, uint8_t *data_in2, size_t number_of_byte1, size_t number_of_byte2)
{
	 uint16_t crc=0;

	 uint8_t i,j;

	  for (i=0; i<number_of_byte1;i++)
	  {

			uint8_t inbyte = data_in1[i];
			for (j=0;j<8;j++)
			{
				  uint8_t mix = ((uint8_t)(crc)^ inbyte) & 0x01;
				  crc = crc >> 1;
				  if (mix)
						crc = crc ^ 0xA001;

				  inbyte = inbyte >> 1;
			}
	  }

	  for (i=0; i<number_of_byte2;i++)
	  {

			uint8_t inbyte = data_in2[i];
			for (j=0;j<8;j++)
			{
				  uint8_t mix = ((uint8_t)(crc)^ inbyte) & 0x01;
				  crc = crc >> 1;
				  if (mix)
						crc = crc ^ 0xA001;

				  inbyte = inbyte >> 1;
			}
	  }

	  // to simplify, change bit position and negate
	  return ~((uint16_t)crc);

} /* DS2431_CalculateNCRC */

