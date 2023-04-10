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

    /**
     * @brief Default Graph constructor
     */
    explicit Graph();

    /**
     * @brief add a node to the graph's map of nodes
     * @param name string with the name of the node/station
     * @param district string with the district of the station
     * @param municipality string with the municipality of the station
     * @param township string with the township of the station
     * @param line string with the line of the station
     */
    void addNode(const std::string& name, const std::string& district,const std::string& municipality, const std::string& township, const std::string& line);

    /**
     *
     * @param name string with the name of the node/station
     * @return Pointer to the Graph's node with the station's name
     */
    Node* findNode(const std::string& name);

    /**
     *@brief Get function for the map of nodes
     * @return Graph's map of nodes.
     */
    const std::unordered_map<std::string, Node*>& getNodes() const;

    /**
     * @brief Get function for the stations in a district
     * @param district string with the name of the district
     * @return vector with all the stations in a district
     */
    std::vector<std::string> getStationsInDistrict(const std::string& district) const;

    /**
     *@brief Get function for the stations in a municipality
     * @param municipality string with the name of the municipality
     * @return vector with all the stations in a municipality
     */
    std::vector<std::string> getStationsInMunicipality(const std::string& municipality) const;

    /**
     *@brief Get function for the stations in a township
     * @param township string with the name of the township
     * @return vector with all the stations in a Township
     */
    std::vector<std::string> getStationsInTownship(const std::string& township) const;

    /**
     *@brief Get function for the stations in a line
     * @param line string with the name of the line
     * @return vector with all the stations in a line
     */
    std::vector<std::string> getStationsInLine(const std::string& line) const;

    /**
     * @brief Function that adds a Bidirectional edge between first and second station
     * @param first string with the name of the first station
     * @param second string with the name of the second station
     * @param capacity int with the capacity of the edge
     * @param service string with the service
     */
    void addBidirectionalEdge(const std::string& first, const std::string& second, int capacity, const std::string& service);

    /**
     * @brief Function that returns a pointer to the edge between source and destination
     * @param source node pointer of the source station
     * @param destination node pointer of the destination station
     * @return an edge pointer
     */
    static Edge* findEdge(Node* source, Node* destination);

    /**
     * @brief Function thar removes the element edge from the vector edges
     * @param edge pointer to the edge to be removed
     * @param edges vector which store the edges
     */
    static void removeEdge(Edge* edge, std::vector<Edge*>& edges);

    /**
     * @brief uses removeEdge(Edge* edge, std::vector<Edge*>& edges) to remove a bidirectional edge between station1 and station2 from all adj and incoming vectors
     * @param station1 node pointer to the first station
     * @param station2 node pointer to the second station
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
     * @param node pointer to a source node
     */
    void dfs(Node* source);

    /**
     * @brief Edmonds Karp algorithm to calculate the max number of trains capable of travelling simultaneously from source to sink
     * @brief Complexity = O(VE²)
     * @param source node pointer to the source node
     * @param sink node pointer to the sink node
     * @return int with max flow
     */
    int edmondsKarp(Node* source, Node* sink);

    /**
     * @brief breadth first search to find augmenting paths using test and Visit
     * @brief Complexity = O(V + E)
     * @param source
     * @param sink
     * @return bool with visited field of sink node
     */
    bool bfsFindAugmentingPath(Node* source, Node* sink);

    /**
     * @brief Function to get the bottleneck capacity alongside all edges on an augmenting path
     * @brief Complexity = O(n) n = size of path
     * @param source node pointer to the source node
     * @param sink node pointer to the sink node
     * @return int with minimum residual along path
     */
    static int findMinResidualAlongPath(Node* source, Node* sink);

    /**
     * @brief Function to augment the flow alon all edges on an augmenting path
     * @brief Complexity = O(n), n = size of path
     * @param source node pointer to the source node
     * @param sink node pointer to the sink node
     * @param flow int with the current flow
     */
    static void augmentFlowAlongPath(Node* source, Node* sink, int flow);

    /**
     * @brief Helper function for bfsFindAugmentingPath that changes the visit and path field of each node. Also pushes the node to the bfs queue if needed
     * @brief Complexity = O(1)
     * @param queue of nodes to be visited
     * @param edge pointer to the next edge
     * @param next node pointer to the next node to be visited
     * @param residual int with the residual
     */
    static void testAndVisit(std::queue<Node*>& queue, Edge* edge, Node* next, int residual);

    /**
     * @brief struct that the Menu receives with the max flow between source and destination
     * @param int flow
     * @param string source station
     * @param string destination station
     */
    struct FlowStations {
        int flow;
        std::string source;
        std::string destination;
    };

    /**
     * @brief gets all pairs of stations with the highest maxflow in the respective district or municipality. Implemented in a subgraph.
     * @brief Complexity = O(V²x(VE²))
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
     * @brief Dijkstra algorithm to determine the max flow and cost of the cheapest path between 2 stations
     * @brief Complexity = O(E + V(log(V))
     * @param source Node pointer to the source of the path
     * @param target Node pointer to the target of the path
     * @return int  the cost of the path
     */
    int dijkstra(Node* source, Node* target);

    /**
     * @brief Helper function to sort the priority queue increasingly by dijkstrasdistance field in dijkstra's algorithm
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
     * @return int affluence, number of trains that can arrive at a station simultaneously
     */
    int maxAffluenceAtStation(Node* station);

    /**
     * @brief Function that calculates the top Max Affluence Stations and stores them in decreasing order in a vector
     * @complexity = O(VE²)
     * @return vector with pairs of stations and respective max affluence
     */
    std::vector<std::pair<int, std::string>> topMaxAffluenceStations();

};

#endif //DA1_GRAPH_H
