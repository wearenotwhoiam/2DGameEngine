#include <core/entry.h>

Engine::engineConfig Engine::CreateEngine()
{
	Engine::engineConfig config;
	config.version = "0.0.1";
	config.title = "2DEngine";
	config.height = 720;
	config.width = 1080;
	return config;
}