#pragma once
#include "../pch.h"

namespace engine
{
	struct engineConfig
	{
		int width{ 0 };
		int height{ 0 };
		std::string title;
		std::string version;
	};

	//defined in game.exe
	engineConfig CreateEngine();
	
	ENGINE_API void RunEngine(const engineConfig&);
}