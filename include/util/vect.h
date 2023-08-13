#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>

template <class T>
struct Vect
{
    T x, y;

    Vect() : x(0), y(0) {}
    Vect(T value) : x(value), y(value) {}
    Vect(T x, T y) : x(x), y(y) {}
    Vect(const nlohmann::json& jsonPair) : x(jsonPair[0].get<T>()), y(jsonPair[1].get<T>()) {}

    void print() const { std::cout << "(" << x << ", " << y << ")" << std::endl; }
    template <class U> const Vect<U> cast() const { return Vect<U>(static_cast<U>(x), static_cast<U>(y)); }

    Vect<T>& operator+=(const Vect<T>& other) { x += other.x; y += other.y; return *this; }
    Vect<T>& operator-=(const Vect<T>& other) { x -= other.x; y -= other.y; return *this; }
    Vect<T>& operator*=(const Vect<T>& other) { x *= other.x; y *= other.y; return *this; }
    Vect<T>& operator/=(const Vect<T>& other) { x /= other.x; y /= other.y; return *this; }
    Vect<T>& operator%=(const Vect<T>& other) { x %= other.x; y %= other.y; return *this; }

    Vect<T>& operator+=(const T& other) { x += other; y += other; return *this; }
    Vect<T>& operator-=(const T& other) { x -= other; y -= other; return *this; }
    Vect<T>& operator*=(const T& other) { x *= other; y *= other; return *this; }
    Vect<T>& operator/=(const T& other) { x /= other; y /= other; return *this; }
    Vect<T>& operator%=(const T& other) { x %= other; y %= other; return *this; }


    Vect<T> operator+(const Vect<T>& other) const { return Vect<T>(x + other.x, y + other.y); }
    Vect<T> operator-(const Vect<T>& other) const { return Vect<T>(x - other.x, y - other.y); }
    Vect<T> operator*(const Vect<T>& other) const { return Vect<T>(x * other.x, y * other.y); }
    Vect<T> operator/(const Vect<T>& other) const { return Vect<T>(x / other.x, y / other.y); }
    Vect<T> operator%(const Vect<T>& other) const { return Vect<T>(x % other.x, y % other.y); }

    Vect<T> operator+(const T& other) const { return Vect<T>(x + other, y + other); }
    Vect<T> operator-(const T& other) const { return Vect<T>(x - other, y - other); }
    Vect<T> operator*(const T& other) const { return Vect<T>(x * other, y * other); }
    Vect<T> operator/(const T& other) const { return Vect<T>(x / other, y / other); }
    Vect<T> operator%(const T& other) const { return Vect<T>(x % other, y % other); }


    const bool operator==(const Vect<T>& other) const { return x == other.x && y == other.y; }
    const bool operator!=(const Vect<T>& other) const { return x != other.x || y != other.y; }
    const bool operator>=(const Vect<T>& other) const { return x >= other.x && y >= other.y; }
    const bool operator<=(const Vect<T>& other) const { return x <= other.x && y <= other.y; }
    const bool operator>(const Vect<T>& other) const { return x > other.x && y > other.y; }
    const bool operator<(const Vect<T>& other) const { return x < other.x && y < other.y; }

    const bool operator==(const T& other) const { return x == other && y == other; }
    const bool operator!=(const T& other) const { return x != other || y != other; }
    const bool operator>=(const T& other) const { return x >= other && y >= other; }
    const bool operator<=(const T& other) const { return x <= other && y <= other; }
    const bool operator>(const T& other) const { return x > other && y > other; }
    const bool operator<(const T& other) const { return x < other && y < other; }
};