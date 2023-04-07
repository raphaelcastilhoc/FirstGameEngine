#pragma once 
#include "rigidbody2.h"

namespace game_engine::ecs
{
    struct rigidbody_component
    {
        GAMEENGINE_INLINE rigidbody_component(const rigidbody_component&) = default;
        GAMEENGINE_INLINE rigidbody_component() = default;
        bool disabled = false;
        rigidbody2 body;
    };

    struct collider_component
    {
        GAMEENGINE_INLINE collider_component(const collider_component&) = default;
        GAMEENGINE_INLINE collider_component() = default;
        SDL_FRect collider = { 0.0f, 0.0f, 64.0f, 64.0f };
        bool disabled = false;
    };
}