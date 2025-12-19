#include "pngwriter.h"
#include <stdexcept>

void writePNG(const char* filename, const Canvas& canvas) {
    int width = canvas.getWidth();
    int height = canvas.getHeight();

    // Open a new file to write the PNG image to
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        throw std::runtime_error("Failed to open file for writing PNG");
    }

    // Create PNG write structure
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        throw std::runtime_error("Failed to create PNG write structure");
    }

    // Create PNG info structure
    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        throw std::runtime_error("Failed to create PNG info structure");
    }

    // Set up error handling
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        throw std::runtime_error("Error during PNG creation");
    }

    png_init_io(png, fp);

    // Set image metadata
    png_set_IHDR(
        png, info, width, height,
        8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png, info);

    // Write pixel data, one row at a time
    for (int y = 0; y < height; ++y) {
        std::vector<png_byte> row(width * 3);
        for (int x = 0; x < width; ++x) {
            RgbColor color = canvas.getPixel(x, y);
            row[x * 3 + 0] = color.red;
            row[x * 3 + 1] = color.green;
            row[x * 3 + 2] = color.blue;
        }
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);

    png_destroy_write_struct(&png, &info);
    fclose(fp);
}
