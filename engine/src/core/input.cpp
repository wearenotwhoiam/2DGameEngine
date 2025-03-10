#include "input.h"
#include "../events/system.h"

namespace engine::input
{
    static const uint8_t* keyboard {NULL};
    static MouseState mouse;
    static Dispatcher disp;

    Dispatcher* GetDispatcher() {return &disp;}
    
    bool IsKey(int key) {return keyboard[key];}

    const Vec2f& GetMouseWheel() {return mouse.wheel;}
    const Vec2f& GetMousePosition() {return mouse.position;}
    bool IsButton(int b) {return mouse.buttons.test(b);}

    void Initialize(SDL_Window* window)
    {
        keyboard = SDL_GetKeyboardState(NULL);
    }

    void DispatchEvents()
    {
        static SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: 
                    disp.Post<QuitEvent>(); 
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse.buttons.set(event.button.button);
                    disp.Post<MouseDownEvent>(event.button.button); 
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse.buttons.reset(event.button.button);
                    disp.Post<MouseUpEvent>(event.button.button); 
                    break;
                case SDL_MOUSEWHEEL:
                    mouse.wheel = Vec2f(event.button.x, event.button.y);
                    disp.Post<MouseWheelEvent>(); 
                    break;
                case SDL_MOUSEMOTION:
                    mouse.position = Vec2f(event.button.x, event.button.y);
                    disp.Post<MouseMotionEvent>();
                    break;
                case SDL_KEYDOWN:
                    keyboard = SDL_GetKeyboardState(NULL);
                    disp.Post<KeyDownEvent>(event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    keyboard = SDL_GetKeyboardState(NULL); 
                    disp.Post<KeyUpEvent>(event.key.keysym.scancode); 
                    break;  
            }
        }
        disp.Dispatch();
    }
}