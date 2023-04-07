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

	struct text_component
	{
		GAMEENGINE_INLINE text_component(const text_component&) = default;
		GAMEENGINE_INLINE text_component() = default;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_Color color = { 0, 0, 0, 255 };
		asset_id font = INVALID_ID;
		std::string text;
	};

	struct animation_component
	{
		GAMEENGINE_INLINE animation_component(const animation_component&) = default;
		GAMEENGINE_INLINE animation_component() = default;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		asset_id animation = INVALID_ID;
	};
}