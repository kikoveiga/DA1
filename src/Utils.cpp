//
// Created by kikoveiga on 14-03-2023.
//

#include "Utils.h"

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
    string l;
    getline(file, l);
    while (getline(file, l)) {
        stringstream ss(l);
        string name, district, municipality, township, line;
        getline(ss, name, ',');
        getline(ss, district, ',');
        getline(ss, municipality, ',');
        getline(ss, township, ',');
        getline(ss, line, '\r');

        Station station = Station(name, district, municipality, township, line);
        graph.addStation(station);
    }
}

void Utils::readNetwork() {

    ifstream file("../dataset/network.csv");
    string l;
    getline(file, l);
    while (getline(file, l)) {
        stringstream ss(l);
        string source, destination, capacity, service;
        getline(ss, source, ',');
        getline(ss, destination, ',');
        getline(ss, capacity, ',');
        getline(ss, service, '\r');

        graph.addEdge(source, destination, stoi(capacity), service);
    }
}
