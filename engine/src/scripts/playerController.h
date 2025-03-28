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

        ENGINE_INLINE void OnCollision(ECS::entityID e)
        {
            ENGINE_INFO("Colliding with %d", e);
            PlayAudio("boom");
            auto& deadSprite = GetComponent<ECS::SpriteComponent>();
            deadSprite.sprite = GetAsset<TextureAsset>("deadSprite")->id;

            GetComponent<ECS::ColliderComponent>().disabled = true;
            GetComponent<ECS::RigidbodyComponent>().disabled = true;
        }

        ENGINE_INLINE void OnUpdate(float dt)
        {
            auto& rb = GetComponent<ECS::RigidbodyComponent>();

            if(input::IsKey(SDL_SCANCODE_SPACE))
            {
                rb.body.SetForceY(-750.f);
            }
            else
            {
                rb.body.SetForceY(0.f);
            }
        }

    private:
        float speed {300.f};
    };

}