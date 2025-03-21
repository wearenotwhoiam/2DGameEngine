#pragma once
#include "physics/rigidbody2D.h"

namespace engine::ecs
{
    struct RigidbodyComponent
    {
        ENGINE_INLINE RigidbodyComponent(const RigidbodyComponent&) = default;
        ENGINE_INLINE RigidbodyComponent() = default;

        bool disabled {false};
        RigidBody2D body;
    };
}