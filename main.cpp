#include <iostream>

#include "InputReader.h"
#include "Painter.h"
#include "masks.h"
#include "Graph.h"


void drawEdges(Graph& graph, Painter& painter, std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (const auto& edge : graph.edges) {
        Point p1 = graph.getPosition(edge.first);
        Point p2 = graph.getPosition(edge.second);
        painter.drawLine(p1.x, p1.y, p2.x, p2.y, r, g, b);
    }
}

void drawVertexNumbers(Painter& painter,  Graph& graph,  std::vector<std::vector<std::vector<int>>>& masks) {
    // Проходим по каждой вершине графа
    for (int i = 0; i < graph.getV(); ++i) { 
        Point point = graph.getPosition(i); // Получаем позицию вершины
        
        // Рассматриваем различные случаи для отображения номера вершины
        if (i < 10) {
            painter.drawDigit(masks[i % 10], point.x - 5, point.y - 17, 0, 0, 0);
        } else if (i < 100) {
            int units = i % 10;
            int tens = i / 10;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, 0, 0, 0);
        } else if (i < 1000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = i / 100;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[hundreds % 10], point.x - 25, point.y - 17, 0, 0, 0);
        } else if (i < 10000) {
            int units = i % 10;
            int tens = (i / 10) % 10;
            int hundreds = (i / 100) % 10;
            int thousands = i / 1000;
            painter.drawDigit(masks[units % 10], point.x - 5, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[tens % 10], point.x - 15, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[hundreds % 10], point.x - 25, point.y - 17, 0, 0, 0);
            painter.drawDigit(masks[thousands % 10], point.x - 35, point.y - 17, 0, 0, 0);
        }
    }
}

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
    for (int i = 0; i < graph.getV(); ++i) {
        Point point = graph.getPosition(i);
        painter.drawCircle(point.x, point.y, 255, 0, 0);
    }

    //draw vertex numbers
    drawVertexNumbers(painter, graph, masks);


        //saving output file     
    painter.save("output.bmp");
    std::cout << "Image saved successfully!\n";

    return 0;
}
