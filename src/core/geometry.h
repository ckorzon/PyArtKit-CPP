
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <initializer_list>
#include "shapes.h"

class Vertex {
    private:
        int x;
        int y;

    public:
        Vertex(int x, int y);
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        void translate(int dx, int dy);
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
        void translate(int dx, int dy) override;
        int getMaxX() const;
        int getMinX() const;
        int getMaxY() const;
        int getMinY() const;
        bool operator==(const Polygon& other) const;
        set<pair<int, int>> getContainedPixels() const override;
        set<pair<int, int>> getBorderPixels() const override;
        bool containsPoint(int x, int y) const override;
};

#endif // GEOMETRY_H
