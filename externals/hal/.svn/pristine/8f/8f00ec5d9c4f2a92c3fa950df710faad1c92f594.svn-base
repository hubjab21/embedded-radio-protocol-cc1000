cmake_minimum_required(VERSION 3.21)

add_library(hal_port_universal STATIC universal/hal_port_io_stream.c)
target_include_directories(hal_port_universal PUBLIC universal)

add_library(
  hal_port_avr STATIC
  avr/hal_port.c #
  avr/src/hal_port_core.c
  avr/src/hal_port_io_usart_buf.c
  avr/src/hal_port_io_usart_poll.c
  avr/src/hal_port_io_usart.c
  avr/src/hal_port_tim.c
  os/none/hal_port_os.c)
target_include_directories(hal_port_avr PUBLIC avr/inc os/none)
target_link_libraries(hal_port_avr PUBLIC hal_port_universal hal)
add_library(hal_port ALIAS hal_port_avr)
