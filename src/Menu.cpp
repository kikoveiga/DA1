//
// Created by kikoveiga on 14-03-2023.
//

#include <iostream>
#include "Menu.h"

using namespace std;

Menu::Menu() {
    command = "0";
}

void Menu::run() {

    bool running = true;

    while (running) {

        switch(stoi(command)) {

            case 0:
                mainMenu();
                break;

            case 1:
                stationMenu();
                break;

            case 2:
                running = false;
                break;
        }
    }
}

void Menu::mainMenu() {
    command = "1";
    cout << "Running the main menu..." << endl;
}

void Menu::stationMenu() {
    command = "2";
    cout << "Running the station menu..." << endl;
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

