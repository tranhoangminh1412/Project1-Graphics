#include "Raster.h"
#include "Color.h"
#include "Color.cpp"
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
    int index = (height - 1 - y) * width + x;
    pixels[index] = pFillColor;
}

void Raster::clear(const Color &pFillColor)
{
    for (int i = 0; i < width * height; ++i)
    {
        pixels[i] = pFillColor;
    }
}

void Raster::writeToPPM(const std::string &filename) const
{
    std::ofstream outFile(filename);

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
        std::cout << "PPM file written: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Error: Could not open the file for writing!" << std::endl;
    }
}

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, const Color &fillColor)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = std::max(std::abs(dx), std::abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    setColorPixel(std::round(x), std::round(y), fillColor);

    for (int i = 0; i < steps; ++i)
    {
        x += xIncrement;
        y += yIncrement;
        setColorPixel(std::round(x), std::round(y), fillColor);
    }
}


int main() {
    Raster raster(100, 100, Red);

    return 0;
}
