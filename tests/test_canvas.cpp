
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "canvas.h"
#include "geometry.h"

TEST_CASE("Canvas Initialization and Pixel Manipulation") {
    Canvas canvas(5, 5, RgbColor(255, 0, 0));
    REQUIRE(canvas.getWidth() == 5);
    REQUIRE(canvas.getHeight() == 5);

    RgbColor green = RgbColor(0, 255, 0);
    canvas.setPixel(2, 3, &green);
    RgbColor pixelColorA = canvas.getPixel(2, 3);
    RgbColor pixelColorB = canvas.getPixel(1, 3);

    REQUIRE(pixelColorA.red == 0);
    REQUIRE(pixelColorA.green == 255);
    REQUIRE(pixelColorA.blue == 0);
    
    REQUIRE(pixelColorB.red == 255);
    REQUIRE(pixelColorB.green == 0);
    REQUIRE(pixelColorB.blue == 0);
}


TEST_CASE("Canvas Add Circle") {
    Canvas canvas(10, 10);
    Circle circle(5, 5, 3);
    RgbColor blue(0, 0, 255);
    canvas.addShape(circle, &blue);

    // Check some pixels that should be inside the circle
    REQUIRE(canvas.getPixel(5, 5) == blue); // Center
    REQUIRE(canvas.getPixel(5, 8) == blue); // Bottom
    REQUIRE(canvas.getPixel(5, 2) == blue); // Top
    REQUIRE(canvas.getPixel(8, 5) == blue); // Right
    REQUIRE(canvas.getPixel(2, 5) == blue); // Left

    // Check some pixels that should be outside the circle
    REQUIRE_FALSE(canvas.getPixel(0, 0) == blue);
    REQUIRE_FALSE(canvas.getPixel(9, 9) == blue);
}


TEST_CASE("Canvas Add Square") {
    Canvas canvas(10, 10);
    Polygon square({Vertex(2, 2), Vertex(5, 2), Vertex(5, 5), Vertex(2, 5)});
    RgbColor green(0, 255, 0);
    RgbColor black(0, 0, 0);
    canvas.addShape(square, &green, &black);

    // Check some pixels that should be inside the square
    REQUIRE(canvas.getPixel(2, 2) == black); // Top-left corner
    REQUIRE(canvas.getPixel(3, 3) == green); // Center
    REQUIRE(canvas.getPixel(5, 2) == black); // Top-right corner
    REQUIRE(canvas.getPixel(2, 5) == black); // Bottom-left corner
    REQUIRE(canvas.getPixel(5, 5) == black); // Bottom-right corner

    // Check some pixels that should be outside the square
    REQUIRE_FALSE(canvas.getPixel(1, 1) == green);
    REQUIRE_FALSE(canvas.getPixel(6, 6) == green);
}


TEST_CASE("Draw Shape Partially Outside Canvas") {
    Canvas canvas(10, 10);
    Circle circle(8, 8, 5); // This circle will extend beyond the canvas boundaries
    RgbColor red(255, 0, 0);
    RgbColor blue(0, 0, 255);
    canvas.addShape(circle, &red, &blue);

    // Check some pixels that should be inside the circle and within the canvas
    REQUIRE(canvas.getPixel(8, 8) == red); // Center
    REQUIRE(canvas.getPixel(9, 8) == red); // Right edge
    REQUIRE(canvas.getPixel(8, 9) == red); // Bottom edge
    // REQUIRE(canvas.getPixel(8, 4) == blue); // Top edge

    // Check some pixels that should be outside the circle or outside the canvas
    REQUIRE_FALSE(canvas.getPixel(0, 0) == red);
}
