add_executable(testbed
    testbed.cpp
)

target_link_libraries(testbed
    fixie
)

add_definitions(-DFIXIE_DLL_LIBRARY_IMPORT)
