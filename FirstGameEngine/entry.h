#pragma once
#include "application.h"

int main(int argc, char** argv)
{
	auto config = game_engine::create_application();
	game_engine::run_application(config);
	return 0;
}