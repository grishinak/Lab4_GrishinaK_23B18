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

void Graph::Planarize(int _height, int _weight) {
        srand(time(NULL));
    // Инициализируем позиции случайным образом, но с учетом ограничения на минимальное расстояние
    for (int i = 0; i < V_; ++i) {
        bool valid_position = false;
        while (!valid_position) {
            // Генерируем случайные координаты
            positions_[i].x = rand() % _height;
            positions_[i].y = rand() % _weight;
            
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

bool linesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
        double x_intersect = x1 + ua * (x2 - x1);
        double y_intersect = y1 + ua * (y2 - y1);
        double dx = x2 - x1;
        double dy = y2 - y1;
        double length = sqrt(dx * dx + dy * dy);
        return length >= 100.0; // Check if length is at least 30 pixels
    }
    return false;
}

void Graph::FRPlanarize(int _height,int _weight) {
    srand(time(NULL));

    // Initialize random vertex positions
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = rand() % _height;
        positions_[i].y = rand() % _weight;
    }

    // Iterative process for graph planarization
    for (int iter = 0; iter < kIterations; ++iter) {
        std::vector<Point> forces(V_, {0, 0});

        // Calculate repulsive forces between vertices
        for (int i = 0; i < V_; ++i) {
            for (int j = 0; j < V_; ++j) {
                if (i != j) {
                    double dx = positions_[j].x - positions_[i].x;
                    double dy = positions_[j].y - positions_[i].y;
                    double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001);
                    double force = repulsive_force_factor_ / distance;
                    forces[i].x -= force * dx / distance;
                    forces[i].y -= force * dy / distance;
                }
            }
        }

        // Calculate attractive forces for edges
        for (const auto& edge : edges_) {
            int u = edge.first;
            int v = edge.second;
            double dx = positions_[v].x - positions_[u].x;
            double dy = positions_[v].y - positions_[u].y;
            double distance = std::max(sqrt(dx * dx + dy * dy), 0.0001);
            double force = spring_force_factor_ * (distance - kIdealEdgeLength);
            forces[u].x += force * dx / distance;
            forces[u].y += force * dy / distance;
            forces[v].x -= force * dx / distance;
            forces[v].y -= force * dy / distance;
        }

        // Update vertex positions considering forces
        for (int i = 0; i < V_; ++i) {
            positions_[i].x += forces[i].x;
            positions_[i].y += forces[i].y;
        }

        // Check for edge intersections and adjust vertex positions
        for (const auto& edge1 : edges_) {
            int u1 = edge1.first;
            int v1 = edge1.second;
            for (const auto& edge2 : edges_) {
                int u2 = edge2.first;
                int v2 = edge2.second;
                if (u1 != u2 && u1 != v2 && v1 != u2 && v1 != v2) {
                    // Check for intersection between edge1 and edge2
                    double x1 = positions_[u1].x;
                    double y1 = positions_[u1].y;
                    double x2 = positions_[v1].x;
                    double y2 = positions_[v1].y;
                    double x3 = positions_[u2].x;
                    double y3 = positions_[u2].y;
                    double x4 = positions_[v2].x;
                    double y4 = positions_[v2].y;
                    if (linesIntersect(x1, y1, x2, y2, x3, y3, x4, y4)) {
                        // If intersection found, adjust positions
                        double dx = x2 - x1;
                        double dy = y2 - y1;
                        double length = sqrt(dx * dx + dy * dy);
                        double ex = dx / length;
                        double ey = dy / length;
                        double nx = ey;
                        double ny = -ex;
                        double px = (x1 + x2) / 2;
                        double py = (y1 + y2) / 2;
                        positions_[v1].x = px + nx * kIdealEdgeLength / 2;
                        positions_[v1].y = py + ny * kIdealEdgeLength / 2;
                        positions_[u2].x = px - nx * kIdealEdgeLength / 2;
                        positions_[u2].y = py - ny * kIdealEdgeLength / 2;
                    }
                }
            }
        }

        // Cool down the system
        repulsive_force_factor_ *= kCoolingFactor;
        spring_force_factor_ *= kCoolingFactor;
    }

    // Convert positions to integer type
    for (int i = 0; i < V_; ++i) {
        positions_[i].x = static_cast<int>(positions_[i].x);
        positions_[i].y = static_cast<int>(positions_[i].y);
    }
}
