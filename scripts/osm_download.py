import osmnx as ox

print("Downloading road network...")

# Bounding box around Lonavala
north = 18.78
south = 18.70
east = 73.48
west = 73.38

graph = ox.graph_from_bbox(
    (west, south, east, north),
    network_type="drive"
)

print(f"Nodes: {len(graph.nodes)}")
print(f"Edges: {len(graph.edges)}")

ox.save_graphml(
    graph,
    "data/lonavala.graphml"
)

print("Saved to data/lonavala.graphml")