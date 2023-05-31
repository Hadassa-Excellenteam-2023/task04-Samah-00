#include "CityMap.h"

double CityMap::calculateEuclideanDistance(const double x1, const double y1, const double x2, const double y2) const {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

double CityMap::calculateChebyshevDistance(const double x1, const double y1, const double x2, const double y2) const {
    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);
    return std::max(dx, dy);
}

double CityMap::calculateManhattanDistance(const double x1, const double y1, const double x2, const double y2) const {
    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);
    return dx + dy;
}

const CityMap::DistanceFunction CityMap::distanceFunctions[] = {
    &CityMap::calculateEuclideanDistance,
    & CityMap::calculateChebyshevDistance,
    & CityMap::calculateManhattanDistance
};

std::multimap<double, std::string> CityMap::getCitiesInRadius(const std::string& cityName, const double radius, const int norm) const {
    std::multimap<double, std::string> result;

    // Find the city with the given name in the map
    auto it = std::find_if(m_cityMap.begin(), m_cityMap.end(),
        [&cityName](const std::pair<double, std::pair<double, std::string>>& entry) {
            return entry.second.second == cityName;
        });

    if (it != m_cityMap.end()) {
        double x = it->first;
        double y = it->second.first;

        // Calculate the square boundaries based on the given radius
        double minX = x - radius;
        double maxX = x + radius;
        double minY = y - radius;
        double maxY = y + radius;

        // Find cities within the square boundaries:-
        //  First, find the range of cities within the x-coordinate boundaries:
        auto range = m_cityMap.lower_bound(minX);
        auto end = m_cityMap.upper_bound(maxX);

        for (auto it = range; it != end; ++it) {
            double currentX = it->first;
            double currentY = it->second.first;

            // Then, for each city within the x_coordinate range, check if it is within the y-coordinate range of the square
            if (currentY >= minY && currentY <= maxY) {
                // Calculate the distance using the selected distance function
                double distance = distanceFunctions[norm](x, y, currentX, currentY);

                // Check if the distance is within the radius
                if (distance <= radius) {
                    result.emplace(distance, it->second.second);
                }
            }
        }
    }
    else {
        // TODO: if the city isn't found, return something accordingly.
        /*
        if (!cityFound) {
            std::cout << "ERROR: \"" << cityName << "\" isn't found in the city list. Please try again." << std::endl;
            return result;
        }*/
    }
    return result;
}



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