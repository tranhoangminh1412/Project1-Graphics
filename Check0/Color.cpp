#include <iostream>
#include "Color.h"
#include <algorithm>  // For std::min and std::max

using namespace std;

// Default constructor - sets color to black
Color::Color() : red(0.0), green(0.0), blue(0.0) {}

// Constructor that sets red, green, and blue values
Color::Color(float pRed, float pGreen, float pBlue) 
    : red(pRed), green(pGreen), blue(pBlue) {
    clamp();
}

// Clamp method to keep color values between 0.0 and 1.0
void Color::clamp() {
    red = std::min(1.0f, std::max(0.0f, red));
    green = std::min(1.0f, std::max(0.0f, green));
    blue = std::min(1.0f, std::max(0.0f, blue));
}

// Overload the addition operator
Color Color::operator+(const Color& other) const {
    Color result(red + other.red, green + other.green, blue + other.blue);
    result.clamp();
    return result;
}

// Overload the subtraction operator
Color Color::operator-(const Color& other) const {
    Color result(red - other.red, green - other.green, blue - other.blue);
    result.clamp();
    return result;
}

// Overload the multiplication operator (scaling)
Color Color::operator*(float scalar) const {
    Color result(red * scalar, green * scalar, blue * scalar);
    result.clamp();
    return result;
}

// int main() {
//     Color c1(1.0f, 0.25f, 0.25f);
//     Color c2(0.0f, 0.5f, 1.0f);
//     Color c3 = c1 + c2;
//     cout << "Red: " << c3.red << ", Green: " << c3.green << ", Blue: " << c3.blue << endl;
    
//     Color c4 = Red;  // Should initialize to pure red
//     cout << "Red: " << c4.red << ", Green: " << c4.green << ", Blue: " << c4.blue << endl;

//     return 0;
// }
