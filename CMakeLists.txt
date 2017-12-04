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
cmake_minimum_required(VERSION 3.2.2)

# Here you need to set your project name
project("OPHIDIAN_PROJECT_TEMPLATE")

# Subproject uses c++ 14
set(CMAKE_CXX_STANDARD 14)

################################################################################
# Handle requirements
################################################################################

find_package(ophidian REQUIRED CONFIG)

################################################################################
# Project logic 
################################################################################

# First add dependencies directory
add_subdirectory(3rdparty)

# Then add project source subdirectory
add_subdirectory(src)

# Then add project test subdirectory
add_subdirectory(test)
