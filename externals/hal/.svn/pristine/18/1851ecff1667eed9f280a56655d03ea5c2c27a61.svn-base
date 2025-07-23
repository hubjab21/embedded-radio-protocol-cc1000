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
SAM3S_EXAMPLES = ../clk_example/sam3s
SAM3S_EXAMPLES += ../diag_example/sam3s
SAM3S_EXAMPLES += ../io_example/sam3s
SAM3S_EXAMPLES += ../os_example/sam3s_freertos
SAM3S_EXAMPLES += ../tim_example/sam3s
SAM3S_EXAMPLES += ../gpio_example/sam3s
SAM3S_EXAMPLES += ../spi_example/sam3s

CLK = ../clk_example/sam3s
DIAG= ../diag_example/sam3s
IO_SPI= ../spi_example/sam3s
IO_USART= ../io_example/sam3s
TIM= ../tim_example/sam3s
GPIO= ../gpio_example/sam3s
OS= ../os_example/sam3s_freertos

SAM3S_TESTS_BIN = $(addsuffix /output.elf, $(SAM3S_EXAMPLES))

SAM3S_CLEAN = $(addsuffix /clean.clean, $(SAM3S_EXAMPLES))
SAM3S_CLK_CLEAN = $(addsuffix /clean.clean, $(CLK))
SAM3S_DIAG_CLEAN = $(addsuffix /clean.clean, $(DIAG))
SAM3S_IO_SPI_CLEAN = $(addsuffix /clean.clean, $(IO_SPI))
SAM3S_IO_USART_CLEAN = $(addsuffix /clean.clean, $(IO_USART))
SAM3S_TIM_CLEAN = $(addsuffix /clean.clean, $(TIM))
SAM3S_GPIO_CLEAN = $(addsuffix /clean.clean, $(GPIO))
SAM3S_OS_CLEAN = $(addsuffix /clean.clean, $(OS))

SAM3S_CLK_FLASH = $(addsuffix /flash.flash, $(CLK))
SAM3S_DIAG_FLASH = $(addsuffix /flash.flash, $(DIAG))
SAM3S_IO_SPI_FLASH = $(addsuffix /flash.flash, $(IO_SPI))
SAM3S_IO_USART_FLASH = $(addsuffix /flash.flash, $(IO_USART))
SAM3S_TIM_FLASH = $(addsuffix /flash.flash, $(TIM))
SAM3S_GPIO_FLASH = $(addsuffix /flash.flash, $(GPIO))
SAM3S_OS_FLASH = $(addsuffix /flash.flash, $(OS))

sam3s_clean: $(SAM3S_CLEAN) 
clk_clean: $(SAM3S_CLK_CLEAN)
diag_clean: $(SAM3S_DIAG_CLEAN)
io_spi_clean: $(SAM3S_IO_SPI_CLEAN)
io_usart_clean: $(SAM3S_IO_USART_CLEAN)
tim_clean: $(SAM3S_TIM_CLEAN)
gpio_clean: $(SAM3S_GPIO_CLEAN)
os_clean: $(SAM3S_OS_CLEAN)

sam3s: $(SAM3S_TESTS_BIN)
clk_flash: $(SAM3S_CLK_FLASH)
diag_flash: $(SAM3S_DIAG_FLASH)
io_spi_flash: $(SAM3S_IO_SPI_FLASH)
io_usart_flash: $(SAM3S_IO_USART_FLASH)
tim_flash: $(SAM3S_TIM_FLASH)
gpio_flash: $(SAM3S_GPIO_FLASH)
os_flash: $(SAM3S_OS_FLASH)

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