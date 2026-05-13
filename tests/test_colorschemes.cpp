
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "colorscheme.h"

TEST_CASE("StaticColorScheme returns the correct color") {
    RgbColor red(255, 0, 0);
    StaticColorScheme scheme(red);
    REQUIRE(scheme.getColorForPixel(0, 0) == red);
    REQUIRE(scheme.getColorForPixel(10, 10) == red);
}

TEST_CASE("HorizontalGradientColorScheme returns correct colors") {
    RgbColor leftColor(255, 0, 0);
    RgbColor rightColor(0, 0, 255);
    HorizontalGradientColorScheme scheme(20, 30, leftColor, rightColor);

    REQUIRE(scheme.getColorForPixel(10, 0) == leftColor);
    REQUIRE(scheme.getColorForPixel(20, 0) == leftColor);
    REQUIRE(scheme.getColorForPixel(20, 15) == leftColor);
    REQUIRE(scheme.getColorForPixel(30, 0) == rightColor);
    REQUIRE(scheme.getColorForPixel(34, 0) == rightColor);
    REQUIRE(scheme.getColorForPixel(30, 90) == rightColor);
    REQUIRE(scheme.getColorForPixel(25, 0) == RgbColor(127, 0, 127)); // Midpoint
}

TEST_CASE("VerticalGradientColorScheme returns correct colors") {
    RgbColor topColor(0, 255, 0);
    RgbColor bottomColor(0, 0, 255);
    VerticalGradientColorScheme scheme(10, 20, topColor, bottomColor);
    REQUIRE(scheme.getColorForPixel(0, 5) == topColor);
    REQUIRE(scheme.getColorForPixel(0, 10) == topColor);
    REQUIRE(scheme.getColorForPixel(100, 10) == topColor);
    REQUIRE(scheme.getColorForPixel(0, 20) == bottomColor);
    REQUIRE(scheme.getColorForPixel(50, 20) == bottomColor);
    REQUIRE(scheme.getColorForPixel(0, 15) == RgbColor(0, 127, 127)); // Midpoint
}

TEST_CASE("RadialGradientColorScheme returns correct colors") {
    RgbColor centerColor(255, 255, 0);
    RgbColor edgeColor(255, 0, 255);
    RadialGradientColorScheme scheme(5, 5, 5, centerColor, edgeColor);

    REQUIRE(scheme.getColorForPixel(5, 5) == centerColor); // Center
    REQUIRE(scheme.getColorForPixel(10, 5) == edgeColor); // Edge
    REQUIRE(scheme.getColorForPixel(7, 5) == RgbColor(255, 153, 102)); // Distance = 2
}
