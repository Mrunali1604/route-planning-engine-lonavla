#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <algorithm>

PathResult dijkstra(const Graph& graph, int source, int destination) {
    const auto& adjacencyList = graph.getAdjacencyList();

    int numNodes = adjacencyList.size();

    const double INF = std::numeric_limits<double>::infinity();

    std::vector<double> distance(numNodes, INF);
    std::vector<int> parent(numNodes, -1);

    int nodesExplored = 0;

    using State = std::pair<double, int>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pq;

    distance[source] = 0.0;
    pq.push({0.0, source});

    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentDistance > distance[currentNode]) {
            continue;
        }

        nodesExplored++;

        if (currentNode == destination) {
            break;
        }

        for (const auto& edge : adjacencyList[currentNode]) {
            int neighbor = edge.first;
            double weight = edge.second;

            double newDistance = currentDistance + weight;

            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                parent[neighbor] = currentNode;

                pq.push({newDistance, neighbor});
            }
        }
    }

    PathResult result;
    result.distance = distance[destination];
    result.nodesExplored = nodesExplored;

    if (distance[destination] == INF) {
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