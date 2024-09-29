#include <iostream>
using namespace std;

#include "Vector2.h"
#include <cmath> 

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector2 Vector2::normalize() const {
    float mag = magnitude();
    if (mag == 0) {
        return Vector2(0, 0); 
    }
    return Vector2(x / mag, y / mag);
}

Vector2 Vector2::perpendicular() const {
    return Vector2(-y, x); 
}

float determinant(const Vector2& a, const Vector2& b) {
    return (a.x * b.y) - (a.y * b.x);
}
