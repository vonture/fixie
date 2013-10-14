#ifndef _DESKTOP_GL_SHADER_HPP_
#define _DESKTOP_GL_SHADER_HPP_

#include <memory>
#include <cstddef>
#include <unordered_map>
#include "fixie_lib/noncopyable.hpp"
#include "fixie_lib/desktop_gl_impl/shader_info.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class shader : public noncopyable
        {
        public:
            shader(const shader_info& info, std::shared_ptr<const gl_functions> functions);
            ~shader();

            void sync_state(const state& state);

            GLint position_attribute_location() const;
            GLint normal_attribute_location() const;
            GLint color_attribute_location() const;
            GLint texcoord_attribute_location(size_t n) const;

        private:
            std::shared_ptr<const gl_functions> _functions;

            GLuint _program;

            GLint _position_location;
            GLint _position_transform_location;

            GLint _normal_location;
            GLint _color_location;

            struct texcoord_uniform
            {
                GLint texcoord_location;
                GLint texcoord_transform_location;
                GLint sampler_location;
            };
            std::unordered_map<size_t, texcoord_uniform> _texcoord_locations;

            struct light_uniform
            {
                GLint ambient_location;
                GLint diffuse_location;
                GLint specular_location;
                GLint position_location;
                GLint spot_direction_location;
                GLint spot_exponent_location;
                GLint spot_cutoff_location;
                GLint constant_attenuation_location;
                GLint linear_attenuation_location;
                GLint quadratic_attenuation_location;
            };
            std::unordered_map<size_t, light_uniform> _light_locations;

            std::unordered_map<size_t, GLint> _clip_plane_locations;
        };
    }
}

#endif // _DESKTOP_GL_SHADER_HPP_
