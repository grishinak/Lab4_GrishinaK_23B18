#ifndef PAINTER_H
#define PAINTER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

struct BMPHeader {
    std::uint16_t type_;
    std::uint32_t size_;
    std::uint16_t reserved1_;
    std::uint16_t reserved2_;
    std::uint32_t offset_;
    std::uint32_t header_size_;
    std::uint32_t width_;
    std::uint32_t height_;
    std::uint16_t planes_;
    std::uint16_t bit_count_;
    std::uint32_t compression_;
    std::uint32_t image_size_;
    std::uint32_t x_pixels_per_meter_;
    std::uint32_t y_pixels_per_meter_;
    std::uint32_t colors_used_;
    std::uint32_t colors_important_;
};


class Painter {
private:
    BMPHeader header_;
    std::vector<std::uint8_t> pixels_;

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