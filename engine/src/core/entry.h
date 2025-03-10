#define SDL_MAIN_HANDLED
#pragma once
#include "engine.h"

extern engine::engineConfig engine::CreateEngine();

int main(int argc, char** argv)
{
	auto config = engine::CreateEngine();
	engine::RunEngine(config);

	return 0;
}
