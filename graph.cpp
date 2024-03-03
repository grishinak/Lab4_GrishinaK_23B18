#include "graph.h"

#include <iostream>
#include <cmath>

double Graph::distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Graph::applyForce(Point& p1, Point& p2) {
    double dist = distance(p1, p2);
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    
    p1.x += static_cast<int>((dx / dist) * k);
    p1.y += static_cast<int>((dy / dist) * k);
}

void Graph::repelNodes() {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                applyForce(positions[i], positions[j]);
            }
        }
    }
}

void Graph::adjustSpringForces() {
    for (auto edge : edges) {
        Point& p1 = positions[edge.first];
        Point& p2 = positions[edge.second];
        
        applyForce(p1, p2);
    }
}

Graph::Graph(int V) : V(V) {
    adj.resize(V);
    positions.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.push_back({u, v});
}

//void Graph::addSingleEdge(const std::pair<int, int>& edge) {
//    addEdge(edge.first, edge.second);
//}

void Graph::addEdges( std::vector<std::pair<int, int>>& edges) {
    for (const auto& edge : edges) {
        addEdge(edge.first, edge.second);
    }
}

void Graph::planarize() {
    // Инициализируем позиции случайным образом, но с учетом ограничения на минимальное расстояние
    for (int i = 0; i < V; ++i) {
        bool validPosition = false;
        while (!validPosition) {
            // Генерируем случайные координаты
            positions[i].x = rand() % 2000;
            positions[i].y = rand() % 2000;
            
            // Проверяем расстояние между текущей вершиной и предыдущими вершинами
            validPosition = true;
            for (int j = 0; j < i; ++j) {
                if (distance(positions[i], positions[j]) < 30+5+5) // 30 по условию между вершинами и 5 радиус вершин
                {
                    validPosition = false;
                    break;
                }
            }
        }
    }
    
    // Выполняем итерации
    for (int iter = 0; iter < 100; ++iter) {
        repelNodes();
        adjustSpringForces();
    }
}
    


void Graph::printPositions() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Node " << i << ": (" << positions[i].x << ", " << positions[i].y << ")" << std::endl;
    }
}

int Graph::getV(){
    return V;
}

Point Graph::getPosition(int index) {
    if (index >=0 && index<=V) {
        return positions[index];
    } else {
        return {0,0};
    }
}