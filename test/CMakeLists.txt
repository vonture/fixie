enable_testing()
set(TEST_PROJECT_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${PUBLIC_INCLUDES} ${SRC_DIR})

file(GLOB TEST_SOURCE ${TESTS_DIR}/*.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCE})
add_dependencies(${TEST_PROJECT_NAME} googletest)

target_link_libraries(${TEST_PROJECT_NAME}
    ${FIXIE_STATIC_PROJECT_NAME}
)

set_target_properties(${TEST_PROJECT_NAME} PROPERTIES
    FOLDER test
)

if(NOT WIN32)
    target_link_libraries(${TEST_PROJECT_NAME} pthread)
    target_link_libraries(${TEST_PROJECT_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
    )
else()
    target_link_libraries(${TEST_PROJECT_NAME}
           debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
           optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
    target_link_libraries(${TEST_PROJECT_NAME}
           debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
           optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
endif()

add_test(test1 ${TEST_PROJECT_NAME})
