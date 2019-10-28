#include <iostream>
#include "../Network/ANN/ANN.h"

using namespace std;

int main() 
{
    ANN n = ANN();
    n.addLayer(10);
    return 0;
}