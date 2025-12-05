#include <iostream>
using namespace std;
#include "Geometry.h"

int main() {
    cout << "Testing Vertex class" << endl;
    Vertex* v = new Vertex(10, 20);
    v->translate(5, 10);
    long currentX = v->getX();
    long currentY = v->getY();
    cout << "Vertex after translation: (" << currentX << ", " << currentY << ")" << endl;
    v->setX(32);
    v->setY(64);
    cout << "Vertex after setting new coordinates: (" << v->getX() << ", " << v->getY() << ")" << endl;
    cout << "Tests completed successfully!" << endl;
    return 0;
}
