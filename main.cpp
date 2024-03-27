#include <iostream>

#include "inputreader.h"
#include "painter.h"
#include "graph.h"
#include "masks.h"
#include "functions.h"


int main() {

    InputReader reader;
    int V = reader.GetV();//сохранение числа вершин
    int E = reader.GetE();//сохранение числа ребер

    std::vector<std::pair<int, int>> edges = reader.GetEdges();//сохранение пар вершин, связанных ребром

    std::cout << "Number of vertices: " << V << std::endl;//вывод числа вершин
    std::cout << "Number of edges: " << E << std::endl;//вывод числа ребер
    PrintEdges(edges);//вывод пар вершин, связанных ребром

    int height = 1000;
    int weight = 1000;

    Graph graph(V);

    graph.AddEdges(edges);//добавили считанные ребра из ввода

    graph.FRPlanarize(height, weight);//планаризовали по силам с помощью алгоритма (1) FRPlanarise() или (2)Planarize() 
    graph.PrintPositions();// вывели координаты вершин 

    Painter painter(height, weight);
    DrawEdges(graph, painter, 0, 0, 255);
    DrawVertices(graph, painter, 255,0,0);
    DrawVertexNumbers(painter, graph, masks, 0, 0, 0);

    painter.Save("output.bmp");
    std::cout << "Image saved successfully!\n";

    return 0;

}