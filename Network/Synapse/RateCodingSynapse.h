#pragma once
#include <iostream>
#include <string>
#include "Synapse.h"
#include "Network/Population/Population.h"
#include "Network/utils/Parameters.h"
#include "Eigen/Core"
#include <deque>
#include <vector>
#include "Network/utils/Clock.h"
#include "Network/utils/Logging.h"

struct RateCodingSynapse_param : Parameters {
    // Time window in seconds
    double time_window = 1;
};

class RateCodingSynapse : public Synapse
{
public:
    RateCodingSynapse(Population* n_from, Population* n_to);
    RateCodingSynapse(Population* n_from, Population* n_to, RateCodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void update();
private:
    RateCodingSynapse_param* param;
    std::vector<std::deque<double>> spikes;
    Clock* clock;
    std::vector<Event*> output;
    int inputSize, outputSize;
    Logging* logger;
    bool singleOutput = false;
};
