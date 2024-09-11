#include <iostream>
#include "Color.h"
#include <algorithm>  

using namespace std;

Color::Color() : red(0.0), green(0.0), blue(0.0) {}

Color::Color(float pRed, float pGreen, float pBlue) 
    : red(pRed), green(pGreen), blue(pBlue) {
    clamp();
}

void Color::clamp() {
    red = min(1.0f, max(0.0f, red));
    green = min(1.0f, max(0.0f, green));
    blue = min(1.0f, max(0.0f, blue));
}

Color Color::operator+(const Color& other) const {
    Color result(red + other.red, green + other.green, blue + other.blue);
    result.clamp();
    return result;
}

Color Color::operator-(const Color& other) const {
    Color result(red - other.red, green - other.green, blue - other.blue);
    result.clamp();
    return result;
}

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
    
//     Color c4 = Red;  
//     cout << "Red: " << c4.red << ", Green: " << c4.green << ", Blue: " << c4.blue << endl;

//     return 0;
// }
