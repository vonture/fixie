set(SAMPLE_WINDOW_WIDTH 640)
set(SAMPLE_WINDOW_HEIGHT 480)

macro(link_glfw PROJECT_NAME)
    if(NOT WIN32)
        target_link_libraries(${PROJECT_NAME} glfw3.a)
    else()
        target_link_libraries(${PROJECT_NAME}
               debug ${GLFW_LIBS_DIRS}/src/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}glfw3${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${GLFW_LIBS_DIRS}/src/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}glfw3${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    endif()
    include_directories(${GLFW_INCLUDE_DIRS})
    add_dependencies(${PROJECT_NAME} glfw)
endmacro()

macro(add_sample PROJECT_NAME SOURCE)
    add_executable(${PROJECT_NAME} ${SOURCE})
    source_group(src FILES ${SOURCE})

    target_link_libraries(${PROJECT_NAME} ${FIXIE_PROJECT_NAME})
    link_glfw(${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER samples)

    add_definitions(-DFIXIE_DLL_LIBRARY_IMPORT -DSAMPLE_NAME=\"${PROJECT_NAME}\" -DSAMPLE_WIDTH=${SAMPLE_WINDOW_WIDTH} -DSAMPLE_HEIGHT=${SAMPLE_WINDOW_HEIGHT})
endmacro()

add_subdirectory(simple_triangle)
add_subdirectory(simple_texturing)
