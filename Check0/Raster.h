#ifndef RASTER_H
#define RASTER_H

#include "Color.h"

class Raster {
private:
    int width;
    int height;
    Color* pixels; // 1D array of Color objects

public:
    // Default constructor (creates an empty raster)
    Raster();

    // Constructor that takes width, height, and fill color
    Raster(int pWidth, int pHeight, const Color& pFillColor);

    // Destructor
    ~Raster();

    // Getters
    int getWidth() const;
    int getHeight() const;

    // Method to get the Color of a pixel at (x, y)
    Color getColorPixel(int x, int y) const;

    // Method to set the Color of a pixel at (x, y)
    void setColorPixel(int x, int y, const Color& pFillColor);

    // Clears the raster to a specified color
    void clear(const Color& pFillColor);

    // Write the raster's array data to a PPM file
    void writeToPPM(const std::string& filename) const;
};

#endif // RASTER_H
