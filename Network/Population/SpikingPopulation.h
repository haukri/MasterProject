#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/Neuron/Neuron.h"
#include "Network/utils/Parameters.h"
#include "Population.h"

class SpikingPopulation : public Population
{
public:
    SpikingPopulation(int, std::string);
    SpikingPopulation(int, std::string, Parameters*);
    void update(std::vector<double> &input, double);
    double getCurrentTime();

private:
    std::vector<Neuron*> neurons;
    std::vector<double> output;
    double current_time;
};
