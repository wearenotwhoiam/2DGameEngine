#pragma once
#include "systems/testSystem.h"
#include "systems/spriteRendererSystem.h"
#include "systems/textRendererSystem.h"
#include "systems/frameAnimationSystem.h"
#include "systems/tilemapRenderSystem.h"
#include "systems/rigidbodySystem.h"
#include "systems/collisionSystem.h"
#include "systems/scriptSystem.h"
#include "../scripts/playerController.h"

#include "assets/registry.h"

namespace Engine::ECS
{
    struct Scene
    {
        ENGINE_INLINE Scene(SDL_Renderer* renderer): m_renderer(renderer)
        {
           // RegisterSystem<ECS::TestSystem>();
            RegisterSystem<ECS::RigidbodySystem>();
            RegisterSystem<ECS::SpriteRendererSystem>();
            RegisterSystem<ECS::TextRendererSystem>();
            RegisterSystem<ECS::FrameAnimationSystem>();
            RegisterSystem<ECS::TilemapRendererSystem>();
            RegisterSystem<ECS::ScriptSystem>();
            RegisterSystem<ECS::CollisionSystem>();
        }

        ENGINE_INLINE ~Scene()
        {
            for(auto& s: m_systems) {ENGINE_DELETE(s);}
            m_registry.Clear();
            m_systems.clear();
        }

        ENGINE_INLINE ECS::Entity AddEntity(const std::string name)
        {
            auto entity = ECS::Entity(&m_registry);
            entity.AddComponent<InfoComponent>().name = name;
            entity.AddComponent<TransformComponent>();
            return entity;
        }

        ENGINE_INLINE void Update(float dt)
        {
            for(auto& sys : m_systems) {sys->Update(dt);}

            SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
            for(auto& e : m_registry.ViewComponentOwners<ColliderComponent>())
            {
                auto& c = m_registry.GetComponent<ColliderComponent>(e);
                SDL_RenderDrawRectF(m_renderer, &c.collider);
            }

            SDL_SetRenderDrawColor(m_renderer, 255,255,255,255);

        }

        ENGINE_INLINE void Start()
        {
            //Player Sprites
            auto flyingSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/fly.png", "flyingSprite", m_renderer);
            auto deadSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/dead.png", "deadSprite", m_renderer);

            //Obstacle Sprites
            auto pipeSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/pipe.png", "pipeSprite", m_renderer);

            //BG Texture
            auto bgSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/bg.png", "bg", m_renderer);
            auto groundSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/ground.png", "ground", m_renderer);

            //Text Font
            auto fontSprite = m_assets.LoadFont("C:/GameDev/C++/2DGameEngine/resources/font..ttf", "font", 30);

            //Background Entity
            auto bgEntity = AddEntity("Background");
            bgEntity.AddComponent<SpriteComponent>().sprite = bgSprite->id;
            
            for(auto& sys : m_systems) {sys->Start();}
        }

        template<typename T>
        ENGINE_INLINE void RegisterSystem()
        {
            ENGINE_STATIC_ASSERT(std::is_base_of<ECS::System, T>::value);
            auto newSystem = new T();
            newSystem->Prepare(&m_registry, m_renderer, &m_assets);
            this->m_systems.push_back(newSystem);
        }

    private:
        std::vector<ECS::System*> m_systems;
        SDL_Renderer* m_renderer = NULL;
        ECS::Registry m_registry;
        AssetRegistry m_assets;
    };
}