#ifndef _FIXIE_LIB_DESKTOP_GL_SHADER_HPP_
#define _FIXIE_LIB_DESKTOP_GL_SHADER_HPP_

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

            GLint vertex_attribute_location() const;
            GLint normal_attribute_location() const;
            GLint color_attribute_location() const;
            GLint texcoord_attribute_location(size_t n) const;

        private:
            std::shared_ptr<const gl_functions> _functions;

            GLuint _program;

            GLint _vertex_location;
            GLint _model_view_transform_location;
            GLint _projection_transform_location;

            GLint _normal_location;
            GLint _color_location;

            struct texcoord_uniform
            {
                GLint texcoord_location;
                GLint texcoord_transform_location;
                GLint sampler_location;
            };
            std::vector<texcoord_uniform> _texcoord_locations;

            GLint _material_ambient_color_location;
            GLint _material_diffuse_color_location;
            GLint _material_specular_color_location;
            GLint _material_specular_exponent_location;
            GLint _material_emissive_color_location;

            struct light_uniform
            {
                GLint ambient_color_location;
                GLint diffuse_color_location;
                GLint specular_color_location;
                GLint position_location;
                GLint spot_direction_location;
                GLint spot_exponent_location;
                GLint spot_cutoff_location;
                GLint constant_attenuation_location;
                GLint linear_attenuation_location;
                GLint quadratic_attenuation_location;
            };
            std::vector<light_uniform> _light_locations;

            GLint _scene_ambient_color_location;

            std::unordered_map<size_t, GLint> _clip_plane_locations;
        };
    }
}

#endif // _FIXIE_LIB_DESKTOP_GL_SHADER_HPP_
