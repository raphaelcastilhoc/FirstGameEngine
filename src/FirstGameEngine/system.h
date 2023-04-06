#pragma once
#include "entity.h"
#include "asset_registry.h"

namespace game_engine::ecs
{
    struct system
    {
        GAMEENGINE_INLINE virtual ~system() = default;

        GAMEENGINE_INLINE void prepare(registry* registry, SDL_Renderer* renderer, asset_registry* asset_registry)
        {
            this->_registry = registry;
            this->_renderer = renderer;
            this->_assets = asset_registry;
        }

        template<typename T>
        GAMEENGINE_INLINE auto view()
        {
            std::vector<entity> entities;
            for (auto& e : _registry->view<T>())
            {
                entities.push_back(entity(e, _registry));
            }

            return entities;
        }

        GAMEENGINE_INLINE virtual void update(float) {}
        GAMEENGINE_INLINE virtual void start() {}

    protected:
        SDL_Renderer* _renderer = NULL;
        registry* _registry = NULL;
        asset_registry* _assets = NULL;
    };
}