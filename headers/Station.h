//
// Created by kikoveiga on 14-03-2023.
//

#include <string>

#ifndef DA1_STATION_H
#define DA1_STATION_H

class Station {

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

public:
    /**
     * @brief Station constructor
     * @param name string with the name of the station
     * @param district string with the district of the station
     * @param municipality string with the municipality of the station
     * @param township string with the township of the station
     * @param line string with the line of the station
     */
    Station(const std::string& name, const std::string& district, const std::string& municipality, const std::string& township, const std::string& line);

    /**
     * @brief Get function for the name of the station
     * @return string name
     */
    const std::string& getName() const;

    /**
     * @brief Get function for the district of the station
     * @return string district
     */
    const std::string& getDistrict() const;

    /**
     * @brief Get function for the municipality of the station
     * @return string municipality
     */
    const std::string& getMunicipality() const;

    /**
     * @brief Get function for the township of the station
     * @return string township
     */
    const std::string& getTownship() const;

    /**
     * @brief Get function for the line of the station
     * @return string line
     */
    const std::string& getLine() const;

};

#endif //DA1_STATION_H
