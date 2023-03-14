//
// Created by kikoveiga on 14-03-2023.
//

#include <string>

#ifndef DA1_STATION_H
#define DA1_STATION_H

class Station {

private:
    const std::string name;
    const std::string district;
    const std::string municipality;
    const std::string township;
    const std::string line;


public:
    const std::string getName() const;
    const std::string getDistrict() const;
    const std::string getMunicipality() const;
    const std::string getTownship() const;
    const std::string getLine() const;

};
#endif //DA1_STATION_H
