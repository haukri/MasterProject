#include <iostream>
#include "Network/Population/Population.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"

using namespace std;

int main() 
{
    // Define population 1 with custom parameters
    LIF_param* p1_param = new LIF_param();
    p1_param->r = 2.0;
    Population* p1 = new Population(10, "iaf", p1_param);

    // Define population 2 with default parameters
    Population* p2 = new Population(10, "iaf");
    
    // Connect the two populations together with a synapse
    StaticSynapse* s1 = new StaticSynapse(p1, p2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.01;
    Network n = Network();

    // Add the synapse to the network
    n.add(s1);

    // Run the network for 100 milliseconds
    n.run(100);

    // Neuron* n = new LIF();
    // Population* p = new Population(10, "iaf");
    //LIF_param p = LIF_param();
    //LIF n = LIF(&p);
    //for(int i = 0; i < 1300; i++) {
    //    n.update(0.3, 0.01);
    //    cout << n.getMembranePotential() << endl;
    //} 
    return 0;
}