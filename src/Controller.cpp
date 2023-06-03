#include "Controller.h"

void Controller::run() {

    // Load data from the file
    m_cityMap.loadData();

    while (true) {
        
        std::string cityName;
        double radius;
        int norm;

        dialog(cityName, radius, norm);

        if (cityName == END_INPUT) {
            std::cout << m_messages[END_MSG] << std::endl;
            break;
        }

        std::vector<City> result;
        // Get cities within the given radius
        try {
             result = m_cityMap.getCitiesInRadius(cityName, radius, norm);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            continue;
        }

        // Count the number of cities where is_north is true
        size_t countNorthCities = std::count_if(result.begin(), result.end(),
            [](const City& city) {
                return city.is_north;
            });

        // Print the cities
        printResults(result, countNorthCities);
    }
}

void Controller::printResults(const std::vector<City>& cities, const size_t countNorthCities) {
    std::cout << m_messages[RESULT_MSG] << std::endl;
    std::cout << cities.size() << " city/cities found in the given radius.\n";
    std::cout << countNorthCities << " cities are to the north of the selected city.\n";
    if (cities.size()) {
        std::cout << "City list:\n";
        for (const auto& entry : cities) {
            std::cout << entry._cityName << std::endl;
        }
    }
}

void Controller::dialog(std::string& cityName, double& radius, int& norm) {
    while (true) {
        std::cout << m_messages[CITY_MSG] << std::endl;
        std::getline(std::cin, cityName);
        if (cityName.empty()) {
            continue;
        }
        if (cityName == END_INPUT) {
            return;
        }
        break;
    }

    while (true) {
        std::cout << m_messages[RADIUS_MSG];
        if (!(std::cin >> radius) || radius <= 0) {
            std::cout << m_messages[INVALID_RADIUS_MSG] << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    while (true) {
        std::cout << m_messages[NORM_MSG];
        if (!(std::cin >> norm) || norm < 0 || norm > 2) {
            std::cout << m_messages[INVALID_NORM_MSG] << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    return;
}