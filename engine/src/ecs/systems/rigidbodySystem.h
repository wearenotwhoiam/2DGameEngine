#pragma once
#include "../system.h"
#include "../components/physics.h"
#include "../components/common.h"

namespace engine::ecs
{
    struct RigidbodySystem: System
    {
        ENGINE_INLINE void Update(float dt)
        {
            for(auto& e : ViewComponentOwners<RigidbodyComponent>())
            {
                auto& rbComp = e.GetComponent<RigidbodyComponent>();
                if(rbComp.disabled) continue;

                auto& trComp = e.GetComponent<TransformComponent>();
                Vec2f force = Vec2f(0.f, rbComp.body.gravityScale * 9.8f);
                rbComp.body.velocity += (rbComp.body.force + force) * dt;
                trComp.translate += rbComp.body.velocity * dt;
            }
        }
    };
}