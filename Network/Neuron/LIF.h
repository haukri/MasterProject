#ifndef LIF_H
#define LIF_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include "Network/utils/Event.h"

struct LIF_param : Parameters {
    // Membrane resting potential in mV
    double u_rest = -70.0;
    // Membrane threshold potential in mV
    double u_thresh = -50.0;
    // Duration of the resting period in ms
    double tau_rest = 4.0;
    // Membrane resistance in Ohm
    double r = 1.0;
    // Membrane time constant in ms
    double tau = 10.0;
};

class LIF : public Neuron
{
public:
    LIF();
    LIF(LIF_param*);
    Event* update(double);
    void handleEvent(Event*);
    double getMembranePotential();
    ~LIF();
private:
    void integrate();
    void fire();
    void rest();
    double t_rest, u, i;
    double input = 0.0;
    double dt;
    LIF_param* param;
};



#endif
