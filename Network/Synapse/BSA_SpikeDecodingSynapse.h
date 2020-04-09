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

struct BSA_SpikeDecodingSynapse_param : Parameters {
    double filter_length = 24;   // Time window in seconds
    double threshold = 0.9550;
};

class BSA_SpikeDecodingSynapse : public Synapse
{
public:
    BSA_SpikeDecodingSynapse(Population* n_from, Population* n_to);
    BSA_SpikeDecodingSynapse(Population* n_from, Population* n_to, BSA_SpikeDecodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void update();
private:
    BSA_SpikeDecodingSynapse_param* param;
    std::vector<std::deque<double>> spikes;
    std::vector<double> filter;
    std::vector<std::deque<double>> input;
    Clock* clock;
    std::vector<Event*> output;
    int inputSize, outputSize;
    Logging* logger;
};
