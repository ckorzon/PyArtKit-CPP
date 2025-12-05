
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/canvas.h"

TEST_CASE("Canvas Initialization and Pixel Manipulation") {
    Canvas canvas(5, 5, RgbColor(255, 0, 0));
    REQUIRE(canvas.getWidth() == 5);
    REQUIRE(canvas.getHeight() == 5);

    canvas.setPixel(2, 3, RgbColor(0, 255, 0));
    RgbColor pixelColorA = canvas.getPixel(2, 3);
    RgbColor pixelColorB = canvas.getPixel(1, 3);

    REQUIRE(pixelColorA.red == 0);
    REQUIRE(pixelColorA.green == 255);
    REQUIRE(pixelColorA.blue == 0);
    
    REQUIRE(pixelColorB.red == 255);
    REQUIRE(pixelColorB.green == 0);
    REQUIRE(pixelColorB.blue == 0);
}

