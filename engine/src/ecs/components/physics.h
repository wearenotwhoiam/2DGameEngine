#pragma once
#include "physics/rigidbody2D.h"

namespace Engine::ECS
{
    struct RigidbodyComponent
    {
        ENGINE_INLINE RigidbodyComponent(const RigidbodyComponent&) = default;
        ENGINE_INLINE RigidbodyComponent() = default;

        bool disabled {false};
        RigidBody2D body;
    };

    struct ColliderComponent
    {
        ENGINE_INLINE ColliderComponent(const ColliderComponent&) = default;
        ENGINE_INLINE ColliderComponent() = default;
        SDL_FRect collider {0.f,0.f,64.f,64.f};
        bool disabled{false};
    };
}