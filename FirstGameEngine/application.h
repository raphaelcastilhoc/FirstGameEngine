#pragma once

#include "pch.h"

namespace game_engine
{
    struct app_config
    {
        int width = 0;
        int height = 0;
        std::string title;
        std::string scene;
        std::string version;
    };

    app_config create_application();

    GAMEENGINE_API void run_application(const app_config&);
}