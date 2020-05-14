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

struct LatencyEncodingSynapse_param : Parameters {
    double window_length_s = 0.5;
};

class LatencyEncodingSynapse : public Synapse
{
public:
    LatencyEncodingSynapse(Population* n_from, Population* n_to);
    LatencyEncodingSynapse(Population* n_from, Population* n_to, LatencyEncodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void resetOutput();
    void update();
private:
    LatencyEncodingSynapse_param* param;
    Eigen::VectorXd spikeTimes;
    int inputSize, outputSize;
    double currentWindow;
    Clock* clock;
    Logging* logger;
    std::vector<Event*> output;
};
