#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Duda, Michal Kochanowski
# Purpose:       HALFRED's Energymicro EFM32
# Parser:        GNU Make
# Hardware:      Energymicro EFM32
# Doc:           in-place comments
#--------------------------------------------------------------------------------
# Content:       build script
#--------------------------------------------------------------------------------
# Comments:		 uses MAKAO build engine
#================================================================================

# --- TARGET CONFIGURATION SECTION ----------------------------------------------

# Define the target device:
TARGET_DEVICE = efm32gg990f1024

# --- OUTPUT FILE CONFIGURATION SECTION -----------------------------------------

# Define the output file name
OUTPUT_FILENAME = output.elf output.bin output.hex output.lss output.sym output.map


SRC = ../app/main.c startup.S
COMPONENTS = ../../../hal

# Additional component is specified to include RTOS files 
COMPONENTS += ../../../externals/freertos

INC_DIR = .

# The following definition instructs HAL component to include port to
# FreeRTOS 
HAL_RTOS =freertos

# --- PREPROCESSOR DEFINTIONS SECTION -------------------------------------------

DEF = F_CPU=14000000


# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak

