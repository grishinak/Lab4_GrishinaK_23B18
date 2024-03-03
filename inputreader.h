#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <iostream>
#include <fstream>
#include <vector>

class InputReader {
private: //поля класса 
    int V_, E_;
    std::vector<std::pair<int, int>> edges_;

public: //методы класса
    InputReader();
    int GetV();  //вернуть количество вершин
    int GetE();  //вернуть количество ребер
    std::vector<std::pair<int, int>> GetEdges();  //вернуть пары связанных вершин
};

#endif // INPUTREADER_H