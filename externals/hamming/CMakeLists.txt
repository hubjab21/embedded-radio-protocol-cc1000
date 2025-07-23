cmake_minimum_required(VERSION 3.21)

project(
  hamming
  VERSION 1.0.0
  LANGUAGES C)

add_library(hamming STATIC hamming.c)
target_include_directories(hamming PUBLIC .)
