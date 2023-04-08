//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_UTILS_H
#define DA1_UTILS_H

#include <sstream>
#include <fstream>
#include <set>

#include "Graph.h"

class Utils {

private:
    Graph graph;
    std::set<std::string> districts;
    std::set<std::string> municipalities;
    std::set<std::pair<std::string, std::string>> edges;

public:
    explicit Utils(bool distOrMun = true, const std::string& distMun = "");
    Graph getGraph();
    std::set<std::string> getDistricts();
    std::set<std::string> getMunicipalities();
    std::set<std::pair<std::string, std::string>> getEdges();
    void readStations(bool distOrMun, const std::string& distMun);
    void readNetwork(const std::string& distMun);
    void removeEdge(const std::pair<std::string, std::string>& edge);
};

#endif //DA1_UTILS_H
