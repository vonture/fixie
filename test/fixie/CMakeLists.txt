FILE(GLOB TEST_SOURCE *.cpp)
add_test_project("${FIXIE_PROJECT_NAME}" "${TEST_SOURCE}")
add_definitions(-DFIXIE_DLL_LIBRARY_IMPORT)
