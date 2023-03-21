//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Graph.h"

using namespace std;

Graph::Graph() = default;

void Graph::addNode(const std::string& name, const std::string& district, const std::string& municipality, const std::string& township, const std::string& line) {
    auto* station = new Station(name, district, municipality, township, line);
    nodes.insert({name, {station, {}}});
}

void Graph::addBidirectionalEdge(const std::string& first, const std::string& second, unsigned capacity, const std::string& service) {
    nodes[first].adj.push_back({second, capacity, service});
    nodes[second].adj.push_back({first, capacity, service});
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}

list<string> Graph::getStationsInDistrict(const std::string &district) const {
    list<string> stations;
    for (auto &node: nodes) {
        if (node.second.source->getDistrict() == district) {
            stations.push_back(node.first);
        }
    }
    return stations;
}