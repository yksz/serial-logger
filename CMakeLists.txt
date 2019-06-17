cmake_minimum_required(VERSION 2.8.7)
project(serialog CXX)

set(CMAKE_C_FLAGS "-Wall -std=c89")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

option(build_tests "Build all of own tests" OFF)
option(build_examples "Build example programs" OFF)

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
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} serialport logger)

### Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

### Test
if(build_tests)
    enable_testing()
    add_subdirectory(test)
endif()

### Example
if(build_examples)
    add_subdirectory(example)
endif()
