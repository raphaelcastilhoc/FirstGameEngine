#include "entry.h"

game_engine::app_config game_engine::create_application()
{
	game_engine::app_config config;
	config.title = "Flappy Plane";
	config.version = "0.0.1";
	config.width = 380;
	config.height = 720;
	config.scene = "resource/serialization/scene.yaml";
	return config;
}