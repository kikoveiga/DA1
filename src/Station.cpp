//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Station.h"

using namespace std;

const string Station::getName() const {
    return name;
}

const string Station::getDistrict() const {
    return district;
}

const string Station::getMunicipality() const {
    return municipality;
}

const string Station::getTownship() const {
    return township;
}

const string Station::getLine() const {
    return line;
}
