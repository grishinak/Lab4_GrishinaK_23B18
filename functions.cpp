#include "functions.h"

void DrawVertices(Graph& _graph, Painter& _painter,std::uint8_t _r, std::uint8_t _g, std::uint8_t _b){
for (int i = 0; i < _graph.GetV(); ++i) {
    Point point = _graph.GetPosition(i);
    _painter.DrawCircle(point.x, point.y, _r, _g, _b);
    }
}

void DrawEdges(Graph& _graph, Painter& _painter, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b) {
    for (const auto& edge : _graph.edges_) {
        Point p1 = _graph.GetPosition(edge.first);
        Point p2 = _graph.GetPosition(edge.second);
        _painter.DrawLine(p1.x, p1.y, p2.x, p2.y, _r, _g, _b);
    }
}

void DrawVertexNumbers(Painter& _painter,  Graph& _graph,  std::vector<std::vector<std::vector<int>>>& _masks,
    std::uint8_t _r, std::uint8_t _g, std::uint8_t _b) {
    // Проходим по каждой вершине графа
    for (int i = 0; i < _graph.GetV(); ++i) { 
        Point point = _graph.GetPosition(i); // Получаем позицию вершины
        
        // Рассматриваем различные случаи для отображения номера вершины
        if (i < 10) {
            _painter.DrawDigit(_masks[i % 10], point.x - 5, point.y - 17, _r, _g, _b);
        } else if (i < 100) {
            int units = i % 10;
            int tens = i / 10;
            _painter.DrawDigit(_masks[units % 10], point.x - 5, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[tens % 10], point.x - 15, point.y - 17, _r, _g, _b);
        } else if (i < 1000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = i / 100;
            _painter.DrawDigit(_masks[units % 10], point.x - 5, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[tens % 10], point.x - 15, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[hundreds % 10], point.x - 25, point.y - 17, _r, _g, _b);
        } else if (i < 10000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = (i / 100) % 10;
            int thousands = i / 1000;
            _painter.DrawDigit(_masks[units % 10], point.x - 5, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[tens % 10], point.x - 15, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[hundreds % 10], point.x - 25, point.y - 17, _r, _g, _b);
            _painter.DrawDigit(_masks[thousands % 10], point.x - 35, point.y - 17, _r, _g, _b);
        }
    }
}

void PrintEdges(std::vector<std::pair<int, int>> _edges) {
     for (const auto& edge : _edges) {
        std::cout << edge.first << " " << edge.second << std::endl;
    }
}