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
    /**
     * @brief Utils constructor
     * @param distOrMun boolean to decide which type of geographical place to parse from the csv to the graph
     * @param distMun  string with the name of the district or the municipality (to get all stations parsed leave empty)
     */
    explicit Utils(bool distOrMun = true, const std::string& distMun = "");

    /**
     * @brief Get function for the graph private field
     * @return graph
     */
    Graph getGraph();

    /**
     * @brief Get function to get the districts field
     * @return districts set<string>
     */
    std::set<std::string> getDistricts();

    /**
     * @brief Get function to get the Municipalities field
     * @return municipalities set<string>
     */
    std::set<std::string> getMunicipalities();

    /**
     * @brief function to parse the information from the csv into graph nodes
     * @brief also updates the districts and municipalites sets
     * @param distOrMun boolean to decide which type of geographical place to parse from the csv to the graph
     * @param distMun (string with the name of the district or the municipality (to get all stations parsed leave empty)
     */
    void readStations(bool distOrMun, const std::string& distMun);

    /**
     * @brief function to parse the information from the csv into graph edges
     * @param distMun string to choose what municipality or district to parse (leave empty to choose all)
     */
    void readNetwork(const std::string& distMun);
};

#endif //DA1_UTILS_H
