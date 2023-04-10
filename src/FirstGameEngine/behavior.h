#pragma once
#include "script_instance.h"

namespace game_engine::ecs
{
    struct script_component
    {
        GAMEENGINE_INLINE script_component(const script_component&) = default;
        GAMEENGINE_INLINE script_component() = default;

        template<typename T>
        GAMEENGINE_INLINE void bind()
        {
            instantiate = [](const script_props& props)
            {
                auto script = static_cast<script_instance*>(new T());
                script->init(props);
                return script;
            };
        }

        script_instance* instance = NULL;
        script_instantiator instantiate;
        std::string name;
    };
}