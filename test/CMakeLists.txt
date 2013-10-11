macro(link_gtest PROJECT_NAME)
    include_directories(${GTEST_INCLUDE_DIRS} ${PUBLIC_INCLUDES} ${SRC_DIR})

    add_dependencies(${PROJECT_NAME} googletest)

    if(NOT WIN32)
        target_link_libraries(${PROJECT_NAME} pthread)
        target_link_libraries(${PROJECT_NAME}
            ${GTEST_LIBS_DIR}/libgtest.a
            ${GTEST_LIBS_DIR}/libgtest_main.a
        )
    else()
        target_link_libraries(${PROJECT_NAME}
               debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
        target_link_libraries(${PROJECT_NAME}
               debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    endif()
endmacro()

macro(add_test_project ORIGIN_PROJECT_NAME SOURCE)
    set(TEST_PROJECT_NAME ${ORIGIN_PROJECT_NAME}_test)
    add_executable(${TEST_PROJECT_NAME} ${SOURCE})
    source_group(src FILES ${SOURCE})
    target_link_libraries(${TEST_PROJECT_NAME} ${ORIGIN_PROJECT_NAME})
    link_gtest("${TEST_PROJECT_NAME}")
    set_target_properties(${TEST_PROJECT_NAME} PROPERTIES FOLDER test)
    add_test(${ORIGIN_PROJECT_NAME} ${TEST_PROJECT_NAME})
endmacro()

enable_testing()

add_subdirectory(fixie_lib)
add_subdirectory(fixie)
