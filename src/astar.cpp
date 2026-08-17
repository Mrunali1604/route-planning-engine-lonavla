#include "AStar.h"
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>


double heuristic(
    const Graph& graph,
    int node,
    int destination
) {
    Coordinates current = graph.getCoordinates(node);
    Coordinates target = graph.getCoordinates(destination);

    constexpr double EARTH_RADIUS_KM = 6371.0;

    double lat1 = current.latitude * M_PI / 180.0;
    double lat2 = target.latitude * M_PI / 180.0;

    double deltaLat =
        (target.latitude - current.latitude) * M_PI / 180.0;

    double deltaLon =
        (target.longitude - current.longitude) * M_PI / 180.0;

    double a =
        std::sin(deltaLat / 2.0) *
        std::sin(deltaLat / 2.0) +
        std::cos(lat1) *
        std::cos(lat2) *
        std::sin(deltaLon / 2.0) *
        std::sin(deltaLon / 2.0);

    double c =
        2.0 * std::atan2(
            std::sqrt(a),
            std::sqrt(1.0 - a)
        );

    return EARTH_RADIUS_KM * c;
}

AStarResult aStar(const Graph& graph, int source, int destination) {
    const auto& adjacencyList = graph.getAdjacencyList();

    int numNodes = adjacencyList.size();

    const double INF = std::numeric_limits<double>::infinity();

    std::vector<double> gScore(numNodes, INF);
    std::vector<double> fScore(numNodes, INF);
    std::vector<int> parent(numNodes, -1);

    int nodesExplored = 0;

    using State = std::pair<double, int>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > openSet;

    gScore[source] = 0.0;
    fScore[source] = heuristic(graph, source, destination);

    openSet.push({fScore[source], source});

    while (!openSet.empty()) {
        auto [currentFScore, currentNode] = openSet.top();
        openSet.pop();

        if (currentFScore > fScore[currentNode]) {
            continue;
        }

        nodesExplored++;

        if (currentNode == destination) {
            break;
        }

        for (const auto& edge : adjacencyList[currentNode]) {
            int neighbor = edge.first;
            double weight = edge.second;

            double tentativeGScore =
                gScore[currentNode] + weight;

            if (tentativeGScore < gScore[neighbor]) {
                parent[neighbor] = currentNode;
                gScore[neighbor] = tentativeGScore;

                fScore[neighbor] =
                    gScore[neighbor] +
                    heuristic(graph, neighbor, destination);

                openSet.push({
                    fScore[neighbor],
                    neighbor
                });
            }
        }
    }

    AStarResult result;

    result.distance = gScore[destination];
    result.nodesExplored = nodesExplored;

    if (gScore[destination] == INF) {
        return result;
    }

    int current = destination;

    while (current != -1) {
        result.path.push_back(current);
        current = parent[current];
    }

    std::reverse(result.path.begin(), result.path.end());

    return result;
}