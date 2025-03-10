#pragma once 
#include "asset.h"

namespace engine
{
    struct Font
    {
        TTF_Font* data = NULL;
        std::string filename;
        int size = 20;
    };

    struct FontAsset : Asset
    {
        ENGINE_INLINE FontAsset() = default;
        ENGINE_INLINE ~FontAsset()
        {
            TTF_CloseFont(instance.data);
        }

        Font instance;
    };
}