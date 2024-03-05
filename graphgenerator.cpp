#include <iostream>
#include <vector>
#include <set>
#include <random>

// Функция для генерации графа с заданным количеством вершин и ребер
void GenerateGraph(int _V, int _E) {
    // Проверяем, возможно ли создать граф с заданным количеством вершин и ребер
    if (_E > _V * (_V - 1) / 2) {
        std::cout << "Невозможно создать граф с заданным количеством вершин и ребер" << std::endl;
        return;
    }

    // Выводим количество вершин и ребер в графе
    std::cout << _V << " " << _E << std::endl;

    // Создаем множество для хранения ребер
    std::set<std::pair<int, int>> edges;
    
    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _V - 1); // Равномерное распределение для выбора вершин

    // Генерируем ребра графа
    while (edges.size() < _E) {
        int u = dis(gen); // Случайная вершина u
        int v = dis(gen); // Случайная вершина v
    }

    // Выводим сгенерированные ребра
    for (auto& edge : edges) {
        std::cout << edge.first << " " << edge.second << std::endl;
    }
}

// Точка входа в программу
int main() {
    int V = 1002; // Количество вершин
    int E = 1002; // Количество ребер

    // Генерируем граф с заданным количеством вершин и ребер
    GenerateGraph(V, E);
    return 0;
}
