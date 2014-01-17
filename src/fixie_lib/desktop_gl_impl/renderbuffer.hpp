#ifndef _FIXIE_LIB_DESKTOP_GL_RENDERBUFFER_HPP_
#define _FIXIE_LIB_DESKTOP_GL_RENDERBUFFER_HPP_

#include "fixie_lib/renderbuffer.hpp"
#include "fixie_lib/desktop_gl_impl/gl_functions.hpp"

namespace fixie
{
    namespace desktop_gl_impl
    {
        class renderbuffer : public fixie::renderbuffer_impl
        {
        public:
            explicit renderbuffer(std::shared_ptr<const gl_functions> functions);
            virtual ~renderbuffer();

            GLuint id() const;

            virtual GLsizei red_size() const override;
            virtual GLsizei green_size() const override;
            virtual GLsizei blue_size() const override;
            virtual GLsizei alpha_size() const override;
            virtual GLsizei depth_size() const override;
            virtual GLsizei stencil_size() const override;

            virtual void set_storage(GLenum target, GLenum internal_format, GLsizei width, GLsizei height) override;
            virtual void set_storage_multisample(GLenum target, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height) override;

        private:
            std::shared_ptr<const gl_functions> _functions;
            GLuint _id;
        };
    }
}

#endif // _FIXIE_LIB_DESKTOP_GL_RENDERBUFFER_HPP_
