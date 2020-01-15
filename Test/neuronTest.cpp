#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/utils/Event.h"

using namespace std;

int main() 
{
    Izhikevich_param* p = new Izhikevich_param();
    Izhikevich n = Izhikevich(0, 0, p);
    Event* e = new NoEvent();

    for(int i = 0; i < 1300; i++) {
        if(i == 500) {
            e = new SpikeEvent();
            static_cast<SpikeEvent*>(e)->multiplicity = 1;
            static_cast<SpikeEvent*>(e)->weight = 1.0;
        }
        else if(i == 800) {
            e = new NoEvent();
        }

        n.handleEvent(e);
        n.update(0.3);
        cout << n.getMembranePotential() << endl;
        n.resetInput();
    }
    return 0;
}