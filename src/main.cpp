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
    auto source = utils.getGraph().getNodes().at("Porto Campanhã");
    auto sink = utils.getGraph().getNodes().at("Lisboa Oriente");

    int help = utils.getGraph().edmondsKarp(&source, &sink);
    cout << help << " flow"<< endl;
}

int main() {

    func_test();

    //Menu menu;
    //menu.run();
}