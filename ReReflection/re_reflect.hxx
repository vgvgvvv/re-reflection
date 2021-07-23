/* ========================================================================= */
/* Copyright (C) 2017-2018 Arvid Gerstmann. All rights reserved.             */
/* ========================================================================= */
#pragma once

#include <stdint.h>
#include <string.h>
#include <stddef.h>

namespace re_reflect
{

/* ========================================================================= */
/* Reflect Macros                                                            */
/* ========================================================================= */
#ifdef USING_REFECTION
    #define CLASS(...) __attribute__((annotate("reflect-class;" #__VA_ARGS__)))
    #define UNION(...) __attribute__((annotate("reflect-class;" #__VA_ARGS__)))
    #define PROPERTY(...) __attribute__((annotate("reflect-property;" #__VA_ARGS__)))
    #define FUNCTION(...) __attribute__((annotate("reflect-function;" #__VA_ARGS__)))
    #define META_OBJECT
#else /* else USING_REFECTION */
    #define CLASS(...) 
    #define UNION(...) 
    #define PROPERTY(...)
    #define FUNCTION(...)
    #define META_OBJECT \
        friend struct PrimitiveResolver; \
        static constexpr bool IsReflected = true; \
        template<class T> \
        friend constexpr bool AfterSerialize(T *) noexcept; \
        template<class T> \
        friend constexpr bool BeforeSerialize(T *) noexcept; \
        template<class T> \
        friend re_reflect::Class const *re_reflect::detail::GetClassImpl(re_reflect::ClassTag<T>) noexcept;
#endif /* USING_REFECTION */


/* ========================================================================= */
/* Traits                                                                    */
/* ========================================================================= */
template<class T>
struct IsSerializable;

template<class T>
struct HasBeforeSerialize;

template<class T>
struct HasAfterSerialize;

template<class T>
struct HasCustomSerialize;

template<class T>
struct HasCustomDump;


/* ========================================================================= */
/* Public API                                                                */
/* ========================================================================= */
class Class;
class Type;
template<class T>
struct TypeTag {};
template<class T>
struct ClassTag {};


template<class T>
Class const *
GetClass() noexcept;

template<class T>
Type const *
GetType() noexcept;


/* ========================================================================= */
/* Serialization                                                             */
/* ========================================================================= */
template<class T, class Serializer>
struct Serialize;


/* ========================================================================= */
/* Helper Functions                                                          */
/* ========================================================================= */
template<class T, class Serializer>
constexpr bool
AfterSerialize(T *_this) noexcept
{
    if constexpr (HasAfterSerialize<T>::value)
        return _this->AfterSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
BeforeSerialize(T *_this) noexcept
{
    if constexpr (HasBeforeSerialize<T>::value)
        return _this->BeforeSerialize();
    return true;
}

template<class T, class Serializer>
constexpr bool
CustomSerialize(T *_this) noexcept
{
    if constexpr (HasCustomSerialize<T>::value)
        return _this->Serialize();
    return true;
}

} /* namespace re_reflect */


/* ========================================================================= */
/* Detail                                                                    */
/* ========================================================================= */
#include "re_reflect_detail.hxx"

