//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {

    Utils utils(true, "LISBOA");

    auto i = utils.getGraph().getMaxFlowStations();
    cout << i.first << endl;

    for (auto& j : i.second) {
        cout << j.first << " -> " << j.second << endl;
    }
}

int main() {

    //func_test();

    Menu menu;
}