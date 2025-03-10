#pragma once

#include "math/vec2.h"

namespace engine::ecs
{
    struct InfoComponent
    {
        ENGINE_INLINE InfoComponent(const InfoComponent&) = default;
        ENGINE_INLINE InfoComponent() = default;

        uuid64 uuid = GenerateUUID();
        std::string name = "entity";
        std::string tag = "dafault";
    };

    struct TransformComponent
    {
        ENGINE_INLINE TransformComponent(const TransformComponent&) = default;
        ENGINE_INLINE TransformComponent() = default; 

        Vec2f translate = Vec2f(0.0f);
        Vec2f scale = Vec2f(1.0f);
        float rotation = 0.0f;
    };
}