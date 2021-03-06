#ifndef _FIXIE_LIB_DESKTOP_GL_CONTEXT_HPP_
#define _FIXIE_LIB_DESKTOP_GL_CONTEXT_HPP_

#include <unordered_set>

#include "fixie_lib/context.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"
#include "fixie_lib/desktop_gl_impl/shader_cache.hpp"
#include "fixie_lib/desktop_gl_impl/gl_version.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class context : public fixie::context_impl
        {
        public:
            context();
            virtual ~context();

            virtual const fixie::caps& caps() override;
            virtual const std::string& renderer_desc() override;

            virtual void initialize_state(fixie::state& state) override;

            virtual std::unique_ptr<texture_impl> create_texture() override;
            virtual std::unique_ptr<renderbuffer_impl> create_renderbuffer() override;
            virtual std::unique_ptr<framebuffer_impl> create_default_framebuffer() override;
            virtual std::unique_ptr<framebuffer_impl> create_framebuffer() override;
            virtual std::unique_ptr<buffer_impl> create_buffer() override;

            virtual void draw_arrays(const state& state, GLenum mode, GLint first, GLsizei count) override;
            virtual void draw_elements(const state& state, GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) override;

            virtual void clear(const state& state, GLbitfield mask) override;

            virtual void flush() override;
            virtual void finish() override;

        private:
            std::shared_ptr<const gl_functions> _functions;
            gl_version _version;
            std::unordered_set<std::string> _extensions;
            fixie::caps _caps;
            shader_cache _shader_cache;

            std::string _renderer_string;

            viewport_state _cur_viewport_state;
            void sync_viewport_state(const viewport_state& state);

            scissor_state _cur_scissor_state;
            void sync_scissor_state(const scissor_state& state);

            color_buffer_state _cur_color_buffer_state;
            void sync_color_buffer_state(const color_buffer_state& state);

            depth_buffer_state _cur_depth_buffer_state;
            void sync_depth_buffer_state(const depth_buffer_state& state);

            stencil_buffer_state _cur_stencil_buffer_state;
            void sync_stencil_buffer_state(const stencil_buffer_state& state);

            point_state _cur_point_state;
            void sync_point_state(const point_state& state);

            line_state _cur_line_state;
            void sync_line_state(const line_state& state);

            polygon_state _cur_polygon_state;
            void sync_polygon_state(const polygon_state& state);

            multisample_state _cur_multisample_state;
            void sync_multisample_state(const multisample_state& state);

            GLuint _vao;
            std::unordered_map<GLint, vertex_attribute> _cur_vertex_attributes;
            void sync_vertex_attribute(const vertex_attribute& attribute, GLint location, GLboolean normalized);
            void sync_vertex_attributes(std::weak_ptr<const fixie::vertex_array> vertex_array, std::weak_ptr<const shader> shader);

            void sync_texture(std::weak_ptr<const fixie::texture> texture, size_t index);
            void sync_textures(const state& state);

            void sync_framebuffer(const state& state);

            void sync_draw_state(const state& state);

            static gl_version initialize_version(std::shared_ptr<const gl_functions> functions);
            static std::unordered_set<std::string> intialize_extensions(std::shared_ptr<const gl_functions> functions, const gl_version& version);
            static fixie::caps initialize_caps(std::shared_ptr<const gl_functions> functions, const gl_version& version, const std::unordered_set<std::string>& extensions);
        };
    }
}

#endif // _FIXIE_LIB_DESKTOP_GL_CONTEXT_HPP_
