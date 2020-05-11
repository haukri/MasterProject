#ifndef SignalGenerator_H
#define SignalGenerator_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include "Network/utils/Clock.h"

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
    Clock* clock;
};



#endif
