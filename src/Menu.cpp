//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"

using namespace std;

bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

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
                stationsMenu();
                break;

            case 2:
                exit(0);
        }
    }
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                   MAIN MENU                   |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. STATIONS MENU                              |\n"
         << "| 2. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= 2) break;
        else cout << "   -INVALID OPTION" << endl;
    }
}

void Menu::stationsMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 STATIONS MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. SEARCH STATION                             |\n"
         << "| 2. NUMBER OF STATIONS                         |\n"
         << "| 3. STATIONS FROM DISTRICT                     |\n"
         << "| 4. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= 4) break;
        else cout << "   -INVALID OPTION" << endl;
    }

    if (command == "1") { // Search Station

        string name;
        while (true) {
            cout << "   -ENTER STATION NAME: "; getline(cin >> ws, name);
            if (utils.getGraph().getNodes().find(name) != utils.getGraph().getNodes().end()) break;
            else cout << "   -STATION NOT FOUND" << endl;
        }

        auto station = utils.getGraph().getNodes().at(name).source;

        cout << "   -STATION " << name << " FOUND" << endl;
        cout << "   -STATION NAME: " << station->getName() << endl;
        cout << "   -STATION DISTRICT: " << station->getDistrict() << endl;
        cout << "   -STATION MUNICIPALITY: " << station->getMunicipality() << endl;
        cout << "   -STATION TOWNSHIP: " << station->getTownship() << endl;
        cout << "   -STATION LINE: " << station->getLine() << endl;
        cout << endl;

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;
        }

    }

    else if (command == "2") { // Number of Stations

        cout << "NUMBER OF STATIONS: " << utils.getGraph().getNodes().size() << endl;

        cout << endl;

        while (true) {
            cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;
        }
    }

    else if (command == "3") { // Stations from District
        string district;
        while (true) {
            cout << "   -ENTER DISTRICT: "; getline(cin >> ws, district);
            if (!utils.getGraph().getStationsInDistrict(district).empty()) break;
            cout << "   -INVALID DISTRICT" << endl;
        }
        list<string> stationsInDistrict = utils.getGraph().getStationsInDistrict(district);

        cout << "STATIONS FROM DISTRICT " << district << ":\n";

        int i = 1;
        for (auto& station : stationsInDistrict) {
            cout << "   [" << i << "] " << station << ", " << utils.getGraph().getNodes().at(station).source->getLine() << endl;
            i++;
        }
        cout << endl;

        while(true) {
            cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;
        }
    }

    else if (command == "4") { // Go Back
        command = "0";
        return;
    }

    command = "1";
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

