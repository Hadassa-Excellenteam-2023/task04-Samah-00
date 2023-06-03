#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <array>
#include <vector>
#include <functional>
#include <algorithm>

constexpr const char* FILENAME = "data.txt";

constexpr const int ERR_ARRAY_SIZE = 7;

enum MessageIndex {
    OPEN_FILE_ERR = 0,
    READ_COORD_ERR,
    INVALID_COORD_ERR,
    INVALID_FORMAT_ERR,
    READ_FILE_ERR,
    CITY_SEARTCH_ERR,
    INVALID_NORM_ERR
};

struct City {
    std::string _cityName;
    double _xCoord, _yCoord;
    double _distance;
    bool is_north;

    // Constructor
    City(const std::string& cityName, double xCoord, double yCoord, double distance, bool isNorth)
        : _cityName(cityName), _xCoord(xCoord), _yCoord(yCoord), _distance(distance), is_north(isNorth)
    {}
    // Comparison function to compare City objects based on _distance
    static bool compareByDistance(const City& city1, const City& city2) {
        return city1._distance < city2._distance;
    }
};

class CityMap {

public:
    CityMap() {
        m_messages[OPEN_FILE_ERR] = "Failed to open the file.";
        m_messages[READ_COORD_ERR] = "Error reading coordinates.";
        m_messages[INVALID_COORD_ERR] = "Invalid coordinate format.";
        m_messages[INVALID_FORMAT_ERR] = "Invalid coordinate format: extra characters found.";
        m_messages[READ_FILE_ERR] = "Error reading file.";
        m_messages[CITY_SEARTCH_ERR] = "City not found";
        m_messages[INVALID_NORM_ERR] = "Invalid norm value.";
    }

    void loadData();

    void addCity(const double x, const double y, const std::string& cityName);

    std::vector<City> getCitiesInRadius(const std::string& cityName, const double radius, const int norm) const;

private:
    std::multimap<double, std::pair<double, std::string>> m_cityMap;

    std::array<std::string, ERR_ARRAY_SIZE> m_messages;

    using DistanceFunction = std::function<double(double, double, double, double)>;

    static double calculateEuclideanDistance(double x1, double y1, double x2, double y2);

    static double calculateChebyshevDistance(double x1, double y1, double x2, double y2);

    static double calculateManhattanDistance(double x1, double y1, double x2, double y2);

    static const std::map<int, DistanceFunction> distanceFunctions;
};