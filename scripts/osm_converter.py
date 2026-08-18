import osmnx as ox
import csv

INPUT_FILE = "data/lonavala.graphml"
NODES_FILE = "data/nodes.csv"
EDGES_FILE = "data/edges.csv"

print("Loading OSM graph...")

graph = ox.load_graphml(INPUT_FILE)


node_id_map = {
    osm_id: index
    for index, osm_id in enumerate(graph.nodes)
}

print(f"Loaded {len(node_id_map)} nodes")



with open(NODES_FILE, "w", newline="") as file:
    writer = csv.writer(file)

    writer.writerow([
        "id",
        "osm_id",
        "latitude",
        "longitude"
    ])

    for osm_id, node_id in node_id_map.items():
        data = graph.nodes[osm_id]

        writer.writerow([
            node_id,
            osm_id,
            data["y"],
            data["x"]
        ])



with open(EDGES_FILE, "w", newline="") as file:
    writer = csv.writer(file)

    writer.writerow([
        "source",
        "destination",
        "distance"
    ])

    for source, destination, data in graph.edges(data=True):

       
        distance_meters = float(data["length"])

        
        distance_km = distance_meters / 1000.0

        writer.writerow([
            node_id_map[source],
            node_id_map[destination],
            distance_km
        ])

print(f"Saved nodes to {NODES_FILE}")
print(f"Saved edges to {EDGES_FILE}")
