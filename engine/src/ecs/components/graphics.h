#pragma once
#include "../assets/asset.h"

namespace engine::ecs
{
    struct SpriteComponent
    {
        ENGINE_INLINE SpriteComponent(const SpriteComponent&) = default;
        ENGINE_INLINE SpriteComponent() = default;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        assetID sprite = INVALID_ID;
    };

    struct TextComponent
    {
        ENGINE_INLINE TextComponent(const TextComponent&) = default;
        ENGINE_INLINE TextComponent() = default;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_Color color = {0,0,0,255};
        assetID font = INVALID_ID;
        std::string text;
    };

    struct AnimationComponent
    {
        ENGINE_INLINE AnimationComponent(const AnimationComponent&) = default;
        ENGINE_INLINE AnimationComponent() = default;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        assetID animation = INVALID_ID;
    };

    struct TilemapComponent
    {
        ENGINE_INLINE TilemapComponent(const TilemapComponent&) = default;
        ENGINE_INLINE TilemapComponent() = default;
        assetID tilemap = INVALID_ID;
    };

    struct TileComponent
    {
        ENGINE_INLINE TileComponent(const TileComponent&) = default;
        ENGINE_INLINE TileComponent() = default;

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        assetID ownerTilemap = INVALID_ID;
        assetID tileset = INVALID_ID;
        float offsetX, offsetY = 0;
        int row, col = 0;
    };
}