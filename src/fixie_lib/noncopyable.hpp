#ifndef _NONCOPYABLE_HPP_
#define _NONCOPYABLE_HPP_

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

#endif // _NONCOPYABLE_HPP_
