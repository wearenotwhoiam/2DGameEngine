#pragma once
#include "asset.h"

namespace engine
{
    struct Tilemap
    {
        std::set<assetID> tilesets;
        int colCount = 0;
        int rowCount = 0;
        int tileSize = 0;
    };

    struct TilemapAsset : Asset
    {
        ENGINE_INLINE TilemapAsset() = default;
        Tilemap instance;
    };
}