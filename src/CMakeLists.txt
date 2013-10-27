FILE(GLOB FIXIE_LIB_SOURCE fixie_lib/*.cpp fixie_lib/*.hpp fixie_lib/*.inl)
FILE(GLOB FIXIE_LIB_NULL_IMPL_SOURCE fixie_lib/null_impl/*.cpp fixie_lib/null_impl/*.hpp fixie_lib/null_impl/*.inl)
FILE(GLOB FIXIE_LIB_DESKTOP_GL_IMPL_SOURCE fixie_lib/desktop_gl_impl/*.cpp fixie_lib/desktop_gl_impl/*.hpp fixie_lib/desktop_gl_impl/*.inl)
FILE(GLOB FIXIE_SOURCE fixie/*.cpp fixie/*.hpp fixie/*.inl)
FILE(GLOB FIXIE_INCLUDE ${PUBLIC_INCLUDES}/fixie/*.h)

add_library(${FIXIE_LIB_PROJECT_NAME} STATIC ${FIXIE_LIB_SOURCE} ${FIXIE_LIB_NULL_IMPL_SOURCE} ${FIXIE_LIB_DESKTOP_GL_IMPL_SOURCE} ${FIXIE_INCLUDE})

include_directories(.)

source_group(src FILES ${FIXIE_LIB_SOURCE})
source_group(src\\null_impl FILES ${FIXIE_LIB_NULL_IMPL_SOURCE})
source_group(src\\desktop_gl_impl FILES ${FIXIE_LIB_DESKTOP_GL_IMPL_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})


set_target_properties(${FIXIE_LIB_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "fixie_lib"
    FOLDER fixie
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

add_library(${FIXIE_PROJECT_NAME} SHARED ${FIXIE_INCLUDE} ${FIXIE_SOURCE})

include_directories(.)

source_group(src FILES ${FIXIE_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})

set_target_properties(${FIXIE_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "fixie"
    FOLDER fixie
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

target_link_libraries(${FIXIE_PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${FIXIE_LIB_PROJECT_NAME}
)

add_dependencies(${FIXIE_PROJECT_NAME} ${FIXIE_LIB_PROJECT_NAME})

add_definitions(-DFIXIE_EXPORT)
