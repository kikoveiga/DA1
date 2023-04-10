//
// Created by kikoveiga on 14-03-2023.
//

#include <functional>
#include "../headers/Graph.h"

using namespace std;

Graph::Graph() = default;

void Graph::addNode(const string& name, const string& district, const string& municipality, const string& township, const string& line) {
    Station station(name, district, municipality, township, line);
    auto* node = new Node{station};
    nodes[name] = node;
}

Graph::Node* Graph::findNode(const string& name) {
    if (nodes.find(name) == nullptr) return nullptr;
    return nodes[name];
}

void Graph::addBidirectionalEdge(const string& first, const string& second, int capacity, const string& service) {

    Node* firstNode = nodes[first];
    Node* secondNode = nodes[second];

    auto* firstEdge = new Edge{firstNode, secondNode, capacity, service, 0};
    auto* secondEdge = new Edge{secondNode, firstNode, capacity, service, 0};

    firstNode->adj.push_back(firstEdge);
    secondNode->adj.push_back(secondEdge);

    firstNode->incoming.push_back(secondEdge);
    secondNode->incoming.push_back(firstEdge);
}

const unordered_map<string, Graph::Node*>& Graph::getNodes() const {
    return nodes;
}

vector<string> Graph::getStationsInDistrict(const string& district) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second->station.getDistrict() == district) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInMunicipality(const string& municipality) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second->station.getMunicipality() == municipality) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInTownship(const string& township) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second->station.getTownship() == township) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

vector<string> Graph::getStationsInLine(const string& line) const {
    vector<string> stations;
    for (auto& node: nodes) {
        if (node.second->station.getLine() == line) {
            stations.push_back(node.first);
        }
    }
    return stations;
}

Graph::Edge* Graph::findEdge(Node* source, Node* destination) {
    for (auto edge : source->adj) {
        if (edge->destination == destination) return edge;
    }
    return nullptr;
}

void Graph::removeEdge(Edge* edge, vector<Edge*>& edges) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if ((*it)->destination->station.getName() == edge->destination->station.getName()) {
            edges.erase(it);
            break;
        }
    }
}

void Graph::removeBidirectionalEdge(Graph::Node* station1, Graph::Node* station2) {

    Edge* edge1 = findEdge(station1, station2);
    Edge* edge2 = findEdge(station2, station1);

    removeEdge(edge1, station1->adj);
    removeEdge(edge1, station2->incoming);
    removeEdge(edge2, station2->adj);
    removeEdge(edge2, station1->incoming);
}

void Graph::setAllNodesUnvisited() {
    for (auto& node : nodes) {
        node.second->visited = false;
    }
}

void Graph::setAllFlows0() {
    for (auto& node : nodes) {
        for (auto edge: node.second->adj) {
            edge->flow = 0;
        }
    }
}

void Graph::dfs(Node* source) {

    source->visited = true;

    for (auto next : source->adj) {
        if (!next->destination->visited) {
            dfs(next->destination);
        }
    }
}


vector<Graph::FlowStations> Graph::getMaxFlowStations() {
    int maxFlow = 0;
    vector<FlowStations> res;

    for (auto& a : nodes) {
        for (auto &b: nodes) {

            if (a.first >= b.first) continue;

            int flow = edmondsKarp(a.second, b.second);

            if (flow < maxFlow) continue;

            if (flow > maxFlow) {
                res.clear();
                maxFlow = flow;
            }

            res.push_back({flow, a.first, b.first});
        }
    }
    return res;
}

vector<Graph::FlowStations> Graph::getAllFlows() {

    vector<FlowStations> res;
    if (nodes.size() == 1) {
        for (auto& a : nodes)
        res.push_back({0, a.first, a.first});
    }

    for (auto& a : nodes) {
        for (auto &b: nodes) {

            if (a.first >= b.first) continue;

            int flow = edmondsKarp(a.second, b.second);
            res.push_back({flow, a.first, b.first});
        }
    }

    sort(res.begin(), res.end(), [](const FlowStations& a, const FlowStations& b) {
        return a.flow > b.flow;
    });

    return res;
}

void Graph::testAndVisit(queue<Node*> &queue, Edge* edge, Node* next, int residual) {
    if (!next->visited && residual > 0) {
        next->visited = true;
        next->path = edge;
        queue.push(next);
    }
}

bool Graph::bfsFindAugmentingPath(Node* source, Node* sink) {
    setAllNodesUnvisited();
    source->visited = true;

    queue<Node*> queue;
    queue.push(source);

    while (!queue.empty() && !sink->visited) {
        Node* node = queue.front();
        queue.pop();
        for (auto edge: node->adj) {
            testAndVisit(queue, edge, edge->destination, edge->capacity - edge->flow);
        }
        for (auto edge: node->incoming) {
            testAndVisit(queue, edge, edge->source, edge->flow);
        }
    }
    return sink->visited;
}

int Graph::findMinResidualAlongPath(Node* source, Node* sink) {
    int flow = INT32_MAX;

    for (auto node = sink; node != source;) {

        auto edge = node->path;

        if (edge->destination == node) {
            flow = min(flow, edge->capacity - edge->flow);
            node = edge->source;
        } else {
            flow = min(flow, edge->flow);
            node = edge->destination;
        }
    }
    return flow;
}

void Graph::augmentFlowAlongPath(Node* source, Node* sink, int f) {

    for (auto next = sink; next != source; ) {

        auto edge = next->path;
        int flow = edge->flow;

        if (edge->destination == next) {
            edge->flow = flow + f;
            next = edge->source;
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
    while (bfsFindAugmentingPath(source, sink)) {
        int flow = findMinResidualAlongPath(source, sink);
        augmentFlowAlongPath(source, sink, flow);
        maxFlow += flow;
    }

    return maxFlow;
}


bool Graph::bfsFindCheapAugmentingPath(Node* source, Node* sink) {
    setAllNodesUnvisited();
    source->visited = true;

    queue<Node*> queue;
    queue.push(source);

    while (!queue.empty() && !sink->visited) {
        Node* node = queue.front();
        queue.pop();
        vector<Edge*> adjHelper = node->adj;
        sort(adjHelper.begin(), adjHelper.end(), [](const Edge* edge1, const Edge* edge2) {
            return edge1->cost < edge2->cost;
        });
        for (auto edge: node->adj) {
            testAndVisit(queue, edge, edge->destination, edge->capacity - edge->flow);
        }
        vector<Edge*> incHelper = node->incoming;
        sort(incHelper.begin(), incHelper.end(), [](const Edge* edge1, const Edge* edge2) {
            return edge1->cost < edge2->cost;
        });
        for (auto edge: node->incoming) {
            testAndVisit(queue, edge, edge->source, edge->flow);
        }
    }
    return sink->visited;
}

void Graph::augmentFlowAlongPathCost(Node* source, Node* sink, int f, int& cost) {

    for (auto next = sink; next != source; ) {

        auto edge = next->path;
        int flow = edge->flow;

        if (edge->destination == next) {
            edge->flow = flow + f;
            next = edge->source;
        }
        else {
            edge->flow = flow - f;
            next = edge->destination;
        }
        cost += edge->cost;
    }
}

pair<int, int> Graph::cheapEdmondsKarp(Node* source, Node* sink) {

    int maxFlow = 0;
    setAllFlows0();
    int cost = 0;
    int totalCost = 0;

    // Loop to find augmentation paths
    while (bfsFindCheapAugmentingPath(source, sink)) {
        int flow = findMinResidualAlongPath(source, sink);
        augmentFlowAlongPathCost(source, sink, flow, cost);
        maxFlow += flow;
        totalCost += (cost * flow);
        cost = 0;
    }

    return {maxFlow, totalCost};
}

int Graph::maxAffluenceAtStation(Node* sink) {
    vector<Node*> sources;
    for (auto& node : nodes) {
        if (node.second->adj.size() == 1 && node.second != sink)
            sources.push_back(node.second);
    }
    addNode("super", " ", "  ", " ", " ");
    auto superNode = nodes["super"];
    for (auto node : sources) {
        addBidirectionalEdge("super", node->station.getName(), INT32_MAX, "STANDARD");
    }

    int affluence = edmondsKarp(superNode, sink);
    for (auto node : sources) {
        node->incoming.pop_back();
        node->adj.pop_back();
    }
    nodes.erase("super");
    return affluence;
}

std::vector<std::pair<int, std::string>> Graph::topMaxAffluenceStations() {

    vector<pair<int, string>> topMaxAffluence(nodes.size());

    for (auto& sink : nodes) {
        topMaxAffluence.emplace_back(maxAffluenceAtStation(sink.second), sink.first);
    }

    sort(topMaxAffluence.begin(), topMaxAffluence.end(), greater<>());
    return topMaxAffluence;
}

bool Graph::compareDijkstra(Node* node1, Node* node2) {
    return node1->distanceDijkstra < node2->distanceDijkstra;
}

int Graph::dijkstra(Graph::Node* source, Graph::Node* target) {

    for (auto& node : nodes) {
        node.second->path = nullptr;
        node.second->distanceDijkstra = INT32_MAX;
    }

    priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> queue(compareDijkstra);
    queue.push(source);
    source->distanceDijkstra = 0;

    while (!queue.empty()) {

        Node* node = queue.top();
        queue.pop();

        for (auto edge: node->adj) {

            int newDistance = node->distanceDijkstra + edge->cost;
            if (newDistance < edge->destination->distanceDijkstra) {
                edge->destination->distanceDijkstra = newDistance;
                edge->destination->path = edge;
                queue.push(edge->destination);
            }
        }
    }
    return target->distanceDijkstra;
}