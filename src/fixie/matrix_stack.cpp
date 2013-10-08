#include "fixie/matrix_stack.hpp"

#include <assert.h>

namespace fixie
{
    matrix_stack::matrix_stack()
    {
        _stack.push_back(matrix4::identity());
    }

    size_t matrix_stack::size() const
    {
        return _stack.size();
    }

    void matrix_stack::push()
    {
        _multiplied.push_back(_multiplied.back() * _stack.back());
        _stack.push_back(_stack.back());
    }

    void matrix_stack::pop()
    {
        if (_stack.size() > 1)
        {
            assert(_multiplied.size() > 0);

            _stack.pop_back();
            _multiplied.pop_back();
        }
    }

    matrix4& matrix_stack::top()
    {
        return _stack.back();
    }

    const matrix4& matrix_stack::top() const
    {
        return _stack.back();
    }

    matrix4 matrix_stack::top_multiplied() const
    {
        return (_multiplied.size() > 0) ? _multiplied.back() * _stack.back() : _stack.back();
    }

    void matrix_stack::clear()
    {
        _stack.clear();
        _stack.push_back(matrix4::identity());
        _multiplied.clear();
    }
}
