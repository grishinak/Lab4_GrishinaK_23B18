#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "graph.h"
#include "painter.h"

void DrawVertices(Graph& _graph, Painter& _painter,std::uint8_t _r, std::uint8_t _g, std::uint8_t _b);

void DrawEdges(Graph& _graph, Painter& _painter, std::uint8_t _r, std::uint8_t _g, std::uint8_t _b);

void DrawVertexNumbers(Painter& _painter,  Graph& _graph,  std::vector<std::vector<std::vector<int>>>& _masks,
    std::uint8_t _r, std::uint8_t _g, std::uint8_t _b);

#endif //FUNCTIONS_H