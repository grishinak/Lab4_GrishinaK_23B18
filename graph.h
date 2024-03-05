#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Point {
    int x, y;
};

class Graph {
private:
    int V_;
    std::vector<std::vector<int>> adj_;
    std::vector<Point> positions_;
    
    double Distance(const Point& _p1, const Point& _p2);
    void ApplyForce(Point& _p1, Point& _p2);
    void RepelNodes();
    void AdjustSpringForces();

public:
    std::vector<std::pair<int, int>> edges_;
    const int kSpring_ = 1; // Spring constant

    Graph(int _V);
    void AddEdge(int _u, int _v);
    void AddEdges( std::vector<std::pair<int, int>>& _edges_);
    void Planarize();
    void PrintPositions();
    int GetV();
    Point GetPosition(int _index);
};

#endif // GRAPH_H
