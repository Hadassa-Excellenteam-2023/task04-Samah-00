#include "CityMap.h"

void CityMap::loadData() {
    std::ifstream file(FILENAME);

    if (!file) {
        throw std::runtime_error("Failed to open the file.");
    }

    std::string line;
    std::string cityName;
    double coordX, coordY;

    while (std::getline(file, line)) {
        // Read the city name
        cityName = line;

        // Read the coordinates
        if (!std::getline(file, line)) {
            throw std::runtime_error("Error reading coordinates.");
        }

        std::istringstream coordinates(line);
        coordinates >> coordX;
        coordinates.ignore(std::numeric_limits<std::streamsize>::max(), '-'); // ignore the "-"
        coordinates >> coordY;

        if (coordinates.fail()) {
            throw std::runtime_error("Invalid coordinate format.");
        }

        // Check for extra characters after the coordinates
        std::string extra;
        if (coordinates >> extra) {
            throw std::runtime_error("Invalid coordinate format: extra characters found.");
        }

        // Add the city to the map using the addCity function
        addCity(coordX, coordY, cityName);
    }

    if (!file.eof()) {
        throw std::runtime_error("Error reading file.");
    }

    file.close();
}

void CityMap::addCity(const double x, const double y, const std::string& cityName) {
    m_cityMap.insert({ x, {y, cityName} });
}