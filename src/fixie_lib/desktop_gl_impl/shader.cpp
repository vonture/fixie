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
            return format("texcoord_%s_%u", shader_type_name(type).c_str(), i);
        }

        static std::string tex_coord_transform_name(size_t i)
        {
            return format("texcoord_transform_%u", i);
        }

        static std::string sampler_name(size_t i)
        {
            return format("sampler_%u", i);
        }

        static std::string tab()
        {
            return "    ";
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
            vertex_shader << tab() << vertex_name(vertex_output) << " = " << model_view_transform_name() << " * " << vertex_name(vertex_input) << ";" << std::endl;
            vertex_shader << tab() << normal_name(vertex_output) << " = mat3(" << model_view_transform_name() << ") * " << normal_name(vertex_input) << ";" << std::endl;
            vertex_shader << tab() << color_name(vertex_output) << " = " << color_name(vertex_input) << ";" << std::endl;
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    vertex_shader << tab() << tex_coord_name(vertex_output, i) << " = " << tex_coord_transform_name(i) << " * " << tex_coord_name(vertex_input, i) << ";" << std::endl;
                }
            }
            vertex_shader << std::endl;
            vertex_shader << tab() << "gl_Position = (" << projection_transform_name() << " * "<< model_view_transform_name() << ") * " << vertex_name(vertex_input) << ";" << std::endl;
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
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    fragment_shader << "in vec4 " << tex_coord_name(fragment_input, i) << ";" << std::endl;
                    fragment_shader << "uniform sampler2D " << sampler_name(i) << ";" << std::endl;
                }
            }
            fragment_shader << "out vec4 " << color_name(fragment_output) << ";" << std::endl;

            fragment_shader << std::endl;
            fragment_shader << "void main(void)" << std::endl;
            fragment_shader << "{" << std::endl;

            const std::string local_output_color_name = "result_color";
            fragment_shader << tab() << "vec4 " << local_output_color_name << " = " << color_name(fragment_input) << ";" << std::endl;

            const std::string texture_result_name = "texture_result";
            fragment_shader << tab() << "vec4 " << texture_result_name << " = vec4(1.0, 1.0, 1.0, 1.0);" << std::endl;
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.texture_environment(i).enabled())
                {
                    const std::string texture_sample_name = format("texture_sample_%u", i);
                    fragment_shader << tab() << "vec4 " << texture_sample_name << " = texture(" << sampler_name(i) << ", " << tex_coord_name(fragment_input, i) << ".xy);" << std::endl;
                    fragment_shader << tab() << texture_result_name << " *= " << texture_sample_name << ";" << std::endl;
                }
            }
            fragment_shader << tab() << local_output_color_name << " *= " << texture_result_name << ";" << std::endl;

            fragment_shader << tab() << color_name(fragment_output) << " = " << local_output_color_name << ";" << std::endl;
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
                if (info.texture_environment(i).enabled())
                {
                    uniform.texcoord_location = gl_call(_functions, gl_get_attrib_location, _program, tex_coord_name(vertex_input, i).c_str());
                    uniform.texcoord_transform_location = gl_call(_functions, gl_get_uniform_location, _program, tex_coord_transform_name(i).c_str());
                    uniform.sampler_location = gl_call(_functions, gl_get_uniform_location, _program, sampler_name(i).c_str());
                }
                else
                {
                    uniform.texcoord_location = -1;
                    uniform.texcoord_transform_location = -1;
                    uniform.sampler_location = -1;
                }
            }
        }

        shader::~shader()
        {
            gl_call(_functions, gl_delete_program, _program);
        }

        void shader::sync_state(const state& state)
        {
            gl_call(_functions, gl_use_program, _program);

            if (_model_view_transform_location != -1)
            {
                gl_call(_functions, gl_uniform_matrix_4fv, _model_view_transform_location, 1, GL_FALSE, state.model_view_matrix_stack().top_multiplied().data);
            }

            if (_projection_transform_location != -1)
            {
                gl_call(_functions, gl_uniform_matrix_4fv, _projection_transform_location, 1, GL_FALSE, state.projection_matrix_stack().top_multiplied().data);
            }

            for (size_t i = 0; i < _texcoord_locations.size(); i++)
            {
                if (_texcoord_locations[i].texcoord_transform_location != -1)
                {
                    gl_call(_functions, gl_uniform_matrix_4fv, _texcoord_locations[i].texcoord_transform_location, 1, GL_FALSE, state.texture_matrix_stack(i).top_multiplied().data);
                }
                if (_texcoord_locations[i].sampler_location != -1)
                {
                    gl_call(_functions, gl_uniform_1i, _texcoord_locations[i].sampler_location, static_cast<GLint>(i));
                }
            }
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
