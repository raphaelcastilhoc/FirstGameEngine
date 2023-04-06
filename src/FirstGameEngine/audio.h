#pragma once
#include "asset.h"

#include <SDL2/SDL_mixer.h>

namespace game_engine
{
    struct audio_clip
    {
        Mix_Chunk* data = NULL;
        std::string filename;
    };

    struct audio_asset : asset
    {
        GAMEENGINE_INLINE audio_asset() = default;

        GAMEENGINE_INLINE ~audio_asset()
        {
            Mix_FreeChunk(instance.data);
        }

        audio_clip instance;
    };
}