#include "fixie_lib/desktop_gl_impl/shader.hpp"
#include "fixie_lib/desktop_gl_impl/exceptions.hpp"
#include "fixie_lib/util.hpp"
#include "fixie_lib/debug.hpp"
#include "fixie/fixie_gl_es.h"
#include <sstream>
#include <array>

namespace fixie
{
    #define GL_COMPILE_STATUS 0x8B81
    #define GL_INFO_LOG_LENGTH 0x8B84
    #define GL_VERTEX_SHADER 0x8B31
    #define GL_FRAGMENT_SHADER 0x8B30
    #define GL_LINK_STATUS 0x8B82

    namespace desktop_gl_impl
    {
        static GLuint compile_shader(std::shared_ptr<const gl_functions> functions, const std::string& source, GLenum type)
        {
            GLuint shader = gl_call(functions, gl_create_shader, type);

            std::array<const GLchar*, 1> source_array = { source.c_str() };
            gl_call(functions, gl_shader_source, shader, static_cast<GLsizei>(source_array.size()), source_array.data(), nullptr);
            gl_call(functions, gl_compile_shader, shader);

            GLint result;
            gl_call(functions, gl_get_shader_iv, shader, GL_COMPILE_STATUS, &result);

            if (result == 0)
            {
                GLint info_log_length;
                gl_call(functions, gl_get_shader_iv, shader, GL_INFO_LOG_LENGTH, &info_log_length);

                std::vector<GLchar> info_log(info_log_length);
                gl_call(functions, gl_get_shader_info_log, shader, static_cast<GLsizei>(info_log.size()), nullptr, info_log.data());

                gl_call(functions, gl_delete_shader, shader);

                throw compile_error(std::string(info_log.data()));
            }

            return shader;
        }

        static GLuint create_program(std::shared_ptr<const gl_functions> functions, const std::string& vertex_source, const std::string& fragment_source)
        {
            GLuint vertex_shader = 0;
            GLuint fragment_shader = 0;
            try
            {
                vertex_shader = compile_shader(functions, vertex_source, GL_VERTEX_SHADER);
                fragment_shader = compile_shader(functions, fragment_source, GL_FRAGMENT_SHADER);
            }
            catch (...)
            {
                functions->gl_delete_shader()(vertex_shader);
                functions->gl_delete_shader()(fragment_shader);
                throw;
            }

            GLuint program = gl_call(functions, gl_create_program);
            gl_call(functions, gl_attach_shader, program, vertex_shader);
            gl_call(functions, gl_delete_shader, vertex_shader);
            gl_call(functions, gl_attach_shader, program, fragment_shader);
            gl_call(functions, gl_delete_shader, fragment_shader);
            gl_call(functions, gl_link_program, program);

            GLint result;
            functions->gl_get_program_iv()(program, GL_LINK_STATUS, &result);
            if (result == 0)
            {
                GLint info_log_length;
                gl_call(functions, gl_get_program_iv, program, GL_INFO_LOG_LENGTH, &info_log_length);

                std::vector<GLchar> info_log(info_log_length);
                gl_call(functions, gl_get_program_info_log, program, static_cast<GLsizei>(info_log.size()), nullptr,
                                                            info_log.data());

                gl_call(functions, gl_delete_program, program);

                throw link_error(std::string(info_log.data()));
            }

            return program;
        }

        static GLuint shader_version()
        {
            return 140;
        }

        enum shader_type
        {
            vertex_input,
            vertex_output,
            fragment_input,
            fragment_output,
        };

        static std::string shader_type_name(shader_type type)
        {
            switch(type)
            {
            case vertex_input:      return "vs";
            case vertex_output:     return "fs";
            case fragment_input:    return "fs";
            case fragment_output:   return "out";
            default: UNREACHABLE(); return "";
            }
        }

        static std::string vertex_name(shader_type type)
        {
            return format("position_%s", shader_type_name(type).c_str());
        }

        static std::string model_view_transform_name()
        {
            return "model_view_transform";
        }

        static std::string projection_transform_name()
        {
            return "projection_transform";
        }

        static std::string normal_name(shader_type type)
        {
            return format("normal_%s", shader_type_name(type).c_str());
        }

        static std::string color_name(shader_type type)
        {
            return format("color_%s", shader_type_name(type).c_str());
        }

        static std::string tex_coord_name(shader_type type, size_t i)
        {
            return format("texcoord_%u_%s", i, shader_type_name(type).c_str());
        }

        static std::string tex_coord_transform_name(size_t i)
        {
            return format("texcoord_%u_transform", i);
        }

        static std::string sampler_name(size_t i)
        {
            return format("sampler_%u", i);
        }

        static std::string material_ambient_color_name()
        {
            return "material_ambient_color";
        }

        static std::string material_diffuse_color_name()
        {
            return "material_diffuse_color";
        }

        static std::string material_specular_color_name()
        {
            return "material_specular_color";
        }

        static std::string material_specular_exponent_name()
        {
            return "material_specular_exponent";
        }

        static std::string material_emissive_color_name()
        {
            return "material_emissive_color";
        }

        static std::string scene_ambient_color_name()
        {
            return "scene_ambient_color";
        }

        static std::string light_ambient_color_name(size_t light)
        {
            return format("light_%u_ambient_color", light);
        }

        static std::string light_diffuse_color_name(size_t i)
        {
            return format("light_%u_diffuse_color");
        }

        static std::string light_specular_color_name(size_t i)
        {
            return format("light_%u_specular_color");
        }

        static std::string light_position_name(size_t i)
        {
            return format("light_%u_position");
        }

        static std::string light_direction_name(size_t i)
        {
            return format("light_%u_direction");
        }

        static std::string light_spotlight_exponent_name(size_t i)
        {
            return format("light_%u_spotlight_exponent");
        }

        static std::string light_spotlight_cutoff_name(size_t i)
        {
            return format("light_%u_spotlight_cutoff");
        }

        static std::string light_constant_attenuation_name(size_t i)
        {
            return format("light_%u_constant_attenuation");
        }

        static std::string light_linear_attenuation_name(size_t i)
        {
            return format("light_%u_linear_attenuation");
        }

        static std::string light_quadratic_attenuation_name(size_t i)
        {
            return format("light_%u_quadratic_attenuation");
        }

        static std::string tab(size_t count)
        {
            return std::string(count * 4, ' ');
        }

        static std::string generate_vertex_shader(const shader_info& info)
        {
            std::ostringstream vertex_shader;

            vertex_shader << "#version " << shader_version() << std::endl;
            vertex_shader << std::endl;

            vertex_shader << "in vec4 " << vertex_name(vertex_input) << ";" << std::endl;
            vertex_shader << "out vec4 " << vertex_name(vertex_output) << ";" << std::endl;
            vertex_shader << "uniform mat4 " << model_view_transform_name() << ";" << std::endl;
            vertex_shader << "uniform mat4 " << projection_transform_name() << ";" << std::endl;
            vertex_shader << "in vec3 " << normal_name(vertex_input) << ";" << std::endl;
            vertex_shader << "out vec3 " << normal_name(vertex_output) << ";" << std::endl;
            vertex_shader << "in vec4 " << color_name(vertex_input) << ";" << std::endl;
            vertex_shader << "out vec4 " << color_name(vertex_output) << ";" << std::endl;
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    vertex_shader << "in vec4 " << tex_coord_name(vertex_input, i) << ";" << std::endl;
                    vertex_shader << "out vec4 " << tex_coord_name(vertex_output, i) << ";" << std::endl;
                    vertex_shader << "uniform mat4 " << tex_coord_transform_name(i) << ";" << std::endl;
                }
            }

            vertex_shader << std::endl;
            vertex_shader << "void main(void)" << std::endl;
            vertex_shader << "{" << std::endl;
            vertex_shader << tab(1) << vertex_name(vertex_output) << " = " << model_view_transform_name() << " * " << vertex_name(vertex_input) << ";" << std::endl;
            vertex_shader << tab(1) << normal_name(vertex_output) << " = mat3(" << model_view_transform_name() << ") * " << normal_name(vertex_input) << ";" << std::endl;
            vertex_shader << tab(1) << color_name(vertex_output) << " = " << color_name(vertex_input) << ";" << std::endl;
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    vertex_shader << tab(1) << tex_coord_name(vertex_output, i) << " = " << tex_coord_transform_name(i) << " * " << tex_coord_name(vertex_input, i) << ";" << std::endl;
                }
            }
            vertex_shader << std::endl;
            vertex_shader << tab(1) << "gl_Position = (" << projection_transform_name() << " * "<< model_view_transform_name() << ") * " << vertex_name(vertex_input) << ";" << std::endl;
            vertex_shader << "}" << std::endl;

            return vertex_shader.str();
        }

        static std::string generate_fragment_shader(const shader_info& info)
        {
            std::ostringstream fragment_shader;

            fragment_shader << "#version " << shader_version() << std::endl;
            fragment_shader << std::endl;

            fragment_shader << "in vec4 " << vertex_name(fragment_input) << ";" << std::endl;
            fragment_shader << "in vec3 " << normal_name(fragment_input) << ";" << std::endl;
            fragment_shader << "in vec4 " << color_name(fragment_input) << ";" << std::endl;
            fragment_shader << std::endl;

            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    fragment_shader << "in vec4 " << tex_coord_name(fragment_input, i) << ";" << std::endl;
                    fragment_shader << "uniform sampler2D " << sampler_name(i) << ";" << std::endl;
                    fragment_shader << std::endl;
                }
            }

            if (info.lighting_enabled())
            {
                fragment_shader << "uniform vec4 " << material_ambient_color_name() << ";" << std::endl;
                fragment_shader << "uniform vec4 " << material_diffuse_color_name() << ";" << std::endl;
                fragment_shader << "uniform vec4 " << material_specular_color_name() << ";" << std::endl;
                fragment_shader << "uniform float " << material_specular_exponent_name() << ";" << std::endl;
                fragment_shader << "uniform vec4 " << material_emissive_color_name() << ";" << std::endl;
                fragment_shader << std::endl;

                for (size_t i = 0; i < info.light_count(); i++)
                {
                    if (info.uses_light(i))
                    {
                        fragment_shader << "uniform vec4 " << light_ambient_color_name(i) << ";" << std::endl;
                        fragment_shader << "uniform vec4 " << light_diffuse_color_name(i) << ";" << std::endl;
                        fragment_shader << "uniform vec4 " << light_specular_color_name(i) << ";" << std::endl;
                        fragment_shader << "uniform vec4 " << light_position_name(i) << ";" << std::endl;
                        fragment_shader << "uniform vec3 " << light_direction_name(i) << ";" << std::endl;
                        fragment_shader << "uniform float " << light_spotlight_exponent_name(i) << ";" << std::endl;
                        fragment_shader << "uniform float " << light_spotlight_cutoff_name(i) << ";" << std::endl;
                        fragment_shader << "uniform float " << light_constant_attenuation_name(i) << ";" << std::endl;
                        fragment_shader << "uniform float " << light_linear_attenuation_name(i) << ";" << std::endl;
                        fragment_shader << "uniform float " << light_quadratic_attenuation_name(i) << ";" << std::endl;
                        fragment_shader << std::endl;
                    }
                }

                fragment_shader << "uniform vec4 " << scene_ambient_color_name() << ";" << std::endl;
                fragment_shader << std::endl;
            }

            fragment_shader << "out vec4 " << color_name(fragment_output) << ";" << std::endl;
            fragment_shader << std::endl;

            fragment_shader << "void main(void)" << std::endl;
            fragment_shader << "{" << std::endl;

            const std::string local_normal_name = "local_normal";
            fragment_shader << tab(1) << "vec3 " << local_normal_name << " = ";
            if (info.two_sided_lighting())
            {
                fragment_shader << "gl_FrontFacing ? " << normal_name(fragment_input) << " : -" << normal_name(fragment_input) << ";" << std::endl;
            }
            else
            {
                fragment_shader << normal_name(fragment_input) << ";" << std::endl;
            }

            const std::string local_output_color_name = "result_color";
            fragment_shader << tab(1) << "vec4 " << local_output_color_name << " = " << color_name(fragment_input) << ";" << std::endl;

            const std::string texture_result_name = "texture_result";
            fragment_shader << tab(1) << "vec4 " << texture_result_name << " = vec4(1.0, 1.0, 1.0, 1.0);" << std::endl;
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    const std::string texture_sample_name = format("texture_sample_%u", i);
                    fragment_shader << tab(1) << "vec4 " << texture_sample_name << " = texture(" << sampler_name(i) << ", " << tex_coord_name(fragment_input, i) << ".xy);" << std::endl;
                    fragment_shader << tab(1) << texture_result_name << " *= " << texture_sample_name << ";" << std::endl;
                }
            }
            fragment_shader << tab(1) << local_output_color_name << " *= " << texture_result_name << ";" << std::endl;
            fragment_shader << std::endl;

            if (info.lighting_enabled())
            {
                const std::string lighting_result_name = "lighting_result";
                fragment_shader << tab(1) << "vec4 " << lighting_result_name << " = " << material_emissive_color_name() << " + " << material_ambient_color_name() << " * " << scene_ambient_color_name() << ";" << std::endl;
                for (size_t i = 0; i < info.light_count(); i++)
                {
                    if (info.uses_light(i))
                    {
                    }
                }
                fragment_shader << tab(1) << local_output_color_name << " *= " << lighting_result_name << ";" << std::endl;
                fragment_shader << std::endl;
            }

            fragment_shader << tab(1) << color_name(fragment_output) << " = " << local_output_color_name << ";" << std::endl;
            fragment_shader << "}" << std::endl;

            return fragment_shader.str();
        }

        shader::shader(const shader_info& info, std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
        {
            _program = create_program(_functions, generate_vertex_shader(info), generate_fragment_shader(info));

            gl_call(_functions, gl_bind_frag_data_location, _program, 0, color_name(fragment_output).c_str());

            _vertex_location = gl_call(_functions, gl_get_attrib_location, _program, vertex_name(vertex_input).c_str());
            _model_view_transform_location = gl_call(_functions, gl_get_uniform_location, _program, model_view_transform_name().c_str());
            _projection_transform_location = gl_call(_functions, gl_get_uniform_location, _program, projection_transform_name().c_str());

            _normal_location = gl_call(_functions, gl_get_attrib_location, _program, normal_name(vertex_input).c_str());
            _color_location = gl_call(_functions, gl_get_attrib_location, _program, color_name(vertex_input).c_str());

            _texcoord_locations.resize(info.texture_unit_count());
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                texcoord_uniform& uniform = _texcoord_locations[i];
                uniform.texcoord_location = gl_call(_functions, gl_get_attrib_location, _program, tex_coord_name(vertex_input, i).c_str());
                uniform.texcoord_transform_location = gl_call(_functions, gl_get_uniform_location, _program, tex_coord_transform_name(i).c_str());
                uniform.sampler_location = gl_call(_functions, gl_get_uniform_location, _program, sampler_name(i).c_str());
            }

            _material_ambient_color_location = gl_call(_functions, gl_get_uniform_location, _program, material_ambient_color_name().c_str());
            _material_diffuse_color_location = gl_call(_functions, gl_get_uniform_location, _program, material_diffuse_color_name().c_str());
            _material_specular_color_location = gl_call(_functions, gl_get_uniform_location, _program, material_specular_color_name().c_str());
            _material_specular_exponent_location = gl_call(_functions, gl_get_uniform_location, _program, material_specular_exponent_name().c_str());
            _material_emissive_color_location = gl_call(_functions, gl_get_uniform_location, _program, material_emissive_color_name().c_str());

            _light_locations.resize(info.light_count());
            for (size_t i = 0; i < info.light_count(); i++)
            {
                light_uniform& uniform = _light_locations[i];
                uniform.ambient_color_location = gl_call(_functions, gl_get_uniform_location, _program, light_ambient_color_name(i).c_str());
                uniform.diffuse_color_location = gl_call(_functions, gl_get_uniform_location, _program, light_diffuse_color_name(i).c_str());
                uniform.specular_color_location = gl_call(_functions, gl_get_uniform_location, _program, light_specular_color_name(i).c_str());
                uniform.position_location = gl_call(_functions, gl_get_uniform_location, _program, light_position_name(i).c_str());
                uniform.spot_direction_location = gl_call(_functions, gl_get_uniform_location, _program, light_direction_name(i).c_str());
                uniform.spot_exponent_location = gl_call(_functions, gl_get_uniform_location, _program, light_spotlight_exponent_name(i).c_str());
                uniform.spot_cutoff_location = gl_call(_functions, gl_get_uniform_location, _program, light_spotlight_cutoff_name(i).c_str());
                uniform.constant_attenuation_location = gl_call(_functions, gl_get_uniform_location, _program, light_constant_attenuation_name(i).c_str());
                uniform.linear_attenuation_location = gl_call(_functions, gl_get_uniform_location, _program, light_linear_attenuation_name(i).c_str());
                uniform.quadratic_attenuation_location = gl_call(_functions, gl_get_uniform_location, _program, light_quadratic_attenuation_name(i).c_str());
            }

            _scene_ambient_color_location = gl_call(_functions, gl_get_uniform_location, _program, scene_ambient_color_name().c_str());
        }

        shader::~shader()
        {
            gl_call(_functions, gl_delete_program, _program);
        }

        void shader::sync_state(const state& state)
        {
            gl_call(_functions, gl_use_program, _program);
            gl_call(_functions, gl_uniform_matrix_4fv, _model_view_transform_location, 1, GL_FALSE, state.model_view_matrix_stack().top_multiplied().data());
            gl_call(_functions, gl_uniform_matrix_4fv, _projection_transform_location, 1, GL_FALSE, state.projection_matrix_stack().top_multiplied().data());

            for (size_t i = 0; i < _texcoord_locations.size(); i++)
            {
                texcoord_uniform& uniform = _texcoord_locations[i];
                gl_call(_functions, gl_uniform_matrix_4fv, uniform.texcoord_transform_location, 1, GL_FALSE, state.texture_matrix_stack(i).top_multiplied().data());
                gl_call(_functions, gl_uniform_1i, uniform.sampler_location, static_cast<GLint>(i));
            }

            gl_call(_functions, gl_uniform_4fv, _material_ambient_color_location, 1, state.lighting_state().front_material().ambient().data());
            gl_call(_functions, gl_uniform_4fv, _material_diffuse_color_location, 1, state.lighting_state().front_material().diffuse().data());
            gl_call(_functions, gl_uniform_4fv, _material_specular_color_location, 1, state.lighting_state().front_material().specular().data());
            gl_call(_functions, gl_uniform_1f, _material_specular_exponent_location, state.lighting_state().front_material().specular_exponent());
            gl_call(_functions, gl_uniform_4fv, _material_emissive_color_location, 1, state.lighting_state().front_material().emissive().data());

            for (size_t i = 0; i < _light_locations.size(); i++)
            {
                light_uniform& uniform = _light_locations[i];
                gl_call(_functions, gl_uniform_4fv, uniform.ambient_color_location, 1, state.lighting_state().light(i).ambient().data());
                gl_call(_functions, gl_uniform_4fv, uniform.diffuse_color_location, 1, state.lighting_state().light(i).diffuse().data());
                gl_call(_functions, gl_uniform_4fv, uniform.specular_color_location, 1, state.lighting_state().light(i).specular().data());
                gl_call(_functions, gl_uniform_4fv, uniform.position_location, 1, state.lighting_state().light(i).position().data());
                gl_call(_functions, gl_uniform_3fv, uniform.spot_direction_location, 1, state.lighting_state().light(i).spot_direction().data());
                gl_call(_functions, gl_uniform_1f, uniform.spot_exponent_location, state.lighting_state().light(i).spot_exponent());
                gl_call(_functions, gl_uniform_1f, uniform.spot_cutoff_location, state.lighting_state().light(i).spot_cutoff());
                gl_call(_functions, gl_uniform_1f, uniform.constant_attenuation_location, state.lighting_state().light(i).constant_attenuation());
                gl_call(_functions, gl_uniform_1f, uniform.linear_attenuation_location, state.lighting_state().light(i).linear_attenuation());
                gl_call(_functions, gl_uniform_1f, uniform.quadratic_attenuation_location, state.lighting_state().light(i).quadratic_attenuation());
            }

            gl_call(_functions, gl_uniform_4fv, _scene_ambient_color_location, 1, state.lighting_state().light_model().ambient_color().data());
        }

        GLint shader::vertex_attribute_location() const
        {
            return _vertex_location;
        }

        GLint shader::normal_attribute_location() const
        {
            return _normal_location;
        }

        GLint shader::color_attribute_location() const
        {
            return _color_location;
        }

        GLint shader::texcoord_attribute_location(size_t n) const
        {
            return _texcoord_locations[n].texcoord_location;
        }
    }
}
