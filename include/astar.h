#ifndef ASTAR_H
#define ASTAR_H

#include "graph.h"
#include <vector>

struct AStarResult {
    double distance;
    std::vector<int> path;
    int nodesExplored;
};

AStarResult aStar(const Graph& graph, int source, int destination);

#endif