#pragma once
#include "ecs_registry.h"

namespace game_engine::ecs
{
	struct entity
	{
		GAMEENGINE_INLINE entity(registry* r) : _registry(r)
		{
			_entity = r->add_entity();
		}

		GAMEENGINE_INLINE entity(entityid e, registry* r) : _registry(r), _entity(e) {}

		GAMEENGINE_INLINE operator entityid()
		{
			return _entity;
		}

		GAMEENGINE_INLINE entity() = default;

		template<typename T, typename... Args>
		GAMEENGINE_INLINE T& add_component(Args&&... args)
		{
			return _registry->add_component<T>(_entity, std::forward<Args>(args)...);
		}

		template<typename T>
		GAMEENGINE_INLINE T& get_component()
		{
			return _registry->get_component<T>(_entity);
		}

		template<typename T>
		GAMEENGINE_INLINE void remove_component()
		{
			_registry->remove_component<T>(_entity);
		}

		template<typename T>
		GAMEENGINE_INLINE bool has_component()
		{
			return _registry->has_component<T>(_entity);
		}

		GAMEENGINE_INLINE bool is_alive()
		{
			return _registry && _registry->is_alive(_entity);
		}

		GAMEENGINE_INLINE entityid id() { return _entity; }

		GAMEENGINE_INLINE void destroy() { _registry->destroy(_entity); }

	private:
		entityid _entity = INVALID_ID;
		registry* _registry = NULL;
	};
}