
#ifndef re_reflection_API_H
#define re_reflection_API_H

#ifdef re_reflection_BUILT_AS_STATIC
#  define re_reflection_API
#  define RE_REFLECTION_NO_EXPORT
#else
#  ifndef re_reflection_API
#    ifdef re_reflection_EXPORTS
        /* We are building this library */
#      define re_reflection_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define re_reflection_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RE_REFLECTION_NO_EXPORT
#    define RE_REFLECTION_NO_EXPORT 
#  endif
#endif

#ifndef RE_REFLECTION_DEPRECATED
#  define RE_REFLECTION_DEPRECATED __declspec(deprecated)
#endif

#ifndef RE_REFLECTION_DEPRECATED_EXPORT
#  define RE_REFLECTION_DEPRECATED_EXPORT re_reflection_API RE_REFLECTION_DEPRECATED
#endif

#ifndef RE_REFLECTION_DEPRECATED_NO_EXPORT
#  define RE_REFLECTION_DEPRECATED_NO_EXPORT RE_REFLECTION_NO_EXPORT RE_REFLECTION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RE_REFLECTION_NO_DEPRECATED
#    define RE_REFLECTION_NO_DEPRECATED
#  endif
#endif

#endif /* re_reflection_API_H */
