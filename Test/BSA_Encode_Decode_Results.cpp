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
    double sine1 = 1;
    double sine2 = 0;
    double sine3 = 0;
    double sine4 = 0;
    double sine5 = 0;
    double sine6 = 0;
    double sine7 = 0;
    double filter_length = 20;
    double dt = 0.0001;
    double mean = 0;
    double variance = 0;
    if(argc >= 10) {
        sine1 = atof(argv[1]);
        sine2 = atof(argv[2]);
        sine3 = atof(argv[3]);
        sine4 = atof(argv[4]);
        sine5 = atof(argv[5]);
        sine6 = atof(argv[6]);
        sine7 = atof(argv[7]);
        filter_length = atof(argv[8]);
        dt = atof(argv[9]);
    }
    if(argc == 12) {
        mean = atof(argv[10]);
        variance = atof(argv[11]);
    }
    // ----------------------

    Clock::getInstance()->setDt(dt);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f1 = sine1;
    paramp1->f2 = sine2;
    paramp1->f3 = sine3;
    paramp1->f4 = sine4;
    paramp1->f5 = sine5;
    paramp1->f6 = sine6;
    paramp1->f7 = sine7;
    paramp1->scale = 1/16.0;
    paramp1->offset = 0.5;
    paramp1->noiseMean = mean;
    paramp1->noiseStd = variance;
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