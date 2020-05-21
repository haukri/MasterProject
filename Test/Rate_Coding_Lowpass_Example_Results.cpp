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
#include "Network/Neuron/iaf_psc_alpha.h"

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
    string filterType = "lowpass";
    if(argc == 11) {
        sine1 = atof(argv[1]);
        sine2 = atof(argv[2]);
        sine3 = atof(argv[3]);
        sine4 = atof(argv[4]);
        sine5 = atof(argv[5]);
        sine6 = atof(argv[6]);
        sine7 = atof(argv[7]);
        filter_length = atof(argv[8]);
        dt = atof(argv[9]);
        filterType = argv[10];
    }
    // ----------------------

    Clock::getInstance()->setDt(dt);

    ANN* ann = new ANN();
    ann->setInputSize(1);
    ann->addLayer(1, filterType);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f1 = sine1;
    paramp1->f2 = sine2;
    paramp1->f3 = sine3;
    paramp1->f4 = sine4;
    paramp1->f5 = sine5;
    paramp1->f6 = sine6;
    paramp1->f7 = sine7;
    paramp1->scale = 1/5.0;
    paramp1->offset = 0.5;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    ArtificialPopulation* p2 = new ArtificialPopulation(ann);

    Population* p3 = new Population(1, "iaf_psc_alpha");
    Population* p4 = new Population(1, "iaf_psc_alpha");
    Population* p5 = new Population(1, "PassThrough");

    // Synapses
    BSA_SpikeEncodingSynapse_param* params1 = new BSA_SpikeEncodingSynapse_param();
    params1->filter_length = filter_length;
    params1->threshold = 0.995;
    params1->scale = 1.0/8.0;
    BSA_SpikeEncodingSynapse* s1 = new BSA_SpikeEncodingSynapse(p1, p3, params1);

    BSA_SpikeDecodingSynapse_param* params2 = new BSA_SpikeDecodingSynapse_param();
    params2->filter_length = 500;
    params2->threshold = 0.995;
    params2->scale = 1.0/8.0;
    BSA_SpikeDecodingSynapse* s2 = new BSA_SpikeDecodingSynapse(p3, p2, params2);

    // Synapses
    BSA_SpikeEncodingSynapse_param* params3 = new BSA_SpikeEncodingSynapse_param();
    params3->filter_length = filter_length;
    params3->threshold = 0.995;
    params3->scale = 1.0/8.0;
    BSA_SpikeEncodingSynapse* s3 = new BSA_SpikeEncodingSynapse(p2, p4, params3);

    BSA_SpikeDecodingSynapse_param* params4 = new BSA_SpikeDecodingSynapse_param();
    params4->filter_length = filter_length;
    params4->threshold = 0.995;
    params4->scale = 1.0/8.0;
    BSA_SpikeDecodingSynapse* s4 = new BSA_SpikeDecodingSynapse(p4, p5, params4);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = dt;
    Network n = Network(n_param);

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);
    n.add(s3);
    n.add(s4);

    cout << (long)s2 << endl;
    cout << (long)s4 << endl;
    cout << (long)p3 << endl;
    cout << (long)p4 << endl;

    // Run the network for 1 second
    n.run(10.0);
    
    return 0;
}