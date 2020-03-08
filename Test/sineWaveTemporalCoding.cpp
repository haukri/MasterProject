#include <iostream>
#include "Network/Population/SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Synapse/StaticSynapse.h"
#include "Network/Synapse/RateCodingSynapse.h"
#include "Network/Network.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/ANN/ANN.h"
#include "Network/Population/ArtificialPopulation.h"
#include "Network/Synapse/TemporalPhaseEncodingSynapse.h"
#include "Network/Synapse/TemporalPhaseDecodingSynapse.h"

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
    paramp1->f = 0.1;
    Population* p1 = new Population(1, "SignalGenerator", paramp1);

    ArtificialPopulation* p2 = new ArtificialPopulation(ann);

    Population* p3 = new Population(1, "PassThrough");
    cout << (long)p3 << endl;

    // Synapses
    TemporalPhaseEncodingSynapse_param* params1 = new TemporalPhaseEncodingSynapse_param();
    params1->window_length_s = 0.1;
    params1->som_frequency = 800;
    // params1->som_phase = -M_PI / 2;
    TemporalPhaseEncodingSynapse* s1 = new TemporalPhaseEncodingSynapse(p1, p3, params1);

    TemporalPhaseDecodingSynapse_param* params2 = new TemporalPhaseDecodingSynapse_param();
    params2->window_length_s = 0.1;
    params2->som_frequency = 800;
    // params2->som_phase = M_PI / 2;
    TemporalPhaseDecodingSynapse* s2 = new TemporalPhaseDecodingSynapse(p3, p2, params2);

    // Create the network

    Network_param* n_param = new Network_param();
    n_param->dt = 0.001;
    Network n = Network(n_param);

    // Add the synapse to the network
    n.add(s1);
    n.add(s2);

    // Run the network for 100 second
    n.run(50.0);
    
    return 0;
}