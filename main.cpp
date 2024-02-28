#include <iostream>

#include "InputReader.h"
#include "Painter.h"
#include "masks.h"



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

    /* //Painter test */

    Painter painter(800, 600);

    // Draw something (e.g., a red rectangle)
    for (int x = 100; x < 300; ++x) {
        for (int y = 100; y < 300; ++y) {
            painter.setPixel(x, y, 255, 0, 0); // Red
        }
    }

painter.drawCircle(50,50,0,0,255);
painter.drawLine(50,50,100,100,0,0,0);


    painter.drawDigit(mask5,150,150,0,144,144);

    painter.save("output.bmp");

    std::cout << "Image saved successfully!\n";

    return 0;
}
