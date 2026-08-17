#include "GridGraph.h"
#include <random>

Graph createGridGraph(int rows, int columns) {
    int totalNodes = rows * columns;

    Graph graph(totalNodes);

    // Starting coordinate: approximately Mumbai
    double startLatitude = 19.0760;
    double startLongitude = 72.8777;

    // Approximate spacing between neighboring nodes
    double latitudeStep = 0.01;
    double longitudeStep = 0.01;

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> variation(0.9, 1.1);

    // Assign coordinates
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {

            int node = row * columns + col;

            double latitude =
                startLatitude + row * latitudeStep;

            double longitude =
                startLongitude + col * longitudeStep;

            graph.setCoordinates(
                node,
                latitude,
                longitude
            );
        }
    }

    // Add roads between neighboring nodes
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {

            int current = row * columns + col;

            // Right neighbor
            if (col + 1 < columns) {
                int right = row * columns + (col + 1);

                double weight = 1.0 * variation(generator);

                graph.addEdge(current, right, weight);
                graph.addEdge(right, current, weight);
            }

            // Bottom neighbor
            if (row + 1 < rows) {
                int bottom = (row + 1) * columns + col;

                double weight = 1.0 * variation(generator);

                graph.addEdge(current, bottom, weight);
                graph.addEdge(bottom, current, weight);
            }
        }
    }

    return graph;
}