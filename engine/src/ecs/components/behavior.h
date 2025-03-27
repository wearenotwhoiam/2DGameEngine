#pragma once
#include "../../scripts/scriptInstance.h"

namespace Engine::ECS
{
    struct ScriptComponent
    {
        ENGINE_INLINE ScriptComponent(const ScriptComponent&) = default;
        ENGINE_INLINE ScriptComponent() = default;

        template<typename T>
        ENGINE_INLINE void BindScript()
        {
            instantiate = [](const ScriptProps& props)
            {
                auto script = static_cast<ScriptInstance*>(new T());
                script->Initialize(props);
                return script;
            };
        }

        ScriptInstance* instance {NULL};
        ScriptInstantiator instantiate;
        std::string name;
    };
}