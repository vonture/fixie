#include "fixie_lib/enum_names.hpp"
#include "fixie_lib/util.hpp"

#include "fixie/fixie_gl_es.h"

namespace fixie
{
    std::string get_gl_enum_name(GLenum value)
    {
        // TODO: make a table of the valid enums
        return format("0x%X", value);
    }
}
