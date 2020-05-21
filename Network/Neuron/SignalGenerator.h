#ifndef SignalGenerator_H
#define SignalGenerator_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include "Network/utils/Clock.h"
#include <random>

struct SignalGenerator_param : Parameters {
    double f1 = 1;
    double f2 = 0;
    double f3 = 0;
    double f4 = 0;
    double f5 = 0;
    double f6 = 0;
    double f7 = 0;
    double scale = 1;
    double offset = 0;
    double noiseMean = 0;
    double noiseStd = 0;
};

class SignalGenerator : public Neuron
{
public:
    SignalGenerator();
    SignalGenerator(SignalGenerator_param*);
    Event* update(double);
    void handleEvent(Event*);
    void resetInput();
    ~SignalGenerator();
private:
    double dt;
    SignalGenerator_param* param;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    Clock* clock;
};



#endif
