#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>

class InputReader {
private: //поля класса 
    int V, E;
    std::vector<std::pair<int, int>> edges;

public: //методы класса
    InputReader();
    int getV();  //вернуть количество вершин
    int getE();  //вернуть количество ребер
    std::vector<std::pair<int, int>> getEdges();  //вернуть пары связанных вершин
};

#endif // INPUTREADER_HPP