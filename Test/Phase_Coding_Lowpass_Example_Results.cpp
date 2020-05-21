#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/TemporalPhaseEncodingSynapse.h"
#include "Network/Synapse/TemporalPhaseDecodingSynapse.h"
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
    double window_length = 20;
    double som_frequency = 80000;
    double dt = 0.0001;
    string filterType = "lowpass";
    if(argc == 12) {
        sine1 = atof(argv[1]);
        sine2 = atof(argv[2]);
        sine3 = atof(argv[3]);
        sine4 = atof(argv[4]);
        sine5 = atof(argv[5]);
        sine6 = atof(argv[6]);
        sine7 = atof(argv[7]);
        window_length = atof(argv[8]);
        som_frequency = atof(argv[9]);
        dt = atof(argv[10]);
        filterType = argv[11];
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
    TemporalPhaseEncodingSynapse_param* params1 = new TemporalPhaseEncodingSynapse_param();
    params1->window_length_s = window_length;
    params1->som_frequency = som_frequency;
    TemporalPhaseEncodingSynapse* s1 = new TemporalPhaseEncodingSynapse(p1, p3, params1);

    TemporalPhaseDecodingSynapse_param* params2 = new TemporalPhaseDecodingSynapse_param();
    params2->window_length_s = window_length;
    params2->delay_s = 0.004;
    params2->som_frequency = som_frequency;
    TemporalPhaseDecodingSynapse* s2 = new TemporalPhaseDecodingSynapse(p3, p2, params2);

    // Synapses
    TemporalPhaseEncodingSynapse_param* params3 = new TemporalPhaseEncodingSynapse_param();
    params3->window_length_s = window_length;
    params3->som_frequency = som_frequency;
    TemporalPhaseEncodingSynapse* s3 = new TemporalPhaseEncodingSynapse(p2, p4, params3);

    TemporalPhaseDecodingSynapse_param* params4 = new TemporalPhaseDecodingSynapse_param();
    params4->window_length_s = window_length;
    params4->delay_s = 0.003;
    params4->som_frequency = som_frequency;
    TemporalPhaseDecodingSynapse* s4 = new TemporalPhaseDecodingSynapse(p4, p5, params4);

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