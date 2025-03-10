#pragma once

#include "ecs.h"

namespace engine::ecs
{
    struct Registry
    {
        ENGINE_INLINE void Clear()
        {
            for(auto& [c, a] : m_componentArrays) ENGINE_DELETE(a);
            m_componentArrays.clear();
            m_signatures.clear();
            m_nextID = INVALID_ID;
        }

        ENGINE_INLINE entityID AddEntity()
        {
            entityID entity = m_nextID++;
            m_signatures[entity] = signature();
            return entity;
        }

        ENGINE_INLINE void DestroyEntity(entityID entity)
        {
            for(auto& [c, a] : m_componentArrays) a->Erase(entity);
            m_signatures.erase(entity);
        }

        ENGINE_INLINE bool IsAlive(entityID entity) const
        {
            return m_signatures.count(entity);
        }

        template <typename T> ENGINE_INLINE entityList ViewComponentOwners()
        {
            entityList list;
            for (auto& [entity, signature] : m_signatures)
            {
                if(signature.count(typeid(T).hash_code()))
                {
                    list.insert(entity);
                    continue;
                }
            }
            return list;
        }
        
        template <typename T> 
        ENGINE_INLINE T& GetComponent(entityID entity)
        {
            ENGINE_ASSERT(m_signatures.count(entity) && "Entity does not exist");
            return static_cast<ComponentArray<T>*>(m_componentArrays[typeid(T).hash_code()])->GetComponentData(entity);
        }

        template <typename T, typename... Args> 
        ENGINE_INLINE T& AddComponent(entityID entity, Args&&...args) 
        {
            ENGINE_ASSERT(m_signatures.count(entity) && "Entity does not exist");
            auto data = T(std::forward<Args>(args)...);
            m_signatures[entity].insert(typeid(T).hash_code());
            return GetComponentArray<T>()->AddComponent(entity, data);
        }

        template <typename T> 
        ENGINE_INLINE void RemoveComponent(entityID entity)
        {
            ENGINE_ASSERT(m_signatures.count(entity) && "Entity does not exist");
            m_signatures.at(entity).erase(typeid(T).hash_code());
            GetComponentArray<T>()->Erase(entity);
        }

        template <typename T> 
        ENGINE_INLINE bool HasComponent(entityID entity) 
        {
            return m_signatures.count(entity) && m_signatures.at(entity).count(typeid(T).hash_code());
        }

        template <typename T> 
        ENGINE_INLINE ComponentArray<T>* GetComponentArray()
        {
            componentID type = typeid(T).hash_code();
            if(m_componentArrays.count(type))
            {
                return static_cast<ComponentArray<T>*>(m_componentArrays[type]);
            }
            auto array = new ComponentArray<T>();
            m_componentArrays[type] = array;
            return array;
        }

    private:
        std::unordered_map<componentID, ComponentArrayInstance*> m_componentArrays;
        std::unordered_map<entityID, signature> m_signatures;
        entityID m_nextID = INVALID_ID;
    };
}