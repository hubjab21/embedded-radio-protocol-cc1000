#================================================================================
#%LICENSE%
#--------------------------------------------------------------------------------
# File:          Makefile
# Author:        Lukasz Krzak
# Purpose:       HALFRED's IO module example
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
TARGET_DEVICE = x86

# --- OUTPUT FILE CONFIGURATION SECTION -----------------------------------------

# Define the output file name
OUTPUT_FILENAME = output.exe

# --- SOURCE DEFINTION SECTION --------------------------------------------------

SRC = ../app/main.c
COMPONENTS = ../../../hal
INC_DIR = .

# --- MAKAO BUILD ENGINE --------------------------------------------------------

# MAKAO path
MAKAO_PATH = ../../../externals/makao
# run MAKAO build engine
include $(MAKAO_PATH)/makao.mak
