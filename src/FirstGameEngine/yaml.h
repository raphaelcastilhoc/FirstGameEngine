#pragma once
#include "vec2.h"
#include <yaml-cpp/yaml.h>

namespace YAML
{
    template <>
    struct convert<game_engine::vec2f>
    {
        GAMEENGINE_INLINE static Node encode(const game_engine::vec2f& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        GAMEENGINE_INLINE static bool decode(const Node& node, game_engine::vec2f& rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
            {
                return false;
            }
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    // stream operator
    GAMEENGINE_INLINE Emitter& operator<<(Emitter& emitter, const game_engine::vec2f& v)
    {
        emitter << Flow;
        emitter << BeginSeq << v.x << v.y << EndSeq;
        return emitter;
    }
}