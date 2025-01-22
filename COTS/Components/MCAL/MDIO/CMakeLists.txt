# set minimum required version of cmake to avoid errors
cmake_minimum_required(VERSION 3.22)

# project name + defining used languages
project(MDIO C) 

# set the compiler to avr-gcc
set(CMAKE_C_COMPILER "avr-gcc")

# set the standard to C11
set(CMAKE_C_STANDARD 11)

# set path to include directories
set(${PROJECT_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inc" "${CMAKE_CURRENT_SOURCE_DIR}/../../common/inc")

# set path to source files
file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# create a static library
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})

# add include directories to target (Library)
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR})