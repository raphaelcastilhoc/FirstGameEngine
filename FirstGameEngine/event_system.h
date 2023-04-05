#pragma once
#include "event.h"

namespace game_engine
{
	struct quit_event : event_instance
	{
		GAMEENGINE_INLINE quit_event() = default;
	};

	struct keydown_event : event_instance
	{
		GAMEENGINE_INLINE keydown_event(int key) : key(key) {}
		int key;
	};

	struct keyup_event : event_instance
	{
		GAMEENGINE_INLINE keyup_event(int key) : key(key) {}
		int key;
	};

	struct keyrepeat_event : event_instance
	{
		GAMEENGINE_INLINE keyrepeat_event(int key) : key(key) {}
		int key;
	};

	struct mousedown_event : event_instance
	{
		GAMEENGINE_INLINE mousedown_event(int btn) :button(btn) {}
		int button;
	};

	struct mouseup_event : event_instance
	{
		GAMEENGINE_INLINE mouseup_event(int btn) : button(btn) {}
		int button;
	};

	struct mousemotion_event : event_instance
	{
		GAMEENGINE_INLINE mousemotion_event() = default;
	};

	struct mousewheel_event : event_instance
	{
		GAMEENGINE_INLINE mousewheel_event() = default;
	};
}