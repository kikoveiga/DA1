//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_GRAPH_H
#define DA1_GRAPH_H

#include "Station.h"

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
#include <limits>

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
        bool visited = false;
    };

    std::unordered_map<std::string, Node> nodes;

public:
    explicit Graph();
    /**
     * Add a Node to the Graph
     * Complexity = O(n)
     */
    void addNode(const std::string& name, const std::string& district,const std::string& municipality, const std::string& township, const std::string& line);

    /**
     * Add a Edge between Node first and second
     *
     * @param first
     * @param second
     * @param capacity
     * @param service
     *  Complexity = O()
     */ // falta complexidade
    void addBidirectionalEdge(const std::string& first, const std::string& second, unsigned capacity, const std::string& service);

    const std::unordered_map<std::string, Node>& getNodes() const;
    std::vector<std::string> getStationsInDistrict(const std::string& district) const;
    std::vector<std::string> getStationsInMunicipality(const std::string& municipality) const;
    std::vector<std::string> getStationsInTownship(const std::string& township) const;
    std::vector<std::string> getStationsInLine(const std::string& line) const;

    void setAllNodesUnvisited();

    bool bfs(std::unordered_map<std::string, std::pair<std::string, unsigned>>& parent, std::string source, std::string sink);

    unsigned edmondsKarp(std::string source, std::string sink);

    std::vector<std::pair<std::pair<std::string, std::string>, unsigned>> getMaxFlowStations();

};
#endif //DA1_GRAPH_H
