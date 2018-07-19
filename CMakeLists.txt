################################################################################
# This is the main CMakeLists file for creation a Ophidian project. 
#
# Its main goals are:
#   - set up global variables.
#   - set up the global include directories
#   - add subdirectories
################################################################################

################################################################################
# Set up global variables
################################################################################

# Set up minimal cmake version
cmake_minimum_required(VERSION 3.5.2)

# Here you need to set your project name
project("OPHIDIAN_PROJECT_TEMPLATE")

# Subproject uses c++ 14
set(CMAKE_CXX_STANDARD 14)

################################################################################
# Handle requirements
################################################################################

# Set Cmake module path for find_package
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set Cmake prefix path for buildind with local dependencies
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

find_package(ophidian 0.1 REQUIRED CONFIG)

find_package(Boost REQUIRED)

find_package(Lemon REQUIRED)

find_package(units REQUIRED CONFIG)

find_package(DEF REQUIRED)

find_package(LEF REQUIRED)

find_package(Flute REQUIRED)

find_package(verilog-parser REQUIRED)

################################################################################
# Project logic 
################################################################################

# First add dependencies directory
add_subdirectory(3rdparty)

# Then add project test subdirectory
add_subdirectory(test)

# our utils
add_subdirectory(util)

# our placer subdirectory
add_subdirectory(placer)

add_executable(hello_world
    main.cpp
)

add_executable(placer_test
    test.cpp
)

target_link_libraries(placer_test
    PUBLIC ophidian::ophidian_design
    myPlacer
)

target_link_libraries(hello_world
    PUBLIC ophidian::ophidian_design
)
