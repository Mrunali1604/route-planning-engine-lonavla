#include "Graph.h"
#include <iostream>
#include <limits>
#include <cmath>

Graph::Graph(int nodes) {
    numNodes = nodes;

    adjacencyList.resize(nodes);
    coordinates.resize(nodes);
}

void Graph::addEdge(int source, int destination, double weight) {
    adjacencyList[source].push_back({destination, weight});
}

void Graph::setCoordinates(
    int node,
    double latitude,
    double longitude
) {
    coordinates[node] = {latitude, longitude};
}

Coordinates Graph::getCoordinates(int node) const {
    return coordinates[node];
}

int Graph::getNumNodes() const {
    return numNodes;
}

void Graph::printGraph() const {
    for (int i = 0; i < numNodes; i++) {
        std::cout << i << " -> ";

        for (const auto& edge : adjacencyList[i]) {
            std::cout << "("
                      << edge.first
                      << ", " << edge.second
                      << ") ";
        }

        std::cout << '\n';
    }
}

const std::vector<std::vector<std::pair<int, double>>>&
Graph::getAdjacencyList() const {
    return adjacencyList;
}

int Graph::findNearestNode(
    double latitude,
    double longitude
) const {

    int nearestNode = -1;
    double minimumDistance = std::numeric_limits<double>::infinity();

    for (int i = 0; i < numNodes; i++) {

        double latDifference =
            coordinates[i].latitude - latitude;

        double lonDifference =
            coordinates[i].longitude - longitude;

        double distance =
            latDifference * latDifference +
            lonDifference * lonDifference;

        if (distance < minimumDistance) {
            minimumDistance = distance;
            nearestNode = i;
        }
    }

    return nearestNode;
}

