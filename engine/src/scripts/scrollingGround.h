#pragma once

#include "scriptInstance.h"
namespace Engine
{
    struct ScrollingGround : ScriptInstance
    {
        ENGINE_INLINE void OnStart()
        {
            width = GetAsset<TextureAsset>("ground")->instance.width;
        }
        ENGINE_INLINE void OnUpdate(float dt)
        {
            auto& transComp = GetComponent<ECS::TransformComponent>();

            if(transComp.translate.x + width < 380)
            {
                transComp.translate.x = 0.0;
            }
        }
    private:
        float width;
    };


}