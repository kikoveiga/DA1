//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_GRAPH_H
#define DA1_GRAPH_H

#include "Station.h"

#include <unordered_map>
#include <vector>


class Graph {

private:

    struct Edge {
        std::string destination;
        unsigned capacity;
        std::string service;
    };

    struct Node {
        Station* source;
        std::vector<Edge> adj;
    };

    std::unordered_map<std::string, Station> stations;
    std::unordered_map<std::string, Node> nodes;

public:
    explicit Graph();

    void addStation(Station station);
    void addEdge(const std::string& source, const std::string& destination, unsigned capacity, const std::string& service);

    const std::unordered_map<std::string, Station>& getStations() const;
    const std::unordered_map<std::string, Node>& getNodes() const;
};
#endif //DA1_GRAPH_H
