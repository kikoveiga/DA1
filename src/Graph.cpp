//
// Created by kikoveiga on 14-03-2023.
//

#include "Graph.h"

using namespace std;

Graph::Graph() = default;

void Graph::addStation(Station station) {
    stations.insert({station.getName(), station});
}

void Graph::addEdge(const std::string& source, const std::string& destination, unsigned capacity, const std::string& service) {
    nodes[source].adj.push_back({destination, capacity, service});
}

const unordered_map<string, Station>& Graph::getStations() const {
    return stations;
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}