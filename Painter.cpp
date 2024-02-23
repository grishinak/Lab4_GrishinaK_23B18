#include "Painter.h"

Painter::Painter(std::uint32_t width, std::uint32_t height) {
    header.type = 0x4D42; // "BM"
    header.size = sizeof(BMPHeader) + width * height * 3;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offset = sizeof(BMPHeader);
    header.header_size = 40;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bit_count = 24; // 24 bits per pixel
    header.compression = 0;
    header.image_size = 0;
    header.x_pixels_per_meter = 0;
    header.y_pixels_per_meter = 0;
    header.colors_used = 0;
    header.colors_important = 0;

    pixels.resize(width * height * 3, 255); // Initialize with white pixels
}

void Painter::setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    if (x < header.width && y < header.height) {
        size_t index = (y * header.width + x) * 3;
        pixels[index] = b;
        pixels[index + 1] = g;
        pixels[index + 2] = r;
    }
}

void Painter::save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Couldn't open file " << filename << " for writing\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    file.write(reinterpret_cast<char*>(pixels.data()), pixels.size());

    file.close();
}
