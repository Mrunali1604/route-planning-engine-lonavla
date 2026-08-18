#include "graphload.h"

#include <fstream>
#include <sstream>
#include <iostream>

Graph loadGraphFromCSV(
    const std::string& nodesFile,
    const std::string& edgesFile
) {
    std::ifstream nodeFile(nodesFile);

    if (!nodeFile.is_open()) {
        throw std::runtime_error(
            "Could not open nodes file: " + nodesFile
        );
    }

    std::string line;

    
    std::getline(nodeFile, line);

    
    int numNodes = 0;

    while (std::getline(nodeFile, line)) {
        if (!line.empty()) {
            numNodes++;
        }
    }

    nodeFile.close();

    Graph graph(numNodes);

    
    nodeFile.open(nodesFile);

    
    std::getline(nodeFile, line);

    while (std::getline(nodeFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string idString;
        std::string osmIdString;
        std::string latitudeString;
        std::string longitudeString;

        std::getline(ss, idString, ',');
        std::getline(ss, osmIdString, ',');
        std::getline(ss, latitudeString, ',');
        std::getline(ss, longitudeString, ',');

        int id = std::stoi(idString);
        double latitude = std::stod(latitudeString);
        double longitude = std::stod(longitudeString);

        graph.setCoordinates(
            id,
            latitude,
            longitude
        );
    }

    nodeFile.close();

    

    std::ifstream edgeFile(edgesFile);

    if (!edgeFile.is_open()) {
        throw std::runtime_error(
            "Could not open edges file: " + edgesFile
        );
    }

   
    std::getline(edgeFile, line);

    while (std::getline(edgeFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string sourceString;
        std::string destinationString;
        std::string distanceString;

        std::getline(ss, sourceString, ',');
        std::getline(ss, destinationString, ',');
        std::getline(ss, distanceString, ',');

        int source = std::stoi(sourceString);
        int destination = std::stoi(destinationString);
        double distance = std::stod(distanceString);

        graph.addEdge(
            source,
            destination,
            distance
        );
    }

    edgeFile.close();

    return graph;
}
