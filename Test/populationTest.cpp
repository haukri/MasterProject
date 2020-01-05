#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/utils/Event.h"

using namespace std;

int main() 
{
    SpikingPopulation* p1 = new SpikingPopulation(1, "izhikevich");
    Event* e = new NoEvent();

    Clock* clock = Clock::getInstance();
    clock->setDt(0.01);

    for(int i = 0; i < 1000; i++) {
        clock->tick();
        if(i == 100) {
            e = new SpikeEvent();
            static_cast<SpikeEvent*>(e)->multiplicity = 1;
            static_cast<SpikeEvent*>(e)->weight = 1.0;
        }
        else if(i == 600) {
            e = new NoEvent();
        }
        p1->setInput(0, e);
        p1->update();
        if(p1->output[0]) {
            // cout << i << endl;
        }
    }
    return 0;
}