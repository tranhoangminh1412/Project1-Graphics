#include <iostream>

using namespace std;

#ifndef VECTOR_H
#define VECTOR_H

struct Vector2 {
    float x;
    float y;

    Vector2();

    Vector2(float px, float py);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;

    float magnitude() const;
    float dot(const Vector2& other) const;
    Vector2 normalize() const;
    Vector2 perpendicular() const;
};

float determinant(const Vector2& a, const Vector2& b);

#endif 