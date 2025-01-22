cmake_minimum_required(VERSION 3.22)

set(CMAKE_SYSTEM_NAME Generic)

# Project settings
project(Lab6 C)
set(CMAKE_C_STANDARD 11)

# AVR settings
set(MCU atmega32)
set(MCU2 m32)
set(PROGRAMMER usbasp)

# Compiler and linker settings
add_compile_options(-Wall -Os -mmcu=${MCU})
add_link_options(-mmcu=${MCU} -Wl,--gc-sections)

# Flash flags
set(FLASH_FLAGS "--remove-section=.eeprom --remove-section=.lock --remove-section=.signature")

# Include directories
set(${PROJECT_NAME}_INCLUDE_DIR 
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Components/common/inc"
)

# Source files
file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Libraries
set(MCAL_LIBS 
MDIO
MPORT
)

set(HAL_LIBS
HSEVEN_SEG
)

# Add subdirectories for libraries
foreach(lib ${MCAL_LIBS})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Components/MCAL/${lib} ${CMAKE_BINARY_DIR}/${lib})
endforeach()

foreach(lib ${HAL_LIBS})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Components/HAL/${lib} ${CMAKE_BINARY_DIR}/${lib})
endforeach()

set(CMAKE_C_COMPILER "avr-gcc")

# Add executable
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${HAL_LIBS})

# Add custom rules
add_custom_target(flash
    ALL
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} ${FLASH_FLAGS} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Generating .hex file from .elf file"
)

add_custom_target(binary
    ALL
    DEPENDS flash
    COMMAND ${CMAKE_OBJCOPY} -I ihex ${PROJECT_NAME}.hex -O binary ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMENT "Generating binary file"
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND avr-size --format=berkeley --mcu=${MCU} ${PROJECT_NAME}.elf
    COMMENT "Displaying binary size"
)

add_custom_target(burn
    DEPENDS flash
    COMMAND avrdude -c ${PROGRAMMER} -p ${MCU2} -U flash:w:${PROJECT_NAME}.hex:i -B 1
    COMMENT "Burning .hex file into MCU flash"
)

# # Clean rule
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}.hex")
