//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {

    Utils utils;
    Graph graph = utils.getGraph();

    auto origem = graph.findNode("Porto Campanhã");
    auto destino = graph.findNode("Lisboa Oriente");


    cout << graph.dijkstra(origem, destino) << endl;

    auto origem1 = destino;

    while (true) {
        cout << origem1->station.getName() << " -> ";
        origem1 = origem1->path->source;
        if (origem1 == origem) {
            cout << origem1->station.getName();
            break;
        }
     }

    cout << endl;

    cout << graph.dijkstra(destino, origem) << endl;

    auto origem2 = origem;
    while (true) {

        cout << origem2->station.getName() << " -> ";
        origem2 = origem2->path->source;
        if (origem2 == destino) {
            cout << destino->station.getName();
            break;
        }

    }
    cout << endl;
}

int main() {

    //func_test();
    Menu menu;
}

