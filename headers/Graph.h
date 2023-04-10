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
        int cost = 2 * (service == "STANDARD") + 4 * (service == "ALFA PENDULAR");
    };

    struct Node {
        Station station;
        std::vector<Edge*> adj;
        std::vector<Edge*> incoming;
        bool visited = false;
        Edge* path = nullptr;
        int distanceDijkstra;
    };

    std::unordered_map<std::string, Node*> nodes;

public:

    explicit Graph();
    /**
     * @brief add a node to the graph's set of nodes
     * @param name
     * @param district
     * @param municipality
     * @param township
     * @param line
     */
    void addNode(const std::string& name, const std::string& district,const std::string& municipality, const std::string& township, const std::string& line);
    /**
     *
     * @param name
     * @return Pointer to the Graph's node with the station name
     */
    Node* findNode(const std::string& name);
    /**
     *
     * @return Graph's set of nodes.
     */
    const std::unordered_map<std::string, Node*>& getNodes() const;
    /**
     *
     * @param district
     * @return vector with the names of every station in a District
     */
    std::vector<std::string> getStationsInDistrict(const std::string& district) const;
    /**
     *
     * @param municipality
     * @return vector with all the Stations in a Municipality
     */
    std::vector<std::string> getStationsInMunicipality(const std::string& municipality) const;
    /**
     *
     * @param township
     * @return vector with all the Stations in a Township
     */
    std::vector<std::string> getStationsInTownship(const std::string& township) const;
    /**
     *
     * @param line
     * @return vector with all the stations in a line
     */
    std::vector<std::string> getStationsInLine(const std::string& line) const;

    /**
     * @brief adds a Bidirectional edge between first and second station
     * @param first
     * @param second
     * @param capacity
     * @param service
     */
    void addBidirectionalEdge(const std::string& first, const std::string& second, int capacity, const std::string& service);

    /**
     * @brief returns a pointer to the edge between source and destination
     * @param source
     * @param destination
     * @return
     */
    static Edge* findEdge(Node* source, Node* destination);

    /**
     * @brief removes the element edge from the vector edges
     * @param edge
     * @param edges
     */
    static void removeEdge(Edge* edge, std::vector<Edge*>& edges);

    /**
     * @brief uses removeEdge(Edge* edge, std::vector<Edge*>& edges) to remove a bidirectional edge between station1 and station2
     * @param station1
     * @param station2
     */
    static void removeBidirectionalEdge(Node* station1, Node* station2);

    /**
     * @brief sets all nodes visited field to false
     */
    void setAllNodesUnvisited();

    /**
     * sets all nodes flow to 0
     */
    void setAllFlows0();

    /**
     * @brief depth-first-search algorithm
     * @brief Complexity = O(V + E)
     * @param node
     */
    void dfs(Node* node);
    /**
     * @brief edmonds karp algorithm to calculate the max number of trains capable of
     * @brief Complexity = O(VE^)
     * @param source
     * @param sink
     * @return
     */
    int edmondsKarp(Node* source, Node* sink);
    /**
     * @brief breadth first search to find augmenting paths using test and Visit
     * @brief Complexity = O(V + E)
     * @param source
     * @param sink
     * @return
     */
    bool bfsFindAugmentingPath(Node* source, Node* sink);
    /**
     * @brief function to get the bottleneck capacity alongside all edges on an augmenting path
     * @brief Complexity = O(n) n = size of path
     */
    static int findMinResidualAlongPath(Node* source, Node* sink);
    /**
     * @brief function to augment the flow alongside all edges on an augmenting path
     * @brief Complexity = O(n), n = size of path
     * @param source
     * @param sink
     * @param flow
     */
    static void augmentFlowAlongPath(Node* source, Node* sink, int flow);
    /**
     * @brief helper function for bfsFindAugmentingPath changes the visit and path field of each node. Also pushes the node to the bfs queue if needed
     * @brief Complexity = O(1)
     * @param queue
     * @param edge
     * @param next
     * @param residual
     */
    static void testAndVisit(std::queue<Node*>& queue, Edge* edge, Node* next, int residual);


    struct FlowStations {
        int flow;
        std::string source;
        std::string destination;
    };

    /**
     * @brief gets all pairs of stations with higher maxflow between them.
     * @brief Complexity = O(V²x (VE²))
     * @return a vector with all pairs of stations with the highest max flow between them
     */
    std::vector<FlowStations> getMaxFlowStations();

    /**
     * @brief returns a vector with the flow for each pair of stations ordered decreasingly by flow
     * @brief Complexity = O (V²x(VE²))
     * @return vector with every pair of stations with the associated flow between them ordered decreasingly by fow
     */
    std::vector<FlowStations> getAllFlows();

    /**
     * @brief dijkstra algorithm to determine the flow and cost of the cheapest path between 2 stations
     * @brief Complexity = O(E + V(log(V))
     * @param source Node* source of the path
     * @param target Node* target of the path
     * @return int  the cost of the path
     */
    int dijkstra(Node* source, Node* target);

    /**
     * @brief helper function to sort the priority queue increasingly by dijkstrasdistance field in dijkstra's algorithm
     * @Complexity = O(1)
     * @param node1 Node* first node to compare
     * @param node2 Node* second node to compare
     * @return boolean node1 < node2;
     */
    static bool compareDijkstra(Node* node1, Node* node2);

    /**
     * @brief Similar to bfsFindAugmentingPath but giving priority to the cheapest edges
     * @brief Complexity = O(V + E)
     * @param source Node* source of the bfs
     * @param sink Node* sink of the bfs
     * @return boolean reflects if search found the sink
     */
    bool bfsFindCheapAugmentingPath(Node* source, Node* sink);
    /**
     * @brief Similar to augmentFlowAlongPath but also augmenting the cost
     * @brief Complexity = O()
     * @param source Node* source of the bfs
     * @param sink Node* sink of the bfs
     * @param f int flow
     * @param cost int cost
     */
    static void augmentFlowAlongPathCost(Node* source, Node* sink, int f, int& cost);
    /**
     * @brief Similar to edmondsKarp but providing the lowest cost while keeping the maxFlow
     * @brief Complexity = O(VE²)
     * @param source Node* source of the path
     * @param sink Node* sink of the path
     * @return pair<int flow, int cost>
     */
    std::pair<int,int> cheapEdmondsKarp(Node* source, Node* sink);
    /**
     * @brief Provides the max number of trains that can reach a station at the same time
     * @complexity = O(VE²)
     * @param station Node* station
     * @return affluence int number of trains that can arrive at a station simultaneously
     */
    int maxAffluenceAtStation(Node* station);

};

#endif //DA1_GRAPH_H
