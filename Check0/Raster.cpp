#include "Raster.h"
#include "Color.cpp"
#include "Vector2.cpp"
#include "Triangle2D.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES

Raster::Raster() : width(0), height(0), pixels(nullptr) {}

Raster::Raster(int pWidth, int pHeight, const Color &pFillColor)
    : width(pWidth), height(pHeight)
{
    pixels = new Color[width * height];
    clear(pFillColor);
}

Raster::~Raster()
{
    delete[] pixels;
}

int Raster::getWidth() const
{
    return width;
}

int Raster::getHeight() const
{
    return height;
}

Color Raster::getColorPixel(int x, int y) const
{
    int index = (height - 1 - y) * width + x;
    return pixels[index];
}

void Raster::setColorPixel(int x, int y, const Color &pFillColor)
{
    if (x < width && y < height)
    {
        int index = (height - 1 - y) * width + x;
        pixels[index] = pFillColor;
    }
}

void Raster::clear(const Color &pFillColor)
{
    for (int i = 0; i < width * height; ++i)
    {
        pixels[i] = pFillColor;
    }
}

void Raster::writeToPPM(const string &filename) const
{
    ofstream outFile(filename);

    if (outFile.is_open())
    {
        outFile << "P3\n"
                << width << " " << height << "\n255\n";

        for (int y = height - 1; y >= 0; --y)
        { // Start from bottom row
            for (int x = 0; x < width; ++x)
            {
                Color color = getColorPixel(x, y);
                outFile << static_cast<int>(color.red * 255) << " "
                        << static_cast<int>(color.green * 255) << " "
                        << static_cast<int>(color.blue * 255) << " ";
            }
            outFile << "\n";
        }
        outFile.close();
        cout << "PPM file written: " << filename << endl;
    }
    else
    {
        cerr << "Error: Could not open the file for writing!" << endl;
    }
}

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, const Color &fillColor)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    setColorPixel(round(x), round(y), fillColor);

    for (int i = 0; i < steps; ++i)
    {
        x += xIncrement;
        y += yIncrement;
        setColorPixel(round(x), round(y), fillColor);
    }
}

void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, const Color &Color1, const Color &Color2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    setColorPixel(round(x), round(y), Color1);

    for (int i = 0; i < steps; ++i)
    {
        float t = static_cast<float>(i) / steps;

        float red = (1 - t) * Color1.red + t * Color2.red;
        float green = (1 - t) * Color1.green + t * Color2.green;
        float blue = (1 - t) * Color1.blue + t * Color2.blue;

        Color interpolatedColor(red, green, blue);
        x += xIncrement;
        y += yIncrement;
        setColorPixel(round(x), round(y), interpolatedColor);
    }
}

void Raster::drawTriangle2D_DotProduct(Triangle2D triangle)
{
    Vector2 v0 = triangle.v1;
    Vector2 v1 = triangle.v2;
    Vector2 v2 = triangle.v3;

    float minX = min({v0.x, v1.x, v2.x});
    float maxX = max({v0.x, v1.x, v2.x});
    float minY = min({v0.y, v1.y, v2.y});
    float maxY = max({v0.y, v1.y, v2.y});

    // Clamp bounding box to raster dimensions
    minX = max(minX, 0.0f);
    maxX = min(maxX, static_cast<float>(width) - 1);
    minY = max(minY, 0.0f);
    maxY = min(maxY, static_cast<float>(height) - 1);

    for (int px = static_cast<int>(minX); px <= static_cast<int>(maxX); ++px)
    {
        for (int py = static_cast<int>(minY); py <= static_cast<int>(maxY); ++py)
        {
            Vector2 P(px + 0.5f, py + 0.5f); // Check the center of the pixel

            // Calculate edge vectors
            Vector2 edge0 = v1 - v0; // Edge from v0 to v1
            Vector2 edge1 = v2 - v1; // Edge from v1 to v2
            Vector2 edge2 = v0 - v2; // Edge from v2 to v0

            // Vectors from each vertex to the point P
            Vector2 toP0 = P - v0; // From v0 to P
            Vector2 toP1 = P - v1; // From v1 to P
            Vector2 toP2 = P - v2; // From v2 to P

            // Compute perpendiculars and dot products
            float dot0 = edge0.perpendicular().dot(toP0);
            float dot1 = edge1.perpendicular().dot(toP1);
            float dot2 = edge2.perpendicular().dot(toP2);

            // If all dot products are positive, P is inside the triangle
            if (dot0 >= 0 && dot1 >= 0 && dot2 >= 0)
            {
                setColorPixel(px, py, triangle.c1); // Set the color of the triangle
            }
        }
    }
}
void Raster::drawTriangle_Barycentric(Triangle2D T)
{
    Vector2 v0 = T.v1;
    Vector2 v1 = T.v2;
    Vector2 v2 = T.v3;
    Color c0 = T.c1;
    Color c1 = T.c2;
    Color c2 = T.c3;

    // // Naïve traversal method
    // for (int px = 0; px < width; ++px)
    // {
    //     for (int py = 0; py < height; ++py)
    //     {
    //         Vector2 P(px + 0.5f, py + 0.5f); // Check the center of the pixel

    //         float lambda1, lambda2, lambda3;
    //         T.calculateBarycentricCoordinates(P, lambda1, lambda2, lambda3);

    //         // Check if the point is inside the triangle
    //         if ((lambda1 + lambda2 + lambda3) <= 1)
    //         {
    //             // Interpolate color based on barycentric coordinates
    //             Color interpolatedColor = c0 * lambda1 + c1 * lambda2 + c2 * lambda3;
    //             setColorPixel(px, py, interpolatedColor);
    //         }
    //     }
    // }

    // Optimization: Bounding Box Method
    int minX = static_cast<int>(max(0.0f, min({v0.x, v1.x, v2.x})));
    int maxX = static_cast<int>(min(static_cast<float>(width - 1), max({v0.x, v1.x, v2.x})));
    int minY = static_cast<int>(max(0.0f, min({v0.y, v1.y, v2.y})));
    int maxY = static_cast<int>(min(static_cast<float>(height - 1), max({v0.y, v1.y, v2.y})));

    for (int px = minX; px <= maxX; ++px)
    {
        for (int py = minY; py <= maxY; ++py)
        {
            Vector2 P(px + 0.5f, py + 0.5f); // Check the center of the pixel

            float lambda1, lambda2, lambda3;
            T.calculateBarycentricCoordinates(P, lambda1, lambda2, lambda3);

            if ((lambda1 + lambda2 + lambda3) <= 1)
            {
                Color interpolatedColor = c0 * lambda1 + c1 * lambda2 + c2 * lambda3;
                setColorPixel(px, py, interpolatedColor);
            }
        }
    }
}



int main()
{
    Raster raster(100, 100, White);

    Triangle2D myTriangle(Vector2(2, 15), Vector2(72, 10), Vector2(45, 80), Red, Green, Blue);
    raster.drawTriangle_Barycentric(myTriangle);

    raster.writeToPPM("output1.ppm");

    return 0;
}
