#pragma once
#include "event.h"

namespace engine
{
    struct Dispatcher
    {
        //posts an event with type T
        template<typename T, typename... Args>
        ENGINE_INLINE void Post(Args&&...args)
        {
            //ensure the base class is an Event Instance
            //add to event type list and all its parameters
            //all events go frame by frame - cleared at end of frame
            ENGINE_STATIC_ASSERT(std::is_base_of<EventInstance,T>::value);
            m_events[TypeID<T>()] = new T(std::forward<Args>(args)...);
        }

        //registers a callback for the event of type T
        template<typename T>
        ENGINE_INLINE void AddCallback(CallbackFunction<T>&& callback)
        {
            //ensure the base class is an Event Instance
            //add to callback list
            ENGINE_STATIC_ASSERT(std::is_base_of<EventInstance,T>::value);
            auto entry = std::make_shared<EventCallback<T>>(callback);
            m_callbacks[TypeID<T>()].push_back(entry);
        }

        //handles all events and cleans memory
        ENGINE_INLINE void Dispatch()
        {
            if(!m_events.size()) return;
            for(auto &[code,entry] : m_events)
            {
                for(auto &callback : m_callbacks[code])
                {
                    if(callback->Run(entry)){break;}
                }
            }
            m_events.clear();
        }
    private:
        std::unordered_map<eventID, EventInstance*> m_events;
        std::unordered_map<eventID, callbackList> m_callbacks;
    };
}