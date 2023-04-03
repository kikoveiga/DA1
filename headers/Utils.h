//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_UTILS_H
#define DA1_UTILS_H

#include <sstream>
#include <fstream>

#include "Graph.h"

class Utils {

private:
    Graph graph;

public:
    explicit Utils();
    Graph getGraph();
    void readStations();
    void readNetwork();
};

#endif //DA1_UTILS_H
