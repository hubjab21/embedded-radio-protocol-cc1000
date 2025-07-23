#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File: 		 Makefile
# Author:        Michal Kochanowski
# Purpose:       HALFRED tests
# Parser:        GNU Make
# Hardware:      any supported by GNU Make
# Doc:           in-place comments
#--------------------------------------------------------------------------------
# Content:       build script
#--------------------------------------------------------------------------------
# Comments:		 uses part of MAKAO build engine
#================================================================================

include ../../externals/makao/host_os.mak

# List SAM3s examples here
SAM3S_TESTS = ../clk_tests/sam3s/sam3s-ek
SAM3S_TESTS += ../delay_test/sam3s/sam3s-ek
SAM3S_TESTS += ../io_test/sam3s/sam3s-ek/spi
SAM3S_TESTS += ../io_test/sam3s/sam3s-ek/usart
SAM3S_TESTS += ../tim_tests/sam3s/sam3s-ek
SAM3S_TESTS += ../gpio_tests/sam3s/sam3s-ek
SAM3S_TESTS += ../os_tests/freertos/sam3s/sam3s-ek

CLK = ../clk_tests/sam3s/sam3s-ek
DELAY= ../delay_test/sam3s/sam3s-ek
IO_SPI= ../io_test/sam3s/sam3s-ek/spi
IO_USART= ../io_test/sam3s/sam3s-ek/usart
TIM= ../tim_tests/sam3s/sam3s-ek
GPIO= ../gpio_tests/sam3s/sam3s-ek
FREERTOS= ../os_tests/freertos/sam3s/sam3s-ek

SAM3S_TESTS_BIN = $(addsuffix /output.elf, $(SAM3S_TESTS))

SAM3S_CLEAN = $(addsuffix /clean.clean, $(SAM3S_TESTS))
SAM3S_CLK_CLEAN = $(addsuffix /clean.clean, $(CLK))
SAM3S_DELAY_CLEAN = $(addsuffix /clean.clean, $(DELAY))
SAM3S_IO_SPI_CLEAN = $(addsuffix /clean.clean, $(IO_SPI))
SAM3S_IO_USART_CLEAN = $(addsuffix /clean.clean, $(IO_USART))
SAM3S_TIM_CLEAN = $(addsuffix /clean.clean, $(TIM))
SAM3S_GPIO_CLEAN = $(addsuffix /clean.clean, $(GPIO))
SAM3S_FREERTOS_CLEAN = $(addsuffix /clean.clean, $(FREERTOS))

SAM3S_CLK = $(addsuffix /flash.flash, $(CLK))
SAM3S_DELAY = $(addsuffix /flash.flash, $(DELAY))
SAM3S_IO_SPI = $(addsuffix /flash.flash, $(IO_SPI))
SAM3S_IO_USART = $(addsuffix /flash.flash, $(IO_USART))
SAM3S_TIM = $(addsuffix /flash.flash, $(TIM))
SAM3S_GPIO = $(addsuffix /flash.flash, $(GPIO))
SAM3S_FREERTOS = $(addsuffix /flash.flash, $(FREERTOS))


sam3s: $(SAM3S_TESTS_BIN)

sam3s_clean: $(SAM3S_CLEAN) 
clk_clean: $(SAM3S_CLK_CLEAN)
delay_clean: $(SAM3S_DELAY_CLEAN)
io_spi_clean: $(SAM3S_IO_SPI_CLEAN)
io_usart_clean: $(SAM3S_IO_USART_CLEAN)
tim_clean: $(SAM3S_TIM_CLEAN)
gpio_clean: $(SAM3S_GPIO_CLEAN)
freertos_clean: $(SAM3S_FREERTOS_CLEAN)

clk_flash: $(SAM3S_CLK)
delay_flash: $(SAM3S_DELAY)
io_spi_flash: $(SAM3S_IO_SPI)
io_usart_flash: $(SAM3S_IO_USART)
tim_flash: $(SAM3S_TIM)
gpio_flash: $(SAM3S_GPIO)
freertos_flash: $(SAM3S_FREERTOS)

%.elf:
	@echo ------ BUILDING TEST: $(@D) ------
	@$(MAKE) -C $(@D) all VERBOSE=less

%.clean:
	@echo ------ CLEANING TEST: $(@D) ------ 
	@-make -C $(@D) clean VERBOSE=less
	
%.flash:
	@echo ------ FLASHING TEST: $(@D) ------ 
	@-make -C $(@D) flash VERBOSE=less

		
# Listing of phony targets.
.PHONY : all clean flash sam3s