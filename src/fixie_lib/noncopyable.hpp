#ifndef _FIXIE_LIB_NONCOPYABLE_HPP_
#define _FIXIE_LIB_NONCOPYABLE_HPP_

namespace fixie
{
    class noncopyable
    {
    protected:
        noncopyable() { };
        ~noncopyable() { };

    private:
        noncopyable(const noncopyable&);
        noncopyable& operator=(const noncopyable&);
    };
}

#endif // _FIXIE_LIB_NONCOPYABLE_HPP_
