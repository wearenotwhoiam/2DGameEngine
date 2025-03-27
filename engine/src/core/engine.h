#pragma once
#include "../pch.h"

namespace Engine
{
	struct EngineConfig
	{
		int width{ 0 };
		int height{ 0 };
		std::string title;
		std::string version;
	};

	//defined in game.exe
	EngineConfig CreateEngine();
	
	ENGINE_API void RunEngine(const EngineConfig&);
}