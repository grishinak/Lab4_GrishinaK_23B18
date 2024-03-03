#include "functions.h"

void drawVertices(Graph& graph, Painter& painter,std::uint8_t r, std::uint8_t g, std::uint8_t b){
for (int i = 0; i < graph.getV(); ++i) {
    Point point = graph.getPosition(i);
    painter.drawCircle(point.x, point.y, r, g, b);
    }
}

void drawEdges(Graph& graph, Painter& painter, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (const auto& edge : graph.edges_) {
        Point p1 = graph.getPosition(edge.first);
        Point p2 = graph.getPosition(edge.second);
        painter.drawLine(p1.x, p1.y, p2.x, p2.y, r, g, b);
    }
}

void drawVertexNumbers(Painter& painter,  Graph& graph,  std::vector<std::vector<std::vector<int>>>& masks,
std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    // Проходим по каждой вершине графа
    for (int i = 0; i < graph.getV(); ++i) { 
        Point point = graph.getPosition(i); // Получаем позицию вершины
        
        // Рассматриваем различные случаи для отображения номера вершины
        if (i < 10) {
            painter.drawDigit(masks[i % 10], point.x - 5, point.y - 17, r, g, b);
        } else if (i < 100) {
            int units = i % 10;
            int tens = i / 10;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, r, g, b);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, r, g, b);
        } else if (i < 1000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = i / 100;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, r, g, b);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, r, g, b);
            painter.drawDigit(masks[hundreds % 10], point.x - 25, point.y - 17, r, g, b);
        } else if (i < 10000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = (i / 100) % 10;
            int thousands = i / 1000;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, r, g, b);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, r, g, b);
            painter.drawDigit(masks[hundreds % 10], point.x - 25, point.y - 17, r, g, b);
            painter.drawDigit(masks[thousands % 10], point.x - 35, point.y - 17, r, g, b);
        }
    }
}