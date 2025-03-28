#pragma once
#include "asset.h"

namespace Engine
{
    struct AudioClip
    {
        Mix_Chunk* data = NULL;
        std::string filename;
    };

    struct MusicTrack
    {
        Mix_Music* data = NULL;
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

    struct MusicAsset : Asset
    {
        ENGINE_INLINE MusicAsset() = default;

        ENGINE_INLINE ~MusicAsset()
        {
            Mix_FreeMusic(instance.data);
        }

        MusicTrack instance;
    };
}