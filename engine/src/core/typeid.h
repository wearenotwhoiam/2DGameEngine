#pragma once
#include "../pch.h"

namespace engine
{
    ENGINE_INLINE const uint32_t GetTypeID()
    {
        static uint32_t type = 1u;
        return type++;
    }

    template<typename T>
    ENGINE_INLINE const uint32_t TypeID()
    {
        static const uint32_t type = GetTypeID();
        return type;
    }
}