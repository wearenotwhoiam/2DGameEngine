#define SDL_MAIN_HANDLED
#pragma once
#include "engine.h"

extern Engine::EngineConfig Engine::CreateEngine();

int main(int argc, char** argv)
{
	auto config = Engine::CreateEngine();
	Engine::RunEngine(config);

	return 0;
}
