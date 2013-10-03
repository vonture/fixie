#include "null_impl/null_context.hpp"
#include "null_impl/null_texture.hpp"
#include "null_impl/null_buffer.hpp"

namespace fixie
{
    namespace null_impl
    {
        std::shared_ptr<texture_impl> context::create_texture()
        {
            return std::make_shared<texture>();
        }

        std::shared_ptr<buffer_impl> context::create_buffer()
        {
            return std::make_shared<buffer>();
        }
    }
}
