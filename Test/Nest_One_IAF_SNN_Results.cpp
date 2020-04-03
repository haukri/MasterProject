#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Neuron/iaf_psc_alpha.h"

using namespace std;

int run() {
    srand(time(NULL));

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.001;
    Network n = Network(n_param);

    // Populations
    iaf_psc_alpha_param* param_p1 = new iaf_psc_alpha_param();
    param_p1->I_e_ = 376.0;
    SpikingPopulation* p1 = new SpikingPopulation(1, "iaf_psc_alpha", param_p1);

    SpikingPopulation* p2 = new SpikingPopulation(1, "iaf_psc_alpha");
    
    cout << (long)p1 << endl;

    StaticSynapse* s1 = new StaticSynapse(p1, p1);

    n.add(s1);

    // Run the network for 100 second
    n.run(1.0);
    
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