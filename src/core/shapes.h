#ifndef SHAPES_H
#define SHAPES_H

#include <set>
#include <utility>
using namespace std;

class Shape {
    public:
        virtual set<pair<long, long>> getContainedPixels() const = 0;
        virtual set<pair<long, long>> getBorderPixels() const = 0;
        virtual bool containsPoint(long x, long y) const = 0;
        virtual ~Shape() = default;
};


class Circle : public Shape {
    private:
        long centerX;
        long centerY;
        long radius;

    public:
        Circle(long centerX, long centerY, long radius);
        set<pair<long, long>> getContainedPixels() const override;
        set<pair<long, long>> getBorderPixels() const override;
        bool containsPoint(long x, long y) const override;
};

#endif