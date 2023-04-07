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
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			for (auto& sys : _systems)
			{
				sys->update(dt);
			}
		}

		GAMEENGINE_INLINE void start()
		{
			auto entity = add_entity("entity");

			auto texture1 = _assets.load_texture("resource/textures/obj1.png", "", _renderer);
			entity.add_component<sprite_component>().sprite = texture1->id;
			auto& rigidbody = entity.add_component<rigidbody_component>();
			rigidbody.body.gravity_scale = 1.0f;

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