FILE(GLOB FIXIE_SOURCE *.cpp *.hpp *.inl)
FILE(GLOB FIXIE_INCLUDE ${PUBLIC_INCLUDES}/*.h)

add_library(${FIXIE_PROJECT_NAME} SHARED ${FIXIE_SOURCE} ${FIXIE_INCLUDE})

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
)

add_definitions(-DFIXIE_EXPORT)


add_library(${FIXIE_STATIC_PROJECT_NAME} STATIC ${FIXIE_SOURCE} ${FIXIE_INCLUDE})

source_group(src FILES ${FIXIE_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})

set_target_properties(${FIXIE_STATIC_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "fixie_static"
    FOLDER fixie
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)
