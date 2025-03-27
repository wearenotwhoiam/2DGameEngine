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
#include "../scripts/scrollingGround.h"
#include "../scripts/pipeSpawner.h"

#include "assets/registry.h"

namespace Engine::ECS
{
    struct Scene
    {
        ENGINE_INLINE Scene(SDL_Renderer* renderer): m_renderer(renderer)
        {
            RegisterSystem<ECS::ScriptSystem>();
           // RegisterSystem<ECS::TestSystem>();
            RegisterSystem<ECS::RigidbodySystem>();
            RegisterSystem<ECS::SpriteRendererSystem>();
            //RegisterSystem<ECS::TextRendererSystem>();
            //RegisterSystem<ECS::FrameAnimationSystem>();
            //RegisterSystem<ECS::TilemapRendererSystem>();
            
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
            SetupScene();
            for(auto& sys : m_systems) {sys->Start();}
        }

        ENGINE_INLINE void SetupScene()
        {
            //Obstacle Sprites
            auto pipeSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/pipe.png", "pipeSprite", m_renderer);

            //Text Font
            auto fontSprite = m_assets.LoadFont("C:/GameDev/C++/2DGameEngine/resources/font.ttf", "font", 30);

            //Background Entity
            auto bgEntity = AddEntity("background");
            auto bgSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/bg.png", "bg", m_renderer);
            bgEntity.AddComponent<SpriteComponent>().sprite = bgSprite->id;

            //Spawner 
            auto spawner = AddEntity("spawner");
            auto& spawnerScript = spawner.AddComponent<ScriptComponent>();
            spawnerScript.BindScript<PipeSpawner>();
            spawnerScript.name = "piperSpawner";

            SetupScrollingGround();
            SetupPlayer();
        }

        ENGINE_INLINE void SetupPlayer()
        {
            //Player Sprites
            auto flyingSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/fly.png", "flyingSprite", m_renderer);
            auto deadSprite = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/dead.png", "deadSprite", m_renderer);

            auto player = AddEntity("player");
            auto& playerScript = player.AddComponent<ECS::ScriptComponent>();
            playerScript.name = "PlayerController";
            playerScript.BindScript<PlayerController>();

            auto& playerTrans = player.GetComponent<TransformComponent>();
            playerTrans.translate = Vec2f(126,360);
            playerTrans.scale = Vec2f(0.5f);

            auto& playerRB = player.AddComponent<RigidbodyComponent>();
            playerRB.body.gravityScale = 25.f;

            player.AddComponent<SpriteComponent>().sprite = flyingSprite->id;

            auto& playerCollider = player.AddComponent<ColliderComponent>();
            playerCollider.collider = {0,0, 58, 38};
        }

        ENGINE_INLINE void SetupScrollingGround()
        {
            //Ground Entity
            auto grEntity = AddEntity("ground");
            ////Scripting
            
            auto& grScrollScript = grEntity.AddComponent<ScriptComponent>();
            grScrollScript.BindScript<ScrollingGround>();
            grScrollScript.name = "scrollingGround";
            ////Transform
            auto& grTransform = grEntity.AddComponent<TransformComponent>();
            grTransform.translate = Vec2f(0.0f, 620);
            ////RigidBody
            grEntity.AddComponent<RigidbodyComponent>().body.velocity.x = -100.f;
            ////Sprite
            auto grAsset = m_assets.LoadTexture("C:/GameDev/C++/2DGameEngine/resources/ground.png", "ground", m_renderer);
            auto& grSprite = grEntity.AddComponent<SpriteComponent>().sprite = grAsset->id;
            ////Collider
            auto& grCollider = grEntity.AddComponent<ColliderComponent>();
            grCollider.collider = {0, 0, (float)grAsset->instance.width, (float)grAsset->instance.height};
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