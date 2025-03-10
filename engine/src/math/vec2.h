#pragma once
#include "../pch.h"

namespace engine::math
{
    template<typename T>
    struct Vec2
    {
        T x=0, y=0;

        ENGINE_INLINE Vec2(T x, T y) : x(x), y(y) {}
        ENGINE_INLINE Vec2(T v) : x(v), y(v) {}
        ENGINE_INLINE Vec2() = default;

        //operator (+)
        ENGINE_INLINE Vec2<T> operator+(const Vec2<T> &v2) const
        {
            return Vec2<T>(this->x+v2.x, this->y+v2.y);
        }
        //operator (+=)
        ENGINE_INLINE Vec2<T> &operator+=(const Vec2<T> &v2)
        {
            this->x += v2.x;
            this->y += v2.y;
            return *this;
        }
        //operator (-)
        ENGINE_INLINE Vec2<T> operator-(const Vec2<T> &v2) const
        {
            return Vec2<T>(this->x-v2.x, this->y-v2.y);
        }
        //operator (-=)
        ENGINE_INLINE Vec2<T> &operator-=(const Vec2<T> &v2)
        {
            this->x -= v2.x;
            this->y -= v2.y;
            return *this;
        }
        //operator (*)
        ENGINE_INLINE Vec2<T> operator*(T s) const
        {
            return Vec2<T>(x * s, y * s);
        }
        //operator (*=)
        ENGINE_INLINE Vec2<T> &operator*=(T s)
        {
            this->x *= s;
            this->y *= s;
            return *this;
        }
        //operate (/)
        ENGINE_INLINE Vec2<T> operator/(T s) const
        {
            return Vec2<T>(x / s, y / s);
        }
        //operator (/=)
        ENGINE_INLINE Vec2<T> &operator/=(T s)
        {
            this->x /= s;
            this->y /= s;
            return *this; 
        }
    };
}

namespace engine
{
    using Vec2u = math::Vec2<uint32_t>;
    using Vec2f = math::Vec2<float>;
    using Vec2i = math::Vec2<int>;
}