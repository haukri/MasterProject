#pragma once
#include <iostream>
#include <string>
#include "Synapse.h"
#include "Network/Population/Population.h"
#include "Network/utils/Parameters.h"
#include "Eigen/Core"
#include <vector>

struct StaticSynapse_param : Parameters {
    double connection_probability = 0.2;
};

class StaticSynapse : public Synapse
{
public:
    StaticSynapse(Population* n_from, Population* n_to);
    StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void update();
    void setWeight(int from_neurons, int to_neuron, double weight);
private:
    StaticSynapse_param* param;
    Eigen::MatrixXd weights;
    int inputSize, outputSize;
};
