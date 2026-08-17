#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

struct Coordinates {
    double latitude;
    double longitude;
};

class Graph {
private:
    int numNodes;
    std::vector<std::vector<std::pair<int, double>>> adjacencyList;
    std::vector<Coordinates> coordinates;

public:
    Graph(int nodes);

    void addEdge(int source, int destination, double weight);

    void setCoordinates(int node, double latitude, double longitude);

    Coordinates getCoordinates(int node) const;

    int getNumNodes() const;
    
    int findNearestNode(double latitude, double longitude) const;

    void printGraph() const;

    const std::vector<std::vector<std::pair<int, double>>>&
    getAdjacencyList() const;
};

#endif