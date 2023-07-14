message("#### BUILDING MCP23017 LIB ####")
cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

project(MCP23017)

add_library(MCP23017 STATIC MCP23017.cpp)

target_link_libraries(MCP23017 pico_stdlib hardware_i2c)
