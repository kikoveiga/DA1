//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Menu.h"
#include <iostream>

using namespace std;

void  func_test() {

    Utils utils;
    vector<std::pair<std::string, int>> res;
    for (auto& helper : utils.getDistricts()) {
        Utils tempUtils(true, helper);
        std::vector<Graph::FlowStations> districtFlows = tempUtils.getGraph().getAllFlows();
        res.push_back({helper, districtFlows[0].flow});
    }
    sort(res.begin(), res.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    for (auto a : res)
        cout << a.first << "->" << a.second << endl;
    /*auto todos = utils.getGraph().getAllFlows();
    cout << utils.getGraph().getNodes().size() << endl;
    cout << todos.size() << endl;
    /*for (auto& flow: todos) {
        cout << flow.flow << " " << flow.source << "->" << flow.destination << endl;
    }*/
}

int main() {

    //func_test();

    Menu menu;
    menu.run();
}

