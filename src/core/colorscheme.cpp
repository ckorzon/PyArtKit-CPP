
#include "colorscheme.h"

RgbColor StaticColorScheme::getColorForPixel(int x, int y) const {
    return color;
}

RgbColor HorizontalGradientColorScheme::getColorForPixel(int x, int y) const {
    // Simple linear interpolation based on x position
    float ratio = static_cast<float>(x - leftBound) / (rightBound - leftBound);
    uint8_t red = static_cast<uint8_t>(leftColor.red * (1 - ratio) + rightColor.red * ratio);
    uint8_t green = static_cast<uint8_t>(leftColor.green * (1 - ratio) + rightColor.green * ratio);
    uint8_t blue = static_cast<uint8_t>(leftColor.blue * (1 - ratio) + rightColor.blue * ratio);
    return RgbColor(red, green, blue);
}

RgbColor VerticalGradientColorScheme::getColorForPixel(int x, int y) const {
    // Simple linear interpolation based on y position
    float ratio = static_cast<float>(y - topBound) / (bottomBound - topBound);
    uint8_t red = static_cast<uint8_t>(topColor.red * (1 - ratio) + bottomColor.red * ratio);
    uint8_t green = static_cast<uint8_t>(topColor.green * (1 - ratio) + bottomColor.green * ratio);
    uint8_t blue = static_cast<uint8_t>(topColor.blue * (1 - ratio) + bottomColor.blue * ratio);
    return RgbColor(red, green, blue);
}

RgbColor RadialGradientColorScheme::getColorForPixel(int x, int y) const {
    // Simple radial interpolation based on distance from the center
    float distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
    float ratio = std::min(distance / radius, 1.0f);
    uint8_t red = static_cast<uint8_t>(centerColor.red * (1 - ratio) + edgeColor.red * ratio);
    uint8_t green = static_cast<uint8_t>(centerColor.green * (1 - ratio) + edgeColor.green * ratio);
    uint8_t blue = static_cast<uint8_t>(centerColor.blue * (1 - ratio) + edgeColor.blue * ratio);
    return RgbColor(red, green, blue);
}
