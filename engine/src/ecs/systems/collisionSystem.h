#pragma once
#include "../system.h"
#include "../components/physics.h"
#include "../components/common.h"
#include "../components/behavior.h"

namespace Engine::ECS
{
    struct CollisionSystem : System
    {
        ENGINE_INLINE void Start()
        {
            for(auto& e: ViewComponentOwners<ColliderComponent>())
            {
                auto trComp = e.GetComponent<TransformComponent>();
                auto colComp = e.GetComponent<ColliderComponent>();
                
                colComp.collider.x = trComp.translate.x;
                colComp.collider.y = trComp.translate.y;
            }
        }

        ENGINE_INLINE void Update(float)
        {
            auto entities = ViewComponentOwners<ColliderComponent>();
            for(auto& e : entities)
            {
                auto& trComp = e.GetComponent<TransformComponent>();
                auto& c1 = e.GetComponent<ColliderComponent>();
                
                c1.collider.x = trComp.translate.x;
                c1.collider.y = trComp.translate.y; 

                if(c1.disabled) continue;

                for(auto&o: entities)
                {
                    if(o==e)continue;
                    auto& c2 = o.GetComponent<ColliderComponent>();
                    if(CheckCollision(c1.collider, c2.collider))
                    {
                        ENGINE_INFO("Collision: %d->%d", e.GetID(), o.GetID());
                        if(e.HasComponent<ScriptComponent>())
                        {
                            auto& script = e.GetComponent<ScriptComponent>();
                            script.instance->OnCollision(o);
                        }
                        
                    }
                }
            }
        }

    private:
        bool CheckCollision(const SDL_FRect&a, const SDL_FRect&b)
        {
            return ((a.x < b.x + b.w) && (a.x + a.w > b.x) &&
                    (a.y < b.y + b.h) && (a.y + a.h > b.y));
        }
    };
} 
