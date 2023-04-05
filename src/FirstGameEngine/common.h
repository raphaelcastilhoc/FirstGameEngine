#pragma once
#include "vec2.h"

namespace game_engine::ecs
{
    struct info_component
    {
        GAMEENGINE_INLINE info_component(const info_component&) = default;
        GAMEENGINE_INLINE info_component() = default;

        uuid64 uuid = generate_uuid();
        std::string name = "entity";
        std::string tag = "default";
    };

    struct transform_component
    {
        GAMEENGINE_INLINE transform_component(const transform_component&) = default;
        GAMEENGINE_INLINE transform_component() = default;

        vec2f translate = vec2f(0.0f);
        vec2f scale = vec2f(1.0f);
        float rotation = 0.0f;
    };
}