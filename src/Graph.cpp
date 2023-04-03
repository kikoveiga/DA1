//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Graph.h"
#include <iostream>

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

vector<string> Graph::getStationsInDistrict(const std::string &district) const {
    vector<string> stations;
    for (auto &node: nodes) {
        if (node.second.source->getDistrict() == district) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInMunicipality(const std::string& municipality) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second.source->getMunicipality() == municipality) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInTownship(const std::string& township) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second.source->getTownship() == township) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInLine(const std::string& line) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second.source->getLine() == line) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

void Graph::setAllNodesUnvisited() {
    for (auto& i : nodes) {
        i.second.visited = false;
    }
}

bool Graph::bfs(std::unordered_map<std::string, std::pair<std::string, unsigned>>& parent, std::string source, std::string sink) {
    std::queue<std::string> q;
    q.push(source);
    parent[source] = std::make_pair("", 0);

    while (!q.empty()) {
        std::string curr = q.front();
        q.pop();

        for (const auto& edge : nodes[curr].adj) {
            std::string dest = edge.destination;
            unsigned cap = edge.capacity;

            if (parent.find(dest) == parent.end() && cap > 0) {
                q.push(dest);
                parent[dest] = std::make_pair(curr, cap);

                if (dest == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

unsigned Graph::edmondsKarp(std::string source, std::string sink) {
    unsigned maxFlow = 0;

    while (true) {
        std::unordered_map<std::string, std::pair<std::string, unsigned>> parent;
        if (!bfs(parent, source, sink)) {
            break;
        }

        unsigned flow = INT32_MAX;
        std::string curr = sink;

        while (curr != source) {
            std::string prev = parent[curr].first;
            unsigned cap = parent[curr].second;
            flow = std::min(flow, cap);
            curr = prev;
        }

        maxFlow += flow;
        curr = sink;

        while (curr != source) {
            std::string prev = parent[curr].first;

            for (auto& edge : nodes[prev].adj) {
                if (edge.destination == curr) {
                    edge.capacity -= flow;
                    break;
                }
            }

            bool reverseEdgeFound = false;
            for (auto& edge : nodes[curr].adj) {
                if (edge.destination == prev) {
                    edge.capacity += flow;
                    reverseEdgeFound = true;
                    break;
                }
            }

            if (!reverseEdgeFound) {
                Edge reverseEdge;
                reverseEdge.destination = prev;
                reverseEdge.capacity = flow;
                nodes[curr].adj.push_back(reverseEdge);
            }

            curr = prev;
        }
    }

    return maxFlow;
}

std::vector<std::pair<std::pair<std::string, std::string>, unsigned>> Graph::getMaxFlowStations() {
    int maxFlow, flow = 0;
    std::vector<std::pair<std::pair<std::string, std::string>, unsigned>> res;
    for (auto& a : nodes) {
        for (auto &b: nodes) {

            cout << a.first << "->" << b.first << endl;
            if (a.first >= b.first)
                continue;
            flow = edmondsKarp(a.first, b.first);
            if (flow > maxFlow) {
                res.clear();
                res.push_back({{a.first, b.first}, flow});
                maxFlow = flow;
            }
            else if (flow == maxFlow)
                res.push_back({{a.first, b.first}, flow});
        }
    }
    return res;
}

