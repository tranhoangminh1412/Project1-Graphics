#ifndef RASTER_H
#define RASTER_H

#include "Color.h"

class Raster {
private:
    int width;
    int height;
    Color* pixels; 

public:
    Raster();

    Raster(int pWidth, int pHeight, const Color& pFillColor);

    // Destructor
    ~Raster();

    int getWidth() const;
    int getHeight() const;

    Color getColorPixel(int x, int y) const;

    void setColorPixel(int x, int y, const Color& pFillColor);

    void clear(const Color& pFillColor);

    void writeToPPM(const string& filename) const;

    void drawLine_DDA(float x1, float y1, float x2, float y2, const Color& fillColor);

};

#endif 
