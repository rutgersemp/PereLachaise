cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pere_lachaise)

pico_sdk_init()

add_executable(main
    main.cpp
)

pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(
    main 
    pico_stdlib 
    hardware_pwm 
    hardware_clocks
    hardware_uart
    hardware_irq
)