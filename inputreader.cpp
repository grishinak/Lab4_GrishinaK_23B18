#include "inputreader.h"

InputReader::InputReader() {
    std::ifstream inputFile("input.txt");  // открытие файла с исходными данными
    if (inputFile.is_open()) //если файл открыт-сохраняем данные 
    {
        inputFile >> V_ >> E_; // данные первой строки 
        for (int i = 0; i < E_; ++i) {
            int u, v;
            inputFile >> u >> v;  //пары связанных вершин ребром
            edges_.push_back(std::make_pair(u, v));//сохранение пары
        }
        inputFile.close();  // закрытие файла
    } 
    else {
        std::cerr << "Error opening input file." << std::endl;
    }//ошибка открытия файла 
}

int InputReader::getV() {
    return V_;
} //получить количество вершин

int InputReader::getE() {
    return E_; //получить количество ребер
}

std::vector<std::pair<int, int>> InputReader::getEdges() {
    return edges_;
} //получить пары связанных вершин 
