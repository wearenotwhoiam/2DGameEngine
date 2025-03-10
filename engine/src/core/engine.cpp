#include "engine.h"
#include "input.h"
#include "typeid.h"
#include "ecs/scene.h"
#include "../events/system.h"
namespace engine
{
	static bool isRunning{true};

	ENGINE_INLINE bool OnQuit(const QuitEvent&)
	{			
		return isRunning = false;
	}

	ENGINE_API void RunEngine(const engineConfig& config)
	{	
		//SDL Startup										
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			ENGINE_ERROR("%", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		{
			ENGINE_ERROR("%", IMG_GetError());
		}
		if (TTF_Init() != 0)
		{
			ENGINE_ERROR("%", TTF_GetError());
		}
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0 || Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 2, 512))
		{
			ENGINE_ERROR("%", Mix_GetError());
		}

		//Create Window
		auto wFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		SDL_Window* window = SDL_CreateWindow
		(
			config.title.c_str(), 
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			config.width, config.height, wFlags
		);
		auto rFlags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rFlags);
		if(!window || !renderer)
		{
			ENGINE_ERROR("%", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		
		input::Initialize(window);

		//Add callbacks
		input::GetDispatcher()->AddCallback<QuitEvent>(OnQuit);

		//create & start a scene
		auto scene = new ecs::Scene(renderer);
		scene->Start();

		//Display Window
		while(isRunning)
		{
			if(input::IsButton(SDL_BUTTON_LEFT))
			{
				auto mouse = input::GetMousePosition();
				ENGINE_INFO("(%f, %f)", mouse.x, mouse.y); 
			}
			if(input::IsKey(SDL_SCANCODE_ESCAPE))
			{
				isRunning = false;
			}

			input::DispatchEvents();
			SDL_RenderClear(renderer);
			scene->Update(0.0f);
			SDL_RenderPresent(renderer);
		}
		
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		ENGINE_DELETE(scene);


		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}
}