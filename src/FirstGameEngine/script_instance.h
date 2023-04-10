#pragma once
#include "graphics.h"
#include "physics.h"
#include "common.h"
#include "entity.h"
#include "asset_registry.h"
#include "input.h"

namespace game_engine
{
    struct script_props
    {
        GAMEENGINE_INLINE script_props(ecs::entityid e, ecs::registry* r, asset_registry* a) :
            entity(e), registry(r), assets(a)
        {
        }
        ecs::entityid entity = INVALID_ID;
        ecs::registry* registry = NULL;
        asset_registry* assets = NULL;
    };

    struct script_instance
    {
        GAMEENGINE_INLINE virtual ~script_instance() = default;

        GAMEENGINE_INLINE void init(const script_props& props)
        {
            this->_registry = props.registry;
            this->_assets = props.assets;
            this->_entity = props.entity;
        }

        GAMEENGINE_INLINE void virtual on_collision(ecs::entity) {}
        GAMEENGINE_INLINE void virtual on_update(float) {}
        GAMEENGINE_INLINE void virtual on_destroy() {}
        GAMEENGINE_INLINE void virtual on_start() {}

    protected:
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
            return _registry->remove_component<T>(_entity);
        }

        template<typename T>
        GAMEENGINE_INLINE bool has_component()
        {
            return _registry->has_component<T>(_entity);
        }

        GAMEENGINE_INLINE ecs::entity add_entity()
        {
            auto entity = _registry->add_entity();
            _registry->add_component<ecs::transform_component>(entity);
            _registry->add_component<ecs::info_component>(entity);
            return ecs::entity(entity, _registry);
        }

        GAMEENGINE_INLINE void destroy()
        {
            _registry->destroy(_entity);
        }

        GAMEENGINE_INLINE ecs::entity find_entity(const std::string& name)
        {
            for (auto& e : _registry->view<ecs::info_component>())
            {
                auto& i = _registry->get_component<ecs::info_component>(e);

                if (!i.name.compare(name))
                {
                    return ecs::entity(e, _registry);
                }
            }
            return ecs::entity();
        }

        template<typename T>
        GAMEENGINE_INLINE T* get_asset(const std::string& name)
        {
            return _assets->get<T>(name);
        }

    private:
        ecs::entityid _entity = INVALID_ID;
        ecs::registry* _registry = NULL;
        asset_registry* _assets = NULL;
    };

    // script allocator function type
    using script_instantiator = std::function<script_instance* (const script_props&)>;
}