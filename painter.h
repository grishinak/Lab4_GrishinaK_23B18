#ifndef PAINTER_H
#define PAINTER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

struct BMPHeader {
    std::uint16_t type;
    std::uint32_t size;
    std::uint16_t reserved1;
    std::uint16_t reserved2;
    std::uint32_t offset;
    std::uint32_t header_size;
    std::uint32_t width;
    std::uint32_t height;
    std::uint16_t planes;
    std::uint16_t bit_count;
    std::uint32_t compression;
    std::uint32_t image_size;
    std::uint32_t x_pixels_per_meter;
    std::uint32_t y_pixels_per_meter;
    std::uint32_t colors_used;
    std::uint32_t colors_important;
};


class Painter {
private:
    BMPHeader header_;
    std::vector<std::uint8_t> pixels_;

public:
    Painter(std::uint32_t width, std::uint32_t height);
    void SetPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void DrawCircle(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void DrawLine(std::uint32_t _x1, std::uint32_t _y1, std::uint32_t _x2, std::uint32_t _y2, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b);
    void Save(const std::string& _filename);
    void DrawDigit(const std::vector<std::vector<int>>& mask, std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b); 
    void DrawLoop(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
};

#endif // PAINTER_H