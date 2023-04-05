#include "application.h"
#include "input.h"
#include "event_system.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

namespace game_engine
{
    static bool is_running = true;

    GAMEENGINE_INLINE bool on_quit(const quit_event&)
    {
        return is_running = false;
    }

    void run_application(const app_config& config)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            GAMEENGINE_ERROR("%s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        // init SDL_image
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
        {
            GAMEENGINE_ERROR("%s", IMG_GetError());
        }

        // init SDL_ttf
        if (TTF_Init() < 0)
        {
            GAMEENGINE_ERROR("%s", TTF_GetError());
        }

        // init SDL_mixer
        if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0 ||
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
        {
            GAMEENGINE_ERROR("%s", Mix_GetError());
        }

        // create window
        auto w_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        SDL_Window* window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.width, config.height, w_flags);

        // create renderer 
        auto r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        auto renderer = SDL_CreateRenderer(window, -1, r_flags);
        if (!window || !renderer)
        {
            GAMEENGINE_ERROR("%s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        input::initialize(window);

        auto dispatcher = input::get_dispatcher();
        dispatcher->add_callback<quit_event>(on_quit);

        auto scene = new ecs::scene(renderer);
        scene->start();

        while (is_running)
        {
            if (input::is_button(SDL_BUTTON_LEFT))
            {
                auto mouse = input::mouse_offset();
                GAMEENGINE_INFO("x position is: %f and y position is: %f", mouse.x, mouse.y);
            }

            if (input::is_key(SDL_SCANCODE_A))
            {
                GAMEENGINE_INFO("Key 'a' is pressed");
            }

            input::dispatch_events();
            SDL_RenderClear(renderer);
            scene->update(0.0f);
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        GAMEENGINE_DELETE(scene);
        IMG_Quit();
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
    }
}