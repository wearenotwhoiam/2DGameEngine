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
            int w1,w2,h1,h2 {0};
            auto spr1 = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/1.png", "1", m_renderer);
            SDL_QueryTexture(spr1->instance.data, nullptr, nullptr, &w1, &h1);
            auto spr2 = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/2.png", "2", m_renderer);
            SDL_QueryTexture(spr2->instance.data, nullptr, nullptr, &w2, &h2);

            auto e1 = AddEntity("Entity1");
            e1.AddComponent<ScriptComponent>().Bind<PlayerController>();
            e1.GetComponent<TransformComponent>().translate.x = 500;
            e1.AddComponent<SpriteComponent>().sprite = spr1->id;
            e1.AddComponent<ColliderComponent>().collider = {1000, 0, (float)w1, (float)h1};

            auto e2 = AddEntity("Entity2");
            e2.AddComponent<SpriteComponent>().sprite = spr2->id;
            e2.AddComponent<ColliderComponent>().collider = {0, 0, (float)w2, (float)h2};

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


#if 0
           //load texture asset
           auto sprite = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/test.png", "test", m_renderer);
           //Create Entity
           ECS::Entity entity = AddEntity("entity");
           //Add Sprite Component
           entity.AddComponent<ECS::SpriteComponent>().sprite = sprite->id;

           //Font
           auto font = m_assets.LoadFont("C:/GameDev/C++/ECS/engine/src/assets/data-latin.ttf", "ft", 30);

           ECS::Entity fontEntity = AddEntity("FontEntity");
           auto& txtComp = fontEntity.AddComponent<ECS::TextComponent>();
           txtComp.text = "HJAJAJAJAJAJ";
           txtComp.font = font->id;

           //animation
           auto frame1 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/1.png", "1", m_renderer);
           auto frame2 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/2.png", "2", m_renderer);
           auto frame3 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/3.png", "3", m_renderer);

           auto animation = m_assets.AddAsset<AnimationAsset>("dance");

           animation->instance.frames.push_back(frame1->id);
           animation->instance.frames.push_back(frame2->id);
           animation->instance.frames.push_back(frame3->id);
           animation->instance.speed = 300;

           ECS::Entity animationEntity = AddEntity("AnimationEntity");
           auto& a = animationEntity.AddComponent<ECS::AnimationComponent>();
           a.animation = animation->id;

           //load texture
           auto texture = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/tex.png", "", m_renderer);
           if(!texture) return;

           //create tilemap asset
           auto tm = m_assets.AddAsset<TilemapAsset>("tilemap");
           tm->instance.tilesets.insert(texture->id);
           tm->instance.colCount = 16;
           tm->instance.rowCount = 8;
           tm->instance.tileSize = 64;
           
           //tilemap entity
          AddEntity("tilemap").AddComponent<TilemapComponent>().tilemap = tm->id;

           //turn image into multiple entities
           for(int col=0; col < tm->instance.colCount; col++)
           {
               for(int row=0; row < tm->instance.rowCount; row++)
               {
                   ECS::Entity e = AddEntity("tile");
                   auto& tile = e.AddComponent<TileComponent>();
                   tile.tileset = texture->id;
                   tile.ownerTilemap= tm->id;
                   tile.offsetX = col;
                   tile.offsetY = row;
                   tile.row = row;
                   tile.col = col;
               }
           }


           auto sprite = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/1.png", "1", m_renderer);

           auto entity = AddEntity("rigidbody");
           entity.AddComponent<SpriteComponent>().sprite = sprite->id;
           auto& rigidbody = entity.AddComponent<RigidbodyComponent>();
           rigidbody.body.gravityScale = 1.f;

#endif