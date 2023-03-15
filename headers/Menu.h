//
// Created by kikoveiga on 14-03-2023.
//

#ifndef DA1_MENU_H
#define DA1_MENU_H

#include "Utils.h"

class Menu {

private:
    Utils utils;
    std::string command;

public:
    explicit Menu();
    void run();
    void mainMenu();
    void stationMenu();
    void cleanTerminal();

};

#endif //DA1_MENU_H
