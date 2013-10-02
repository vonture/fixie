cmake_minimum_required(VERSION 2.8.8)
project(glfw_builder C CXX)
include(ExternalProject)

ExternalProject_Add(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
# Disable install step
    INSTALL_COMMAND ""
)

set_target_properties(glfw PROPERTIES
    FOLDER samples/ext
)

# Specify include dir
ExternalProject_Get_Property(glfw source_dir)
set(GLFW_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

# Specify MainTest's link libraries
ExternalProject_Get_Property(glfw binary_dir)
set(GLFW_LIBS_DIRS ${binary_dir} PARENT_SCOPE)
