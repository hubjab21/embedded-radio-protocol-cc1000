#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File: 		 Makefile
# Author:        Łukasz Krzak, Michal Kochanowski
# Purpose:       HALFRED examples
# Parser:        GNU Make
# Hardware:      any supported by GNU Make
# Doc:           in-place comments
#--------------------------------------------------------------------------------
# Content:       build script
#--------------------------------------------------------------------------------
# Comments:		 uses part of MAKAO build engine
#================================================================================

include ../externals/makao/host_os.mak

# List LINUX examples here
LINUX_EXAMPLES =  diag_example/linux 
LINUX_EXAMPLES += gpio_example/linux
LINUX_EXAMPLES += io_example/linux
LINUX_EXAMPLES += os_example/linux
LINUX_EXAMPLES += heap_example/linux

# List WINDOWS examples here
WINDOWS_EXAMPLES = diag_example/windows
WINDOWS_EXAMPLES += gpio_example/windows
WINDOWS_EXAMPLES += io_example/windows
#WINDOWS_EXAMPLES += os_example/windows
#WINDOWS_EXAMPLES += heap_example/windows

# List STM32 examples here
STM32_EXAMPLES = diag_example/stm32
STM32_EXAMPLES += gpio_example/stm32
STM32_EXAMPLES += io_example/stm32
STM32_EXAMPLES += heap_example/stm32
STM32_EXAMPLES += nv_example/stm32_at45db
STM32_EXAMPLES += tim_example/stm32
STM32_EXAMPLES += usb_example/stm32
STM32_EXAMPLES += os_example/stm32_freertos
#STM32_EXAMPLES += os_example/stm32_ucos2
STM32_EXAMPLES += os_integration_example/stm32

# List AVR examples here
AVR_EXAMPLES += gpio_example/avr
AVR_EXAMPLES += io_example/avr
AVR_EXAMPLES += tim_example/avr
AVR_EXAMPLES += os_example/avr_freertos

# List SAM3s examples here
SAM3S_EXAMPLES = clk_example/sam3s
SAM3S_EXAMPLES += diag_example/sam3s
SAM3S_EXAMPLES += gpio_example/sam3s
SAM3S_EXAMPLES += io_example/sam3s
SAM3S_EXAMPLES += spi_example/sam3s
SAM3S_EXAMPLES += tim_example/sam3s
SAM3S_EXAMPLES += os_example/sam3s_freertos

# List stm32f4 examples here
STM32F4_EXAMPLES = clk_example/stm32f4
STM32F4_EXAMPLES += diag_example/stm32f4
STM32F4_EXAMPLES += gpio_example/stm32f4
STM32F4_EXAMPLES += io_example/stm32f4
STM32F4_EXAMPLES += spi_example/stm32f4
STM32F4_EXAMPLES += tim_example/stm32f4

# All examples:
ALL_EXAMPLES = $(LINUX_EXAMPLES) $(WINDOWS_EXAMPLES) $(STM32_EXAMPLES) $(AVR_EXAMPLES) $(SAM3S_EXAMPLES) $(STM32F4_EXAMPLES)


ifeq ($(HAL_HOST_OS),Windows_NT)
all_deps=windows stm32
else
all_deps=linux stm32
endif

LINUX_EXAMPLES_BIN = $(addsuffix /output.elf, $(LINUX_EXAMPLES))
WINDOWS_EXAMPLES_BIN = $(addsuffix /output.elf, $(WINDOWS_EXAMPLES))
STM32_EXAMPLES_BIN = $(addsuffix /output.elf, $(STM32_EXAMPLES))
AVR_EXAMPLES_BIN = $(addsuffix /output.elf, $(AVR_EXAMPLES))
SAM3S_EXAMPLES_BIN = $(addsuffix /output.elf, $(SAM3S_EXAMPLES))
STM32F4_EXAMPLES_BIN = $(addsuffix /output.elf, $(STM32F4_EXAMPLES))

ALL_CLEAN = $(addsuffix /clean.clean, $(ALL_EXAMPLES))
SAM3S_CLEAN = $(addsuffix /clean.clean, $(SAM3S_EXAMPLES))
STM32F4_CLEAN = $(addsuffix /clean.clean, $(STM32F4_EXAMPLES))
AVR_CLEAN = $(addsuffix /clean.clean, $(AVR_EXAMPLES))
all: $(all_deps)

linux: $(LINUX_EXAMPLES_BIN)
windows: $(WINDOWS_EXAMPLES_BIN)
stm32: $(STM32_EXAMPLES_BIN)
avr: $(AVR_EXAMPLES_BIN)
sam3s: $(SAM3S_EXAMPLES_BIN)
stm32f4: $(STM32F4_EXAMPLES_BIN)

%.elf:
	@echo ------ BUILDING EXAMPLE: $(@D) ------
	@$(MAKE) -C $(@D) all VERBOSE=less

%.clean:
	@echo ------ CLEANING EXAMPLE: $(@D) ------ 
	@-make -C $(@D) clean VERBOSE=less

clean: $(ALL_CLEAN)
sam3s_clean: $(SAM3S_CLEAN) 
stm32f4_clean: $(STM32F4_CLEAN)
avr_clean: $(AVR_CLEAN)
		
# Listing of phony targets.
.PHONY : all clean linux windows stm32 avr sam3s stm32f4