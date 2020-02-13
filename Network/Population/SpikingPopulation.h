#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/utils/Parameters.h"
#include "Population.h"

class SpikingPopulation : public Population
{
public:
    SpikingPopulation(int, std::string);
    SpikingPopulation(int, std::string, Parameters*);
    void update();
    ~SpikingPopulation() {};
private:

};
