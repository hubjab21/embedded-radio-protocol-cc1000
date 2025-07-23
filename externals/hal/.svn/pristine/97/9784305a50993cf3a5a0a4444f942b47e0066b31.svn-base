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

#ifndef HAL_PORT_DS2431_H
#define HAL_PORT_DS2431_H

#include <stdint.h>
#include <stdbool.h>
#include "hal.h"

/* ROM Commands */
#define DS2431_SEARCH_ROM			 0xF0
#define	DS2431_READ_ROM				 0x33
#define DS2431_MATCH_ROM			 0x55
#define DS2431_SKIP_ROM				 0xCC

/* Function Commands */
#define DS2431_WRITE_SCRATCHPAD		 0x0F
#define DS2431_READ_SCRATCHPAD		 0xAA
#define DS2431_COPY_SCRATCHPAD		 0x55
#define DS2431_READ_MEMORY			 0xF0

/* Family Code */
#define DS2431_FAMILY_CODE			 0x2D
#define DS2431_COPY_SUCCESS_FLAG	 0xAA
#define DS2431_ES_REGISTER_FLAG		 0x07

/* Page Address */
#define DS2431_DATA_MEMORY_PAGE_0	 0x0000
#define DS2431_DATA_MEMORY_PAGE_1	 0x0020
#define DS2431_DATA_MEMORY_PAGE_2	 0x0040
#define DS2431_DATA_MEMORY_PAGE_3	 0x0060

#define DS2431_DATA_MEMORY_PAGE_SIZE 0x20
#define DS2431_DATA_MEMORY_ROW_SIZE  0x08

#define DS2431_DATA_MEMORY_ROW_0 	 0x0000
#define DS2431_DATA_MEMORY_ROW_1     0x0008
#define DS2431_DATA_MEMORY_ROW_2     0x0010
#define DS2431_DATA_MEMORY_ROW_3     0x0018
#define DS2431_DATA_MEMORY_ROW_4	 0x0020
#define DS2431_DATA_MEMORY_ROW_5     0x0028
#define DS2431_DATA_MEMORY_ROW_6     0x0030
#define DS2431_DATA_MEMORY_ROW_7     0x0038
#define DS2431_DATA_MEMORY_ROW_8     0x0040
#define DS2431_DATA_MEMORY_ROW_9     0x0048
#define DS2431_DATA_MEMORY_ROW_10    0x0050
#define DS2431_DATA_MEMORY_ROW_11    0x0058
#define DS2431_DATA_MEMORY_ROW_12    0x0060
#define DS2431_DATA_MEMORY_ROW_13    0x0068
#define DS2431_DATA_MEMORY_ROW_14    0x0070
#define DS2431_DATA_MEMORY_ROW_15    0x0078
/* Protection row */
#define DS2431_PROTECTION_ROW		 0x0080
/* Reserved */
#define DS2431_RESERVED_ROW		     0x0088

/* Write protect mode */
typedef enum{
	DS2431_NO_WRITE_PROTECT = 0x00,
	DS2431_WRITE_PROTECT = 0x55,
	DS2431_EEPROM_MODE = 0xAA
} DS2431_ProtectionMode;

/* Protection Config struct */
typedef struct{
	DS2431_ProtectionMode Memory_Page_0;
	DS2431_ProtectionMode Memory_Page_1;
	DS2431_ProtectionMode Memory_Page_2;
	DS2431_ProtectionMode Memory_Page_3;
	DS2431_ProtectionMode Copy_Protect;
} DS2431_ProtectConfigTypeDef;

typedef enum{
	DS2431_SECURE_TRANSMISION = 0, /* With CRC (writing, reading) and read scratchpad to ensure transmision is ok */
	DS2431_SECURE_CRC_TRANSMISION, /* With CRC check of writing */
	DS2431_UNSECURE_FAST_TRANSMISION /* Only transmit and copy to EEPROM */
} DS2431_WriteType;

/* DS2431 Results */
typedef enum{
	DS2431_OK = 0,
	DS2431_BAD_CRC,
	DS2431_NO_RESET_PRESENCE_PULSE,
	DS2431_NO_BUS,
	DS2431_ADDRESS_ERROR,
	DS2431_COPY_STATUS_FAILED,
	DS2431_AUTHORIZATION_NOT_ACCEPTED,
	DS2431_NO_DATA_INTEGRITY,
	DS2431_LOSS_POWER_OR_NOT_ENOUGH_BIT_SEND,
	DS2431_SCRATCHPAD_VERIFY_FAILED
} DS2431_RESULT;

// -----------------------------------------------------------------------------
//  User functions API
// -----------------------------------------------------------------------------

/** Initialize DS2431 Device

	\param dev: a IODevice structure
	\return none
*/
void DS2431_Init(IOBusDevice dev);

/** Deinitialize DS2431 Device

	\param dev: a IOBusDevice structure
	\return none
*/
void DS2431_Deinit(IOBusDevice dev);

/** Set protection mode for Memory Page and Copy Operation (copy from scratchpad to EEPROM).
    It's very important that ONCE programmed to DS2431_WRITE_PROTECT or DS2431_EEPROM_MODE and
    configuration register becomes read only.
    It's highly recommended to fill all field with 0xFF before set EEPROM_MODE, to fully
    use this mode, otherwise it's imposible to change '0' bit to '1'.

	\param dev: a IOBusDevice structure
	\param config: pointer to a DS2431_ProtectConfigTypeDef structure that contains the configuration
	               setting for the protection of memory
	\return none
*/
DS2431_RESULT DS2431_SetProtectMode(IOBusDevice dev, DS2431_ProtectConfigTypeDef *config);

/** This function return actual configuration of memory protection.

	\param dev: a IOBusDevice structure
	\param config: pointer to a DS2431_ProtectConfigTypeDef structure
	\return none
*/
DS2431_RESULT DS2431_GetProtectMode(IOBusDevice dev, DS2431_ProtectConfigTypeDef *config);

/** Write data to memory of DS2431, it's only allowed to addressing start on a row boundary,
    so it's recommended to use defines as DS2431_DATA_MEMORY_ROW_0 and size n*DS2431_DATA_MEMORY_ROW_SIZE
    or to use define as DS2431_DATA_MEMORY_PAGE_0 and size n*DS2431_DATA_MEMORY_PAGE_SIZE.
    It's also important, to write all data field in 0xFF, when EEPROM_MODE is enabled, due to
    boolean AND action.
    In EEPROM_MODE it's better to not use DS2431_SECURE_TRANSMISION but only DS2431_SECURE_CRC_TRANSMISION or
    DS2431_UNSECURE_FAST_TRANSMISION, due to working of EEPROM MODE (becouse bit '0' never become '1' int this type),
    and some comparision can failed.

	\param dev: a IOBusDevice structure
	\return none
*/
DS2431_RESULT DS2431_Write(IOBusDevice dev, uint8_t *src, uint16_t address, size_t size, DS2431_WriteType type);

/** Read memory from DS2431, it's only allowed to addressing memory page (0x0000 to 0x0080).
    Size must be multiple of memory row size, wchich is give as DS2431_DATA_MEMORY_ROW_SIZE.

	\param dev: a IOBusDevice structure
	\return none
*/
DS2431_RESULT DS2431_Read(IOBusDevice dev, uint8_t *dest, uint16_t address, size_t size);

#endif /* HAL_PORT_DS2431_H */
