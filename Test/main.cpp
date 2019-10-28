#include <iostream>
#include "../Network/ANN/ANN.h"

using namespace std;

int main() 
{
    ANN n = ANN();
    n.setInputSize(5);
    n.addLayer(10);
    n.addLayer(20);
    n.setOutputSize(4);
    n.build();
    return 0;
}