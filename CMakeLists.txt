cmake_minimum_required(VERSION 2.6)

project(fixie)

set(FIXIE_VERSION 0.0.0)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG BUILD_DEBUG=1)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELEASE BUILD_RELEASE=1)

include_directories(include)

add_subdirectory(src)
add_subdirectory(samples)
