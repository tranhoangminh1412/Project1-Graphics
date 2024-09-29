#include <iostream>
#include "Color.h"
#include "Vector2.h"

using namespace std;

#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Triangle2D
{
    Vector2 v1, v2, v3;

    // Colors corresponding to each vertex
    Color c1, c2, c3;

    // Default constructor
    Triangle2D();

    // Constructor with parameters for vertices and colors
    Triangle2D(const Vector2 &vertex1, const Vector2 &vertex2, const Vector2 &vertex3,
               const Color &color1, const Color &color2, const Color &color3);

    void calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2,float &lambda3);
};

#endif