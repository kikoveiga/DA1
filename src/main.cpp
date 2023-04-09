//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {

    Utils utils;
    Graph graph = utils.getGraph();

    auto origem = graph.findNode("Lisboa Oriente");
    auto destino = graph.findNode("Porto Campanhã");


    cout << graph.dijkstra(origem, destino) << endl;

    while (destino != origem) {
        cout << destino->station.getName() << " -> " << destino->path->source->station.getName() << endl;
        destino = destino->path->source;
    }
}

int main() {

    //func_test();
    Menu menu;
}

