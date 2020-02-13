#include <iostream>
#include "Network.h"
#include <chrono> 


using namespace std;

Network::Network() : 
    param(new Network_param())
{
    clock = Clock::getInstance();
    logger = Logging::getInstance();
}

Network::Network(Network_param* param) : 
    param(param) 
{
    clock = Clock::getInstance();
    logger = Logging::getInstance();
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
    cout << "Running network for " << runtime << " seconds" << endl;
    auto start = std::chrono::high_resolution_clock::now(); 
    clock->setDt(param->dt);
    while(clock->getCurrentTime() < runtime) {
        clock->tick(param->dt);
        update();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    cout << "Execution time: " << duration.count()/1000.0 << " milliseconds" << endl; 
    
    logger->saveLog();
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