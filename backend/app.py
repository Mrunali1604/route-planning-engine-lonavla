from flask import Flask, request, jsonify
import subprocess
import os
import re
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

ENGINE_PATH = r"C:\Users\Mrunali\route-planning-engine\build\route_engine.exe"


@app.route("/")
def home():
    return jsonify({
        "service": "Route Planning Engine",
        "status": "running"
    })


@app.route("/route", methods=["GET"])
def route():

    source_lat = request.args.get("source_lat", type=float)
    source_lon = request.args.get("source_lon", type=float)

    destination_lat = request.args.get("destination_lat", type=float)
    destination_lon = request.args.get("destination_lon", type=float)

    if None in (
        source_lat,
        source_lon,
        destination_lat,
        destination_lon
    ):
        return jsonify({
            "error": "Missing coordinates"
        }), 400

    env = os.environ.copy()
    env["PATH"] = r"C:\msys64\ucrt64\bin;" + env["PATH"]

    try:

        result = subprocess.run(
            [
                ENGINE_PATH,
                str(source_lat),
                str(source_lon),
                str(destination_lat),
                str(destination_lon)
            ],
            capture_output=True,
            text=True,
            check=True,
            env=env
        )

        output = result.stdout

        path_match = re.search(
        r"PATH:([0-9,]+)",
        output
        )

        if not path_match:
            return jsonify({
            "status": "error",
            "message": "Route path not found"
        }), 500

        path = [
        int(node)
        for node in path_match.group(1).split(",")
        ]

        # Extract C++ results
        source_node = re.search(
            r"Source node:\s*(\d+)",
            output
        )

        destination_node = re.search(
            r"Destination node:\s*(\d+)",
            output
        )

        dijkstra_distance = re.search(
            r"=== Dijkstra ===.*?Shortest distance:\s*([\d.]+)",
            output,
            re.S
        )

        dijkstra_nodes = re.search(
            r"=== Dijkstra ===.*?Nodes explored:\s*(\d+)",
            output,
            re.S
        )

        dijkstra_time = re.search(
            r"=== Dijkstra ===.*?Execution time:\s*([\d.]+)",
            output,
            re.S
        )

        astar_distance = re.search(
            r"=== A\* ===.*?Shortest distance:\s*([\d.]+)",
            output,
            re.S
        )

        astar_nodes = re.search(
            r"=== A\* ===.*?Nodes explored:\s*(\d+)",
            output,
            re.S
        )

        astar_time = re.search(
            r"=== A\* ===.*?Execution time:\s*([\d.]+)",
            output,
            re.S
        )

        return jsonify({
            "status": "success",

            "source": {
                "latitude": source_lat,
                "longitude": source_lon,
                "node": int(source_node.group(1))
            },

            "destination": {
                "latitude": destination_lat,
                "longitude": destination_lon,
                "node": int(destination_node.group(1))
            },

            "dijkstra": {
                "distance_km": float(dijkstra_distance.group(1)),
                "nodes_explored": int(dijkstra_nodes.group(1)),
                "execution_time_ms": float(dijkstra_time.group(1))
            },

            "astar": {
                "distance_km": float(astar_distance.group(1)),
                "nodes_explored": int(astar_nodes.group(1)),
                "execution_time_ms": float(astar_time.group(1)),
                "path": path
            }
        })

    except subprocess.CalledProcessError as error:

        return jsonify({
            "status": "error",
            "message": error.stderr
        }), 500


if __name__ == "__main__":
    app.run(debug=True)