#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Krzak, Michal Kochanowski
# Purpose:       HALFRED's OS module example
# Parser:        GNU Make
# Hardware:      any supported by GNU Make
# Doc:           in-place comments
#--------------------------------------------------------------------------------
# Content:       build script
#--------------------------------------------------------------------------------
# Comments:		 uses MAKAO build engine
#================================================================================


# --- TARGET CONFIGURATION SECTION ----------------------------------------------

# Define the target device:
TARGET_DEVICE = at91sam3s4c

# --- OUTPUT FILE CONFIGURATION SECTION -----------------------------------------

# Define the output file name
OUTPUT_FILENAME = output.elf output.bin output.hex output.lss output.sym output.map

# --- SOURCE DEFINTION SECTION --------------------------------------------------

SRC = ../app/main.c startup.S
COMPONENTS = ../../../hal

# Additional component is specified to include RTOS files 
COMPONENTS += ../../../externals/freertos

INC_DIR = .

# The following definition instructs HAL component to include port to
# FreeRTOS 
HAL_RTOS =freertos

# --- PREPROCESSOR DEFINTIONS SECTION -------------------------------------------

DEF = F_CPU=4000000

# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak
