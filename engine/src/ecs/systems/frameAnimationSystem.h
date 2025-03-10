#pragma once
#include "../components/graphics.h"
#include "../components/common.h"
#include "ecs/system.h"

namespace engine::ecs
{
    struct FrameAnimationSystem : System
    {
        ENGINE_INLINE void Update(float)
        {
            for(auto& e : ViewComponentOwners<AnimationComponent>())
            {
                auto& transformComp = e.GetComponent<TransformComponent>();
                auto& animComp = e.GetComponent<AnimationComponent>();
                
                auto& animation = m_assets->GetAsset<AnimationAsset>(animComp.animation)->instance;

                int index = (SDL_GetTicks64()/animation.speed) % animation.frames.size();
                auto& frame = m_assets->GetAsset<TextureAsset>(animation.frames[index])->instance;

                SDL_FRect dst
                {
                    transformComp.translate.x, transformComp.translate.y,
                    transformComp.scale.x * frame.width, transformComp.scale.y * frame.height
                };

                SDL_RenderCopyExF(m_renderer, frame.data, NULL, &dst, transformComp.rotation, NULL, animComp.flip);
            }

        }
    };
}