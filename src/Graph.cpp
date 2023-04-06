//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Graph.h"

using namespace std;

Graph::Graph() = default;

void Graph::addNode(Node* node) {
    nodes[node->station.getName()] = node;
}

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

void Graph::removeEdge(Graph::Node *station1, Graph::Node *station2) {
    Edge* edgeToRemove = nullptr;
    for (auto it = station1->adj.begin(); it != station1->adj.end(); ++it) {
        if ((*it)->destination->station.getName() == station2->station.getName()) {
            edgeToRemove = *it;
            station1->adj.erase(it);
            break;
        }
    }
    for (auto it = station1->incoming.begin(); it != station1->incoming.end(); ++it) {
        if ((*it)->source->station.getName() == station2->station.getName()) {
            edgeToRemove = *it;
            station1->incoming.erase(it);
            break;
        }
    }
    for (auto it = station2->adj.begin(); it != station2->adj.end(); ++it) {
        if ((*it)->destination->station.getName() == station1->station.getName()) {
            edgeToRemove = *it;
            station2->adj.erase(it);
            break;
        }
    }
    for (auto it = station2->incoming.begin(); it != station2->incoming.end(); ++it) {
        if ((*it)->source->station.getName() == station1->station.getName()) {
            edgeToRemove = *it;
            station1->incoming.erase(it);
            break;
        }
    }
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

void Graph::dfs(Node* node) {

    node->visited = true;

    for (auto next : node->adj) {
        if (!next->destination->visited) {
            dfs(next->destination);
        }
    }
}


std::vector<Graph::FlowStations> Graph::getMaxFlowStations() {
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

std::vector<Graph::FlowStations> Graph::getAllFlows() {

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
            flow = std::min(flow, edge->capacity - edge->flow);
            node = edge->source;
        }

        else {
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
    int lastFlow;
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

int Graph::maxAffluence(Node* sink) {
    vector<Node*> sources;
    for (auto& node : nodes) {
        if (node.second->adj.size() == 1)
            sources.push_back(node.second);
    }
    addNode("super", " ", "  ", " ", " ");
    auto superNode = nodes["super"];
    for (auto& node : sources) {
        addBidirectionalEdge("super", node->station.getName(), INT32_MAX, "STANDARD");
    }
    int affluence = edmondsKarp(superNode, sink);
    for (auto& node : sources) {
        node->incoming.pop_back();
        node->adj.pop_back();
    }
    return affluence;
}


