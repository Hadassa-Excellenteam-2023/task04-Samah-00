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

    using DistanceFunction = double (*)(double, double);

    // Define the distance function pointer array as a static member
    static const DistanceFunction distanceFunctions[];

public:
    CityMap() = default;

    void loadData();

    void addCity(const double x, const double y, const std::string& cityName);

    double calculateEuclideanDistance(const double x1, const double y1, const double x2, const double y2) const;

    double calculateChebyshevDistance(const double x1, const double y1, const double x2, const double y2) const;

    double calculateManhattanDistance(const double x1, const double y1, const double x2, const double y2) const;

    std::multimap<double, std::string> getCitiesInRadius(const std::string& cityName, const double radius, const int norm) const;
};