#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/BSA_SpikeEncodingSynapse.h"

using namespace std;

int main(int argc, char* argv[]) 
{

    int populationSize = 50;
    if(argc > 1) {
        populationSize = atoi(argv[1]);
    }

    ANN* ann1 = new ANN();
    ann1->setInputSize(populationSize);
    ann1->addLayer(populationSize, "tanh");

    ANN* ann2 = new ANN();
    ann2->setInputSize(populationSize);
    ann2->addLayer(populationSize, "tanh");


    ArtificialPopulation* p1 = new ArtificialPopulation(ann1);
    ArtificialPopulation* p2 = new ArtificialPopulation(ann2);

    StaticSynapse* s1 = new StaticSynapse(p1, p2);

    // Create the network

    Network_param* n_param = new Network_param();
    n_param->dt = 0.01;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);

    // Run the network for 10 second
    n.run(10.0);
    
    return 0;
}