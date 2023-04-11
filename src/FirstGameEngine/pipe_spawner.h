#pragma once
#include "script_instance.h"
#include "random.h"

namespace game_engine
{
	struct pipe_spawner : script_instance
	{
		GAMEENGINE_INLINE void on_update(float dt)
		{
			if (game_over)
			{
				return;
			}

			auto player = find_entity("player");
			auto& player_rigidbody = player.get_component<ecs::rigidbody_component>();

			// check if player's rigidbody is disabled
			if (player.is_alive() && player_rigidbody.disabled)
			{
				// stop ground scroll animation
				auto ground = find_entity("ground");
				auto& ground_rigidbody = ground.get_component<ecs::rigidbody_component>();
				ground_rigidbody.disabled = true;

				// stop all pipes motion 
				for (auto& pipe : pipes)
				{
					auto& pipe_rigidbody = pipe.get_component<ecs::rigidbody_component>();
					pipe_rigidbody.disabled = true;
					auto& pipe_collider = pipe.get_component<ecs::collider_component>();
					pipe_collider.disabled = true;
				}

				game_over = true;
				return;
			}

			update_pipes();

			// create pipes
			if (time > 2.5f)
			{
				time = 0.0f;
				float space = math::random(60, 150);
				spawn_pipe(380, -space);
				spawn_pipe(380, 720 / 2 + space);
			}

			time += dt;
		}

		GAMEENGINE_INLINE void spawn_pipe(float x, float y)
		{
			auto pipe = add_entity();
			auto& tr = pipe.get_component<ecs::transform_component>();
			tr.translate = vec2f(x, y);

			// add rigidbody
			auto& rb = pipe.add_component<ecs::rigidbody_component>();
			rb.body.gravity_scale = 0.0f;
			rb.body.velocity.x = -100.f;

			// add sprite
			auto pipe_sprite = get_asset<texture_asset>("pipe");
			auto& sp = pipe.add_component<ecs::sprite_component>();
			sp.flip = (y < 0) ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;
			sp.sprite = pipe_sprite->id;

			// add collider
			auto& cl = pipe.add_component<ecs::collider_component>();
			cl.collider = {
			  tr.translate.x,
			  tr.translate.y,
			  (float)pipe_sprite->instance.width,
			  (float)pipe_sprite->instance.height
			};

			pipes.push_back(pipe);
		}

		GAMEENGINE_INLINE void update_pipes()
		{
			auto it = pipes.begin();
			while (it != pipes.end())
			{
				// remove dead pipe
				auto& pipe = (*it);
				if (!pipe.is_alive())
				{
					it = pipes.erase(it);
					continue;
				}

				it++;
			}
		}

	private:
		std::vector<ecs::entity> pipes;
		bool game_over = false;
		float time = 0.0f;
		int score = 0;
	};
}