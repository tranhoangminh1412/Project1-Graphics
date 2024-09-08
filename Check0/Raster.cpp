#include "Raster.h"
#include "Color.h"
#include "Color.cpp"
#include <iostream>
#include <fstream>

// Default constructor: creates an empty raster
Raster::Raster() : width(0), height(0), pixels(nullptr) {}

// Constructor that initializes the raster with a width, height, and fill color
Raster::Raster(int pWidth, int pHeight, const Color& pFillColor)
    : width(pWidth), height(pHeight) {
    pixels = new Color[width * height]; // 1D array to hold Color objects
    clear(pFillColor); // Fill the raster with the specified color
}

// Destructor to free allocated memory
Raster::~Raster() {
    delete[] pixels;
}

// Getter for width
int Raster::getWidth() const {
    return width;
}

// Getter for height
int Raster::getHeight() const {
    return height;
}

// Method to get the color of a pixel at position (x, y)
Color Raster::getColorPixel(int x, int y) const {
    // Convert (x, y) to 1D index: index = y * width + x
    return pixels[y * width + x];
}

// Method to set the color of a pixel at position (x, y)
void Raster::setColorPixel(int x, int y, const Color& pFillColor) {
    // Convert (x, y) to 1D index: index = y * width + x
    pixels[y * width + x] = pFillColor;
}

// Clears the raster by setting all pixels to a specified color
void Raster::clear(const Color& pFillColor) {
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = pFillColor;
    }
}

// Method to write the raster to a PPM file
void Raster::writeToPPM(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        // Write the PPM header
        outFile << "P3\n" << width << " " << height << "\n255\n";

        // Write the pixel data
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Color color = getColorPixel(x, y);
                outFile << static_cast<int>(color.red * 255) << " "
                        << static_cast<int>(color.green * 255) << " "
                        << static_cast<int>(color.blue * 255) << " ";
            }
            outFile << "\n";
        }
        outFile.close();
        std::cout << "PPM file written: " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open the file for writing!" << std::endl;
    }
}

int main() {
    // Create a 10x10 raster and fill it with blue
    Raster raster(10, 10, Blue);

    // Change the color of a pixel at (5, 5) to red
    raster.setColorPixel(5, 5, Red);

    // Write the raster to a PPM file
    raster.writeToPPM("output.ppm");

    return 0;
}