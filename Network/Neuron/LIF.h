#ifndef LIF_H
#define LIF_H

#include <iostream>
#include "Neuron.h"
#include "Parameter.h"

struct LIF_param {
    // Membrane resting potential in mV
    double u_rest = 0.0;
    // Membrane threshold potential in mV
    double u_thresh = 1.0;
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
    LIF(LIF_param &param);
    void update();
    ~LIF();
private:
    LIF_param* params;
};



#endif
