#pragma once

#include "../components/behavior.h"
#include "../system.h"

namespace Engine::ECS
{
    struct ScriptSystem : System
    {
        ENGINE_INLINE ~ScriptSystem()
        {
            for(auto& e: ViewComponentOwners<ScriptComponent>())
            {
                auto& script = e.GetComponent<ScriptComponent>();
                ENGINE_DELETE(script.instance);
            }
        }

        ENGINE_INLINE void Start()
        {
            for(auto& e : ViewComponentOwners<ScriptComponent>())
            {
                auto& script = e.GetComponent<ScriptComponent>();
                ScriptProps props(e, m_registry, m_assets);
                script.instance = script.instantiate(props);
                script.instance->OnStart();
            }
        }

        ENGINE_INLINE void Update(float dt)
        {
            for(auto& e : ViewComponentOwners<ScriptComponent>())
            {
                e.GetComponent<ScriptComponent>().instance->OnUpdate(dt);
            }
        }

    };
}