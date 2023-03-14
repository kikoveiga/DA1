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
    std::unordered_map<std::string, Station> stations;

    struct Edge {
        Station* dest;
        Station* source;
        int capacity;
    };

    struct Node {
        Station* station;
        std::vector<Edge *> adj;
    };


public:
    explicit Graph();
    void addStation(Station station);
    const std::unordered_map<std::string, Station>& getStations() const;
};
#endif //DA1_GRAPH_H
