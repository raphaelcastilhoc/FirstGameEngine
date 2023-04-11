#pragma once
#include "asset_registry.h"
#include "graphics.h"
#include "common.h"
#include "physics.h"
#include "sprite_renderer_system.h"
#include "text_renderer_system.h"
#include "frame_animation_system.h"
#include "tilemap_renderer_system.h"
#include "rigidbody_system.h"
#include "collision_system.h"
#include "script_system.h"
#include "player_controller.h"
#include "scrolling_ground.h"
#include "pipe_spawner.h"

namespace game_engine::ecs
{
	struct scene
	{
		GAMEENGINE_INLINE scene(SDL_Renderer* rd) : _renderer(rd)
		{
			register_system<ecs::sprite_renderer_system>();
			register_system<ecs::text_renderer_system>();
			register_system<ecs::frame_animation_system>();
			register_system<ecs::tilemap_renderer_system>();
			register_system<ecs::rigidbody_system>();
			register_system<ecs::collision_system>();
			register_system<ecs::script_system>();
		}

		GAMEENGINE_INLINE ~scene()
		{
			for (auto& s : _systems) { GAMEENGINE_DELETE(s); }
			_registry.clear();
			_systems.clear();
		}

		GAMEENGINE_INLINE ecs::entity add_entity(const std::string& name)
		{
			auto entity = ecs::entity(&_registry);
			entity.add_component<info_component>().name = name;
			entity.add_component<transform_component>();
			return entity;
		}

		GAMEENGINE_INLINE void update(float dt)
		{
			for (auto& sys : _systems)
			{
				sys->update(dt);
			}

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
		}

		GAMEENGINE_INLINE void start()
		{
			auto dead = _assets.load_texture("resource/textures/dead.png", "dead", _renderer);
			auto fly = _assets.load_texture("resource/textures/fly.png", "fly", _renderer);
			auto pipe = _assets.load_texture("resource/textures/pipe.png", "pipe", _renderer);
			auto ground = _assets.load_texture("resource/textures/ground.png", "ground", _renderer);
			
			auto font = _assets.load_font("resource/fonts/font.ttf", "font", 30);

			_assets.load_audio("resource/audios/song.mp3", "music");
			_assets.load_audio("resource/audios/boom.wav", "boom");

			auto bg = add_entity("background");
			auto background = _assets.load_texture("resource/textures/background.png", "bg", _renderer);
			bg.add_component<sprite_component>().sprite = background->id;

			auto gd = add_entity("ground");
			auto& gds = gd.add_component<ecs::script_component>();
			gds.bind<scrolling_ground>();
			gds.name = "scrolling_ground";
			auto& gd_tr = gd.get_component<transform_component>();
			gd_tr.translate = vec2f(0.0f, 620);
			gd.add_component<rigidbody_component>().body.velocity.x = -100.0f;
			auto& gd_sp = gd.add_component<sprite_component>().sprite = ground->id;
			auto& gd_cl = gd.add_component<collider_component>();
			gd_cl.collider = { 0, 0, (float)ground->instance.width, (float)ground->instance.height };

			auto player = add_entity("player");
			auto& ps = player.add_component<ecs::script_component>();
			ps.bind<player_controller>();
			ps.name = "player_controller";
			auto& tr = player.get_component<transform_component>();
			tr.translate = vec2f(126, 360);
			tr.scale = vec2f(0.5f);
			auto& rb = player.add_component<rigidbody_component>();
			rb.body.gravity_scale = 25.0f;
			player.add_component<sprite_component>().sprite = fly->id;
			auto& cl = player.add_component<collider_component>();
			cl.collider = { 0, 0, 58, 38 };

			auto spawner = add_entity("spawner");
			auto& spawner_script = spawner.add_component<script_component>();
			spawner_script.bind<pipe_spawner>();
			spawner_script.name = "pipe_spawner";

			auto score = add_entity("score");
			auto& s_tr = score.get_component<transform_component>();
			s_tr.translate = vec2f(120, 20);
			auto& tx = score.add_component<text_component>();
			tx.text = "Score: 0";
			tx.font = font->id;

			for (auto& sys : _systems)
			{
				sys->start();
			}
		}

		template <typename T>
		GAMEENGINE_INLINE void register_system()
		{
			GAMEENGINE_STATIC_ASSERT(std::is_base_of<ecs::system, T>::value);
			auto new_system = new T();
			new_system->prepare(&_registry, _renderer, &_assets);
			this->_systems.push_back(new_system);
		}

	private:
		std::vector<ecs::system*> _systems;
		SDL_Renderer* _renderer = NULL;
		ecs::registry _registry;
		asset_registry _assets;
	};
}