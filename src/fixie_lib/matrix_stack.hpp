#ifndef _FIXIE_LIB_MATRIX_STACK_HPP_
#define _FIXIE_LIB_MATRIX_STACK_HPP_

#include <vector>

#include "fixie_lib/matrix.hpp"

namespace fixie
{
    class matrix_stack
    {
    public:
        matrix_stack();

        size_t size() const;

        void push();
        void pop();

        matrix4& top();
        const matrix4& top() const;

        matrix4 top_multiplied() const;

        void clear();

    private:
        std::vector<matrix4> _stack;
        std::vector<matrix4> _multiplied;
    };
}

#endif // _FIXIE_LIB_MATRIX_STACK_HPP_
