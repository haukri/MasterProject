#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/BSA_SpikeEncodingSynapse.h"

using namespace std;

int main() 
{
    srand(time(NULL));

    ANN* ann = new ANN();
    ann->setInputSize(1);
    ann->addLayer(1, "tanh");

    Eigen::MatrixXd w = Eigen::MatrixXd(1, 1);
    w(0,0) = 0.05;
    Eigen::MatrixXd b = Eigen::MatrixXd(1, 1);
    b(0,0) = 0.0;
    static_cast<Dense*>(ann->getLayer(0))->setWeights(w);
    static_cast<Dense*>(ann->getLayer(0))->setBiases(b);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f = 0.1;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    ArtificialPopulation* p2 = new ArtificialPopulation(ann);

    Population* p3 = new Population(1, "PassThrough");
    cout << (long)p3 << endl;

    // Synapses
    BSA_SpikeEncodingSynapse_param* params1 = new BSA_SpikeEncodingSynapse_param();
    params1->threshold = 0.955;
    BSA_SpikeEncodingSynapse* s1 = new BSA_SpikeEncodingSynapse(p1, p3, params1);

    RateCodingSynapse* s2 = new RateCodingSynapse(p3, p2);


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