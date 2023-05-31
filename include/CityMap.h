#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <limits>

constexpr const char* FILENAME = "data.txt";

class CityMap {
private:
    std::multimap<double, std::pair<double, std::string>> m_cityMap;

public:
    CityMap() = default;

    void loadData();

    void addCity(const double x, const double y, const std::string& cityName);
};