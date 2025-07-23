set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/linker_script.ld)
set(__MCU_NAME__ atmega128)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_LIBRARY_ARCHITECTURE avr)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CPU_FLAGS
    "-ffunction-sections -fdata-sections -gdwarf-2 -mmcu=${__MCU_NAME__}")
set(COMMON_DEBUG_DIAGNOSTIC_FLAGS "-Wall")

set(CMAKE_EXECUTABLE_SUFFIX .elf)

# ########## ASM Options ###########
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_ASM_COMPILER "avr-gcc")
set(CMAKE_ASM_FLAGS "-x assembler-with-cpp ${CPU_FLAGS}")
set(CMAKE_ASM_FLAGS_DEBUG "-Os -g3 ${COMMON_DEBUG_DIAGNOSTIC_FLAGS}")
set(CMAKE_ASM_FLAGS_RELEASE "-Os -Wall")

# ########## C Options ###########
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_C_FLAGS "${CPU_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG
    "-Os -g3 ${COMMON_DEBUG_DIAGNOSTIC_FLAGS} -Wimplicit-fallthrough=3 -Wwrite-strings -Wvla"
)
set(CMAKE_C_FLAGS_RELEASE "-Os -Wall")

# ########## C++ Options ###########
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_CXX_FLAGS "${CPU_FLAGS} -fconcepts")
set(CMAKE_CXX_FLAGS_DEBUG
    "-Os -g3 ${COMMON_DEBUG_DIAGNOSTIC_FLAGS} -Wimplicit-fallthrough=5 -Wdelete-non-virtual-dtor -Woverloaded-virtual -Wold-style-cast "
)
set(CMAKE_CXX_FLAGS_RELEASE "-Os -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")

add_compile_options(-ffunction-sections -fdata-sections -fno-strict-aliasing
                    -fshort-enums -Wno-packed-bitfield-compat -Wno-psabi)

add_compile_definitions(F_CPU=7372800 __AVR_ATmega128__)
