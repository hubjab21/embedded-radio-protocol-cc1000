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

#ifndef HAL_PORT_DS18S20_H
#define HAL_PORT_DS18S20_H

#include <stdint.h>
#include <stdbool.h>
#include "hal.h"

/* ROM Commands */
#define DEV_DS18S20_SEARCH_ROM			0xF0
#define	DEV_DS18S20_READ_ROM			0x33
#define DEV_DS18S20_MATCH_ROM			0x55
#define DEV_DS18S20_SKIP_ROM			0xCC
#define DEV_DS18S20_ALARM_SEARCH		0xEC

/* Function Commands */
#define DEV_DS18S20_CONVERT_T			0x44
#define DEV_DS18S20_WRITE_SCRATCHPAD	0x4E
#define DEV_DS18S20_READ_SCRATCHPAD		0xBE
#define DEV_DS18S20_COPY_SCRATCHPAD		0x48
#define DEV_DS18S20_RECALL_EE			0xB8
#define DEV_DS18S20_READ_POWER_SUPPLY	0xB4

/* CRC parameters */
#define DS18S20_CRC8INIT	0x00
#define DS18S20_CRC8POLY	0x18              //0X18 = X^8+X^5+X^4+X^0

/* Family Code */
#define DEV_DS18S20_FAMILY_CODE			0x10

/* DS18S20 Results */
typedef enum{
	DS18S20_OK = 0,
	DS18S20_BAD_CRC,
	DS18S20_ALARM_TRIGGER,
	DS18S20_NO_RESET_PRESENCE_PULSE,
	DS18S20_NO_BUS
} DS18S20_RESULT;

/* DS18S20 Temperature Return Type */
typedef struct{
	bool sign; /* 0 means positive value */
	uint8_t decimal;
	uint8_t fraction;
} DS18S20_Temperature;

/* DS18S20 Alarm Type */
typedef struct{
	struct {
		bool sign;
		uint8_t value;
	} TH;
	struct {
		bool sign;
		uint8_t value;
	} TL;
} DS18S20_Alarm;

// -----------------------------------------------------------------------------
//  User functions API
// -----------------------------------------------------------------------------

/** Initialize DS18S20 Thermometer
	\param dev: a IODevice structure
	\return none
*/
void DS18S20_Init(IOBusDevice dev);

/** Deinitialize DS18S20 Thermometer
	\param dev: a IOBusDevice structure
	\return none
*/
void DS18S20_Deinit(IOBusDevice dev);

/** Read temperature from ds18s20 sensor (range: -55 to +85 with 0.5 Celsius degree accurancy).
  * With 0.5C resolution, a half bit is put into fractional part of variable.
  * In order to approximately 750ms convert time, delay loop is used inside, to get better efficiency,
  * is possible to do stuff like: set alarm triggers -> force convert_t -> check alarm flags -> (do sth from min. 750ms)
  *
  * Example usage: (Let assume that measurde temperature is -13,5 degree of Celcius)
  *
  * DS18S20_Temperature temperature;
  * DS18S20_ReadTemperature(IOB_1WIRE_SENSOR, &temperature);
  * printf(tempetarue.sign); -> 1 (0 otherwise)
  * printf(temperatur.decimal); ->  13
  * printf(temperatur.fraction); -> 5
  *
	\param dev: a IOBusDevice structure
	\param temperature: a pointer to DS18S20_Temperature struct
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus,
			DS18S20_BAD_CRC if CRC is bad
*/
DS18S20_RESULT DS18S20_ReadTemperature(IOBusDevice dev, DS18S20_Temperature* temperature);

/** Read ROM from ds18s20 sensor (64bit)
  *	| 8 bit CRC | 48 bit unique serial number | 8 bit family code |
  *
	\param dev: a IOBusDevice structure
	\param rom: a pointer to 64 bit unsigned int, save there unique lasered ROME code
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus,
			DS18S20_BAD_CRC if CRC is bad
*/
DS18S20_RESULT DS18S20_ReadROM(IOBusDevice dev, uint64_t *rom);

/** Write 2 byte of alarm level
  *	| T_H | T_L |
  *
	\param  dev: a IOBusDevice structure
	\param  alarm: a pointer to DS18S20_Alarm struct, read from there TH,TL and put to scrachpad
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus
*/
DS18S20_RESULT DS18S20_WriteAlarmTrigger(IOBusDevice dev, DS18S20_Alarm *alarm);

/** Read 2 byte of alarm level
  *	| T_H | T_L |
  *
	\param  dev: a IOBusDevice structure
	\param  alarm: a pointer to DS18S20_Alarm struct, write there TH and TL
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus,
			DS18S20_BAD_CRC if CRC is bad
*/
DS18S20_RESULT DS18S20_ReadAlarmTrigger(IOBusDevice dev, DS18S20_Alarm *alarm);

/** Save 2 byte of TH and TL alarm trigger value and save them on EEPROM
	\param  dev: a IOBusDevice structure
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus
*/
DS18S20_RESULT DS18S20_SaveAlarmTrigger(IOBusDevice dev);

/** Load 2 byte of TH and TL alarm trigger from EEPROM and put them to scratchpad
	\param  dev: a IOBusDevice structure
	\return DS18S20_OK if is ok, DS18S20_NO_RESET_PRESENCE_PULSE if is no device in the bus
*/
DS18S20_RESULT DS18S20_LoadAlarmTrigger(IOBusDevice dev);

/** This is a global request. Searching ds18s20's where flag of alarm is set
	\param  dev: a IOBus structure
	\return DS18S20_OK if is ok, DS18S20_ALARM_TRIGGER if some alarm is set
*/
DS18S20_RESULT DS18S20_SearchAlarm(IOBus bus);

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------

DS18S20_RESULT DS18S20_ReadScratchpad(IOBusDevice dev, uint8_t *scratchpad);

DS18S20_RESULT DS18S20_CopyScratchpad(IOBusDevice dev);

DS18S20_RESULT DS18S20_WriteScratchpad(IOBusDevice dev, uint8_t *data);

DS18S20_RESULT DS18S20_RecallEE(IOBusDevice dev);


#endif /* HAL_PORT_DS18S20_H */
