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

struct TemporalPhaseDecodingSynapse_param : Parameters {
    double som_frequency = 40;
    double som_phase = 0;
    double window_length_s = 0.5;
};

class TemporalPhaseDecodingSynapse : public Synapse
{
public:
    TemporalPhaseDecodingSynapse(Population* n_from, Population* n_to);
    TemporalPhaseDecodingSynapse(Population* n_from, Population* n_to, TemporalPhaseDecodingSynapse_param*);
    void initialize(Population* n_from, Population* n_to);
    void resetOutput();
    void update();
private:
    TemporalPhaseDecodingSynapse_param* param;
    Eigen::VectorXd spikeTimes;
    int inputSize, outputSize;
    double currentWindow;
    double phaseStep, phaseOffset;
    Clock* clock;
    Logging* logger;
    std::vector<Event*> output;
};
