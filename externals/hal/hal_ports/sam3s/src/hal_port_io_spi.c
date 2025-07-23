/*
================================================================================
%LICENSE%
--------------------------------------------------------------------------------
 File:          hal_port_io_spi.c
 Author:        Michał Kochanowski
 Purpose:       HALFRED's port for ATMEL SAM3S microcontrollers
 Compiler:      %COMPILER%
 Hardware:      ATMEL SAM3S
 Doc:           doxygen
--------------------------------------------------------------------------------
 Content:       IO module port for Atmel SAM3S (SPI)
--------------------------------------------------------------------------------
 Comments:      this file only maps io_SPIx pointer to an actual devices
                handling particular modes of operation
================================================================================
*/
#include "hal_config.h"
#include "hal_port_io_spi.h"

#if defined HALPORT_USE_SPI1 && (HALPORT_USE_SPI1 != 0)

#if defined HALPORT_SPI1_MODE

#if HALPORT_SPI1_MODE == HALPORT_SPI_MODE_BUFFERED
// SPI1 by default works in buffered mode
#if defined HALPORT_SPI1_ENABLE_BUFFERED_MODE
extern struct SPI_IODeviceDesc io_spi1_buf;
SPI_IODevice io_spi1 = &io_spi1_buf;
#else
#error Conflicting definitions:
#error HALPORT_SPI1_MODE and HALPORT_SPI1_ENABLE_BUFFERED_MODE
#error Buffered mode not enabled for SPI1. Check your hal_config.h
#endif
#elif HALPORT_SPI1_MODE == HALPORT_SPI_MODE_POLLING
// SPI1 by default works in polling mode
#if defined HALPORT_SPI1_ENABLE_POLLING_MODE
extern struct SPI_IODeviceDesc io_spi1_poll;
SPI_IODevice io_spi1 = &io_spi1_poll;
#else
#error Conflicting definitions:
#error HALPORT_SPI1_MODE and HALPORT_SPI1_ENABLE_POLLING_MODE
#error Polling mode not enabled for SPI1. Check your hal_config.h
#endif
#else
#error Wrong HALPORT_SPI1_MODE definition! Possible values:
#error HALPORT_SPI_MODE_POLLING, HALPORT_SPI_MODE_BUFFERED
#error Check your hal_config.h!
#endif

#else
#error Missing HALPORT_SPI1_MODE definition! Check your hal_config.h
#endif

#endif // HALPORT_SPI1_MODE


#if defined HALPORT_USE_SPIS1 && (HALPORT_USE_SPIS1 != 0)

#if defined HALPORT_SPIS1_MODE

#if HALPORT_SPIS1_MODE == HALPORT_SPI_MODE_SOFTWARE

#if defined HALPORT_SPIS1_ENABLE_SOFT_MODE
extern struct SPI_IODeviceDesc io_spiS1_soft;
SPI_IODevice io_spiS1 = &io_spiS1_soft;
#else
#error Conflicting definitions:
#error HALPORT_SPIS1_MODE and HALPORT_SPIS1_ENABLE_SOFT_MODE
#error Software mode not enabled for SPIS1. Check your hal_config.h
#endif

#else
#error Missing HALPORT_SPIS1_MODE definition or mismatch! Check your hal_config.h
#endif

#endif
#endif // HALPORT_SPIS1_MODE
