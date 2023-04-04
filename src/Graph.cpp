//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Graph.h"

using namespace std;

Graph::Graph() = default;


void Graph::addNode(const string& name, const string& district, const string& municipality, const string& township, const string& line) {
    auto* station = new Station(name, district, municipality, township, line);
    nodes.insert({name, {station, {}}});
}

void Graph::addBidirectionalEdge(const string& first, const string& second, int capacity, const string& service) {

    Node* firstNode = &nodes[first];
    Node* secondNode = &nodes[second];

    firstNode->adj.push_back({secondNode, capacity, service});
    secondNode->adj.push_back({firstNode, capacity, service});
}

const unordered_map<string, Graph::Node>& Graph::getNodes() const {
    return nodes;
}

vector<string> Graph::getStationsInDistrict(const string& district) const {
    vector<string> stations;
    for (auto &node: nodes) {
        if (node.second.source->getDistrict() == district) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInMunicipality(const string& municipality) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second.source->getMunicipality() == municipality) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInTownship(const string& township) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second.source->getTownship() == township) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInLine(const string& line) const {
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

void Graph::setAllFlows0() {
    for (auto& v : nodes) {
        for (auto& e: v.second.adj) {
            e.flow = 0;
        }
    }
}

/*
bool Graph::bfs(unordered_map<string, pair<string, unsigned>>& parent, string source, string sink) {
    queue<string> q;
    q.push(source);
    parent[source] = make_pair("", 0);

    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        for (const auto& edge : nodes[curr].adj) {
            Node* dest = edge.destination;
            unsigned cap = edge.capacity;

            if (parent.find(dest) == parent.end() && cap > 0) {
                q.push(dest);
                parent[dest] = make_pair(curr, cap);

                if (dest == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

unsigned Graph::edmondsKarp(const string& source, const string& sink) {
    unsigned maxFlow = 0;

    while (true) {
        unordered_map<string, pair<string, unsigned>> parent;
        if (!bfs(parent, source, sink)) {
            break;
        }

        unsigned flow = INT32_MAX;
        string curr = sink;

        while (curr != source) {
            string prev = parent[curr].first;
            unsigned cap = parent[curr].second;
            flow = min(flow, cap);
            curr = prev;
        }

        maxFlow += flow;
        curr = sink;

        while (curr != source) {
            string prev = parent[curr].first;

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

vector<pair<pair<string, string>, unsigned>> Graph::getMaxFlowStations() {
    int maxFlow, flow = 0;
    vector<pair<pair<string, string>, unsigned>> res;
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
*/

void Graph::testAndVisit(queue<Node*> &queue, Edge* edge, Node* next, int residual) {
    if (!next->visited && residual > 0) {
        next->visited = true;
        next->path = edge;
        queue.push(next);
    }
}

bool Graph::findAugmentingPath(Node* source, Node* sink) {
    setAllNodesUnvisited();
    source->visited = true;

    queue<Node*> queue;
    queue.push(source);

    while (!queue.empty() && !sink->visited) {
        Node* node = queue.front();
        queue.pop();
        for(auto& edge: node->adj) {
            testAndVisit(queue, &edge, edge.destination, edge.capacity - edge.flow);
        }
        for(auto& e: node->adj) {
            testAndVisit(queue, &e, e.destination, e.flow); // acho que aqui é v porque lá têm e.getOrigin
        }
    }
    return sink->visited;
}

int Graph::findMinResidualAlongPath(Node* source, Node* sink) {
    int flow = INT32_MAX;
    for (auto v = sink; v != source;) {
        auto e = v->path;
        if (e->destination == v) {
            flow = std::min(flow, e->capacity - e->flow);
        }

        else {
            flow = min(flow, e->flow);
            v = e->destination;
        }
    }
    return flow;
}

void Graph::augmentFlowAlongPath(Node* source, Node* sink, int f) {
    for (Node* next = sink; next != source; ) {
        auto edge = next->path;
        double flow = edge->flow;
        if (edge->destination == next) {
            edge->flow = flow + f;
        }
        else {
            edge->flow = flow - f;
            next = edge->destination;
        }
    }
}

int Graph::edmondsKarp(Node* source, Node* sink) {

    int maxFlow = 0;
    setAllFlows0();

    // Loop to find augmentation paths
    while (findAugmentingPath(source, sink)) {
        int flow = findMinResidualAlongPath(source, sink);
        augmentFlowAlongPath(source, sink, flow);
        maxFlow += flow;
    }
    return maxFlow;
}
