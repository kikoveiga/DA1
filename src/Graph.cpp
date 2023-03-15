//
// Created by kikoveiga on 14-03-2023.
//

#include "Graph.h"

using namespace std;

Graph::Graph() = default;

void Graph::addStation(Station station) {
    stations.insert({station.getName(), station});
}

void Graph::addEdge(const std::string& first, const std::string& second, unsigned capacity, const std::string& service) {
    nodes[first].adj.push_back({second, capacity, service});
    nodes[second].adj.push_back({first, capacity, service});
}

const unordered_map<string, Station>& Graph::getStations() const {
    return stations;
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}