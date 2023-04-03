//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {
    Utils utils;
    /*std::vector<std::pair<std::pair<std::string, std::string>, unsigned>> test = utils.getGraph().getMaxFlowStations();
    for (std::pair<std::pair<std::string, std::string>, unsigned> help : test) {
        std::cout << help.first.first << " -> " << help.first.second << " : max = " << help.second << std::endl;*/
    }
    std::cout << "Lisboa Oriente -> " << "Lisboa Santa Apolónia : max = " << utils.getGraph().edmondsKarp("Funcheira", "Santa Clara-Sabóia");
}

int main() {
    func_test();

    /*Menu menu;
    menu.run();
}*/
}