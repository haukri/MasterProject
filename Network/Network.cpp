#include <iostream>
#include "Network.h"


using namespace std;

Network::Network() : 
    param(new Network_param())
{
    clock = Clock::getInstance();
}

Network::Network(Network_param* param) : 
    param(param) 
{
    clock = Clock::getInstance();
}

void Network::add(Synapse* n_synapse) {
    synapses.push_back(n_synapse);
    if(!networkContainsPopulation(n_synapse->from_population))
        populations.push_back(n_synapse->from_population);
    if(!networkContainsPopulation(n_synapse->to_population))
        populations.push_back(n_synapse->to_population);
};

bool Network::networkContainsPopulation(Population* p1) {
    for(Population* p2 : populations) {
        if(p1 == p2)
            return true;
    }
    return false;
};

void Network::run(double runtime) {
    cout << "Running network for " << runtime << " milliseconds" << endl;
    clock->setDt(param->dt);
    while(clock->getCurrentTime() < runtime) {
        clock->tick(param->dt);
        update();
    }
};

void Network::run() {
    cout << "Running network without time limit" << endl;
};

void Network::update() {
    for(Population* p : populations) {
        p->update();
    }
    for(Synapse* s : synapses) {
        s->update();
    }
}

Network::~Network()
{
    
}