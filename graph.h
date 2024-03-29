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

    //for Planarise()
    void ApplyForce(Point& _p1, Point& _p2);
    void RepelNodes();
    void AdjustSpringForces();

    const int kSpring_ = 1; // Spring constant for Planarise()

    // Определение констант для алгоритма FRPlanarize()
    static constexpr double kInitialRepulsiveForceFactor = 0.1;
    static constexpr double kInitialSpringForceFactor = 0.01;
    static constexpr double kCoolingFactor = 0.95;
    static constexpr double kIdealEdgeLength = 30.0;
    static constexpr int kIterations = 100;

    // Члены данных для констант алгоритма FRPlanarize()
    double repulsive_force_factor_ = kInitialRepulsiveForceFactor;
    double spring_force_factor_ = kInitialSpringForceFactor;


public:
    std::vector<std::pair<int, int>> edges_;
    
    Graph(int _V);
    void AddEdge(int _u, int _v);
    void AddEdges( std::vector<std::pair<int, int>>& _edges_);
    void PrintPositions();
    int GetV();
    Point GetPosition(int _index);

    void Planarize(int _height, int _weight);
    void FRPlanarize(int _height,int _weight);
};

#endif // GRAPH_H
