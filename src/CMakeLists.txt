cmake_minimum_required(VERSION 3.21)

list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/externals)

add_executable(cc1000_bsks main.c cli_cmd_proc.c cc1000.c)
target_include_directories(cc1000_bsks PRIVATE include conf/cc1000_433500)
target_compile_options(
  cc1000_bsks
  PRIVATE -Wextra
          -Wformat=2
          -Wformat-overflow=2
          -Wformat-security
          -Wformat-signedness
          -Winit-self
          -Wcast-align
          -Wnull-dereference
          -Wduplicated-cond
          -Wnull-dereference
          -Wlogical-op
          -Wdouble-promotion
          -Wunused-parameter
          -Wconversion
          -Wpedantic)

include_directories(conf/hal_conf)
find_package(hal)
target_link_libraries(cc1000_bsks PRIVATE hal)

add_custom_command(
  TARGET cc1000_bsks
  POST_BUILD
  BYPRODUCTS cc1000_bsks.bin
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:cc1000_bsks> cc1000_bsks.bin
  COMMENT "Generating binary file cc1000_bsks.bin"
  VERBATIM)

add_custom_command(
  TARGET cc1000_bsks
  POST_BUILD
  COMMAND bootfile.exe -m atmega128_8 -l 0 -d 123456beef -s crc32 -i
          cc1000_bsks.bin -o cc1000_bsks.rbt
  VERBATIM)
