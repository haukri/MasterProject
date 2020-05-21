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
    double som_frequency = 100;
    double som_phase = 0;
    double window_length_s = 0.1;
    double dt = 0.0001;
    double mean = 0;
    double variance = 0;
    if(argc >= 12) {
        sine1 = atof(argv[1]);
        sine2 = atof(argv[2]);
        sine3 = atof(argv[3]);
        sine4 = atof(argv[4]);
        sine5 = atof(argv[5]);
        sine6 = atof(argv[6]);
        sine7 = atof(argv[7]);
        som_frequency = atof(argv[8]);
        som_phase = atof(argv[9]);
        window_length_s = atof(argv[10]);
        dt = atof(argv[11]);
    }
    if(argc == 14) {
        mean = atof(argv[12]);
        variance = atof(argv[13]);
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
    TemporalPhaseEncodingSynapse_param* params1 = new TemporalPhaseEncodingSynapse_param();
    params1->window_length_s = window_length_s;
    params1->som_frequency = som_frequency;
    params1->som_phase = som_phase;
    TemporalPhaseEncodingSynapse* s1 = new TemporalPhaseEncodingSynapse(p1, p3, params1);

    TemporalPhaseDecodingSynapse_param* params2 = new TemporalPhaseDecodingSynapse_param();
    params2->window_length_s = window_length_s;
    params2->som_frequency = som_frequency;
    params2->som_phase = som_phase;
    TemporalPhaseDecodingSynapse* s2 = new TemporalPhaseDecodingSynapse(p3, p4, params2);

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