#include "inputreader.h"


InputReader::InputReader() {
//try{    
    std::ifstream input_file("input.txt");  // открытие файла с исходными данными
    if (input_file.is_open()) //если файл открыт-сохраняем данные 
    {
        input_file >> V_ >> E_; // данные первой строки 
        for (int i = 0; i < E_; ++i) {
            int u, v;
            input_file >> u >> v;  //пары связанных вершин ребром
            if ((u < 0 || u >= V_) || (v < 0 || v >= V_)) {
                throw WrongEdgeException(u);
                }else
            edges_.push_back(std::make_pair(u, v));//сохранение пары
        }
        input_file.close();  // закрытие файла
    } 
    else {
        std::cerr << "Error opening input file." << std::endl;
    }//ошибка открытия файла }

//} catch (const WrongEdgeException& ex){
//  std::cerr<<"Wrong edge exception"<<std::endl;
//}
}

int InputReader::GetV() {
    return V_;
} //получить количество вершин

int InputReader::GetE() {
    return E_; //получить количество ребер
}

std::vector<std::pair<int, int>> InputReader::GetEdges() {
    return edges_;
} //получить пары связанных вершин 
