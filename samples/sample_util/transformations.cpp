#include "transformations.hpp"

#include <math.h>

namespace sample_util
{
    static const GLfloat pi = 3.1415926535897932384626433832795f;

    void perspective_matrix(GLfloat fov_y, GLfloat aspect_ratio, GLfloat near_z, GLfloat far_z)
    {
        const float frustum_height = tanf(fov_y / 360.0f * pi) * near_z;
        const float frustum_width = frustum_height * aspect_ratio;
        glFrustumf(-frustum_width, frustum_width, -frustum_height, frustum_height, near_z, far_z);
    }
}
