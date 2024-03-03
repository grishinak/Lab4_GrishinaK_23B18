#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Point {
    int x, y;
};

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<Point> positions;
    const int k = 1; // Spring constant
    
    double distance(const Point& p1, const Point& p2);
    void applyForce(Point& p1, Point& p2);
    void repelNodes();
    void adjustSpringForces();

public:
    std::vector<std::pair<int, int>> edges;
    
    Graph(int V);
    void addEdge(int u, int v);
  //  void addSingleEdge(const std::pair<int, int>& edge);
    void addEdges( std::vector<std::pair<int, int>>& edges);
    void planarize();
    void printPositions();
    int getV();
    Point getPosition(int index);
};

#endif // GRAPH_H
