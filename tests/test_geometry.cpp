#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/geometry.h"

TEST_CASE("Vertex Creation and Manipulation") {
    Vertex v(10, 20);
    REQUIRE(v.getX() == 10);
    REQUIRE(v.getY() == 20);

    v.setX(30);
    v.setY(40);
    REQUIRE(v.getX() == 30);
    REQUIRE(v.getY() == 40);

    v.translate(5, -10);
    REQUIRE(v.getX() == 35);
    REQUIRE(v.getY() == 30);
}


TEST_CASE("Polygon Creation and Vertex Management") {
    Vertex v1(0, 0);
    Vertex v2(10, 0);
    Vertex v3(10, 10);
    Vertex v4(0, 10);

    Polygon poly({v1, v2, v3});
    REQUIRE(poly.getVertexCount() == 3);
    REQUIRE(poly.getVertex(0) == v1);
    REQUIRE(poly.getVertex(1) == v2);
    REQUIRE(poly.getVertex(2) == v3);

    poly.addVertex(v4);
    REQUIRE(poly.getVertexCount() == 4);
    REQUIRE(poly.getVertex(3) == v4);

    REQUIRE_THROWS_AS(poly.addVertex(v1), std::invalid_argument); // Duplicate vertex
}

TEST_CASE("Polygon Translation and Bounding Box") {
    Polygon poly({Vertex(0, 0), Vertex(10, 0), Vertex(10, 10), Vertex(0, 10)});
    
    REQUIRE(poly.getMinX() == 0);
    REQUIRE(poly.getMaxX() == 10);
    REQUIRE(poly.getMinY() == 0);
    REQUIRE(poly.getMaxY() == 10);

    poly.translate(5, 5);
    
    REQUIRE(poly.getMinX() == 5);
    REQUIRE(poly.getMaxX() == 15);
    REQUIRE(poly.getMinY() == 5);
    REQUIRE(poly.getMaxY() == 15);
}
