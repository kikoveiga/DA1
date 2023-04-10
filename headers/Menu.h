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
    std::vector<std::pair<std::string, std::string>> bidirectionalEdges;
public:

    /**
     * @brief Menu constructor
     */
    explicit Menu();

    /**
     * @brief function designed to initialize the menu
     */
    void run();

    /**
     * @brief function designed to choose an option in the menus
     */
    void enterOption(int n);

    /**
     * @brief function designed to parse a number from user input to command private field
     */
    void enterN();

    /**
     * @brief function designed to get the name of a station from user input
     * @param n
     *
     * @return
     */
    std::string enterStation(int n);

    /**
     * @brief function designed to await for user input for
     */
    void press0ToContinue();

    /**
     * @brief function designed to print a station object in a user friendly way
     * @param name string name of the station
     */
    void printStation(const std::string& name);

    /**
     * @brief clear empty space for increased readability in the menu
     */
    static void cleanTerminal();

    /**
     * @brief function designed to handle the menu requests
     */
    void mainMenu();

    /**
     * @brief function designed to handle the stations related requests
     */
    void stationsMenu();

    /**
     * @brief function designed to handle maxFlow related requests
     */
    void maxFlowMenu();

    /**
     * @brief function designed to handle reduced connectivity requests
     */
    void reducedConMenu();

    /**
     * @brief function designed to choose which edges to suppress from the main graph when using the reduced connectivity menu
     */
    void changeEdges();
};

#endif //DA1_MENU_H
