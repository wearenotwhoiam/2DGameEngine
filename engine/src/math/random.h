#pragma once
#include "../pch.h"

namespace Engine::Math
{
    ENGINE_INLINE int Random(int min, int max)
    {
        static thread_local std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
}