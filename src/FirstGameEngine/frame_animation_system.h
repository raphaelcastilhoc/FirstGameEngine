#pragma once
#include "system.h"

namespace game_engine::ecs
{
	struct frame_animation_system : system
	{
		GAMEENGINE_INLINE void update(float)
		{
			for (auto& e : view<animation_component>())
			{
				auto& tr = e.get_component<transform_component>();
				auto& an = e.get_component<animation_component>();

				auto& anim = _assets->get<animation_asset>(an.animation)->instance;

				// compute current frame
				int index = (get_ticks_ms() / anim.speed) % anim.frames.size();
				auto& frame = _assets->get<texture_asset>(anim.frames[index])->instance;

				// define target viewport
				SDL_FRect dst
				{
				  tr.translate.x, tr.translate.y,
				  frame.width * tr.scale.x, frame.height * tr.scale.y
				};

				// render sprite        
				SDL_RenderCopyExF(_renderer, frame.data, NULL, &dst, tr.rotation, NULL, an.flip);
			}
		}
	};
}