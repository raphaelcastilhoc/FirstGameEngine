#pragma once

namespace game_engine
{
	GAMEENGINE_INLINE const uint32_t get_unique_typeid()
	{
		static uint32_t type = 1u;
		return type++;
	}

	template<typename T>
	GAMEENGINE_INLINE const uint32_t type_id()
	{
		static const uint32_t type = get_unique_typeid();
		return type;
	}
}
