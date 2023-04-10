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

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Menu::press0ToContinue() {

    while (true) {
        cout << "PRESS 0 TO CONTINUE: "; getline(cin >> ws, command);
        if (command == "0") break;
    }
}

void Menu::enterOption(int n) {

    while (true) {
        cout << "   -OPTION: "; getline(cin >> ws, command);
        if (isNumber(command) && 1 <= stoi(command) && stoi(command) <= n) break;
        else cout << "   -INVALID OPTION" << endl;
    }
}

void Menu::enterN() {

    while (true) {
        cout << "   -ENTER N: "; getline(cin >> ws, command);
        if (isNumber(command) && stoi(command) > 0) break;
        cout << "   -INVALID N" << endl;
    }
}

string Menu::enterStation(int n) {

    string station;

    while (true) {
        cout << "   -ENTER STATION";

        if (n) {cout << ' ' << n << ": "; getline(cin >> ws, station);}
        else {cout << ": ", getline(cin >> ws, command);}

        if (utils.getGraph().findNode(n ? station : command) != nullptr) break;
        cout << "   -INVALID STATION" << endl;
    }
    return station;
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
                reducedConMenu();
                break;
            case 4:
                exit(0);

        }
    }
}

void Menu::printStation(const string& name) {

    auto station = utils.getGraph().findNode(name)->station;

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
         << "| 3. REDUCED CONNECTIVITY MENU                  |\n"
         << "| 4. EXIT                                       |\n"
         << "-------------------------------------------------\n";

    enterOption(4);
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

    enterOption(7);

    if (command == "1") { // Search Station

        enterStation(0);
        printStation(command);
        press0ToContinue();
    }

    else if (command == "2") { // Number of Stations

        cout << "   -NUMBER OF STATIONS: " << utils.getGraph().getNodes().size() << endl;
        cout << endl;

        press0ToContinue();
    }

    else if (command == "3") { // Stations from District

        while (true) {
            cout << "   -ENTER DISTRICT: "; getline(cin >> ws, command);
            if (!utils.getGraph().getStationsInDistrict(toUpper(command)).empty()) break;
            cout << "   -INVALID DISTRICT" << endl;
        }

        vector<string> stationsInDistrict = utils.getGraph().getStationsInDistrict(command);

        cout << endl;
        cout << "STATIONS FROM DISTRICT " << command << ":\n";

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

        while (true) {
            cout << "   -ENTER MUNICIPALITY: "; getline(cin >> ws, command);
            if (!utils.getGraph().getStationsInMunicipality(toUpper(command)).empty()) break;
            cout << "   -INVALID MUNICIPALITY" << endl;
        }

        vector<string> stationsInMunicipality = utils.getGraph().getStationsInMunicipality(command);

        cout << endl;
        cout << "STATIONS FROM MUNICIPALITY " << command << ":\n";

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

        while (true) {
            cout << "   -ENTER TOWNSHIP: "; getline(cin >> ws, command);
            if (!utils.getGraph().getStationsInTownship(command).empty()) break;
            cout << "   -INVALID TOWNSHIP" << endl;
        }

        vector<string> stationsInTownship = utils.getGraph().getStationsInTownship(command);

        cout << endl;
        cout << "STATIONS FROM TOWNSHIP " << command << ":\n";

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

        while (true) {
            cout << "   -ENTER LINE: "; getline(cin >> ws, command);
            if (!utils.getGraph().getStationsInLine(command).empty()) break;
            cout << "   -INVALID LINE" << endl;
        }

        vector<string> stationsInLine = utils.getGraph().getStationsInLine(command);

        cout << endl;
        cout << "STATIONS FROM LINE " << command << ":\n";

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
         << "| 5. MAX AFFLUENCE AT STATION                   |\n"
         << "| 6. TOP N MAX AFFLUENCE STATIONS               |\n"
         << "| 7. DIJKSTRA BETWEEN 2 STATIONS                |\n"
         << "| 8. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(8);

    if (command == "1") { // Max Flow Between 2 Stations

        string station1 = enterStation(1);
        string station2 = enterStation(2);

        cout << endl;
        cout << "MAX FLOW BETWEEN " << station1 << " AND " << station2 << ": "
        << utils.getGraph().edmondsKarp(utils.getGraph().findNode(station1), utils.getGraph().findNode(station2)) << endl;
        cout << endl;

        press0ToContinue();

    }

    else if (command == "2") { // Top N Districts In Flow

        enterN();

        cout << endl;
        cout << "TOP " << stoi(command) << " DISTRICT(S) IN FLOW:\n";

        vector<pair<int, string>> topDistricts;
        set<string> districts = utils.getDistricts();

        for (auto& district : districts) {

            Utils tempUtils(true, district);
            auto maxFlowStations = tempUtils.getGraph().getMaxFlowStations();

            if (!maxFlowStations.empty()) topDistricts.emplace_back(maxFlowStations[0].flow, district);
        }

        sort(topDistricts.begin(), topDistricts.end(), greater<>());
        for (int i = 0; i < stoi(command) & i < topDistricts.size(); i++) {
            cout << "   [" << i + 1 << "] " << topDistricts[i].second << " - " << topDistricts[i].first << endl;
        }

        cout << endl;
        press0ToContinue();
    }

    else if (command == "3") { // Top N Municipalities In Flow

        enterN();

        cout << endl;
        cout << "TOP " << stoi(command) << " MUNICIPALITIES IN FLOW:\n";

        vector<pair<int, string>> topMunicipalities;
        set<string> municipalities = utils.getMunicipalities();

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

        cout << endl;
        press0ToContinue();
    }

    else if (command == "4") { // Top N Max Flows

        enterN();

        auto result = utils.getGraph().getAllFlows();

        cout << endl;
        cout << "TOP " << min(stoi(command), (int) result.size()) << " MAX FLOWS: " << endl;

        for (int i = 0; i < stoi(command) && i < result.size(); i++) {
            cout << "   [" << i + 1 << "] " << result[i].source << " <-> " << result[i].destination << " - " << result[i].flow << endl;
        }

        cout << endl;
        press0ToContinue();
    }

    else if (command == "5") { // Max Affluence At Station

        enterStation(0);

        auto result = utils.getGraph().maxAffluenceAtStation(utils.getGraph().findNode(command));
        cout << endl << "Max Affluence at " << command << ": " << result << endl;
        cout << endl;
        press0ToContinue();
    }

    else if (command == "6") { // Top N Max Affluence Stations

        enterN();
        vector<pair<int, string>> topStations = utils.getGraph().topMaxAffluenceStations();

        cout << endl << "TOP " << min(stoi(command), (int) utils.getGraph().getNodes().size()) << " MAX AFFLUENCE STATIONS: \n";

        for (int i = 0; i < utils.getGraph().getNodes().size() && i < stoi(command); i++) {

            cout << "   [" << i + 1 << "] " << topStations[i].second << " - " << topStations[i].first << endl;
        }

        cout << endl;
        press0ToContinue();

    }

    else if (command == "7") { // Dijkstra Between 2 Stations

        auto station1 = utils.getGraph().findNode(enterStation(1));
        auto station2 = utils.getGraph().findNode(enterStation(2));

        int result = utils.getGraph().dijkstra(station1, station2);

        if (result == INT32_MAX) cout << endl << "THERE IS NO AVAILABLE PATH FROM " << station1->station.getName() << " TO " << station2->station.getName() << endl << endl;

        else {

            vector<string> path;
            auto destination = station2;
            int capacity = INT32_MAX;

            while (true) {
                path.push_back(destination->station.getName());
                if (destination == station1) break;
                capacity = min(capacity, destination->path->capacity);
                destination = destination->path->source;
            }

            cout << endl;
            cout << "-CHEAPEST PATH BETWEEN " << station1->station.getName() << " AND " << station2->station.getName() << ": " << endl;
            cout << "   -COST: " << result << endl;
            cout << "   -CAPACITY: " << capacity << endl;
            cout << "   -PATH: ";

            for (auto it = path.rbegin(); it != path.rend(); it++) {
                cout << (*it) << " -> ";
            }
            cout << "\b\b\b\b" << "   " << endl;
            cout << endl;
        }

        press0ToContinue();
    }

    else if (command == "8") { // Go Back
            command = "0";
            return;
    }

    command = "2";
}

void Menu::reducedConMenu() {

    Utils tempUtils;
    Graph tempGraph = tempUtils.getGraph();

    if (bidirectionalEdges.empty()) {
        cleanTerminal();
        changeEdges();
        return;
    }

    for (auto& i : bidirectionalEdges) {
        tempGraph.removeBidirectionalEdge(tempGraph.findNode(i.first), tempGraph.findNode(i.second));
    }

    cleanTerminal();
    cout << "-------------------------------------------------\n"
         << "|          REDUCED CONNECTIVITY MENU            |\n"
         << "|-----------------------------------------------|\n"
         << "| 1. MAX FLOW BETWEEN 2 STATIONS                |\n"
         << "| 2. TOP N MOST AFFECTED STATIONS               |\n"
         << "| 3. LIST FAILING SEGMENTS                      |\n"
         << "| 4. CHANGE FAILING SEGMENTS                    |\n"
         << "| 5. GO BACK                                    |\n"
         << "-------------------------------------------------\n";

    enterOption(5);

    if (command == "1") { // Max Flow Between 2 Stations

        string station1 = enterStation(1);
        string station2 = enterStation(2);

        int before = utils.getGraph().edmondsKarp(utils.getGraph().findNode(station1), utils.getGraph().findNode(station2));
        int after = tempGraph.edmondsKarp(tempGraph.findNode(station1), tempGraph.findNode(station2));
        cout << endl;
        cout << "MAX FLOW BETWEEN " << command << " AND " << station2 << ":\n";
        cout << "   -MAX FLOW: " << before << " -> " << after << endl;
        cout << "   -Difference: " << before - after << endl;
        cout << endl;

        press0ToContinue();

    }

    else if (command == "2") { // Most Affected Stations

        vector<pair<string, pair<int, int>>> affluences;

        for (auto& node : tempGraph.getNodes()) {

            int beforeAffluence = utils.getGraph().maxAffluenceAtStation(utils.getGraph().findNode(node.first));
            int afterAffluence = tempGraph.maxAffluenceAtStation(node.second);
            affluences.push_back({node.first,{beforeAffluence, afterAffluence}});
        }

        sort(affluences.begin(), affluences.end(), [] (const pair<string, pair<int, int>>& pair1, pair<string, pair<int, int>>& pair2)
            {return pair1.second.first - pair1.second.second > pair2.second.first - pair2.second.second;});

        enterN();
        cout << endl << "TOP " << min(stoi(command), (int) affluences.size()) << " MOST AFFECTED STATIONS IN AFFLUENCE: " << endl;

        for (int i = 0; i < affluences.size() && i < stoi(command); i++) {

            if (affluences[i].second.second == affluences[i].second.first)
                break;

            cout << "   [" << i + 1 << "] " << affluences[i].first << ": " << affluences[i].second.first << " -> " << affluences[i].second.second << endl;
        }

        cout << endl;
        press0ToContinue();
    }

    else if (command == "3") { // List Failing Segments

        cout << endl << "FAILING SEGMENTS: " << endl;
        int i = 0;
        for (auto& edge : bidirectionalEdges)
            cout << "   [" << i++ + 1 << "] " << edge.first << " <-> " << edge.second << endl;

        cout << endl;
        press0ToContinue();
    }

    else if (command == "4") {
        changeEdges();
    }

    else if (command == "5") { // Go Back
            command = "0";
            return;
    }

    command = "3";
}

void Menu::changeEdges() {
    bidirectionalEdges.erase(bidirectionalEdges.begin(), bidirectionalEdges.end());
    string flag = "1";

    while (flag == "1") {
        cout << "\n\n Choose a pair of adjacent stations to remove an edge." << endl;

        string station1 = enterStation(1);
        string station2 = enterStation(2);

        if (utils.getGraph().findEdge(utils.getGraph().findNode(station1), utils.getGraph().findNode(station2)) == nullptr)
            cout << "   -NON EXISTENT EDGE\n\n";

        else {
            command < station2 ? bidirectionalEdges.emplace_back(station1, station2) : bidirectionalEdges.emplace_back(station2, station1);
            cout << "   -BIDIRECTIONAL EDGE REMOVED!" << endl << endl;
        }

        cout << "PRESS 0 TO CONTINUE OR 1 TO REMOVE MORE EDGES: "; getline(cin >> ws, flag);
    }
    reducedConMenu();
}
