//
// Created by kikoveiga on 14-03-2023.
//

#include "Menu.h"
#include <iostream>

using namespace std;

int main() {

    Utils utils = Utils();
    Graph grafo = utils.getGraph();
    unordered_map<string, Station> stations = grafo.getStations();
    auto nodes = grafo.getNodes();

    /*for (auto station : stations) {
        cout << station.second.getName() << ' ' << station.second.getDistrict() << ' ' << station.second.getMunicipality() << ' ' << station.second.getTownship() << ' ' << station.second.getLine() << endl;
    }

    cout << '\n';

    cout << "There are " << stations.size() << " stations in the graph." << endl;*/

    int resposta = 0;
    for (auto i : nodes) {
        cout << i.first << endl;
        for (auto j : i.second.adj) {
            resposta++;
            cout << j.destination << ' ' << j.capacity << ' ' << j.service << endl;
        }
        cout << endl;
    }

    cout << resposta << endl;

    Menu menu;
    menu.run();
}