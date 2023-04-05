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

public:
    explicit Menu();
    void run();
    void press0ToContinue();
    void printStation(const std::string& name);
    void mainMenu();
    void stationsMenu();
    void maxFlowMenu();
    void cleanTerminal();

};

#endif //DA1_MENU_H
