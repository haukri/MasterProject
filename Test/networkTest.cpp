#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"

using namespace std;

int main() 
{
    // Define population 1 with custom parameters
    LIF_param* p1_param = new LIF_param();
    p1_param->r = 2.0;
    SpikingPopulation* p1 = new SpikingPopulation(10, "izhikevich", p1_param);

    // Define population 2 with default parameters
    SpikingPopulation* p2 = new SpikingPopulation(10, "izhikevich");
    
    // Connect the two populations together with a synapse
    StaticSynapse* s1 = new StaticSynapse(p1, p2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.01;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);

    // Run the network for 1 second
    n.run(1.0);
    
    return 0;
}