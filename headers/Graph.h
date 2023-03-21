//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_GRAPH_H
#define DA1_GRAPH_H

#include "Station.h"

#include <unordered_map>
#include <list>
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

    std::unordered_map<std::string, Node> nodes;

public:
    explicit Graph();

    void addNode(const std::string& name, const std::string& district,const std::string& municipality, const std::string& township, const std::string& line);
    void addBidirectionalEdge(const std::string& first, const std::string& second, unsigned capacity, const std::string& service);

    const std::unordered_map<std::string, Node>& getNodes() const;
    std::list<std::string> getStationsInDistrict(const std::string& district) const;
};
#endif //DA1_GRAPH_H
