#pragma once
#include "../core/typeid.h"

namespace engine::ecs
{
    using entityID = size_t;
    using componentID = size_t;
    using signature = std::set<uint32_t>;
    using entityList = std::set<entityID>;

    struct ComponentArrayInstance
    {
        ENGINE_INLINE virtual ~ComponentArrayInstance() = default;
        virtual void Erase(entityID) = 0;
    };

    template <typename T> struct ComponentInstance
    {
        ENGINE_INLINE ComponentInstance(entityID e, const T& d) : ownerEntity(e), data(d) {}
        ENGINE_INLINE operator entityID() const { return ownerEntity; }
        entityID ownerEntity = INVALID_ID;
        T data;
    };

    template <typename T> 
    struct ComponentArray : ComponentArrayInstance
    {
        ENGINE_INLINE T& AddComponent(entityID e, const T& d)
        {
            if(HasComponent(e)) return GetComponentData(e);
            
            entries.push_back(ComponentInstance(e, d));
            return entries.back().data;
        }

        ENGINE_INLINE void Erase(entityID e) override
        {
            if(!HasComponent(e)) return;
            auto it = std::find(entries.begin(), entries.end(), e);
            if(it != entries.end()) entries.erase(it);
        }

        ENGINE_INLINE bool HasComponent(entityID e) const
        {
            return std::find(entries.begin(), entries.end(), e) != entries.end();
        }

        ENGINE_INLINE T& GetComponentData(entityID e)
        {
            ENGINE_ASSERT(HasComponent(e) && "Entity does not exist");
            return (*std::find(entries.begin(), entries.end(), e)).data;
        }
    private:
        std::vector<ComponentInstance<T>> entries;            
    };
}