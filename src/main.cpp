//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {
    Utils utils(true, "AVEIRO");
    auto nigga = utils.getGraph().getNodes();
    cout << nigga.size();

    for (auto node : nigga) {
        cout << node.second->station.getName() << ", ";
    }


}

int main() {

    func_test();

    //Menu menu;
}