//
// Created by kikoveiga on 14-03-2023.
//

#include "Utils.h"
#include <iostream>

using namespace std;

int main() {

    Utils utils = Utils();
    Graph grafo = utils.getGraph();
    vector<Station> stations = grafo.getStations();

    for (Station station : stations) {
        cout << station.getName() << ' ' << station.getDistrict() << ' ' << station.getMunicipality() << ' ' << station.getTownship() << ' ' << station.getLine() << endl;
    }

    cout << '\n';

    cout << "There are " << stations.size() << " stations in the graph." << endl;
}