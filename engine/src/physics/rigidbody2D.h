#pragma once
#include "../math/vec2.h"

namespace engine
{
    struct RigidBody2D
    {
        ENGINE_INLINE void SetForce(const Vec2f& f){force =f;}
        ENGINE_INLINE void SetForceX(float x) {force.x;}
        ENGINE_INLINE void SetForceY(float y) {force.y;}

        float gravityScale {0.f};
        Vec2f velocity {0.f,0.f};
        Vec2f force {0.f, 0.f};
    };
}