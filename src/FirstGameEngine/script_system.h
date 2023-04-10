#pragma once
#include "system.h"

namespace game_engine::ecs
{
    struct script_system : system
    {
        GAMEENGINE_INLINE ~script_system()
        {
            for (auto& e : view<script_component>())
            {
                auto& script = e.get_component<script_component>();
                GAMEENGINE_DELETE(script.instance);
            }
        }

        GAMEENGINE_INLINE void start()
        {
            for (auto& e : view<script_component>())
            {
                auto& script = e.get_component<script_component>();
                script_props props(e, _registry, _assets);
                script.instance = script.instantiate(props);
                script.instance->on_start();
            }
        }

        GAMEENGINE_INLINE void update(float dt)
        {
            for (auto& e : view<script_component>())
            {
                e.get_component<script_component>().instance->on_update(dt);
            }
        }
    };
}