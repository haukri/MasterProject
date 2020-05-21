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

struct ReceptiveFieldDecodingSynapse_param : Parameters {
    double window_length_s = 0.5;
    int number_of_neurons = 10;
    double input_min = 0.0;
    double input_max = 1.0;
    double delay_s = 0;
};

class ReceptiveFieldDecodingSynapse : public Synapse
{
public:
    ReceptiveFieldDecodingSynapse(Population* n_from, Population* n_to);
    ReceptiveFieldDecodingSynapse(Population* n_from, Population* n_to, ReceptiveFieldDecodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void resetOutput();
    void update();
private:
    ReceptiveFieldDecodingSynapse_param* param;
    Eigen::VectorXd spikeTimes;
    int inputSize, outputSize;
    double outputStep;
    double currentWindow;
    bool earliestSpike = false;
    Clock* clock;
    Logging* logger;
    std::vector<Event*> output;
};
