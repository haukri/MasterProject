#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/Neuron/CurrentGenerator.h"

using namespace std;

int main() 
{
    // Populations
    Izhikevich_param* p1_param = new Izhikevich_param();
    SpikingPopulation* p1 = new SpikingPopulation(1, "izhikevich", p1_param);

    Izhikevich_param* p2_param = new Izhikevich_param();
    SpikingPopulation* p2 = new SpikingPopulation(1, "izhikevich", p2_param);

    CurrentGenerator_param* p3_param = new CurrentGenerator_param();
    p3_param->I = 500;
    SpikingPopulation* p3 = new SpikingPopulation(1, "CurrentGenerator", p3_param);
    
    // Synapses
    StaticSynapse* s4 = new StaticSynapse(p3, p2);
    s4->setWeight(0, 0, 1);
    StaticSynapse* s1 = new StaticSynapse(p3, p1);
    s1->setWeight(0, 0, 1);


    StaticSynapse* s2 = new StaticSynapse(p1, p2);
    s2->setWeight(0, 0, -20);

    StaticSynapse* s3 = new StaticSynapse(p2, p1);
    s3->setWeight(0, 0, -20);

    cout << (long)p1 << endl;
    cout << (long)p2 << endl;

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.0001;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);
    n.add(s4);
    n.add(s2);
    n.add(s3);


    // Run the network for 100 second
    n.run(100.0);
    
    return 0;
}