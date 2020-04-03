#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"

using namespace std;

int run() {
    srand(time(NULL));

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.001;
    Network n = Network(n_param);

    // Populations
    SpikingPopulation* p1 = new SpikingPopulation(10, "iaf_psc_alpha");

    SpikingPopulation* p2 = new SpikingPopulation(1, "iaf_psc_alpha");

    CurrentGenerator_param* c1_param = new CurrentGenerator_param();
    c1_param->I = 10;
    c1_param->noiseOn = 1;
    c1_param->noiseMean = 30;
    c1_param->noiseStd = 10;
    SpikingPopulation* c1 = new SpikingPopulation(10, "CurrentGenerator", c1_param);
    

    // Synapses
    StaticSynapse* s1 = new StaticSynapse(c1, p1);
    for(int i = 0; i < 10; i++) {
        s1->setWeight(i, i, 10);
    }

    StaticSynapse* s2 = new StaticSynapse(p1, p2);
    for(int i = 0; i < 10; i++) {
        s2->setWeight(i, 0, 200);
    }

    cout << (long)p1 << endl;
    cout << (long)p2 << endl;


    // Add the synapse to the network
    n.add(s1);
    n.add(s2);


    // Run the network for 100 second
    n.run(100.0);
    
    return 0;
}

int main() 
{
    try {
        return run();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
    catch (...) { cout << "default exception"; }
}