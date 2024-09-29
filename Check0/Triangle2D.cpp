#include <iostream>
#include "Color.h"
#include "Vector2.h"
#include "Triangle2D.h"

using namespace std;

// Default constructor
Triangle2D ::Triangle2D()
    : v1(0.0f, 0.0f), v2(0.0f, 0.0f), v3(0.0f, 0.0f),
      c1(Black), c2(Black), c3(Black) {}

// Constructor with parameters for vertices and colors
Triangle2D::Triangle2D(const Vector2 &vertex1, const Vector2 &vertex2, const Vector2 &vertex3,
                       const Color &color1, const Color &color2, const Color &color3)
    : v1(vertex1), v2(vertex2), v3(vertex3), c1(color1), c2(color2), c3(color3) {}

float area(const Vector2 &a, const Vector2 &b, const Vector2 &c)
{
    Vector2 edge1 = b - a;
    Vector2 edge2 = c - a;
    return 0.5f * abs(determinant(edge1, edge2));
}

void Triangle2D ::calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3)
{
    // // Calculate edge vectors
    // Vector2 edge0 = v2 - v1; // Edge from v0 to v1
    // Vector2 edge1 = v3 - v2; // Edge from v1 to v2
    // Vector2 edge2 = v1 - v3; // Edge from v2 to v0

    // // Vectors from each vertex to the point P
    // Vector2 toP0 = P - v1; // From v0 to P
    // Vector2 toP1 = P - v2; // From v1 to P
    // Vector2 toP2 = P - v3; // From v2 to P

    // float area = determinant(edge0,edge1)

    // float area0 = determinant(edge0, )

    // Calculate areas of the triangles formed with point P
    float areaABC = area(v1, v2, v3); // Area of triangle ABC
    float areaPAB = area(P, v1, v2);   // Area of triangle PAB
    float areaPBC = area(P, v2, v3);   // Area of triangle PBC
    float areaPCA = area(P, v3, v1);   // Area of triangle PCA

    // Calculate barycentric coordinates
    lambda1 = areaPBC / areaABC; // Area opposite to vertex 1
    lambda2 = areaPCA / areaABC; // Area opposite to vertex 2
    lambda3 = areaPAB / areaABC; // Area opposite to vertex 3
    round(lambda1);
    round(lambda2);
    round(lambda3);
}
