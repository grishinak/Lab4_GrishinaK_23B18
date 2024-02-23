#include "InputReader.hpp"

InputReader::InputReader() {
    std::ifstream inputFile("input.txt");  // открытие файла с исходными данными
    if (inputFile.is_open()) //если файл открыт-сохраняем данные 
    {
        inputFile >> V >> E; // данные первой строки 
        for (int i = 0; i < E; ++i) {
            int u, v;
            inputFile >> u >> v;  //пары связанных вершин ребром
            edges.push_back(std::make_pair(u, v));//сохранение пары
        }
        inputFile.close();  // закрытие файла
    } 
    else {
        std::cerr << "Error opening input file." << std::endl;
    }//ошибка открытия файла 
}

int InputReader::getV() {
    return V;
} //получить количество вершин

int InputReader::getE() {
    return E; //получить количество ребер
}

std::vector<std::pair<int, int>> InputReader::getEdges() {
    return edges;
} //получить пары связанных вершин 
