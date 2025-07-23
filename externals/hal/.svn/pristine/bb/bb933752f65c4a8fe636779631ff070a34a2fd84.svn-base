/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File: 			main.c
 Author:        Łukasz Duda, Michal Kochanowskis
 Purpose:       HALFRED's CLK module example
 Compiler:      %COMPILER%
 Hardware:      AT91SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       exemplary application, that uses SPI module
--------------------------------------------------------------------------------
 Comments:
================================================================================
*/

// Include the one and only HAL header
#include "hal.h"
// Definitions of AT45 memory
#define NV_AT45DB_CMD_MEMORY_PAGE_READ                          0xD2
#define NV_AT45DB_CMD_CONT_ARRAY_READ_LEGACY_CMD                0xE8
#define NV_AT45DB_CMD_CONT_ARRAY_READ_LOW_FREQ                  0x03
#define NV_AT45DB_CMD_CONT_ARRAY_READ_HIGH_FREQ                 0x0B
#define NV_AT45DB_CMD_BUFFER1_READ_LOW_FREQ                     0xD1
#define NV_AT45DB_CMD_BUFFER2_READ_LOW_FREQ                     0xD3
#define NV_AT45DB_CMD_BUFFER1_READ                              0xD4
#define NV_AT45DB_CMD_BUFFER2_READ                              0xD6

#define NV_AT45DB_CMD_BUFFER1_WRITE                             0x84
#define NV_AT45DB_CMD_BUFFER2_WRITE                             0x87
#define NV_AT45DB_CMD_BUFFER1_TO_MEMORY_WITH_ERASE              0x83
#define NV_AT45DB_CMD_BUFFER2_TO_MEMORY_WITH_ERASE              0x86
#define NV_AT45DB_CMD_BUFFER1_TO_MEMORY                         0x88
#define NV_AT45DB_CMD_BUFFER2_TO_MEMORY                         0x89
#define NV_AT45DB_CMD_PAGE_ERASE                                0x81
#define NV_AT45DB_CMD_BLOCK_ERASE                               0x50
#define NV_AT45DB_CMD_SECTOR_ERASE                              0x7C
#define NV_AT45DB_CMD_CHIP_ERASE_B0                             0xC7
#define NV_AT45DB_CMD_CHIP_ERASE_B1                             0x94
#define NV_AT45DB_CMD_CHIP_ERASE_B2                             0x80
#define NV_AT45DB_CMD_CHIP_ERASE_B3                             0x9A
#define NV_AT45DB_CMD_MEMORY_PAGE_PROGRAM_THROUGH_BUFFER1       0x82
#define NV_AT45DB_CMD_MEMORY_PAGE_PROGRAM_THROUGH_BUFFER2       0x85

#define NV_AT45DB_CMD_ENABLE_SECTOR_PROTECTION                  0x3D2A7FA9
#define NV_AT45DB_CMD_DISABLE_SECTOR_PROTECTION                 0x3D2A7F9A
#define NV_AT45DB_CMD_ERASE_SECTOR_PROTECTION_REGISTER          0x3D2A7FCF
#define NV_AT45DB_CMD_PROGRAM_SECTOR_PROTECTION_REGISTER        0x3D2A7FFC
#define NV_AT45DB_CMD_READ_SECTOR_PROTECTION_REGISTER           0x32
#define NV_AT45DB_CMD_SECTOR_LOCKDOWN                           0x3D2A7F30
#define NV_AT45DB_CMD_READ_SECTOR_LOCKDOWN_REGISTER             0x35
#define NV_AT45DB_CMD_PROGRAM_SECURITY_REGISTER                 0x9B000000
#define NV_AT45DB_CMD_READ_SECURITY_REGISTER                    0x77

#define NV_AT45DB_CMD_MEMORY_PAGE_TO_BUFFER1_TRANSFER           0x53
#define NV_AT45DB_CMD_MEMORY_PAGE_TO_BUFFER2_TRANSFER           0x55
#define NV_AT45DB_CMD_MEMORY_PAGE_TO_BUFFER1_COMPARE            0x60
#define NV_AT45DB_CMD_MEMORY_PAGE_TO_BUFFER2_COMPARE            0x61
#define NV_AT45DB_CMD_AUTO_PAGE_REWRITE_THROUGH_BUFFER1         0x58
#define NV_AT45DB_CMD_AUTO_PAGE_REWRITE_THROUGH_BUFFER2         0x59
#define NV_AT45DB_CMD_DEEP_POWER_DOWN                           0xB9
#define NV_AT45DB_CMD_RESUME_FROM_POWER_DOWN                    0xAB
#define NV_AT45DB_CMD_STATUS_REGISTER_READ                      0xD7
#define NV_AT45DB_CMD_MANUFACTURER_AND_DEVICE_ID_READ           0x9F

#define NV_AT45DB_STATUSBIT_RDY                                 0x80
#define NV_AT45DB_STATUSBIT_COMP_FAIL                           0x40
#define NV_AT45DB_STATUSBIT_PROTECT                             0x02
#define NV_AT45DB_STATUSBIT_PAGESIZE                            0x01

#define NV_AT45DB_INFO_B1_ATMEL_ID                              0x1F
#define NV_AT45DB_INFO_B2_FAMILY_MASK                           0xE0
#define NV_AT45DB_INFO_B3_FAMILY_ID                             0x20
#define NV_AT45DB_INFO_B2_DENSITY_MASK                          0x1F
#define NV_AT45DB_INFO_B2_DENSITY_1MB                           0x02
#define NV_AT45DB_INFO_B2_DENSITY_2MB                           0x03
#define NV_AT45DB_INFO_B2_DENSITY_4MB                           0x04
#define NV_AT45DB_INFO_B2_DENSITY_8MB                           0x05
#define NV_AT45DB_INFO_B2_DENSITY_16MB                          0x06
#define NV_AT45DB_INFO_B2_DENSITY_32MB                          0x07
#define NV_AT45DB_INFO_B2_DENSITY_64MB                          0x08

#define NV_AT45DB_CMD_LEN                                       1
#define NV_AT45DB_DEV_INFO_LEN                                  4
#define NV_AT45DB_ADDR_LEN                                      3


// -----------------------------------------------------------------------------
//  main
// -----------------------------------------------------------------------------

static void spi_transmit(const uint8_t *src, uint8_t *dst, uint32_t len)
{
    uint8_t dummy;

    while (len--)
    {
        if (src)
        {
        	IODEV_Write(IO_SPI, (void*)src, 1, 0);
            src++;
        }
        else
        {
            dummy = 0xFF;
            IODEV_Write(IO_SPI, &dummy, 1, 0);
        }
        DELAY_MS(2);
        if (dst)
        {
        	IODEV_Read(IO_SPI, dst, 1, 0);
        	dst++;
        }
        else
        {
        	IODEV_Read(IO_SPI, &dummy, 1, 0);
        }
    }
}


/**************************************************************************************************\
\**************************************************************************************************/
static inline uint8_t at45db_get_status()
{
    uint8_t cmd_buf[1+1];

    cmd_buf[0] = 0xD7;
    cmd_buf[1] = 0xFF;

    HAL_GPIO_SetPinLow(CS_PIN);
    spi_transmit(cmd_buf, cmd_buf, sizeof(cmd_buf));
    HAL_GPIO_SetPinHigh(CS_PIN);

    return cmd_buf[1];
}

/**************************************************************************************************\
\**************************************************************************************************/
static inline uint32_t at45db_wait_until_busy(uint32_t max_loops)
{
	HAL_GPIO_SetPinLow(CS_PIN);
    for ( ; (0 == (at45db_get_status() & 0x80)) && max_loops; max_loops--)
    {
        asm volatile ("nop");
        asm volatile ("nop");
        asm volatile ("nop");

    }
    HAL_GPIO_SetPinHigh(CS_PIN);
    return max_loops;
}

/**************************************************************************************************\
\**************************************************************************************************/
static inline void at45db_get_dev_info(uint8_t dev_info[])
{
    static const uint8_t cmd_buf[1] = { 0x9F };

    HAL_GPIO_SetPinLow(CS_PIN);

    spi_transmit(cmd_buf, NULL, sizeof(cmd_buf));
    spi_transmit(NULL, dev_info, 4);

    HAL_GPIO_SetPinHigh(CS_PIN);

}

/**************************************************************************************************\
\**************************************************************************************************/
static inline void at45db_read_data(uint8_t addr[], uint32_t len, uint8_t *dst)
{
    uint8_t cmd_buf[NV_AT45DB_CMD_LEN + NV_AT45DB_ADDR_LEN + 1];

    cmd_buf[0] = NV_AT45DB_CMD_CONT_ARRAY_READ_HIGH_FREQ;
    cmd_buf[1] = addr[0];
    cmd_buf[2] = addr[1];
    cmd_buf[3] = addr[2];
    cmd_buf[4] = 0;

    HAL_GPIO_SetPinLow(CS_PIN);

    spi_transmit(cmd_buf, NULL, sizeof(cmd_buf));
    spi_transmit(NULL, dst, len);

    HAL_GPIO_SetPinHigh(CS_PIN);

}

/**************************************************************************************************\
\**************************************************************************************************/
static inline void at45db_write_page(uint8_t addr[], uint16_t len, const uint8_t *src)
{
    uint8_t cmd_buf[NV_AT45DB_CMD_LEN + NV_AT45DB_ADDR_LEN];

    cmd_buf[0] = NV_AT45DB_CMD_MEMORY_PAGE_PROGRAM_THROUGH_BUFFER1;
    cmd_buf[1] = addr[0];
    cmd_buf[2] = addr[1];
    cmd_buf[3] = addr[2];

    HAL_GPIO_SetPinLow(CS_PIN);

    spi_transmit(cmd_buf, NULL, sizeof(cmd_buf));
    spi_transmit(src, NULL, len);

    HAL_GPIO_SetPinHigh(CS_PIN);
}


int main(void){

	// initialize HAL core
	CORE_Init();
	CORE_EnableInterrupts();
	CC_Init(cc_sam3s);
	// initialize clock controller
	CC_SetClockSource(cc_sam3s, SAM3S_MAIN_CLOCK, SAM3S_XTAL_CLOCK_SOURCE, SAM3S_XTAL_FREQ);
	HAL_GPIO_Init();
	HAL_GPIO_ConfigurePin(TEST_PIN, DEFAULT_CONFIG);
	HAL_GPIO_ConfigurePin(TEST_PIN2, DEFAULT_CONFIG);
	HAL_GPIO_ConfigurePin(CS_PIN, DEFAULT_CONFIG);

    IODEV_Init(IO_DEV);
    IODEV_EnableWrite(IO_DEV);
    IODEV_EnableRead(IO_DEV);

	DIAG_Init();
	DIAG_SetOutputDevice(0, IO_DEV);
    DIAG_ActivateChannel(0);

   IODEV_Init(IO_SPI);
   IODEV_EnableWrite(IO_SPI);
   IODEV_EnableRead(IO_SPI);

   	DIAG0_LogMsg(0,"\nSPI mine : ");
	DIAG0_LogMsg(0,"START");
	DIAG0_LogNL(0);

	HAL_GPIO_SetPinLow(TEST_PIN);
	HAL_GPIO_SetPinHigh(CS_PIN);


	DIAG0_LogMsg(0,"MISO: ");

	DIAG0_LogNL(0);

	uint8_t dev_info[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

	DIAG0_LogUINT(0, at45db_get_status(), 16);

	DIAG0_LogNL(0);

	DIAG0_LogMsg(0,"\nA kod: ");

	at45db_get_dev_info(dev_info);

	DIAG0_LogUINT(0, dev_info[0], 16);
	DIAG0_LogUINT(0, dev_info[1], 16);
	DIAG0_LogUINT(0, dev_info[2], 16);
	DIAG0_LogUINT(0, dev_info[3], 16);
	DIAG0_LogUINT(0, dev_info[4], 16);

	DIAG0_LogNL(0);

	while(1){
		;
	}

	// deinitialize IODevice
	IODEV_Deinit(IO_SPI);
	// deinitialize Diag module
	DIAG_Deinit();
	// deinitialize IODevice
	IODEV_Deinit(IO_DEV);
	// deinitialize CLOCK module
	CC_Deinit(cc_sam3s);
	// deinitialize HAL core
	CORE_Deinit();

	return 0;

} /* main */
