#pragma once
#include "system.h"

namespace game_engine::ecs
{
	struct collision_system : system
	{
		GAMEENGINE_INLINE void start()
		{
			for (auto& entity : view<collider_component>())
			{
				auto& transform = entity.get_component<transform_component>();
				auto& collider = entity.get_component<collider_component>();
				collider.collider.x = transform.translate.x;
				collider.collider.y = transform.translate.y;
			}
		}

		GAMEENGINE_INLINE void update(float)
		{
			auto entities = view<collider_component>();

			for (auto& entity : entities)
			{
				auto& transform = entity.get_component<transform_component>();
				auto& first_entity_collider = entity.get_component<collider_component>();

				// update box collider offset
				first_entity_collider.collider.x = transform.translate.x;
				first_entity_collider.collider.y = transform.translate.y;

				// continue if disabled
				if (first_entity_collider.disabled)
				{
					continue;
				}

				// check collision with others
				for (auto& second_entity : entities)
				{
					if (second_entity == entity)
					{
						continue;
					}

					auto& second_entity_collider = second_entity.get_component<collider_component>();
					if (check_collision(first_entity_collider.collider, second_entity_collider.collider))
					{
						GAMEENGINE_INFO("collision: %d -> %d", entity.id(), second_entity.id());
					}
				}
			}
		}

	private:
		bool check_collision(const SDL_FRect& first_box, const SDL_FRect& second_box)
		{
			return ((first_box.x < second_box.x + second_box.w) && (first_box.x + first_box.w > second_box.x)) &&
				((first_box.y < second_box.y + second_box.h) && (first_box.y + first_box.h > second_box.y));
		}
	};
}