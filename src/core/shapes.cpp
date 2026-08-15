
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

Ellipse::Ellipse(int centerX, int centerY, int radiusX, int radiusY)
    : centerX(centerX), centerY(centerY), radiusX(radiusX), radiusY(radiusY) {}

set<pair<int, int>> Ellipse::getContainedPixels() const {
    set<pair<int, int>> pixels;
    for (int x = centerX - radiusX; x <= centerX + radiusX; ++x) {
        for (int y = centerY - radiusY; y <= centerY + radiusY; ++y) {
            if (this->containsPoint(x, y)) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

set<pair<int, int>> Ellipse::getBorderPixels() const {
    set<pair<int, int>> pixels;
    for (int x = centerX - radiusX; x <= centerX + radiusX; ++x) {
        for (int y = centerY - radiusY; y <= centerY + radiusY; ++y) {
            if (this->containsPoint(x, y)) {
                // Check if any of the 8 surrounding pixels are outside the ellipse
                bool isBorder = false;
                for (int dx = -1; dx <= 1 && !isBorder; ++dx) {
                    for (int dy = -1; dy <= 1 && !isBorder; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        if (!this->containsPoint(x + dx, y + dy)) {
                            isBorder = true;
                        }
                    }
                }
                if (isBorder) {
                    pixels.insert({x, y});
                }
            }
        }
    }
    return pixels;
}

bool Ellipse::containsPoint(int x, int y) const {
    // Need to use double precision here to avoid integer division issues (rounds down)
    double dx = x - centerX;
    double dy = y - centerY;
    double xComponent = (dx * dx) / (radiusX * radiusX);
    double yComponent = (dy * dy) / (radiusY * radiusY);
    return (xComponent + yComponent) <= 1;
}

void Ellipse::translate(int dx, int dy) {
    centerX += dx;
    centerY += dy;
}

HalfCircle::HalfCircle(int centerX, int centerY, int radius, pair<int, int> normalVector)
    : centerX(centerX), centerY(centerY), radius(radius), normalVector(normalVector) {}

set<pair<int, int>> HalfCircle::getContainedPixels() const {
    set<pair<int, int>> pixels;
    int rSquared = radius * radius;
    for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy <= rSquared) {
                if ((normalVector.first * dx + normalVector.second * dy) >= 0) {
                    pixels.insert({x, y});
                }
            }
        }
    }
    return pixels;
}

set<pair<int, int>> HalfCircle::getBorderPixels() const {
    set<pair<int, int>> pixels;
    int rSquared = radius * radius;
    for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy == rSquared) {
                if ((normalVector.first * dx + normalVector.second * dy) >= 0) {
                    pixels.insert({x, y});
                }
            }
        }
    }
    return pixels;
}

bool HalfCircle::containsPoint(int x, int y) const {
    int dx = x - centerX;
    int dy = y - centerY;
    if (dx * dx + dy * dy <= radius * radius) {
        // Check if the point is on the correct side of the normal vector
        return (normalVector.first * dx + normalVector.second * dy) >= 0;
    }
    return false;
}

void HalfCircle::translate(int dx, int dy) {
    centerX += dx;
    centerY += dy;
}

double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}
