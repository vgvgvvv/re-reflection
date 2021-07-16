
#ifndef ReReflection_API_H
#define ReReflection_API_H

#ifdef ReReflection_BUILT_AS_STATIC
#  define ReReflection_API
#  define REREFLECTION_NO_EXPORT
#else
#  ifndef ReReflection_API
#    ifdef ReReflection_EXPORTS
        /* We are building this library */
#      define ReReflection_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define ReReflection_API __declspec(dllimport)
#    endif
#  endif

#  ifndef REREFLECTION_NO_EXPORT
#    define REREFLECTION_NO_EXPORT 
#  endif
#endif

#ifndef REREFLECTION_DEPRECATED
#  define REREFLECTION_DEPRECATED __declspec(deprecated)
#endif

#ifndef REREFLECTION_DEPRECATED_EXPORT
#  define REREFLECTION_DEPRECATED_EXPORT ReReflection_API REREFLECTION_DEPRECATED
#endif

#ifndef REREFLECTION_DEPRECATED_NO_EXPORT
#  define REREFLECTION_DEPRECATED_NO_EXPORT REREFLECTION_NO_EXPORT REREFLECTION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef REREFLECTION_NO_DEPRECATED
#    define REREFLECTION_NO_DEPRECATED
#  endif
#endif

#endif /* ReReflection_API_H */
