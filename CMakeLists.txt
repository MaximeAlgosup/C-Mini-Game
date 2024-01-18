# How to use with mingw: (Windows)
#   cmake -S . -B Build -G "MinGW Makefiles"
#   cd Build
#   mingw32-make

# How to use with msys2: (Windows)
#   cmake -S . -B Build -G "MSYS Makefiles"
#   cd Build
#   make

cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")

project(
  tests
  VERSION 1.0
  LANGUAGES C
)

find_package(Threads REQUIRED)

add_executable(game
    game.c
)

target_compile_options(game
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(game
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
