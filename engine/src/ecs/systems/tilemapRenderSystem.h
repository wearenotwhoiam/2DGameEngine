#pragma once
#include "../system.h"
#include "../components/common.h"
#include "../components/graphics.h"

namespace engine::ecs
{
    struct TilemapRendererSystem : System
    {
        ENGINE_INLINE void Update(float)
        {
            for(auto& e: ViewComponentOwners<TilemapComponent>())
            {
                auto& transformComp = e.GetComponent<TransformComponent>();
                auto& tilemapComp = e.GetComponent<TilemapComponent>().tilemap;

                auto& tilemap = m_assets->GetAsset<TilemapAsset>(tilemapComp)->instance;

                for (auto& tileEntity : ViewComponentOwners<TileComponent>())
                {
                    //check if tile belongs to tilemap
                    auto& tile = tileEntity.GetComponent<TileComponent>();
                    if(tile.ownerTilemap != tilemapComp && !tilemap.tilesets.count(tile.tileset)) continue;

                    //tile position
                    float x = tile.offsetX + transformComp.translate.x;
                    float y = tile.offsetY + transformComp.translate.y;

                    //render tile
                    DrawTile(tile.tileset, x, y, tile.row, tile.col, tilemap.tileSize, tile.flip);
                }
            }   
        }
    private:
        ENGINE_INLINE void DrawTile(assetID tilesetID, float x, float y, int row, int col, int size, SDL_RendererFlip flip)
        {
            SDL_FRect dstRect = { x * size, y * size, size, size};
            SDL_Rect srcRect = { row * size, col * size, size, size};

            auto& tileset = m_assets->GetAsset<TextureAsset>(tilesetID)->instance;

            SDL_RenderCopyExF(m_renderer, tileset.data, &srcRect, &dstRect, 0, NULL, flip);

            SDL_RenderDrawRectF(m_renderer, &dstRect);
        }
    };

}