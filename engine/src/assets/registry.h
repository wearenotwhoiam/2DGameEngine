#pragma once
#include "font.h"
#include "audio.h"
#include "tilemap.h"
#include "texture.h"
#include "animation.h"
#include "../core/typeid.h"

namespace engine
{
    struct AssetRegistry
    {
        ENGINE_INLINE void Clear()
        {
            for(auto&[_, list] : m_data)
            {
                for(auto a : list) {ENGINE_DELETE(a);}
            }
            m_data.clear();
        }

        template <typename T>
        ENGINE_INLINE T* GetAsset(assetID id)
        {
            ENGINE_STATIC_ASSERT(std::is_base_of<Asset, T>::value);
            const auto type = TypeID<T>();

            if(!m_data.count(type)) return NULL;

            for(auto& asset : m_data.at(type))
            {
                if(asset->id == id) return static_cast<T*>(asset);
            }
            return NULL;
        }

        template <typename T>
        ENGINE_INLINE T* GetAsset(const std::string& name)
        {
            assetID id = GetID<T>(name);
            ENGINE_STATIC_ASSERT(std::is_base_of<Asset, T>::value);
            const auto type = TypeID<T>();

            if(!m_data.count(type)) return NULL;

            for(auto& asset : m_data.at(type))
            {
                if(asset->id == id) return static_cast<T*>(asset);
            }
            return NULL;
        }

        template <typename T>
        ENGINE_INLINE assetID GetID(const std::string& name)
        {   
            ENGINE_STATIC_ASSERT(std::is_base_of<Asset, T>::value);
            const auto type = TypeID<T>();
            if(!m_data.count(type)) return INVALID_ID;

            for(auto& asset : m_data.at(type))
            {
                if(!asset->name.compare(name)) return asset->id;
            }

            return INVALID_ID;
        }

        template <typename T>
        ENGINE_INLINE T* AddAsset(const std::string& name)
        {
            auto asset = new T();
            asset->name = name;
            m_data[TypeID<T>()].push_back(asset);
            return asset;
        }

        ENGINE_INLINE TextureAsset* LoadTexture(const std::string& src, const std::string& name, SDL_Renderer* rd)
        {
            Texture texture;
            texture.data = IMG_LoadTexture(rd, src.c_str());
            texture.filename = src;

            if(!texture.data)
            {
                ENGINE_ERROR("%s", IMG_GetError());
                return NULL;
            }

            SDL_QueryTexture(texture.data, NULL, NULL, &texture.width, &texture.height);
            auto asset = new TextureAsset();
            asset->instance = texture;
            asset->name = name;
            m_data[TypeID<TextureAsset>()].push_back(asset);
            return asset;
        }

        ENGINE_INLINE FontAsset* LoadFont(const std::string& src, const std::string& name, int size)
        {
            Font font;

            font.data = TTF_OpenFont(src.c_str(), size);
            font.filename = src;
            font.size = size;

            if(!font.data)
            {
                ENGINE_ERROR("%s", IMG_GetError());
                return NULL;
            }

            auto asset = new FontAsset();
            asset->instance = font;
            asset->name = name;

            m_data[TypeID<FontAsset>()].push_back(asset);
            return asset;
        }

       
        private:
        std::unordered_map<assetTypeID, std::vector<Asset*>> m_data;
    };
}