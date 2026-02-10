
#include "shapes.h"

Circle::Circle(long centerX, long centerY, long radius)
    : centerX(centerX), centerY(centerY), radius(radius) {}

set<pair<long, long>> Circle::getContainedPixels() const {
    set<pair<long, long>> pixels;
    long rSquared = radius * radius;
    for (long x = centerX - radius; x <= centerX + radius; ++x) {
        for (long y = centerY - radius; y <= centerY + radius; ++y) {
            long dx = x - centerX;
            long dy = y - centerY;
            if (dx * dx + dy * dy <= rSquared) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

set<pair<long, long>> Circle::getBorderPixels() const {
    set<pair<long, long>> pixels;
    long rSquared = radius * radius;
    for (long x = centerX - radius; x <= centerX + radius; ++x) {
        for (long y = centerY - radius; y <= centerY + radius; ++y) {
            long dx = x - centerX;
            long dy = y - centerY;
            if (dx * dx + dy * dy == rSquared) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

bool Circle::containsPoint(long x, long y) const {
    long dx = x - centerX;
    long dy = y - centerY;
    return dx * dx + dy * dy <= radius * radius;
}

void Circle::translate(long dx, long dy) {
    centerX += dx;
    centerY += dy;
}
