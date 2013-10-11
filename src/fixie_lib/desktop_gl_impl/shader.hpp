#ifndef _DESKTOP_GL_SHADER_HPP_
#define _DESKTOP_GL_SHADER_HPP_

#include <memory>
#include <cstddef>
#include <unordered_map>
#include "fixie_lib/desktop_gl_impl/shader_info.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader
        {
        public:
            shader(const shader_info& info, std::shared_ptr<gl_functions> functions);

            void sync_state(const state& state);

        private:
            std::shared_ptr<gl_functions> _functions;

            GLuint _program;

            GLuint _position_location;
            GLuint _normal_location;
            GLuint _color_location;
            std::vector<GLuint> _texcoord_locations;

            std::vector<GLuint> _texture_locations;

            struct light_uniform
            {
                GLint _ambient_location;
                GLint _diffuse_location;
                GLint _specular_location;
                GLint _position_location;
                GLint _spot_direction_location;
                GLint _spot_exponent_location;
                GLint _spot_cutoff_location;
                GLint _constant_attenuation_location;
                GLint _linear_attenuation_location;
                GLint _quadratic_attenuation_location;
            };
            std::unordered_map<size_t, light_uniform> _light_locations;

            std::unordered_map<size_t, GLint> _clip_plane_locations;
        };
    }
}

#endif // _DESKTOP_GL_SHADER_HPP_
