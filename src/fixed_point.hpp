#ifndef _FIXED_POINT_HPP_
#define _FIXED_POINT_HPP_

#include "fixie_gl_types.h"

namespace fixie
{
    GLfloat fixed_to_float(GLfixed val);
    GLfixed float_to_fixed(GLfloat val);
}

#endif // _FIXED_POINT_HPP_
