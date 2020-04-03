#ifndef CurrentGenerator_H
#define CurrentGenerator_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include <random>

struct CurrentGenerator_param : Parameters {
    double I = 10.0;
    double noiseMean = 0;
    double noiseStd = 1.0;
    double noiseOn = 0;
    double ac_hz = 0;
};

class CurrentGenerator : public Neuron
{
public:
    CurrentGenerator();
    CurrentGenerator(CurrentGenerator_param*);
    Event* update(double);
    void handleEvent(Event*);
    void resetInput();
    ~CurrentGenerator();
private:
    double dt;
    CurrentGenerator_param* param;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    Clock* clock;
};



#endif
