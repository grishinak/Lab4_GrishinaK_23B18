#include "graph.h"

#include <iostream>
#include <cmath>
#include <algorithm>

double Graph::Distance(const Point& _p1, const Point& _p2) {
    return sqrt(pow(_p1.x - _p2.x, 2) + pow(_p1.y - _p2.y, 2));
}

void Graph::ApplyForce(Point& _p1, Point& _p2) {
    double dist = Distance(_p1, _p2);
    double dx = _p2.x - _p1.x;
    double dy = _p2.y - _p1.y;
    
    _p1.x += static_cast<int>((dx / dist) * kSpring_);
    _p1.y += static_cast<int>((dy / dist) * kSpring_);
}

void Graph::RepelNodes() {
    for (int i = 0; i < V_; ++i) {
        for (int j = 0; j < V_; ++j) {
            if (i != j) {
                ApplyForce(positions_[i], positions_[j]);
            }
        }
    }
}

void Graph::AdjustSpringForces() {
    for (auto edge : edges_) {
        Point& p1 = positions_[edge.first];
        Point& p2 = positions_[edge.second];
        
        ApplyForce(p1, p2);
    }
}


Graph::Graph(int _V) : V_(_V) {
    adj_.resize(_V);
    positions_.resize(_V);
}

void Graph::AddEdge(int _u, int _v) {
    adj_[_u].push_back(_v);
    adj_[_v].push_back(_u);
    edges_.push_back({_u, _v});
}


void Graph::AddEdges( std::vector<std::pair<int, int>>& _edges_) {
    for (const auto& edge : _edges_) {
        AddEdge(edge.first, edge.second);
    }
}

void Graph::Planarize() {
    // Инициализируем позиции случайным образом, но с учетом ограничения на минимальное расстояние
    for (int i = 0; i < V_; ++i) {
        bool valid_position = false;
        while (!valid_position) {
            // Генерируем случайные координаты
            positions_[i].x = rand() % 2000;
            positions_[i].y = rand() % 2000;
            
            // Проверяем расстояние между текущей вершиной и предыдущими вершинами
            valid_position = true;
            for (int j = 0; j < i; ++j) {
                if (Distance(positions_[i], positions_[j]) < 30+5+5) // 30 по условию между вершинами и 5 радиус вершин
                {
                    valid_position = false;
                    break;
                }
            }
        }
    }
    
    // Выполняем итерации
    for (int iter = 0; iter < 100; ++iter) {
        RepelNodes();
        AdjustSpringForces();
    }
}



void Graph::PrintPositions() {
    for (int i = 0; i < V_; ++i) {
        std::cout << "Node " << i << ": (" << positions_[i].x << ", " << positions_[i].y << ")" << std::endl;
    }
}

int Graph::GetV(){
    return V_;
}

Point Graph::GetPosition(int _index) {
    if (_index >=0 && _index<=V_) {
        return positions_[_index];
    } else {
        return {0,0};
    }
}


void Graph::FRPlanarize() {

    // Инициализация случайных позиций вершин
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = rand() % 2000; // Примерный размер поля для случайной инициализации //2000 - painter parameters by constructor
        positions_[i].y = rand() % 2000; // Примерный размер поля для случайной инициализации //2000 - painter parameters by constructor
    }

    // Итеративный процесс для планаризации графа
    for (int iter = 0; iter < kIterations; ++iter) {
        std::vector<Point> forces(V_, {0, 0});

        // Расчет отталкивающих сил между вершинами
        for (int i = 0; i < V_; ++i) {
            for (int j = 0; j < V_; ++j) {
                if (i != j) {
                    double dx = positions_[j].x - positions_[i].x;
                    double dy = positions_[j].y - positions_[i].y;
                    double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001); // Избегаем деления на ноль
                    double force = repulsiveForceFactor_ / distance;
                    forces[i].x -= force * dx / distance;
                    forces[i].y -= force * dy / distance;
                }
            }
        }

        // Расчет притягивающих сил для ребер
        for (const auto& edge : edges_) {
            int u = edge.first;
            int v = edge.second;
            double dx = positions_[v].x - positions_[u].x;
            double dy = positions_[v].y - positions_[u].y;
            double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001); // Избегаем деления на ноль
            double force = springForceFactor_ * (distance - kIdealEdgeLength);
            forces[u].x += force * dx / distance;
            forces[u].y += force * dy / distance;
            forces[v].x -= force * dx / distance;
            forces[v].y -= force * dy / distance;
        }

        // Обновление позиций вершин с учетом сил
        for (int i = 0; i < V_; ++i) {
            positions_[i].x += forces[i].x;
            positions_[i].y += forces[i].y;
        }

        // Охлаждение системы
        repulsiveForceFactor_ *= kCoolingFactor;
        springForceFactor_ *= kCoolingFactor;
    }

    // Приведение позиций к типу int
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = static_cast<int>(positions_[i].x);
        positions_[i].y = static_cast<int>(positions_[i].y);
    }
}
