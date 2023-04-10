#pragma once
#include "script_instance.h"

namespace game_engine
{
    struct scrolling_ground : script_instance
    {
        GAMEENGINE_INLINE void on_start()
        {
            width = get_asset<texture_asset>("ground")->instance.width;
        }

        GAMEENGINE_INLINE void on_update(float dt)
        {
            auto& tr = get_component<ecs::transform_component>();

            if (tr.translate.x + width < 380)
            {
                tr.translate.x = 0.0f;
            }
        }

    private:
        float width;
    };
}