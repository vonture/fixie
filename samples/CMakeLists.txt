add_executable(testbed
    testbed.cpp
)

target_link_libraries(testbed
    ${FIXIE_PROJECT_NAME}
)

set_target_properties(testbed PROPERTIES
    FOLDER samples
)

add_definitions(-DFIXIE_DLL_LIBRARY_IMPORT)
