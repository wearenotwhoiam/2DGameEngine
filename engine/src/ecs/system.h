#pragma once
#include "entity.h"
#include "assets/registry.h"

namespace engine::ecs
{
    struct System
    {
        ENGINE_INLINE virtual ~System() = default;

        ENGINE_INLINE void Prepare(Registry* reg, SDL_Renderer* ren, AssetRegistry* as)
        {
            this->m_registry = reg;
            this->m_renderer = ren;
            this->m_assets = as;
        }

        template<typename T>
        ENGINE_INLINE auto ViewComponentOwners()
        {
            std::vector<Entity>entities;
            for(auto& e: m_registry->ViewComponentOwners<T>())
            {
                entities.push_back(Entity(e, m_registry));
            }
            return entities;
        }

        ENGINE_INLINE virtual void Update(float) {}
        ENGINE_INLINE virtual void Start() {}
        
    protected:
        SDL_Renderer* m_renderer = NULL;
        Registry* m_registry = NULL;
        AssetRegistry* m_assets = NULL;
    };
}