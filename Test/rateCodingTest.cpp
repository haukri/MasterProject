#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"

using namespace std;

int main() 
{
    srand(time(NULL));

    // Populations

    Izhikevich_param* p1_param = new Izhikevich_param();
    p1_param->v_thres = 40;
    SpikingPopulation* p1 = new SpikingPopulation(10, "izhikevich", p1_param);

    SpikingPopulation* c1 = new SpikingPopulation(10, "CurrentGenerator");

    SpikingPopulation* p2 = new SpikingPopulation(10, "izhikevich");
    

    // Synapses

    StaticSynapse* s1 = new StaticSynapse(c1, p1);

    RateCodingSynapse* s2 = new RateCodingSynapse(p1, p2);


    // Create the network

    Network_param* n_param = new Network_param();
    n_param->dt = 0.01;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);

    // Run the network for 100 second
    n.run(100.0);
    
    return 0;
}