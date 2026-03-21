
#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include "color.h"

class ColorScheme {
    public:
        virtual RgbColor getColorForPixel(int x, int y) const = 0;
};




#endif // COLORSCHEME_H
