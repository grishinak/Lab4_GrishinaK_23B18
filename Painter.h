#ifndef PAINTER_H
#define PAINTER_H

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

#pragma pack(push, 1)
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
#pragma pack(pop)

class Painter {
private:
    BMPHeader header;
    std::vector<std::uint8_t> pixels;

public:
    Painter(std::uint32_t width, std::uint32_t height);
    void setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void drawCircle(int x, int y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void drawLine(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2,
                       std::uint8_t r, std::uint8_t g, std::uint8_t b);
    void save(const std::string& filename);

    void drawDigit(const std::vector<std::vector<int>>& mask, std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b); 
    void DrawLoop(std::uint32_t x, std::uint32_t y, std::uint8_t r, std::uint8_t g, std::uint8_t b);
};

#endif // PAINTER_H