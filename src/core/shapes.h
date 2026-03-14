#ifndef SHAPES_H
#define SHAPES_H

#include <set>
#include <utility>
using namespace std;

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

#endif