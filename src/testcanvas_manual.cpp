
#include <iostream>
using namespace std;
#include "Canvas.h"

int main() {
    Canvas canvas(5, 5, RgbColor(255, 0, 0));
    cout << "Canvas created with dimensions: " << canvas.getWidth() << "x" << canvas.getHeight() << endl;
    canvas.setPixel(2, 3, RgbColor(0, 255, 0));
    RgbColor pixelColorA = canvas.getPixel(2, 3);
    RgbColor pixelColorB = canvas.getPixel(1, 3);
    cout << "Pixel at (2, 3) color: (" << (int)pixelColorA.red << ", " << (int)pixelColorA.green << ", " << (int)pixelColorA.blue << ")" << endl;
    cout << "Pixel at (1, 3) color: (" << (int)pixelColorB.red << ", " << (int)pixelColorB.green << ", " << (int)pixelColorB.blue << ")" << endl;
    canvas.resize(100, 100);
    cout << "Canvas resized to: " << canvas.getWidth() << "x" << canvas.getHeight() << endl;
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            canvas.setPixel(x, y, RgbColor(x % 256, y % 256, (x + y) % 256));
        }
    }
    canvas.toPNG("test_output.png");
    cout << "PNG image 'test_output.png' created." << endl;
    return 0;
};
