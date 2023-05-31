#include <iostream>
#include "Controller.h"

constexpr const int RUN_TIME_ERROR = 1;

int main() {

    Controller controller;

    try {
        controller.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return RUN_TIME_ERROR; // Return a non-zero value to indicate an error occurred
    }

    return 0;
}
