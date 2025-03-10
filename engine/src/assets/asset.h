#pragma once
#include "../pch.h"

namespace engine
{
    using assetTypeID = uint32_t;
    using assetID = uuid64;

    struct Asset
    {
        ENGINE_INLINE virtual ~Asset() = default;
        assetID id = GenerateUUID();
        std::string name;
    };
}