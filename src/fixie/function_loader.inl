#if defined(__APPLE__)
    #include <mach-o/dyld.h>

    static void* get_gl_proc_address(const std::string& name)
    {
        static const struct mach_header* image = nullptr;
        if (!image)
        {
            image = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", NSADDIMAGE_OPTION_RETURN_ON_ERROR);
        }

        /* prepend a '_' for the Unix C symbol mangling convention */
        std::string symbol_name = std::string("_") + name;

        NSSymbol symbol = image ? NSLookupSymbolInImage(image, symbol_name.c_str(),
                                                        NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR)
                                : nullptr;

        return symbol ? NSAddressOfSymbol(symbol) : nullptr;
    }
#elif defined(__sgi) || defined (__sun)
    #include <dlfcn.h>
    #include <stdio.h>

    static void* get_gl_proc_address(const std::string& name)
    {
        static void* h = nullptr;
        static void* gpa = nullptr;

        if (!h)
        {
            h = dlopen(nullptr, RTLD_LAZY | RTLD_LOCAL);
            if (!h)
            {
                return nullptr;
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
#elif defined(_WIN32)
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
            static PROC get_gl_proc_address(const std::string& name)
            {
                PROC func_ptr = wglGetProcAddress(name.c_str());
                if(func_ptr)
                {
                    return func_ptr;
                }

                HMODULE gl_module = GetModuleHandleA("OpenGL32.dll");
                return reinterpret_cast<PROC>(GetProcAddress(gl_module, name.c_str()));
            }
        }
    }
#else
    #include <GL/glx.h>

    namespace fixie
    {
        namespace priv
        {
            static void* get_gl_proc_address(const std::string& name)
            {
                return reinterpret_cast<void*>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>(name.c_str())));
            }
        }
    }
#endif

namespace fixie
{
    template<typename T> std::function<T> load_gl_function(const std::string &name)
    {
        return (T*)(priv::get_gl_proc_address(name));
    }
}
