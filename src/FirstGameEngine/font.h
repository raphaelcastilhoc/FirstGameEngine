#pragma once
#include "asset.h"
#include <SDL2/SDL_ttf.h>

namespace game_engine
{
    struct font
    {
        TTF_Font* data = NULL;
        std::string filename;
        int size = 20;
    };

    struct font_asset : asset
    {
        GAMEENGINE_INLINE font_asset() = default;
        GAMEENGINE_INLINE ~font_asset()
        {
            TTF_CloseFont(instance.data);
        }

        font instance;
    };
}