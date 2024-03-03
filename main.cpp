#include <iostream>

#include "inputreader.h"
#include "painter.h"
#include "masks.h"
#include "graph.h"

#include "functions.h"

int main() {

    /* //inputreader test */
    InputReader reader;//создание обьекта класса 
    int V = reader.getV();//сохранение числа вершин
    int E = reader.getE();//сохранение числа ребер
    std::vector<std::pair<int, int>> edges = reader.getEdges();//сохранение пар вершин, связанных ребром

    std::cout << "Number of vertices: " << V << std::endl;//вывод числа вершин
    std::cout << "Number of edges: " << E << std::endl;//вывод числа ребер

    for (const auto& edge : edges) {
        std::cout << edge.first << " " << edge.second << std::endl;
    }//вывод пар вершин, связанных ребром
// all printed out from inputreader

    /*graph test*/
    Graph graph(V);
    graph.addEdges(edges);//добавили считанные ребра из ввода
    graph.planarize();//планаризовали по силам
    graph.printPositions();// вывели координаты вершин 
//all printed out from graph

    /* painter test*/
    Painter painter(2000, 2000);
 
        //draw edges
    drawEdges(graph, painter, 0, 0, 255);

    //draw vertices
    drawVertices(graph, painter, 255,0,0);

    //draw vertex numbers
    drawVertexNumbers(painter, graph, masks, 0, 0, 0);


        //saving output file     
    painter.save("output.bmp");
    std::cout << "Image saved successfully!\n";

    return 0;
}

