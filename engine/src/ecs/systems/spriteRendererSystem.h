#pragma once
#include "ECS/system.h"
#include "components/graphics.h"
#include "components/common.h"

namespace Engine::ECS
{
    struct SpriteRendererSystem : System
    {
        ENGINE_INLINE void Update(float)
        {
            for(auto& e : ViewComponentOwners<SpriteComponent>())
            {
                //Get Components
                auto& transformComp = e.GetComponent<TransformComponent>();
                auto& spriteComp = e.GetComponent<SpriteComponent>();

                //Get Texture
                auto& sprite = m_assets->GetAsset<TextureAsset>(spriteComp.sprite)->instance;

                //Destination
                SDL_FRect dst
                {
                    transformComp.translate.x,transformComp.translate.y,
                    sprite.width * transformComp.scale.x, sprite.height * transformComp.scale.y
                };
                
                //Render Sprite
                SDL_RenderCopyExF(m_renderer, sprite.data, NULL, &dst, transformComp.rotation, NULL, spriteComp.flip);

            }
        }
    };
}