//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {
    Utils utils;
    /*std::vector<std::pair<std::pair<std::string, std::string>, int>> test = utils.getGraph().getMaxFlowStations();
    for (std::pair<std::pair<std::string, std::string>, int> help : test)
        std::cout << help.first.first << " -> " << help.first.second << " : max = " << help.second << std::endl;*/

    auto source = utils.getGraph().getNodes().at("Santarém");
    auto sink = utils.getGraph().getNodes().at("Lisboa Oriente");

    //cout << utils.getGraph().edmondsKarp(source, sink);


}

int main() {

    func_test();

    //Menu menu;
}