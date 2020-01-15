#pragma once
#include "Eigen/Core"
#include "Network/Population/Population.h"
#include "Network/Synapse/Synapse.h"
#include "Network/utils/Parameters.h"
#include "Network/utils/Clock.h"
#include <vector>
#include "Network/utils/Logging.h"

struct Network_param {
    double dt = 0.01;
};

class Network
{
public:
    Network();
    Network(Network_param*);
    void add(Synapse*);
    void run();
    void run(double);
    ~Network();

private:
    void update();
    bool networkContainsPopulation(Population*);
    std::vector<Synapse*> synapses;
    Network_param* param;
    std::vector<Population*> populations;
    Clock* clock;
    Logging* logger;
};
