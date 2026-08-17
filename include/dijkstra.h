#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>

struct PathResult {
    double distance;
    std::vector<int> path;
    int nodesExplored;
};

PathResult dijkstra(const Graph& graph, int source, int destination);

#endif