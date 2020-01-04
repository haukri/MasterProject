#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/Neuron/Neuron.h"
#include "Network/utils/Parameters.h"
#include "Population.h"
#include "Network/utils/Clock.h"

class SpikingPopulation : public Population
{
public:
    SpikingPopulation(int, std::string);
    SpikingPopulation(int, std::string, Parameters*);
    void update();
    double getCurrentTime();

private:
    std::vector<Neuron*> neurons;
    double current_time;
    Clock* clock;
};
