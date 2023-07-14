cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

project(MCP23017)

# include_directories(<nameofdir>) to add directories
# target_include_directories(MCP23017 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(../lib)
file(GLOB SOURCES "lib/MCP23017.hpp" )

link_directories(../lib/build)

# add_executable(<nameoftarget> <mainfile> <anyotherfiles>)
add_executable(MCP23017_test ${SOURCES} test.cpp)

target_link_libraries(MCP23017_test
    libMCP23017.a
    pico_stdlib
    hardware_i2c
    )

pico_enable_stdio_usb(MCP23017_test 1)
pico_enable_stdio_uart(MCP23017_test 0)
pico_add_extra_outputs(MCP23017_test)