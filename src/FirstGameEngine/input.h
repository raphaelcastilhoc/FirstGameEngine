#pragma once

#include "dispatcher.h"
#include "vec2.h"

#include <SDL2/SDL.h>

namespace game_engine::input
{
	struct mouse_state
	{
		std::bitset<7> buttons = { 0 };
		vec2f offset;
		vec2f wheel;
	};

	GAMEENGINE_API const vec2f& mouse_offset();
	GAMEENGINE_API const vec2f& mouse_wheel();
	GAMEENGINE_API bool is_button(int);

	GAMEENGINE_API void initialize(SDL_Window*);
	GAMEENGINE_API dispatcher* get_dispatcher();
	GAMEENGINE_API void dispatch_events();
	GAMEENGINE_API bool is_key(int);
}