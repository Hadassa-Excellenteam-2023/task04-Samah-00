#include "Controller.h"

void Controller::run() {

    // Load data from the file
    m_cityMap.loadData();

    while (true) {
        std::string cityName;
        double radius;
        int norm;

        std::cout << "Please enter selected city name (with line break after it): " << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, cityName);

        if (cityName == "0") {
            std::cout << "Bye" << std::endl;
            break;
        }

        std::cout << "Please enter the wanted radius: ";
        if (!(std::cin >> radius) || radius <= 0) {
            std::cout << "Invalid radius value. Please enter a positive number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance): ";
        if (!(std::cin >> norm) || norm < 0 || norm > 2) {
            std::cout << "Invalid norm value. Please enter 0, 1, or 2." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Get cities within the given radius
        std::multimap<double, std::string> result = m_cityMap.getCitiesInRadius(cityName, radius, norm);

        /* WE ARE HERE*/

        // Print the cities
        std::cout << "Cities within the radius:" << std::endl;
        for (const auto& entry : result) {
            double distance = entry.first;
            const std::string& storedCityName = entry.second;
            std::cout << storedCityName << " (Distance: " << distance << ")" << std::endl;
        }
    }
}