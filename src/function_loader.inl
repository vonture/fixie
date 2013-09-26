#if defined(__APPLE__)
#include <mach-o/dyld.h>

static void* GetGLProcAddress(const std::string &name)
{
    static const struct mach_header* image = NULL;
    if (!image)
    {
        image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
    }

    /* prepend a '_' for the Unix C symbol mangling convention */
    std::string symbol_name = std::string("_") + name;

    NSSymbol symbol = image ? NSLookupSymbolInImage(image, symbol_name.c_str(),
                                                    NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR)
                            : NULL;

    return symbol ? NSAddressOfSymbol(symbol) : NULL;
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* GetGLProcAddress(const std::string &name)
{
    static void* h = NULL;
    static void* gpa = NULL;

    if (!h)
    {
        h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL);
        if (!h)
        {
            return NULL;
        }
        gpa = dlsym(h, "glXGetProcAddress");
    }

    if (gpa)
    {
        return ((void*(*)(const GLubyte*))gpa)(name.c_str());
    }
    else
    {
        return dlsym(h, name.c_str());
    }
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX
    #define NOMINMAX
#endif

#include <windows.h>

#include <stdlib.h>
#include <stddef.h>
#include <stddef.h>

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#endif

namespace fixie
{
    namespace priv
    {
        static int TestPointer(const PROC pTest)
        {
            if(!pTest)
            {
                return 0;
            }

            ptrdiff_t iTest = (ptrdiff_t)pTest;
            return (iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) ? 0 : 1;
        }

        static PROC GetGLProcAddress(const std::string &name)
        {
            PROC func_ptr = wglGetProcAddress(name.c_str());
            if(TestPointer(func_ptr))
            {
                return func_ptr;
            }

            HMODULE gl_module = GetModuleHandleA("OpenGL32.dll");
            return (PROC)GetProcAddress(gl_module, name.c_str());
        }
    }
}
#endif

namespace fixie
{
    template<typename T> std::function<T> load_gl_function(const std::string &name)
    {
        return (T*)(priv::GetGLProcAddress(name));
    }
}
