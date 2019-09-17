cmake_minimum_required(VERSION 2.8.7)
project(serialog C)

set(CMAKE_C_FLAGS "-Wall -std=c99")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-g")

### Build Libraries
add_subdirectory(vendor/serialport)
add_subdirectory(vendor/c-logger)

### Build a Executable File
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor/serialport/src
    ${PROJECT_SOURCE_DIR}/vendor/c-logger/src
    ${PROJECT_SOURCE_DIR}/vendor/getopty
)
file(GLOB source_files
    ${PROJECT_SOURCE_DIR}/src/*.c
)
add_executable(${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} serialport_static logger_static)

### Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
