#include "Izhikevich.h"
#include <iostream>
#include <limits>

using namespace std;

Izhikevich::Izhikevich() : param(new Izhikevich_param) {
    v = param->c;
    u = 0.0;
}

Izhikevich::Izhikevich(Izhikevich_param* param) : param(param) { }

Event Izhikevich::update(double n_dt) {
    dt = n_dt;
    
    dv = 0.04*v*v + 5*v + 140 - u + input_current;
    du = param->a*(param->b*v - u);

    v += dv * dt + input_spike;
    u += du * dt;

    v = ( v < -std::numeric_limits< double >::max() ? -std::numeric_limits< double >::max() : v );

    if(v > param->v_thres) {
        v = param->c;
        u += param->d;
        return SpikeEvent();
    }

    return NoEvent();
}

double Izhikevich::getMembranePotential() {
    return v;
};

void Izhikevich::handleEvent(Event* e) {
    if(e->type == EventType::Spike) {
        input_spike = static_cast<SpikeEvent*>(e)->weight * static_cast<SpikeEvent*>(e)->multiplicity;
        input_current = 0.0;
    }
    else if(e->type == EventType::Current) {
        input_current = static_cast<CurrentEvent*>(e)->weight * static_cast<CurrentEvent*>(e)->current;
        input_spike = 0.0;
    }
    else {
        input_current = 0.0;
        input_spike = 0.0;
    }
}

Izhikevich::~Izhikevich() {
}