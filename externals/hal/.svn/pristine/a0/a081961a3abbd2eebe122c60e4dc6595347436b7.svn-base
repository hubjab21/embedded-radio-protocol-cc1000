cmake_minimum_required(VERSION 3.21)

project(
  hal
  VERSION 1.0.0
  LANGUAGES C)

set(MCU_FAMILY
    "avr"
    CACHE STRING "Name of the MCU family")

message(STATUS "Name of the MCU family: ${MCU_FAMILY}")

add_library(
  hal_avr STATIC
  hal/hal.c
  hal_ports/avr/hal_port.c #
  hal_ports/avr/src/hal_port_core.c
  hal_ports/avr/src/hal_port_io_usart_buf.c
  hal_ports/avr/src/hal_port_io_usart_poll.c
  hal_ports/avr/src/hal_port_io_usart.c
  hal_ports/avr/src/hal_port_tim.c
  hal_ports/os/none/hal_port_os.c
  hal_ports/cli/vt100/hal_port_cli.c)
target_include_directories(hal_avr PUBLIC hal/inc hal_ports/avr/inc
                                          hal_ports/os/none)

add_library(hal ALIAS hal_avr)
