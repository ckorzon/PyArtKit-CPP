
#include "shapes.h"

Circle::Circle(int centerX, int centerY, int radius)
    : centerX(centerX), centerY(centerY), radius(radius) {}

set<pair<int, int>> Circle::getContainedPixels() const {
    set<pair<int, int>> pixels;
    int rSquared = radius * radius;
    for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy <= rSquared) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

set<pair<int, int>> Circle::getBorderPixels() const {
    set<pair<int, int>> pixels;
    int rSquared = radius * radius;
    for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy == rSquared) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

bool Circle::containsPoint(int x, int y) const {
    int dx = x - centerX;
    int dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void Circle::translate(int dx, int dy) {
    centerX += dx;
    centerY += dy;
}
