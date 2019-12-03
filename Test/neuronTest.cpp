#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"

using namespace std;

int main() 
{
    Izhikevich_param* p = new Izhikevich_param();
    Izhikevich n = Izhikevich(p);

    for(int i = 0; i < 1300; i++) {
        n.update(0.3, 0.1);
        cout << n.getMembranePotential() << endl;
    }
    return 0;
}