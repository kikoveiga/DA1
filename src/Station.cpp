//
// Created by kikoveiga on 14-03-2023.
//

#include "../headers/Station.h"

using namespace std;

Station::Station(const string& name, const string& district, const string& municipality, const string& township, const string& line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

const string& Station::getName() const {
    return name;
}

const string& Station::getDistrict() const {
    return district;
}

const string& Station::getMunicipality() const {
    return municipality;
}

const string& Station::getTownship() const {
    return township;
}

const string& Station::getLine() const {
    return line;
}
