#pragma once
#include "registry.h"

namespace Engine::ECS
{
    struct Entity
    {
        //Constructors
        ENGINE_INLINE Entity(Registry* r) : m_registry(r)
        {
            entity = r->AddEntity();
        }
        ENGINE_INLINE Entity(entityID e, Registry* r) : entity(e), m_registry(r) {}
        ENGINE_INLINE operator entityID() const { return entity; }
        ENGINE_INLINE Entity() = default;

        //Add Component to Entity
        template<typename T, typename... Args>
        ENGINE_INLINE T& AddComponent(Args&&... args)
        {
            return m_registry->AddComponent<T>(entity, std::forward<Args>(args)...);
        }
        //Get Specific Component
        template<typename T>
        ENGINE_INLINE T& GetComponent()
        {
            return m_registry->GetComponent<T>(entity);
        }
        //Remove Component
        template<typename T>
        ENGINE_INLINE void RemoveComponent()
        {
            m_registry->RemoveComponent<T>(entity);
        }
        //Check if entity currently owns specific component
        template<typename T>
        ENGINE_INLINE bool HasComponent()
        {
            return m_registry->HasComponent<T>(entity);
        }
        //Check if entity is alive
        ENGINE_INLINE bool IsAlive() const
        {
            return m_registry && m_registry->IsAlive(entity);
        }

        ENGINE_INLINE entityID GetID() const { return entity; }
        ENGINE_INLINE void Destroy() { m_registry->DestroyEntity(entity); }
        private:
            entityID entity = INVALID_ID;
            Registry* m_registry = NULL;

            //std::unordered_map<std::string, std::unique_ptr<ScriptInstance>> scripts;
    };
}