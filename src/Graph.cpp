//
// Created by kikoveiga on 14-03-2023.
//

#include "Graph.h"

using namespace std;

Graph::Graph() = default;

const vector<Station>& Graph::getStations() const {
    return stations;
}

void Graph::addStation(Station station) {
    stations.push_back(station);
}