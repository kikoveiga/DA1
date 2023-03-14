//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_GRAPH_H
#define DA1_GRAPH_H

#include "Station.h"

#include <vector>


class Graph {

private:
    std::vector<Station> stations;

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
    const std::vector<Station>& getStations() const;
};
#endif //DA1_GRAPH_H
