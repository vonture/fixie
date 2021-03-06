#ifndef _FIXIE_PLATFORM_H_
#define _FIXIE_PLATFORM_H_

#ifndef FIXIE_API
    #if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
        #if defined(FIXIE_EXPORT)
            #define FIXIE_API __declspec(dllexport)
        #else
            #define FIXIE_API __declspec(dllimport)
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

#ifndef FIXIE_APIENTRY
    #if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
        #define FIXIE_APIENTRY __stdcall
    #else
        #define FIXIE_APIENTRY
    #endif
#endif

#ifndef FIXIE_APIENTRYP
    #define FIXIE_APIENTRYP FIXIE_APIENTRY*
#endif

#endif // _FIXIE_PLATFORM_H_
