#pragma once

#include "../pch.h"
#include "typeid.h"

namespace engine
{
    using eventID = uint32_t;

    struct EventInstance
    {
        ENGINE_INLINE virtual ~EventInstance() = default;
    };

    //callback lambda  
    template<typename T>
    using CallbackFunction = std::function<bool(const T&)>;

    struct CallbackInstance
    {
        ENGINE_INLINE virtual ~CallbackInstance() = default;
        virtual bool Run(EventInstance* ) = 0;
    };

    template<typename T>
    struct EventCallback : CallbackInstance
    {
        ENGINE_INLINE EventCallback(CallbackFunction<T>& callback) : callback(callback){}

        ENGINE_INLINE bool Run(EventInstance* e)
        {
            auto data = static_cast<const T&>(*e);
            return callback(data);
        }

    private:
        CallbackFunction<T> callback;
    };

    using callbackList = std::vector<std::shared_ptr<CallbackInstance>>;
}