FILE(GLOB FIXIE_SOURCE *.cpp *.hpp *.inl)
FILE(GLOB FIXIE_INCLUDE ../include/*.h)

add_library(fixie SHARED ${FIXIE_SOURCE} ${FIXIE_INCLUDE})

source_group(src FILES ${FIXIE_SOURCE})
source_group(include FILES ${FIXIE_INCLUDE})

set_target_properties(fixie PROPERTIES
    OUTPUT_NAME "fixie"
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

target_link_libraries(fixie
    ${OPENGL_LIBRARIES}
)

add_definitions(-DFIXIE_EXPORT)
