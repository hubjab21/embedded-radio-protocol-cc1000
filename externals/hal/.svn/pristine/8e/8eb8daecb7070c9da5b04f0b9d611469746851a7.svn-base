#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Duda
# Purpose:       HALFRED's GPIO test
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
TARGET_DEVICE = stm32f051r8t6

# --- OUTPUT FILE CONFIGURATION SECTION -----------------------------------------

# Define the output file name
OUTPUT_FILENAME = output.elf output.bin output.hex output.lss output.sym output.map

# --- SOURCE DEFINITION SECTION --------------------------------------------------

SRC = ../../../app/spi.c startup.S 
COMPONENTS = ../../../../../hal
INC_DIR = .

# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak
