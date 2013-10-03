#ifndef _NULL_CONTEXT_HPP_
#define _NULL_CONTEXT_HPP_

#include "context.hpp"

namespace fixie
{
    namespace null_impl
    {
        class context : public fixie::context_impl
        {
        public:
            virtual std::shared_ptr<texture_impl> create_texture() override;
            virtual std::shared_ptr<buffer_impl> create_buffer() override;
        };
    }
}

#endif // _NULL_CONTEXT_HPP_
