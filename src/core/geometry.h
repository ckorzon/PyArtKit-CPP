
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <initializer_list>
#include "shapes.h"

class Vertex {
    private:
        long x;
        long y;

    public:
        Vertex(long x, long y);
        long getX() const;
        long getY() const;
        void setX(long x);
        void setY(long y);
        void translate(long dx, long dy);
        bool operator==(const Vertex& other) const;
};


class Polygon : public Shape {
    private:
        std::vector<Vertex> vertices;

    public:
        template<typename... Arguments>
        Polygon(const Vertex& firstVertex, const Arguments&... remainingVertices);
        Polygon(std::initializer_list<Vertex> vertexList);
        Polygon() {};
        void addVertex(const Vertex& vertex);
        int getVertexCount() const;
        Vertex getVertex(int index) const;
        void translate(long dx, long dy);
        long getMaxX() const;
        long getMinX() const;
        long getMaxY() const;
        long getMinY() const;
        bool operator==(const Polygon& other) const;
        set<pair<long, long>> getContainedPixels() const override;
        set<pair<long, long>> getBorderPixels() const override;
        bool containsPoint(long x, long y) const override;
};

#endif // GEOMETRY_H
