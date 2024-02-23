#include <iostream>

#include "InputReader.hpp"

int main() {
    InputReader reader;//создание обьекта класса 
    int V = reader.getV();//сохранение числа вершин
    int E = reader.getE();//сохранение числа ребер
    std::vector<std::pair<int, int>> edges = reader.getEdges();//сохранение пар вершин, связанных ребром

    std::cout << "Number of vertices11 вершин: " << V << std::endl;//вывод числа вершин
    std::cout << "Number of edges: " << E << std::endl;//вывод числа ребер

    for (const auto& edge : edges) {
        std::cout << edge.first << " " << edge.second << std::endl;
    }//вывод пар вершин, связанных ребром

    return 0;
}
