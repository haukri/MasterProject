#include "LIF.h"
#include <iostream>

using namespace std;

LIF::LIF() : param(new LIF_param) {
    u = param->u_rest;
    t_rest = 0.0;
    i = 0.0;
}

LIF::LIF(LIF_param* param) : param(param) { }

double LIF::update(double n_input, double n_dt) {
    input = n_input;
    dt = n_dt;
    if(t_rest > 0.0) {
        rest();
    }
    else if(u > param->u_thresh) {
        fire();
    }
    else {
        integrate();
    }
    return t_rest > 0.0 ? 0.01 : 0;
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

LIF::~LIF() {
}