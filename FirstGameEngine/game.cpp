#include "entry.h"

game_engine::app_config game_engine::create_application()
{
	game_engine::app_config config;
	config.title = "GameEngine2D";
	config.version = "0.0.1";
	config.width = 1080;
	config.height = 720;
	return config;
}