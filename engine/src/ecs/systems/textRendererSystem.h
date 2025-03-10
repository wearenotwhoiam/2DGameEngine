#pragma once
#include "../system.h"
#include "../components/graphics.h"
#include "../components/common.h"

namespace engine::ecs
{
    struct TextRendererSystem : System
    {
        ENGINE_INLINE void Update(float)
        {
            for(auto& e: ViewComponentOwners<TextComponent>())
            {
                auto& transformComp = e.GetComponent<TransformComponent>();
                auto& textComp = e.GetComponent<TextComponent>();
                
                auto& font = m_assets->GetAsset<FontAsset>(textComp.font)->instance;

                SDL_Surface* surface = NULL;
                surface = TTF_RenderText_Blended(font.data, textComp.text.c_str(), textComp.color);
                if(!surface)
                {
                    ENGINE_ERROR("%s", TTF_GetError());
                    continue;
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
                SDL_FreeSurface(surface);
                if(!texture)
                {
                    ENGINE_ERROR("%s", SDL_GetError());
                    continue;
                }

                int width, height;
                SDL_QueryTexture(texture, NULL, NULL, &width, &height);

                SDL_FRect dst
                {
                    transformComp.translate.x, transformComp.translate.y,
                    width * transformComp.scale.x, height * transformComp.scale.y
                };

                SDL_RenderCopyExF(m_renderer, texture, NULL, &dst, transformComp.rotation, NULL, textComp.flip);

                SDL_DestroyTexture(texture);
            }
        }
    };
}