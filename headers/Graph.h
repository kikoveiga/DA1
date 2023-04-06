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
#include <algorithm>

class Graph {

private:

    struct Node;

    struct Edge {
        Node* source;
        Node* destination;
        int capacity;
        std::string service;
        int flow;
    };

    struct Node {
        Station station;
        std::vector<Edge*> adj;
        std::vector<Edge*> incoming;
        bool visited = false;
        Edge* path = nullptr;
    };


    std::unordered_map<std::string, Node*> nodes;

public:
    explicit Graph();

    /**
     * Add a Node to the Graph
     * Complexity = O(n)
     */

    void addNode(Node* node);
    void addNode(const std::string& name, const std::string& district,const std::string& municipality, const std::string& township, const std::string& line);

    Node* findNode(const std::string& name);
    /**
     * Add a Edge between Node first and second
     *
     * @param first
     * @param second
     * @param capacity
     * @param service
     *  Complexity = O()
     */ // falta complexidade
    void addBidirectionalEdge(const std::string& first, const std::string& second, int capacity, const std::string& service);

    const std::unordered_map<std::string, Node*>& getNodes() const;
    std::vector<std::string> getStationsInDistrict(const std::string& district) const;
    std::vector<std::string> getStationsInMunicipality(const std::string& municipality) const;
    std::vector<std::string> getStationsInTownship(const std::string& township) const;
    std::vector<std::string> getStationsInLine(const std::string& line) const;

    void setAllNodesUnvisited();
    void setAllFlows0();

    void dfs(Node* node);

    bool bfs(std::unordered_map<std::string, std::pair<std::string, unsigned>>& parent, std::string source, std::string sink);

    int edmondsKarp(Node* source, Node* sink);
    bool bfsFindAugmentingPath(Node* source, Node* sink);
    int findMinResidualAlongPath(Node* source, Node* sink);
    void augmentFlowAlongPath(Node* source, Node* sink, int flow);
    void testAndVisit(std::queue<Node*>& queue, Edge* edge, Node* next, int residual);


    std::pair<int, std::vector<std::pair<std::string, std::string>>> getMaxFlowStations();

};
#endif //DA1_GRAPH_H
