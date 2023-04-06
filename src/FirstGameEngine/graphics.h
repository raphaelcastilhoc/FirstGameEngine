#pragma once
#include "asset.h"

namespace game_engine::ecs
{
	struct sprite_component
	{
		GAMEENGINE_INLINE sprite_component(const sprite_component&) = default;
		GAMEENGINE_INLINE sprite_component() = default;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		asset_id sprite = INVALID_ID;
	};
}