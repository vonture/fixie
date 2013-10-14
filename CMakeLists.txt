cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME_STR fixie)
project(${PROJECT_NAME_STR})

option(USE_SOLUTION_FOLDERS "Enable solution folders in Visual Studio. Disable for Express versions." ON)
if (USE_SOLUTION_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

option(BUILD_SAMPLES "Build sample projects." ON)
option(BUILD_TESTS "Build test projects." ON)

set(FIXIE_VERSION 0.0.0)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PUBLIC_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/external)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SAMPLES_DIR ${PROJECT_SOURCE_DIR}/samples)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/test)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG BUILD_DEBUG=1)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELEASE BUILD_RELEASE=1)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -std=c++11 -Wno-deprecated -pthread)
endif()

if(MSVC)
    set(MSVC_COMPILER_DEFS "-D_CRT_SECURE_NO_DEPRECATE -D_VARIADIC_MAX=10")
    add_definitions(${MSVC_COMPILER_DEFS})
    add_definitions(/MP)
endif()

find_package(OpenGL REQUIRED)

include_directories(${PUBLIC_INCLUDES})
set(FIXIE_PROJECT_NAME ${PROJECT_NAME_STR})
set(FIXIE_LIB_PROJECT_NAME ${PROJECT_NAME_STR}_lib)

add_subdirectory(${SRC_DIR})

if (BUILD_SAMPLES)
    add_subdirectory(${EXT_PROJECTS_DIR}/glfw)
    add_subdirectory(${SAMPLES_DIR})
endif()

if (BUILD_TESTS)
    add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
    add_subdirectory(${TESTS_DIR})
endif()
