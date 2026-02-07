
#include "Canvas.h"
#include <stdexcept>
#include "pngwriter.h"


bool RgbColor::operator==(const RgbColor& other) const {
    return (red == other.red && green == other.green && blue == other.blue);
}

Canvas::Canvas(int w, int h) : width(w), height(h) {
    blueAspect.resize(w * h, 0);
    greenAspect.resize(w * h, 0);
    redAspect.resize(w * h, 0);
}

Canvas::Canvas(int w, int h, const RgbColor& backgroundColor) : width(w), height(h) {
    blueAspect.resize(w * h, backgroundColor.blue);
    greenAspect.resize(w * h, backgroundColor.green);
    redAspect.resize(w * h, backgroundColor.red);
}

int Canvas::getWidth() const {
    return width;
}

int Canvas::getHeight() const {
    return height;
}

void Canvas::resize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    blueAspect.resize(newWidth * newHeight, 0);
    greenAspect.resize(newWidth * newHeight, 0);
    redAspect.resize(newWidth * newHeight, 0);
}

void Canvas::setPixel(int x, int y, const RgbColor* color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    int index = y * width + x;
    blueAspect[index] = color->blue;
    greenAspect[index] = color->green;
    redAspect[index] = color->red;
}

bool Canvas::contains(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 || y < height);
}

void Canvas::addShape(const Shape& shape, const RgbColor* fillColor, const RgbColor* borderColor) {
    const set<pair<long, long>> pixels = shape.getContainedPixels();
    for (const auto& pixel : pixels) {
        // Allow shapes to fall partially outside of the canvas
        if (!this->contains(pixel.first, pixel.second)){
            continue;
        }
        setPixel(pixel.first, pixel.second, fillColor);
    }
    if (borderColor != nullptr) {
        const set<pair<long, long>> borderPixels = shape.getBorderPixels();
        for (const auto& pixel : borderPixels) {
            if (!this->contains(pixel.first, pixel.second)){
                continue;
            }
            setPixel(pixel.first, pixel.second, borderColor);
        }
    }
}

uint8_t Canvas::getPixelRed(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    int index = y * width + x;
    return redAspect[index];
}

uint8_t Canvas::getPixelGreen(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    int index = y * width + x;
    return greenAspect[index];
}

uint8_t Canvas::getPixelBlue(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    int index = y * width + x;
    return blueAspect[index];
}

RgbColor Canvas::getPixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }
    int index = y * width + x;
    return RgbColor(redAspect[index], greenAspect[index], blueAspect[index]);
}

void Canvas::toPNG(const char* filename) const {
    writePNG(filename, *this);
}
