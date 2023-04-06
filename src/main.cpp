//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {

    Utils utils;

    auto todos = utils.getGraph().getAllFlows();
    cout << utils.getGraph().getNodes().size() << endl;
    cout << todos.size() << endl;
    /*for (auto& flow: todos) {
        cout << flow.flow << " " << flow.source << "->" << flow.destination << endl;
    }*/
}

int main() {

    //func_test();

    Menu menu;
}