#include <iostream>
#include "Network/Population/Population.h"

using namespace std;

int main() 
{
    // Neuron* n = new LIF();
    Population* p = new Population(10, "iaf");
    return 0;
}