#ifndef _FIXIE_PLATFORM_H_
#define _FIXIE_PLATFORM_H_

#ifndef FIXIE_API
    #if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
        #if defined(FIXIE_EXPORT)
            #define FIXIE_API __declspec(dllexport)
        #elif defined(FIXIE_DLL_LIBRARY_IMPORT)
            #define FIXIE_API __declspec(dllimport)
        #else // statically linked
            #define AS_API
        #endif
    #elif defined(__GNUC__)
        #if defined(FIXIE_EXPORT)
            #define FIXIE_API __attribute__((visibility ("default")))
        #else
            #define FIXIE_API
        #endif
    #else
        #define FIXIE_API
    #endif
#endif

#endif // _FIXIE_PLATFORM_H_
