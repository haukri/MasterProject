#pragma once
#include <iostream>
#include <string>
#include "Synapse.h"
#include "Network/Population/Population.h"
#include "Network/utils/Parameters.h"

struct StaticSynapse_param : Parameters {
    double connection_probability;
};

class StaticSynapse : public Synapse
{
public:
    StaticSynapse(Population* n_from, Population* n_to);
    StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param*);
    void update(double from, double to);

private:
    Population* from_population;
    Population* to_population;
    StaticSynapse_param* param;
};
