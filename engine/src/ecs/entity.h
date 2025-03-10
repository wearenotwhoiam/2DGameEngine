#pragma once
#include "registry.h"

namespace engine::ecs
{
    struct Entity
    {
        //Constructors
        ENGINE_INLINE Entity(Registry* r) : registry(r)
        {
            entity = r->AddEntity();
        }
        ENGINE_INLINE Entity(entityID e, Registry* r) : entity(e), registry(r) {}
        ENGINE_INLINE operator entityID() const { return entity; }
        ENGINE_INLINE Entity() = default;

        //Add Component to Entity
        template<typename T, typename... Args>
        ENGINE_INLINE T& AddComponent(Args&&... args)
        {
            return registry->AddComponent<T>(entity, std::forward<Args>(args)...);
        }
        //Get Specific Component
        template<typename T>
        ENGINE_INLINE T& GetComponent()
        {
            return registry->GetComponent<T>(entity);
        }
        //Remove Component
        template<typename T>
        ENGINE_INLINE void RemoveComponent()
        {
            registry->RemoveComponent<T>(entity);
        }
        //Check if entity currently owns specific component
        template<typename T>
        ENGINE_INLINE bool HasComponent()
        {
            return Registry->HasComponent<T>(entity);
        }
        //Check if entity is alive
        template<typename T>
        ENGINE_INLINE bool IsAlive()
        {
            return registry && registry->IsAlive(entity);
        }

        ENGINE_INLINE entityID GetID() const { return entity; }
        ENGINE_INLINE void Destroy() { registry->DestroyEntity(entity); }
        private:
            entityID entity = INVALID_ID;
            Registry* registry = NULL;
    };
}