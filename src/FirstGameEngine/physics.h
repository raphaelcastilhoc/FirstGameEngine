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
}