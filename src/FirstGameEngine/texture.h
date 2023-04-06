#pragma once
#include "asset.h"

namespace game_engine
{
    struct texture
    {
        SDL_Texture* data = NULL;
        std::string filename;
        int height = 0;
        int width = 0;
    };

    struct texture_asset : asset
    {
        GAMEENGINE_INLINE texture_asset() = default;

        GAMEENGINE_INLINE ~texture_asset()
        {
            SDL_DestroyTexture(instance.data);
        }

        texture instance;
    };
}