#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File: 		 Makefile
# Author:        Michal Kochanowski, Łukasz Duda
# Purpose:       HALFRED tests
# Parser:        GNU Make
# Hardware:      any supported by GNU Make
# Doc:           in-place comments
#--------------------------------------------------------------------------------
# Content:       build script
#--------------------------------------------------------------------------------
# Comments:		 uses part of MAKAO build engine
#================================================================================

include ../externals/makao/host_os.mak

# List SAM3s examples here
SAM3S_TESTS = clk_tests/sam3s/sam3s-ek
SAM3S_TESTS += delay_test/sam3s/sam3s-ek
SAM3S_TESTS += io_test/sam3s/sam3s-ek/spi
SAM3S_TESTS += io_test/sam3s/sam3s-ek/usart
SAM3S_TESTS += tim_tests/sam3s/sam3s-ek
SAM3S_TESTS += gpio_tests/sam3s/sam3s-ek
SAM3S_TESTS += os_tests/freertos/sam3s/sam3s-ek

# List stm32f4 examples here
STM32F4_TESTS = clk_tests/stm32f4/STM32f4_discovery
STM32F4_TESTS += delay_test/stm32f4/STM32f4_discovery
STM32F4_TESTS += io_test/stm32f4/STM32f4_discovery/spi
STM32F4_TESTS += io_test/stm32f4/STM32f4_discovery/usart
STM32F4_TESTS += tim_tests/stm32f4/STM32f4_discovery
STM32F4_TESTS += gpio_tests/stm32f4/STM32f4_discovery

# List stm32f0 examples here
STM32F0_TESTS = clk_tests/stm32f0/STM32f0_discovery
STM32F0_TESTS += delay_test/stm32f0/STM32f0_discovery
STM32F0_TESTS += io_test/stm32f0/STM32f0_discovery/spi
STM32F0_TESTS += io_test/stm32f0/STM32f0_discovery/usart
STM32F0_TESTS += tim_tests/stm32f0/STM32f0_discovery
STM32F0_TESTS += gpio_tests/stm32f0/STM32f0_discovery


# All tests:
ALL_TESTS = $(STM32F0_TESTS) $(STM32F4_TESTS) $(SAM3S_TESTS)
STM32F4_TESTS_BIN = $(addsuffix /output.elf, $(STM32F4_TESTS))
STM32F0_TESTS_BIN = $(addsuffix /output.elf, $(STM32F0_TESTS))

ALL_CLEAN = $(addsuffix /clean.clean, $(ALL_TESTS))
STM32F4_CLEAN = $(addsuffix /clean.clean, $(STM32F4_TESTS))
STM32F0_CLEAN = $(addsuffix /clean.clean, $(STM32F0_TESTS))

all: $(ALL_TESTS)
stm32f4: $(STM32F4_TESTS_BIN)
stm32f0: $(STM32F0_TESTS_BIN)

%.elf:
	@echo ------ BUILDING EXAMPLE: $(@D) ------
	@$(MAKE) -C $(@D) all VERBOSE=less

%.clean:
	@echo ------ CLEANING EXAMPLE: $(@D) ------ 
	@-make -C $(@D) clean VERBOSE=less

clean: $(ALL_CLEAN) 
stm32f4_clean: $(STM32F4_CLEAN)
stm32f0_clean: $(STM32F0_CLEAN)
		
# Listing of phony targets.
.PHONY : all clean  stm32f4 stm32f0