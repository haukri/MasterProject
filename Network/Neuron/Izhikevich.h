#ifndef Izhikevich_H
#define Izhikevich_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"

struct Izhikevich_param : Parameters {
    double a = 0.02;
    double b = 0.2;
    double c = -65;
    double d = 8;
    double v_thres = 30;
};

class Izhikevich : public Neuron
{
public:
    Izhikevich(long populationID, int neuronID);
    Izhikevich(long populationID, int neuronID, Izhikevich_param*);
    Event* update(double);
    void handleEvent(Event*);
    double getMembranePotential();
    void resetInput();
    ~Izhikevich();
private:
    double u, v, du, dv;
    double input_current = 0.0;
    double input_spike = 0.0;
    double dt;
    Izhikevich_param* param;
};



#endif
