#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/Neuron/Neuron.h"

class Population
{
public:
    Population(int, std::string);
    virtual void update()
    {
        std::cout << "Update not implemented!" << std::endl;
    }

private:
    std::vector<Neuron*> neurons;
};
