set(SAMPLE_WINDOW_WIDTH 640)
set(SAMPLE_WINDOW_HEIGHT 480)

set(SAMPLE_UTIL_PROJECT_NAME sample_util)

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

macro(add_sample PROJECT_NAME SOURCE COPY_FILES)
    add_executable(${PROJECT_NAME} ${SOURCE} ${COPY_FILES})
    source_group(src FILES ${SOURCE})
    source_group(media FILES ${COPY_FILES})

    include_directories(${SAMPLES_DIR})

    target_link_libraries(${PROJECT_NAME} ${FIXIE_PROJECT_NAME})
    target_link_libraries(${PROJECT_NAME} ${SAMPLE_UTIL_PROJECT_NAME})
    link_glfw(${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER samples)

    foreach(COPY_FILE ${COPY_FILES})
        set_source_files_properties(${COPY_FILE} PROPERTIES HEADER_FILE_ONLY TRUE)
        add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E
                           copy ${COPY_FILE} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
        add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E
                           copy ${COPY_FILE} ${PROJECT_BINARY_DIR}/samples/${PROJECT_NAME})
    endforeach()

    add_definitions(-DSAMPLE_NAME=\"${PROJECT_NAME}\" -DSAMPLE_WIDTH=${SAMPLE_WINDOW_WIDTH} -DSAMPLE_HEIGHT=${SAMPLE_WINDOW_HEIGHT})
endmacro()

add_subdirectory(sample_util)
add_subdirectory(simple_triangle)
add_subdirectory(simple_texturing)
add_subdirectory(simple_model)
add_subdirectory(simple_lighting)
