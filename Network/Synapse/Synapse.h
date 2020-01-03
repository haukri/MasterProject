#pragma once
#include <iostream>
#include <string>
#include "Network/Population/Population.h"

class Synapse
{
public:
    Population* from_population;
    Population* to_population;
    virtual void update() {
        std::cout << "update in synapse not implemented!" << std::endl;
    };
private:
};
