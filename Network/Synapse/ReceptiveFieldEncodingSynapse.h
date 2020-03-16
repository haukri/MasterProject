#pragma once
#include <iostream>
#include <string>
#include "Synapse.h"
#include "Network/Population/Population.h"
#include "Network/utils/Parameters.h"
#include "Eigen/Core"
#include <vector>
#include "Network/utils/Clock.h"
#include "Network/utils/Logging.h"

struct ReceptiveFieldEncodingSynapse_param : Parameters {
    double window_length_s = 0.5;
    int number_of_neurons = 10;
    double beta = 1.5;
    double input_min = 0.0;
    double input_max = 1.0;
};

class ReceptiveFieldEncodingSynapse : public Synapse
{
public:
    ReceptiveFieldEncodingSynapse(Population* n_from, Population* n_to);
    ReceptiveFieldEncodingSynapse(Population* n_from, Population* n_to, ReceptiveFieldEncodingSynapse_param*);
    double gaussian(int index, double value);
    void initialize(Population* n_from, Population* n_to);
    void resetOutput();
    void update();
private:
    ReceptiveFieldEncodingSynapse_param* param;
    Eigen::VectorXd spikeTimes;
    int inputSize, outputSize;
    double currentWindow;
    double gaussianMax;
    Clock* clock;
    Logging* logger;
    std::vector<Event*> output;
};
