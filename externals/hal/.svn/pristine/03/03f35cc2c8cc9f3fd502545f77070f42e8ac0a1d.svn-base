#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File: 		 Makefile
# Author:        Michal Kochanowski,Lukasz Duda
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
efm32gg_examples = ../clk_example/efm32gg
efm32gg_examples += ../diag_example/efm32gg
efm32gg_examples += ../io_example/efm32gg
efm32gg_examples += ../os_example/efm32gg_freertos
efm32gg_examples += ../tim_example/efm32gg
efm32gg_examples += ../gpio_example/efm32gg
efm32gg_examples += ../spi_example/efm32gg

CLK = ../clk_example/efm32gg
DIAG= ../diag_example/efm32gg
IO_SPI= ../spi_example/efm32gg
IO_USART= ../io_example/efm32gg
TIM= ../tim_example/efm32gg
GPIO= ../gpio_example/efm32gg
OS= ../os_example/efm32gg_freertos

EFM32GG_TESTS_BIN = $(addsuffix /output.elf, $(efm32gg_examples))

EFM32GG_CLEAN = $(addsuffix /clean.clean, $(efm32gg_examples))
EFM32GG_CLK_CLEAN = $(addsuffix /clean.clean, $(CLK))
EFM32GG_DIAG_CLEAN = $(addsuffix /clean.clean, $(DIAG))
EFM32GG_IO_SPI_CLEAN = $(addsuffix /clean.clean, $(IO_SPI))
EFM32GG_IO_USART_CLEAN = $(addsuffix /clean.clean, $(IO_USART))
EFM32GG_TIM_CLEAN = $(addsuffix /clean.clean, $(TIM))
EFM32GG_GPIO_CLEAN = $(addsuffix /clean.clean, $(GPIO))
EFM32GG_OS_CLEAN = $(addsuffix /clean.clean, $(OS))

EFM32GG_CLK_FLASH = $(addsuffix /flash.flash, $(CLK))
EFM32GG_DIAG_FLASH = $(addsuffix /flash.flash, $(DIAG))
EFM32GG_IO_SPI_FLASH = $(addsuffix /flash.flash, $(IO_SPI))
EFM32GG_IO_USART_FLASH = $(addsuffix /flash.flash, $(IO_USART))
EFM32GG_TIM_FLASH = $(addsuffix /flash.flash, $(TIM))
EFM32GG_GPIO_FLASH = $(addsuffix /flash.flash, $(GPIO))
EFM32GG_OS_FLASH = $(addsuffix /flash.flash, $(OS))

efm32gg_clean: $(EFM32GG_CLEAN) 
clk_clean: $(EFM32GG_CLK_CLEAN)
diag_clean: $(EFM32GG_DIAG_CLEAN)
io_spi_clean: $(EFM32GG_IO_SPI_CLEAN)
io_usart_clean: $(EFM32GG_IO_USART_CLEAN)
tim_clean: $(EFM32GG_TIM_CLEAN)
gpio_clean: $(EFM32GG_GPIO_CLEAN)
os_clean: $(EFM32GG_OS_CLEAN)

efm32gg: $(EFM32GG_TESTS_BIN)
clk_flash: $(EFM32GG_CLK_FLASH)
diag_flash: $(EFM32GG_DIAG_FLASH)
io_spi_flash: $(EFM32GG_IO_SPI_FLASH)
io_usart_flash: $(EFM32GG_IO_USART_FLASH)
tim_flash: $(EFM32GG_TIM_FLASH)
gpio_flash: $(EFM32GG_GPIO_FLASH)
os_flash: $(EFM32GG_OS_FLASH)

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