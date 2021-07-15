#pragma once
#include <stdint.h>


namespace re_reflect
{
	namespace detail
	{
		template<class Type, size_t FieldNum, size_t FunctionNum, size_t TemplateNum = 0>
        struct ClassStorage;

		template<size_t ParamNum>
        struct FunctionStorage;

		
	}
	
    class Type {

    public:
        Type() noexcept
            : size(0)
            , hash(0)
        {}

        Type(int size,
            uint64_t hash,
            char const* name) noexcept
            : size(size)
            , hash(hash)
            , name(name)
        {}

        virtual bool IsClass() const noexcept { return false; }

        uint64_t Size() const noexcept
        {
            return size;
        }

        uint64_t Hash() const noexcept
        {
            return hash;
        }

        char const* Name() const noexcept
        {
            return name;
        }

        bool
            operator==(Type const& other) const noexcept
        {
            return hash == other.hash;
        }

        bool
            operator!=(Type const& other) const noexcept
        {
            return !(*this == other);
        }

    private:
        uint64_t size;
        uint64_t hash;
        char const* name{};
    };
	
}

