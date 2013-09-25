set(FIXIE_SOURCE
    color.hpp
    color.cpp
    debug.hpp
    context.cpp
    context.hpp
    fixie.cpp
)

add_library(fixie SHARED ${FIXIE_SOURCE})
set_target_properties(fixie PROPERTIES
    OUTPUT_NAME "fixie"
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${FIXIE_VERSION}
)

add_definitions(-DFIXIE_EXPORT)
