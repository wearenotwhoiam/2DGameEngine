#pragma once
#include "dispatcher.h"
#include "../math/vec2.h"

namespace engine::input
{
    struct MouseState
    {
        std::bitset<7> buttons {0};
        Vec2f position;
        Vec2f wheel;
    };

    ENGINE_API const Vec2f& GetMousePosition();
    ENGINE_API const Vec2f& GetMouseWheel();
    ENGINE_API bool IsButton(int);

    ENGINE_API void Initialize(SDL_Window*);
    ENGINE_API Dispatcher* GetDispatcher();
    ENGINE_API void DispatchEvents();
    ENGINE_API bool IsKey(int);
}