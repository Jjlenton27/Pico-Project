cmake_minimum_required(VERSION 3.13)

set(ROOT /home/ubu/Documents/Pico-Team-Tracker/)

set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)

project(Pico-Team-Tracker C CXX ASM)
pico_sdk_init()

#include_directories(${ROOT}/Display)
#add_subdirectory(${ROOT}/Display)

add_executable(${CMAKE_PROJECT_NAME}
	main.cpp
	define.h

	#${PROJECT_SOURCE_DIR}/Display/screen.cpp
	#${PROJECT_SOURCE_DIR}/Display/screen.h
)


target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE Display)

target_link_libraries(${CMAKE_PROJECT_NAME}
	pico_stdlib
	pico_cyw43_arch_none
	hardware_spi
)

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
