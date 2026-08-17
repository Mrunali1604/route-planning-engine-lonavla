# Route Planning Engine

A C++ route planning engine that computes shortest paths on a real-world road network using **Dijkstra's algorithm** and **A***. The project uses OpenStreetMap road data from Lonavala, Maharashtra, and provides a Flask API and lightweight web interface for route queries.

## Features

* Real-world road network from OpenStreetMap
* Graph-based road network representation
* Dijkstra shortest-path algorithm
* A* shortest-path algorithm with geographic heuristic
* Latitude/longitude-based nearest-node lookup
* Shortest-distance and path reconstruction
* Nodes explored and execution-time measurement
* Automated benchmark across 100 routes
* Flask REST API
* Web interface with 25 predefined Lonavala locations
* Side-by-side Dijkstra vs A* comparison

## Tech Stack

* **C++17** — routing engine and graph algorithms
* **CMake** — build system
* **Python** — OpenStreetMap data processing and Flask backend
* **Flask** — REST API
* **HTML/CSS/JavaScript** — frontend
* **OpenStreetMap** — real-world road network data

## Algorithms

### Dijkstra

Dijkstra's algorithm computes the shortest path by exploring nodes in increasing order of their current shortest known distance.

### A*

A* extends Dijkstra's approach by using a heuristic to prioritize nodes that are geographically closer to the destination.

For this project, the heuristic is based on the geographic coordinates of the road-network nodes.

Both algorithms are tested on the same routes, allowing their search efficiency to be compared.

## Dataset

The routing graph is based on OpenStreetMap road data for **Lonavala, Maharashtra, India**.

The processed graph contains approximately:

* **1,931 nodes**
* **4,506 edges**

The engine maps user-provided coordinates to the nearest road-network nodes before calculating the route.

## Benchmark

The project includes an automated benchmark that tests both algorithms across 100 randomly selected routes.

### Results

| Metric                            |     Result |
| --------------------------------- | ---------: |
| Routes tested                     |        100 |
| Distance mismatches               |          0 |
| Average nodes explored — Dijkstra |     969.45 |
| Average nodes explored — A*       |     361.82 |
| Average node reduction            | **65.78%** |
| Average execution time — Dijkstra |  0.4933 ms |
| Average execution time — A*       |  0.2712 ms |
| Average time reduction            | **43.95%** |

The zero distance mismatches confirm that both algorithms produced the same shortest-path distance across the tested routes, while A* explored substantially fewer nodes on average.

## Project Structure

```text
route-planning-engine-lonavla/
│
├── backend/
│   └── app.py
│
├── data/
│   ├── nodes.csv
│   ├── edges.csv
│   └── lonavala.graphml
│
├── frontend/
│   └── index.html
│
├── include/
│   ├── astar.h
│   ├── benchmark.h
│   ├── dijkstra.h
│   ├── graph.h
│   ├── graphload.h
│   └── gridgraph.h
│
├── scripts/
│   ├── osm_converter.py
│   └── osm_download.py
│
├── src/
│   ├── astar.cpp
│   ├── benchmark.cpp
│   ├── dijkstra.cpp
│   ├── graph.cpp
│   ├── graphload.cpp
│   ├── gridgraph.cpp
│   └── main.cpp
│
├── CMakeLists.txt
└── .gitignore
```

## Building the C++ Engine

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

The executable will be generated in:

```text
build/route_engine.exe
```

Run it with:

```bash
./build/route_engine.exe
```

## Running the Backend

Make sure Python and Flask are installed.

From the project root:

```bash
py -3.13 backend/app.py
```

The Flask server will start locally.


The frontend sends the selected coordinates to the Flask API, which passes the routing request to the C++ engine.
## Example

A route request can be made between locations such as:
```text
Source:      Lonavala Railway Station
Destination: Bhushi Dam

The interface displays:

* Shortest distance
* Computed path
* Dijkstra vs A* nodes explored
* Dijkstra vs A* execution time


This project demonstrates the implementation and evaluation of classical shortest-path algorithms on a real-world geographic road network, combining **C++ graph algorithms**, **OpenStreetMap data**, and a **Python/Flask web interface**.
## Purpose
* Number of road nodes in the path
* Source and destination
```



