//
// Created by kikoveiga on 14-03-2023.
//

#include "Graph.h"

using namespace std;

Graph::Graph() = default;

const unordered_map<string, Station>& Graph::getStations() const {
    return stations;
}

void Graph::addStation(Station station) {
    stations.insert({station.getName(), station});
}