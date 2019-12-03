#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/Neuron/Neuron.h"
#include "Network/utils/Parameters.h"

class Population
{
public:
    Population(int, std::string);
    Population(int, std::string, Parameters*);
    virtual void update()
    {
        std::cout << "Update not implemented!" << std::endl;
    }

private:
    std::vector<Neuron*> neurons;
};
