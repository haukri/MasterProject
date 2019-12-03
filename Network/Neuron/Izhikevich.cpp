#include "Izhikevich.h"
#include <iostream>

using namespace std;

Izhikevich::Izhikevich() : param(new Izhikevich_param) {
    v = param->c;
    u = 0.0;
}

Izhikevich::Izhikevich(Izhikevich_param* param) : param(param) { }

double Izhikevich::update(double n_input, double n_dt) {
    input = n_input;
    dt = n_dt;
    
    dv = 0.04*v*v + 5*v + 150 - u - input;
    du = param->a*(param->b*v - u);

    v += dv * dt;
    u += du * dt;

    if(v > param->v_thres) {
        v = param->c;
        u += param->d;
    }

    return u;
}

double Izhikevich::getMembranePotential() {
    return v;
};

Izhikevich::~Izhikevich() {
}