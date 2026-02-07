
#include "Geometry.h"
#include <algorithm>
#include <stdexcept>

Vertex::Vertex(long x, long y) : x(x), y(y) {}

long Vertex::getX() const {
    return x;
}

long Vertex::getY() const {
    return y;
}

void Vertex::setX(long x) {
    this->x = x;
}

void Vertex::setY(long y) {
    this->y = y;
}

void Vertex::translate(long dx, long dy) {
    this->x += dx;
    this->y += dy;
}

bool Vertex::operator==(const Vertex& other) const {
    return this->x == other.x && this->y == other.y;
}

void Polygon::addVertex(const Vertex& vertex) {
    if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end()) {
        throw std::invalid_argument("Duplicate vertex");
    }
    vertices.push_back(vertex);
}

template<typename... Arguments>
Polygon::Polygon(const Vertex& firstVertex, const Arguments&... remainingVertices) {
    vertices.reserve(1 + sizeof...(remainingVertices));
    addVertex(firstVertex);
    // Fold expression to add remaining vertices (C++17 feature)
    (addVertex(remainingVertices), ...);
}

Polygon::Polygon(std::initializer_list<Vertex> vertexList) {
    vertices.reserve(vertexList.size());
    for (const auto& vertex : vertexList) {
        addVertex(vertex);
    }
}

int Polygon::getVertexCount() const {
    return vertices.size();
}

Vertex Polygon::getVertex(int index) const {
    if (index < 0 || index >= static_cast<int>(vertices.size())) {
        throw std::out_of_range("Index out of range");
    }
    return vertices[index];
}

void Polygon::translate(long dx, long dy) {
    for (auto& vertex : vertices) {
        vertex.translate(dx, dy);
    }
}

long Polygon::getMaxX() const {
    if (vertices.empty()) {
        throw std::runtime_error("Polygon has no vertices");
    }
    long maxX = vertices[0].getX();
    for (const auto& vertex : vertices) {
        if (vertex.getX() > maxX) {
            maxX = vertex.getX();
        }
    }
    return maxX;
}

long Polygon::getMinX() const {
    if (vertices.empty()) {
        throw std::runtime_error("Polygon has no vertices");
    }
    long minX = vertices[0].getX();
    for (const auto& vertex : vertices) {
        if (vertex.getX() < minX) {
            minX = vertex.getX();
        }
    }
    return minX;
}

long Polygon::getMaxY() const {
    if (vertices.empty()) {
        throw std::runtime_error("Polygon has no vertices");
    }
    long maxY = vertices[0].getY();
    for (const auto& vertex : vertices) {
        if (vertex.getY() > maxY) {
            maxY = vertex.getY();
        }
    }
    return maxY;
}

long Polygon::getMinY() const {
    if (vertices.empty()) {
        throw std::runtime_error("Polygon has no vertices");
    }
    long minY = vertices[0].getY();
    for (const auto& vertex : vertices) {
        if (vertex.getY() < minY) {
            minY = vertex.getY();
        }
    }
    return minY;
}

bool Polygon::operator==(const Polygon& other) const {
    if (this->getVertexCount() != other.getVertexCount()) {
        return false;
    }
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (!(this->vertices[i] == other.vertices[i])) {
            return false;
        }
    }
    return true;
}

bool Polygon::containsPoint(long x, long y) const {
    int n = vertices.size();
    if (n < 3) {
        return false; // A polygon must have at least 3 vertices
    }

    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Vertex& vi = vertices[i];
        const Vertex& vj = vertices[j];

        if (((vi.getY() > y) != (vj.getY() > y)) &&
            (x < (vj.getX() - vi.getX()) * (y - vi.getY()) / (vj.getY() - vi.getY()) + vi.getX())) {
            inside = !inside;
        }
    }
    return inside;
}

set<pair<long, long>> Polygon::getContainedPixels() const {
    long minX = getMinX();
    long maxX = getMaxX();
    long minY = getMinY();
    long maxY = getMaxY();
    set<pair<long, long>> pixels;
    for (long x = minX; x <= maxX; ++x) {
        for (long y = minY; y <= maxY; ++y) {
            if (containsPoint(x, y)) {
                pixels.insert({x, y});
            }
        }
    }
    return pixels;
}

set<pair<long, long>> Polygon::getBorderPixels() const {
    set<pair<long, long>> borderPixels;

    int n = vertices.size();

    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Vertex& vi = vertices[i];
        const Vertex& vj = vertices[j];

        // Simple line drawing algorithm (Bresenham's line algorithm)
        long x0 = vi.getX();
        long y0 = vi.getY();
        long x1 = vj.getX();
        long y1 = vj.getY();

        long dx = abs(x1 - x0);
        long dy = abs(y1 - y0);
        long step_x = (x0 < x1) ? 1 : -1;
        long step_y = (y0 < y1) ? 1 : -1;
        long err = dx - dy;

        while (true) {
            borderPixels.insert({x0, y0});
            if (x0 == x1 && y0 == y1) break;
            long e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += step_x;
            }
            if (e2 < dx) {
                err += dx;
                y0 += step_y;
            }
        }
    }

    return borderPixels;
}