cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(Project1 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Project1
  Project1.c
)
add_library(bme280 OBJECT
  bme280.c
)
add_library(bme280_selftest OBJECT
  bme280_selftest.c
)


pico_enable_stdio_uart(Project1 1)
pico_enable_stdio_usb(Project1 0)

pico_add_extra_outputs(Project1)



target_link_libraries(Project1 pico_stdlib hardware_i2c)
target_link_libraries(bme280 bme280.h)
target_link_libraries(bme280_selftest bme280_selftest.h)