#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/BSA_SpikeDecodingSynapse.h"
#include "Network/Synapse/BSA_SpikeEncodingSynapse.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    srand(time(NULL));

    // Command line arguments
    double filter_length = 20;
    double dt = 0.0001;
    // ----------------------


    Clock::getInstance()->setDt(dt);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f1 = 1;
    paramp1->f2 = 4;
    paramp1->f3 = 7;
    paramp1->f4 = 12;
    paramp1->f5 = 18;
    paramp1->f6 = 24;
    paramp1->f7 = 50;
    paramp1->scale = 1/16.0;
    paramp1->offset = 0.5;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    Population* p3 = new Population(1, "PassThrough");
    Population* p4 = new Population(1, "PassThrough");

    // Synapses
    BSA_SpikeEncodingSynapse_param* params1 = new BSA_SpikeEncodingSynapse_param();
    params1->filter_length = filter_length;
    params1->threshold = 0.995;
    params1->scale = 1.0/8.0;
    BSA_SpikeEncodingSynapse* s1 = new BSA_SpikeEncodingSynapse(p1, p3, params1);

    BSA_SpikeDecodingSynapse_param* params2 = new BSA_SpikeDecodingSynapse_param();
    params2->filter_length = filter_length;
    params2->threshold = 0.995;
    params2->scale = 1.0/8.0;
    BSA_SpikeDecodingSynapse* s2 = new BSA_SpikeDecodingSynapse(p3, p4, params2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = dt;
    Network n = Network(n_param);

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);

    cout << (long)s2 << endl;

    // Run the network for 100 second
    n.run(1.0);
    
    return 0;
}