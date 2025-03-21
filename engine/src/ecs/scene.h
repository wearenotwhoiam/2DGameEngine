#pragma once
#include "systems/testSystem.h"
#include "systems/spriteRendererSystem.h"
#include "systems/textRendererSystem.h"
#include "systems/frameAnimationSystem.h"
#include "systems/tilemapRenderSystem.h"
#include "assets/registry.h"

namespace engine::ecs
{
    struct Scene
    {
        ENGINE_INLINE Scene(SDL_Renderer* renderer): m_renderer(renderer)
        {
           // RegisterSystem<ecs::TestSystem>();
            RegisterSystem<ecs::SpriteRendererSystem>();
            RegisterSystem<ecs::TextRendererSystem>();
            RegisterSystem<ecs::FrameAnimationSystem>();
            RegisterSystem<ecs::TilemapRendererSystem>();
        }

        ENGINE_INLINE ~Scene()
        {
            for(auto& s: m_systems) {ENGINE_DELETE(s);}
            m_registry.Clear();
            m_systems.clear();
        }

        ENGINE_INLINE ecs::Entity AddEntity(const std::string name)
        {
            auto entity = ecs::Entity(&m_registry);
            entity.AddComponent<InfoComponent>().name = name;
            entity.AddComponent<TransformComponent>();
            return entity;
        }

        ENGINE_INLINE void Update(float dt)
        {
            SDL_SetRenderDrawColor(m_renderer, 255,255,255,255);
            for(auto& sys : m_systems) {sys->Update(dt);}
        }

        ENGINE_INLINE void Start()
        {
            // //load texture asset
            // auto sprite = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/test.png", "test", m_renderer);
            // //Create Entity
            // ecs::Entity entity = AddEntity("entity");
            // //Add Sprite Component
            // entity.AddComponent<ecs::SpriteComponent>().sprite = sprite->id;

            // //Font
            // auto font = m_assets.LoadFont("C:/GameDev/C++/ECS/engine/src/assets/data-latin.ttf", "ft", 30);

            // ecs::Entity fontEntity = AddEntity("FontEntity");
            // auto& txtComp = fontEntity.AddComponent<ecs::TextComponent>();
            // txtComp.text = "HJAJAJAJAJAJ";
            // txtComp.font = font->id;

            // //animation
            // auto frame1 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/1.png", "1", m_renderer);
            // auto frame2 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/2.png", "2", m_renderer);
            // auto frame3 = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/3.png", "3", m_renderer);

            // auto animation = m_assets.AddAsset<AnimationAsset>("dance");

            // animation->instance.frames.push_back(frame1->id);
            // animation->instance.frames.push_back(frame2->id);
            // animation->instance.frames.push_back(frame3->id);
            // animation->instance.speed = 300;

            // ecs::Entity animationEntity = AddEntity("AnimationEntity");
            // auto& a = animationEntity.AddComponent<ecs::AnimationComponent>();
            // a.animation = animation->id;

            //load texture
            auto texture = m_assets.LoadTexture("C:/GameDev/C++/ECS/engine/src/assets/tex.png", "", m_renderer);
//            if(!texture) return;

            //create tilemap asset
            auto tm = m_assets.AddAsset<TilemapAsset>("tilemap");
            tm->instance.tilesets.insert(texture->id);
            tm->instance.colCount = 16;
            tm->instance.rowCount = 8;
            tm->instance.tileSize = 64;

            // ecs::Entity tilemap = AddEntity("tilemap");
            // tilemap.AddComponent<TilemapComponent>().tilemap = tm->id;

            //tilemap entity
           AddEntity("tilemap").AddComponent<TilemapComponent>().tilemap = tm->id;

            //turn image into multiple entities
            for(int col=0; col < tm->instance.colCount; col++)
            {
                for(int row=0; row < tm->instance.rowCount; row++)
                {
                    ecs::Entity e = AddEntity("tile");
                    auto& tile = e.AddComponent<TileComponent>();
                    tile.tileset = texture->id;
                    tile.ownerTilemap= tm->id;
                    tile.offsetX = col;
                    tile.offsetY = row;
                    tile.row = row;
                    tile.col = col;
                }
            }

            for(auto& sys : m_systems) {sys->Start();}
        }

        template<typename T>
        ENGINE_INLINE void RegisterSystem()
        {
            ENGINE_STATIC_ASSERT(std::is_base_of<ecs::System, T>::value);
            auto newSystem = new T();
            newSystem->Prepare(&m_registry, m_renderer, &m_assets);
            this->m_systems.push_back(newSystem);
        }

    private:
        std::vector<ecs::System*> m_systems;
        SDL_Renderer* m_renderer = NULL;
        ecs::Registry m_registry;
        AssetRegistry m_assets;
    };
}