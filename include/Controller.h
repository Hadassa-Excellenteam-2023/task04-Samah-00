#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <algorithm>
#include "CityMap.h"

const std::string END_INPUT = "0";

constexpr const int MSG_ARRAY_SIZE = 7;

enum ErrorIndex {
    CITY_MSG = 0,
    RADIUS_MSG,
    NORM_MSG,
    RESULT_MSG,
    INVALID_RADIUS_MSG,
    INVALID_NORM_MSG,
    END_MSG
};

class Controller {
public:
    Controller() {
        m_messages[CITY_MSG] = "Please enter selected city name (with line break after it): ";
        m_messages[RADIUS_MSG] = "Please enter the wanted radius: ";
        m_messages[NORM_MSG] = "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance): ";
        m_messages[RESULT_MSG] = "Cities within the radius:";
        m_messages[INVALID_RADIUS_MSG] = "Invalid radius value. Please enter a positive number.";
        m_messages[INVALID_NORM_MSG] = "Invalid norm value. Please enter 0, 1, or 2.";
        m_messages[END_MSG] = "Bye";
    }

    void run();

private:
    CityMap m_cityMap;

    std::array<std::string, MSG_ARRAY_SIZE> m_messages;

    void printResults(const std::vector<City>& cities, const size_t countNorthCities);

    void dialog(std::string& cityName, double& radius, int& norm);
};
