#include <iostream>
#include <chrono>
#include <cstdlib>

#include "graph.h"
#include "dijkstra.h"
#include "aStar.h"
#include "graphload.h"
#include "benchmark.h"

void printPath(const std::vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];

        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << '\n';
}

void printPathCSV(const std::vector<int>& path) {
    std::cout << "PATH:";

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];

        if (i + 1 < path.size()) {
            std::cout << ",";
        }
    }

    std::cout << '\n';
}

int main(int argc, char* argv[]) {

    std::cout << "Route Planning Engine\n\n";

    Graph graph = loadGraphFromCSV(
        "data/nodes.csv",
        "data/edges.csv"
    );

    std::cout << "Loaded nodes: "
              << graph.getNumNodes()
              << "\n\n";

    

    double sourceLatitude;
    double sourceLongitude;
    double destinationLatitude;
    double destinationLongitude;

    if (argc == 5) {

        sourceLatitude = std::stod(argv[1]);
        sourceLongitude = std::stod(argv[2]);

        destinationLatitude = std::stod(argv[3]);
        destinationLongitude = std::stod(argv[4]);

    } else {

        // Temporary test route
        sourceLatitude = 18.7609806;
        sourceLongitude = 73.4454386;

        destinationLatitude = 18.7335116;
        destinationLongitude = 73.4437913;
    }

    int source = graph.findNearestNode(
        sourceLatitude,
        sourceLongitude
    );

    int destination = graph.findNearestNode(
        destinationLatitude,
        destinationLongitude
    );

    std::cout << "Source node: "
              << source << "\n";

    std::cout << "Destination node: "
              << destination << "\n\n";



    auto dijkstraStart =
        std::chrono::high_resolution_clock::now();

    PathResult dijkstraResult =
        dijkstra(graph, source, destination);

    auto dijkstraEnd =
        std::chrono::high_resolution_clock::now();

    double dijkstraTime =
        std::chrono::duration<double, std::milli>(
            dijkstraEnd - dijkstraStart
        ).count();

    std::cout << "=== Dijkstra ===\n";

    std::cout << "Shortest distance: "
              << dijkstraResult.distance
              << " km\n";

    std::cout << "Path length: "
              << dijkstraResult.path.size()
              << " nodes\n";

    std::cout << "Nodes explored: "
              << dijkstraResult.nodesExplored
              << "\n";

    std::cout << "Execution time: "
              << dijkstraTime
              << " ms\n\n";




    auto aStarStart =
        std::chrono::high_resolution_clock::now();

    AStarResult aStarResult =
        aStar(graph, source, destination);

    auto aStarEnd =
        std::chrono::high_resolution_clock::now();

    double aStarTime =
        std::chrono::duration<double, std::milli>(
            aStarEnd - aStarStart
        ).count();

    std::cout << "=== A* ===\n";

    std::cout << "Shortest distance: "
              << aStarResult.distance
              << " km\n";

    std::cout << "Path length: "
              << aStarResult.path.size()
              << " nodes\n";

    std::cout << "Nodes explored: "
              << aStarResult.nodesExplored
              << "\n";

    std::cout << "Execution time: "
              << aStarTime
              << " ms\n";

    printPathCSV(aStarResult.path);


    if (argc != 5) {
        runBenchmark(graph, 100);
    }

    return 0;
}
