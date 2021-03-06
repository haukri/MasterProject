#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"

using namespace std;

int main() 
{
    // Define population 1 with custom parameters
    Izhikevich_param* p1_param = new Izhikevich_param();
    p1_param->v_thres = 40;
    SpikingPopulation* p1 = new SpikingPopulation(10, "izhikevich", p1_param);

    // Define population 2 with default parameters
    SpikingPopulation* p2 = new SpikingPopulation(10, "izhikevich");

    // Create a current generator
    SpikingPopulation* p3 = new SpikingPopulation(10, "CurrentGenerator");
    
    // Connect the two populations together with a synapse
    StaticSynapse* s1 = new StaticSynapse(p3, p1);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.01;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);

    // Run the network for 100 second
    n.run(100.0);
    
    return 0;
}