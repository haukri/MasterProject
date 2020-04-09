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
#include "Network/Neuron/CurrentGenerator.h"
#include "Network/Synapse/BSA_SpikeEncodingSynapse.h"
#include "Network/Synapse/BSA_SpikeDecodingSynapse.h"

using namespace std;

int run() {
    srand(time(NULL));

    int numberOfNeurons = 200;

    // Create the network
    Network_param* n_param = new Network_param();
    n_param->dt = 0.0001;
    Network n = Network(n_param);

    // Create ANN
    ANN* ann = new ANN();
    ann->setInputSize(1);
    ann->addLayer(3, "tanh");

    Eigen::MatrixXd w = Eigen::MatrixXd(1, 3);
    w(0,0) = 1;
    w(0,1) = 1.5;
    w(0,2) = 2;
    Eigen::MatrixXd b = Eigen::MatrixXd(1, 3);
    b(0,0) = -3.5;
    b(0,1) = -7;
    b(0,2) = -7.5;
    static_cast<Dense*>(ann->getLayer(0))->setWeights(w);
    static_cast<Dense*>(ann->getLayer(0))->setBiases(b);

    ArtificialPopulation* pout = new ArtificialPopulation(ann);

    CurrentGenerator_param* param_c1 = new CurrentGenerator_param();
    param_c1->ac_hz = 35;
    param_c1->I = 0;
    SpikingPopulation* p1 = new SpikingPopulation(numberOfNeurons, "CurrentGenerator", param_c1);
    CurrentGenerator_param* param_c2 = new CurrentGenerator_param();
    param_c2->I = 0;
    param_c2->noiseOn = 1;
    param_c2->noiseMean = 0;
    param_c2->noiseStd = 200;
    SpikingPopulation* p3 = new SpikingPopulation(numberOfNeurons, "CurrentGenerator", param_c2);

    // Populations
    iaf_psc_alpha_param* param_p1 = new iaf_psc_alpha_param();
    param_p1->I_e_ = 200.0;
    param_p1->V_reset_ = -10;
    param_p1->Theta_ = 10;
    param_p1->C_ = 200;
    param_p1->Tau_ = 20;
    param_p1->TauR_ = 2;
    SpikingPopulation* p2 = new SpikingPopulation(numberOfNeurons, "iaf_psc_alpha", param_p1);

    RateCodingSynapse_param* param_s1 = new RateCodingSynapse_param();
    param_s1->time_window = 0.1;
    RateCodingSynapse* s1 = new RateCodingSynapse(p2, pout, param_s1);

    StaticSynapse* s2 = new StaticSynapse(p1, p2);
    for(int i = 0; i < numberOfNeurons; i++) {
        s2->setWeight(i, i, 50.0);
    }
    StaticSynapse* s3 = new StaticSynapse(p3, p2);
    for(int i = 0; i < numberOfNeurons; i++) {
        s3->setWeight(i, i, 1.0);
    }

    Population* p4 = new Population(3, "PassThrough");
    SpikingPopulation* p5 = new SpikingPopulation(3, "iaf_psc_alpha");


    BSA_SpikeEncodingSynapse_param* param_s7 = new BSA_SpikeEncodingSynapse_param();
    param_s7->filter_length = 100;
    param_s7->threshold = 0.95;
    BSA_SpikeEncodingSynapse* s7 = new BSA_SpikeEncodingSynapse(pout, p4, param_s7);

    BSA_SpikeDecodingSynapse_param* param_s8 = new BSA_SpikeDecodingSynapse_param();
    param_s8->filter_length = 100;
    param_s8->threshold = 0.95;
    BSA_SpikeDecodingSynapse* s8 = new BSA_SpikeDecodingSynapse(p4, p5, param_s8);

    n.add(s1);
    n.add(s2);
    n.add(s3);
    n.add(s7);
    n.add(s8);

    cout << (long)p2 << endl;
    cout << "ann " << (long)pout << endl;
    cout << "ratecoding " << (long)s1 << endl;
    cout << "bsa " << (long)s7 << endl;
    cout << "rateend " << (long)s8 << endl;

    // Run the network
    n.run(0.6);
    
    return 0;
}

int main() 
{
    try {
        return run();
    }
    catch (int param) { cout << "int exception"; }
    catch (char param) { cout << "char exception"; }
    catch (string param) { cout << "string exception: " + param; }
    catch (...) { cout << "default exception"; }
}