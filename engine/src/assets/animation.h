#pragma once
#include "asset.h"

namespace engine
{
    struct Animation
    {
        std::vector<assetID> frames;
        int speed = 100;
    };

    struct AnimationAsset : Asset
    {
        ENGINE_INLINE AnimationAsset() = default;
        Animation instance;
    };
}