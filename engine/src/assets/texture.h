#pragma once
#include "asset.h"

namespace engine
{
    struct Texture
    {
        SDL_Texture* data = NULL;
        std::string filename;
        int height = 0;
        int width = 0;
    };

    struct TextureAsset : Asset
    {
        ENGINE_INLINE TextureAsset() = default;

        ENGINE_INLINE ~TextureAsset() 
        {
            SDL_DestroyTexture(instance.data);
        }
        
        Texture instance;
    };

}