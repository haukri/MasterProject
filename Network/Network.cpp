#include <iostream>
#include "Network.h"


using namespace std;

Network::Network() : 
    param(new Network_param())
{

}

Network::Network(Network_param* param) : 
    param(param) 
{

}

void Network::add(Synapse* n_synapse){ 
    synapses.push_back(n_synapse);
};

void Network::run(double runtime) {
    cout << "Running network for " << runtime << " milliseconds" << endl;
};

void Network::run() {
    cout << "Running network without time limit" << endl;   
};

Network::~Network()
{
    
}