#include "Painter.h"
#include <cmath>

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

void Painter::drawCircle(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
        const int radius = 5; // половина диаметра
        for (int i = x - radius; i <= x + radius; ++i) {
            for (int j = y - radius; j <= y + radius; ++j) {
                if (std::sqrt((i - x) * (i - x) + (j - y) * (j - y)) <= radius) {
                    setPixel(i, j, r, g, b);
                }
            }
        }
    }

void Painter::drawLine(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2,
                       std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    int dx = std::abs(static_cast<int>(x2) - static_cast<int>(x1));
    int dy = -std::abs(static_cast<int>(y2) - static_cast<int>(y1));
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        setPixel(x1, y1, r, g, b);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
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