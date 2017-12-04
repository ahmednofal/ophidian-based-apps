################################################################################
# This is the CMakeLists file for the Dependencies directory.
# 
#   - Fetch dependencies.
#   - Configure dependencies.
#
################################################################################

# Init submodules and fetch dependences from git
execute_process(
COMMAND git submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE submodule_init_exit_code
)

# Add Catch
add_subdirectory(catch)
