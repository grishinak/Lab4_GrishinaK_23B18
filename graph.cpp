#include "graph.h"

#include <iostream>
#include <cmath>

double Graph::Distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Graph::ApplyForce(Point& p1, Point& p2) {
    double dist = Distance(p1, p2);
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    
    p1.x += static_cast<int>((dx / dist) * kspring_);
    p1.y += static_cast<int>((dy / dist) * kspring_);
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

Graph::Graph(int V) : V_(V) {
    adj_.resize(V);
    positions_.resize(V);
}

void Graph::AddEdge(int u, int v) {
    adj_[u].push_back(v);
    adj_[v].push_back(u);
    edges_.push_back({u, v});
}

//void Graph::addSingleEdge(const std::pair<int, int>& edge) {
//    addEdge(edge.first, edge.second);
//}

void Graph::AddEdges( std::vector<std::pair<int, int>>& edges) {
    for (const auto& edge : edges) {
        AddEdge(edge.first, edge.second);
    }
}

void Graph::Planarize() {
    // Инициализируем позиции случайным образом, но с учетом ограничения на минимальное расстояние
    for (int i = 0; i < V_; ++i) {
        bool validPosition = false;
        while (!validPosition) {
            // Генерируем случайные координаты
            positions_[i].x = rand() % 2000;
            positions_[i].y = rand() % 2000;
            
            // Проверяем расстояние между текущей вершиной и предыдущими вершинами
            validPosition = true;
            for (int j = 0; j < i; ++j) {
                if (Distance(positions_[i], positions_[j]) < 30+5+5) // 30 по условию между вершинами и 5 радиус вершин
                {
                    validPosition = false;
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

Point Graph::GetPosition(int index) {
    if (index >=0 && index<=V_) {
        return positions_[index];
    } else {
        return {0,0};
    }
}