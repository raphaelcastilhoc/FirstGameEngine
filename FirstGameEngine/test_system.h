#include "system.h"
#include "common.h"

namespace game_engine::ecs
{
    struct test_system : system
    {
        void update(float)
        {
            for (auto& e : view<transform_component>())
            {
                auto& t = e.get_component<transform_component>();
                GAMEENGINE_INFO("id:[%d], x:%f", e.id(), t.translate.x++);
            }
        }
    };
}