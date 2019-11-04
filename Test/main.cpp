#include <iostream>
#include "../Network/ANN/ANN.h"
#include "../Eigen/Dense"

using namespace std;

int main() 
{
    ANN n = ANN();
    n.setInputSize(5);
    n.addLayer(10);
    n.addLayer(20);
    n.addLayer(2);
    n.build();
    Eigen::MatrixXf input = Eigen::MatrixXf(1, 5);
    n.predict(input);
    return 0;
}