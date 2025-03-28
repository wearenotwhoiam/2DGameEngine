#pragma once

#include "../ECS/components/graphics.h"
#include "../ECS/components/common.h"
#include "../ECS/components/physics.h"
#include "../ECS/entity.h"

#include "../assets/registry.h"

#include "core/input.h"

namespace Engine
{
    struct ScriptProps
    {
        ENGINE_INLINE ScriptProps(ECS::entityID e, ECS::Registry* r, AssetRegistry* a):
            entity(e), registry(r), assets(a) {}

        ECS::entityID entity {INVALID_ID};
        ECS::Registry* registry {NULL};
        AssetRegistry* assets {NULL};
    };

    struct ScriptInstance
    {
        ENGINE_INLINE virtual ~ScriptInstance() = default;

        ENGINE_INLINE void Initialize(const ScriptProps& props)
        {
            this->m_entity = props.entity;
            this->m_registry = props.registry;
            this->m_assets = props.assets;
        }

        ENGINE_INLINE void virtual OnCollision(ECS::entityID) {}
        ENGINE_INLINE void virtual OnUpdate(float) {}
        ENGINE_INLINE void virtual OnStart() {}
        ENGINE_INLINE void virtual OnDestroy() {}

protected:
        template<typename T, typename... Args>
        ENGINE_INLINE T& AddComponent(Args&&... args)
        {
            return m_registry->AddComponent<T>(m_entity, std::forward<Args>(args)...);
        }

        template<typename T>
        ENGINE_INLINE T& GetComponent()
        {
            return m_registry->GetComponent<T>(m_entity);
        }     
        template<typename T>
        ENGINE_INLINE void Remove()
        {
            return m_registry->RemoveComponent<T>(m_entity);
        }  
        template<typename T>
        ENGINE_INLINE bool HasComponent()
        {
            return m_registry->HasComponent<T>(m_entity);
        }    

        ENGINE_INLINE ECS::Entity AddEntity()
        {
            auto entity = m_registry->AddEntity();
            m_registry->AddComponent<ECS::TransformComponent>(entity);
            m_registry->AddComponent<ECS::InfoComponent>(entity);
            return ECS::Entity(entity,m_registry);
        }

        ENGINE_INLINE void DestroyEntity()
        {
            m_registry->DestroyEntity(m_entity);
        }

        ENGINE_INLINE ECS::Entity FindEntity(const std::string& name)
        {
            for(auto& e: m_registry->ViewComponentOwners<ECS::InfoComponent>())
            {
                auto& infoComp = m_registry->GetComponent<ECS::InfoComponent>(e);

                if(!infoComp.name.compare(name))
                {
                    return ECS::Entity(e, m_registry);
                }
            }

            return ECS::Entity();
        }

        template<typename T>
        ENGINE_INLINE T* GetAsset(const std::string& name)
        {
            return m_assets->GetAsset<T>(name);
        }

        ENGINE_INLINE void PlayAudio(std::string name, int channel = -1, int loops = 0, int vol = 50)
        {
            auto& chunk = m_assets->GetAsset<AudioAsset>(name)->instance.data;
            Mix_VolumeChunk(chunk, vol);
            Mix_PlayChannel(channel, chunk, loops);
        }

        ENGINE_INLINE void PlayMusic(std::string name, int channel = -1, int loops = 0, int vol = 50)
        {
            auto& music = m_assets->GetAsset<MusicAsset>(name)->instance.data;
            Mix_VolumeMusic(128);
            ENGINE_INFO("%d", (Mix_PlayMusic(music, loops) < 0));

        }
private:
        ECS::entityID m_entity {INVALID_ID};
        ECS::Registry* m_registry {NULL};
        AssetRegistry* m_assets {NULL};
    };

    using ScriptInstantiator = std::function<ScriptInstance*(const ScriptProps&)>;
}