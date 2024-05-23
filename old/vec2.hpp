// =================================================================================
// File Name : vec2.hpp
// Author    :
// Purpose   : Class that mimic the raylib Vector2 struct but with extra
//             functionality.
// TODO      : 
// =================================================================================
#ifndef VEC2_HPP
#define VEC2_HPP

template<typename T>
class Vec2 {
private:
    T _x;
    T _y;
public:
    Vec2() = default;

    // constexpr -> values are known at compile time.
    constexpr Vec2(T x, T y)
        : _x {x}
        , _y {y}
    {}

    constexpr T GetX() const { return _x; }
    constexpr T GetY() const { return _y; }

    constexpr void SetX(T x) { _x = x; }
    constexpr void SeyY(T y) { _y = y; }

    constexpr Vec2 operator+(const Vec2& rhs) const {
        return Vec2(_x + rhs._x, _y + rhs._y);
    }
    constexpr Vec2 operator+(const int& rhs) const {
        return Vec2(_x + rhs, _y + rhs);
    }


    constexpr Vec2 operator-(const Vec2& rhs) const {
        return Vec2(_x - rhs._x, _y - rhs._y);
    }
    constexpr Vec2 operator-(const int& rhs) const {
        return Vec2(_x - rhs, _y - rhs);
    }


    constexpr Vec2 operator*(const Vec2& rhs) const {
        return Vec2(_x * rhs._x, _y * rhs._y);
    }
    constexpr Vec2 operator*(const int& rhs) const {
        return Vec2(_x * rhs, _y * rhs);
    }


    constexpr Vec2& operator+=(const Vec2& rhs) {
        return *this = *this + rhs;
    }
    constexpr Vec2& operator-=(const Vec2& rhs) {
        return *this = *this - rhs;
    }
    constexpr Vec2& operator*=(const Vec2& rhs) {
        return *this = *this * rhs;
    }
    constexpr bool operator==(const Vec2& rhs) const {
        return (_x == rhs._x && _y == rhs._y);
    }
    constexpr bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }
};

#endif // VEC2_HPP
