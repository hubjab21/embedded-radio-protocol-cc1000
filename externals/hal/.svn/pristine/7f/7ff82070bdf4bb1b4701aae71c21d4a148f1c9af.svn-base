#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Duda
# Purpose:       HALFRED's GPIO module example
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
TARGET_DEVICE = stm32f407

# --- OUTPUT FILE CONFIGURATION SECTION -----------------------------------------

# Define the output file name
OUTPUT_FILENAME = output.elf output.bin output.hex output.lss output.sym

# --- SOURCE DEFINITION SECTION --------------------------------------------------

SRC = main.c ../../../../hal_ports/universal/hal_port_ds2431.c startup.S
COMPONENTS = ../../../../hal
INC_DIR = . ../../../../hal_ports/universal/

# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak
