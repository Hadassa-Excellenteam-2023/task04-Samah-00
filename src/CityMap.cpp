#include "CityMap.h"

double CityMap::calculateEuclideanDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

double CityMap::calculateChebyshevDistance(double x1, double y1, double x2, double y2) {
    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);
    return std::max(dx, dy);
}

double CityMap::calculateManhattanDistance(double x1, double y1, double x2, double y2) {
    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);
    return dx + dy;
}

const std::map<int, CityMap::DistanceFunction> CityMap::distanceFunctions = {
    { 0, &CityMap::calculateEuclideanDistance },
    { 1, &CityMap::calculateChebyshevDistance },
    { 2, &CityMap::calculateManhattanDistance }
};

std::vector<City> CityMap::getCitiesInRadius(const std::string& cityName, const double radius, const int norm) const {
    std::vector<City> result;

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
        // Get the appropriate distance calculation function based on the norm
        auto distanceFuncIt = distanceFunctions.find(norm);
        if (distanceFuncIt != distanceFunctions.end()) {
            DistanceFunction distanceFunc = distanceFuncIt->second;

            // Find the range of cities within the x-coordinate boundaries:
            auto range = m_cityMap.lower_bound(minX);
            auto end = m_cityMap.upper_bound(maxX);

            // Then, for each city within the x_coordinate range, check if it is within the y-coordinate range of the square
            for (auto it = range; it != end; ++it) {
                double currentX = it->first;
                double currentY = it->second.first;

                if (currentY >= minY && currentY <= maxY) {
                    double distance = (distanceFunc)(x, y, currentX, currentY);
                    // Check if the distance is within the radius
                    if (distance <= radius && it->second.second != cityName) {
                        City newCity(it->second.second, currentX, currentY, distance, (currentY > y));
                        result.push_back(newCity);

                    }
                }
            }
        }
        else {
            throw std::runtime_error(m_messages[INVALID_NORM_ERR]);
        }
    }
    else {
        throw std::runtime_error(m_messages[CITY_SEARTCH_ERR]);
    }

    // Sort the vector based on _distance
    std::sort(result.begin(), result.end(), City::compareByDistance);

    return result;
}



void CityMap::loadData() {
    std::ifstream file(FILENAME);

    if (!file) {
        throw std::runtime_error(m_messages[OPEN_FILE_ERR]);
    }

    std::string line;
    std::string cityName;
    double coordX, coordY;

    while (std::getline(file, line)) {
        // Read the city name
        cityName = line;

        // Remove the comma if present
        size_t commaPos = cityName.find(',');
        if (commaPos != std::string::npos) {
            cityName.erase(commaPos, 1);
        }

        // Read the coordinates
        if (!std::getline(file, line)) {
            throw std::runtime_error(m_messages[READ_COORD_ERR]);
        }

        std::istringstream coordinates(line);
        coordinates >> coordX;
        coordinates.ignore(std::numeric_limits<std::streamsize>::max(), '-'); // ignore the "-"
        coordinates >> coordY;

        if (coordinates.fail()) {
            throw std::runtime_error(m_messages[INVALID_COORD_ERR]);
        }

        // Check for extra characters after the coordinates
        std::string extra;
        if (coordinates >> extra) {
            throw std::runtime_error(m_messages[INVALID_FORMAT_ERR]);
        }

        // Add the city to the map using the addCity function
        addCity(coordX, coordY, cityName);
    }

    if (!file.eof()) {
        throw std::runtime_error(m_messages[READ_FILE_ERR]);
    }

    file.close();
}

void CityMap::addCity(const double x, const double y, const std::string& cityName) {
    m_cityMap.insert({ x, {y, cityName} });
}