#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/utils/Parameters.h"
#include "Population.h"

class SpikingPopulation : public Population
{
public:
    SpikingPopulation(int amount, std::string type) : Population(amount, type) { };
    SpikingPopulation(int amount, std::string type, Parameters* param) : Population(amount, type, param) {};
    void update();
    ~SpikingPopulation() {};
private:

};
