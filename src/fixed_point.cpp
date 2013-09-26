#include "fixed_point.hpp"
#include <limits>

namespace fixie
{
    GLfloat fixed_to_float(GLfixed val)
    {
        GLshort int_part = static_cast<GLshort>(val >> 16);
        GLushort frac_part = static_cast<GLushort>(val & 0xFFFF);
        return int_part + static_cast<GLfloat>(frac_part) / (1 << 16);
    }

    GLfixed float_to_fixed(GLfloat val)
    {
        GLshort int_part = static_cast<GLshort>(val);
        GLushort frac_part = static_cast<GLushort>((std::numeric_limits<GLushort>::max() + 1) * val);
        return (int_part << 16) | frac_part;
    }
}
