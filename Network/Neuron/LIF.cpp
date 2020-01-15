#include "LIF.h"
#include <iostream>
#include "Network/utils/Event.h"

using namespace std;

LIF::LIF() : param(new LIF_param) {
    u = param->u_rest;
    t_rest = 0.0;
    i = 0.0;
    initialize();
}

LIF::LIF(LIF_param* param) : param(param) {
    initialize();
}

Event* LIF::update(double n_dt) {
    dt = n_dt;
    if(t_rest > 0.0) {
        rest();
    }
    else if(u > param->u_thresh) {
        fire();
        return new SpikeEvent();
    }
    else {
        integrate();
    }
    return new NoEvent();
}

void LIF::integrate() {
    double du = ((param->r*input)-u)/param->tau;
    u += du * dt;
    t_rest = 0.0;
}

void LIF::fire() {
    u = param->u_rest;
    t_rest = param->tau_rest;
}

void LIF::rest() {
    u = param->u_rest;
    t_rest -= dt;
}

double LIF::getMembranePotential() {
    return u;
};

void LIF::handleEvent(Event* e) {
    // TODOS
}

LIF::~LIF() {
}