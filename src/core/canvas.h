#ifndef CANVAS_H
#define CANVAS_H

#include <cstdint>
#include <vector>

class RgbColor {
public:
    RgbColor() : red(0), green(0), blue(0) {};
    RgbColor(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {};
    uint8_t red; // Red component
    uint8_t green; // Green component
    uint8_t blue; // Blue component
    bool operator==(const RgbColor& other) const;
};


class Canvas {
private:
    int width;  // Width of the canvas
    int height; // Height of the canvas

    std::vector<uint8_t> blueAspect; // Blue aspect ratio
    std::vector<uint8_t> greenAspect; // Green aspect ratio
    std::vector<uint8_t> redAspect; // Red aspect ratio

public:
    Canvas(int w, int h);
    Canvas(int w, int h, const RgbColor& backgroundColor);
    int getWidth() const;
    int getHeight() const;
    void resize(int newWidth, int newHeight);
    void setPixel(int x, int y, const RgbColor& color);
    RgbColor getPixel(int x, int y) const;
    void toPNG(const char* filename) const;
};



#endif // CANVAS_H
