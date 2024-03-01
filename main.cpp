#include <iostream>

#include "InputReader.h"
#include "Painter.h"
#include "masks.h"
#include "Graph.h"


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

    Painter painter(2000, 2000);
 
        //draw vertices
    for (int i = 0; i < graph.getV(); ++i) {
        Point point = graph.getPosition(i);
        painter.drawCircle(point.x, point.y, 255, 0, 0);
    }



    //draw numbers of vertices
    for (int i=0; i < graph.getV();++i){ 
    Point point = graph.getPosition(i);
        if (i<10) {
            painter.drawDigit(masks[i%10] ,point.x-5, point.y-17, 255, 0, 0);
        } else if (i<100){
            int units =i%10;
            int tens=i/10;
            painter.drawDigit(masks[units%10] ,point.x-5, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[tens%10] ,point.x-15, point.y-17, 255, 0, 0);
        } else if (i<1000) {
            int units =i%10;
            int tens=(i/10)%10;
            int hundreds=((i/10)/10)%10;
            painter.drawDigit(masks[units%10] ,point.x-5, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[tens%10] ,point.x-15, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[hundreds%10] ,point.x-25, point.y-17, 255, 0, 0);
        }else if (i<1000) {
            int units =i%10;
            int tens=(i/10)%10;
            int hundreds=((i/10)/10)%10;
            int thousands=(((i/10)/10)/10)%10;
            painter.drawDigit(masks[units%10] ,point.x-5, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[tens%10] ,point.x-15, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[hundreds%10] ,point.x-25, point.y-17, 255, 0, 0);
            painter.drawDigit(masks[thousands%10] ,point.x-35, point.y-17, 255, 0, 0);
        }

    }
        
   

    painter.save("output.bmp");
    std::cout << "Image saved successfully!\n";

    /* //Painter test */

 /*  Painter painter(800, 600);

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

    std::cout << "Image saved successfully!\n";*/  

    return 0;
}
