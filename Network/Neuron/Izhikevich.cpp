#include "Izhikevich.h"
#include <iostream>
#include <limits>

using namespace std;

Izhikevich::Izhikevich(long n_populationID, int n_neuronID) : param(new Izhikevich_param) {
    populationID = n_populationID;
    neuronID = n_neuronID;
    v = param->c;
    u = 0.0;
    initialize();
}

Izhikevich::Izhikevich(long n_populationID, int n_neuronID, Izhikevich_param* param) : param(param) {
    populationID = n_populationID;
    neuronID = n_neuronID;
    v = param->c;
    u = 0.0;
    initialize();
}

Event* Izhikevich::update(double n_dt) {
    dt = n_dt;
    
    dv = 0.04*v*v + 5*v + 140 - u + input_current;
    du = param->a*(param->b*v - u);

    v += dv * dt + input_spike;
    u += du * dt;

    v = ( v < -std::numeric_limits< double >::max() ? -std::numeric_limits< double >::max() : v );

    logger->logValue(populationID, neuronID, ValueType::voltage, v);

    if(v > param->v_thres) {
        v = param->c;
        u += param->d;
        return new SpikeEvent();
    }

    return new NoEvent();
}

void Izhikevich::resetInput() {
    input_spike = 0.0;
    input_current = 0.0;
}

double Izhikevich::getMembranePotential() {
    return v;
};

void Izhikevich::handleEvent(Event* e) {
    if(e->type == EventType::Spike) {
        input_spike += static_cast<SpikeEvent*>(e)->weight * static_cast<SpikeEvent*>(e)->multiplicity;
    }
    else if(e->type == EventType::Current) {
        input_current += static_cast<CurrentEvent*>(e)->weight * static_cast<CurrentEvent*>(e)->current;
    }
}

Izhikevich::~Izhikevich() {
}