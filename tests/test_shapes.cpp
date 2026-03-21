#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "shapes.h"


TEST_CASE("Circle Creation and Containment") {
    Circle circle(0, 0, 5);
    
    REQUIRE(circle.containsPoint(0, 0) == true);
    REQUIRE(circle.containsPoint(3, 4) == true); // 3-4-5 triangle
    REQUIRE(circle.containsPoint(5, 0) == true);
    REQUIRE(circle.containsPoint(6, 0) == false);
}

TEST_CASE("Circle Border Pixels") {
    Circle circle(1, 3, 5);
    auto borderPixels = circle.getBorderPixels();
    
    REQUIRE(borderPixels.count({6, 3}) == 1);
    REQUIRE(borderPixels.count({4, 7}) == 1);
    REQUIRE(borderPixels.count({1, 8}) == 1);
    REQUIRE(borderPixels.count({-4, 3}) == 1);
    REQUIRE(borderPixels.count({1, -2}) == 1);
}

TEST_CASE("Circle Translation") {
    Circle circle(0, 0, 5);
    circle.translate(2, 3);
    
    REQUIRE(circle.containsPoint(2, 3) == true);
    REQUIRE(circle.containsPoint(5, 7) == true); // 3-4-5 triangle
    REQUIRE(circle.containsPoint(7, 3) == true);
    REQUIRE(circle.containsPoint(8, 3) == false);
}

TEST_CASE("Ellipse Creation and Containment") {
    Ellipse ellipse(0, 0, 5, 3);

    REQUIRE(ellipse.getCenterX() == 0);
    REQUIRE(ellipse.getCenterY() == 0);
    REQUIRE(ellipse.getRadiusX() == 5);
    REQUIRE(ellipse.getRadiusY() == 3);

    REQUIRE(ellipse.containsPoint(0, 0) == true);
    REQUIRE(ellipse.containsPoint(3, 0) == true);
    REQUIRE(ellipse.containsPoint(0, 2) == true);
    REQUIRE(ellipse.containsPoint(5, 0) == true);
    REQUIRE(ellipse.containsPoint(-5, 0) == true);
    REQUIRE_FALSE(ellipse.containsPoint(6, 0));
    REQUIRE_FALSE(ellipse.containsPoint(-6, 0));
    REQUIRE_FALSE(ellipse.containsPoint(0, 4));
}

TEST_CASE("Ellipse Translation") {
    Ellipse ellipse(0, 0, 5, 3);
    ellipse.translate(2, 3);

    REQUIRE(ellipse.getCenterX() == 2);
    REQUIRE(ellipse.getCenterY() == 3);
    REQUIRE(ellipse.getRadiusX() == 5);
    REQUIRE(ellipse.getRadiusY() == 3);

    REQUIRE(ellipse.containsPoint(2, 3) == true);
    REQUIRE(ellipse.containsPoint(5, 3) == true);
    REQUIRE(ellipse.containsPoint(2, 5) == true);
    REQUIRE(ellipse.containsPoint(7, 3) == true);
    REQUIRE(ellipse.containsPoint(8, 3) == false);
    REQUIRE(ellipse.containsPoint(2, 7) == false);
}

TEST_CASE("Ellipse Border Pixels") {
    Ellipse ellipse(1, 3, 5, 3);
    auto borderPixels = ellipse.getBorderPixels();
    
    REQUIRE(borderPixels.count({6, 3}) == 1);
    REQUIRE(borderPixels.count({-4, 3}) == 1);
    REQUIRE(borderPixels.count({1, 0}) == 1);
    REQUIRE(borderPixels.count({1, 6}) == 1);
}
