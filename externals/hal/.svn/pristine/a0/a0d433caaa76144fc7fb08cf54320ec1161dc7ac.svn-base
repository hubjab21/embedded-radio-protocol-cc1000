#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Krzak
# Purpose:       HALFRED's DIAG module example
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

INC_DIR = .

# --- PREPROCESSOR DEFINTIONS SECTION -------------------------------------------

# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak
