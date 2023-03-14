//
// Created by kikoveiga on 14-03-2023.
//

#include "Utils.h"
#include <iostream>

using namespace std;

int main() {

    Utils utils = Utils();
    Graph grafo = utils.getGraph();
    unordered_map<string, Station> stations = grafo.getStations();

    for (auto station : stations) {
        cout << station.second.getName() << ' ' << station.second.getDistrict() << ' ' << station.second.getMunicipality() << ' ' << station.second.getTownship() << ' ' << station.second.getLine() << endl;
    }

    cout << '\n';

    cout << "There are " << stations.size() << " stations in the graph." << endl;
}