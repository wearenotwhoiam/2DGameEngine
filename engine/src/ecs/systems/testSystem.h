#include "../system.h"
#include "../components/common.h"

namespace engine::ecs
{
    struct TestSystem : System
    {
        void Update(float dt)
        {
            for(auto e: ViewComponentOwners<TransformComponent>())
            {
                auto& transComp = e.GetComponent<TransformComponent>();
                ENGINE_INFO("id:[%d], x:%f", e.GetID(), transComp.translate.x++);
            }
        }
    };
}