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

public:
    explicit Utils();
    Graph getGraph();
    std::set<std::string> getDistricts();
    std::set<std::string> getMunicipalities();
    void readStations();
    void readNetwork();
    Graph filterGraph(bool distOrMun, const std::string& distMun) const;
};

#endif //DA1_UTILS_H
