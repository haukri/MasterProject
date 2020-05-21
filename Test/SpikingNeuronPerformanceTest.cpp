#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/iaf_psc_alpha.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    int populationSize = 50;
    if(argc > 1) {
        populationSize = atoi(argv[1]);
    }
    // Define population 1 with custom parameters
    SpikingPopulation* p1 = new SpikingPopulation(populationSize, "iaf_psc_alpha");
    SpikingPopulation* p2 = new SpikingPopulation(populationSize, "iaf_psc_alpha");
    
    // Connect the two populations together with a synapse
    StaticSynapse* s1 = new StaticSynapse(p1, p2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.0001;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);

    // Run the network for 100 second
    n.run(10.0);
    
    return 0;
}