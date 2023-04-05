#pragma once

// std libs
#include <set>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>
#include <memory>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

// SDL2 libraries
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_image.h>

#define GAMEENGINE_API __declspec(dllexport)

// export api
//#ifdef GAMEENGINE_EXPORT
//	#ifdef _MSC_VER
//		#define GAMEENGINE_API __declspec(dllexport)
//	#else
//		#define GAMEENGINE_API __attribute__((visibility("default")))
//	#endif
//#else
//	#ifdef _MSC_VER
//		#define GAMEENGINE_API __declspec(dllimport)
//	#else
//		#define GAMEENGINE_API
//	#endif
//#endif


// logging macros
#if defined(_DEBUG)
    #define GAMEENGINE_LOG(level, message, ...) \
            fprintf(stderr, "[%s] ", level); \
            fprintf(stderr, message, ##__VA_ARGS__); \
            fprintf(stderr, "\n");

    #define GAMEENGINE_WARNING(message, ...) GAMEENGINE_LOG("warning", message, ##__VA_ARGS__)
    #define GAMEENGINE_ERROR(message, ...) GAMEENGINE_LOG("error", message, ##__VA_ARGS__)
    #define GAMEENGINE_INFO(message, ...) GAMEENGINE_LOG("info", message, ##__VA_ARGS__)
#else
    #define GAMEENGINE_INFO
    #define GAMEENGINE_ERROR	
    #define GAMEENGINE_WARNING
#endif

// runtime assertion
#define GAMEENGINE_ASSERT assert

// static assertion
#if defined(__clang__) || defined(__gcc__)
    #define GAMEENGINE_STATIC_ASSERT _Static_assert
#else
    #define GAMEENGINE_STATIC_ASSERT static_assert
#endif

// function inlining
#if defined(__clang__) || defined(__gcc__)
    #define GAMEENGINE_INLINE __attribute__((always_inline)) inline
    #define GAMEENGINE_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
    #define GAMEENGINE_INLINE __forceinline
    #define GAMEENGINE_NOINLINE __declspec(noinline)
#else
    #define GAMEENGINE_INLINE inline
    #define GAMEENGINE_NOINLINE
#endif

// free allocated memory and sets it to null pointer
#define GAMEENGINE_DELETE(m) if (m != NULL) { delete (m); m = NULL; }

// attach lamda function to function call
#define GAMEENGINE_BIND(f) [this](auto&&... args)->decltype(auto) \
{ return this->f(std::forward<decltype(args)>(args)...); }

// get current time in second and millisecond
#define get_ticks() SDL_GetTicks()/1000.0f
#define get_ticks_ms() SDL_GetTicks()

// window size
#define INVALID_ID 0
#define MAX_DELTATIME 0.05f

// universal unique id (uuid)
namespace game_engine
{
    using uuid64 = size_t;
    GAMEENGINE_API uuid64 generate_uuid();
}