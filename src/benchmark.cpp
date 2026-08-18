#include "Benchmark.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>
#include <cmath>

#include "Dijkstra.h"
#include "AStar.h"

void runBenchmark(
    const Graph& graph,
    int numberOfRoutes
) {
    std::cout << "\n=== Automated Routing Benchmark ===\n\n";

    const int numNodes = graph.getNumNodes();

    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(0, numNodes - 1);

    long long totalDijkstraNodes = 0;
    long long totalAStarNodes = 0;

    double totalDijkstraTime = 0.0;
    double totalAStarTime = 0.0;

    double totalNodeReduction = 0.0;
    double totalTimeReduction = 0.0;

    int validRoutes = 0;
    int distanceMismatches = 0;

    std::cout << std::left
              << std::setw(8) << "Route"
              << std::setw(18) << "Dijkstra Nodes"
              << std::setw(14) << "A* Nodes"
              << std::setw(18) << "Dijkstra ms"
              << std::setw(12) << "A* ms"
              << "\n";

    std::cout << std::string(70, '-') << "\n";

    for (int i = 0; i < numberOfRoutes; i++) {

        int source = distribution(generator);
        int destination = distribution(generator);

        if (source == destination) {
            i--;
            continue;
        }

       

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

        
        if (dijkstraResult.path.empty() ||
            aStarResult.path.empty()) {
            i--;
            continue;
        }

        validRoutes++;

        // Verify both algorithms found the same distance
        if (std::abs(
                dijkstraResult.distance -
                aStarResult.distance
            ) > 1e-6) {

            distanceMismatches++;
        }

        totalDijkstraNodes +=
            dijkstraResult.nodesExplored;

        totalAStarNodes +=
            aStarResult.nodesExplored;

        totalDijkstraTime += dijkstraTime;
        totalAStarTime += aStarTime;

        double nodeReduction =
            (1.0 -
             static_cast<double>(aStarResult.nodesExplored) /
             dijkstraResult.nodesExplored) * 100.0;

        double timeReduction =
            (1.0 -
             aStarTime / dijkstraTime) * 100.0;

        totalNodeReduction += nodeReduction;
        totalTimeReduction += timeReduction;

        std::cout << std::fixed
                  << std::setprecision(4)
                  << std::left
                  << std::setw(8) << validRoutes
                  << std::setw(18)
                  << dijkstraResult.nodesExplored
                  << std::setw(14)
                  << aStarResult.nodesExplored
                  << std::setw(18)
                  << dijkstraTime
                  << std::setw(12)
                  << aStarTime
                  << "\n";
    }

    

    std::cout << "\n=== Benchmark Summary ===\n\n";

    std::cout << "Routes tested: "
              << validRoutes
              << "\n";

    std::cout << "Distance mismatches: "
              << distanceMismatches
              << "\n\n";

    if (validRoutes > 0) {

        double avgDijkstraNodes =
            static_cast<double>(totalDijkstraNodes) /
            validRoutes;

        double avgAStarNodes =
            static_cast<double>(totalAStarNodes) /
            validRoutes;

        double avgDijkstraTime =
            totalDijkstraTime /
            validRoutes;

        double avgAStarTime =
            totalAStarTime /
            validRoutes;

        double avgNodeReduction =
            totalNodeReduction /
            validRoutes;

        double avgTimeReduction =
            totalTimeReduction /
            validRoutes;

        std::cout << std::fixed
                  << std::setprecision(4);

        std::cout << "Average nodes explored:\n";
        std::cout << "  Dijkstra: "
                  << avgDijkstraNodes
                  << "\n";

        std::cout << "  A*:       "
                  << avgAStarNodes
                  << "\n\n";

        std::cout << "Average execution time:\n";
        std::cout << "  Dijkstra: "
                  << avgDijkstraTime
                  << " ms\n";

        std::cout << "  A*:       "
                  << avgAStarTime
                  << " ms\n\n";

        std::cout << "Average node reduction: "
                  << avgNodeReduction
                  << "%\n";

        std::cout << "Average time reduction: "
                  << avgTimeReduction
                  << "%\n";
    }
}
