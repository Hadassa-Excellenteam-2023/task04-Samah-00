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
        std::cin >> radius;

        std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance): ";
        std::cin >> norm;
        /*        // Get cities within the given radius
        std::multimap<double, std::string> result = m_cityMap.getCitiesInRadius(cityName, radius, norm);

        // Print the cities
        std::cout << "Cities within the radius:" << std::endl;
        for (const auto& entry : result) {
            double distance = entry.first;
            const std::string& storedCityName = entry.second;
            std::cout << storedCityName << " (Distance: " << distance << ")" << std::endl;
        }
        */
    }
}