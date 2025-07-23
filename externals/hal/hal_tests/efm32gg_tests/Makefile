#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File: 		 Makefile
# Author:        Michal Kochanowski, Lukasz Duda
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
efm32gg_tests = ../clk_tests/efm32gg/stk3700
efm32gg_tests += ../delay_test/efm32gg/stk3700
efm32gg_tests += ../io_test/efm32gg/stk3700/spi
efm32gg_tests += ../io_test/efm32gg/stk3700/usart
efm32gg_tests += ../tim_tests/efm32gg/stk3700
efm32gg_tests += ../gpio_tests/efm32gg/stk3700
efm32gg_tests += ../os_tests/freertos/efm32gg/stk3700

CLK = ../clk_tests/efm32gg/stk3700
DELAY= ../delay_test/efm32gg/stk3700
IO_SPI= ../io_test/efm32gg/stk3700/spi
IO_USART= ../io_test/efm32gg/stk3700/usart
TIM= ../tim_tests/efm32gg/stk3700
GPIO= ../gpio_tests/efm32gg/stk3700
FREERTOS= ../os_tests/freertos/efm32gg/stk3700

efm32gg_tests_BIN = $(addsuffix /output.elf, $(efm32gg_tests))

EFM32GG_CLEAN = $(addsuffix /clean.clean, $(efm32gg_tests))
EFM32GG_CLK_CLEAN = $(addsuffix /clean.clean, $(CLK))
EFM32GG_DELAY_CLEAN = $(addsuffix /clean.clean, $(DELAY))
EFM32GG_IO_SPI_CLEAN = $(addsuffix /clean.clean, $(IO_SPI))
EFM32GG_IO_USART_CLEAN = $(addsuffix /clean.clean, $(IO_USART))
EFM32GG_TIM_CLEAN = $(addsuffix /clean.clean, $(TIM))
EFM32GG_GPIO_CLEAN = $(addsuffix /clean.clean, $(GPIO))
EFM32GG_FREERTOS_CLEAN = $(addsuffix /clean.clean, $(FREERTOS))

EFM32GG_CLK = $(addsuffix /flash.flash, $(CLK))
EFM32GG_DELAY = $(addsuffix /flash.flash, $(DELAY))
EFM32GG_IO_SPI = $(addsuffix /flash.flash, $(IO_SPI))
EFM32GG_IO_USART = $(addsuffix /flash.flash, $(IO_USART))
EFM32GG_TIM = $(addsuffix /flash.flash, $(TIM))
EFM32GG_GPIO = $(addsuffix /flash.flash, $(GPIO))
EFM32GG_FREERTOS = $(addsuffix /flash.flash, $(FREERTOS))


efm32gg: $(efm32gg_tests_BIN)

efm32gg_clean: $(EFM32GG_CLEAN) 
clk_clean: $(EFM32GG_CLK_CLEAN)
delay_clean: $(EFM32GG_DELAY_CLEAN)
io_spi_clean: $(EFM32GG_IO_SPI_CLEAN)
io_usart_clean: $(EFM32GG_IO_USART_CLEAN)
tim_clean: $(EFM32GG_TIM_CLEAN)
gpio_clean: $(EFM32GG_GPIO_CLEAN)
freertos_clean: $(EFM32GG_FREERTOS_CLEAN)

clk_flash: $(EFM32GG_CLK)
delay_flash: $(EFM32GG_DELAY)
io_spi_flash: $(EFM32GG_IO_SPI)
io_usart_flash: $(EFM32GG_IO_USART)
tim_flash: $(EFM32GG_TIM)
gpio_flash: $(EFM32GG_GPIO)
freertos_flash: $(EFM32GG_FREERTOS)

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
.PHONY : all clean flash efm32gg