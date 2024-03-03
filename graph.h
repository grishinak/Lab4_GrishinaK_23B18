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
    
    double Distance(const Point& p1, const Point& p2);
    void ApplyForce(Point& p1, Point& p2);
    void RepelNodes();
    void AdjustSpringForces();

public:
    std::vector<std::pair<int, int>> edges_;
    const int kspring_ = 1; // Spring constant
    Graph(int V);
    void AddEdge(int u, int v);
  //  void addSingleEdge(const std::pair<int, int>& edge);
    void AddEdges( std::vector<std::pair<int, int>>& edges_);
    void Planarize();
    void PrintPositions();
    int GetV();
    Point GetPosition(int index);
};

#endif // GRAPH_H
