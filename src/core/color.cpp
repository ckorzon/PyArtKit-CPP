
#include "color.h"

bool RgbColor::operator==(const RgbColor& other) const {
    return (red == other.red && green == other.green && blue == other.blue);
}
