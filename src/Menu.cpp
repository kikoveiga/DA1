//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"

using namespace std;

bool isNumber(const string& s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

string toUpper(string& s) {
    for (auto& c: s) c = toupper(c);
    return s;
}

string capitalizeFirstLetter(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (i == 0 || s[i - 1] == ' ') {
            s[i] = toupper(s[i]);
        }
        else {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Menu::press0ToContinue() {

    while (true) {
        cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
        if (command == "0") break;
    }
}

Menu::Menu() {
    command = "0";
    run();
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
                maxFlowMenu();
                break;

            case 3:
                exit(0);
        }
    }
}

void Menu::printStation(const string& name) {

    auto station = utils.getGraph().getNodes().at(name)->station;

    cout << endl;
    cout << "   -STATION " << name << " FOUND" << endl;
    cout << "      -NAME: " << station.getName() << endl;
    cout << "      -DISTRICT: " << station.getDistrict() << endl;
    cout << "      -MUNICIPALITY: " << station.getMunicipality() << endl;
    cout << "      -TOWNSHIP: " << station.getTownship() << endl;
    cout << "      -LINE: " << station.getLine() << endl;
    cout << endl;
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                   MAIN MENU                   |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. STATIONS MENU                              |\n"
         << "| 2. MAX FLOW MENU                              |\n"
         << "| 3. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= 3) break;
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
         << "| 4. STATIONS FROM MUNICIPALITY                 |\n"
         << "| 5. STATIONS FROM TOWNSHIP                     |\n"
         << "| 6. STATIONS FROM LINE                         |\n"
         << "| 7. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= 7) break;
        else cout << "   -INVALID OPTION" << endl;
    }

    if (command == "1") { // Search Station

        string name;
        while (true) {
            cout << "   -ENTER STATION NAME: "; getline(cin >> ws, name);
            if (utils.getGraph().getNodes().find(name) != utils.getGraph().getNodes().end()) break;
            cout << "   -STATION NOT FOUND" << endl;
        }

        printStation(name);
        press0ToContinue();
    }

    else if (command == "2") { // Number of Stations

        cout << "NUMBER OF STATIONS: " << utils.getGraph().getNodes().size() << endl;
        cout << endl;

        press0ToContinue();
    }

    else if (command == "3") { // Stations from District
        string district;
        while (true) {
            cout << "   -ENTER DISTRICT: "; getline(cin >> ws, district);
            if (!utils.getGraph().getStationsInDistrict(toUpper(district)).empty()) break;
            cout << "   -INVALID DISTRICT" << endl;
        }

        vector<string> stationsInDistrict = utils.getGraph().getStationsInDistrict(district);

        cout << endl;
        cout << "STATIONS FROM DISTRICT " << district << ":\n";

        for (int i = 0; i < stationsInDistrict.size(); i++) {
            cout << "   [" << i + 1 << "] " << stationsInDistrict.at(i) << endl;
        }
        cout << endl;

        while(true) {
            cout << "SELECT A STATION OR PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;

            if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= stationsInDistrict.size()) {
                printStation(stationsInDistrict.at(stoi(command) - 1));
                press0ToContinue();
                break;
            }
            else cout << "   -INVALID OPTION" << endl;
        }
    }

    else if (command == "4") { // Stations from Municipality
        string municipality;
        while (true) {
            cout << "   -ENTER MUNICIPALITY: "; getline(cin >> ws, municipality);
            if (!utils.getGraph().getStationsInMunicipality(toUpper(municipality)).empty()) break;
            cout << "   -INVALID MUNICIPALITY" << endl;
        }

        vector<string> stationsInMunicipality = utils.getGraph().getStationsInMunicipality(municipality);

        cout << endl;
        cout << "STATIONS FROM MUNICIPALITY " << municipality << ":\n";

        for (int i = 0; i < stationsInMunicipality.size(); i++) {
            cout << "   [" << i + 1 << "] " << stationsInMunicipality.at(i) << endl;
        }
        cout << endl;

        while(true) {
            cout << "SELECT A STATION OR PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;

            if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= stationsInMunicipality.size()) {
                printStation(stationsInMunicipality.at(stoi(command) - 1));
                press0ToContinue();
                break;
            }
            else cout << "   -INVALID OPTION" << endl;
        }
    }

    else if (command == "5") { // Stations from Township
        string township;
        while (true) {
            cout << "   -ENTER TOWNSHIP: "; getline(cin >> ws, township);
            if (!utils.getGraph().getStationsInTownship(township).empty()) break;
            cout << "   -INVALID TOWNSHIP" << endl;
        }

        vector<string> stationsInTownship = utils.getGraph().getStationsInTownship(township);

        cout << endl;
        cout << "STATIONS FROM TOWNSHIP " << township << ":\n";

        for (int i = 0; i < stationsInTownship.size(); i++) {
            cout << "   [" << i + 1 << "] " << stationsInTownship.at(i) << endl;
        }
        cout << endl;

        while(true) {
            cout << "SELECT A STATION OR PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;

            if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= stationsInTownship.size() ) {
                printStation(stationsInTownship.at(stoi(command) - 1));
                press0ToContinue();
                break;
            }
            else cout << "   -INVALID OPTION" << endl;
        }
    }

    else if (command == "6") { // Stations from Line
        string line;
        while (true) {
            cout << "   -ENTER LINE: "; getline(cin >> ws, line);
            if (!utils.getGraph().getStationsInLine(line).empty()) break;
            cout << "   -INVALID LINE" << endl;
        }

        vector<string> stationsInLine = utils.getGraph().getStationsInLine(line);

        cout << endl;
        cout << "STATIONS FROM LINE " << line << ":\n";

        for (int i = 0; i < stationsInLine.size(); i++) {
            cout << "   [" << i + 1 << "] " << stationsInLine.at(i) << endl;
        }
        cout << endl;

        while(true) {
            cout << "SELECT A STATION OR PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
            if (command == "0") break;

            if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= stationsInLine.size()) {
                printStation(stationsInLine.at(stoi(command) - 1));
                press0ToContinue();
                break;
            }
            else cout << "   -INVALID OPTION" << endl;
        }
    }

    else if (command == "7") { // Go Back
        command = "0";
        return;
    }

    command = "1";
}

void Menu::maxFlowMenu() {

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|                 MAX FLOW MENU                 |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. MAX FLOW BETWEEN 2 STATIONS                |\n"
         << "| 2. TOP N DISTRICTS IN FLOW                    |\n"
         << "| 3. TOP N MUNICIPALITIES IN FLOW               |\n"
         << "| 4. TOP N MAX FLOWS                            |\n"
         << "| 5. MIN COST                                   |\n"
         << "| 6. GO BACK                                    |\n"
         << "-------------------------------------------------\n";
    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= 5) break;
        else cout << "   -INVALID OPTION" << endl;
    }

    if (command == "1") { // Max Flow Between 2 Stations
        string station1, station2;
        while (true) {
            cout << "   -ENTER STATION 1: "; getline(cin >> ws, station1);
            if (utils.getGraph().getNodes().find(station1) != utils.getGraph().getNodes().end()) break;
            cout << "   -INVALID STATION" << endl;
        }
        while (true) {
            cout << "   -ENTER STATION 2: "; getline(cin >> ws, station2);
            if (utils.getGraph().getNodes().find(station2) != utils.getGraph().getNodes().end()) break;
            cout << "   -INVALID STATION" << endl;
        }

        cout << endl;
        cout << "MAX FLOW BETWEEN " << station1 << " AND " << station2 << ":\n";
        cout << "   -MAX FLOW: " << utils.getGraph().edmondsKarp(utils.getGraph().getNodes().at(station1), utils.getGraph().getNodes().at(station2)) << endl;
        cout << endl;

        press0ToContinue();

    }

    else if (command == "2") { // Top Districts

        while (true) {
            cout << "   -ENTER N: "; getline(cin >> ws, command);
            if (isNumber(command) && stoi(command) > 0) break;
            cout << "   -INVALID N" << endl;
        }

        cout << endl;
        cout << "TOP " << command << " DISTRICT(S) IN FLOW:\n";

        vector<pair<int, string>> topDistricts;
        set<std::string> districts = utils.getDistricts();

        for (auto& district : districts) {

            Utils tempUtils(true, district);
            auto maxFlowStations = tempUtils.getGraph().getMaxFlowStations();

            if (!maxFlowStations.empty()) topDistricts.emplace_back(maxFlowStations[0].flow, district);
        }

        sort(topDistricts.begin(), topDistricts.end(), greater<>());
        for (int i = 0; i < stoi(command) & i < topDistricts.size(); i++) {
            cout << "   [" << i + 1 << "] " << topDistricts[i].second << " - " << topDistricts[i].first << endl;
        }

        press0ToContinue();
    }

    else if (command == "3") { // Top Municipalities

        while (true) {
            cout << "   -ENTER N: ";
            getline(cin >> ws, command);
            if (isNumber(command) && stoi(command) > 0) break;
            cout << "   -INVALID N" << endl;
        }

        cout << endl;
        cout << "TOP " << command << " MUNICIPALITIES IN FLOW:\n";

        vector<pair<int, string>> topMunicipalities;
        set<std::string> municipalities = utils.getMunicipalities();

        for (auto &municipality: municipalities) {

            Utils tempUtils(false, municipality);
            auto maxFlowStations = tempUtils.getGraph().getMaxFlowStations();

            if (!maxFlowStations.empty()) topMunicipalities.emplace_back(tempUtils.getGraph().getMaxFlowStations()[0].flow, municipality);
        }

        sort(topMunicipalities.begin(), topMunicipalities.end(), greater<>());
        for (int i = 0; i < stoi(command) & i < topMunicipalities.size(); i++) {
            cout << "   [" << i + 1 << "] " << topMunicipalities[i].second << " - " << topMunicipalities[i].first
                 << endl;
        }

        press0ToContinue();
    }

    else if (command == "4") { // Top N Max Flows

        while (true) {
            cout << "   -ENTER N: ";
            getline(cin >> ws, command);
            if (isNumber(command) && stoi(command) > 0) break;
            cout << "   -INVALID N" << endl;
        }

        auto result = utils.getGraph().getAllFlows();

        for (int i = 0; i < stoi(command) && i < result.size(); i++) {
            cout << "   [" << i + 1 << "] " << result[i].source << " -> " << result[i].destination << " - " << result[i].flow << endl;
        }

        press0ToContinue();
    }

    else if (command == "5") {
        string station1, station2;
        while (true) {
            cout << "   -ENTER STATION 1: "; getline(cin >> ws, station1);
            if (utils.getGraph().getNodes().find(station1) != utils.getGraph().getNodes().end()) break;
            cout << "   -INVALID STATION" << endl;
        }
        while (true) {
            cout << "   -ENTER STATION 2: "; getline(cin >> ws, station2);
            if (utils.getGraph().getNodes().find(station2) != utils.getGraph().getNodes().end()) break;
            cout << "   -INVALID STATION" << endl;
        }

        auto result = utils.getGraph().cheapEdmondsKarp(utils.getGraph().findNode(station1), utils.getGraph().findNode(station2));

        cout << "number of trains: " << result.first << "  -> total cost:" << result.second << endl;

    }

    else if (command == "6") { // Go Back
            command = "0";
            return;
    }

    command = "2";
}


