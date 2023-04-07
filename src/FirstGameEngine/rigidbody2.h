#pragma once
#include "vec2.h"

namespace game_engine
{
    struct rigidbody2
    {
        GAMEENGINE_INLINE void set_force(const vec2f& f) { force = f; }
        GAMEENGINE_INLINE void set_force_x(float x) { force.x = x; }
        GAMEENGINE_INLINE void set_force_y(float y) { force.y = y; }

        float gravity_scale = 0.0f;
        vec2f velocity;
        vec2f force;
    };
}