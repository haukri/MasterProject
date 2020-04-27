#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/BSA_SpikeDecodingSynapse.h"
#include "Network/Synapse/BSA_SpikeEncodingSynapse.h"

using namespace std;

int main() 
{
    srand(time(NULL));

    ANN* ann = new ANN();
    ann->setInputSize(1);
    ann->addLayer(1, "tanh");

    Eigen::MatrixXd w = Eigen::MatrixXd(1, 1);
    w(0,0) = 0.1;
    Eigen::MatrixXd b = Eigen::MatrixXd(1, 1);
    b(0,0) = 0.0;
    static_cast<Dense*>(ann->getLayer(0))->setWeights(w);
    static_cast<Dense*>(ann->getLayer(0))->setBiases(b);

    // Populations
    SignalGenerator_param* paramp1 = new SignalGenerator_param();
    paramp1->f1 = 6;
    paramp1->f2 = 4;
    paramp1->scale = 0.15;
    paramp1->offset = 0.5;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    ArtificialPopulation* p2 = new ArtificialPopulation(ann);

    Population* p3 = new Population(1, "PassThrough");
    cout << (long)p3 << endl;

    // Synapses
    BSA_SpikeEncodingSynapse_param* params1 = new BSA_SpikeEncodingSynapse_param();
    params1->filter_length = 21;
    params1->threshold = 0.995;
    params1->scale = 1.0/10.0;
    BSA_SpikeEncodingSynapse* s1 = new BSA_SpikeEncodingSynapse(p1, p3, params1);

    BSA_SpikeDecodingSynapse_param* params2 = new BSA_SpikeDecodingSynapse_param();
    params2->filter_length = 21;
    params2->threshold = 0.995;
    params2->scale = 1.0/10.0;
    BSA_SpikeDecodingSynapse* s2 = new BSA_SpikeDecodingSynapse(p3, p2, params2);

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.0001;
    Network n = Network(n_param);

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);

    cout << (long)s1 << endl;
    cout << (long)s2 << endl;

    // Run the network for 100 second
    n.run(5.0);
    
    return 0;
}