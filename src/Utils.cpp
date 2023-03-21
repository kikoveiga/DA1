//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Utils.h"

using namespace std;

Utils::Utils() {
    readStations();
    readNetwork();
}

const Graph& Utils::getGraph() const {
    return graph;
}

void Utils::readStations() {

    ifstream file("../dataset/stations.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;

        for (int i = 0; i <= 4; i++) {

            if (ss.peek() == '"') {
                ss.ignore();
                getline(ss, field, '"');
                ss.ignore();
            }
            else if (i == 4) getline(ss, field, '\r');
            else getline(ss, field, ',');

            fields.push_back(field);
        }

        graph.addNode(fields[0], fields[1], fields[2], fields[3], fields[4]);
    }
}

void Utils::readNetwork() {

    ifstream file("../dataset/network.csv");
    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;

        for (int i = 0; i <= 3; i++) {

            if (ss.peek() == '"') {
                ss.ignore();
                getline(ss, field, '"');
                ss.ignore();
            }
            else if (i == 3) getline(ss, field, '\r');
            else getline(ss, field, ',');

            fields.push_back(field);
        }
        graph.addBidirectionalEdge(fields[0], fields[1], stoi(fields[2]), fields[3]);
    }
}
