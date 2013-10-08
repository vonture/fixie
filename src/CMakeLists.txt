FILE(GLOB FIXIE_SOURCE fixie/*.cpp fixie/*.hpp fixie/*.inl)
FILE(GLOB FIXIE_NULL_IMPL_SOURCE fixie/null_impl/*.cpp fixie/null_impl/*.hpp fixie/null_impl/*.inl)
FILE(GLOB FIXIE_DESKTOP_GL_IMPL_SOURCE fixie/desktop_gl_impl/*.cpp fixie/desktop_gl_impl/*.hpp fixie/desktop_gl_impl/*.inl)
FILE(GLOB FIXIE_INCLUDE ${PUBLIC_INCLUDES}/fixie/*.h)

add_library(${FIXIE_PROJECT_NAME} SHARED ${FIXIE_SOURCE} ${FIXIE_NULL_IMPL_SOURCE} ${FIXIE_DESKTOP_GL_IMPL_SOURCE} ${FIXIE_INCLUDE})

source_group(src FILES ${FIXIE_SOURCE})
source_group(src/null_impl FILES ${FIXIE_NULL_IMPL_SOURCE})
source_group(src/desktop_gl FILES ${FIXIE_DESKTOP_GL_IMPL_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})

include_directories(.)

set_target_properties(${FIXIE_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "fixie"
    FOLDER fixie
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

target_link_libraries(${FIXIE_PROJECT_NAME}
    ${OPENGL_LIBRARIES}
)

add_definitions(-DFIXIE_EXPORT)


add_library(${FIXIE_STATIC_PROJECT_NAME} STATIC ${FIXIE_SOURCE} ${FIXIE_NULL_IMPL_SOURCE} ${FIXIE_DESKTOP_GL_IMPL_SOURCE} ${FIXIE_INCLUDE})

source_group(src FILES ${FIXIE_SOURCE})
source_group(src/null_impl FILES ${FIXIE_NULL_IMPL_SOURCE})
source_group(src/desktop_gl FILES ${FIXIE_DESKTOP_GL_IMPL_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})

include_directories(.)

set_target_properties(${FIXIE_STATIC_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "fixie_static"
    FOLDER fixie
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)
