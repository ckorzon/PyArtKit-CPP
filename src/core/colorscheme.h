
#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include "color.h"
#include <cmath>
#include <algorithm>

class ColorScheme {
    public:
        virtual RgbColor getColorForPixel(int x, int y) const = 0;
};


class StaticColorScheme : public ColorScheme {
    private:
        RgbColor color;
    public:
        StaticColorScheme(const RgbColor& color) : color(color) {}
        RgbColor getColorForPixel(int x, int y) const override;
        void setColor(const RgbColor& newColor) { color = newColor; }
        RgbColor getColor() const { return color; }
};


class HorizontalGradientColorScheme : public ColorScheme {
    private:
        RgbColor leftColor;
        RgbColor rightColor;
        int leftBound;
        int rightBound;
    public:
        HorizontalGradientColorScheme(int leftBound, int rightBound, const RgbColor& leftColor, const RgbColor& rightColor) 
            : leftColor(leftColor), rightColor(rightColor), leftBound(leftBound), rightBound(rightBound) {}
        
        RgbColor getColorForPixel(int x, int y) const override;
        void setLeftColor(const RgbColor& newLeftColor) { leftColor = newLeftColor; }
        void setRightColor(const RgbColor& newRightColor) { rightColor = newRightColor; }
        RgbColor getLeftColor() const { return leftColor; }
        RgbColor getRightColor() const { return rightColor; }
        void setBounds(int newLeftBound, int newRightBound) { leftBound = newLeftBound; rightBound = newRightBound; }
        int getLeftBound() const { return leftBound; }
        int getRightBound() const { return rightBound; }
};


class VerticalGradientColorScheme : public ColorScheme {
    private:
        RgbColor topColor;
        RgbColor bottomColor;
        int topBound;
        int bottomBound;
    public:
        VerticalGradientColorScheme(int topBound, int bottomBound,const RgbColor& topColor, const RgbColor& bottomColor) 
            : topColor(topColor), bottomColor(bottomColor), topBound(topBound), bottomBound(bottomBound) {}
        
        RgbColor getColorForPixel(int x, int y) const override;
        void setTopColor(const RgbColor& newTopColor) { topColor = newTopColor; }
        void setBottomColor(const RgbColor& newBottomColor) { bottomColor = newBottomColor; }
        RgbColor getTopColor() const { return topColor; }
        RgbColor getBottomColor() const { return bottomColor; }
        void setBounds(int newTopBound, int newBottomBound) { topBound = newTopBound; bottomBound = newBottomBound; }
        int getTopBound() const { return topBound; }
        int getBottomBound() const { return bottomBound; }
};


class RadialGradientColorScheme : public ColorScheme {
    private:
        RgbColor centerColor;
        RgbColor edgeColor;
        int centerX;
        int centerY;
        int radius;
    public:
        RadialGradientColorScheme(int centerX, int centerY, int radius, const RgbColor& centerColor, const RgbColor& edgeColor) 
            : centerColor(centerColor), edgeColor(edgeColor), centerX(centerX), centerY(centerY), radius(radius) {}
        
        RgbColor getColorForPixel(int x, int y) const override;
        void setCenterColor(const RgbColor& newCenterColor) { centerColor = newCenterColor; }
        void setEdgeColor(const RgbColor& newEdgeColor) { edgeColor = newEdgeColor; }
        RgbColor getCenterColor() const { return centerColor; }
        RgbColor getEdgeColor() const { return edgeColor; }
        void setCenter(int newCenterX, int newCenterY) { centerX = newCenterX; centerY = newCenterY; }
        int getCenterX() const { return centerX; }
        int getCenterY() const { return centerY; }
        void setRadius(int newRadius) { radius = newRadius; }
        int getRadius() const { return radius; }
};

#endif // COLORSCHEME_H
