#pragma once

//std libs
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <set>
#include <random>
#include <limits>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_map>

//SDL2 libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

//export API
#ifdef ENGINE_EXPORT
	#ifdef _MSC_VER
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __attribute__((visibility("default")))
	#endif
#else
	#ifdef _MSC_VER
		#define ENGINE_API __declspec(dllimport)
	#else
		#define ENGINE_API
	#endif
#endif

//Message Logger
//Only works when in DEBUG mode or it eats dirt
#if defined(_DEBUG)
	#define ENGINE_LOG(level, message, ...) \
		fprintf(stderr, "[%s] ", level); \
		fprintf(stderr, message, ##__VA_ARGS__); \
		fprintf(stderr, "\n");\

	#define ENGINE_INFO(message, ...) ENGINE_LOG("info", message, ##__VA_ARGS__)
	#define ENGINE_ERROR(message, ...) ENGINE_LOG("error", message, ##__VA_ARGS__)
	#define ENGINE_WARNING(message, ...) ENGINE_LOG("warning", message, ##__VA_ARGS__)
#else
	#define ENGINE_INFO
	#define ENGINE_ERROR
	#define ENGINE_WARNING
#endif

//Essentially making own macros out of macros
//Runtime Assertion
#define ENGINE_ASSERT assert
//Static Assertion
#if defined(__clang__) || defined(__gcc__)
	#define ENGINE_STATIC_ASSERT _Static_assert
#else
	#define ENGINE_STATIC_ASSERT static_assert
#endif

//Function Inlining
#if defined(__clang__) || defined(__gcc__)
	#define ENGINE_INLINE __attribute__((always_inline)) inline
	#define ENGINE_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
	#define ENGINE_INLINE __forceinline
	#define ENGINE_NOINLINE __declspec(noinline)
#else
	#define ENGINE_INLINE inline
	#define ENGINE_NOINLINE
#endif

//CONSTANTS
//Free allocated memory, sets to null pointer
#define ENGINE_DELETE(m) if(m!=NULL) {delete (m); m = NULL;}

//Attach lambda function to function call
#define ENGINE_BIND(f) [this](auto&&... args)->decltype(auto) \
{return this->f(std::forward<decltype(args)>(args)...);}

//Get Current Time - second/millisecond
#define GetTicks() SDL_GetTicks()/1000.f
#define GetTicks_ms() SDL_GetTicks()

//Window Size
#define INVALID_ID 0
#define MAX_DELTATIME 0.05f

//Universal UID
namespace engine
{
	using uuid64 = uint64_t;
	ENGINE_API uuid64 GenerateUUID();
}

