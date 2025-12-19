#ifndef PNGWRITER_H
#define PNGWRITER_H

#include <png.h>
#include <vector>
#include "canvas.h"

void writePNG(const char* filename, const Canvas& canvas);

#endif // PNGWRITER_H
