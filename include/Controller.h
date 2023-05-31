#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "CityMap.h"


class Controller {

public:
    void run();

private:
    CityMap m_cityMap;
};