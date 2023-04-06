#pragma once
#include "test_system.h"
#include "asset_registry.h"

namespace game_engine::ecs
{
	struct scene
	{
		GAMEENGINE_INLINE scene(SDL_Renderer* rd) : _renderer(rd)
		{
			register_system<ecs::test_system>();
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
		}

		GAMEENGINE_INLINE void start()
		{
			auto frame1 = _assets.add<texture_asset>("frame1");
			auto frame2 = _assets.add<texture_asset>("frame2");
			auto anim = _assets.add<animation_asset>("test");

			anim->instance.frames.push_back(frame1->id);
			anim->instance.frames.push_back(frame2->id);
			anim->instance.speed = 200;


			auto e = this->add_entity("test");
			e.add_component<transform_component>();
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