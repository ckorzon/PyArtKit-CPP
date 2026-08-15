#ifndef CANVAS_H
#define CANVAS_H

#include <cstdint>
#include <vector>
#include <memory>
#include "shapes.h"
#include "colorscheme.h"

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
    void setPixel(int x, int y, const RgbColor* color);
    void setPixel(int x, int y, const ColorScheme* color);
    void addShape(const Shape& shape, const RgbColor* fillColor, const RgbColor* borderColor = nullptr);
    void addShape(const Shape& shape, const ColorScheme* fillColor, const ColorScheme* borderColor = nullptr);
    RgbColor getPixel(int x, int y) const;
    uint8_t getPixelRed(int x, int y) const;
    uint8_t getPixelGreen(int x, int y) const;
    uint8_t getPixelBlue(int x, int y) const;
    void toPNG(const char* filename) const;
    bool contains(int x, int y) const;
};


#endif // CANVAS_H
