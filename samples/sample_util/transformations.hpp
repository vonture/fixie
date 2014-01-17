#ifndef _SAMPLE_UTIL_TRANSFORMATIONS_HPP_
#define _SAMPLE_UTIL_TRANSFORMATIONS_HPP_

#include "fixie/fixie_gl_es.h"

namespace sample_util
{
    void perspective_matrix(GLfloat fov_y, GLfloat aspect_ratio, GLfloat near_z, GLfloat far_z);
}

#endif // _SAMPLE_UTIL_TRANSFORMATIONS_HPP_
