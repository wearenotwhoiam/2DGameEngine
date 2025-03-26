#pragma once
#include "scriptInstance.h"

namespace  Engine
{
    struct PlayerController : ScriptInstance
    {
        ENGINE_INLINE void OnStart()
        {
            ENGINE_INFO("Player Script started");
        }

        ENGINE_INLINE void OnCollision(ECS::Entity e)
        {
            ENGINE_INFO("Colliding with %d", e.GetID());
        }

        ENGINE_INLINE void OnUpdate(float dt)
        {
            auto& t = GetComponent<ECS::TransformComponent>();

            if(input::IsKey(SDL_SCANCODE_A))
            {
                t.translate.x -= (speed * dt);
            }
            if(input::IsKey(SDL_SCANCODE_D))
            {
                t.translate.x += (speed * dt);

            }
            if(input::IsKey(SDL_SCANCODE_W))
            {
                t.translate.y -= (speed * dt);

            }
            if(input::IsKey(SDL_SCANCODE_S))
            {
                t.translate.y += (speed * dt);
            }
        }

    private:
        float speed {300.f};
    };

}