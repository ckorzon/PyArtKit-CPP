#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class RgbColor {
public:
    RgbColor() : red(0), green(0), blue(0) {};
    RgbColor(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {};
    uint8_t red; // Red component
    uint8_t green; // Green component
    uint8_t blue; // Blue component
    bool operator==(const RgbColor& other) const;
};

#endif // COLOR_H
