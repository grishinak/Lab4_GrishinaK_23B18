#include "painter.h"

#include <cmath>
#include <vector>
#include <algorithm>

Painter::Painter(std::uint32_t _width, std::uint32_t _height) {
    header_.type = 0x4D42; // "BM"
    header_.size = sizeof(BMPHeader) + _width * _height * 3;
    header_.reserved1 = 0;
    header_.reserved2 = 0;
    header_.offset = sizeof(BMPHeader);
    header_.header_size = 40;
    header_.width = _width;
    header_.height = _height;
    header_.planes = 1;
    header_.bit_count = 24; // 24 bits per pixel
    header_.compression = 0;
    header_.image_size = 0;
    header_.x_pixels_per_meter = 0;
    header_.y_pixels_per_meter = 0;
    header_.colors_used = 0;
    header_.colors_important = 0;

    pixels_.resize(_width * _height * 3, 255); // Initialize with white pixels
}

void Painter::SetPixel(std::uint32_t _x, std::uint32_t _y, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b) {
    if (_x < header_.width && _y < header_.height) {
        size_t index = (_y * header_.width + _x) * 3;
        pixels_[index] = _b;
        pixels_[index + 1] = _g;
        pixels_[index + 2] = _r;
    }
}

void Painter::DrawCircle(int _x, int _y, uint8_t _r, uint8_t _g, uint8_t _b) {
        const int kRadius = 5; // половина диаметра
        for (int i = _x - kRadius; i <= _x + kRadius; ++i) {
            for (int j = _y - kRadius; j <= _y + kRadius; ++j) {
                if (std::sqrt((i - _x) * (i - _x) + (j - _y) * (j - _y)) <= kRadius) {
                    SetPixel(i, j, _r, _g, _b);
                }
            }
        }
    }

    void Painter::DrawLoop(std::uint32_t _x, std::uint32_t _y, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b) {
    // Рисуем петлю из точки (x, y) в ту же самую точку (x, y)
    const int kRadius = 8; // Радиус петли
    const int kCenterX = _x+(kRadius+3);
    const int kCenterY = _y+(kRadius+3);

    // Рисуем внешний круг петли
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180.0;
        int xCoord = kCenterX + static_cast<int>(kRadius * std::cos(angle));
        int yCoord = kCenterY + static_cast<int>(kRadius * std::sin(angle));
        DrawCircle(xCoord, yCoord, _r, _g, _b);
    }

    // Рисуем внутренний круг петли
    const int kInnerRadius = kRadius - 1; // Радиус внутреннего круга петли
    for (int i = 0; i < 360; ++i) {
        double angle = i * M_PI / 180.0;
        int xCoord = kCenterX + static_cast<int>(kInnerRadius * std::cos(angle));
        int yCoord = kCenterY + static_cast<int>(kInnerRadius * std::sin(angle));
        DrawCircle(xCoord, yCoord, 255, 255, 255);
    }
}


void Painter::DrawLine(std::uint32_t _x1, std::uint32_t _y1, std::uint32_t _x2, std::uint32_t _y2, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b) {
    int dx = std::abs(static_cast<int>(_x2) - static_cast<int>(_x1));
    int dy = -std::abs(static_cast<int>(_y2) - static_cast<int>(_y1));
    int sx = _x1 < _x2 ? 1 : -1;
    int sy = _y1 < _y2 ? 1 : -1;
    int err = dx + dy;

   if ( _x1==_x2 && _y1==_y2)
       {DrawLoop(_x1,_y1,0, 255,0);}//рисуем петлю радиусом 8 если соединяемые точки совпадают


    while (true) {
        SetPixel(_x1, _y1, _r, _g, _b);
        if (_x1 == _x2 && _y1 == _y2) {break;}
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; _x1 += sx; }
        if (e2 <= dx) { err += dx; _y1 += sy; }
    }
}

void Painter::Save(const std::string& _filename) {
    std::ofstream file(_filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Couldn't open file " << _filename << " for writing\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&header_), sizeof(BMPHeader));
    file.write(reinterpret_cast<char*>(pixels_.data()), pixels_.size());

    file.close();
}

void Painter::DrawDigit(const std::vector<std::vector<int>>& mask, std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    
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
                if (x + j < header_.width && y + i < header_.height) {
                    // Устанавливаем пиксель с цветом (r, g, b)
                    SetPixel(x + j, y + i, r, g, b);
                }
            }
        }
    }
}
