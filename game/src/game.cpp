#include <core/entry.h>

engine::engineConfig engine::CreateEngine()
{
	engine::engineConfig config;
	config.version = "0.0.1";
	config.title = "2DEngine";
	config.height = 720;
	config.width = 1080;
	return config;
}