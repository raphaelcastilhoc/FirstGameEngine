#pragma once
#include "asset.h"

namespace game_engine
{
    struct animation
    {
        std::vector<asset_id> frames;
        int speed = 100;
    };

    struct animation_asset : asset
    {
        GAMEENGINE_INLINE animation_asset() = default;
        animation instance;
    };
}