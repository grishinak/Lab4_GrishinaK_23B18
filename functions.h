#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "graph.h"
#include "painter.h"

void DrawVertices(Graph& graph, Painter& painter,std::uint8_t r, std::uint8_t g, std::uint8_t b);

void DrawEdges(Graph& graph, Painter& painter, std::uint8_t r, std::uint8_t g, std::uint8_t b);

void DrawVertexNumbers(Painter& painter,  Graph& graph,  std::vector<std::vector<std::vector<int>>>& masks,
std::uint8_t r, std::uint8_t g, std::uint8_t b);

#endif //FUNCTIONS_H