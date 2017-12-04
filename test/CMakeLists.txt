################################################################################
# This is the CMakeLists file for the Ophidian project Test binary. 
#
# Its main goals are:
#   - Add test target.
#   - Link test target.
#   - Prepare test input environment.
################################################################################

# Recursively fetch test code
file(GLOB_RECURSE tests_SRC  
    "*.cpp"
)

# Add test target
add_executable(ophidian_project_tests ${tests_SRC})

# Link test target dependencies
target_link_libraries(ophidian_project_tests PUBLIC 
    Catch 
)
