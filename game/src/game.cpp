#include <core/entry.h>

Engine::EngineConfig Engine::CreateEngine()
{
	Engine::EngineConfig config;

	config.title = "Flappy Terd";
	config.version = "0.0.1";
	config.width = 380;
	config.height = 720;
	return config;
}