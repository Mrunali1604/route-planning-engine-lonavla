#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include "Graph.h"
#include <string>

Graph loadGraphFromCSV(
    const std::string& nodesFile,
    const std::string& edgesFile
);

#endif