//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_MENU_H
#define DA1_MENU_H

#include "Utils.h"
#include <iostream>
#include <algorithm>

class Menu {

private:
    Utils utils;
    std::string command;
    std::vector<std::pair<std::string, std::string>> edges;
public:
    explicit Menu();
    void run();
    void press0ToContinue();
    void printStation(const std::string& name);
    void mainMenu();
    void stationsMenu();
    void maxFlowMenu();
    void reducedConMenu();
    static void cleanTerminal();
    void changeEdges();
};

#endif //DA1_MENU_H
