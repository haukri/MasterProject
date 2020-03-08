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

struct TemporalPhaseEncodingSynapse_param : Parameters {
    double som_frequency = 40;
    double som_phase = 0;
    double window_length_s = 0.5;
};

class TemporalPhaseEncodingSynapse : public Synapse
{
public:
    TemporalPhaseEncodingSynapse(Population* n_from, Population* n_to);
    TemporalPhaseEncodingSynapse(Population* n_from, Population* n_to, TemporalPhaseEncodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void resetOutput();
    void update();
private:
    TemporalPhaseEncodingSynapse_param* param;
    Eigen::VectorXd spikeTimes;
    int inputSize, outputSize;
    double currentWindow;
    double phaseStep, phaseOffset;
    Clock* clock;
    Logging* logger;
    std::vector<Event*> output;
};
