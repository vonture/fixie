#include "fixie_lib/desktop_gl_impl/shader.hpp"
#include "fixie_lib/desktop_gl_impl/exceptions.hpp"
#include "fixie_lib/util.hpp"
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
            GLuint shader = functions->gl_create_shader()(type);

            std::array<const GLchar*, 1> source_array = { source.c_str() };
            functions->gl_shader_source()(shader, source_array.size(), source_array.data(), nullptr);
            functions->gl_compile_shader()(shader);

            GLint result;
            functions->gl_get_shader_iv()(shader, GL_COMPILE_STATUS, &result);

            if (result == 0)
            {
                GLint info_log_length;
                functions->gl_get_shader_iv()(shader, GL_INFO_LOG_LENGTH, &info_log_length);

                std::vector<GLchar> info_log(info_log_length);
                functions->gl_get_shader_info_log()(shader, info_log.size(), nullptr, info_log.data());

                functions->gl_delete_shader()(shader);

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
            }

            GLuint program = functions->gl_create_program()();
            functions->gl_attach_shader()(program, vertex_shader);
            functions->gl_delete_shader()(vertex_shader);
            functions->gl_attach_shader()(program, fragment_shader);
            functions->gl_delete_shader()(fragment_shader);
            functions->gl_link_program()(program);

            GLint result;
            functions->gl_get_program_iv()(program, GL_LINK_STATUS, &result);
            if (result == 0)
            {
                GLint info_log_length;
                functions->gl_get_program_iv()(program, GL_INFO_LOG_LENGTH, &info_log_length);

                std::vector<GLchar> info_log(info_log_length);
                functions->gl_get_program_info_log()(program, info_log.size(), nullptr, info_log.data());

                functions->gl_delete_program()(program);

                throw link_error(std::string(info_log.data()));
            }

            return program;
        }

        shader::shader(const shader_info& info, std::shared_ptr<const gl_functions> functions)
            : _functions(functions)
        {
            const GLuint shader_version = 140;
            auto position_name = [](bool vs) { return format("position_%s", vs ? "vs" : "fs"); };
            const std::string position_transform_name = "position_transform";
            auto normal_name = [](bool vs) { return format("normal_%s", vs ? "vs" : "fs"); };
            auto color_name = [](bool vs) { return format("color_%s", vs ? "vs" : "fs"); };
            auto tex_coord_name = [](bool vs, size_t i) { return format("texcoord_%s_%u", vs ? "vs" : "fs", i); };
            auto tex_coord_transform_name = [](size_t i) { return format("texcoord_transform_%u", i); };
            auto sampler_name = [](size_t i) { return format("sampler_%u", i); };
            const std::string ambient_color_name = "ambient_color";
            const std::string output_color_name = "color_out";
            const std::string tab = "    ";

            std::ostringstream vertex_shader;

            vertex_shader << "#version " << shader_version << std::endl;
            vertex_shader << std::endl;

            if (info.uses_vertex_position())
            {
                vertex_shader << "in vec4 " << position_name(true) << ";" << std::endl;
                vertex_shader << "out vec4 " << position_name(false) << ";" << std::endl;
                vertex_shader << "uniform mat4 " << position_transform_name << ";" << std::endl;
            }
            if (info.uses_vertex_normal())
            {
                vertex_shader << "in vec3 " << normal_name(true) << ";" << std::endl;
                vertex_shader << "out vec3 " << normal_name(false) << ";" << std::endl;
            }
            if (info.uses_vertex_color())
            {
                vertex_shader << "in vec4 " << color_name(true) << ";" << std::endl;
                vertex_shader << "out vec4 " << color_name(false) << ";" << std::endl;
            }
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.uses_texture_unit(i))
                {
                    vertex_shader << "in vec4 " << tex_coord_name(true, i) << ";" << std::endl;
                    vertex_shader << "out vec2 " << tex_coord_name(false, i) << ";" << std::endl;
                    vertex_shader << "uniform mat4 " << tex_coord_transform_name(i) << ";" << std::endl;
                }
            }

            vertex_shader << std::endl;
            vertex_shader << "void main(void)" << std::endl;
            vertex_shader << "{" << std::endl;

            if (info.uses_vertex_position())
            {
                vertex_shader << tab << position_name(false) << " = " << position_transform_name << " * " << position_name(true) << ";" << std::endl;
                vertex_shader << tab << "gl_Position = " << position_name(false) << ";" << std::endl;
            }
            else
            {
                vertex_shader << tab << "gl_Position = vec4(0, 0, 0, 1)";
            }

            if (info.uses_vertex_color())
            {
                vertex_shader << tab << color_name(false) << " = " << color_name(true) << ";" << std::endl;
            }

            vertex_shader << "}" << std::endl;


            std::ostringstream fragment_shader;

            fragment_shader << "#version " << shader_version << std::endl;
            fragment_shader << std::endl;

            if (info.uses_vertex_position())
            {
                fragment_shader << "in vec4 " << position_name(false) << ";" << std::endl;
            }
            if (info.uses_vertex_normal())
            {
                fragment_shader << "in vec3 " << normal_name(false) << ";" << std::endl;
            }
            if (info.uses_vertex_color())
            {
                fragment_shader << "in vec4 " << color_name(false) << ";" << std::endl;
            }
            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.uses_texture_unit(i))
                {
                    fragment_shader << "in vec2 " << tex_coord_name(false, i) << ";" << std::endl;
                    fragment_shader << "uniform sampler2D " << sampler_name(i) << ";" << std::endl;
                }
            }
            fragment_shader << "uniform vec4 " << ambient_color_name << ";" << std::endl;
            fragment_shader << "out vec4 " << output_color_name << ";" << std::endl;

            fragment_shader << std::endl;
            fragment_shader << "void main(void)" << std::endl;
            fragment_shader << "{" << std::endl;

            const std::string local_output_color_name = "result_color";

            fragment_shader << tab << "vec4 " << local_output_color_name << " = ";
            if (info.uses_vertex_color())
            {
                fragment_shader << color_name(false) << ";" << std::endl;
            }
            else
            {
                fragment_shader << "vec4(1, 1, 1, 1);" << std::endl;
            }

            fragment_shader << tab << output_color_name << " = " << local_output_color_name << ";" << std::endl;

            fragment_shader << "}" << std::endl;

            _program = create_program(_functions, vertex_shader.str(), fragment_shader.str());

            _functions->gl_bind_frag_data_location()(_program, 0, output_color_name.c_str());

            if (info.uses_vertex_position())
            {
                _position_location = _functions->gl_get_attrib_location()(_program, position_name(true).c_str());
                _position_transform_location =  _functions->gl_get_uniform_location()(_program, position_transform_name.c_str());
            }
            else
            {
                _position_location = -1;
                _position_transform_location = -1;
            }

            if (info.uses_vertex_normal())
            {
                _normal_location = _functions->gl_get_attrib_location()(_program, normal_name(true).c_str());
            }
            else
            {
                _normal_location = -1;
            }

            if (info.uses_vertex_color())
            {
                _color_location = _functions->gl_get_attrib_location()(_program, color_name(true).c_str());
            }
            else
            {
                _color_location = -1;
            }

            for (size_t i = 0; i < info.texture_unit_count(); ++i)
            {
                if (info.uses_texture_unit(i))
                {
                    texcoord_uniform& uniform = _texcoord_locations[i];
                    uniform.texcoord_location = _functions->gl_get_attrib_location()(_program, tex_coord_name(true, i).c_str());
                    uniform.texcoord_transform_location = _functions->gl_get_uniform_location()(_program, tex_coord_transform_name(i).c_str());
                    uniform.sampler_location = _functions->gl_get_uniform_location()(_program, sampler_name(i).c_str());
                }
            }
        }

        shader::~shader()
        {
            _functions->gl_delete_program()(_program);
        }

        void shader::sync_state(const state& state)
        {
            _functions->gl_use_program()(_program);

            //_functions->
            matrix4 transform_matrix = state.model_view_matrix_stack().top_multiplied() * state.projection_matrix_stack().top_multiplied();
            _functions->gl_uniform_matrix_4fv()(_position_transform_location, 1, GL_FALSE, transform_matrix.data);

        }

        GLint shader::position_attribute_location() const
        {
            return _position_location;
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
            auto iter = _texcoord_locations.find(n);
            if (iter != end(_texcoord_locations))
            {
                return iter->second.texcoord_location;
            }
            else
            {
                return -1;
            }
        }
    }
}
