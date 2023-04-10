//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Utils.h"

using namespace std;

Utils::Utils(bool distOrMun, const string& distMun) {
    readStations(distOrMun, distMun);
    readNetwork(distMun);
}

Graph Utils::getGraph() {
    return graph;
}

set<string> Utils::getDistricts() {
    return districts;
}
set<string> Utils::getMunicipalities() {
    return municipalities;
}

void Utils::readStations(bool distOrMun, const string& distMun) {

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
        if (fields[1].empty() && fields[2].empty()) continue;


        if (distMun.empty() || (distOrMun && distMun == fields[1]) || (!distOrMun && distMun == fields[2])) {
            graph.addNode(fields[0], fields[1], fields[2], fields[3], fields[4]);
            districts.insert(fields[1]);
            municipalities.insert(fields[2]);
        }
    }
}

void Utils::readNetwork(const string& distMun) {

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
                } else if (i == 3) getline(ss, field, '\r');

                else getline(ss, field, ',');

                fields.push_back(field);
            }

            if (distMun.empty() || (graph.findNode(fields[0]) != nullptr && graph.findNode(fields[1]) != nullptr)) {
                graph.addBidirectionalEdge(fields[0], fields[1], stoi(fields[2]), fields[3]);
            }
            edges.insert({fields[0], fields[1]});
        }
}
