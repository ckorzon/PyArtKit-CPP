#ifndef SHAPES_H
#define SHAPES_H

#include <set>
#include <utility>
#include <cmath>
using namespace std;
#define PI 3.14159265358979323846

class Shape {
    public:
        virtual set<pair<int, int>> getContainedPixels() const = 0;
        virtual set<pair<int, int>> getBorderPixels() const = 0;
        virtual bool containsPoint(int x, int y) const = 0;
        virtual void translate(int dx, int dy) = 0;
        virtual ~Shape() = default;
};


class Circle : public Shape {
    private:
        int centerX;
        int centerY;
        int radius;

    public:
        Circle(int centerX, int centerY, int radius);
        set<pair<int, int>> getContainedPixels() const override;
        set<pair<int, int>> getBorderPixels() const override;
        bool containsPoint(int x, int y) const override;
        void translate(int dx, int dy) override;
};


class Ellipse : public Shape {
    private:
        int centerX;
        int centerY;
        int radiusX;
        int radiusY;

    public:
        Ellipse(int centerX, int centerY, int radiusX, int radiusY);
        set<pair<int, int>> getContainedPixels() const override;
        set<pair<int, int>> getBorderPixels() const override;
        bool containsPoint(int x, int y) const override;
        void translate(int dx, int dy) override;
        int getCenterX() const { return centerX; }
        int getCenterY() const { return centerY; }
        int getRadiusX() const { return radiusX; }
        int getRadiusY() const { return radiusY; }
};


double degreesToRadians(double degrees);

#endif