#pragma once
#include "asset.h"

namespace engine
{
    struct AudioClip
    {
        Mix_Chunk* data = NULL;
        std::string filename;
    };

    struct AudioAsset : Asset
    {
        ENGINE_INLINE AudioAsset() = default;

        ENGINE_INLINE ~AudioAsset()
        {
            Mix_FreeChunk(instance.data);
        }

        AudioClip instance;
    };
}