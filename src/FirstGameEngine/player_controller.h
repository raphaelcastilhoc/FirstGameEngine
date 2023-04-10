#pragma once
#include "script_instance.h"

namespace game_engine
{
    struct player_controller : script_instance
    {

        GAMEENGINE_INLINE void on_start()
        {
            GAMEENGINE_INFO("player_controller_script started!");
        }

        GAMEENGINE_INLINE void on_collision(ecs::entity collided_entity)
        {
            GAMEENGINE_INFO("Colliding with: %d", collided_entity.id());
        }

        GAMEENGINE_INLINE void on_update(float dt)
        {
            auto& t = get_component<ecs::transform_component>();

            if (input::is_key(SDL_SCANCODE_A))
            { // move left
                t.translate.x -= (speed * dt);
            }
            if (input::is_key(SDL_SCANCODE_D))
            { // move right
                t.translate.x += (speed * dt);
            }
            if (input::is_key(SDL_SCANCODE_W))
            { // move up
                t.translate.y -= (speed * dt);
            }
            if (input::is_key(SDL_SCANCODE_S))
            { // move down
                t.translate.y += (speed * dt);
            }
        }

    private:
        float speed = 300.0f;
    };
}