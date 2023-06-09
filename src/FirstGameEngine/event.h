#pragma once
#include "typeid.h"

namespace game_engine
{
    using event_id = uint32_t;

    // base type for all events
    struct event_instance
    {
        GAMEENGINE_INLINE virtual ~event_instance() = default;
    };

    // callback lambda
    template <typename T>
    using callback_function = std::function<bool(const T&)>;

    struct callback_instance
    {
        GAMEENGINE_INLINE virtual ~callback_instance() = default;
        virtual bool run(event_instance*) = 0;
    };

    template <typename T>
    struct event_callback : callback_instance
    {
        GAMEENGINE_INLINE event_callback(callback_function<T>& clbk) : callback(clbk) {}

        GAMEENGINE_INLINE bool run(event_instance* e)
        {
            auto data = static_cast<const T&>(*e);
            return callback(data);
        }

    private:
        callback_function<T> callback;
    };

    using callback_list = std::vector<std::shared_ptr<callback_instance>>;
}