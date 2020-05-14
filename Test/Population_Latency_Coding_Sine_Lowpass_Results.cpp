#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/ReceptiveFieldEncodingSynapse.h"
#include "Network/Synapse/ReceptiveFieldDecodingSynapse.h"

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
    double window_length_s = 20;
    int number_of_neurons = 30;
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
        window_length_s = atof(argv[8]);
        number_of_neurons = atoi(argv[9]);
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
    paramp1->scale = 1/16.0;
    paramp1->offset = 0.5;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    ArtificialPopulation* p2 = new ArtificialPopulation(ann);

    Population* p3 = new Population(number_of_neurons, "PassThrough");
    Population* p4 = new Population(number_of_neurons, "PassThrough");
    Population* p5 = new Population(1, "PassThrough");

    // Synapses
    ReceptiveFieldEncodingSynapse_param* params1 = new ReceptiveFieldEncodingSynapse_param();
    params1->window_length_s = window_length_s;
    params1->number_of_neurons = number_of_neurons;
    params1->input_min = 0;
    params1->input_max = 1;
    ReceptiveFieldEncodingSynapse* s1 = new ReceptiveFieldEncodingSynapse(p1, p3, params1);

    ReceptiveFieldDecodingSynapse_param* params2 = new ReceptiveFieldDecodingSynapse_param();
    params2->window_length_s = window_length_s;
    params2->number_of_neurons = number_of_neurons;
    params2->input_min = 0;
    params2->input_max = 1;
    ReceptiveFieldDecodingSynapse* s2 = new ReceptiveFieldDecodingSynapse(p3, p2, params2);

    // Synapses
    ReceptiveFieldEncodingSynapse_param* params3 = new ReceptiveFieldEncodingSynapse_param();
    params3->window_length_s = window_length_s;
    params3->number_of_neurons = number_of_neurons;
    params3->input_min = 0;
    params3->input_max = 1;
    ReceptiveFieldEncodingSynapse* s3 = new ReceptiveFieldEncodingSynapse(p2, p4, params3);

    ReceptiveFieldDecodingSynapse_param* params4 = new ReceptiveFieldDecodingSynapse_param();
    params4->window_length_s = window_length_s;
    params4->number_of_neurons = number_of_neurons;
    params4->input_min = 0;
    params4->input_max = 1;
    ReceptiveFieldDecodingSynapse* s4 = new ReceptiveFieldDecodingSynapse(p4, p5, params4);

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

    // Run the network for 1 second
    n.run(1.0);
    
    return 0;
}