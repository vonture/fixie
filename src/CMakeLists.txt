set(FIXIE_SOURCE
    debug.hpp
    fixie.cpp
    context.cpp
    context.hpp
)

add_library(fixie SHARED ${FIXIE_SOURCE})
set_target_properties(fixie PROPERTIES
    OUTPUT_NAME "fixie"
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

add_definitions(-DFIXIE_EXPORT)
