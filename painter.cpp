#include "painter.h"

#include <cmath>
#include <vector>
#include <algorithm>

Painter::Painter(std::uint32_t width, std::uint32_t height) {
    header_.type_ = 0x4D42; // "BM"
    header_.size_ = sizeof(BMPHeader) + width * height * 3;
    header_.reserved1_ = 0;
    header_.reserved2_ = 0;
    header_.offset_ = sizeof(BMPHeader);
    header_.header_size_ = 40;
    header_.width_ = width;
    header_.height_ = height;
    header_.planes_ = 1;
    header_.bit_count_ = 24; // 24 bits per pixel
    header_.compression_ = 0;
    header_.image_size_ = 0;
    header_.x_pixels_per_meter_ = 0;
    header_.y_pixels_per_meter_ = 0;
    header_.colors_used_ = 0;
    header_.colors_important_ = 0;

    pixels_.resize(width * height * 3, 255); // Initialize with white pixels
}

void Painter::setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    if (x < header_.width_ && y < header_.height_) {
        size_t index = (y * header_.width_ + x) * 3;
        pixels_[index] = b;
        pixels_[index + 1] = g;
        pixels_[index + 2] = r;
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

    void Painter::DrawLoop(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    // Рисуем петлю из точки (x, y) в ту же самую точку (x, y)
    const int radius = 8; // Радиус петли
    const int centerX = x+(radius+3);
    const int centerY = y+(radius+3);

    // Рисуем внешний круг петли
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180.0;
        int xCoord = centerX + static_cast<int>(radius * std::cos(angle));
        int yCoord = centerY + static_cast<int>(radius * std::sin(angle));
        drawCircle(xCoord, yCoord, r, g, b);
    }

    // Рисуем внутренний круг петли
    const int innerRadius = radius-1; // Радиус внутреннего круга петли
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180.0;
        int xCoord = centerX + static_cast<int>(innerRadius * std::cos(angle));
        int yCoord = centerY + static_cast<int>(innerRadius * std::sin(angle));
        drawCircle(xCoord, yCoord, 255, 255, 255);
    }
}


void Painter::drawLine(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2,
                       std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    int dx = std::abs(static_cast<int>(x2) - static_cast<int>(x1));
    int dy = -std::abs(static_cast<int>(y2) - static_cast<int>(y1));
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;

   if ( x1==x2 && y1==y2)
       {DrawLoop(x1,y1,0, 255,0);}//рисуем петлю радиусом 8 если соединяемые точки совпадают


    while (true) {
        setPixel(x1, y1, r, g, b);
        if (x1 == x2 && y1 == y2) {break;}
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

    file.write(reinterpret_cast<char*>(&header_), sizeof(BMPHeader));
    file.write(reinterpret_cast<char*>(pixels_.data()), pixels_.size());

    file.close();
}

void Painter::drawDigit(const std::vector<std::vector<int>>& mask, std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    
    // Лямбда-выражение для поворота массива на 180 градусов
    auto rotateArray180Degrees = [](std::vector<std::vector<int>>& arr) {
        int rows = arr.size();
        int cols = arr[0].size();
        for (int i = 0; i < rows / 2; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::swap(arr[i][j], arr[rows - 1 - i][cols - 1 - j]);
            }
        }
    };

    // Отражаем маску по горизонтали
    std::vector<std::vector<int>> maskCopy = mask;
    rotateArray180Degrees(maskCopy);

    // Лямбда-выражение для разворачивания порядка элементов в каждой строке массива // y axis
    auto reverseRows = [](std::vector<int>& row) {
        std::reverse(row.begin(), row.end());
    };

    for (auto& row : maskCopy) {
        reverseRows(row);
    }
    
    // Применяем маску к изображению, начиная с позиции (x, y)
    for (size_t i = 0; i < maskCopy.size(); ++i) {
        for (size_t j = 0; j < maskCopy[i].size(); ++j) {
            if (maskCopy[i][j] == 1) {
                // Проверяем, не выходим ли за границы изображения
                if (x + j < header_.width_ && y + i < header_.height_) {
                    // Устанавливаем пиксель с цветом (r, g, b)
                    setPixel(x + j, y + i, r, g, b);
                }
            }
        }
    }
}
