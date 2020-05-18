#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/LatencyEncodingSynapse.h"
#include "Network/Synapse/LatencyDecodingSynapse.h"
#include "Network/Neuron/iaf_psc_alpha.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    srand(time(NULL));

    // Command line arguments
    double window_length_s = 0.1;
    double dt = 0.001;
    if(argc == 3) {
        window_length_s = atof(argv[1]);
        dt = atof(argv[2]);
    }
    // ----------------------

    Clock::getInstance()->setDt(dt);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f1 = 1;
    paramp1->f2 = 2;
    paramp1->scale = 1/5.0;
    paramp1->offset = 0.5;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    iaf_psc_alpha_param* paramp3 = new iaf_psc_alpha_param();
    Population* p3 = new Population(1, "iaf_psc_alpha");
    Population* p4 = new Population(1, "PassThrough");

    // Synapses
    LatencyEncodingSynapse_param* params1 = new LatencyEncodingSynapse_param();
    params1->window_length_s = window_length_s;
    LatencyEncodingSynapse* s1 = new LatencyEncodingSynapse(p1, p3, params1);

    LatencyDecodingSynapse_param* params2 = new LatencyDecodingSynapse_param();
    params2->window_length_s = window_length_s;
    params2->delay_s = 0.004;
    LatencyDecodingSynapse* s2 = new LatencyDecodingSynapse(p3, p4, params2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = dt;
    Network n = Network(n_param);

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);


    cout << (long)s2 << endl;
    cout << (long)s1 << endl;
    cout << (long)p3 << endl;

    // Run the network for 100 second
    n.run(5.0);
    
    return 0;
}