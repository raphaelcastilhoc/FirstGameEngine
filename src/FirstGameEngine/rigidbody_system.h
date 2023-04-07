#pragma once
#include "system.h"

namespace game_engine::ecs
{
	struct rigidbody_system : system
	{
		GAMEENGINE_INLINE void update(float dt)
		{
			for (auto& entity : view<rigidbody_component>())
			{
				auto& rigidbody = entity.get_component<rigidbody_component>();
				if (rigidbody.disabled)
				{
					continue;
				}

				auto& transform = entity.get_component<transform_component>();
				vec2f gravity_force = vec2f(0.0f, rigidbody.body.gravity_scale * 9.8f);
				rigidbody.body.velocity += (rigidbody.body.force + gravity_force) * dt;
				transform.translate += rigidbody.body.velocity * dt;
			}
		}
	};
}