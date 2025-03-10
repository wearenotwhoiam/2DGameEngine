#pragma once
#include "../core/event.h"

namespace engine
{
    struct QuitEvent : EventInstance
    {
        ENGINE_INLINE QuitEvent() = default;
    };
    
    struct KeyDownEvent : EventInstance
    {
        ENGINE_INLINE KeyDownEvent(int key) : key(key){}
        int key;
    };

    struct KeyUpEvent: EventInstance
    {
        ENGINE_INLINE KeyUpEvent(int key) : key(key){}
        int key;
    };

    struct MouseDownEvent : EventInstance
    {
        ENGINE_INLINE MouseDownEvent(int button) : button(button){}
        int button;
    };

    struct MouseUpEvent: EventInstance
    {
        ENGINE_INLINE MouseUpEvent(int button) : button(button){}
        int button; 
    };

    struct MouseMotionEvent : EventInstance
    {
        ENGINE_INLINE MouseMotionEvent() = default;
    };

    struct MouseWheelEvent: EventInstance
    {
        ENGINE_INLINE MouseWheelEvent() = default;
    };
}